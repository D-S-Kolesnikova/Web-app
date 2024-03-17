//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <vcl\printers.hpp>
#include <fstream.h>
#include <math.h>
#pragma hdrstop

int poryadokX;
int poryadokY;

#include "Manpar5.h"
#include "Manpar4_01.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
extern int XSP,YSP;
Tff7 *ff7;
AnsiString ordinat;
bool flagf7=true;
AnsiString title6ff;
extern int ab;
//------------------------------------------------------------
//My fuction
//#include <conio.h>

	class pics2
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
        bool Natura;//Если = true, то по осям Х и У одинаковый масштаб
pics2(
bool Natura_,
char regim, char *source1, char *source2, int Hor_, int Ver_,
int StepPicsX_=30, int ZnakPicsX_=2, int StepPicsY_=50, int ZnakPicsY_=4,
int XPics0_=50, int YPics0_=50, int XPicsOtstup_=100, int YPicsOtstup_=100,
double XReal0_=-1000.0, double YReal0_=1000.0,	double XReal1_=-1000.0, double YReal1_=1000.0)
                         	{//Constructor
                           Natura=Natura_;
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


            ////////Variant 2->
            if(Natura)
            {
            if(CenaDeleniyaHorizontal>CenaDeleniyaVertical)
            	{
	            CenaDeleniyaHorizontal=CenaDeleniyaVertical;
                XPics0=YPics0;
                XPicsOtstup=YPicsOtstup;
				}
            else
            	{
                CenaDeleniyaVertical=CenaDeleniyaHorizontal;
                YPics0=XPics0;
                YPicsOtstup=XPicsOtstup;
                }
            }
            ////////Variant 2<-

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
                        svel0=FloatToStr((i)*CenaDeleniyaHorizontal+XReal0)+'\0';
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

            ////////Variant 2->
            if(Natura)
            {
            if(CenaDeleniyaHorizontal>CenaDeleniyaVertical)
            	{
	            CenaDeleniyaHorizontal=CenaDeleniyaVertical;
                XPics0=YPics0;
                XPicsOtstup=YPicsOtstup;
				}
            else
            	{
                CenaDeleniyaVertical=CenaDeleniyaHorizontal;
                YPics0=XPics0;
                YPicsOtstup=XPicsOtstup;
                }
            }
            ////////Variant 2<-

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
//*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall Tff7::Tff7(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void Tff7::DoPaint(TCanvas *Canvas)
{
char ORDINAT[20];
for (int i=0;i<20;i++) ORDINAT[i]='\0';
for (int i=0;i<20&&ordinat[i+1]!='\0';i++) ORDINAT[i]=ordinat[i+1];

char FAB[10];
for (int fab=0;fab<10;fab++) FAB[fab]='\0';

int CH, CW;
bool natural;

switch (ab)
{
case 0:
	{
    natural=false;
    CH=ClientHeight;
    CW=ClientWidth;
    poryadokX=5;
    FAB[0]='Y';FAB[1]='a';FAB[2]='w';FAB[3]='.';FAB[4]='t';FAB[5]='x';FAB[6]='t';
    }
case 1:
	{
    natural=true;
    CH=CW=ClientHeight;
    poryadokX=5;
	FAB[0]='B';FAB[1]='e';FAB[2]='t';FAB[3]='t';FAB[4]='a';FAB[5]='.';FAB[6]='t';FAB[7]='x';FAB[8]='t';
	break;
	}
case 2:
	{
    natural=false;
    CH=ClientHeight;
    CW=ClientWidth;
    poryadokX=1;
	FAB[0]='X';FAB[1]='.';FAB[2]='t';FAB[3]='x';FAB[4]='t';
	break;
	}
case 3:
	{
    natural=true;
    CH=ClientHeight;
    CW=ClientWidth;
    poryadokX=1;
	FAB[0]='X';FAB[1]='.';FAB[2]='t';FAB[3]='x';FAB[4]='t';
	break;
	}

 }

pics2 gr(natural,'a',FAB,ORDINAT,CW,CH,40,poryadokX,30,poryadokY);

gr.ZalivkaFormi(255, 255, 255,CW,CH,Canvas);
gr.MajorOsi(clBlack,2,Canvas);
gr.MajorSetka(clBlack,clBlack,1,Canvas);
gr.MajorLine(clBlack,2,FAB,ORDINAT,Canvas);

Canvas->TextOut((int)(CW/32),(int)(CH/32),title6ff);
	switch(ab)
    {
        case 0:
        {Canvas->TextOut((int)(CW*0.9),(int)(CH*0.95),"Yaw, deg");break;}
    	case 1:
		{Canvas->TextOut((int)(CW*0.9),(int)(CH*0.95),"Betta, deg");break;}
    	case 2:
        case 3:
		{Canvas->TextOut((int)(CW*0.9),(int)(CH*0.95),"X, m");break;}
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void Tff7::DoPaintPr(TCanvas *Canvas)
{
int CW=XSP;//4500;
int CH=YSP;//3000;
char ORDINAT[20];
for (int i=0;i<20;i++) ORDINAT[i]='\0';
for (int i=0;i<20&&ordinat[i+1]!='\0';i++) ORDINAT[i]=ordinat[i+1];

char FAB[10];
for (int fab=0;fab<10;fab++) FAB[fab]='\0';
bool natural;

switch (ab)
{
case 0:
	{
    natural=false;
    poryadokX=5;
    FAB[0]='Y';FAB[1]='a';FAB[2]='w';FAB[3]='.';FAB[4]='t';FAB[5]='x';FAB[6]='t';
	break;
    }
case 1:
	{
    natural=true;
    CW=CH;
    poryadokX=5;
	FAB[0]='B';FAB[1]='e';FAB[2]='t';FAB[3]='t';FAB[4]='a';FAB[5]='.';FAB[6]='t';FAB[7]='x';FAB[8]='t';
	break;
	}
case 2:
	{
    natural=false;
    CW=CH;
    poryadokX=1;
	FAB[0]='X';FAB[1]='.';FAB[2]='t';FAB[3]='x';FAB[4]='t';
	break;
	}
case 3:
	{
    natural=true;
    CW=CH;
    poryadokX=1;
	FAB[0]='X';FAB[1]='.';FAB[2]='t';FAB[3]='x';FAB[4]='t';
	break;
	}
 }

pics2 gr(natural,'a',FAB,ORDINAT,CW,CH,300,poryadokX,300,poryadokY,300,50,500,50);

gr.ZalivkaFormi(255, 255, 255,CW,CH,Canvas);
gr.MajorOsi(clBlack,2,Canvas);
gr.MajorSetka(clBlack,clBlack,1,Canvas);
gr.MajorLine(clBlack,2,FAB,ORDINAT,Canvas);

Canvas->TextOut((int)(CW/32),(int)(CH/32),title6ff);
	switch(ab)
    {
        case 0:
        {Canvas->TextOut((int)(CW*0.9),(int)(CH*0.95),"Yaw, deg");break;}
    	case 1:
		{Canvas->TextOut((int)(CW*0.9),(int)(CH*0.95),"Betta, deg");break;}
        case 2:
        case 3:
        {Canvas->TextOut((int)(CW*0.9),(int)(CH*0.95),"X, m");break;}
    }
}
//---------------------------------------------------------------------------
void __fastcall Tff7::PaintBox1Paint(TObject *Sender)
{
switch(ab)
{
	case 0:
	{ordinat="Pitch.txt"+'\0'; title6ff="Pitch, deg";poryadokY=2;break;}
	case 1:
	{ordinat="Alfa.txt"+'\0'; title6ff="Alfa, deg";poryadokY=5;break;}
	case 2:
	{ordinat="Z.txt"+'\0'; title6ff="Z, m";poryadokY=2;break;}
	case 3:
	{ordinat="Y.txt"+'\0'; title6ff="Y, m";poryadokY=1;break;}
}
ff7->DoPaint(PaintBox1->Canvas);
}
//---------------------------------------------------------------------------
void __fastcall Tff7::Print1Click(TObject *Sender)
{
	if (PrintDialog1->Execute())
    {

    Printer()->BeginDoc();
    ff7->DoPaintPr(Printer()->Canvas);
    Printer()->EndDoc();
    }
}
//---------------------------------------------------------------------------
void __fastcall Tff7::Size1Click(TObject *Sender)
{
ff6_01->ShowModal();
}
//---------------------------------------------------------------------------
