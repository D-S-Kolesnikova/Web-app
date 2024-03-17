//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "minaf1.h"

#include "minaf2.h"
#include "minaf1_01.h"

#include "Vfm\um016.h"
#include "Noise.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
/*****************************************/
//Paper size for printing
int XSP,YSP;
/*****************************************/
//Переключение аргумента для построения графиков и таблиц результатов с t на Nx
//осуществляется с помощью нижеследующей логической переменной
bool BB10=true;
//Переключение аргумента для построения графиков и таблиц результатов с t на
//углы пеленга
bool BB_FI=true;
bool BB_HI=true;

bool WZFI=true;
bool WZHI=true;

TForm1 *Form1;
char Form1Flag=0;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------;

void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
Form2->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
/*****************************************/
//Paper size for printing
XSP=4500;
YSP=3000;
/*****************************************/
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
    /////
	BitBtn10->Caption="Nx -> Arg\0";
    BB10=true;
	BBFI->Caption="Zfi -> Arg\0";
    BB_FI=true;
	BBHI->Caption="Zhi -> Arg\0";
    BB_HI=true;
    WZFI=true;
	WZfi->Caption="WZfi -> Arg\0";
    WZHI=true;
	WZhi->Caption="WZhi -> Arg\0";    
    remove("t.tmp\0");
    /////

double M0nu,Dmnu,Lnu, Ixnu, Iynu,Iznu,
       LengthOiXnu,LengthOiYnu,LengthOiZnu,
       dzetaiMinnu, dzetaiMaxnu,
       Vnu, TETAnu, PSInu,
	   tetanu, psinu, gammanu, omegaxnu, omegaynu, omegaznu,
	   xnu, ynu, znu, hnu, step_print_maxnu,
	   TimeBeginPrintnu, TimeEndPrintnu, Time0nu,
       Kmvrnu, Kmgnu,
       Quantitynu,
       REnginenu, FiEnginenu,
       PowerEngineXnu, PowerEngineYnu, PowerEngineZnu,
       TawEnginenu, Law_Deg,
       SwitchMassnu, SwitchTimenu, SwitchdTimenu,
       accelerationtnu, velocitytnu, velocityMax_tnu,
       TETAt, PSIt,       RgtXnu, RgtYnu, RgtZnu,
       SpeedNoseXnu, SpeedNoseYnu, SpeedNoseZnu,
       AngelSpeedNoseXnu, AngelSpeedNoseYnu, AngelSpeedNoseZnu,       InewXnu, InewYnu, InewZnu,       INoseXnu, INoseYnu, INoseZnu;       int TawPuskMinusMaxnu, RepeatEnginenu;
//Начальные условия движения мины ->
xnu=StrToFloat(X0->Text);
ynu=StrToFloat(Y0->Text);
znu=StrToFloat(Z0->Text);

tetanu=StrToFloat(Pitch0->Text)/ToDegree;
psinu=StrToFloat(Yaw0  ->Text)/ToDegree;
gammanu=StrToFloat(Roll0 ->Text)/ToDegree;

TETAnu=StrToFloat(TETA0->Text)/ToDegree;
PSInu=StrToFloat(PSI0 ->Text)/ToDegree;

omegaxnu=StrToFloat(Wx0->Text);
omegaynu=StrToFloat(Wy0->Text);
omegaznu=StrToFloat(Wz0->Text);

M0nu=StrToFloat(m0 ->Text);
Ixnu=StrToFloat(Ix0->Text);
Iynu=StrToFloat(Iy0->Text);
Iznu=StrToFloat(Iz0->Text);

Dmnu=StrToFloat(Dm->Text);
Lnu =StrToFloat(L ->Text);
Vnu =StrToFloat(V0->Text);
//Начальные условия движения мины <-

//Коррекция ->

LengthOiXnu=StrToFloat(LengthSCiX->Text);
LengthOiYnu=StrToFloat(LengthSCiY->Text);
LengthOiZnu=StrToFloat(LengthSCiZ->Text);
dzetaiMinnu=StrToFloat(dzetaiMin ->Text)/ToDegree;
dzetaiMaxnu=StrToFloat(dzetaiMax ->Text)/ToDegree;
//Коррекция<-

hnu=StrToFloat(Step0 ->Text);
step_print_maxnu=StrToInt(Print0->Text);
TimeBeginPrintnu=StrToFloat(TimeBegin0->Text);
TimeEndPrintnu=StrToFloat(TimeEnd0  ->Text);
Kmvrnu=StrToFloat(Kmxvr->Text);
Kmgnu= StrToFloat(Kg->Text);
Time0nu= StrToFloat(t0->Text);

//Корректирующие двигатели ->
Quantitynu=StrToFloat(NEngine->Text);
REnginenu =StrToFloat(REngineX->Text);
FiEnginenu=StrToFloat(AngleEngine->Text)/ToDegree;
PowerEngineXnu=StrToFloat(Px->Text);
PowerEngineYnu=StrToFloat(Py->Text);
PowerEngineZnu=StrToFloat(Pz->Text);
TawEnginenu   =StrToFloat(TawEngine->Text);
TawPuskMinusMaxnu=StrToFloat(TawPuskMinusMax->Text);
Law_Deg=StrToFloat(LawDeg->Text)/ToDegree;
RepeatEnginenu=StrToInt(RepeatEngine->Text);
//Корректирующие двигатели <-

//Параметры переключения ->
SwitchMassnu =StrToFloat(mnew->Text);
SwitchTimenu =StrToFloat(tswitch->Text);
SwitchdTimenu=StrToFloat(dtswitch->Text);
//Параметры переключения <-

//Движение Ц ->
accelerationtnu=StrToFloat(aT0->Text);
velocitytnu    =StrToFloat(VT0->Text);
velocityMax_tnu=StrToFloat(VTMAX->Text);
TETAt          =StrToFloat(TETAT0->Text)/ToDegree;PSIt           =StrToFloat(PSIT0->Text)/ToDegree;RgtXnu         =StrToFloat(XT0->Text);
RgtYnu         =StrToFloat(YT0->Text);
RgtZnu         =StrToFloat(ZT0->Text);
//Движение Ц <-

//Импульс от сброса обтекателя ->
SpeedNoseXnu	 =StrToFloat(Vxo->Text);
SpeedNoseYnu	 =StrToFloat(Vyo->Text);
SpeedNoseZnu	 =StrToFloat(Vzo->Text);
AngelSpeedNoseXnu=StrToFloat(wxo->Text);AngelSpeedNoseYnu=StrToFloat(wyo->Text);AngelSpeedNoseZnu=StrToFloat(wzo->Text);InewXnu			 =StrToFloat(Ixnew->Text);InewYnu			 =StrToFloat(Iynew->Text);InewZnu			 =StrToFloat(Iznew->Text);INoseXnu		 =StrToFloat(Ixo->Text);INoseYnu		 =StrToFloat(Iyo->Text);INoseZnu	 	 =StrToFloat(Izo->Text);//Импульс от сброса обтекателя <-



Missile LA(M0nu,Dmnu,Lnu,Ixnu,Iynu,Iznu,
         LengthOiXnu,LengthOiYnu,LengthOiZnu,
         dzetaiMinnu, dzetaiMaxnu,
		 Vnu,TETAnu,PSInu,
		 tetanu,psinu,gammanu,
		 omegaxnu,omegaynu,omegaznu,
		 xnu,ynu,znu,hnu,step_print_maxnu,
		 TimeBeginPrintnu,TimeEndPrintnu,Time0nu,
         Kmvrnu,Kmgnu,
         Quantitynu,
         REnginenu, FiEnginenu,
         PowerEngineXnu, PowerEngineYnu, PowerEngineZnu,
         TawEnginenu,
         TawPuskMinusMaxnu,
         Law_Deg,
         SwitchMassnu, SwitchTimenu, SwitchdTimenu,
         accelerationtnu, velocitytnu, velocityMax_tnu,
         TETAt, PSIt,         RgtXnu,RgtYnu,RgtZnu,
         ControlBox->Checked,
         Pulse->Checked,
         SpeedNoseXnu, SpeedNoseYnu, SpeedNoseZnu,
         AngelSpeedNoseXnu, AngelSpeedNoseYnu, AngelSpeedNoseZnu,         InewXnu, InewYnu, InewZnu,         INoseXnu, INoseYnu, INoseZnu,         VidTrue->Checked,         RepeatEnginenu,         //Система управления, не импульсная коррекция         StrToFloat(KSSPitch  ->Text),         StrToFloat(KsiSSPitch->Text),         StrToFloat(KSSYaw  ->Text),         StrToFloat(KsiSSYaw->Text),         StrToFloat(TSSRoll->Text),         StrToFloat(KsiSSRoll->Text),         StrToFloat(Kpitch->Text),         StrToFloat(Kyaw->Text),         StrToFloat(Kkpitch->Text),         StrToFloat(Kkyaw->Text),         StrToFloat(KvisibilityFI->Text),         StrToFloat(KvisibilityHI->Text),         StrToFloat(PRoll->Text),         StrToFloat(AbsWx->Text),         StrToFloat(KADMx->Text),         NxControl->Checked,         YesVisibilitynu->Checked,         NotAutonu->Checked,         Unullnu->Checked,         //"ослепление" ГСН ЛА	     StrToFloat(RemotenessMaxnu->Text)
         );LA.Pusk();

ff1_01->ShowModal();

}


//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn4Click(TObject *Sender)
{
//Начальные условия движения мины->
X0->Text=FloatToStr(0.0);
Y0->Text=FloatToStr(40000.0);
Z0->Text=FloatToStr(0.0);

Pitch0->Text=FloatToStr(-40.0);
Yaw0  ->Text=FloatToStr(0.0);
Roll0 ->Text=FloatToStr(0.0);

TETA0->Text=FloatToStr(0.0);
PSI0 ->Text=FloatToStr(0.0);

Wx0->Text=FloatToStr(6.0);
Wy0->Text=FloatToStr(0.0);
Wz0->Text=FloatToStr(0.0);

m0 ->Text=FloatToStr(1200.0);
Ix0->Text=FloatToStr(180.0);
Iy0->Text=FloatToStr(700.0);
Iz0->Text=FloatToStr(700.0);

Dm->Text=FloatToStr(1.4);
L ->Text=FloatToStr(3.704);
V0->Text=FloatToStr(4806.0);


//Начальные условия движения мины<-

//Коррекция->
LengthSCiX->Text=FloatToStr(0.05);
LengthSCiY->Text=FloatToStr(0.0);
LengthSCiZ->Text=FloatToStr(0.0);
dzetaiMin ->Text=FloatToStr( 5.0);
dzetaiMax ->Text=FloatToStr(13.0);
//Коррекция<-

Step0 ->Text=FloatToStr(0.0001);
Print0->Text=IntToStr(10);
TimeBegin0->Text=FloatToStr(0.0);
TimeEnd0  ->Text=FloatToStr(-1.0);

//Корректирующие двигатели ->
NEngine->Text    =IntToStr(6);
AngleEngine->Text=FloatToStr(90.0);
REngineX->Text   =FloatToStr(0.0);
Px->Text         =FloatToStr(5000.0);
Py->Text         =FloatToStr(0.0);
Pz->Text         =FloatToStr(0.0);
TawEngine->Text  =FloatToStr(0.04);
//Коррeктирующие двигатели <-

//Параметры переключения ->
Ixnew->Text=FloatToStr(0.0407);
Iynew->Text=FloatToStr(0.5760);
Iznew->Text=FloatToStr(0.5760);
mnew->Text=FloatToStr(19.0);
tswitch->Text=FloatToStr(40.0);
dtswitch->Text=FloatToStr(0.5);
//Параметры переключения <-

//Движение Ц ->
aT0->Text   =FloatToStr(0.02);
VT0->Text   =FloatToStr(0.01);
VTMAX->Text =FloatToStr(0.04);
TETAT0->Text=FloatToStr(0.1);PSIT0->Text =FloatToStr(0.3);
XT0->Text   =FloatToStr(50000.0);
YT0->Text   =FloatToStr(0.0);
ZT0->Text   =FloatToStr(10000.0);
//Движение Ц <-

}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn6Click(TObject *Sender)
{
oM0   ->Text=m0   ->Text;
oV0   ->Text=V0   ->Text;
oTETA0->Text=Pitch0->Text;
oPSI0 ->Text=PSI0 ->Text;
oD    ->Text=Dm   ->Text;
ot0   ->Text=0.0;
oStep ->Text=0.1;
odtc  ->Text=3.5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn5Click(TObject *Sender)
{
	missile la( StrToFloat(oM0->Text),
    			StrToFloat(oV0->Text),
                dr(StrToFloat(oTETA0->Text)),
                StrToFloat(ox->Text),
                StrToFloat(oy->Text),
                StrToFloat(oz->Text),
                StrToFloat(oD->Text),
                dr(StrToFloat(oPSI0->Text)),
                StrToFloat(oStep->Text),
                StrToFloat(ot0->Text),
                StrToFloat(oyt->Text));

    tswitch->Text=FloatToStr(la.Run(9999999.9,9999999.9)-StrToFloat(odtc->Text));
}
//---------------------------------------------------------------------------



void __fastcall TForm1::BitBtn7Click(TObject *Sender)
{
WinExec("ShowM.exe",1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn8Click(TObject *Sender)
{
double PitchN,YawN,RollN,Point_gXN,Point_gYN,Point_gZN,TimeN;
FILE *fd1;
fd1=fopen("f_Temp.txt","r");
char line[256];
int i=0;
while (fgets(line,256,fd1)!=NULL)
    {
		switch(i)
        {
        case 0 : PitchN   =atof(line);break;
        case 1 : YawN     =atof(line);break;
        case 2 : RollN    =atof(line);break;
        case 3 : Point_gXN=atof(line);break;
        case 4 : Point_gYN=atof(line);break;
        case 5 : Point_gZN=atof(line);break;
        default: TimeN    =atof(line);
		}
        ++i;
     }
fclose(fd1);

    Matrix A; A.GetMatrix(PitchN, YawN, RollN);
    Matrix A_=A; A_=~A;
    Vector vg(StrToFloat(Vxo->Text),StrToFloat(Vyo->Text),StrToFloat(Vzo->Text));
	Vector v = A_*vg;
	double Alfa = -atan2(v.Y, v.X), Betta = asin(v.Z/v.GetLength());
    Noise  LA
    			(StrToFloat(m0->Text)-StrToFloat(mnew->Text),
                 StrToFloat(DiametrN->Text),StrToFloat(LengthN->Text),
                 StrToFloat(Ixo->Text),StrToFloat(Iyo->Text),StrToFloat(Izo->Text),
				 v.GetLength(),
	 			 Alfa,Betta,
	  		  	 PitchN,YawN,RollN,
				 StrToFloat(wxo->Text),StrToFloat(wyo->Text),StrToFloat(wzo->Text),
			     Point_gXN,Point_gYN,Point_gZN,
			     StrToFloat(StepN->Text),StrToInt(PrintN->Text),
				 TimeN, StrToFloat(PrintTimeEndN->Text), TimeN,
                 1.0, 1.0);


fd1=fopen("fTemp.txt","w");
fprintf(fd1,"Alfa =%f\n",Alfa *ToDegree);
fprintf(fd1,"Betta=%f\n",Betta*ToDegree);
fclose(fd1);

LA.Pusk();

ff1_01->ShowModal();//*/
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn9Click(TObject *Sender)
{
WinExec("notepad.exe Noise.dt",1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn10Click(TObject *Sender)
{
if (BB10)
	{
	BitBtn10->Caption="t -> Arg\0";
    BB10=false;
    rename("t.txt\0",   "t.tmp\0");
    remove("t.txt\0");
    rename("AccX.txt\0","t.txt\0");
    }
else
	{
	BitBtn10->Caption="Nx -> Arg\0";
    BB10=true;
    rename("t.txt\0","AccX.txt\0");
    rename("t.tmp\0","t.txt\0"   );
    remove("t.tmp\0");
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BBFIClick(TObject *Sender)
{
if (BB_FI)
	{
	BBFI->Caption="t -> Arg\0";
    BB_FI=false;
    rename("t.txt\0",   "t.tmp\0");
    remove("t.txt\0");
    rename("VFI.txt\0","t.txt\0");
    }
else
	{
	BBFI->Caption="Zfi -> Arg\0";
    BB_FI=true;
    rename("t.txt\0","VFI.txt\0");
    rename("t.tmp\0","t.txt\0"   );
    remove("t.tmp\0");
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::BBHIClick(TObject *Sender)
{
if (BB_HI)
	{
	BBHI->Caption="t -> Arg\0";
    BB_HI=false;
    rename("t.txt\0",   "t.tmp\0");
    remove("t.txt\0");
    rename("VHI.txt\0","t.txt\0");
    }
else
	{
	BBHI->Caption="Zhi -> Arg\0";
    BB_HI=true;
    rename("t.txt\0","VHI.txt\0");
    rename("t.tmp\0","t.txt\0"   );
    remove("t.tmp\0");
    }


}
//---------------------------------------------------------------------------
void __fastcall TForm1::UnullnuClick(TObject *Sender)
{
NotAutonu->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NotAutonuClick(TObject *Sender)
{
Unullnu->Checked=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WZfiClick(TObject *Sender)
{
if (WZFI)
	{
	WZfi->Caption="t -> Arg\0";
    WZFI=false;
    rename("t.txt\0",   "t.tmp\0");
    remove("t.txt\0");
    rename("AVFI.txt\0","t.txt\0");
    }
else
	{
	WZfi->Caption="WZfi -> Arg\0";
    WZFI=true;
    rename("t.txt\0","AVFI.txt\0");
    rename("t.tmp\0","t.txt\0"   );
    remove("t.tmp\0");
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WZhiClick(TObject *Sender)
{
if (WZHI)
	{
	WZhi->Caption="t -> Arg\0";
    WZHI=false;
    rename("t.txt\0",   "t.tmp\0");
    remove("t.txt\0");
    rename("AVHI.txt\0","t.txt\0");
    }
else
	{
	WZhi->Caption="WZhi -> Arg\0";
    WZHI=true;
    rename("t.txt\0","AVHI.txt\0");
    rename("t.tmp\0","t.txt\0"   );
    remove("t.tmp\0");
    }
}
//---------------------------------------------------------------------------
