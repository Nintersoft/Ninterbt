// CodeGear C++Builder
// Copyright (c) 1995, 2014 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.BluetoothAdapter.pas' rev: 28.00 (Android)

#ifndef Androidapi_Jni_BluetoothadapterHPP
#define Androidapi_Jni_BluetoothadapterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <Androidapi.JNIBridge.hpp>	// Pascal unit
#include <Androidapi.JNI.JavaTypes.hpp>	// Pascal unit
#include <System.Classes.hpp>	// Pascal unit
#include <System.Rtti.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Bluetoothadapter
{
//-- type declarations -------------------------------------------------------
__interface JBluetoothSocketClass;
typedef System::DelphiInterface<JBluetoothSocketClass> _di_JBluetoothSocketClass;
__interface  INTERFACE_UUID("{51A8D015-29B2-4D55-91E4-58E22A6823B7}") JBluetoothSocketClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface JBluetoothSocket;
typedef System::DelphiInterface<JBluetoothSocket> _di_JBluetoothSocket;
__interface JBluetoothDevice;
typedef System::DelphiInterface<JBluetoothDevice> _di_JBluetoothDevice;
__interface  INTERFACE_UUID("{C64419F2-762B-4B30-9EB7-468A9FA58822}") JBluetoothSocket  : public Androidapi::Jni::Javatypes::JObject 
{
	
public:
	virtual void __cdecl connect(void) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JInputStream __cdecl getInputStream(void) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JOutputStream __cdecl getOutputStream(void) = 0 ;
	virtual bool __cdecl isConnected(void) = 0 ;
	virtual _di_JBluetoothDevice __cdecl getRemoteDevice(void) = 0 ;
};

class DELPHICLASS TJBluetoothSocket;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TJBluetoothSocket : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothSocketClass,_di_JBluetoothSocket> 
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothSocketClass,_di_JBluetoothSocket>  inherited;
	
public:
	/* TJavaImport.Create */ inline __fastcall TJBluetoothSocket(void * ID, void * ClsID, Androidapi::Jnibridge::TJavaVTable* VTable) : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothSocketClass,_di_JBluetoothSocket> (ID, ClsID, VTable) { }
	/* TJavaImport.Destroy */ inline __fastcall virtual ~TJBluetoothSocket(void) { }
	
};

#pragma pack(pop)

__interface JBluetoothDeviceClass;
typedef System::DelphiInterface<JBluetoothDeviceClass> _di_JBluetoothDeviceClass;
__interface  INTERFACE_UUID("{FB8F9E83-CF98-4737-B7B0-64EFB07EBE2A}") JBluetoothDeviceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{F2560E3D-D26E-4DD8-B384-43070B02FF04}") JBluetoothDevice  : public Androidapi::Jni::Javatypes::JObject 
{
	
public:
	virtual _di_JBluetoothSocket __cdecl createInsecureRfcommSocketToServiceRecord(Androidapi::Jni::Javatypes::_di_JUUID UUID) = 0 ;
	virtual _di_JBluetoothSocket __cdecl createRfcommSocketToServiceRecord(Androidapi::Jni::Javatypes::_di_JUUID UUID) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName(void) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAddress(void) = 0 ;
};

class DELPHICLASS TJBluetoothDevice;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TJBluetoothDevice : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothDeviceClass,_di_JBluetoothDevice> 
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothDeviceClass,_di_JBluetoothDevice>  inherited;
	
public:
	/* TJavaImport.Create */ inline __fastcall TJBluetoothDevice(void * ID, void * ClsID, Androidapi::Jnibridge::TJavaVTable* VTable) : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothDeviceClass,_di_JBluetoothDevice> (ID, ClsID, VTable) { }
	/* TJavaImport.Destroy */ inline __fastcall virtual ~TJBluetoothDevice(void) { }
	
};

#pragma pack(pop)

__interface JBluetoothAdapterClass;
typedef System::DelphiInterface<JBluetoothAdapterClass> _di_JBluetoothAdapterClass;
__interface JBluetoothAdapter;
typedef System::DelphiInterface<JBluetoothAdapter> _di_JBluetoothAdapter;
__interface  INTERFACE_UUID("{05CE5465-2953-4CC3-9D9B-01D71E90F412}") JBluetoothAdapterClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
public:
	virtual _di_JBluetoothAdapter __cdecl getDefaultAdapter(void) = 0 ;
};

__interface  INTERFACE_UUID("{D5C8CAD6-E717-4B95-89F1-A6FD0861B7DB}") JBluetoothAdapter  : public Androidapi::Jni::Javatypes::JObject 
{
	
public:
	virtual bool __cdecl isEnabled(void) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName(void) = 0 ;
	virtual bool __fastcall cancelDiscovery(void) = 0 ;
	virtual bool __cdecl checkBluetoothAddress(Androidapi::Jni::Javatypes::_di_JString Address) = 0 ;
	virtual bool __cdecl disable(void) = 0 ;
	virtual bool __cdecl enable(void) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAddress(void) = 0 ;
	virtual void __cdecl closeProfileProxy(int profile, Androidapi::Jni::Javatypes::_di_JObject BluetoothProfile) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSet __cdecl getBondedDevices(void) = 0 ;
	virtual _di_JBluetoothDevice __cdecl getRemoteDevice(Androidapi::Jni::Javatypes::_di_JString ID) = 0 ;
};

class DELPHICLASS TJBluetoothAdapter;
#pragma pack(push,4)
class PASCALIMPLEMENTATION TJBluetoothAdapter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAdapterClass,_di_JBluetoothAdapter> 
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAdapterClass,_di_JBluetoothAdapter>  inherited;
	
public:
	/* TJavaImport.Create */ inline __fastcall TJBluetoothAdapter(void * ID, void * ClsID, Androidapi::Jnibridge::TJavaVTable* VTable) : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBluetoothAdapterClass,_di_JBluetoothAdapter> (ID, ClsID, VTable) { }
	/* TJavaImport.Destroy */ inline __fastcall virtual ~TJBluetoothAdapter(void) { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall checkBluetooth(void);
extern DELPHI_PACKAGE System::Classes::TStringList* __fastcall getBonded(void);
}	/* namespace Bluetoothadapter */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_BLUETOOTHADAPTER)
using namespace Androidapi::Jni::Bluetoothadapter;
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
#endif	// Androidapi_Jni_BluetoothadapterHPP
