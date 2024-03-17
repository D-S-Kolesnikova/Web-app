//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <dir.h>
#pragma hdrstop

#include "Manpar3.h"
#include "Manpar4.h"
#include "Manpar5.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
Tpar3 *par3;
//---------------------------------------------------------------------------
/////////////
int iii;
int ab;
/////////////
__fastcall Tpar3::Tpar3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::XClick(TObject *Sender)
{
iii=0;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::FormCreate(TObject *Sender)
{
iii=0;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::YClick(TObject *Sender)
{
iii=1;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::ZClick(TObject *Sender)
{
iii=2;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::VelocityXClick(TObject *Sender)
{
iii=3;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::VelocityYClick(TObject *Sender)
{
iii=4;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::VelocityZClick(TObject *Sender)
{
iii=5;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::WxClick(TObject *Sender)
{
iii=6;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::WyClick(TObject *Sender)
{
iii=7;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::WzClick(TObject *Sender)
{
iii=8;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::PitchClick(TObject *Sender)
{
iii=9;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RollClick(TObject *Sender)
{
iii=10;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::YawClick(TObject *Sender)
{
iii=11;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::AlfaClick(TObject *Sender)
{
iii=12;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::BettaClick(TObject *Sender)
{
iii=13;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::FxClick(TObject *Sender)
{
iii=14;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::FyClick(TObject *Sender)
{
iii=15;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::FzClick(TObject *Sender)
{
iii=16;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::MxClick(TObject *Sender)
{
iii=17;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::MyClick(TObject *Sender)
{
iii=18;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::MzClick(TObject *Sender)
{
iii=19;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::TETAClick(TObject *Sender)
{
iii=20;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::PSIClick(TObject *Sender)
{
iii=21;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::AlfaSpaceClick(TObject *Sender)
{
iii=22;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::TargetXClick(TObject *Sender)
{
iii=23;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::NxClick(TObject *Sender)
{
iii=24;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::OmegaX8Click(TObject *Sender)
{
iii=25;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::dzetaiClick(TObject *Sender)
{
iii=26;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::hiiClick(TObject *Sender)
{
iii=27;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::TargetYClick(TObject *Sender)
{
iii=28;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::TargetZClick(TObject *Sender)
{
iii=29;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::BitBtn1Click(TObject *Sender)
{
ff6->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::CancelClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::BitBtn3Click(TObject *Sender)
{
ab=0;
ff7->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::BitBtn2Click(TObject *Sender)
{
ab=1;
ff7->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::BitBtn4Click(TObject *Sender)
{
ab=2;
ff7->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::BitBtn5Click(TObject *Sender)
{
ab=3;
ff7->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton1Click(TObject *Sender)
{
iii=30;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton2Click(TObject *Sender)
{
iii=31;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton3Click(TObject *Sender)
{
iii=32;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::Kfi_Click(TObject *Sender)
{
iii=33;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton5Click(TObject *Sender)
{
iii=34;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton6Click(TObject *Sender)
{
iii=35;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton7Click(TObject *Sender)
{
iii=36;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton8Click(TObject *Sender)
{
iii=37;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton9Click(TObject *Sender)
{
iii=38;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton10Click(TObject *Sender)
{
iii=39;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton4Click(TObject *Sender)
{
iii=40;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton11Click(TObject *Sender)
{
iii=41;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton12Click(TObject *Sender)
{
iii=42;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton13Click(TObject *Sender)
{
iii=43;
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton14Click(TObject *Sender)
{
iii=44;	
}
//---------------------------------------------------------------------------
void __fastcall Tpar3::RadioButton15Click(TObject *Sender)
{
iii=45;	
}
//---------------------------------------------------------------------------
