//---------------------------------------------------------------------------

#include <fmx.h>
#include <FMX.Helpers.Android.hpp>
#include <Androidapi.JNI.Toast.hpp>
#include <System.IOUtils.hpp>
#include <Androidapi.JNI.BluetoothAdapter.hpp>
#include <Androidapi.Helpers.hpp>
#pragma hdrstop

#include "Carregando.h"
#include "Principal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmCarregar *frmCarregar;
//---------------------------------------------------------------------------
	int a;
	_di_JUUID uid;
	String estado, docs;
//---------------------------------------------------------------------------
__fastcall TfrmCarregar::TfrmCarregar(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCarregar::tmCarregaTimer(TObject *Sender)
{
	int i = 0;
	TStringList* lista = new TStringList;

	if (a == 0) {
		//frmPrincipal->BannerAd1->LoadAd();
		//frmPrincipal->BannerAd2->LoadAd();
		a++;
	}
	if (a == 1) {
		docs =	Ioutils::TPath::Combine(Ioutils::TPath::GetHomePath(), L"ninterbt.conf");
		if (TFile::Exists(docs)) {
			frmPrincipal->mmDados->Lines->LoadFromFile(docs);
			if (frmPrincipal->mmDados->Lines->Strings[0] == "NBTS") frmPrincipal->cbMud->IsChecked = true;
			else frmPrincipal->cbMud->IsChecked = false;
			if (frmPrincipal->mmDados->Lines->Strings[1] == "NBTS") frmPrincipal->cbDes->IsChecked = true;
			else frmPrincipal->cbDes->IsChecked = false;
			if (frmPrincipal->mmDados->Lines->Strings[2] == "ALTR") frmPrincipal->csiAltr->IsSelected = true;
			else if (frmPrincipal->mmDados->Lines->Strings[2] == "CONF") frmPrincipal->csiConf->IsSelected = true;
			else  frmPrincipal->csiCtrl->IsSelected = true;
		}
		a++;
	}
	else if (a == 2) {

		estado = checkBluetooth();

		if (Pos("disabled",estado) != 0) {
			if (frmPrincipal->idioma->Lang == "en") Androidapi::Jni::Toast::Toast("Please, turn on the buetooth for using this application");
			else Androidapi::Jni::Toast::Toast("Por favor, ligue o bluetooth para usar esta aplicacao");
			goto fim;
		}

		else {

		uid = TJUUID::JavaClass->fromString(StringToJString("00001101-0000-1000-8000-00805F9B34FB"));
		frmPrincipal->uid = uid;

		lista->Clear();
		lista->AddStrings(getBonded());
		frmPrincipal->lstDisp->Items->Clear();
		frmPrincipal->lstDisp->BeginUpdate();

		for (i = 0; i < lista->Count; i++) {
			frmPrincipal->lstDisp->Items->Add();
			frmPrincipal->lstDisp->Items->Item[i]->Text = adquireDados(2, lista->Strings[i]);
			frmPrincipal->lstDisp->Items->Item[i]->Detail = adquireDados(1, lista->Strings[i]);
		}

		frmPrincipal->lstDisp->EndUpdate();

		}

		fim:
		a++;

	}
	else if (a == 3) {
		if (frmPrincipal->cbDes->IsChecked) {

			frmPrincipal->btLig->Enabled = true;
			frmPrincipal->btDesl->Enabled = true;

			frmPrincipal->cmControleManual->Enabled = true;
			frmPrincipal->Alter1->Enabled = true;
			frmPrincipal->Alter2->Enabled = true;
			frmPrincipal->Alter3->Enabled = true;
			frmPrincipal->Alter4->Enabled = true;
			frmPrincipal->Alter5->Enabled = true;
			frmPrincipal->Alter6->Enabled = true;
			frmPrincipal->Alter7->Enabled = true;
			frmPrincipal->Alter8->Enabled = true;
			frmPrincipal->Alter9->Enabled = true;
			frmPrincipal->Alter10->Enabled = true;
			frmPrincipal->Alter11->Enabled = true;
			frmPrincipal->Alter12->Enabled = true;
			frmPrincipal->Alter13->Enabled = true;
			frmPrincipal->Alter14->Enabled = true;
			frmPrincipal->Alter15->Enabled = true;
			frmPrincipal->Alter16->Enabled = true;
			frmPrincipal->Alter17->Enabled = true;
			frmPrincipal->Alter18->Enabled = true;
			frmPrincipal->Alter19->Enabled = true;
			frmPrincipal->Alter20->Enabled = true;
			frmPrincipal->Alter21->Enabled = true;
			frmPrincipal->Alter22->Enabled = true;
			frmPrincipal->Alter23->Enabled = true;
			frmPrincipal->Alter24->Enabled = true;
			frmPrincipal->Alter25->Enabled = true;
		}

		a++;
	}
	else if (a > 3) {
		frmPrincipal->Show();
		frmCarregar->Hide();
		a = 0;
		tmCarrega->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCarregar::FormShow(TObject *Sender)
{
	RearranjoVisual();
	tmCarrega->Enabled = true;
	a = 0;
}
//---------------------------------------------------------------------------
String TfrmCarregar::adquireDados (int esc, String linha){

	String res = "";
	bool comeco = true;

	if (esc == 1) {
		for (int i = 0; i < linha.Length(); i++) {
			if (comeco) {
				if (linha.c_str()[i] == '=') {
					comeco = false;
				}
			}
			else{
				res = res + linha.c_str()[i];
			}
		}
	}
	else {
		for (int i = 0; i < linha.Length(); i++) {
			if (linha.c_str()[i] != '=') {
				res = res + linha.c_str()[i];
			}
			else{
				break;
			}
		}
	}

	return res;

}
//---------------------------------------------------------------------------
void __fastcall TfrmCarregar::FormKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift)
{
	if (Key == vkHardwareBack) {
		Application->Terminate();
	}
}
//---------------------------------------------------------------------------
void TfrmCarregar::RearranjoVisual(){
	if (Caixa->Height > 310) {
		imgNbt->Position->X = (Caixa->Width - imgNbt->Width)/2;
		imgNbt->Position->Y = (Caixa->Height)/2 - 35 - imgNbt->Height;
		indicador->Position->X = (Caixa->Width - indicador->Width)/2;
		indicador->Position->Y = (Caixa->Height - indicador->Height)/2;
		lblCarregando->Position->X = (Caixa->Width - lblCarregando->Width)/2;
		lblCarregando->Position->Y = (Caixa->Height + indicador->Height)/2 + 5;
	}
	else if (Caixa->Height <= 310 && Caixa->Width >= 350){
		imgNbt->Position->Y = (Caixa->Height - imgNbt->Height)/2;
		imgNbt->Position->X = (Caixa->Width - 10)/2  - imgNbt->Width;
		lblCarregando->Position->Y = Caixa->Height/2 + lblCarregando->Height + 5;
		lblCarregando->Position->X = Caixa->Width/2 + 5;
		indicador->Position->Y = Caixa->Height/2 - indicador->Height - 5;
		indicador->Position->X = lblCarregando->Position->X + lblCarregando->Width/2 - indicador->Width/2;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCarregar::FormResize(TObject *Sender)
{
	RearranjoVisual();
}
//---------------------------------------------------------------------------

