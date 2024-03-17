//---------------------------------------------------------------------------
#ifndef minaf2H
#define minaf2H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label4;
	TBitBtn *BitBtn1;
	TBitBtn *Cancel;
	TCheckBox *X;
	TCheckBox *Y;
	TCheckBox *Z;
	TCheckBox *VelocityX;
	TCheckBox *VelocityY;
	TCheckBox *VelocityZ;
	TCheckBox *Wx;
	TCheckBox *Wy;
	TCheckBox *Wz;
	TCheckBox *Pitch;
	TCheckBox *Roll;
	TCheckBox *Yaw;
	TCheckBox *Alfa;
	TCheckBox *Betta;
	TCheckBox *Fx;
	TCheckBox *Fy;
	TCheckBox *Fz;
	TCheckBox *Mx;
	TCheckBox *My;
	TCheckBox *Mz;
	TCheckBox *TETA;
	TCheckBox *PSI;
	TCheckBox *K2tetta;
	TCheckBox *TargetX;
	TCheckBox *Nx;
	TCheckBox *Wxust;
	TCheckBox *dzetai;
	TCheckBox *hii;
	TCheckBox *TargetY;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TCheckBox *TargetZ;
	TBitBtn *BitBtn4;
	TCheckBox *Dpitch;
	TCheckBox *Dyaw;
	TCheckBox *Droll;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TCheckBox *Kfi_;
	TCheckBox *Kpitch_;
	TCheckBox *Khi_;
	TCheckBox *Kyaw_;
	TCheckBox *Kroll;
	TCheckBox *Kroll_;
	TCheckBox *N_x;
	TCheckBox *VFI;
	TCheckBox *VHI;
	TCheckBox *UFI;
	TCheckBox *UHI;
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall BitBtn3Click(TObject *Sender);
	void __fastcall BitBtn4Click(TObject *Sender);
	
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
