//Аппроксимация сеточных функций
//m - ось абцис (х)
//а - ось ординат (у)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Vfm\inout99.h"

const double pi=3.141593;

inline double DegToRad(double Deg)
{return Deg*pi/180;};

inline double RadToDeg(double Rad)
{return Rad*180/pi;};


//
//Исключаем считывание типовой аэродинамической таблицы
//#include "inout99.h"
//

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


//Функция сеточной интерпаляции
double aerovvod (double m, double a, double sda[11][6])
{
RadToDeg(a);

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

DegToRad(a);

return rez_a;
}

//Выключаем проверочную функцию, позволяющую запустить файл в автономном режиме
/*
void main(void)
{
double sda[11][6];
double a;
aerotablica (21,sda);

int i,j;
for(j=0;j<6;j++)
{
printf("\n");
for(i=0;i<11;i++)
printf("%.3f ",sda[i][j]);
}

a=aerovvod(2.3,4.5,sda);

printf ("cx=%f\n",a);

}

*/