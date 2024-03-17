//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "minaf2.h"
#include "Manpar3.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BitBtn1Click(TObject *Sender)
{
fcloseall();
//chdir(pathname);
int Size=45;
bool *blck; blck = new bool [Size];
FILE  **FP;
FP=(FILE**)malloc((Size+1)*sizeof(FILE*));

FP[Size]=fopen("edit.txt","w");
FP[0] =fopen("T.txt","r");
FP[1] =fopen("X.txt","r");
FP[2] =fopen("Y.txt","r");
FP[3] =fopen("Z.txt","r");
FP[4] =fopen("Vx.txt","r");
FP[5] =fopen("Vy.txt","r");
FP[6] =fopen("Vz.txt","r");
FP[7] =fopen("Wx.txt","r");
FP[8] =fopen("Wy.txt","r");
FP[9] =fopen("Wz.txt","r");
FP[10]=fopen("Pitch.txt","r");
FP[11]=fopen("Roll.txt","r");
FP[12]=fopen("Yaw.txt","r");
FP[13]=fopen("Alfa.txt","r");
FP[14]=fopen("Betta.txt","r");
FP[15]=fopen("Fx.txt","r");
FP[16]=fopen("Fy.txt","r");
FP[17]=fopen("Fz.txt","r");
FP[18]=fopen("Mx.txt","r");
FP[19]=fopen("My.txt","r");
FP[20]=fopen("Mz.txt","r");
FP[21]=fopen("TETA.txt","r");
FP[22]=fopen("PSI.txt","r");
FP[23]=fopen("AlfaSpace.txt","r");
FP[24]=fopen("TargetX.txt","r");
FP[25]=fopen("Wz8.txt","r");
FP[26]=fopen("Wx8.txt","r");
FP[27]=fopen("dzetai.txt","r");
FP[28]=fopen("hii.txt","r");
FP[29]=fopen("TargetY.txt","r");
FP[30]=fopen("TargetZ.txt","r");
FP[31]=fopen("Dpitch.txt","r");
FP[32]=fopen("Dyaw.txt","r");
FP[33]=fopen("Droll.txt","r");//*/
FP[34]=fopen("LGPitch.txt","r");//*/
FP[35]=fopen("LSPitch.txt","r");//*/
FP[36]=fopen("LGYaw.txt","r");//*/
FP[37]=fopen("LSYaw.txt","r");//*/
FP[38]=fopen("LRoll.txt","r");//*/
FP[39]=fopen("LSRoll.txt","r");//*/
FP[40]=fopen("AccX.txt","r");//*/
FP[41]=fopen("VFI.txt","r");//*/
FP[42]=fopen("VHI.txt","r");//*/
FP[43]=fopen("UFI.txt","r");//*/
FP[44]=fopen("UHI.txt","r");//*/

blck[0]=true;
blck[1] =X->Checked;
blck[2] =Y->Checked;
blck[3] =Z->Checked;
blck[4] =VelocityX->Checked;
blck[5] =VelocityY->Checked;
blck[6] =VelocityZ->Checked;
blck[7] =Wx->Checked;
blck[8] =Wy->Checked;
blck[9] =Wz->Checked;
blck[10]=Pitch->Checked;
blck[11]=Roll->Checked;
blck[12]=Yaw->Checked;
blck[13]=Alfa->Checked;
blck[14]=Betta->Checked;
blck[15]=Fx->Checked;
blck[16]=Fy->Checked;
blck[17]=Fz->Checked;
blck[18]=Mx->Checked;
blck[19]=My->Checked;
blck[20]=Mz->Checked;
blck[21]=TETA->Checked;
blck[22]=PSI->Checked;
blck[23]=K2tetta->Checked;
blck[24]=TargetX->Checked;
blck[25]=Nx->Checked;
blck[26]=Wxust->Checked;
blck[27]=dzetai->Checked;
blck[28]=hii->Checked;
blck[29]=TargetY->Checked;
blck[30]=TargetZ->Checked;
blck[31]=Dpitch->Checked;
blck[32]=Dyaw->Checked;
blck[33]=Droll->Checked;
blck[34]=Kfi_->Checked;
blck[35]=Kpitch_->Checked;
blck[36]=Khi_->Checked;
blck[37]=Kyaw_->Checked;
blck[38]=Kroll->Checked;
blck[39]=Kroll_->Checked;
blck[40]=N_x->Checked;
blck[41]=VFI->Checked;
blck[42]=VHI->Checked;
blck[43]=UFI->Checked;
blck[44]=UHI->Checked;

AnsiString *VariStr;
VariStr = new AnsiString [Size];

VariStr[0] ="t, c           ";
VariStr[1] ="X, m         ";
VariStr[2] ="Y, m         ";
VariStr[3] ="Z, m         ";
VariStr[4] ="VelocityX, m/c";
VariStr[5] ="VelocityY, m/c";
VariStr[6] ="VelocityZ, m/c";
VariStr[7] ="Wx, rad/c";
VariStr[8] ="Wy, rad/c";
VariStr[9] ="Wz, rad/c";
VariStr[10]="Pitch, deg ";
VariStr[11]="Roll, deg   ";
VariStr[12]="Yaw, deg  ";
VariStr[13]="Alfa, deg   ";
VariStr[14]="Betta, deg ";
VariStr[15]="Fx, N          ";
VariStr[16]="Fy, N        ";
VariStr[17]="Fz, N        ";
VariStr[18]="Mx, N*m     ";
VariStr[19]="My, N*m                   ";
VariStr[20]="Mz, N*m     ";
VariStr[21]="TETA, rad   ";
VariStr[22]="PSI, rad                 ";
VariStr[23]="AlfaSpace, rad";
VariStr[24]="TargetX, m     ";
VariStr[25]="Wzust, rad/c";
VariStr[26]="Wxust, rad/c";
VariStr[27]="Dzetaizm, deg";
VariStr[28]="Hii, deg"     ;
VariStr[29]="TargetY, m       ";
VariStr[30]="TargetZ, m       ";
VariStr[31]="DeltaPitch, deg  ";
VariStr[32]="DeltaYaw, deg  ";
VariStr[33]="DeltaRoll, deg   ";
VariStr[34]="Kfi_, [-]   ";
VariStr[35]="Kpitch_, [-]";
VariStr[36]="Khi_, [-]   ";
VariStr[37]="Kyaw_, [-]  ";
VariStr[38]="Kroll, [-]  ";
VariStr[39]="Kroll_, [-] ";
VariStr[40]="N_x, [m/kv.s]";
VariStr[41]="VisibilityFI, [deg]";
VariStr[42]="VisibilityHI, [deg]";
VariStr[43]="UFI, B    ";
VariStr[44]="UHI, B    ";

char line[256];

for (int k=0; ; k++)
	{
    for (int j=0; j<Size; j++)
    	{
        	if (blck[j]==false) continue;
        	switch(k)
	    	    {
    	    	case 0:
		        	{fprintf(FP[Size],"%s\t",VariStr[j]);break;}
    		    default:
        			{
	        	    if(fgets(line,256,FP[j])==NULL) {k=-10;break;}
    	        	fprintf(FP[Size],"%.3e\t",atof(line));
	        	    }
		        }
        }
        fprintf(FP[Size],"\n");
        if(k<0) break;
    }
    for (int k=0; k<(Size+1); k++) fclose(FP[k]);
 /*********************************************************/
FILE *fp=fopen("file.prn","w");
fprintf(fp,"edit.txt");
fclose(fp);
/********************************************************/
WinExec("editor2.exe",1);
remove("file.prn");

delete [] blck;
delete [] VariStr;
free(*FP);
fcloseall();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CancelClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BitBtn2Click(TObject *Sender)
{
par3->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BitBtn3Click(TObject *Sender)
{
 /*********************************************************/
FILE *fp=fopen("file.prn","w");
fprintf(fp,"Visibility.txt");
fclose(fp);
/********************************************************/
WinExec("editor2.exe",1);
remove("file.prn");

}
//---------------------------------------------------------------------------
void __fastcall TForm2::BitBtn4Click(TObject *Sender)
{
 /*********************************************************/
FILE *fp=fopen("file.prn","w");
fprintf(fp,"fPulse.txt");
fclose(fp);
/********************************************************/
WinExec("editor2.exe",1);
remove("file.prn");


}
//---------------------------------------------------------------------------
