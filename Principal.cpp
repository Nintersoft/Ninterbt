//---------------------------------------------------------------------------

#include <fmx.h>
#include <FMX.Helpers.Android.hpp>
#include <Androidapi.JNI.Toast.hpp>
#include <OpenViewUrl.hpp>
#include <Androidapi.Helpers.hpp>
#include <System.IOUtils.hpp>
#include <Androidapi.JNI.BluetoothAdapter.hpp>
#pragma hdrstop

#include "Principal.h"
#include "Carregando.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmPrincipal *frmPrincipal;
//---------------------------------------------------------------------------
	bool adaptado, MudAb = true, Desenv = false, CA, SEM_AD, Manual = false, Auto = false, prim;
	String targetMACAddress;
	_di_JBluetoothAdapter Adapter;
	_di_JBluetoothDevice remoteDevice;
	_di_JBluetoothSocket Sock;
	_di_JInputStream istream;
	_di_JOutputStream ostream;
//---------------------------------------------------------------------------
__fastcall TfrmPrincipal::TfrmPrincipal(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::FormCreate(TObject *Sender)
{
	// This defines the default active tab at runtime
	abasPrinc->ActiveTab = abaDisp;
	Auto = false;
	Manual = false;
	SEM_AD = false;

	//BannerAd1->AdUnitID = "SECRETO";
	//BannerAd2->AdUnitID = "SECRETO";

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::FormKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift)
{
	/*String mensagem;

	if (idioma->Lang == "en") mensagem = "You will quit. Are you sure?";
	else mensagem = "Gostaria de sair da aplicacao?";
	*/
	if(Key == vkHardwareBack) {
		Application->Terminate();
	/*	if (abasPrinc->ActiveTab != abaDisp) {
			abasPrinc->ActiveTab != abaDisp;
			if (Sock->isConnected()) {
				Sock->Release();
				if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Device disconnected successfully!");
				else Androidapi::Jni::Toast::Toast("Dispositivo desconectado!");
				RedefInicio();
			}
		}
		else {
			struct TCloseDialogHandler : public TCppInterfacedObject<TInputCloseDialogProc> {
				void __fastcall Invoke(const System::Uitypes::TModalResult AResult) {
					switch (AResult) {
						case mrYes :
							Application->Terminate();
						break;
					}
				}
			};
			_di_TInputCloseDialogProc handler = new TCloseDialogHandler();

			MessageDlg(mensagem, TMsgDlgType::mtConfirmation, mbYesNo, 0, handler);
		}*/
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrincipal::abasPrincGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
		  bool &Handled)
{
/*#ifdef __ANDROID__
	switch (EventInfo.GestureID) {
		case sgiLeft :
			if(abasPrinc->ActiveTab != abasPrinc->Tabs[abasPrinc->TabCount-1]) {
				abasPrinc->ActiveTab = abasPrinc->Tabs[abasPrinc->TabIndex+1];
				Handled = true;
			}
			break;
		case sgiRight :
			if(abasPrinc->ActiveTab != abasPrinc->Tabs[0]) {
				abasPrinc->ActiveTab = abasPrinc->Tabs[abasPrinc->TabIndex-1];
				Handled = true;
			}
			break;
	default:
		;
	}
#endif
*/
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btNavClick(TObject *Sender)
{
	vsNav->ShowMaster();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btAtualizarClick(TObject *Sender)
{

	int i = 0;
	TStringList* lista = new TStringList;

	String estado = checkBluetooth();

	if (Pos("disabled",estado) != 0) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Please, turn on the buetooth for using this application");
		else Androidapi::Jni::Toast::Toast("Por favor, ligue o bluetooth para usar esta aplicacao");
	}
	else {

		uid = TJUUID::JavaClass->fromString(StringToJString("00001101-0000-1000-8000-00805F9B34FB"));

		lista->Clear();
		lista->AddStrings(getBonded());
		frmPrincipal->lstDisp->Items->Clear();
		frmPrincipal->lstDisp->BeginUpdate();

		for (i = 0; i < lista->Count; i++) {
			frmPrincipal->lstDisp->Items->Add();
			frmPrincipal->lstDisp->Items->Item[i]->Text = frmCarregar->adquireDados(2, lista->Strings[i]);
			frmPrincipal->lstDisp->Items->Item[i]->Detail = frmCarregar->adquireDados(1, lista->Strings[i]);
		}

		frmPrincipal->lstDisp->EndUpdate();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cbEntradaSerialChange(TObject *Sender)
{
	if (cbEntradaSerial->IsChecked) {
		String mensagem;

		if (idioma->Lang == "en") mensagem = "Warning: Just enable this option if your device does not recognize serial bluetooth input/output (Eg.: If your device is recognized as BT headset). Continue?";
		else mensagem = "Aviso: Ative essa opcao apenas se seu dispositivo nao reconhece entrada/saida serial via bluetooth! (Ex.: Caso o dispositivo seja identificado como headset BT). Continuar?";

		struct TCloseDialogHandler : public TCppInterfacedObject<TInputCloseDialogProc> {
			void __fastcall Invoke(const System::Uitypes::TModalResult AResult) {
				switch (AResult) {
					case mrYes :
						frmPrincipal->cbEntradaSerial->IsChecked = true;
					break;
					case mrNo:
						frmPrincipal->cbEntradaSerial->IsChecked = false;
					break;
				}
			}
		};
		_di_TInputCloseDialogProc handler = new TCloseDialogHandler();

		MessageDlg(mensagem, TMsgDlgType::mtConfirmation, mbYesNo, 0, handler);

		if (cbEntradaSerial->IsChecked) adaptar();
	}
}
//---------------------------------------------------------------------------
void TfrmPrincipal::adaptar(){
	adaptado = true;
	btLig->Enabled = true;
	btDesl->Enabled = true;
}
//--------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btAbrDWClick(TObject *Sender)
{
	Openviewurl::OpenURL("http://docwiki.nintersoft.ml/Ninterbt");
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSalvaConfClick(TObject *Sender)
{
	String arq = Ioutils::TPath::Combine(Ioutils::TPath::GetHomePath(), L"ninterbt.conf");
	mmDados->Lines->SaveToFile(arq);
	if (idioma->Lang == "en") ShowMessage("Please, restart this application to apply all the saved settings");
	else ShowMessage("Por favor, reinicie a aplicacao para aplicar as novas configuracoes");
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cbDesChange(TObject *Sender)
{

	if (cbDes->IsChecked && mmDados->Lines->Strings[1] != "NBTS") {

		String mensagem;

		if (idioma->Lang == "en") mensagem = "Warning: Just enable this option under development circunstances. Do you really want to continue?";
		else mensagem = "Aviso: Ative esta opcao apenas para fins de teste ou desenvolvimento. Deseja continuar?";

		struct TCloseDialogHandler : public TCppInterfacedObject<TInputCloseDialogProc> {
			void __fastcall Invoke(const System::Uitypes::TModalResult AResult) {
				switch (AResult) {
					case mrYes :
						frmPrincipal->cbDes->IsChecked = true;
					break;
					case mrNo:
						frmPrincipal->cbDes->IsChecked = false;
					break;
				}
			}
		};
		_di_TInputCloseDialogProc handler = new TCloseDialogHandler();

		MessageDlg(mensagem, TMsgDlgType::mtConfirmation, mbYesNo, 0, handler);

	}

	mmDados->BeginUpdate();
	if (cbDes->IsChecked) mmDados->Lines->Strings[1] = "NBTS";
	else mmDados->Lines->Strings[1] = "!NBTS";
	mmDados->EndUpdate();


}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::csiAltrClick(TObject *Sender)
{
	mmDados->BeginUpdate();
	mmDados->Lines->Strings[2] = "ALTR";
	mmDados->EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::csiConfClick(TObject *Sender)
{
	mmDados->BeginUpdate();
	mmDados->Lines->Strings[2] = "CONF";
	mmDados->EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::csiCtrlClick(TObject *Sender)
{
	mmDados->BeginUpdate();
	mmDados->Lines->Strings[2] = "CTRL";
	mmDados->EndUpdate();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cbMudChange(TObject *Sender)
{
	mmDados->BeginUpdate();
	if (cbMud->IsChecked) mmDados->Lines->Strings[0] = "NBTS";
	else mmDados->Lines->Strings[0] = "!NBTS";
	mmDados->EndUpdate();
	if (cbMud->IsChecked) cxAbaSelec->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::lstDispItemClick(TObject * const Sender, TListViewItem * const AItem)

{
  if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Selected device: " + AItem->Text);
  else Androidapi::Jni::Toast::Toast("Dispositivo selecionado: "+AItem->Text);

  // Dependendo do dispositivo bluetooth selecionado - fazer alguma coisa com ele
	targetMACAddress = AItem->Detail;
	if (Trim(targetMACAddress)=="") goto fim;

	Adapter = TJBluetoothAdapter::JavaClass->getDefaultAdapter();
	remoteDevice = Adapter->getRemoteDevice(StringToJString(targetMACAddress));
	Sock = remoteDevice->createRfcommSocketToServiceRecord(uid);

	try {
		Sock->connect();
	}
	catch (...){
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Cannot connect with the bluetooth device, retrying...");
		else Androidapi::Jni::Toast::Toast("Nao foi possivel conectar-se com o dispositivo bluetooth, tentando novamente...");
		goto fim;
	}
	if (!Sock->isConnected) {
		fim:
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Cannot stabilish a new connection, please, try again.");
		else Androidapi::Jni::Toast::Toast("Falha ao tentar uma nova conexao, tente novamente.");
	}
	else {

		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Connected");
		else Androidapi::Jni::Toast::Toast("Conectado");

		btLig->Enabled = true;
		btDesl->Enabled = true;

		if (MudAb) {
			if (csiCtrl->IsSelected) {
				abasPrinc->ActiveTab = abaControle;
				abasSec->ActiveTab = abaSec;
			}
			else if (csiAltr->IsSelected) {
				abasPrinc->ActiveTab = abaControle;
				abasSec->ActiveTab = abaPrinc;
			}
			else if (csiConf->IsSelected) {
				abasPrinc->ActiveTab = abaConfig;
			}
		}

		ostream = Sock->getOutputStream();
		istream = Sock->getInputStream();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::BannerAd2DidFail(TObject *Sender, const UnicodeString Error)

{
	SEM_AD = true;
	//tmAds->Enabled = true;
	BannerAd2->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::BannerAd1DidFail(TObject *Sender, const UnicodeString Error)

{
	SEM_AD = true;
	//tmAds->Enabled = true;
	BannerAd1->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::BannerAd1DidLoad(TObject *Sender)
{
	tmAds->Enabled = false;
	BannerAd1->Visible = true;
	SEM_AD = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::BannerAd2DidLoad(TObject *Sender)
{
	tmAds->Enabled = false;
	BannerAd2->Visible = true;
	SEM_AD = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmAdsTimer(TObject *Sender)
{
	/*if (!SEM_AD) {
		SEM_AD = false;
		tmAds->Enabled = false;
	}
	else {
		BannerAd1->LoadAd();
		BannerAd2->LoadAd();
	}*/
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btDeslClick(TObject *Sender)
{
  if (CA == false) {
	if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("The circuit is already disabled!");
	else Androidapi::Jni::Toast::Toast("O circuito ja esta desativado!");
  }
  if (CA == true) {
	ostream->write(Num(']'));
	if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Circuit disabled!");
	else Androidapi::Jni::Toast::Toast("Circuito desativado!");
	CA = False;
	RedefInicio();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::vsNavExit(TObject *Sender)
{
	vsNav->HideMaster();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btSelecSobreClick(TObject *Sender)
{
	abasPrinc->ActiveTab = abaSobre;
	vsNav->HideMaster();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btSelecDispClick(TObject *Sender)
{
	abasPrinc->ActiveTab = abaDisp;
	vsNav->HideMaster();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btSelecConfigClick(TObject *Sender)
{
	abasPrinc->ActiveTab = abaConfig;
	vsNav->HideMaster();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::btSelecInClick(TObject *Sender)
{
	abasPrinc->ActiveTab = abaControle;
	abasSec->ActiveTab = abaSec;
	vsNav->HideMaster();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btSelecAlterClick(TObject *Sender)
{
	abasPrinc->ActiveTab = abaControle;
	abasSec->ActiveTab = abaPrinc;
	vsNav->HideMaster();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btLigClick(TObject *Sender)
{
	if (CA) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("The cicruit is already enabled!");
		else Androidapi::Jni::Toast::Toast("Circuito ja esta ativado!");
	}
	else  {
		try {
		ostream->write(Num('['));

			if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Circuit enabled!");
			else Androidapi::Jni::Toast::Toast("Circuito ativado!");

			//  cmControleAuto->Enabled = true;
			cmControleManual->Enabled = true;
			CA = true;
			Alter1->Enabled = true;
			Alter2->Enabled = true;
			Alter3->Enabled = true;
			Alter4->Enabled = true;
			Alter5->Enabled = true;
			Alter6->Enabled = true;
			Alter7->Enabled = true;
			Alter8->Enabled = true;
			Alter9->Enabled = true;
			Alter10->Enabled = true;
			Alter11->Enabled = true;
			Alter12->Enabled = true;
			Alter13->Enabled = true;
			Alter14->Enabled = true;
			Alter15->Enabled = true;
			Alter16->Enabled = true;
			Alter17->Enabled = true;
			Alter18->Enabled = true;
			Alter19->Enabled = true;
			Alter20->Enabled = true;
			Alter21->Enabled = true;
			Alter22->Enabled = true;
			Alter23->Enabled = true;
			Alter24->Enabled = true;
			Alter25->Enabled = true;
		} catch (...) {
		}
	}
}
//---------------------------------------------------------------------------
int TfrmPrincipal::Num (unsigned char caractere){
	int num = caractere;
	return num;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::cmControleAutoChange(TObject *Sender)
{
	try {
		if (Auto) {
			if (!cmControleAuto->IsChecked) {
				Auto = false;
				ostream->write(Num('>'));
				if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Automactic luminosity control disabled");
				else Androidapi::Jni::Toast::Toast("Controle de luminosidade automatica desativado");
			}
		}
		else {
			if (cmControleAuto->IsChecked){
				Auto = true;
				ostream->write(Num('<'));
				if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Automactic luminosity control enabled");
				else Androidapi::Jni::Toast::Toast("Controle de luminosidade automatica ativado");
			}
		}
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------
void TfrmPrincipal::RedefInicio() {

	if (!Desenv) {

		Alter1->IsChecked = false;
		Alter2->IsChecked = false;
		Alter3->IsChecked = false;
		Alter4->IsChecked = false;
		Alter5->IsChecked = false;
		Alter6->IsChecked = false;
		Alter7->IsChecked = false;
		Alter8->IsChecked = false;
		Alter9->IsChecked = false;
		Alter10->IsChecked = false;
		Alter11->IsChecked = false;
		Alter12->IsChecked = false;
		Alter13->IsChecked = false;
		Alter14->IsChecked = false;
		Alter15->IsChecked = false;
		Alter16->IsChecked = false;
		Alter17->IsChecked = false;
		Alter18->IsChecked = false;
		Alter19->IsChecked = false;
		Alter20->IsChecked = false;
		Alter21->IsChecked = false;
		Alter22->IsChecked = false;
		Alter23->IsChecked = false;
		Alter24->IsChecked = false;
		Alter25->IsChecked = false;

		Alter1->Enabled = false;
		Alter2->Enabled = false;
		Alter3->Enabled = false;
		Alter4->Enabled = false;
		Alter5->Enabled = false;
		Alter6->Enabled = false;
		Alter7->Enabled = false;
		Alter8->Enabled = false;
		Alter9->Enabled = false;
		Alter10->Enabled = false;
		Alter11->Enabled = false;
		Alter12->Enabled = false;
		Alter13->Enabled = false;
		Alter14->Enabled = false;
		Alter15->Enabled = false;
		Alter16->Enabled = false;
		Alter17->Enabled = false;
		Alter18->Enabled = false;
		Alter19->Enabled = false;
		Alter20->Enabled = false;
		Alter21->Enabled = false;
		Alter22->Enabled = false;
		Alter23->Enabled = false;
		Alter24->Enabled = false;
		Alter25->Enabled = false;

		cmControleAuto->IsChecked = false;
		cmControleAuto->Enabled = false;

		cmControleManual->IsChecked = false;
		cmControleManual->Enabled = false;

		baLuminosidade->Value = 10;

		Manual = false;
		Auto = false;

	}

}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::cmControleManualChange(TObject *Sender)
{
	try {
		if (Manual) {
			if (!cmControleManual->IsChecked) {
				Manual = false;
				ostream->write(Num('}'));
				if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Manual luminosity control disabled");
				else Androidapi::Jni::Toast::Toast("Controle de luminosidade manual desativado");
			}
		}
		else {
			if (cmControleManual->IsChecked){
				Manual = true;
				ostream->write(Num('{'));
				if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Manual luminosity control enabled");
				else Androidapi::Jni::Toast::Toast("Controle de luminosidade manual ativado");
			}
		}
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::abasPrincChange(TObject *Sender)
{
	if (abasPrinc->ActiveTab == abaControle) {
		if (SEM_AD == false) {
			BannerAd1->Visible = true;
			BannerAd2->Visible = true;
		}
	}
	else {
		if (SEM_AD == false) {
			BannerAd1->Visible = false;
			BannerAd2->Visible = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::baLuminosidadeTracking(TObject *Sender)
{
	if (Manual) {
		try {
			float lum;
			lum = baLuminosidade->Value;
			if (lum <= 1.5) ostream->write(Num('1'));
			else if (lum > 1.5 && lum <= 2.5) ostream->write(Num('2'));
			else if (lum > 2.5 && lum <= 3.5) ostream->write(Num('3'));
			else if (lum > 3.5 && lum <= 4.5) ostream->write(Num('4'));
			else if (lum > 4.5 && lum <= 5.5) ostream->write(Num('5'));
			else if (lum > 5.5 && lum <= 6.5) ostream->write(Num('6'));
			else if (lum > 6.5 && lum <= 7.5) ostream->write(Num('7'));
			else if (lum > 7.5 && lum <= 8.5) ostream->write(Num('8'));
			else if (lum > 8.5 && lum <= 9.5) ostream->write(Num('9'));
			else ostream->write(Num('0'));
		} catch (...) {
			if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
			else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
			abasPrinc->ActiveTab = abaDisp;
			RedefInicio();
		}
	}
	else {
		tmSegura->Enabled = true;
		baLuminosidade->Value = 10;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::tmSeguraTimer(TObject *Sender)
{
	int cont = 0;
	if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("The manual luminosity control is disabled");
	else Androidapi::Jni::Toast::Toast("O controle de luminosidade manual esta desativado");
	do {
		cont++;
	}while (cont < 5);
	tmSegura->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cxAlternResize(TObject *Sender)
{
	Alter1->Position->X = cxAltern->Width - 8 - Alter1->Width;
	Alter2->Position->X = Alter1->Position->X;
	Alter3->Position->X = Alter1->Position->X;
	Alter4->Position->X = Alter1->Position->X;
	Alter5->Position->X = Alter1->Position->X;
	Alter6->Position->X = Alter1->Position->X;
	Alter7->Position->X = Alter1->Position->X;
	Alter8->Position->X = Alter1->Position->X;
	Alter9->Position->X = Alter1->Position->X;
	Alter10->Position->X = Alter1->Position->X;
	Alter11->Position->X = Alter1->Position->X;
	Alter12->Position->X = Alter1->Position->X;
	Alter13->Position->X = Alter1->Position->X;
	Alter14->Position->X = Alter1->Position->X;
	Alter15->Position->X = Alter1->Position->X;
	Alter16->Position->X = Alter1->Position->X;
	Alter17->Position->X = Alter1->Position->X;
	Alter18->Position->X = Alter1->Position->X;
	Alter19->Position->X = Alter1->Position->X;
	Alter20->Position->X = Alter1->Position->X;
	Alter21->Position->X = Alter1->Position->X;
	Alter22->Position->X = Alter1->Position->X;
	Alter23->Position->X = Alter1->Position->X;
	Alter24->Position->X = Alter1->Position->X;
	Alter25->Position->X = Alter1->Position->X;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::cxInicialResize(TObject *Sender)
{
	cmControleAuto->Width = cxInicial->Width - 16;
	cmControleAuto->Position->X = 8;
	cmControleManual->Width = cxInicial->Width - 16;
	cmControleManual->Position->X = 8;
	lblContrLum->Width = cxInicial->Width - 16;
	lblContrLum->Position->X = 8;
	baLuminosidade->Width = cxInicial->Width - 16;
	baLuminosidade->Position->X = 8;
	txtAjdContLum->Width = cxInicial->Width - 16;
	txtAjdContLum->Position->X = 8;
	lblContCirc->Width = cxInicial->Width - 16;
	lblContCirc->Position->X = 8;
	txtAjdContCir->Width = cxInicial->Width - 16;
	txtAjdContCir->Position->X = 8;
	btDesl->Position->X = (cxInicial->Width/2) - btDesl->Width - 2;
	btLig->Position->X = (cxInicial->Width/2) + 2;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::cxConfigResize(TObject *Sender)
{
	cbMud->Width = cxConfig->Width - 16;
	cbMud->Position->X = 8;
	lblConfAjdCBMud->Width = cxConfig->Width - 32;
	lblConfAjdCBMud->Position->X = 16;
	cbDes->Width = cxConfig->Width - 16;
	cbDes->Position->X = 8;
	lblConfAjdCBDes->Width = cxConfig->Width - 32;
	lblConfAjdCBDes->Position->X = 16;
	lblConfAba->Width = cxConfig->Width - 16;
	lblConfAba->Position->X = 8;
	cxAbaSelec->Position->X = cxConfig->Width - cxAbaSelec->Width - 8;
	lblConfAjdCXAS->Width = cxConfig->Width - 32;
	lblConfAjdCXAS->Position->X = 16;
	lblConfLing->Width = cxConfig->Width - 16;
	lblConfLing->Position->X = 8;
	beLangPad->Position->X = cxConfig->Width - beLangPad->Width - 8;
	lblConfAjdIdi->Width = cxConfig->Width - 32;
	lblConfAjdIdi->Position->X = 16;
	btSalvaConf->Position->X = (cxConfig->Width - btSalvaConf->Width)/2;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::Alter1Switch(TObject *Sender)
{
	try {
		if (Alter1->IsChecked) ostream->write(Num('A'));
		else ostream->write('a');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter2Switch(TObject *Sender)
{
	try {
		if (Alter2->IsChecked) ostream->write(Num('B'));
		else ostream->write('b');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter3Switch(TObject *Sender)
{
	try {
		if (Alter3->IsChecked) ostream->write(Num('C'));
		else ostream->write('c');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter4Switch(TObject *Sender)
{
	try {
		if (Alter4->IsChecked) ostream->write(Num('D'));
		else ostream->write('d');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter5Switch(TObject *Sender)
{
	try {
		if (Alter5->IsChecked) ostream->write(Num('E'));
		else ostream->write('e');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter6Switch(TObject *Sender)
{
	try {
		if (Alter6->IsChecked) ostream->write(Num('F'));
		else ostream->write('f');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter7Switch(TObject *Sender)
{
	try {
		if (Alter7->IsChecked) ostream->write(Num('G'));
		else ostream->write('g');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter8Switch(TObject *Sender)
{
	try {
		if (Alter8->IsChecked) ostream->write(Num('H'));
		else ostream->write('h');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter9Switch(TObject *Sender)
{
	try {
		if (Alter9->IsChecked) ostream->write(Num('I'));
		else ostream->write('i');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter10Switch(TObject *Sender)
{
	try {
		if (Alter10->IsChecked) ostream->write(Num('J'));
		else ostream->write('j');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter11Switch(TObject *Sender)
{
	try {
		if (Alter11->IsChecked) ostream->write(Num('K'));
		else ostream->write('k');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter12Switch(TObject *Sender)
{
	try {
		if (Alter12->IsChecked) ostream->write(Num('L'));
		else ostream->write('l');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter13Switch(TObject *Sender)
{
	try {
		if (Alter13->IsChecked) ostream->write(Num('M'));
		else ostream->write('m');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter14Switch(TObject *Sender)
{
	try {
		if (Alter14->IsChecked) ostream->write(Num('N'));
		else ostream->write('n');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter15Switch(TObject *Sender)
{
	try {
		if (Alter15->IsChecked) ostream->write(Num('O'));
		else ostream->write('o');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter16Switch(TObject *Sender)
{
	try {
		if (Alter16->IsChecked) ostream->write(Num('P'));
		else ostream->write('p');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter17Switch(TObject *Sender)
{
	try {
		if (Alter17->IsChecked) ostream->write(Num('Q'));
		else ostream->write('q');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter18Switch(TObject *Sender)
{
	try {
		if (Alter18->IsChecked) ostream->write(Num('R'));
		else ostream->write('r');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter19Switch(TObject *Sender)
{
	try {
		if (Alter19->IsChecked) ostream->write(Num('S'));
		else ostream->write('s');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter20Switch(TObject *Sender)
{
	try {
		if (Alter20->IsChecked) ostream->write(Num('T'));
		else ostream->write('t');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter21Switch(TObject *Sender)
{
	try {
		if (Alter21->IsChecked) ostream->write(Num('U'));
		else ostream->write('u');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter22Switch(TObject *Sender)
{
	try {
		if (Alter22->IsChecked) ostream->write(Num('V'));
		else ostream->write('v');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter23Switch(TObject *Sender)
{
	try {
		if (Alter23->IsChecked) ostream->write(Num('W'));
		else ostream->write('w');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter24Switch(TObject *Sender)
{
	try {
		if (Alter24->IsChecked) ostream->write(Num('X'));
		else ostream->write('x');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::Alter25Switch(TObject *Sender)
{
	try {
		if (Alter25->IsChecked) ostream->write(Num('Y'));
		else ostream->write('y');
	} catch (...) {
		if (idioma->Lang == "en") Androidapi::Jni::Toast::Toast("You need connect to a device before sending a command.");
		else Androidapi::Jni::Toast::Toast("Voce deve conectar-se a um dispsitivo antes de enviar um comando");
		abasPrinc->ActiveTab = abaDisp;
		RedefInicio();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::FormShow(TObject *Sender)
{

	if (cbMud->IsChecked) MudAb = true;
	else MudAb = false;
	if (cbDes->IsChecked) Desenv = true;
	else Desenv = false;

	prim = true;

	abasPrinc->ActiveTab = abaDisp;

	if (Desenv) {
		Alter1->Enabled = true;
		Alter2->Enabled = true;
		Alter3->Enabled = true;
		Alter4->Enabled = true;
		Alter5->Enabled = true;
		Alter6->Enabled = true;
		Alter7->Enabled = true;
		Alter8->Enabled = true;
		Alter9->Enabled = true;
		Alter10->Enabled = true;
		Alter11->Enabled = true;
		Alter12->Enabled = true;
		Alter13->Enabled = true;
		Alter14->Enabled = true;
		Alter15->Enabled = true;
		Alter16->Enabled = true;
		Alter17->Enabled = true;
		Alter18->Enabled = true;
		Alter19->Enabled = true;
		Alter20->Enabled = true;
		Alter21->Enabled = true;
		Alter22->Enabled = true;
		Alter23->Enabled = true;
		Alter24->Enabled = true;
		Alter25->Enabled = true;

		btLig->Enabled = true;
		btDesl->Enabled = true;

		cmControleManual->Enabled = true;
		cmControleAuto->Enabled = true;
	}

	abasPrinc->TabPosition = TTabPosition::None;

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::FormResize(TObject *Sender)
{
	vsNav->Width = frmPrincipal->Width  - 60;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btNav5Click(TObject *Sender)
{
	vsNav->ShowMaster();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrincipal::vsNavStartShowing(TObject *Sender)
{
	BannerAd1->Visible = false;
	BannerAd2->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::vsNavHidden(TObject *Sender)
{
	if (abasPrinc->ActiveTab == abaControle) {
		if (!SEM_AD) {
			BannerAd1->Visible = true;
			BannerAd2->Visible = true;
		}
	}
	else {
		if (!SEM_AD) {
			BannerAd1->Visible = false;
			BannerAd2->Visible = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::vsNavShown(TObject *Sender)
{
	BannerAd1->Visible = false;
	BannerAd2->Visible = false;
}
//---------------------------------------------------------------------------
