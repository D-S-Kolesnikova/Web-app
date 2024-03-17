//---------------------------------------------------------------------------
#ifndef Minaf1_01H
#define Minaf1_01H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class Tff1_01 : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *BitBtn1;
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall Tff1_01(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern Tff1_01 *ff1_01;
//---------------------------------------------------------------------------
#endif
