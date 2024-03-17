//TargetOne.cpp - компаненты класса, описывающего движение Ц#include "contract.h"void TargetOne::GetTargetOne(double acceleration, double velocity, double velocityMax_nu,                             double TETAnu,       double PSInu,                             double X0_nu, double Y0_nu, double Z0_nu)	{
     TETA=TETAnu;
     PSI =PSInu;

     Acceleration = acceleration;
     Velocity0    = velocity;

     velocityMax=velocityMax_nu;

     R0.X=X0_nu;
     R0.Y=Y0_nu;
     R0.Z=Z0_nu;
    };

Vector TargetOne::GetXYZ(double t_)
    {
    double Velocity=Velocity0+Acceleration*t_;
    double S=Velocity0*t_+Acceleration*t_*t_/2.0;
    if (Velocity>=velocityMax) Acceleration=0.0;

    Vector Rtg;
     Rtg.X = R0.X+S*cos(TETA)*cos(PSI);
     Rtg.Y = R0.Y+S*sin(TETA);
     Rtg.Z = R0.Z-S*cos(TETA)*sin(PSI);

    return Rtg;
    };

Vector TargetOne::GetVXYZ(double t_)
    {
    double Velocity=Velocity0+Acceleration*t_;
    if (Velocity>=velocityMax) Acceleration=0.0;

    Vector Vtg;
     Vtg.X = Velocity*cos(TETA)*cos(PSI);
     Vtg.Y = Velocity*sin(TETA);
     Vtg.Z =-Velocity*cos(TETA)*sin(PSI);
    return Vtg;
    };

void TargetOne::NextStep(void)
	{
    Life=false;
    };


