//---------------------------------------------------------------------------
#ifndef Manpar3H
#define Manpar3H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class Tpar3 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label4;
	TRadioButton *X;
	TRadioButton *Y;
	TRadioButton *Z;
	TRadioButton *VelocityX;
	TRadioButton *VelocityY;
	TRadioButton *VelocityZ;
	TRadioButton *Wx;
	TRadioButton *Wy;
	TRadioButton *Wz;
	TRadioButton *Pitch;
	TRadioButton *Roll;
	TRadioButton *Yaw;
	TRadioButton *Alfa;
	TRadioButton *Betta;
	TRadioButton *Fx;
	TRadioButton *Fy;
	TRadioButton *Fz;
	TRadioButton *Mx;
	TRadioButton *My;
	TRadioButton *Mz;
	TRadioButton *TETA;
	TRadioButton *PSI;
	TRadioButton *AlfaSpace;
	TRadioButton *TargetX;
	TRadioButton *OmegaX8;
	TRadioButton *dzetai;
	TRadioButton *hii;
	TRadioButton *TargetY;
	TBitBtn *BitBtn1;
	TBitBtn *Cancel;
	TRadioButton *Nx;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TRadioButton *TargetZ;
	TBitBtn *BitBtn4;
	TBitBtn *BitBtn5;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton3;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TRadioButton *Kfi_;
	TRadioButton *RadioButton5;
	TRadioButton *RadioButton6;
	TRadioButton *RadioButton7;
	TRadioButton *RadioButton8;
	TRadioButton *RadioButton9;
	TRadioButton *RadioButton10;
	TRadioButton *RadioButton4;
	TRadioButton *RadioButton11;
	TRadioButton *RadioButton12;
	TRadioButton *RadioButton13;
	TRadioButton *RadioButton14;
	TRadioButton *RadioButton15;
	void __fastcall XClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall YClick(TObject *Sender);
	void __fastcall ZClick(TObject *Sender);
	void __fastcall VelocityXClick(TObject *Sender);
	void __fastcall VelocityYClick(TObject *Sender);
	void __fastcall VelocityZClick(TObject *Sender);
	void __fastcall WxClick(TObject *Sender);
	void __fastcall WyClick(TObject *Sender);
	void __fastcall WzClick(TObject *Sender);
	void __fastcall PitchClick(TObject *Sender);
	void __fastcall RollClick(TObject *Sender);
	void __fastcall YawClick(TObject *Sender);
	void __fastcall AlfaClick(TObject *Sender);
	void __fastcall BettaClick(TObject *Sender);
	void __fastcall FxClick(TObject *Sender);
	void __fastcall FyClick(TObject *Sender);
	void __fastcall FzClick(TObject *Sender);
	void __fastcall MxClick(TObject *Sender);
	void __fastcall MyClick(TObject *Sender);
	void __fastcall MzClick(TObject *Sender);
	void __fastcall TETAClick(TObject *Sender);
	void __fastcall PSIClick(TObject *Sender);
	void __fastcall AlfaSpaceClick(TObject *Sender);
	void __fastcall TargetXClick(TObject *Sender);
	void __fastcall OmegaX8Click(TObject *Sender);
	void __fastcall dzetaiClick(TObject *Sender);
	void __fastcall hiiClick(TObject *Sender);
	void __fastcall TargetYClick(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall NxClick(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall TargetZClick(TObject *Sender);
	void __fastcall BitBtn4Click(TObject *Sender);
	void __fastcall BitBtn5Click(TObject *Sender);
	void __fastcall RadioButton1Click(TObject *Sender);
	void __fastcall RadioButton2Click(TObject *Sender);
	void __fastcall RadioButton3Click(TObject *Sender);
	void __fastcall Kfi_Click(TObject *Sender);
	void __fastcall RadioButton5Click(TObject *Sender);
	void __fastcall RadioButton6Click(TObject *Sender);
	void __fastcall RadioButton7Click(TObject *Sender);
	void __fastcall RadioButton8Click(TObject *Sender);
	void __fastcall RadioButton9Click(TObject *Sender);
	void __fastcall RadioButton10Click(TObject *Sender);
	void __fastcall RadioButton4Click(TObject *Sender);
	void __fastcall RadioButton11Click(TObject *Sender);
	void __fastcall RadioButton12Click(TObject *Sender);
	void __fastcall RadioButton13Click(TObject *Sender);
	void __fastcall RadioButton14Click(TObject *Sender);
	void __fastcall RadioButton15Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tpar3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern Tpar3 *par3;
//---------------------------------------------------------------------------
#endif
