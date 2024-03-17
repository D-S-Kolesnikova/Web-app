#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "vfm\aerov.h"
#include "contract.h"


#define pi 3.141593
#define g0 9.80665
#define e 2.718281828459

class missile
{
protected:
	double V;	//0
	double TETA;//1
	double x;	//2
	double y;	//3
	double z;	//4
	int n;
double *el;
double *elh;

	double pr1V;	//0
	double pr1TETA;	//1
	double pr1x;	//2
	double pr1y;	//3
	double pr1z;	//4
double *pr;

	double Dm;	//0
	double S;	//1
	double M0;	//2
	double PSI;	//3

	double a;	//0
	double Max;	//1
	double ro;	//2
	double q;	//3
	double Cx;	//4
	double X;	//5
	double g;	//6
	double G;	//7
	double r;	//8
	double h;	//9
	double t;	//10
	double th;	//11
	double yt;	//12

	//ћассивы с аеродинамическими характеристиками
	double Cxa1[11][6];
	double Cxa2[11][6];
	int SwitchMass;

	FILE *MinaT;
	FILE *MinaX;
	FILE *MinaY;
	FILE *MinaZ;
	FILE *MinaV;
	FILE *MinaTETA;
	FILE *MinaG;
	FILE *MinaSwitchMass;


void WriteElPr(void)
{
	fprintf(MinaT,"%f \n",t);
	fprintf(MinaX,"%f \n",x);
	fprintf(MinaY,"%f \n",y);
	fprintf(MinaZ,"%f \n",z);
	fprintf(MinaV,"%f \n",V);
	fprintf(MinaTETA,"%f \n",TETA*ToDegree);
	fprintf(MinaG,"%f \n",G);

//	getch();
};
void RightPart(void)
{
	ro=exp(-1.8488E-09*y*y-93.138E-06*y+202.55E-03);
	a=sqrt( 39.571E-06*y*y-1.8266*y+109.57E+03);
	q=ro*V*V/2.0;
	Max=V/a;

	switch (SwitchMass)
	{
	case 0:
		Cx=aerovvod(Max,1,Cxa1);break;
	default:
		Cx=aerovvod(Max,1,Cxa2);
	};

	//Cx=0.337*Max+0.157;

	X=Cx*S*q;
	G=M0*g0;
	pr1V=(-X-G*sin(TETA))/M0;
	pr1TETA=(-G*cos(TETA))/(M0*V);
	pr1x=V*cos(TETA)*cos(PSI);
	pr1y=V*sin(TETA);
	pr1z=-V*cos(TETA)*sin(PSI);
	r=sqrt(x*x+y*y+z*z);

	//printf("rpart->x= %f, y= %f, z= %f, n= %d\n",x,y,z,n);
	//getch();
};

void Rks(void)
{
	double ra[5];
	double *rr;
	rr = new double[n];
	int ir,jr;
   ra[0]=ra[1]=ra[4]=h/2.0; 
   ra[2]=ra[3]=h;
   th=t;
	
   for (ir=0;ir<n;ir++) elh[ir]=rr[ir]=el[ir];
   
   for (ir=0;ir<=3;ir++)
	{
	RightPart();
	VectorSetPr(pr);
	th=t+ra[ir];
	 for (jr=0;jr<n;jr++)
	 {
		 elh[jr]=elh[jr]+ra[ir+1]*pr[jr]/3.0;
		 rr[jr]=el[jr]+ra[ir]*pr[jr];
	 }	 
	   VectorGetEl(rr);	   
    }
	delete [] rr;
};

public:
	missile (double M0nu,double Vnu,double TETAnu,double xnu,double ynu,double znu,
		     double Dmnu,double PSInu,double hnu,double tnu,double ytnu)
	{
		M0=M0nu;V=Vnu;TETA=TETAnu;x=xnu;y=ynu;z=znu;Dm=Dmnu;PSI=PSInu;h=hnu;t=tnu;
		yt=ytnu;
		S=pi*Dm*Dm/4; n=5;
		el = new double[n];
		elh= new double[n];
		pr = new double[n];
		MinaT=fopen("T.txt","w");
		MinaX=fopen("X.txt","w");
		MinaY=fopen("Y.txt","w");
		MinaZ=fopen("Z.txt","w");
		MinaV=fopen("V.txt","w");
		MinaTETA=fopen("TETA.txt","w");
		MinaG=fopen("G.txt","w");
		MinaSwitchMass=fopen("MinaSwitchMass.txt","w");

 		aerotablica ( 3 ,Cxa1 );
		aerotablica ( 57,Cxa2 );

		SwitchMass=0;
	};

	~missile()
	{
		delete [] el;
		delete [] elh;
		delete [] pr;
		fclose(MinaT);
		fclose(MinaX);
		fclose(MinaY);
		fclose(MinaZ);
		fclose(MinaV);
		fclose(MinaTETA);
		fclose(MinaG);
		fclose(MinaSwitchMass);
	};

	void VectorSetEl(double *vector)
	{
	vector[0]=V;
	vector[1]=TETA;
	vector[2]=x;
	vector[3]=y;
	vector[4]=z;
	};

	void VectorSetPr(double *vector)
	{
	vector[0]=pr1V;
	vector[1]=pr1TETA;
	vector[2]=pr1x;
	vector[3]=pr1y;
	vector[4]=pr1z;
	};

	void VectorGetEl(double *vector)
	{
	V=vector[0];
	TETA=vector[1];
	x=vector[2];
	y=vector[3];
	z=vector[4];
	};

	void VectorGetPr(double *vector)
	{
	pr1V=vector[0];
	pr1TETA=vector[1];
	pr1x=vector[2];
	pr1y=vector[3];
	pr1z=vector[4];
	};


double Run(double TimeMinMass, double MinMass)
{
	RightPart();
	WriteElPr();
	VectorSetEl(el);

	int i;
	
	double Temph=0.0;
    char   TempPrint=0;

	while(1)
	{

    if((t+h)>TimeMinMass&&Temph==0.0) {Temph=h; h=TimeMinMass-t;};
    if(t<TimeMinMass+0.0001&&t>TimeMinMass-0.0001) {M0=MinMass; h=Temph; SwitchMass=1;}

	Rks();
	VectorGetEl(elh);
	if (TETA<=0.0&&y<(0.001+yt)&&y>=yt){WriteElPr();SwitchMass=0; return th;};
	if (TETA<=0.0&&y<yt){TempPrint=1;h=h/2;continue;};

	t=th;
	for(i=0;i<n;i++) el[i]=elh[i];
	VectorGetEl(el);
	if(t<TimeMinMass+0.0001&&t>TimeMinMass-0.0001)
		fprintf(MinaSwitchMass,"t =%f c\nx= %f m\ny= %f m\nz= %f m\nV= %f m/c\nTETA= %f rad = %f gradusov \nG= %f H\n",
			                    t,       x,       y,       z,       V,         TETA,         RadToDeg(TETA),G);
				
	if (TempPrint==0) WriteElPr();
	};

};

};


inline double dr(double d)
{return d*pi/180;}

inline double rd(double r)
{return r*180/pi;}



