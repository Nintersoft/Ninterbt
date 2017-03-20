{*******************************************************}
{                                                       }
{         Delphi FireMonkey Notification Service        }
{                                                       }
{           Helpers for Android implementations         }
{                                                       }
{ Copyright(c) 2013-2014 Embarcadero Technologies, Inc. }
{                                                       }
{*******************************************************}

unit FMX.Helpers.Android;

interface

{$SCOPEDENUMS ON}

uses
  Androidapi.JNI.GraphicsContentViewText, FMX.Surfaces, FMX.Graphics, FMX.Controls;

function IsGingerbreadDevice: Boolean;
function GetNativeTheme: Integer; overload;
function GetNativeTheme(const AControl: TControl): Integer; overload;

{ Surface convertions }

function JBitmapToSurface(const SrcBitmap: JBitmap; const DestSurface: TBitmapSurface): Boolean;
function SurfaceToJBitmap(const SrcSurface: TBitmapSurface; const DestBitmap: JBitmap): Boolean;
function NativeViewToSurface(const ANativeView: JView; const ASurface: TBitmapSurface): Boolean;

{ Work with UI Thread }

type
  TMethodCallback = procedure of object;
  TCallBack = reference to procedure;

procedure CallInUIThread(AMethod: TMethodCallback); overload;
procedure CallInUIThread(AMethod: TCallBack); overload;
procedure CallInUIThreadAndWaitFinishing(AMethod: TMethodCallback); overload;
procedure CallInUIThreadAndWaitFinishing(AMethod: TCallBack); overload;

implementation

uses
  Androidapi.Bitmap, Androidapi.Helpers, Androidapi.JNI.App, Androidapi.JNI.JavaTypes,
  Androidapi.JNIBridge, FMX.Platform, FMX.Types, FMX.Styles, FMX.Forms, System.Generics.Collections,
  System.SyncObjs, System.SysUtils;

const
  ANDROID_LIGHT_THEME = '[LIGHTSTYLE]';
  ANDROID_DARK_THEME = '[DARKSTYLE]';
	
function IsGingerbreadDevice: Boolean;
begin
  Result := TOSVersion.Major = 2;
end;

function GetThemeFromDescriptor(ADescriptor: TStyleDescription): Integer;
begin
  Result := 0;
  if ADescriptor <> nil then
  begin
    if ADescriptor.PlatformTarget.Contains(ANDROID_LIGHT_THEME) then
      Result := TJAlertDialog.JavaClass.THEME_HOLO_LIGHT;
    if ADescriptor.PlatformTarget.Contains(ANDROID_DARK_THEME) then
      Result := TJAlertDialog.JavaClass.THEME_HOLO_DARK;
  end;
end;

function GetNativeTheme: Integer;
var
  LStyleDescriptor: TStyleDescription;
begin
  Result := 0;
  if not IsGingerbreadDevice and (Screen <> nil) and (Screen.ActiveForm <> nil) and
    (Screen.ActiveForm.StyleBook <> nil) then
  begin
    LStyleDescriptor := TStyleManager.FindStyleDescriptor(Screen.ActiveForm.StyleBook.Style);
    //GetThemeFromDescriptor(LStyleDescriptor);
	Result := GetThemeFromDescriptor(LStyleDescriptor);
  end;
end;

function GetNativeTheme(const AControl: TControl): Integer;
var
  LStyleDescriptor: TStyleDescription;
begin
  Result := 0;
  if not IsGingerbreadDevice then
  begin
    LStyleDescriptor := TStyleManager.GetStyleDescriptionForControl(AControl);
    //GetThemeFromDescriptor(LStyleDescriptor);
    Result := GetThemeFromDescriptor(LStyleDescriptor);  // <--here the result assignment was missing
  end;
end;

function JBitmapToSurface(const SrcBitmap: JBitmap; const DestSurface: TBitmapSurface): Boolean;
var
  PixelBuffer: Pointer;
  BitmapInfo: AndroidBitmapInfo;
begin
  Result := False;

  FillChar(BitmapInfo, SizeOf(BitmapInfo), 0);

  if AndroidBitmap_getInfo(TJNIResolver.GetJNIEnv, (SrcBitmap as ILocalObject).GetObjectID, @BitmapInfo) <> 0 then
    Exit;

  if AndroidBitmap_lockPixels(TJNIResolver.GetJNIEnv, (SrcBitmap as ILocalObject).GetObjectID, @PixelBuffer) <> 0 then
    Exit;

  try
    DestSurface.SetSize(BitmapInfo.Width, BitmapInfo.Height, TPixelFormat.RGBA);
    Move(PixelBuffer^, DestSurface.Bits^, DestSurface.Pitch * DestSurface.Height);

    Result := True;
  finally
    AndroidBitmap_unlockPixels(TJNIResolver.GetJNIEnv, (SrcBitmap as ILocalObject).GetObjectID);
  end;
end;

function SurfaceToJBitmap(const SrcSurface: TBitmapSurface; const DestBitmap: JBitmap): Boolean;
var
  PixelBuffer: Pointer;
  BitmapInfo: AndroidBitmapInfo;
begin
  Result := False;

  FillChar(BitmapInfo, SizeOf(BitmapInfo), 0);

  if AndroidBitmap_getInfo(TJNIResolver.GetJNIEnv, (DestBitmap as ILocalObject).GetObjectID, @BitmapInfo) <> 0 then
    Exit;

  if AndroidBitmap_lockPixels(TJNIResolver.GetJNIEnv, (DestBitmap as ILocalObject).GetObjectID, @PixelBuffer) <> 0 then
    Exit;

  try
    Move(SrcSurface.Bits^, PixelBuffer^, SrcSurface.Pitch * SrcSurface.Height);

    Result := True;
  finally
    AndroidBitmap_unlockPixels(TJNIResolver.GetJNIEnv, (DestBitmap as ILocalObject).GetObjectID);
  end;
end;

function NativeViewToSurface(const ANativeView: JView; const ASurface: TBitmapSurface): Boolean;
var
  NativeBitmap: JBitmap;
  OldCacheEnabledValue: Boolean;
  OldCacheQualityValue: Integer;
  Successful: Boolean;
begin
  CallInUIThreadAndWaitFinishing(procedure begin
    OldCacheEnabledValue := ANativeView.isDrawingCacheEnabled;
    OldCacheQualityValue := ANativeView.getDrawingCacheQuality;

    ANativeView.setDrawingCacheEnabled(True);
    ANativeView.setDrawingCacheQuality(TJView.JavaClass.DRAWING_CACHE_QUALITY_HIGH);
    try
      NativeBitmap := ANativeView.getDrawingCache;
      if NativeBitmap <> nil then
      begin
        Successful := JBitmapToSurface(NativeBitmap, ASurface);
      end;
    finally
      ANativeView.setDrawingCacheEnabled(OldCacheEnabledValue);
      ANativeView.setDrawingCacheQuality(OldCacheQualityValue);
    end;
  end);
  Result := Successful;
end;

type

  TRunnable = class (TJavaLocal, JRunnable)
  strict private
    FActivity: JActivity;
    FMethodCallback: TMethodCallback;
    FCallback: TCallBack;
    FFinished: Boolean;
  public
    constructor Create; overload;
    constructor Create(ACallback: TCallBack); overload;
    constructor Create(AMethodCallback: TMethodCallback); overload;
    procedure Start;
    { JRunnable }
    procedure run; cdecl;
    property Finished: Boolean read FFinished;
  end;

  TFinishedRunnableCollector = class
  strict private class var
    FFinishedThreadCollector : TFinishedRunnableCollector;
  strict private
    FTimerService: IFMXTimerService;
    FTimerHandle: Cardinal;
    procedure DoTimer;
    function SupportTimer: Boolean;
    function HasTimer: Boolean;
    procedure Start(Timeout: Integer = 2000);
  public
    constructor Create;
    class procedure Call(Timeout: Integer = 2000);
  end;

var
  ActiveJavaRunnables: TThreadList<TRunnable>;

procedure CallInUIThread(AMethod: TMethodCallback); overload;
var
  Runnable: TRunnable;
begin
  Runnable := TRunnable.Create(AMethod);
  ActiveJavaRunnables.Add(Runnable);
  Runnable.Start;
end;

procedure CallInUIThread(AMethod: TCallBack); overload;
var
  Runnable: TRunnable;
begin
  Runnable := TRunnable.Create(AMethod);
  ActiveJavaRunnables.Add(Runnable);
  Runnable.Start;
end;

procedure CallInUIThreadAndWaitFinishing(AMethod: TMethodCallback); overload;
var
  Event: TEvent;
begin
  Event := TEvent.Create;
  try
    CallInUIThread(procedure()
      begin
        if Assigned(AMethod) then
          AMethod;
        Event.SetEvent;
      end);
    Event.WaitFor;
  finally
    Event.DisposeOf;
  end;
end;

procedure CallInUIThreadAndWaitFinishing(AMethod: TCallBack); overload;
var
  Event: TEvent;
begin
  Event := TEvent.Create;
  try
    CallInUIThread(procedure()
      begin
        if Assigned(AMethod) then
          AMethod;
        Event.SetEvent;
      end);
    Event.WaitFor;
  finally
    Event.DisposeOf;
  end;
end;

{ TRunnable }

constructor TRunnable.Create(ACallback: TCallBack);
begin
  Create;
  FCallback := ACallback;
end;

constructor TRunnable.Create(AMethodCallback: TMethodCallback);
begin
  Create;
  FMethodCallback := AMethodCallback;
end;

constructor TRunnable.Create;
begin
  inherited Create;
  FFinished := False;
  FActivity := SharedActivity;
end;

procedure TRunnable.run;
begin
  try
    if Assigned(FCallback) then
      FCallback;
    if Assigned(FMethodCallback) then
      FMethodCallback;
  finally
    FFinished := True;
    TFinishedRunnableCollector.Call;
  end;
end;

procedure TRunnable.Start;
begin
  if Assigned(FActivity) then
    FActivity.runOnUiThread(Self);
end;

{ TFinishedThreadCollector }

procedure TFinishedRunnableCollector.Start(Timeout: Integer = 2000);
begin
  if SupportTimer then
  begin
    if HasTimer then
      FTimerService.DestroyTimer(FTimerHandle);
    FTimerHandle := FTimerService.CreateTimer(Timeout, DoTimer);
  end;
end;

function TFinishedRunnableCollector.SupportTimer: Boolean;
begin
  Result := Assigned(FTimerService);
end;

procedure TFinishedRunnableCollector.DoTimer;
var
  I: Integer;
  JavaThread: TRunnable;
  List: TList<TRunnable>;
begin
  try
    List := ActiveJavaRunnables.LockList;
    try
      I := 0;
      while (I < List.Count) do
      begin
        JavaThread := List[I];
        if JavaThread.Finished then
          List.Remove(JavaThread)
        else
          Inc(I);
      end;
    finally
      ActiveJavaRunnables.UnlockList;
    end;
  finally
    if SupportTimer then
      FTimerService.DestroyTimer(FTimerHandle);
  end;
end;

function TFinishedRunnableCollector.HasTimer: Boolean;
begin
  Result := FTimerHandle <> 0;
end;

constructor TFinishedRunnableCollector.Create;
begin
  TPlatformServices.Current.SupportsPlatformService(IFMXTimerService, FTimerService);
  FTimerHandle := 0;
end;

class procedure TFinishedRunnableCollector.Call(Timeout: Integer);
begin
  if not Assigned(FFinishedThreadCollector) then
    FFinishedThreadCollector := TFinishedRunnableCollector.Create;

  FFinishedThreadCollector.Start;
end;

initialization
  ActiveJavaRunnables := TThreadList<TRunnable>.Create;

finalization
  ActiveJavaRunnables.DisposeOf;
end.
