// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Helpers.Android.pas' rev: 28.00 (Android)

#ifndef Fmx_Helpers_AndroidHPP
#define Fmx_Helpers_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Androidapi.JNI.GraphicsContentViewText.hpp>	// Pascal unit
#include <FMX.Surfaces.hpp>	// Pascal unit
#include <FMX.Graphics.hpp>	// Pascal unit
#include <FMX.Controls.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Helpers
{
namespace Android
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TMethodCallback)(void);

__interface TCallBack;
typedef System::DelphiInterface<TCallBack> _di_TCallBack;
__interface TCallBack  : public System::IInterface 
{
	
public:
	virtual void __fastcall Invoke(void) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall IsGingerbreadDevice(void);
extern DELPHI_PACKAGE int __fastcall GetNativeTheme(void)/* overload */;
extern DELPHI_PACKAGE int __fastcall GetNativeTheme(Fmx::Controls::TControl* const AControl)/* overload */;
extern DELPHI_PACKAGE bool __fastcall JBitmapToSurface(const Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap SrcBitmap, Fmx::Surfaces::TBitmapSurface* const DestSurface);
extern DELPHI_PACKAGE bool __fastcall SurfaceToJBitmap(Fmx::Surfaces::TBitmapSurface* const SrcSurface, const Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap DestBitmap);
extern DELPHI_PACKAGE bool __fastcall NativeViewToSurface(const Androidapi::Jni::Graphicscontentviewtext::_di_JView ANativeView, Fmx::Surfaces::TBitmapSurface* const ASurface);
extern DELPHI_PACKAGE void __fastcall CallInUIThread(TMethodCallback AMethod)/* overload */;
extern DELPHI_PACKAGE void __fastcall CallInUIThread(_di_TCallBack AMethod)/* overload */;
extern DELPHI_PACKAGE void __fastcall CallInUIThreadAndWaitFinishing(TMethodCallback AMethod)/* overload */;
extern DELPHI_PACKAGE void __fastcall CallInUIThreadAndWaitFinishing(_di_TCallBack AMethod)/* overload */;
}	/* namespace Android */
}	/* namespace Helpers */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_HELPERS_ANDROID)
using namespace Fmx::Helpers::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_HELPERS)
using namespace Fmx::Helpers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Helpers_AndroidHPP
