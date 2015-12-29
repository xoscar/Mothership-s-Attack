#pragma hdrstop
#include "Unit3.h"
#include <math.h>
#include <assert.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

Matrix::Matrix()
{
   Mat = NULL;
}

/*
Matriz<T>::Matriz(const Matriz<T> &m)
{
  n_ren = m.n_ren;
  n_col = m.n_col;
  mat = new T*[n_ren];
  assert(mat);
  for(int i = 0; i < n_ren; i++)
  {
     mat[i] = new T[n_col];
     assert(mat[i]);
  }
  for( int i =0; i < n_ren; i++)
    for(int j = 0; j < n_col; j++)
        mat[i][j] = m.mat[i][j];
}
*/
Matrix::Matrix(Matrix &m)
{
   ren=m.numRen();
   col=m.numCol();
   Mat =new float*[ren];
   for(int i = 0; i < ren; i++)
  {
     Mat[i] = new float[col];
     assert(Mat[i]);
  }
   for(int i=0; i<ren; i++)
      for( int j=0; j<col; j++)
         Mat[i][j]=m.GETM(i,j);
}

Matrix::Matrix(int nr,int nc, float valor)
{
  ren = nr;
  col = nc;
  Mat = new float*[ren];
  assert(Mat);
  for(int i = 0; i < ren; i++)
  {
      Mat[i] = new float[col];
      assert(Mat[i]);
  }

  for(int i = 0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = valor;
}



Matrix::Matrix(double nr,double nc, float m[][3])
{
  ren = nr;
  col = nc;
  Mat = new float*[ren];
  assert(Mat);
  for(int i = 0; i < ren; i++)
  {
      Mat[i] = new float[col];
      assert(Mat[i]);
  }
  for(int i = 0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = m[i][j];
}

void Matrix::Inicializa(int R, int C)
{
   col=C;
   ren=R;
   Mat=new float *[ren];
   assert(Mat);

   for(int i=0; i<ren; i++)
   {
      Mat[i]=new float[col];
      assert(Mat[i]);
   }

   for(int i=0; i<ren; i++)
      for(int j=0; j<col; j++)
         Mat[i][j]=0;
}

Matrix &Matrix::operator*=(Matrix &mat2)
{
   Matrix aux;
   aux.Inicializa(ren, mat2.numCol());


   for(int i=0; i<ren; i++)
   {
      for(int j=0; j<mat2.numCol(); j++)
      {
         float suma=0;
        // Mat[i][j]=0;
         for(int k=0; k<col; k++)
         {
           suma+=floor(Mat[i][k]*mat2.GETM(k,j)+0.5);
           aux.SETM(i,j,suma);
         }
         //aux.SETM(i,j,suma);
      }
   }
   asignar(aux);
   return *this;
}

//A G R E G A R

Matrix &Matrix::operator*(const Matrix &m1)
{
  //assert((this->ren == m1.ren) && (col == m1.col));
   Matrix *result = new Matrix(ren,col,0);
   assert(result);
   for(int i=0; i < ren; i++)
     for(int j = 0; j < col; j++)
       for(int k = 0; k < ren; k++)
            result->Mat[i][j]= result->Mat[i][j] + Mat[i][k] * m1.Mat[k][j];
                                                        //j
   return *result;
}


Matrix Matrix::operator*(float val)
{
   Matrix temp;
   temp.Inicializa(ren,col);
   for(int i=0; i<ren;i++)
      for(int j=0; j<col; j++)
         temp.SETM(i,j,Mat[i][j]* val);
   return temp;
}

/*
Matrix &Matrix::operator=(Matrix &m)
{
//eliminar el tamaño de la matriz destino
  for(int i= 0; i<ren;i++ )
     //Se borran los renglones de la matriz
       delete [] Mat[i];
  //Se borra el arreglo de punteros
  delete []Mat;
//Asignar los nuevos datos de la matriz que llego
  ren=m.numRen();
  col = m.numCol();
  Mat = new float*[ren];
  assert(Mat);
  for(int i = 0; i < ren; i++)
  {
     Mat[i] = new float[col];
     assert(Mat[i]);
  }
  for( int i =0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = m.Mat[i][j];

  return *this;
}*/

Matrix &Matrix::operator =(Matrix &mat2)
{
    ren=mat2.numRen();
    col=mat2.numCol();

   Mat =new float*[ren];
   for(int i = 0; i < ren; i++)
  {
     Mat[i] = new float[col];
     assert(Mat[i]);
  }
    for(int i=0;i<ren;i++)
       for(int j=0;j<col;j++)
          Mat[i][j]=mat2.GETM(i,j);
    return *this;
}

Matrix &Matrix::asignar(Matrix m)
{
   for(int i=0;i<m.numRen();i++)
       for(int j=0;j<m.numCol();j++)
                Mat[i][j]=m.GETM(i,j);
   return *this;
}

Matrix::~Matrix()
{
  //Se libera la memoria
  for(int i= 0; i<ren;i++ )
     //Se borran los renglones de la matriz
       delete [] Mat[i];
  //Se borra el arreglo de punteros
  delete []Mat;

}

Matrix &Matrix::Identidad()
{
  for(int i=0; i < ren; i++)
     for( int j = 0; j < col; j++)
      if( i == j)
         Mat[i][i]= 1;
      else
         Mat[i][j]= 0;
  return *this;
}

//---------------TRANSFORMACIONES-----------------------------
Matrix & Matrix::traslacion(Matrix f,Matrix id,int tx,int ty)
{
   id.Identidad();
   id.SETM(2,0,tx);
   id.SETM(2,1,ty);
   f*=id;
   this->asignar(f);
   return *this;
}

Matrix & Matrix::Esc(Matrix f, Matrix id, int Tx, int Ty, int SX, int SY)
{
        id.Identidad();
        id.SETM(0,0,SX);
        id.SETM(1,1,SY);
        id.SETM(2,0,Tx*(-SX+1.0));
        id.SETM(2,1,Ty*(-SY+1.0));

        f*= id;

        this->asignar(f);

        return *this;
}

Matrix & Matrix::Rotar(Matrix f, Matrix id, int teta)
{
        id.Identidad();

        id.SETM(0,0, cos(teta*(M_PI/180.0))+.5);
        id.SETM(1,0, -sin(teta*(M_PI/180.0))+.5);
        id.SETM(0,1, sin(teta*(M_PI/180.0))+.5);
        id.SETM(1,1, cos(teta*(M_PI/180.0))+.5);

        f*=id;

        this->asignar(f);

        return *this;
}


Matrix & Matrix::Rotardos(Matrix f, Matrix id, int teta,int pfx, int pfy)
{
        id.Identidad();
        id.SETM(0,0, cos(teta*(M_PI/180.0)));
        id.SETM(1,0, -sin(teta*(M_PI/180.0)));
        id.SETM(0,1, sin(teta*(M_PI/180.0)));
        id.SETM(1,1, cos(teta*(M_PI/180.0)));

        id.SETM(2,0, -pfx*(cos(teta*M_PI/180.0)-1)+ pfy*sin(teta*M_PI/180.0));
        id.SETM(2,1, -pfy*(cos(teta*M_PI/180.0)-1)-pfx*sin(teta*M_PI/180.0));

        f*=id;

        this->asignar(f);

        return *this;
}


Matrix & Matrix::ReflexionX(Matrix f, Matrix id)
{
        id.Identidad();
        id.SETM(1,1,-1);

        f*=id;

        this->asignar(f);

        return *this;
}

Matrix & Matrix::ReflexionY(Matrix f, Matrix id)
{
        id.Identidad();
        id.SETM(0,0,-1);

        f*=id;

        this->asignar(f);

        return *this;
}

Matrix & Matrix::ReflexionO(Matrix f, Matrix id)
{
        id.Identidad();
        id.SETM(1,1,-1);
        id.SETM(0,0,-1);

        f*=id;

        this->asignar(f);

        return *this;
}

Matrix & Matrix::ReflexionYX(Matrix f, Matrix id)
{
        id.Identidad();
        id.SETM(0,1,1);
        id.SETM(0,0,0);
        id.SETM(1,1,0);
        id.SETM(1,0,1);

        f*=id;

        this->asignar(f);

        return *this;
}

Matrix & Matrix::ReflexionYMX(Matrix f, Matrix id)
{
        id.Identidad();
        id.SETM(0,1,-1);
        id.SETM(0,0,0);
        id.SETM(1,1,0);
        id.SETM(1,0,-1);

        f*=id;

        this->asignar(f);

        return *this;
}

