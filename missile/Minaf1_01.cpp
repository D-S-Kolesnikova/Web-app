//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Minaf1_01.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
Tff1_01 *ff1_01;
//---------------------------------------------------------------------------
__fastcall Tff1_01::Tff1_01(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tff1_01::BitBtn1Click(TObject *Sender)
{
Close();	
}
//---------------------------------------------------------------------------