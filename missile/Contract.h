#define	pr1Speed_gX Left[0]
#define	pr1Speed_gY Left[1]
#define	pr1Speed_gZ Left[2]
#define	pr1Point_gX Left[3]
#define	pr1Point_gY Left[4]
#define	pr1Point_gZ Left[5]
#define	pr1omegaX   Left[6]
#define	pr1omegaY   Left[7]
#define	pr1omegaZ   Left[8]
#define	pr1ro_rg    Left[9]
#define	pr1lamda_rg Left[10]
#define	pr1mu_rg    Left[11]
#define	pr1nu_rg    Left[12]

#define	Speed_gX el[0]
#define	Speed_gY el[1]
#define	Speed_gZ el[2]
#define	Point_gX el[3]
#define	Point_gY el[4]
#define	Point_gZ el[5]
#define	omegaX   el[6]
#define	omegaY   el[7]
#define	omegaZ   el[8]
#define	ro_rg    el[9]
#define	lamda_rg el[10]
#define	mu_rg    el[11]
#define	nu_rg    el[12]

// File Contract.h

#include <stdlib.h>
#include <math.h>
//#include <time.h>
#include "array.h"

#include <stdlib.h>
#include <conio.h>

const double Pi       = 3.1415926535898;
const double ToDegree = 57.295779513082;


const unsigned char	Type_Missile = 1;
const unsigned char	Type_Target  = 5;


class Object
{
 public:
        Object() { Life = true; Target = NULL;}

	virtual void NextStep() = 0;
	virtual unsigned char GetType() = 0;
    virtual Vector GetXYZ(double)   = 0;

	bool   GetLife() {return Life;}
	double GetTime() {return Time;}

 protected:

	Object *Target;
	bool   Life;
	double Time;
};


class TargetOne: public Object
{
 public:
    void GetTargetOne(double,double,double,double,double,double,double,double);
	void NextStep();
    Vector GetXYZ (double);
    Vector GetVXYZ(double);
    unsigned char GetType() {return Type_Target;}

protected:
	double TETA;
    double PSI;
	double Acceleration;
    double Velocity0;
    double velocityMax;
    Vector R0;
    double TimeNonAcceleration;
};



class Missile: public Object
{
 public:
       Missile (double ,double ,double ,
				double ,double ,double ,
                double ,double ,double ,
                double ,double ,
				double ,
	 			double ,double ,
				double ,double ,double ,
				double ,double ,double ,
			    double ,double ,double ,
			    double ,int    ,
				double ,double ,double ,
				double ,double ,
                int    ,
                double , double ,
                double , double , double ,
                double ,
                int,
                double,
                double , double , double ,
                double , double , double ,
                double , double ,                double , double , double,
                bool,
                bool,
                double , double , double ,                double , double , double ,                double , double , double ,                double , double , double ,                bool,                int,                double , double , double , double , double , double,                double , double,                double , double,                double , double,                double,                double,                double,                bool,                bool , bool , bool,                double);
	   ~Missile();

	void NextStep();

    Vector GetXYZ(double t_)
    {
    Vector t(t_,0,0);
    return t;
    }

	void Pusk(void)
	{
    	RightPart();
        ControlSS();
        ControlSN();
        NAVIGATION=false;

		while(Life)
        	{
            if (Time==TimeBeginPrint) OutputFile();
	        NextStep();
//            if(Time>44) Step=0.000001;
            }
	}

	unsigned char GetType() {return Type_Missile;}

    double & Getro(y){DensityAir(y);}
    double & Geta(y) {SpeedSound(y);}

 protected:

    FILE *fError;
    FILE *f_Temp;
    /**/     Vector TempPower;
    /**/     FILE *TempPowerX;
    /**/     FILE *TempPowerY;
    /**/     FILE *TempPowerZ;
    //Параметры атмосферы
	double SpeedSound(double);    //Скорость звука
	double DensityAir(double);    //Плотность воздуха

    //Аэродинамические коэффициенты
	double Cx(double, double);
	double Cy(double, double);
	double Cy_delta(double, double);
	double Cz(double, double);
	double Cz_delta(double, double);
	double Mx_wx(double, double);
	double Mx_delta(double, double);
	double Mz_wz(double, double);
	double Mz_alfa(double, double);
	double Mz_delta(double, double);
	double My_wy(double, double);
	double My_betta(double, double);
	double My_delta(double, double);
	double Mxvr(double, double);

	//Коэффициенты при вращающем моменте и силе тяжести
    double Kmvr;
    double Kmg;

	//Массив с аэродинамическими характеристиками вращающего момента
    //осталось от мины
	double amxvr[11][6];

	void Rks4(void);
	void RightPart(void);
	//Функция определяющая условия завершения полета
	void ConditionTermination();
    //Функция восстанавливающая значения унлов тангажа, рысканья и крена
    //по параметрам Родриго-Гамильтона
	void SetAngle(double, double, double, double);
	//Функция вывода величин в текстовые файлы
	void OutputFile();
	//Функция управления выводом величин в текстовые файлы
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
	Vector F;
    Vector fg;
	Vector M;

    //Параметры управления - не импульсная коррекция->

    double CoefficientPitch;
    double CoefficientYaw;
    double CoefficientPitchCr;
    double CoefficientYawCr;    double CoefficientVisibilityFI;    double CoefficientVisibilityHI;
    //углы поворота рулей по соответствующему каналу
	double DeltaPitch;
	double DeltaYaw;
    //обобщенный угол поворота руля для стабилизации по каналу крена, на самом деле
    //данная стабилизация выполняется совместными отклонениями рулевых органов
    //по каналам тангажа и рысканья для аэродинамических органов
	double DeltaRoll;

    //по каналу тангажа
    double K_pitch_SS;
    double Ksi_pitch_SS;

    //по каналу рысканья
    double K_yaw_SS;
    double Ksi_yaw_SS;

    //по каналу крена
    double T_roll_SS;
    double Ksi_roll_SS;

    //функция определения требуемых коэффициентов Kdg и KyKrp по каждому из
    //каналов исходя из параметров текущего состояния ЛА и его положения в
    //пространстве
    void ControlSS(void);
    void ControlSN(void);

    //Ограничитель угла поворота рулей
    void MinMax(double, double&, double);

    //Параметры управляющих и формирующих звеньев СС
    //Канал тангажа
   double LawGuidancePitch;
   double LawSpeedPitch;
	//Канал рысканья
   double LawGuidanceYaw;
   double LawSpeedYaw;
	//Канал крена
   double LawSpeedRoll;
   double LawRoll;
   double KyKrpe;

    //Угловые скорости требуемые для управления
   double GuidancePitch;
   double GuidanceYaw;
   double GuidanceRoll;

    //Параметры исполнительных органов стабилизации по крену
   double Proll;//-суммарная тяга управляющих органов по крену
   double Mroll;//-суммарная момент управляющих органов по крену
   double Wx_development;// модуль угловой скорости при достижении которой
   //начинается наведение по каналам тангажа и рысканья
   double K_AD_development;//коэффициент при управляющем аэродинамическом моменте по крену
   //Параметр разрешающий начало управления по крену и тангажу
   bool NAVIGATION;
   //Параметр определяющий приоритет в коррекции скорости крена перед коррекцией угла крена
   bool OmegaXcorrection;
   //Параметр определяющий текущую суммарную тягу органов коррекции по крену
   double StabRoll;
   //Параметр определяет как будут считаться коэффициенты в каналах наведения
   //false - по текущим характеристикам ЛА, true - по осевой перегрузке
   bool NxControl;
   //Осевая перегрузка
   double Nx;
   //Угол пеленга
   double VisibilityFI;
   double VisibilityHI;
   //Уголовая скорость по углу пеленга
   double AccelerationVisibilityFI;
   double AccelerationVisibilityHI;
   //Управляющие функционалы
   double UFI;
   double UHI;
   //Включение управления по углу пеленга
   bool YesVisibility;
   //Использование управляющих функционалов определенных вручную
   bool NotAuto;
   //Использование управляющих функционалов = 0
   bool Unull;
   //"ослепление" ГСН ЛА
   double RemotenessMax;

    //Параметры управления - не импульсная коррекция-<

    double nui;
    double mui;
	double dzetai;
    double hii;
    double dzetaa;
    double hia;
	double dzetag;
    double hig;

	double Fi;
	double Hi;

    //Переключения на участке сброса обтекателя(перед началом коррекции)->
    void   SavePulseFile();
    bool   Pulse;
    FILE  *fPulse;
    double SwitchMass;
    double SwitchTime;
    double SwitchdTime;
    int    SwitchCorrection;
    void   SwitchCorrectionStart(void);
    Vector SpeedNose;
    Vector AngelSpeedNose;
    Vector DeltaSpeed;
    Vector DeltaAngelSpeed;
    Vector Inew;
    Vector INose;
    //Переключения на участке сброса обтекателя(перед началом коррекции)<-


    //Параметры коррекции->
    bool ControlU;
    double LengthOiX;
    double LengthOiY;
    double LengthOiZ;
    double dzetaiMin;
    double dzetaiMax;
    void   ControlCorrectionFlight(Matrix,Matrix);
    bool   VidTrue;//коррекция по hia, если данный параметр = "истина" (угол в
                   //связанной с.к. (в данном случае индекс "а" не обозначает ско-
                   //ростную с.к.)
                   //коррекция по hii, если данный параметр =  "ложь"  (угол в
                   //измерительной с.к.)
    //Параметры коррекции<-

    ///////////////////////////////////////////////////
    ////Начало параметров корректирующих двигателей////
    int  Quantity;
    double REngine;
    double FiEngine;
    double *HiiEngine;
    Matrix *S;
    Vector *rEngine;
    Vector PowerEngine;
    Vector PowerCorrection;
    Vector NCorrection;
    void   PowerEngineCorrection(void);
    double TawEngine;
    double *TawEndEngine;
    int RepeatEngine; //Количество повторных пусков двигателя
    int TawPuskMinus;
    int TawPuskMinusMax;
    double LawDeg;

    int *DeltaMulti;
    int *DeltaDzetai;
    int *DeltaHii;
    int *DeltaTaw;
    int *DeltaFirst;
    int *DeltaSecond;
    ////Конец параметров корректирующих двигателей/////
    ///////////////////////////////////////////////////

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
	FILE *OutVisibility;

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

	FILE *Outdzetai;
	FILE *Outhii;

	FILE *OutTargetX;
	FILE *OutTargetY;
	FILE *OutTargetZ;

	FILE *OutDpitch;
	FILE *OutDyaw;
	FILE *OutDroll;

	double TimeBeginPrint;
	double TimeEndPrint;
	int    NumTimePrint;
	int    NumPrint;
    int    SwitchStep;
    void   ChangeStep();

    //Движение Ц ->
    Vector Rgt;
    TargetOne TargetONE;
    //Движение Ц <-

 //Аппроксимация сеточных функций
//m - ось абцис (х)
//а - ось ординат (у)

double chislo(char *fname,int i,int k)
//Эта функция требует наличия двух заголовочных файлов:
//#include <stdio.h>
//#include <stdlib.h>
//fname - путь и имя к файлу из которого производится чтение(12 символов)
//i - номер строки файла
//k - номер позиции с которой производится чтение
//действие функции - начиная с позиции i, k производится чтение из файла
//начальные пробелы откидываютя, считываются цифры, '.', '+', '-' до пер-
//вого пpобельного символа, после чего преобразубтся в числовое значение

/*************************************************
Порядок нумерации
	      #1
457897	  #2
	      #3
###########
0123456789
то есть выполнение функции вида приведёт к следующему результату
chislo("name.ext",2,2)=7897.0
**************************************************/
{
//*fd1-указатель на файл данных
FILE *fd1;
char line[256];
int nline=0,j;
char *ch;
double chislo_d;
//Открытие файла данных или выход из программы при отсутствии этого файла
//(открытие файла только для чтения)
if ((fd1=fopen(fname,"r"))==NULL)
		{
		perror(fname);
		return 0.00005;
		}
//Нахождение строки с нужным номером i
while (fgets(line,256,fd1)!=NULL)
		//счётчик строк nline
		{
		nline++;
		//printf("nl=%d\n",nline);
		//getch();
		if (nline==i) break;
		}

//Проверка на несоответстие первого символа пробелу
			if (line[k-1]==' ' || line[k-1]=='*' || line[k-1]=='=')
			for (;line[k]==' ' || line[k]=='*'   || line[k]=='=';k++);

			//printf("\nkkk%d",k);
//Считывание числа в символьном виде с указанной позиции до пробела
//1-ый этап - подсчёт количества символов в символьном представлении
//числа
			for (j=0;line[k]!=' ';k++)
			{
			if(line[k]=='*')break;
			j++;
			}
			//printf("\nssss%s",line);

//2-ой этап - выделение динамической памяти для массива с символами,
//представляющими число
				ch=(char*)malloc(j*sizeof(char));
//повторное использование nline, но в другом контексте
				for (nline=0,k=k-j;nline<j;nline++)
				{
//запись символов в массив
				ch[nline]=line[k];
				k++;
				}
fclose(fd1);
// преобразование числа из символьного представления в вещественное
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
//
//Исключаем считывание типовой аэродинамической таблицы

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

//rez_m	=alur(sda[i-1][0],c3		   ,sda[i][0],c4         ,m);
rez_a	=alur(sda[0][j-1],c1		   ,sda[0][j],c2         ,a);

/*printf ("c1=%f\n",c1);
printf ("c2=%f\n",c2);
printf ("c3=%f\n",c3);
printf ("c4=%f\n",c4);*/

//return (c1+c2+c3+c4)/4.0;
//return rez_m;
return rez_a;

}

//проверочная функция
void main_(double m, double a, double sda[11][6])
{
double la;

int i,j;
for(j=0;j<6;j++)
{
printf("\n");
for(i=0;i<11;i++)
printf("%.3f ",sda[i][j]);
}

la=aerovvod(m,a,sda);

printf ("cx=%f\n",la);

}

};



