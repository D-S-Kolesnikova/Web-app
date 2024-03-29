//----------------------------Array.h (begin)--------------------------
//����������� �������� ����� ���������, �������� ����� 
//��������� � �������� ����� ��������� � ���������
#include <stdio.h>

struct Vector
{
	Vector(double vx=0.0,double vy=0.0,double vz=0.0)
		{X=vx; Y=vy; Z=vz;};
	
	void TestGetVector(double a1,double a2,double a3)
		{X =  a1; Y =  a2; Z =  a3;};

	double GetLength() 
		{return sqrt(X*X + Y*Y + Z*Z);};
	
	double GetPitch()
		{
			double length = GetLength();
			if(length == 0) return 0;
			return asin(Y/length);
		};

	double GetYaw()
		{return -atan2(Z, X);};

	void ShowV(Vector pos)
			{
			printf("\n%f\n%f\n%f\n",pos.X,pos.Y,pos.Z);
			};

   	void fShowV(Vector pos, FILE *fMatrix)
			{
			fprintf(fMatrix,"%f\n%f\n%f\n",pos.X,pos.Y,pos.Z);
			};


	double X;
	double Y;
	double Z;
};

class Matrix
{
protected:
	double m[3][3];

public:

//������� �������� �� ��������� � ���������� ������ �.�.
	void GetMatrix(double tetta, double psi, double gamma)
		{
				m[0][0] =  cos(tetta)*cos(psi);
				m[0][1] = -sin(tetta)*cos(psi)*cos(gamma) + sin(psi)*sin(gamma);
				m[0][2] =  sin(tetta)*cos(psi)*sin(gamma) + sin(psi)*cos(gamma);

				m[1][0] =  sin(tetta);
				m[1][1] =  cos(tetta)*         cos(gamma);
				m[1][2] = -cos(tetta)*         sin(gamma);

				m[2][0] = -cos(tetta)*sin(psi);
				m[2][1] =  sin(tetta)*sin(psi)*cos(gamma) + cos(psi)*sin(gamma);
				m[2][2] = -sin(tetta)*sin(psi)*sin(gamma) + cos(psi)*cos(gamma);
		};

//������� �������� �� ���������� ������ � ���������   �.�.
    void GetMatrix(double r,double l,double mm,double n)
        {
				m[0][0] =  r*r+l*l-mm*mm-n*n;
				m[0][1] =  2*(r*n+l*mm);
				m[0][2] =  2*(-r*mm+l*n);

				m[1][0] =  2*(-r*n+l*mm);
				m[1][1] =  r*r+mm*mm-n*n-l*l;
				m[1][2] =  2*(r*l+n*mm);

				m[2][0] =  2*(r*mm+n*l);
				m[2][1] =  2*(-r*l+n*mm);
				m[2][2] =  r*r+n*n-l*l-mm*mm;

        };

//������� �������� �� ��������� � ������������� �.�.
	void GetMatrix(double nu, double mu)
		{
				m[0][0] =  cos(nu)*cos(mu);
				m[0][1] =  cos(nu)*sin(mu);
				m[0][2] = -sin(nu);

				m[1][0] =         -sin(mu);
				m[1][1] =          cos(mu);
				m[1][2] =              0.0;

				m[2][0] =  sin(nu)*cos(mu);
				m[2][1] =  sin(nu)*sin(mu);
				m[2][2] =  cos(nu);
		};

	void TestGetMatrix(double a1,double a2,double a3,
					   double a4,double a5,double a6,
					   double a7,double a8,double a9)
		{
				m[0][0] =  a1;
				m[0][1] =  a2;
				m[0][2] =  a3;

				m[1][0] =  a4;
				m[1][1] =  a5;
				m[1][2] =  a6;

				m[2][0] =  a7;
				m[2][1] =  a8;
				m[2][2] =  a9;
		};

	void InitNull()
		{
				for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++) m[i][j] = 0.0;
		};


	Matrix& operator = (Matrix& pos)
			{
				for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++) m[i][j] = pos.m[i][j];
				return *this;
			};


	friend Matrix& operator ~ (Matrix& pos)
			{
				double memory;
				for(int i = 0; i < 2; i++)
				for(int j = i + 1; j < 3; j++)
					{
					memory      = pos.m[i][j];
					pos.m[i][j] = pos.m[j][i];
					pos.m[j][i] = memory;
					}
				return pos;
			};

    friend Matrix  operator + (Matrix pos1, Matrix pos2)
			{
				Matrix pos_new;
				for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++)
					pos_new.m[i][j] = pos1.m[i][j] + pos2.m[i][j];
				return pos_new;
			};

    friend Vector  operator + (Vector pos1, Vector pos2)
			{
				Vector pos_new;
				pos_new.X = pos1.X + pos2.X;
				pos_new.Y = pos1.Y + pos2.Y;
				pos_new.Z = pos1.Z + pos2.Z;
				return pos_new;
			};

    friend Vector  operator - (Vector pos1, Vector pos2)
			{
				Vector pos_new;
				pos_new.X = pos1.X - pos2.X;
				pos_new.Y = pos1.Y - pos2.Y;
				pos_new.Z = pos1.Z - pos2.Z;
				return pos_new;
			};

    friend Vector  operator * (Vector pos1, Vector pos2)
			{
				Vector pos_new;
				pos_new.X = pos1.X * pos2.X;
				pos_new.Y = pos1.Y * pos2.Y;
				pos_new.Z = pos1.Z * pos2.Z;
				return pos_new;
			};

    friend Vector  operator / (Vector pos1, Vector pos2)
			{
				Vector pos_new;
				pos_new.X = pos1.X / pos2.X;
				pos_new.Y = pos1.Y / pos2.Y;
				pos_new.Z = pos1.Z / pos2.Z;
				return pos_new;
			};

	friend Matrix  operator - (Matrix pos1, Matrix pos2)
			{
				Matrix pos_new;
				for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++)
					pos_new.m[i][j] = pos1.m[i][j] - pos2.m[i][j];
				return pos_new;
			};

	friend Matrix  operator * (Matrix pos1, Matrix pos2)
			{
				Matrix pos_new;
				pos_new.InitNull();
				for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++)
	   			for(int k = 0; k < 3; k++)
					pos_new.m[i][j] += pos1.m[i][k]*pos2.m[k][j];
				return pos_new;
			};

	friend Vector  operator * (Vector v, Matrix pos)
			{
				Vector v_new;
				v_new.X = v.X*pos.m[0][0] + v.Y*pos.m[1][0] + v.Z*pos.m[2][0];
				v_new.Y = v.X*pos.m[0][1] + v.Y*pos.m[1][1] + v.Z*pos.m[2][1];
				v_new.Z = v.X*pos.m[0][2] + v.Y*pos.m[1][2] + v.Z*pos.m[2][2];
				return v_new;
			};

	friend Vector  operator * (Matrix pos, Vector v)
			{
				Vector v_new;
				v_new.X = v.X*pos.m[0][0] + v.Y*pos.m[0][1] + v.Z*pos.m[0][2];
				v_new.Y = v.X*pos.m[1][0] + v.Y*pos.m[1][1] + v.Z*pos.m[1][2];
				v_new.Z = v.X*pos.m[2][0] + v.Y*pos.m[2][1] + v.Z*pos.m[2][2];
				return v_new;
			};

	friend Matrix  operator * (double number, Matrix pos)
			{
				Matrix pos_new;
				for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++) pos_new.m[i][j] = pos.m[i][j]*number;
				return pos_new;
			};

	friend Vector  operator * (double number, Vector pos)
			{
				Vector pos_new;
				pos_new.X=pos.X*number;
				pos_new.Y=pos.Y*number;
				pos_new.Z=pos.Z*number;
				return pos_new;
			};

	friend Matrix  operator * (Matrix pos, double number)
			{
				Matrix pos_new;
				for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++) pos_new.m[i][j] = pos.m[i][j]*number;
				return pos_new;
			};

	friend Vector  operator * (Vector pos, double number)
			{
				Vector pos_new;
				pos_new.X=pos.X*number;
				pos_new.Y=pos.Y*number;
				pos_new.Z=pos.Z*number;
				return pos_new;
			};

	friend Matrix  operator / (Matrix pos, double number)
			{
				Matrix pos_new;
				for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++) pos_new.m[i][j] = pos.m[i][j]/number;
				return pos_new;
			};

	friend Vector  operator / (Vector pos, double number)
			{
				Vector pos_new;
				pos_new.X= pos.X/number;
				pos_new.Y= pos.Y/number;
				pos_new.Z= pos.Z/number;
				return pos_new;
			};

  //��������� ��������� (������������ ��� [a,b] ��� ��� a x b)
    friend Vector  operator % (Vector a, Vector b)
			{
				Vector pos_new;
				pos_new.X= a.Y*b.Z - a.Z*b.Y;
				pos_new.Y= a.Z*b.X - a.X*b.Z;
				pos_new.Z= a.X*b.Y - a.Y*b.X;
				return pos_new;
			};

	void ShowM(Matrix pos)
			{
				for(int i = 0; i < 3; i++)
				{
					if(i!=0) printf("\n");
					for(int j = 0; j < 3; j++)
					printf("%f\t",pos.m[i][j]);
				};
				printf("\n");
			};

	void fShowM(Matrix pos, FILE *fMatrix)
			{
				for(int i = 0; i < 3; i++)
				{
					if(i!=0) fprintf(fMatrix,"\n");
					for(int j = 0; j < 3; j++)
					fprintf(fMatrix,"%f\t",pos.m[i][j]);
				};
				fprintf(fMatrix,"\n");
			};
};
//----------------------------Array.h (end)--------------------------