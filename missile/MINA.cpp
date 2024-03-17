//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("minaf1.cpp", Form1);
USERES("mina.res");
USEFORM("minaf2.cpp", Form2);
USEFORM("Manpar3.cpp", par3);
USEFORM("Manpar4.cpp", ff6);
USEFORM("Manpar4_01.cpp", ff6_01);
USEUNIT("Missile.cpp");
USEFILE("Array.h");
USEFILE("Contract.h");
USEFORM("Manpar5.cpp", ff7);
USEFORM("Minaf1_01.cpp", ff1_01);
USEUNIT("TargetOne.cpp");
USEUNIT("space.cpp");
USEUNIT("Control.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->CreateForm(__classid(Tpar3), &par3);
		Application->CreateForm(__classid(Tff6), &ff6);
		Application->CreateForm(__classid(Tff6_01), &ff6_01);
		Application->CreateForm(__classid(Tff7), &ff7);
		Application->CreateForm(__classid(Tff1_01), &ff1_01);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
