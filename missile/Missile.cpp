// File Missile.cpp

#include "Contract.h"
#include <conio.h>

double Sqr(double w) {return w*w;}


Missile::Missile (double M0nu,double Dmnu,double Lnu,
				  double Ixnu,double Iynu,double Iznu,
                  double LengthOiXnu,double LengthOiYnu,double LengthOiZnu,
                  double dzetaiMinnu,double dzetaiMaxnu,
				  double Vnu,
	 			  double TETAnu,double PSInu,
				  double tetanu,double psinu,double gammanu,
				  double omegaxnu,double omegaynu,double omegaznu,
			      double xnu,double ynu,double znu,
			      double hnu,int step_print_maxnu,
				  double TimeBeginPrintnu, double TimeEndPrintnu, double Time0nu,
                  double Kmvrnu, double Kmgnu,
                  int Quantitynu,
                  double REnginenu, double FiEnginenu,
                  double PowerEngineXnu, double PowerEngineYnu, double PowerEngineZnu,
                  double TawEnginenu,
                  int TawPuskMinusMaxnu,
                  double LawDegnu,
				  double SwitchMassnu, double SwitchTimenu, double SwitchdTimenu,
                  double accelerationtnu, double velocitytnu, double velocityMax_tnu,
                  double TETAt, double PSIt,                  double RgtXnu, double RgtYnu, double RgtZnu,                  bool ControlUnu,                  bool Pulsenu,                  double SpeedNoseXnu, double SpeedNoseYnu, double SpeedNoseZnu,                  double AngelSpeedNoseXnu, double AngelSpeedNoseYnu, double AngelSpeedNoseZnu,                  double InewXnu, double InewYnu, double InewZnu,                  double INoseXnu, double INoseYnu, double INoseZnu,                  bool   VidTruenu, int RepeatEnginenu,                  double Kccpitchnu, double Ksipitchnu,                  double Kccyawnnu,  double Ksiyawnu,                  double Tccrollnu,  double Ksirollnu,                  double CoefficientPitchnu,        double CoefficientYawnu,                  double CoefficientPitchCrnu,      double CoefficientYawCrnu,				  double CoefficientVisibilityFInu, double CoefficientVisibilityHInu,                  double PRollnu,                  double AbsWxnu,                  double KADMxnu,                  bool NxControlnu,                  bool YesVisibilitynu, bool NotAutonu, bool Unullnu,                  //"ослепление" ГСН ЛА                  double RemotenessMaxnu):Object()
	{
    fError=fopen("fError.err","w");
    //Параметры системы управления, не импульсная коррекция
				  K_pitch_SS=Kccpitchnu;  Ksi_pitch_SS=Ksipitchnu;
                  K_yaw_SS  =Kccyawnnu;   Ksi_yaw_SS=Ksiyawnu;                  T_roll_SS =Tccrollnu;   Ksi_roll_SS=Ksirollnu;
                  DeltaPitch=DeltaYaw=DeltaRoll=0.0;

                 CoefficientPitch=CoefficientPitchnu;
                 CoefficientYaw=CoefficientYawnu;
                 CoefficientPitchCr=CoefficientPitchCrnu;
                 CoefficientYawCr=CoefficientYawCrnu;			   	 CoefficientVisibilityFI=CoefficientVisibilityFInu;			     CoefficientVisibilityHI=CoefficientVisibilityHInu;
                  Proll=PRollnu;
                  Mroll=StabRoll=0.0;
                  Wx_development=AbsWxnu;                  K_AD_development=KADMxnu;                  NAVIGATION=false;
                  OmegaXcorrection=true;
                  NxControl=NxControlnu;

                  YesVisibility=YesVisibilitynu;
                  NotAuto=NotAutonu;
                  Unull=Unullnu;

                  RemotenessMax=RemotenessMaxnu;

    //Параметры системы управления, не импульсная коррекция
	switch(Type_Missile)
		{
		case 1:
			{
			   aerotablica (39,amxvr  );


			    ///////////////////////////////////////////////////
			    ////Начало параметров корректирующих двигателей////
                ControlU  = ControlUnu;
			    Quantity  = Quantitynu;
                REngine   = REnginenu;
                FiEngine  = FiEnginenu;
                dzetaiMin = dzetaiMinnu;
                dzetaiMax = dzetaiMaxnu;
                LawDeg    = LawDegnu;
                S         = new Matrix[Quantity];
                rEngine   = new Vector[Quantity];

//"-" - перед тягой показывает направление толчка от двигателя
                PowerEngine.X = -PowerEngineXnu;
                PowerEngine.Y = -PowerEngineYnu;
                PowerEngine.Z = -PowerEngineZnu;

                TawEngine     =    TawEnginenu;
                TawEndEngine  = new double[Quantity];

                double  DELTA=360.0/Quantity;
                double *EpselonEngine;
                EpselonEngine = new double[Quantity];
                HiiEngine     = new double[Quantity];

                double  EpselonEngineTemp=90-DELTA;
                //Тестовая Печать->
                FILE *fEngine;
                fEngine=fopen("fEngine.txt","w");
                //Тестовая Печать<-
                for (int ij=0; ij<Quantity; ij++)
                	{
                        EpselonEngineTemp+=DELTA;
                        if(EpselonEngineTemp>180.0)
                     	EpselonEngine[ij]=(EpselonEngineTemp-360.0)/ToDegree;
                        else
                     	EpselonEngine[ij]=EpselonEngineTemp/ToDegree;

                         rEngine[ij].X =-0.5*DiametrMiddle*cos(EpselonEngine[ij])*cos(FiEngine)+REngine;
                         rEngine[ij].Y = 0.5*DiametrMiddle*sin(EpselonEngine[ij]);
                         rEngine[ij].Z =-0.5*DiametrMiddle*cos(EpselonEngine[ij])*sin(FiEngine);

                         TawEndEngine[ij]=-1.0;

                         HiiEngine[ij]=ij*DELTA/ToDegree;

                         //Матрица перехода от исполнительной k связанной с.к.
                         S[ij].GetMatrix(EpselonEngine[ij],FiEngine,0.0);

                 //Тестовая Печать->
                fprintf(fEngine,"EpselonEngine[%d]=%f;EpselonEngineTemp=%f\nHiiEngine[%d]=%f;\n",
                        ij,EpselonEngine[ij]*ToDegree,EpselonEngineTemp,
                        ij,HiiEngine[ij]*ToDegree);

                         S[ij].fShowM(S[ij],fEngine);
                         PowerEngine.fShowV(S[ij]*PowerEngine,fEngine);
                 //Тестовая Печать<-



                         TawPuskMinus=0;
                         //+1 для корректного использования интервалов без коррекции
                         //см. соответствующую процедуру
                         TawPuskMinusMax=TawPuskMinusMaxnu+1;
                         RepeatEngine=RepeatEnginenu;

                    }

                //Тестовая Печать->
                fclose(fEngine);
                //Тестовая Печать<-

                delete [] EpselonEngine;

			    DeltaMulti  = new int[Quantity];
			    DeltaDzetai = new int[Quantity];
			    DeltaHii    = new int[Quantity];
			    DeltaTaw    = new int[Quantity];
			    DeltaFirst  = new int[Quantity];
                DeltaSecond = new int[Quantity];

                for (int ij=0; ij<Quantity; ij++)
                {
                DeltaMulti[ij] = DeltaDzetai[ij] = DeltaHii[ij] =
                DeltaTaw[ij]   = DeltaFirst[ij]  = DeltaSecond[ij] = 0;
                }

			    ////Конец параметров корректирующих двигателей/////
			    ///////////////////////////////////////////////////

                 //-> Импульсный блок отделения обтекателя
                  Pulse=Pulsenu;
                  Inew.TestGetVector(InewXnu,InewYnu,InewZnu);                  INose.TestGetVector(INoseXnu,INoseYnu,INoseZnu);                  SpeedNose.TestGetVector(SpeedNoseXnu,SpeedNoseYnu,SpeedNoseZnu);                  AngelSpeedNose.TestGetVector(AngelSpeedNoseXnu,AngelSpeedNoseYnu,AngelSpeedNoseZnu);                 //<- Импульсный блок отделения обтекателя                 VidTrue=VidTruenu;
			  break;
			}
		}

	Size = 13;
	el    = new double [Size];
	elh   = new double [Size];
	Left  = new double [Size];


		Mass=M0nu;			  Alfa=TETAnu; Point_gX=xnu;
		DiametrMiddle=Dmnu;   Betta=PSInu;  Point_gY=ynu;
		Length=Lnu;						   Point_gZ=znu;
//  \\--> Изменен порядок ввода начальных условий,
//  //--> то есть целесообразно вводить н.у. не по углам подъема траектории
//        и курсовому, а углы атаки и скольжения
        LengthOiX=LengthOiXnu;
        LengthOiY=LengthOiYnu;
        LengthOiZ=LengthOiZnu;
		Ix=Ixnu;              Pitch =tetanu;
		Iy=Iynu;              Yaw   =psinu;
		Iz=Iznu;              Roll  =gammanu;
		                      omegaX=omegaxnu;
   		                      omegaY=omegaynu;
   		                      omegaZ=omegaznu;

		Step=hnu;
		NumPrint=step_print_maxnu;
		NumTimePrint = -1;
        SwitchStep=0;

		TimeBeginPrint=TimeBeginPrintnu;
		TimeEndPrint  =TimeEndPrintnu;
		if (TimeEndPrint<0.0) TimeEndPrint=24.0*60.0*60.0;

		Kmvr=Kmvrnu; Kmg=Kmgnu;

		SquareMiddle=Pi*DiametrMiddle*DiametrMiddle/4;

		Matrix A; A.GetMatrix(Pitch, Yaw, Roll);

        /*
        Правильность определения  Alfa и Betta по нижеприведенным формулам надо проверять,
        так как было решено использовать эти углы в качестве н.у., то необходимость в этих действиях отпадает
		Alfa =Pitch-TETA;
		Betta=(Yaw-PSI)*cos(TETA);
        */

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
	OutVisibility=fopen("Visibility.txt", "w");
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
    Outdzetai    =fopen("dzetai.txt", "w");
	Outhii       =fopen("hii.txt", "w");
	OutTargetX   =fopen("TargetX.txt", "w");
	OutTargetY   =fopen("TargetY.txt", "w");
	OutTargetZ   =fopen("TargetZ.txt", "w");

   	fPulse       =fopen("fPulse.txt", "w");

    f_Temp       =fopen("f_Temp.txt","w");
    TempPowerX   =fopen("TPX.txt", "w");
	TempPowerY   =fopen("TPY.txt", "w");
	TempPowerZ   =fopen("TPZ.txt", "w");
   	OutDpitch    =fopen("Dpitch.txt", "w");
    OutDyaw      =fopen("Dyaw.txt", "w");
    OutDroll     =fopen("Droll.txt", "w");

    //Удаление файлов, которые не создаются заново при каждом расчете, а дописываются
    remove("LGPitch.txt");
	remove("LSPitch.txt");
	remove("LGYaw.txt"  );
	remove("LSYaw.txt"  );
	remove("LRoll.txt"  );
	remove("LSRoll.txt" );
	remove("AccX.txt"   );
	remove("VFI.txt"    );
	remove("VHI.txt"    );
	remove("UFI.txt"    );
	remove("UHI.txt"    );
    remove("AccelerationVisibilityFI.txt"    );
	remove("AccelerationVisibilityHI.txt"    );


   TargetONE.GetTargetOne(accelerationtnu, velocitytnu, velocityMax_tnu,
                          TETAt, PSIt, RgtXnu, RgtYnu, RgtZnu);    SwitchMass=SwitchMassnu;    SwitchTime=SwitchTimenu;
    SwitchdTime=SwitchdTimenu;
    SwitchCorrection=0;
};//
Missile::~Missile()
{
	delete [] el;
	delete [] elh;
	delete [] Left;

	switch(Type_Missile)
		{
		case 1:
	        {
			delete [] DeltaMulti;
			delete [] DeltaDzetai;
			delete [] DeltaHii;
			delete [] DeltaTaw;
			delete [] DeltaFirst;
            delete [] DeltaSecond;
            delete [] S;
            delete [] rEngine;
            delete [] TawEndEngine;
            delete [] HiiEngine;
            break;
	        }
        }
    fclose(fError);
	fclose(OutT);
	fclose(OutVx); 		 fclose(OutVy); 	fclose(OutVz);
	fclose(OutX); 		 fclose(OutY); 		fclose(OutZ);
	fclose(OutWx); 		 fclose(OutWy); 	fclose(OutWz);
	fclose(OutPitch);    fclose(OutYaw); 	fclose(OutRoll);
	fclose(OutAlfa);	 fclose(OutBetta);	fclose(OutVisibility);
	fclose(OutFx);		 fclose(OutFy);		fclose(OutFz);
	fclose(OutMx);		 fclose(OutMy);		fclose(OutMz);
	fclose(OutTETA);	 fclose(OutPSI);
    fclose(OutAlfaSpace);fclose(OutWx8);	fclose(OutWz8);
    fclose(Outdzetai);   fclose(Outhii);
  	fclose(OutTargetX);	 fclose(OutTargetY);fclose(OutTargetZ);

    fclose(fPulse);
    fclose(f_Temp);
  	fclose(TempPowerX);	 fclose(TempPowerY);fclose(TempPowerZ);
   	fclose(OutDpitch);	 fclose(OutDyaw);   fclose(OutDroll);
};

//
void Missile::PowerEngineCorrection(void)
{
NCorrection.X     = NCorrection.Y     = NCorrection.Z     =
PowerCorrection.X = PowerCorrection.Y = PowerCorrection.Z = 0.0;


   double hii_360;
   double dzeta_360;

   if (VidTrue)
   	{
    hii_360=hia;
    dzeta_360=dzetaa;
    }
   else
    {
    hii_360=hii;
    dzeta_360=dzetai;
    }

   double hii_Correction=hii_360+Pi;
   double hii_sp=hii_Correction;
   hii_Correction=hii_360+Pi+LawDeg;
   if (hii_Correction>2*Pi) hii_Correction=hii_Correction-2*Pi;
   //LawDeg - угол упреждения

   Vector *powerCorrection;
   Vector *nCorrection;

    powerCorrection = new Vector[Quantity];
 	nCorrection     = new Vector[Quantity];

    bool   lp=false;
    double ak;

      for (int ij=0; ij<Quantity; ij++)
      {
      if ((DeltaFirst[ij] == 1)&& (DeltaTaw[ij] == 0))
         {
         ak=hii_Correction-HiiEngine[ij];

         if (omegaX<=0)
         if ((ak>=0)    &&(ak<= 10*Step)) lp=true;

         if (omegaX> 0)
         if (
             ((ak<=0)   &&(ak>=-10*Step))
             ||
             ((ak<=2*Pi)&&(ak>=2*Pi-10*Step))
            )lp=true;


         if(lp)
         {DeltaHii[ij]=1;lp=false;}
         else DeltaHii[ij]=0;

  	     if ((dzeta_360<=dzetaiMax)&&(dzeta_360>=dzetaiMin))
         DeltaDzetai[ij]=1;
         else DeltaDzetai[ij]=0;

         if ((DeltaHii[ij]==1)&&(DeltaDzetai[ij]==1)&&(TawPuskMinus==0))
            {
            DeltaSecond[ij]++;
           	if (DeltaSecond[ij]==RepeatEngine) DeltaFirst[ij]   = 0;
            TawEndEngine[ij] = Time + TawEngine;
            DeltaTaw[ij]     = 1;
            //Проверочная печать->
            fprintf(OutVisibility,"Включился двигатель № %d\n",ij);
            fprintf(OutVisibility,"Срабатывание № %d\n",DeltaSecond[ij]);
            fprintf(OutVisibility,"Time = %f [c] TawEndEngine[%d] = %f [c]\n",Time,ij,TawEndEngine[ij]);
            fprintf(OutVisibility,"hii = %f [rad] = %f [deg]\n",hii,hii*ToDegree);
            fprintf(OutVisibility,"hia = %f [rad] = %f [deg]\n",hia,hia*ToDegree);
            fprintf(OutVisibility,"hig = %f [rad] = %f [deg]\n",hig,hig*ToDegree);
            fprintf(OutVisibility,"hii_Correction = %f [rad] = %f [deg]\n",hii_Correction,hii_Correction*ToDegree);
            fprintf(OutVisibility,"Значение угла коррекции без упреждения hii_sp = %f [rad] = %f [deg]\n",hii_sp,hii_sp*ToDegree);
            fprintf(OutVisibility,"Значение угла упреддения hii_упр = %f [rad] = %f [deg]\n",LawDeg,LawDeg*ToDegree);
            fprintf(OutVisibility,"HiiEngine[%d]   = %f [rad] = %f [deg]\n",ij,HiiEngine[ij],HiiEngine[ij]*ToDegree);
            fprintf(OutVisibility,"dzetai = %f [rad] = %f [deg]\n",dzetai,dzetai*ToDegree);
            fprintf(OutVisibility,"dzetaa = %f [rad] = %f [deg]\n",dzetaa,dzetaa*ToDegree);
            fprintf(OutVisibility,"dzetag = %f [rad] = %f [deg]\n",dzetag,dzetag*ToDegree);
            fprintf(OutVisibility,"Roll   = %f [rad] = %f [deg]\n",Roll,  Roll  *ToDegree);
            fprintf(OutVisibility,"DeltaFirst = %d DeltaHii = %d DeltaDzetai = %d DeltaTaw = %d\n",
                                   DeltaFirst[ij], DeltaHii[ij], DeltaDzetai[ij], DeltaTaw[ij]);
            fprintf(OutVisibility,"********************************************\n");
            //Проверочная печать<-

            }
            if ((DeltaHii[ij]==1)&&(DeltaDzetai[ij]==1)) ++TawPuskMinus;
            if (TawPuskMinus==TawPuskMinusMax) TawPuskMinus=0;
        }

      if (DeltaTaw[ij] == 1) if (Time>=TawEndEngine[ij]) DeltaTaw[ij]=0;
         //  Данная хитрость при ее включении позволяет рассматривать
         //  коррекцию только с помощью одного 0-го двигателя
         //  for (int ij=1; ij<Quantity; ij++) DeltaTaw[ij]=0;

      DeltaMulti[ij] = DeltaHii[ij]*DeltaDzetai[ij]*DeltaTaw[ij];

      powerCorrection[ij] = (S[ij]*PowerEngine)*DeltaMulti[ij];
      PowerCorrection     = PowerCorrection + powerCorrection[ij];


      nCorrection[ij] = rEngine[ij]%powerCorrection[ij];
      NCorrection     = NCorrection + nCorrection[ij];

      }

	delete [] powerCorrection;
	delete [] nCorrection;
}
//

void Missile::ChangeStep(void)
{
    int DeltaTemp=0;
    for (int ij=0; ij<Quantity; ij++)   DeltaTemp+=DeltaFirst[ij];

    if ((DeltaTemp>0)&&(dzetai<dzetaiMax)&&(SwitchStep==0))
    	{
        Step=0.1*Step;
        SwitchStep=1;
        }

    if (((DeltaTemp==0)||(dzetai>dzetaiMax))&&(SwitchStep==1))
        {
        Step=10*Step;
        SwitchStep=0;
        }
}
//
void Missile::SetAngle(double r, double l, double m, double n)
{
    if (fabs(2*r*n + 2*l*m)<=1.0)
		Pitch = asin (2*r*n + 2*l*m);
    else
    	{
    	Pitch = asin ((2*r*n + 2*l*m)/fabs(2*r*n + 2*l*m));
    	fprintf(fError,"Time=%f, Pitch=asin(%f)\n",Time,2*r*n + 2*l*m);
    	}

	Roll  = atan2(2*r*l - 2*n*m, r*r + m*m - n*n - l*l);
	Yaw   = atan2(2*r*m - 2*l*n, r*r + l*l - m*m - n*n);
};

void Missile::RightPart()
{

	SetAngle(ro_rg, lamda_rg, mu_rg, nu_rg);

	Vector vg(Speed_gX, Speed_gY, Speed_gZ);
	double velocity =  vg.GetLength(),
		   q        =  DensityAir(Point_gY)*velocity*velocity/2,
		   mahh     =  velocity/SpeedSound(Point_gY);

/*//Можно использовать любой подход этот или 2-ой, это одно и тоже,
  //только этот подход более медленный при вычеслении
    //Матрица перехода от связанной k норм. земн. с.к.
	Matrix A; A.GetMatrix(Pitch, Yaw, Roll);
   	Matrix A_= A;
           A_=~A_;*/

//2-ой подход
	Matrix A_;//Матрица перехода от норм. земн. с.к. к связанной
    A_.GetMatrix(ro_rg, lamda_rg, mu_rg, nu_rg);

   	Matrix A= A_;//Матрица перехода от связанной с.к. к норм. земн.
           A=~A;
	Vector v = A_*vg;
	Alfa = -atan2(v.Y, v.X);

    if (fabs(v.Z/velocity)<=1.0)
    	Betta = asin(v.Z/velocity);
    else
    	{
    	Betta = asin((v.Z/velocity)/fabs(v.Z/velocity));
    	fprintf(fError,"Time=%f, Betta=asin(%f)\n",Time,v.Z/velocity);
    	}



	double AlfaSpace=sqrt(Sqr(Alfa)+Sqr(Betta));

		   F.X  = -Cx(mahh,AlfaSpace)*q*SquareMiddle;
		   F.Y  = (Cy(mahh,Alfa)*Alfa  + Cy_delta(mahh, Alfa) *DeltaPitch)*q*SquareMiddle;
		   F.Z  = (Cz(mahh,Betta)*Betta + Cz_delta(mahh, Betta)*DeltaYaw  )*q*SquareMiddle;

		   M.X = (Mx_wx(mahh,AlfaSpace)*omegaX*Length/velocity + K_AD_development*Mx_delta(mahh,AlfaSpace)*DeltaRoll
                  +Kmvr*Mxvr(mahh,AlfaSpace))*q*SquareMiddle*Length + Mroll;
		   M.Y = (My_wy(mahh,Betta)*omegaY*Length/velocity + My_betta(mahh,Betta)*Betta +
		         My_delta(mahh, Betta)*DeltaYaw)*q*SquareMiddle*Length;
		   M.Z = (Mz_wz(mahh,Alfa)*omegaZ*Length/velocity + Mz_alfa(mahh,Alfa)*Alfa +
		         Mz_delta(mahh, Alfa)*DeltaPitch)*q*SquareMiddle*Length;

//omegaXdm = velocity*Mxvr(mahh,AlfaSpace)/(Mx_wx(mahh,AlfaSpace)*DiametrMiddle);
//omegaZdm = sqrt(-Mz_alfa(mahh,Alfa)*q*SquareMiddle*Length/Iz);


    Vector Gg(0.0,-Kmg*Mass*9.81,0.0);
    if (ControlU)
    	{
            TempPower=PowerCorrection;
    		F=F+PowerCorrection;
    		M=M+NCorrection;
    	}
//=================================



	fg = A*F+Gg;
	//  TempPower=fg;

    //Определяем осевую перегрузку
    Vector FforNx=A_*fg; Nx=fabs(FforNx.X/Mass);

    if (fabs(Speed_gY/velocity)<=1.0)
		TETA=asin( Speed_gY/velocity);
    else
    	{
    	Betta = asin((Speed_gY/velocity)/fabs(Speed_gY/velocity));
    	fprintf(fError,"Time=%f, TETA=asin(%f)\n",Time,Speed_gY/velocity);
    	}

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

void Missile::Rks4()
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

void Missile::ConditionTermination()
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

void Missile::PrintInFile()
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

void Missile::OutputFile()
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
  //fprintf(OutVisibility,"%f\n",Visibility*ToDegree); - задействован для вывода
  //параметров в момент включения корректирующих двигателей в связи с отсутствием
  //необходимости определения и вывода на печать данной величины (пространственного
  //угла пеленга)
//	fprintf(OutFx        ,"%f\n",F.X);
//	fprintf(OutFy        ,"%f\n",F.Y);
//	fprintf(OutFz        ,"%f\n",F.Z);
	fprintf(OutFx        ,"%f\n",fg.X);
	fprintf(OutFy        ,"%f\n",fg.Y);
	fprintf(OutFz        ,"%f\n",fg.Z);
	fprintf(OutMx        ,"%f\n",M.X);
	fprintf(OutMy        ,"%f\n",M.Y);
	fprintf(OutMz        ,"%f\n",M.Z);
	fprintf(OutTETA      ,"%f\n",TETA*ToDegree);
	fprintf(OutPSI       ,"%f\n",PSI*ToDegree);
	fprintf(OutAlfaSpace ,"%f\n",AlfaSpace*ToDegree);
	fprintf(OutWx8       ,"%f\n",Mroll);
//	fprintf(OutWx8       ,"%f\n",omegaXdm);
	fprintf(OutWz8       ,"%f\n",StabRoll);
//	fprintf(OutWz8       ,"%f\n",omegaZdm);
	fprintf(Outdzetai    ,"%f\n",dzetai*ToDegree);
	fprintf(Outhii       ,"%f\n",hii*ToDegree);

   	fprintf(OutTargetX	 ,"%f\n",Rgt.X);
	fprintf(OutTargetY	 ,"%f\n",Rgt.Y);
	fprintf(OutTargetZ	 ,"%f\n",Rgt.Z);

    fprintf(TempPowerX	 ,"%f\n",TempPower.X);
	fprintf(TempPowerY	 ,"%f\n",TempPower.Y);
	fprintf(TempPowerZ	 ,"%f\n",TempPower.Z);

    fprintf(OutDpitch	 ,"%f\n",DeltaPitch*ToDegree);
	fprintf(OutDyaw	     ,"%f\n",DeltaYaw*ToDegree);
	fprintf(OutDroll	 ,"%f\n",DeltaRoll*ToDegree);

    FILE *FPTEMP;
    FPTEMP=fopen("LGPitch.txt","a");
	fprintf(FPTEMP,"%f\n",LawGuidancePitch);
    fclose(FPTEMP);

    FPTEMP=fopen("LSPitch.txt","a");
	fprintf(FPTEMP,"%f\n",LawSpeedPitch);
    fclose(FPTEMP);

    FPTEMP=fopen("LGYaw.txt","a");
	fprintf(FPTEMP,"%f\n",LawGuidanceYaw);
    fclose(FPTEMP);

    FPTEMP=fopen("LSYaw.txt","a");
	fprintf(FPTEMP,"%f\n",LawSpeedYaw);
    fclose(FPTEMP);

    FPTEMP=fopen("LRoll.txt","a");
	fprintf(FPTEMP,"%f\n",LawRoll);
    fclose(FPTEMP);
    FPTEMP=fopen("LSRoll.txt","a");
	fprintf(FPTEMP,"%f\n",LawSpeedRoll);
    fclose(FPTEMP);

    FPTEMP=fopen("AccX.txt","a");
	fprintf(FPTEMP,"%f\n",Nx);
    fclose(FPTEMP);

    FPTEMP=fopen("VFI.txt","a");
	fprintf(FPTEMP,"%f\n",VisibilityFI*ToDegree);
    fclose(FPTEMP);

    FPTEMP=fopen("VHI.txt","a");
	fprintf(FPTEMP,"%f\n",VisibilityHI*ToDegree);
    fclose(FPTEMP);

    FPTEMP=fopen("UFI.txt","a");
	fprintf(FPTEMP,"%f\n",UFI);
    fclose(FPTEMP);

    FPTEMP=fopen("UHI.txt","a");
	fprintf(FPTEMP,"%f\n",UHI);
    fclose(FPTEMP);

    FPTEMP=fopen("AVFI.txt","a");
	fprintf(FPTEMP,"%f\n",AccelerationVisibilityFI);
    fclose(FPTEMP);

    FPTEMP=fopen("AVHI.txt","a");
	fprintf(FPTEMP,"%f\n",AccelerationVisibilityHI);
    fclose(FPTEMP);

    //При работе двигателей выводится на печать следующая информация
    for(int ij=0;ij<Quantity;++ij)
    if (DeltaTaw[ij] == 1)
    {
      Matrix A; A.GetMatrix(Pitch, Yaw, Roll);
      Vector Pg;
      Pg=A*PowerCorrection;

      fprintf(OutVisibility,"~Норм. земн. с.к.~ -> Pgx = %f Pgy = %f Pgz = %f \n",
                                                   Pg.X,    Pg.Y,    Pg.Z);

      fprintf(OutVisibility,"~Cвяз. с ЛА  с.к.~ -> Pax = %f Pay = %f Paz = %f \n",
                             PowerCorrection.X,PowerCorrection.Y,PowerCorrection.Z);

      fprintf(OutVisibility,"~Cвяз. с ЛА  с.к.~ -> Max = %f May = %f Maz = %f \n",
                             NCorrection.X,NCorrection.Y,NCorrection.Z);

      fprintf(OutVisibility,"X = %f Y = %f Z = %f Xt = %f Yt = %f Zt = %f \n",
                             Point_gX,Point_gY,Point_gZ,Rgt.X,Rgt.Y,Rgt.Z);

      break;
     }


};

void Missile::NextStep()
{
	Rks4();
    ControlSS();
    ControlSN();
    PrintInFile();
	ConditionTermination();
//=================================
    if (ControlU)
    	{
           SetAngle(ro_rg, lamda_rg, mu_rg, nu_rg);

		   SwitchCorrectionStart();
   //*
	Matrix A_;//Матрица перехода от норм. земн. с.к. к связанной
    A_.GetMatrix(ro_rg, lamda_rg, mu_rg, nu_rg);

   	Matrix A= A_;//Матрица перехода от связанной с.к. к норм. земн.
           A=~A;
   //*/
   /*
   Matrix A ; A.GetMatrix(Pitch, Yaw, Roll);
   Matrix A_=A; A_=~A_;
   //*/
    		ControlCorrectionFlight(A,A_);
	   		PowerEngineCorrection();
   		}

//=================================
};

void Missile::SwitchCorrectionStart()
{
  if((Time>=SwitchTime)&&(Time<(SwitchTime+SwitchdTime))&&(SwitchCorrection==0))
  {
   if(Pulse)
   	{
    Vector vg(Speed_gX, Speed_gY, Speed_gZ);
    DeltaSpeed=(Mass-SwitchMass)*(vg-SpeedNose)/SwitchMass;

    Vector I(Ix,Iy,Iz);
    Vector Omega(omegaX,omegaY,omegaZ);
    DeltaAngelSpeed=((I-Inew)*Omega-INose*AngelSpeedNose)/I;

    Speed_gX=Speed_gX+DeltaSpeed.X;
    Speed_gY=Speed_gY+DeltaSpeed.Y;
	Speed_gZ=Speed_gZ+DeltaSpeed.Z;
	omegaX=omegaX+DeltaAngelSpeed.X;
	omegaY=omegaY+DeltaAngelSpeed.Y;
	omegaZ=omegaZ+DeltaAngelSpeed.Z;

        Pulse=false;

      //->
fprintf(fPulse,"~ ВКЛЮЧЁН УЧЁТ ИМПУЛЬСНОГО ВОЗДЕЙСТВИЯ ПРИ СБРОСЕ ОБТЕКАТЕЛЯ ~\n");
fprintf(fPulse,"~Норм. земн. с.к.~ ->\n~Скорость мины до отделения обтекателя(м/с)\n");
fprintf(fPulse,"Vgx=%f\tVgy=%f\tVgz=%f\t\n",vg.X,vg.Y,vg.Z);
fprintf(fPulse,"~Норм. земн. с.к.~ ->\n~Скорость мины после отделения обтекателя(м/с)\n");
fprintf(fPulse,"Vgx=%f\tVgy=%f\tVgz=%f\t\n",Speed_gX,Speed_gY,Speed_gZ);
fprintf(fPulse,"~Связ. с ЛА  с.к.~ ->\n~Скорость мины до отделения обтекателя(м/с)\n");
fprintf(fPulse,"Wx=%f\tWy=%f\tWz=%f\t\n",Omega.X,Omega.Y,Omega.Z);
fprintf(fPulse,"~Связ. с ЛА  с.к.~ ->\n~Скорость мины после отделения обтекателя(м/с)\n");
fprintf(fPulse,"Wx=%f\tWy=%f\tWz=%f\t\n",omegaX,omegaY,omegaZ);
      //<-
      SavePulseFile();
    }

fprintf(fPulse,"Cтарая масса мины - %f\n", Mass);
   Mass=SwitchMass;
fprintf(fPulse,"Новая масса мины - %f\n", Mass);

fprintf(fPulse,"Cтарые моменты инерции мины - %f(Ix),%f(Iy),%f(Iz)\n",Ix,Iy,Iz);
    Ix=Inew.X;
    Iy=Inew.Y;
    Iz=Inew.Z;
fprintf(fPulse,"Новые моменты инерции мины - %f(Ix),%f(Iy),%f(Iz)\n",Ix,Iy,Iz);

   SwitchCorrection=1;
   aerotablica ( 93,amxvr  );
  }
  if((Time>(SwitchTime+SwitchdTime))&&(SwitchCorrection==1))
  {
  for (int ij=0; ij<Quantity; ij++) DeltaFirst[ij]=1;
  SwitchCorrection=2;
  }
};

void Missile::ControlCorrectionFlight(Matrix A, Matrix A_)
{
    //////////////////////////////////////////////
	/////////////Измерительный блок///////////////
    Rgt = TargetONE.GetXYZ(Time);
//  Закоментированное нужно для тестового определения положения Ц
//	Rgt.X=7400;Rgt.Y=0;Rgt.Z=50;
//  fprintf(f_Temp,"t=%f x=%f y=%f z=%f\n",Time,Rgt.X,Rgt.Y,Rgt.Z);
    Matrix D;
    nui=-Betta; mui=-Alfa;
    D.GetMatrix(nui, mui);
    Vector sg(Point_gX,Point_gY,Point_gZ);
    Vector l(LengthOiX,LengthOiY,LengthOiZ);
    sg=sg+A*l;
    Vector bg=Rgt-sg;
    Vector ba=A_*bg;
    Vector bi=D *ba;

    dzetai=atan2(sqrt( Sqr( bi.Y ) + Sqr( bi.Z )),bi.X);
    hii    =atan2(bi.Z,bi.Y);

    dzetaa=atan2(sqrt( Sqr( ba.Y ) + Sqr( ba.Z )),ba.X);
    hia    =atan2(ba.Z,ba.Y);

    dzetag=atan2(sqrt( Sqr( bg.Y ) + Sqr( bg.Z )),bg.X);
    hig    =atan2(bg.Z,bg.Y);


  /*for(int ij=0;ij<Quantity;++ij)
    if (DeltaTaw[ij] == 1)
    {
      fprintf(OutVisibility,"proverka -> \nX = %f Y = %f Z = %f Xt = %f Yt = %f Zt = %f \n",
                             Point_gX,Point_gY,Point_gZ,Rgt.X,Rgt.Y,Rgt.Z);
    fprintf(f_Temp,"bg.Z=%f\tbg.Y=%f\thig=%f\n",bg.Z,bg.Y,hig*ToDegree);

      break;
     }*/
    ChangeStep();
    /////Конец описания измерительного блока//////
    //////////////////////////////////////////////
}

void Missile::SavePulseFile()
{

	fprintf(f_Temp,"%f\n",Pitch);
	fprintf(f_Temp,"%f\n",Yaw);
	fprintf(f_Temp,"%f\n",Roll);
	fprintf(f_Temp,"%f\n",Point_gX);
	fprintf(f_Temp,"%f\n",Point_gY);
	fprintf(f_Temp,"%f\n",Point_gZ);
	fprintf(f_Temp,"%f\n",Time);

}
