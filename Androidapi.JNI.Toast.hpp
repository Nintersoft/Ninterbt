// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Toast.pas' rev: 28.00 (Android)

#ifndef Androidapi_Jni_ToastHPP
#define Androidapi_Jni_ToastHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Androidapi.JNIBridge.hpp>	// Pascal unit
#include <Androidapi.JNI.JavaTypes.hpp>	// Pascal unit
#include <Androidapi.JNI.GraphicsContentViewText.hpp>	// Pascal unit
#include <System.Rtti.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Toast
{
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TToastLength : unsigned char { LongToast, ShortToast };

__interface JToastClass;
typedef System::DelphiInterface<JToastClass> _di_JToastClass;
__interface JToast;
typedef System::DelphiInterface<JToast> _di_JToast;
__interface  INTERFACE_UUID("{69E2D233-B9D3-4F3E-B882-474C8E1D50E9}") JToastClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
public:
	virtual int __cdecl _GetLENGTH_LONG(void) = 0 ;
	virtual int __cdecl _GetLENGTH_SHORT(void) = 0 ;
	HIDESBASE virtual _di_JToast __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	virtual _di_JToast __cdecl makeText(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JCharSequence text, int duration) = 0 ;
	__property int LENGTH_LONG = {read=_GetLENGTH_LONG};
	__property int LENGTH_SHORT = {read=_GetLENGTH_SHORT};
};

__interface  INTERFACE_UUID("{FD81CC32-BFBC-4838-8893-9DD01DE47B00}") JToast  : public Androidapi::Jni::Javatypes::JObject 
{
	
public:
	virtual void __cdecl cancel(void) = 0 ;
	virtual int __cdecl getDuration(void) = 0 ;
	virtual int __cdecl getGravity(void) = 0 ;
	virtual float __cdecl getHorizontalMargin(void) = 0 ;
	virtual float __cdecl getVerticalMargin(void) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getView(void) = 0 ;
	virtual int __cdecl getXOffset(void) = 0 ;
	virtual int __cdecl getYOffset(void) = 0 ;
	virtual void __cdecl setDuration(int value) = 0 ;
	virtual void __cdecl setGravity(int gravity, int xOffset, int yOffset) = 0 ;
	virtual void __cdecl setMargin(float horizontalMargin, float verticalMargin) = 0 ;
	virtual void __cdecl setText(Androidapi::Jni::Javatypes::_di_JCharSequence s) = 0 ;
	virtual void __cdecl setView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual void __cdecl show(void) = 0 ;
};

class DELPHICLASS TJToast;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TJToast : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToastClass,_di_JToast> 
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToastClass,_di_JToast>  inherited;
	
public:
	/* TJavaImport.Create */ inline __fastcall TJToast(void * ID, void * ClsID, Androidapi::Jnibridge::TJavaVTable* VTable) : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToastClass,_di_JToast> (ID, ClsID, VTable) { }
	/* TJavaImport.Destroy */ inline __fastcall virtual ~TJToast(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall Toast(const System::UnicodeString Msg, TToastLength duration = (TToastLength)(0x1));
}	/* namespace Toast */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_TOAST)
using namespace Androidapi::Jni::Toast;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI)
using namespace Androidapi::Jni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_Jni_ToastHPP
