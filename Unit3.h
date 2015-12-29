//---------------------------------------------------------------------------

#ifndef MATRIXH
#define MATRIXH
//---------------------------------------------------------------------------
class Matrix
{
   int col, ren;
   float **Mat;

public:
   Matrix();
   Matrix(Matrix &);
   Matrix::Matrix(int nr,int nc, float valor);
   Matrix::Matrix(double nr,double nc, float m[][3]);
   ~Matrix();
   void SETM(int R, int C, float val){Mat[R][C]=val;}
   float GETM(int R, int C){return Mat[R][C];}
   int numCol(){return col;}
   int numRen(){return ren;}
   void Inicializa(int, int);
   Matrix &operator *=(Matrix &mat2);
   // A G R E G A R
   Matrix &operator*(const Matrix &m1);

   Matrix operator*(float);//Multiplicar por un escalar
   //Matrix & operator =(Matrix &mat2);
   Matrix &operator=(Matrix &m);
   Matrix & asignar(Matrix);
   Matrix & Identidad();

   //transformaciones
   Matrix & traslacion(Matrix,Matrix,int Tx ,int Ty);

   Matrix & Esc(Matrix, Matrix, int Tx, int Ty, int Pfx, int Pfy);

   Matrix & Rotar(Matrix, Matrix, int teta);

   Matrix & Rotardos(Matrix, Matrix, int teta,int pfx, int pfy);

   Matrix & ReflexionX(Matrix, Matrix);
   Matrix & ReflexionY(Matrix, Matrix);
   Matrix & ReflexionO(Matrix, Matrix);

   Matrix & ReflexionYX(Matrix, Matrix);
   Matrix & ReflexionYMX(Matrix, Matrix);

};
#endif

