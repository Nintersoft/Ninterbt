//---------------------------------------------------------------------------

#ifndef PrincipalH
#define PrincipalH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ActnList.hpp>
#include <FMX.Gestures.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <System.Actions.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Types.hpp>
#include <FMX.MultiView.hpp>
#include <FMX.Advertising.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Memo.hpp>
//---------------------------------------------------------------------------
class TfrmPrincipal : public TForm
{
__published:	// IDE-managed Components
	TTabControl *abasPrinc;
	TTabItem *abaControle;
	TTabControl *abasSec;
	TTabItem *abaPrinc;
	TToolBar *ToolBar1;
	TLabel *lblTituloAltern;
	TTabItem *abaSec;
	TToolBar *barraTopoInicial;
	TLabel *lblTituloInicial;
	TTabItem *abaConfig;
	TToolBar *barraTopoConfig;
	TLabel *lblTituloConfig;
	TTabItem *abaSobre;
	TToolBar *barraTopoSbr;
	TLabel *lblTituloSbr;
	TTabItem *abaDisp;
	TToolBar *ToolBar5;
	TLabel *lblTituloDisp;
	TMultiView *vsNav;
	TPanel *vsPrincipal;
	TListView *lstDisp;
	TCheckBox *cbEntradaSerial;
	TBannerAd *BannerAd1;
	TBannerAd *BannerAd2;
	TVertScrollBox *cxSobre;
	TVertScrollBox *cxConfig;
	TVertScrollBox *cxAltern;
	TVertScrollBox *cxInicial;
	TTabItem *teste;
	TSpeedButton *btAtualizar;
	TSpeedButton *btNav;
	TLang *idioma;
	TSpeedButton *btNav3;
	TListBox *listaOpcoes;
	TListBoxHeader *listaCabecalho;
	TLabel *lblvsNavTitulo;
	TListBoxItem *btSelecAlter;
	TListBoxItem *btSelecIn;
	TListBoxItem *btSelecDisp;
	TListBoxItem *btSelecConfig;
	TListBoxGroupHeader *lblSelecContr;
	TListBoxGroupHeader *lblSelecConfig;
	TListBoxGroupHeader *lblSelecSobre;
	TListBoxItem *btSelecSobre;
	TSpeedButton *btNav2;
	TSpeedButton *btNav1;
	TLabel *lblSbrApp;
	TLabel *lblSbrVer;
	TLabel *lblSbrAgrd;
	TLabel *lblSbrAppTit;
	TLabel *LblSbrVerV;
	TLabel *lblSbrAgrd1;
	TLabel *lblSbrAgrd2;
	TLabel *lblSbrAgrd3;
	TLabel *lblSbrAgrd4;
	TLabel *lblSbrAgrd5;
	TLabel *lblSbrAgrd6;
	TLabel *lblSbrAgrd7;
	TImage *logoNS;
	TCheckBox *cbDes;
	TLabel *lblConfAba;
	TComboBox *cxAbaSelec;
	TLabel *lblConfLing;
	TRadioButton *beLangPad;
	TSwitch *Alter1;
	TSwitch *Alter2;
	TSwitch *Alter3;
	TSwitch *Alter4;
	TSwitch *Alter5;
	TSwitch *Alter6;
	TSwitch *Alter7;
	TSwitch *Alter8;
	TSwitch *Alter9;
	TSwitch *Alter10;
	TSwitch *Alter11;
	TSwitch *Alter12;
	TSwitch *Alter13;
	TSwitch *Alter14;
	TSwitch *Alter15;
	TSwitch *Alter16;
	TSwitch *Alter17;
	TSwitch *Alter18;
	TSwitch *Alter19;
	TSwitch *Alter20;
	TSwitch *Alter21;
	TSwitch *Alter22;
	TSwitch *Alter23;
	TSwitch *Alter24;
	TSwitch *Alter25;
	TLabel *lblAlternDisp1;
	TLabel *lblAlternDisp2;
	TLabel *lblAlternDisp3;
	TLabel *lblAlternDisp4;
	TLabel *lblAlternDisp5;
	TLabel *lblAlternDisp6;
	TLabel *lblAlternDisp7;
	TCheckBox *cbMud;
	TLabel *lblSbrNintersoft;
	TLabel *lblAlternDisp8;
	TLabel *lblAlternDisp9;
	TLabel *lblAlternDisp10;
	TLabel *lblAlternDisp11;
	TLabel *lblAlternDisp12;
	TLabel *lblAlternDisp13;
	TLabel *lblAlternDisp14;
	TLabel *lblAlternDisp15;
	TLabel *lblAlternDisp16;
	TLabel *lblAlternDisp17;
	TLabel *lblAlternDisp18;
	TLabel *lblAlternDisp19;
	TLabel *lblAlternDisp20;
	TLabel *lblAlternDisp21;
	TLabel *lblAlternDisp22;
	TLabel *lblAlternDisp23;
	TLabel *lblAlternDisp24;
	TLabel *lblAlternDisp25;
	TSpeedButton *btSalvaConf;
	TLabel *lblConfAjdCBMud;
	TLabel *lblConfAjdCBDes;
	TLabel *lblConfAjdCXAS;
	TLabel *lblConfAjdIdi;
	TMemo *mmDados;
	TCheckBox *cmControleAuto;
	TTrackBar *baLuminosidade;
	TTimer *tmSegura;
	TSpeedButton *btLig;
	TSpeedButton *btDesl;
	TLabel *lblPropAppM;
	TCheckBox *cmControleManual;
	TLabel *lblContrLum;
	TLabel *txtAjdContLum;
	TLabel *lblContCirc;
	TLabel *txtAjdContCir;
	TLabel *lblSbrAgrd8;
	TListBoxGroupHeader *lblAjuda;
	TListBoxItem *btAbrDW;
	TListBoxItem *csiCtrl;
	TListBoxItem *csiAltr;
	TListBoxItem *csiConf;
	TTimer *tmAds;
	TSpeedButton *btEscBar;
	TSpeedButton *btNav5;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall abasPrincGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
          bool &Handled);
	void __fastcall btNavClick(TObject *Sender);
	void __fastcall btAtualizarClick(TObject *Sender);
	void __fastcall cbEntradaSerialChange(TObject *Sender);
	void __fastcall btAbrDWClick(TObject *Sender);
	void __fastcall btSalvaConfClick(TObject *Sender);
	void __fastcall cbDesChange(TObject *Sender);
	void __fastcall csiAltrClick(TObject *Sender);
	void __fastcall csiConfClick(TObject *Sender);
	void __fastcall csiCtrlClick(TObject *Sender);
	void __fastcall cbMudChange(TObject *Sender);
	void __fastcall lstDispItemClick(TObject * const Sender, TListViewItem * const AItem);
	void __fastcall BannerAd2DidFail(TObject *Sender, const UnicodeString Error);
	void __fastcall BannerAd1DidFail(TObject *Sender, const UnicodeString Error);
	void __fastcall BannerAd1DidLoad(TObject *Sender);
	void __fastcall BannerAd2DidLoad(TObject *Sender);
	void __fastcall tmAdsTimer(TObject *Sender);
	void __fastcall btDeslClick(TObject *Sender);
	void __fastcall vsNavExit(TObject *Sender);
	void __fastcall btSelecSobreClick(TObject *Sender);
	void __fastcall btSelecDispClick(TObject *Sender);
	void __fastcall btSelecConfigClick(TObject *Sender);
	void __fastcall btSelecInClick(TObject *Sender);
	void __fastcall btSelecAlterClick(TObject *Sender);
	void __fastcall btLigClick(TObject *Sender);
	void __fastcall cmControleAutoChange(TObject *Sender);
	void __fastcall cmControleManualChange(TObject *Sender);
	void __fastcall abasPrincChange(TObject *Sender);
	void __fastcall baLuminosidadeTracking(TObject *Sender);
	void __fastcall tmSeguraTimer(TObject *Sender);
	void __fastcall cxAlternResize(TObject *Sender);
	void __fastcall cxInicialResize(TObject *Sender);
	void __fastcall cxConfigResize(TObject *Sender);
	void __fastcall Alter1Switch(TObject *Sender);
	void __fastcall Alter2Switch(TObject *Sender);
	void __fastcall Alter3Switch(TObject *Sender);
	void __fastcall Alter4Switch(TObject *Sender);
	void __fastcall Alter5Switch(TObject *Sender);
	void __fastcall Alter6Switch(TObject *Sender);
	void __fastcall Alter7Switch(TObject *Sender);
	void __fastcall Alter8Switch(TObject *Sender);
	void __fastcall Alter9Switch(TObject *Sender);
	void __fastcall Alter10Switch(TObject *Sender);
	void __fastcall Alter11Switch(TObject *Sender);
	void __fastcall Alter12Switch(TObject *Sender);
	void __fastcall Alter13Switch(TObject *Sender);
	void __fastcall Alter14Switch(TObject *Sender);
	void __fastcall Alter15Switch(TObject *Sender);
	void __fastcall Alter16Switch(TObject *Sender);
	void __fastcall Alter17Switch(TObject *Sender);
	void __fastcall Alter18Switch(TObject *Sender);
	void __fastcall Alter19Switch(TObject *Sender);
	void __fastcall Alter20Switch(TObject *Sender);
	void __fastcall Alter21Switch(TObject *Sender);
	void __fastcall Alter22Switch(TObject *Sender);
	void __fastcall Alter23Switch(TObject *Sender);
	void __fastcall Alter24Switch(TObject *Sender);
	void __fastcall Alter25Switch(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall btNav5Click(TObject *Sender);
	void __fastcall vsNavStartShowing(TObject *Sender);
	void __fastcall vsNavHidden(TObject *Sender);
	void __fastcall vsNavShown(TObject *Sender);


private:	// User declarations
public:		// User declarations
	_di_JUUID uid;
	__fastcall TfrmPrincipal(TComponent* Owner);
	void adaptar();
	int Num(unsigned char caractere);
	void RedefInicio ();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrincipal *frmPrincipal;
//---------------------------------------------------------------------------
#endif
