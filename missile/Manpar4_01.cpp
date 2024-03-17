//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Manpar4_01.h"
#include "Manpar4.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
Tff6_01 *ff6_01;
extern int XSP,YSP;
//---------------------------------------------------------------------------
__fastcall Tff6_01::Tff6_01(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tff6_01::BitBtn1Click(TObject *Sender)
{
XSP=StrToInt(Edit1->Text);
YSP=StrToInt(Edit2->Text);
Close();
}
//---------------------------------------------------------------------------