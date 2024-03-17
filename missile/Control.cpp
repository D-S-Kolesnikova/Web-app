 //В этом файле определены функции управления за исключением импульсной коррекции
#include "Contract.h"

void Missile::MinMax(double min_angle, double& angle, double max_angle)
{
	if(angle < min_angle/ToDegree) angle = min_angle/ToDegree;
	if(angle > max_angle/ToDegree) angle = max_angle/ToDegree;
};

void Missile::ControlSS(void)
{
	double Pla=0;

    Vector v(Speed_gX, Speed_gY, Speed_gZ);
	double velocity =  v.GetLength(),
		   q        =  DensityAir(Point_gY)*velocity*velocity/2,
		   mahh     =  velocity/SpeedSound(Point_gY);

    //Два параметра для ликвидации исключительной ситуации при значении
    //подкоренного выражения меньше 0
    bool flagDs=true;//если тестируемое подкоренное выражение < 0.0
                     // flagDs=true иначе flagDS=false
    double Ds;  //значение выражения заключенного в функции sqrt

	double a11 = -Mz_wz(mahh,Alfa)*q*SquareMiddle*Length*Length/(Iz*velocity),
		   a12 = -Mz_alfa(mahh,Alfa)*q*SquareMiddle*Length/Iz,
           a12_= 0.0,
		   a13 = -Mz_delta(mahh, Alfa)*q*SquareMiddle*Length/Iz,
		   a42 = (Pla + Cy(mahh, Alfa)*q*SquareMiddle)/(Mass*velocity),
           a43 = Cy_delta(mahh, Alfa)*q*SquareMiddle/(Mass*velocity);

    double K_pitch, T1_pitch, T_pitch, Ksi_pitch;
    if((a12 + a11*a42)>=0.0) //оценка Ds без его непосредственного использования
           {
		   K_pitch = (a12*a43 - a13*a42)/(a12 + a11*a42);
		   T1_pitch = (-a13 + a12_*a43)/(a12*a43 - a13*a42);
		   T_pitch = 1/sqrt(a12 + a11*a42);
		   Ksi_pitch = 0.5*(a11 + a12_ + a42)/sqrt(a12 + a11*a42);
           }
	else flagDs=false;

	double b11 = -My_wy(mahh,Betta)*q*SquareMiddle*Length*Length/(Iy*velocity),
		   b12 = -My_betta(mahh,Betta)*q*SquareMiddle*Length/Iy,
           b12_= 0.0,
		   b13 = -My_delta(mahh, Betta)*q*SquareMiddle*Length/Iy,
		   b42 = (Pla-Cz(mahh,Betta)*q*SquareMiddle)/(Mass*velocity),
           b43 = -Cz_delta(mahh,Betta)*q*SquareMiddle/(Mass*velocity);

	double K_yaw, T1_yaw, T_yaw, Ksi_yaw;
    if((b12 + b11*b42)>=0.0) //оценка Ds без его непосредственного использования
           {
		   K_yaw = (b12*b43 - b13*b42)/(b12 + b11*b42);
		   T1_yaw = (-b13 + b12_*b43)/(b12*b43 - b13*b42);
		   T_yaw = 1/sqrt(b12 + b11*b42);
		   Ksi_yaw = 0.5*(b11 + b12_ + b42)/sqrt(b12 + b11*b42);
           }
	else flagDs=false;

	double K_roll = -Mx_delta(mahh,Alfa)*velocity/(Mx_wx(mahh,Alfa)*Length),
		   T_roll = -Ix*velocity/(Mx_wx(mahh,Alfa)*q*SquareMiddle*Length*Length);

        Ds=Ksi_pitch_SS*Ksi_pitch_SS*Ksi_pitch_SS*Ksi_pitch_SS*T_pitch*T_pitch-
           2*Ksi_pitch*Ksi_pitch_SS*Ksi_pitch_SS*T_pitch*T1_pitch + T1_pitch*T1_pitch*
           Ksi_pitch_SS*Ksi_pitch_SS;
           if((Ds>=0.0)&&(flagDs))
	LawSpeedPitch =
           -2*T_pitch*(Ksi_pitch*T1_pitch - Ksi_pitch_SS*T_pitch -
           sqrt(Ds))/(K_pitch*T1_pitch*T1_pitch),
    LawGuidancePitch=
           K_pitch_SS*(1+LawSpeedPitch*K_pitch)/K_pitch;

        Ds=Ksi_yaw_SS*Ksi_yaw_SS*Ksi_yaw_SS*Ksi_yaw_SS*T_yaw*T_yaw-
           2*Ksi_yaw*Ksi_yaw_SS*Ksi_yaw_SS*T_yaw*T1_yaw + T1_yaw*T1_yaw*
           Ksi_yaw_SS*Ksi_yaw_SS;
           if((Ds>=0.0)&&(flagDs))
	LawSpeedYaw =
           -2*T_yaw*(Ksi_yaw*T1_yaw - Ksi_yaw_SS*T_yaw -
           sqrt(Ds))/(K_yaw*T1_yaw*T1_yaw);
	LawGuidanceYaw =
           K_yaw_SS*(1+LawSpeedPitch*K_yaw)/K_yaw;


//double T_pitch_SS=T_pitch/sqrt(LawSpeedPitch*K_pitch + 1);
//double T_yaw_SS=T_yaw/sqrt(LawSpeedYaw*K_yaw + 1);

    LawSpeedRoll =
           (2*Ksi_roll_SS*T_roll - T_roll_SS)/(T_roll_SS*K_roll);
    LawRoll =
           T_roll/(T_roll_SS*T_roll_SS*K_roll);

}
//---------------------------------------------------------------------------
void Missile::ControlSN(void)
{
//////////////////////////////
    Rgt = TargetONE.GetXYZ (Time);
    Vector Vgt = TargetONE.GetVXYZ(Time);
    double dx  = Rgt.X - Point_gX,
		   dy  = Rgt.Y - Point_gY,
		   dz  = Rgt.Z - Point_gZ,
           dvx = Vgt.X - Speed_gX,
		   dvy = Vgt.Y - Speed_gY,
		   dvz = Vgt.Z - Speed_gZ;
	Vector dr(dx, dy, dz),
           dv(dvx, dvy, dvz);

//Определение угла пеленга->
	Matrix A_;//Матрица перехода от норм. земн. с.к. к связанной
    A_.GetMatrix(ro_rg, lamda_rg, mu_rg, nu_rg);
	Vector Rlat = A_*dr;

    //Запоминаем значения на прошлом шаге ула пеленга->
	double VisibilityFIold=VisibilityFI;
	double VisibilityHIold=VisibilityHI;
    //Запоминаем значения на прошлом шаге ула пеленга-<

	VisibilityFI = atan2(Rlat.Y,Rlat.X);
	VisibilityHI =-atan2(Rlat.Z,Rlat.X);
//Определение угла пеленга-<

//Определение угловой скорости по углу пеленга->
	if(Time<Step)
    	{
    	AccelerationVisibilityFI=0.0;
    	AccelerationVisibilityHI=0.0;
    	}
    else
    	{
    	AccelerationVisibilityFI=(VisibilityFIold-VisibilityFI)/Step;
    	AccelerationVisibilityHI=(VisibilityHIold-VisibilityHI)/Step;
    	}

    if(fabs(AccelerationVisibilityFI)>1.50)
    AccelerationVisibilityFI=0;
    if(fabs(AccelerationVisibilityHI)>1.50)
    AccelerationVisibilityHI=0;

//Определение угловой скорости по углу пеленга->

	Matrix B; B.GetMatrix(dr.GetPitch(), dr.GetYaw(), 0);
	B = ~B;
	Vector w = B*dv;
	double Remoteness = dr.GetLength();
	Fi = dr.GetPitch();
    /*
    //Выберем коэффициенты пропорциональностами по каналам для первичной оценки
    //данные элементы требуется уточнить
    double CoefficientYaw=3.0;
    double CoefficientPitch=3.0;
    */
    //Данный параметр реализует численное диференцирование для получения
    //"производной по ХИ" помноженной на CoefficientYaw, которая используется
    //при невозможности найти эту величину иным способом представленным ниже
	double guidance_yaw_number = CoefficientYawCr*CoefficientYaw*(dr.GetYaw() - Hi)/Step;

	Hi = dr.GetYaw();

	GuidanceRoll = 0.0;

    //"ослепление" ГСН ЛА
	if(Remoteness <= RemotenessMax) return;

     //"производная по ФИ" помноженная на CoefficientPitch
	 GuidancePitch = CoefficientPitchCr*CoefficientPitch*w.Y/Remoteness;

     //"производная по ХИ" помноженная на CoefficientYaw с реализацией обхода
     //особой точки с cos(Fi)=0
	 if(fabs(Fi*ToDegree) < 89.0)
        GuidanceYaw = -CoefficientYawCr*CoefficientYaw*w.Z/(Remoteness*cos(Fi));
	 else
	    GuidanceYaw = guidance_yaw_number;

     UFI=GuidancePitch/CoefficientPitchCr-CoefficientVisibilityFI*VisibilityFI;
     UHI=GuidanceYaw  /CoefficientYawCr  -CoefficientVisibilityHI*VisibilityHI;

   if(NxControl)//Переопределяем коеффициенты в зависимости от осевой перегрузки
   {
   LawGuidancePitch=exp(-21.184e-3 * Nx + 4.611)+ 0.02*Nx;
   LawSpeedPitch   =exp(-127.7e-9 * Nx*Nx*Nx + 108.29e-6 *Nx*Nx -29.676e-3 *Nx)+ 0.0002*Nx;

   LawGuidanceYaw  =exp(-18.933e-3 * Nx + 4.619)+ 0.02*Nx;
   LawSpeedYaw     =exp( 6.3e-6 *Nx*Nx -22.876e-3 *Nx - 243.41e-3)+ 0.0006*Nx;

   LawRoll         =-1800.0;
   LawSpeedRoll    =0.00000024457*Nx*Nx+0.00021261*Nx-19.803;  //*/
   }

    if(NotAuto)
    {
UFI=-0.01910968 - 0.07016129*VisibilityFI*ToDegree;
if (UFI>0.143) UFI=0.143;
if (UFI<0.019) UFI=0.019;
 
UHI=-0.05951898 - 0.042464768*VisibilityHI*ToDegree;
if (UHI>0.42000) UHI=0.42000;
if (UHI<0.01500) UHI=0.01500;
    }
    if(Unull) UFI=UHI=0.0;

    if (!YesVisibility)
    {
    DeltaPitch = LawGuidancePitch*GuidancePitch - LawSpeedPitch*omegaZ;
   	DeltaYaw   = LawGuidanceYaw*GuidanceYaw - LawSpeedYaw*omegaY;
    }
    else
    {
    DeltaPitch = LawGuidancePitch*CoefficientPitchCr*
                (CoefficientVisibilityFI*VisibilityFI + UFI) - LawSpeedPitch*omegaZ;
	DeltaYaw   = LawGuidanceYaw*CoefficientYawCr*
                (CoefficientVisibilityHI*VisibilityHI + UHI) - LawSpeedYaw * omegaY;
    }

	DeltaRoll = LawRoll*(GuidanceRoll - Roll) - LawSpeedRoll*omegaX;
    StabRoll  = DeltaRoll;


	MinMax(-15.0, DeltaPitch, 15.0);
	MinMax(-15.0, DeltaYaw,   15.0);
    MinMax(-15.0, DeltaRoll,  15.0);
    MinMax(-ToDegree, StabRoll,  ToDegree);
    Mroll= -0.5*DiametrMiddle*Proll*StabRoll;

//Останов упраленния по каналам тангажа и рысканья до гашения начальной угловой
//скорости и выравнивания по углу крена
     if ((fabs(Roll)<1/ToDegree)&& (fabs(omegaX)<Wx_development))
     NAVIGATION=true;
     if (!NAVIGATION)
     {
     DeltaPitch= 0;
     DeltaYaw  = 0;
     }
//   double AccelerationX; //осевая перегрузка
};
/*
void Missile::GuidanceStraight()
{
	double dx  = Target->GetXg() - Xg,
		   dy  = Target->GetYg() - Yg,
		   dz  = Target->GetZg() - Zg;
	Vector dr(dx, dy, dz), l;
	Remoteness = dr.GetLength();
	if(Remoteness <= RemotenessMax) return;
	dr.X /= Remoteness; dr.Y /= Remoteness; dr.Z /= Remoteness;
	Matrix A(Pitch, Yaw, Roll);
	A = ~A;
	l = A*dr;
	GuidancePitch =  CoefficientPitch*atan2(l.Y, l.X);
	GuidanceYaw   = -CoefficientYaw  *atan2(l.Z, l.X);
};

//////////////////////////////
*/

   /*     fprintf(fError,"afi%f vfiold%f vfi%f Step%f\n",
            	AccelerationVisibilityFI,VisibilityFIold,VisibilityFI,Step);

        fprintf(fError,"ahi%f vhiold%f vhi%f Step%f\n",
            	AccelerationVisibilityHI,VisibilityHIold,VisibilityHI,Step);*/
