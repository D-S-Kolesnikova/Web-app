//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <vcl\printers.hpp>
#include <fstream.h>
#include <math.h>
#pragma hdrstop

#include "Manpar4.h"
#include "Manpar4_01.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
extern int XSP,YSP;
Tff6 *ff6;
AnsiString ordinat;
bool flagf6=true;
int poryadok;
AnsiString title6ff;
extern int iii;
//------------------------------------------------------------
//My fuction
//#include <conio.h>

	class pics
		{//major
        protected:
                int Hor;//Общий горизонтальный размер изображения
                int Ver;//Общий вертикальный размер изображения
                int StepPicsX;//Шаг сетки по оси Х
                int ZnakPicsX;//Кол-во знаков у цифровых значений подписи под осью Х
                int StepPicsY;//Шаг сетки по оси У
                int ZnakPicsY;//Кол-во знаков у цифровых значений подписи под осью У
        		double XReal0;//Минимальное значение по оси Х
                double YReal0;//Минимальное значение по оси У
        		double XReal1;//Максимальное значение по оси Х
                double YReal1;//Максимальное значение по оси У
                int XPics0;//Левый отступ перед областью графопостроения
                int YPics0;//Нижний отступ перед областью графопостроения
                int XPicsOtstup;//Правый отступ перед областью графопостроения
                int YPicsOtstup;//Верхний отступ перед областью графопостроения

//Находит максимальный и минимальный элементы массива, заданного в виде столбца
//цифр в файле, определённым указателем char *source
                void FileArrayMinMax(char *source, double Chislo[2])
						{//FileArrayMinMax
						ifstream InFile;
						InFile.open(source);
						char string[60];
						char next;
						//cin.get();

							InFile>>string;
							next=InFile.peek();
							if (next!=EOF) Chislo[0]=Chislo[1]=atof(string); else return;

                        while(1)
						{
						InFile>>string;
					   	next=InFile.peek();
						if (next==EOF) break;
					    if (Chislo[0]>atof(string)) Chislo[0]=atof(string);
					    if (Chislo[1]<atof(string)) Chislo[1]=atof(string);
						}
							    InFile.close();
					    }//FileArrayMinMax
//Находим максимальные элементы в 2-ух файлах-столбцах, 1-ый файл ось Х, 2-ой
//файл ось У, автоопределение интервала для построения графика
                        void PicsAutoInterval (char *source1, char *source2)
                        	{//PicsAutoInterval
							double Chislo[2];
							FileArrayMinMax(source1, Chislo);
							XReal0=Chislo[0]; XReal1=Chislo[1];
							FileArrayMinMax(source2, Chislo);
                            YReal0=Chislo[0]; YReal1=Chislo[1];
                            }//PicsAutoInterval


        public:
pics(
char regim, char *source1, char *source2, int Hor_, int Ver_,
int StepPicsX_=30, int ZnakPicsX_=2, int StepPicsY_=50, int ZnakPicsY_=4,
int XPics0_=50, int YPics0_=50, int XPicsOtstup_=100, int YPicsOtstup_=100,
double XReal0_=-1000.0, double YReal0_=1000.0,	double XReal1_=-1000.0, double YReal1_=1000.0)
                         	{//Constructor
						   Hor=Hor_;
                           Ver=Ver_;
                           StepPicsX=StepPicsX_;
                           ZnakPicsX=ZnakPicsX_;
                           StepPicsY=StepPicsY_;
                           ZnakPicsY=ZnakPicsY_;

          		           XReal0=XReal0_;
                           YReal0=YReal0_;
	        		       XReal1=XReal1_;
	                       YReal1=YReal1_;

                            XPics0=XPics0_;
            			    YPics0=YPics0_;
                			XPicsOtstup=XPicsOtstup_;
			                YPicsOtstup=YPicsOtstup_;

                     //Включается автоопределение интервала графопостроения
                     if (regim=='a')
                     PicsAutoInterval (source1,source2);

                    //Не дает области графопостроения выродиться в точку
                    //или линию
                    if (XReal0==XReal1) {XReal0=0.95*XReal0; XReal1=1.05*XReal1;};
                    if (YReal0==YReal1) {YReal0=0.95*YReal0; YReal1=1.05*YReal1;};

                    if (XReal0==0.0&&XReal1==0.0) {XReal0=-0.05; XReal1=0.05;};
                    if (YReal0==0.0&&YReal1==0.0) {YReal0=-0.05; YReal1=0.05;};

                            }//Constructor

           //Заливка формы
        	void ZalivkaFormi(char r, char g, char b, int Hor, int Ver, TCanvas *Canvas)
            	{//ZalivkaFormi-1
                int i;
                char c;
                char j,k,l;
                	j=k=l=0;
                	if (r=='v') j=1;
                	if (g=='v') k=1;
                	if (b=='v') l=1;
                for (i=0;i<Ver;i++)
					{
					c=255-255.0/Ver*i;
                    if (j==1) r=c;
                    if (k==1) g=c;
                    if (l==1) b=c;
                    Canvas->Brush->Color=TColor(RGB(r,g,b));
					Canvas->FillRect(Rect(0,i,Hor,i+1));
					}
                }//ZalivkaFormi-1
        	void ZalivkaFormi(char r, char g, char b, TCanvas *Canvas)
                {//ZalivkaFormi-2
				Canvas->Brush->Color=TColor(RGB(r,g,b));
                }//ZalivkaFormi-2

           //Построение главных осей
            void MajorOsi(TColor ColorName, const char nmr, TCanvas *Canvas)
            	{//MajorOsi
                Canvas->Pen->Color=ColorName;//cl3DLight
				Canvas->Pen->Width=nmr;
				Canvas->MoveTo(XPics0,YPics0);
				Canvas->LineTo(XPics0,Ver-YPics0);
				Canvas->LineTo(Hor-XPics0,Ver-YPics0);
                }//MajorOsi

           //Построение сетки с подписями числовых значений
            void MajorSetka(TColor ColorNameLine, TColor ColorNameText,
                            const char nmr, TCanvas *Canvas)
            	{//MajorSetka
                int i,j,k,l;
				AnsiString svel0;
				char svel1[256];
            double CenaDeleniyaHorizontal=fabs((XReal0-XReal1)/(Hor-XPics0-XPicsOtstup));
            double CenaDeleniyaVertical  =fabs((YReal0-YReal1)/(Ver-YPics0-YPicsOtstup));

				Canvas->Pen->Color=ColorNameLine;//clNavy
				Canvas->Pen->Width=nmr;

				Canvas->Font->Color=ColorNameText;//cl3DLight
                	for(i=StepPicsY;i<(Ver-YPicsOtstup);i=i+StepPicsY)
					{
					Canvas->MoveTo(XPics0,Ver-YPics0-i);
  					Canvas->LineTo(Hor-XPics0,Ver-YPics0-i);
                	}
 					for(i=0;i<(Ver-YPicsOtstup);i=i+StepPicsY)
		 			{
                        svel0=FloatToStr(i*CenaDeleniyaVertical+YReal0)+'\0';
                		for(l=0;l<256;l++) svel1[l]='\0';
                		for(l=1;(svel0[l]!='\0')&&(l<254);l++)
                        svel1[l-1]=svel0[l];
                		for(l=0;(svel1[l]!='\0')&&(l<255);l++)
				 	    if (svel1[l]=='.') svel1[l+ZnakPicsY]='\0';
                    Canvas->TextOut(10,Ver-YPics0-i,svel1);
					}

					for(i=StepPicsX;i<(Hor-XPicsOtstup);i=i+StepPicsX)
					{
					Canvas->MoveTo(XPics0+i,Ver-YPics0);
					Canvas->LineTo(XPics0+i,YPics0);
                    }

					for(i=0;i<(Hor-XPicsOtstup);i=i+StepPicsX)
					{
                        svel0=FloatToStr(i*CenaDeleniyaHorizontal+XReal0)+'\0';
                		for(l=0;l<256;l++) svel1[l]='\0';
                		for(l=1;(svel0[l]!='\0')&&(l<254);l++)
                        svel1[l-1]=svel0[l];
                		for(l=0;(svel1[l]!='\0')&&(l<255);l++)
					    if (svel1[l]=='.') svel1[l+ZnakPicsX]='\0';
                    Canvas->TextOut(XPics0*0.85+i,Ver-YPics0*0.85,svel1);
                    }
                    }//MajorSetka

           //Построение графика
            void MajorLine(TColor ColorName,
                            const char nmr, char *source1, char *source2, TCanvas *Canvas)
            {//MajorLine
            Canvas->Pen->Color=ColorName;//clOlive
            Canvas->Pen->Width=nmr;

            double CenaDeleniyaHorizontal=(Hor-XPics0-XPicsOtstup)/sqrt((XReal0-XReal1)*(XReal0-XReal1));
            double CenaDeleniyaVertical  =(Ver-YPics0-YPicsOtstup)/sqrt((YReal0-YReal1)*(YReal0-YReal1));
            double x,y;
            ifstream InFile1;
            ifstream InFile2;

            	InFile1.open(source1);
	            InFile2.open(source2);

            char string1[60],string2[60];
            char next1,next2;

                InFile1>>string1;
			   	next1=InFile1.peek();

            	InFile2>>string2;
			   	next2=InFile2.peek();

              x=atof(string1);
              x=XPics0+(sqrt((XReal0-x)*(XReal0-x)))*CenaDeleniyaHorizontal;
              y=atof(string2);
		      y=(Ver-YPics0)-(sqrt((YReal0-y)*(YReal0-y)))*CenaDeleniyaVertical;
              Canvas->MoveTo(x,y);

                while(1)
                	{
					InFile1>>string1;
				   	next1=InFile1.peek();
					if (next1==EOF) break;

					InFile2>>string2;

				   	next2=InFile2.peek();
					if (next2==EOF) break;

              x=atof(string1);
              x=XPics0+(sqrt((XReal0-x)*(XReal0-x)))*CenaDeleniyaHorizontal;
              y=atof(string2);
		      y=(Ver-YPics0)-(sqrt((YReal0-y)*(YReal0-y)))*CenaDeleniyaVertical;



        Canvas->LineTo(x,y);
		}


	    InFile1.close();
    	InFile2.close();

    	}//MajorLine

            double &v0(void) {return XReal0;}
            double &v1(void) {return XReal1;}
            double &s0(void) {return YReal0;}
            double &s1(void) {return YReal1;}

        }//major
        ;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall Tff6::Tff6(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void Tff6::DoPaint(TCanvas *Canvas)
{
char ORDINAT[20];
for (int i=0;i<20;i++) ORDINAT[i]='\0';
for (int i=0;i<20&&ordinat[i+1]!='\0';i++) ORDINAT[i]=ordinat[i+1];

pics gr('a',"T.txt",ORDINAT,ClientWidth,ClientHeight,40,3,30,poryadok);
gr.ZalivkaFormi(255, 255, 255,ClientWidth,ClientHeight,Canvas);
//gr.ZalivkaFormi(0, '0', '0',Canvas);
gr.MajorOsi(clBlack,2,Canvas);
gr.MajorSetka(clBlack,clBlack,1,Canvas);
gr.MajorLine(clBlack,2,"T.txt",ORDINAT,Canvas);

Canvas->TextOut((int)(ClientWidth/32),(int)(ClientHeight/32),title6ff);
Canvas->TextOut((int)(ClientWidth*0.9),(int)(ClientHeight*0.95),"t, c");
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void Tff6::DoPaintPr(TCanvas *Canvas)
{
int xpr=XSP;//4500;
int ypr=YSP;//3000;
char ORDINAT[20];
for (int i=0;i<20;i++) ORDINAT[i]='\0';
for (int i=0;i<20&&ordinat[i+1]!='\0';i++) ORDINAT[i]=ordinat[i+1];


pics gr('a',"T.txt",ORDINAT,xpr,ypr,450,3,300,poryadok,300,50,500,50);
//int XPics0_=1000, int YPics0_=50, int XPicsOtstup_=100, int YPicsOtstup_=1000,
//double XReal0_=-1000.0, double YReal0_=1000.0,	double XReal1_=-1000.0, double YReal1_=1000.0)


gr.ZalivkaFormi(255, 255, 255,xpr,ypr,Canvas);
//gr.ZalivkaFormi(0, '0', '0',Canvas);
gr.MajorOsi(clBlack,2,Canvas);
gr.MajorSetka(clBlack,clBlack,1,Canvas);
gr.MajorLine(clBlack,2,"T.txt",ORDINAT,Canvas);

Canvas->TextOut((int)(xpr/32),(int)(ypr/32),title6ff);
Canvas->TextOut((int)(xpr*0.9),(int)(ypr*0.95),"t, c");
}
//---------------------------------------------------------------------------
void __fastcall Tff6::PaintBox1Paint(TObject *Sender)
{
//if (flagf6==true)
//{
switch(iii)
{
	case 0:
	{ordinat="X.txt"+'\0'; poryadok=1; title6ff="Х, m";break;}
	case 1:
	{ordinat="Y.txt"+'\0'; poryadok=1; title6ff="Y, m";break;}
	case 2:
	{ordinat="Z.txt"+'\0'; poryadok=1; title6ff="Z, m";break;}
	case 3:
	{ordinat="Vx.txt"+'\0'; poryadok=1; title6ff="Vx, m/sec";break;}
	case 4:
	{ordinat="Vy.txt"+'\0'; poryadok=1; title6ff="Vy, m/sec";break;}
	case 5:
	{ordinat="Vz.txt"+'\0'; poryadok=3; title6ff="Vz, m/sec";break;}
	case 6:
	{ordinat="Wx.txt"+'\0'; poryadok=4; title6ff="OmegaX, rad/sec";break;}
	case 7:
	{ordinat="Wy.txt"+'\0'; poryadok=4; title6ff="OmegaY, rad/sec";break;}
	case 8:
	{ordinat="Wz.txt"+'\0'; poryadok=4; title6ff="OmegaZ, rad/sec";break;}
	case 9:
	{ordinat="Pitch.txt"+'\0'; poryadok=4; title6ff="Pitch, deg";break;}
	case 10:
	{ordinat="Roll.txt"+'\0'; poryadok=4; title6ff="Roll, deg";break;}
	case 11:
	{ordinat="Yaw.txt"+'\0'; poryadok=4; title6ff="Yaw, deg";break;}
	case 12:
	{ordinat="Alfa.txt"+'\0'; poryadok=5; title6ff="Alfa, deg";break;}
	case 13:
	{ordinat="Betta.txt"+'\0'; poryadok=5; title6ff="Betta, deg";break;}
	case 14:
	{ordinat="Fx.txt"+'\0'; poryadok=1; title6ff="Fx, N";break;}
	case 15:
	{ordinat="Fy.txt"+'\0'; poryadok=3; title6ff="Fy, N";break;}
	case 16:
	{ordinat="Fz.txt"+'\0'; poryadok=3; title6ff="Fz, N";break;}
	case 17:
	{ordinat="Mx.txt"+'\0'; poryadok=2; title6ff="Mx, [N*m]";break;}
	case 18:
	{ordinat="My.txt"+'\0'; poryadok=2; title6ff="My, [N*m]";break;}
	case 19:
	{ordinat="Mz.txt"+'\0'; poryadok=2; title6ff="Mz, [N*m]";break;}
	case 20:
	{ordinat="TETA.txt"+'\0'; poryadok=2; title6ff="TETA, sec";break;}
	case 21:
	{ordinat="PSI.txt"+'\0'; poryadok=3; title6ff="PSI, secc";break;}
	case 22:
	{ordinat="AlfaSpace.txt"+'\0'; poryadok=5; title6ff="AlfaSpace, deg";break;}
	case 23:
	{ordinat="TargetX.txt"+'\0'; poryadok=1; title6ff="TargetX, m";break;}
	case 24:
	{ordinat="Wz8.txt"+'\0'; poryadok=2; title6ff="Wz уст,  1/с";break;}
	case 25:
	{ordinat="Wx8.txt"+'\0'; poryadok=2; title6ff="Wx уст., 1/с";break;}
	case 26:
	{ordinat="dzetai.txt"+'\0'; poryadok=5; title6ff="dzetai, deg";break;}
	case 27:
	{ordinat="hii.txt"+'\0'; poryadok=5; title6ff="hii, deg";break;}
	case 28:
	{ordinat="TargetY.txt"+'\0'; poryadok=1; title6ff="TargetY, m";break;}
    case 29:
	{ordinat="TargetZ.txt"+'\0'; poryadok=1; title6ff="TargetZ, m";break;}
    case 30:
	{ordinat="Dpitch.txt"+'\0'; poryadok=3; title6ff="DeltaPitch, m";break;}
    case 31:
	{ordinat="Dyaw.txt"+'\0'; poryadok=3; title6ff="DeltaYaw, m";break;}
    case 32:
	{ordinat="Droll.txt"+'\0'; poryadok=3; title6ff="DeltaRoll, m";break;}
    case 33:
	{ordinat="LGPitch.txt"+'\0'; poryadok=3; title6ff="Kfi`, [-]";break;}
    case 34:
	{ordinat="LSPitch.txt"+'\0'; poryadok=3; title6ff="Kpitch`, [-]";break;}
    case 35:
	{ordinat="LGYaw.txt"+'\0'; poryadok=3; title6ff="Khi`, [-]";break;}
    case 36:
	{ordinat="LSYaw.txt"+'\0'; poryadok=3; title6ff="Kyaw`, [-]";break;}
    case 37:
	{ordinat="LRoll.txt"+'\0'; poryadok=3; title6ff="Kroll, [-]";break;}
    case 38:
	{ordinat="LSRoll.txt"+'\0'; poryadok=3; title6ff="Kroll`, m";break;}
    case 39:
	{ordinat="AccX.txt"+'\0'; poryadok=3; title6ff="Nx, m/kv.s";break;}
    case 40:
	{ordinat="VFI.txt"+'\0'; poryadok=3; title6ff="VisibilityFI, deg";break;}
    case 41:
	{ordinat="VHI.txt"+'\0'; poryadok=3; title6ff="VisibilityHI, deg";break;}
    case 42:
	{ordinat="UFI.txt"+'\0'; poryadok=3; title6ff="UFI, B";break;}
    case 43:
	{ordinat="UHI.txt"+'\0'; poryadok=3; title6ff="UHI, B";break;}
    case 44:
	{ordinat="AVFI.txt"+'\0'; poryadok=5; title6ff="AccelerationVisibilityFI, rad/s";break;}
    case 45:
	{ordinat="AVHI.txt"+'\0'; poryadok=5; title6ff="AccelerationVisibilityHI, rad/s";break;}

}
//flagf6=false;}
DoPaint(PaintBox1->Canvas);
//StBar6(title6ff);
}
//---------------------------------------------------------------------------
void __fastcall Tff6::Print1Click(TObject *Sender)
{
	if (PrintDialog1->Execute())
    {

    Printer()->BeginDoc();
    DoPaintPr(Printer()->Canvas);
    Printer()->EndDoc();
    }
}
//---------------------------------------------------------------------------
void __fastcall Tff6::Size1Click(TObject *Sender)
{
ff6_01->ShowModal();
}
//---------------------------------------------------------------------------
