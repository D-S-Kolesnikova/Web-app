// File Noise.h
class Noise: public Object
{
 public:
 Noise
(double ,double ,double ,
 double ,double ,double ,
 double ,
 double ,double ,
 double ,double ,double ,
 double ,double ,double ,
 double ,double ,double ,
 double ,int ,
 double ,double ,double ,
 double , double );

	   ~Noise();

	void NextStep();

    Vector GetXYZ(double t_)
    {
    Vector t(t_,0,0);
    return t;
    }

	void Pusk(void)
	{
    	RightPart();

		while(Life)
        	{
            if (Time==TimeBeginPrint) OutputFile();
	        NextStep();
            }
	}

	unsigned char GetType() {return Type_Missile;}

 protected:


    /**/     Vector TempPower;
    /**/     FILE *TempPowerX;
    /**/     FILE *TempPowerY;
    /**/     FILE *TempPowerZ;

	double SpeedSound(double);
	double DensityAir(double);
	double Cx(double, double);
	double Cy(double, double);
	double Cz(double, double);
	double Mx_wx(double, double);
	double Mz_wz(double, double);
	double Mz_alfa(double, double);
	double My_wy(double, double);
	double My_betta(double, double);
	double Mxvr(double, double);
    double Sqr(double sqr) {return sqr*sqr;}

    double Kmvr;
    double Kmg;

	double aCx[11][6];
	double aCya[11][6];
	double amza[11][6];
	double amz_wz_[11][6];
	double amxvr[11][6];
	double amx_wx_[11][6];


	void Rks4(void);
	void RightPart(void);
	void ConditionTermination();
	void SetAngle(double, double, double, double);
	void OutputFile();
	void PrintInFile();

	int    Size;
	double Step;
	double TimeBegin;
	double TimeStep;
	double *elh;
	double *el;
	double *Left;

	double Mass;
	double Ix;
	double Iy;
	double Iz;
	double SquareMiddle;
	double DiametrMiddle;
	double Length;

	double omegaXdm;
    double omegaZdm;

	double Pitch;
	double Yaw;
	double Roll;
	double Alfa;
	double Betta;
	double TETA;
	double PSI;

double Cx_     ;
double Cy_     ;
double Mx_wx_  ;
double Mz_wz_  ;
double Mz_alfa_;
double Mxvr_   ;

	Vector F;
	Vector M;


	FILE *OutT;
	FILE *OutVx;
	FILE *OutVy;
	FILE *OutVz;
	FILE *OutX;
	FILE *OutY;
	FILE *OutZ;

	FILE *OutWx;
	FILE *OutWy;
	FILE *OutWz;
	FILE *OutPitch;
	FILE *OutYaw;
	FILE *OutRoll;

	FILE *OutAlfa;
	FILE *OutBetta;

	FILE *OutFx;
	FILE *OutFy;
	FILE *OutFz;

	FILE *OutMx;
	FILE *OutMy;
	FILE *OutMz;

	FILE *OutTETA;
	FILE *OutPSI;

	FILE *OutAlfaSpace;
	FILE *OutWx8;
    FILE *OutWz8;


	double TimeBeginPrint;
	double TimeEndPrint;
	int    NumTimePrint;
	int    NumPrint;

 //Аппроксимация сеточных функций
//m - ось абцис (х)
//а - ось ординат (у)

double chislo(char *fname,int i,int k)
{
FILE *fd1;
char line[256];
int nline=0,j;
char *ch;
double chislo_d;
if ((fd1=fopen(fname,"r"))==NULL)
		{
		perror(fname);
		return 0.00005;
		}
while (fgets(line,256,fd1)!=NULL)
		{
		nline++;
		if (nline==i) break;
		}
			if (line[k-1]==' ' || line[k-1]=='*' || line[k-1]=='=')
			for (;line[k]==' ' || line[k]=='*'   || line[k]=='=';k++);

			for (j=0;line[k]!=' ';k++)
			{
			if(line[k]=='*')break;
			j++;
			}
				ch=(char*)malloc(j*sizeof(char));
				for (nline=0,k=k-j;nline<j;nline++)
				{
				ch[nline]=line[k];
				k++;
				}
fclose(fd1);
chislo_d=atof(ch);
free(ch);
return chislo_d;
}
//Линейная интерполяция по двум точкам
double alur(double x1, double y1, double x2, double y2, double x)
{
double b,k;
//////////////////////
if(x2==x1) x2=x1+0.0001;
/////////////////////
b=(y2-y1)/(x2-x1);
k=(y1*x2-y2*x1)/(x2-x1);

return b*x+k;
}
//Считывание из файла стандартного аэродинамического массива
void aerotablica (int begin_number, double sda[11][6])
{
int i,j,k;
for(j=0;j<6;j++)
{
/////////////////////////////
	k=1;
/////////////////////////////
for(i=0;i<11;i++)
{
sda[i][j]=chislo("akfm.dt",begin_number+j,k);
k=k+9;
}
}
}


//Функция сеточной интерпoляции
double aerovvod (double m, double a, double sda[11][6])
{
int i,j;
double c1,c2,c3,c4;
double rez_m, rez_a;
for(i=2;i<11;i++)
if(m<=sda[i][0]) break;

/*Выключаем блок линейного прогноза и заменяем на блок который при выходе за за-
данный диапазон Маха или Альфы, считаеи их равными последниму из заданных
if(m<sda[1][0])  i=2;
if(m>=sda[10][0])i=10;
*/
if(m<sda[1][0])  {i=2; m=sda[1][0]; }
if(m>=sda[10][0]){i=10;m=sda[10][0];}

//printf ("\ni=%d\n",i);


for(j=2;j<6;j++)
if(a<=sda[0][j]) break;
//аналогично с предыдущим
if(a<sda[0][1]) {j=2;a=sda[0][1];}
if(a>=sda[0][5]){j=5;a=sda[0][5];}

//printf ("\nj=%d\n",j);


c1		=alur(sda[i-1][0],sda[i-1][j-1],sda[i][0],sda[i][j-1],m);
c2		=alur(sda[i-1][0],sda[i-1][j]  ,sda[i][0],sda[i][j]  ,m);


c3		=alur(sda[0][j-1],sda[i-1][j-1],sda[0][j],sda[i-1][j],a);
c4		=alur(sda[0][j-1],sda[i][j-1]  ,sda[0][j],sda[i][j]  ,a);

rez_a	=alur(sda[0][j-1],c1		   ,sda[0][j],c2         ,a);

return rez_a;

}

};


/////////////////////////////////////////////////////////

Noise::Noise (double M0nu,double Dmnu,double Lnu,
				  double Ixnu,double Iynu,double Iznu,
				  double Vnu,
	 			  double TETAnu,double PSInu,
				  double tetanu,double psinu,double gammanu,
				  double omegaxnu,double omegaynu,double omegaznu,
			      double xnu,double ynu,double znu,
			      double hnu,int step_print_maxnu,
				  double TimeBeginPrintnu, double TimeEndPrintnu, double Time0nu,
                  double Kmvrnu, double Kmgnu):Object()
	{

	Size = 13;
	el    = new double [Size];
	elh   = new double [Size];
	Left  = new double [Size];

FILE *fd1;
fd1=fopen("Noise.dt","r");
char line[256];
int i=0;
while (fgets(line,256,fd1)!=NULL)
    {
		switch(i)
        {
        case 0 : Cx_     =atof(line);break;
        case 1 : Cy_     =atof(line);break;
        case 2 : Mx_wx_  =atof(line);break;
        case 3 : Mz_wz_  =atof(line);break;
        case 4 : Mz_alfa_=atof(line);break;
        case 5 : Mxvr_   =atof(line);break;
		}
        ++i;
     }
fclose(fd1);


		Mass=M0nu;			  Alfa=TETAnu;  Point_gX=xnu;
		DiametrMiddle=Dmnu;   Betta=PSInu;  Point_gY=ynu;
		Length=Lnu;						    Point_gZ=znu;

		Ix=Ixnu;              Pitch =tetanu;
		Iy=Iynu;              Yaw   =psinu;
		Iz=Iznu;              Roll  =gammanu;
		                      omegaX=omegaxnu;
   		                      omegaY=omegaynu;
   		                      omegaZ=omegaznu;

		Step=hnu;
		NumPrint=step_print_maxnu;
		NumTimePrint = -1;

		TimeBeginPrint=TimeBeginPrintnu;
		TimeEndPrint  =TimeEndPrintnu;
		if (TimeEndPrint<0.0) TimeEndPrint=24.0*60.0*60.0;

		Kmvr=Kmvrnu; Kmg=Kmgnu;

		SquareMiddle=Pi*DiametrMiddle*DiametrMiddle/4;

		Matrix A; A.GetMatrix(Pitch, Yaw, Roll);

		Vector Speed_s;

		Speed_s.X=Vnu*cos(Betta)*cos(Alfa);
		Speed_s.Y=-Speed_s.X*tan(Alfa);
		Speed_s.Z=Vnu*sin(Betta);

		Vector Speed_g=A*Speed_s;
		Speed_gX=Speed_g.X;
		Speed_gY=Speed_g.Y;
		Speed_gZ=Speed_g.Z;

///
    Life = true;
	Target = NULL;

	ro_rg  = cos(Yaw/2)*cos(Pitch/2)*cos(Roll/2) -
						   sin(Yaw/2)*sin(Pitch/2)*sin(Roll/2);
	lamda_rg = sin(Yaw/2)*sin(Pitch/2)*cos(Roll/2) +
						   cos(Yaw/2)*cos(Pitch/2)*sin(Roll/2);
	mu_rg = sin(Yaw/2)*cos(Pitch/2)*cos(Roll/2) +
						   cos(Yaw/2)*sin(Pitch/2)*sin(Roll/2);
	nu_rg = cos(Yaw/2)*sin(Pitch/2)*cos(Roll/2) -
						   sin(Yaw/2)*cos(Pitch/2)*sin(Roll/2);

    //Процедура нормализации ->
    //принципиально не нужна, т.к. переменные уже нормализованные
    //приводится для порядка на всякий случай
	double rg=sqrt(ro_rg*ro_rg+lamda_rg*lamda_rg+mu_rg*mu_rg+nu_rg*nu_rg);
    ro_rg=ro_rg/rg;
    lamda_rg=lamda_rg/rg;
    mu_rg=mu_rg/rg;
    nu_rg=nu_rg/rg;
    //Процедура нормализации <-

	for(int i = 0; i < Size; i++)
	elh[i] = el[i];

   	//Block printing
	Time = TimeBegin = Time0nu;
    TimeStep = 0.0;

	OutT         =fopen("T.txt","w");
	OutVx        =fopen("Vx.txt","w");
	OutVy        =fopen("Vy.txt", "w");
	OutVz        =fopen("Vz.txt", "w");
	OutX         =fopen("X.txt", "w");
	OutY         =fopen("Y.txt", "w");
	OutZ         =fopen("Z.txt", "w");
	OutWx        =fopen("Wx.txt", "w");
	OutWy        =fopen("Wy.txt", "w");
	OutWz        =fopen("Wz.txt", "w");
	OutPitch     =fopen("Pitch.txt", "w");
	OutYaw       =fopen("Yaw.txt", "w");
	OutRoll      =fopen("Roll.txt", "w");
	OutAlfa      =fopen("Alfa.txt", "w");
	OutBetta     =fopen("Betta.txt", "w");
	OutFx        =fopen("Fx.txt", "w");
	OutFy        =fopen("Fy.txt", "w");
	OutFz        =fopen("Fz.txt", "w");
	OutMx        =fopen("Mx.txt", "w");
	OutMy        =fopen("My.txt", "w");
	OutMz        =fopen("Mz.txt", "w");
	OutTETA      =fopen("TETA.txt", "w");
	OutPSI       =fopen("PSI.txt", "w");
	OutAlfaSpace =fopen("AlfaSpace.txt", "w");
	OutWx8       =fopen("Wx8.txt", "w");
	OutWz8       =fopen("Wz8.txt", "w");

    TempPowerX   =fopen("TPX.txt", "w");
	TempPowerY   =fopen("TPY.txt", "w");
	TempPowerZ   =fopen("TPZ.txt", "w");

};
//
Noise::~Noise()
{
	delete [] el;
	delete [] elh;
	delete [] Left;

	fclose(OutT);
	fclose(OutVx); 		 fclose(OutVy); 	fclose(OutVz);
	fclose(OutX); 		 fclose(OutY); 		fclose(OutZ);
	fclose(OutWx); 		 fclose(OutWy); 	fclose(OutWz);
	fclose(OutPitch);    fclose(OutYaw); 	fclose(OutRoll);
	fclose(OutAlfa);	 fclose(OutBetta);	
	fclose(OutFx);		 fclose(OutFy);		fclose(OutFz);
	fclose(OutMx);		 fclose(OutMy);		fclose(OutMz);
	fclose(OutTETA);	 fclose(OutPSI);
    fclose(OutAlfaSpace);fclose(OutWx8);	fclose(OutWz8);

  	fclose(TempPowerX);	 fclose(TempPowerY);fclose(TempPowerZ);
};
//

void Noise::SetAngle(double r, double l, double m, double n)
{

    if (fabs(2*r*n + 2*l*m)>1.0) {Life=false;return;}
    Pitch = asin (2*r*n + 2*l*m);
	Roll  = atan2(2*r*l - 2*n*m, r*r + m*m - n*n - l*l);
	Yaw   = atan2(2*r*m - 2*l*n, r*r + l*l - m*m - n*n);
};
//

void Noise::RightPart()
{
	SetAngle(ro_rg, lamda_rg, mu_rg, nu_rg);

	Vector vg(Speed_gX, Speed_gY, Speed_gZ);
	double velocity =  vg.GetLength(),
		   q        =  DensityAir(Point_gY)*velocity*velocity/2,
		   mahh     =  velocity/SpeedSound(Point_gY);

	Matrix A_;//Матрица перехода от норм. земн. с.к. к связанной
    A_.GetMatrix(ro_rg, lamda_rg, mu_rg, nu_rg);

   	Matrix A= A_;//Матрица перехода от связанной с.к. к норм. земн.
           A=~A;
	Vector v = A_*vg;
	Alfa = -atan2(v.Y, v.X); Betta = atan2(v.Z,sqrt(Sqr(v.X)+Sqr(v.Y)));

	double AlfaSpace=sqrt(Sqr(Alfa)+Sqr(Betta));


		   F.X  = -Cx(mahh,AlfaSpace)   *q*SquareMiddle;
		   F.Y  =  Cy(mahh,Alfa)*Alfa   *q*SquareMiddle;
		   F.Z  =  Cz(mahh,Betta)*Betta *q*SquareMiddle;

//	Matrix C;
//	C.GetMatrix(Alfa,Betta,0.0);
//	F=C*F;

		   M.X = (Mx_wx(mahh,AlfaSpace)*omegaX*DiametrMiddle/velocity
           			+Kmvr*Mxvr(mahh,AlfaSpace))*q*SquareMiddle*DiametrMiddle;

		   M.Y = (My_wy(mahh,Betta)*omegaY*DiametrMiddle/velocity + My_betta(mahh,Betta)*Betta
		         )*q*SquareMiddle*Length;

		   M.Z = (Mz_wz(mahh,Alfa)*omegaZ*DiametrMiddle/velocity + Mz_alfa(mahh,Alfa)*Alfa
		         )*q*SquareMiddle*Length;


omegaXdm = velocity*Mxvr(mahh,AlfaSpace)/(Mx_wx(mahh,AlfaSpace)*DiametrMiddle);
//omegaZdm = sqrt(-Mz_alfa(mahh,Alfa)*q*SquareMiddle*Length/Iz);


	Vector fg;
    Vector Gg(0.0,-Kmg*Mass*9.81,0.0);
	fg = A*F+Gg;
    TempPower=fg;

	TETA=atan2( Speed_gY,sqrt(Sqr(Speed_gX)+Sqr(Speed_gZ)));
	PSI =atan2(-Speed_gZ,Speed_gX);


	pr1Speed_gX  = fg.X/Mass;
	pr1Speed_gY  = fg.Y/Mass;
	pr1Speed_gZ  = fg.Z/Mass;
	pr1Point_gX  = Speed_gX;
	pr1Point_gY  = Speed_gY;
	pr1Point_gZ  = Speed_gZ;
	pr1omegaX    = M.X/Ix - (Iz - Iy)*omegaY*omegaZ/Ix;
	pr1omegaY    = M.Y/Iy - (Ix - Iz)*omegaX*omegaZ/Iy;
	pr1omegaZ    = M.Z/Iz - (Iy - Ix)*omegaX*omegaY/Iz;
	pr1ro_rg     =-( omegaX*lamda_rg + omegaY*mu_rg + omegaZ*nu_rg)/2;
	pr1lamda_rg  = ( omegaX*ro_rg  - omegaY*nu_rg + omegaZ*mu_rg)/2;
	pr1mu_rg     = ( omegaX*nu_rg + omegaY*ro_rg  - omegaZ*lamda_rg)/2;
	pr1nu_rg     = (-omegaX*mu_rg + omegaY*lamda_rg + omegaZ*ro_rg )/2;
};

void Noise::Rks4()
{
	double a[5];
	double *elTemp;
	elTemp   = new double [Size];

	a[0] = a[1] = a[4] = Step/2; a[2] = a[3] = Step;
	TimeStep=Time;
	for(int i = 0; i < Size; i++)
    elTemp[i] = elh[i] = el[i];
	for(int i = 0; i < 4; i++)
	   {
	    RightPart();
	    TimeStep = Time + a[i];
	    for(int j = 0; j < Size; j++)
	       {
	        elh[j] += a[i+1]*Left[j]/3;
	        el[j]  += a[i]*Left[j];
 	       }
		 }
	for(int i = 0; i < Size; i++)
    el[i] = elTemp[i];
	delete [] elTemp;

	double rg =sqrt(el[9] *el[9] +el[10] *el[10] +el[11] *el[11] +el[12] *el[12] );
	double rgh=sqrt(elh[9]*elh[9]+elh[10]*elh[10]+elh[11]*elh[11]+elh[12]*elh[12]);
    for(int j=9;j< Size; j++)
    {
    el[j] =el[j] /rg;
    elh[j]=elh[j]/rgh;
    }


};

void Noise::ConditionTermination()
{

	if (TETA<=0.0&&fabs(elh[4])<0.001) Life=false;

	if(elh[4]>=(-0.001)||!Life)
	{
		Time=TimeStep;
		for(int i=0;i<Size;i++) el[i]=elh[i];
	}
	else
	{  	Step=Step/2;
		NumPrint*=2;
		return;
	};

	if(!Life) OutputFile();


};

void Noise::PrintInFile()
{
	if(Time > TimeEndPrint){Life=false;return;}
	if(Time < TimeBeginPrint) return;

	NumTimePrint += 1;
	if(NumTimePrint == NumPrint)
	  {
	   NumTimePrint = 0;
	   OutputFile();
	  }
};

void Noise::OutputFile()
{
	if(!OutT) return; //Если запуск с CD-ROM

	Vector vg(Speed_gX, Speed_gY, Speed_gZ);
	double velocity =  vg.GetLength(),
		   q        =  DensityAir(Point_gY)*velocity*velocity/2,
		   mahh     =  velocity/SpeedSound(Point_gY),
		   AlfaSpace=  sqrt(Sqr(Alfa)+Sqr(Betta));

	fprintf(OutT,         "%f\n",Time	);
	fprintf(OutVx,        "%f\n",Speed_gX);
	fprintf(OutVy,        "%f\n",Speed_gY);
	fprintf(OutVz,        "%f\n",Speed_gZ);
	fprintf(OutX,         "%f\n",Point_gX);
	fprintf(OutY,         "%f\n",Point_gY);
	fprintf(OutZ,         "%f\n",Point_gZ);
	fprintf(OutWx,        "%f\n",omegaX);
	fprintf(OutWy,        "%f\n",omegaY);
	fprintf(OutWz,        "%f\n",omegaZ);
	fprintf(OutPitch,     "%f\n",Pitch*ToDegree);
	fprintf(OutYaw,       "%f\n",Yaw*ToDegree);
	fprintf(OutRoll,      "%f\n",Roll*ToDegree);
	fprintf(OutAlfa,      "%f\n",Alfa*ToDegree);
	fprintf(OutBetta,     "%f\n",Betta*ToDegree);
	fprintf(OutFx        ,"%f\n",F.X);
	fprintf(OutFy        ,"%f\n",F.Y);
	fprintf(OutFz        ,"%f\n",F.Z);
	fprintf(OutMx        ,"%f\n",M.X);
	fprintf(OutMy        ,"%f\n",M.Y);
	fprintf(OutMz        ,"%f\n",M.Z);
	fprintf(OutTETA      ,"%f\n",TETA*ToDegree);
	fprintf(OutPSI       ,"%f\n",PSI*ToDegree);
	fprintf(OutAlfaSpace ,"%f\n",AlfaSpace*ToDegree);
	fprintf(OutWx8       ,"%f\n",omegaXdm);
	fprintf(OutWz8       ,"%f\n",omegaZdm);

    fprintf(TempPowerX	 ,"%f\n",TempPower.X);
	fprintf(TempPowerY	 ,"%f\n",TempPower.Y);
	fprintf(TempPowerZ	 ,"%f\n",TempPower.Z);

};

void Noise::NextStep()
{
	Rks4();
	PrintInFile();
	ConditionTermination();
};


double Noise::SpeedSound(double height)
{
	if(height <= 0.0)
		return 340.0;

	else if(height > 0.0 && height <= 11000.0)
		return sqrt(299.79e-9*height*height - 2.6135*height + 115.80e+3);

	else if(height > 11000.0 && height <= 25000.0)
		return 295.07;

	else if(height > 25000.0 && height <= 46000.0)
		return sqrt(-179.80e-9*height*height + 1.1098*height + 59.433e+3);

	else
		return 331.82;
};

double Noise::DensityAir(double height)
{
	if(height <= 0.0)
		return 1.225;

	else if(height > 0.0 && height <= 13000.0)
		return 3.1088e-9*height*height - 114.04e-6*height + 1.223;

	else if(height > 13000.0 && height <= 26000.0)
		return log(-298.95e-12*height*height + (12.780e+3)/height + 28.677e-6*height);

	else if(height > 26000.0 && height <= 39000.0)
		return exp(-7.9310*log(height) - 94590/height + 80.891);

	else if(height > 39000.0 && height <= 49000.0)
		return exp(1.4632e-9*height*height + 264.69e-3*log(height) - 266.74e-6*height);

	else
		return 0.0;
};

double Noise::Cx(double M, double alfa_)
{
	return Cx_;
};

double Noise::Cy(double M, double alfa_)
{
	return Cy_;
};


double Noise::Cz(double M, double alfa_)
{
	return -Cy(M,alfa_);
};


double Noise::Mx_wx(double M, double alfa_)
{
	return Mx_wx_;
};

double Noise::Mz_wz(double M, double alfa_)
{
	return Mz_wz_;
};

double Noise::Mz_alfa(double M, double alfa_)
{
	return Mz_alfa_;
};

double Noise::My_wy(double M, double alfa_)
{
	return Mz_wz(M, alfa_);
};

double Noise::My_betta(double M, double alfa_)
{
	return Mz_alfa(M, alfa_);
};


double Noise::Mxvr(double M, double alfa_)
{
		return Mxvr_;
};
