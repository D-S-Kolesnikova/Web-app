//---------------------------------------------------------------------------
#ifndef Manpar4H
#define Manpar4H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>
//---------------------------------------------------------------------------
class Tff6 : public TForm
{
__published:	// IDE-managed Components
	TPaintBox *PaintBox1;
	TMainMenu *MainMenu1;
	TMenuItem *Print1;
	TPrintDialog *PrintDialog1;
	TMenuItem *Size1;
	void __fastcall PaintBox1Paint(TObject *Sender);
	
	
	
	
	void __fastcall Print1Click(TObject *Sender);
	
	
	
	void __fastcall Size1Click(TObject *Sender);
	
	
	
	
	
	
	
	
private:	// User declarations
public:		// User declarations
   	void DoPaint(TCanvas *Canvas);
   	void DoPaintPr(TCanvas *Canvas);
	__fastcall Tff6(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern Tff6 *ff6;
//---------------------------------------------------------------------------
#endif
