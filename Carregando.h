//---------------------------------------------------------------------------

#ifndef CarregandoH
#define CarregandoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
//---------------------------------------------------------------------------
class TfrmCarregar : public TForm
{
__published:	// IDE-managed Components
	TImage *imgNbt;
	TLabel *lblCarregando;
	TTimer *tmCarrega;
	TVertScrollBox *Caixa;
	TAniIndicator *indicador;
	void __fastcall tmCarregaTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCarregar(TComponent* Owner);
	String adquireDados(int, String);
	void RearranjoVisual();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCarregar *frmCarregar;
//---------------------------------------------------------------------------
#endif
