//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit3.h"
#include "Unit2.h"
#include "Main.h"
#include <Math.h>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
float XPV,YPV;

Matrix m1(10,3,1);
Matrix m1star(12,3,1);
int numM = 10;
int vM1 = 100;
int dano = 5;
bool m1finish = false;
bool m1finishOvni = false;
bool m1quitStar = false;


Matrix ovni(7,3,1);
Matrix star(12,3,1);
int vOvni = 50;
int dispOvniint[40][2];
int dispOvnist = 40;
int dispAOvni = 0;
bool finish = false;
bool finishOvni = false;
bool quitStar = false;
bool flag = false;

Matrix ovni2(7,3,1);
Matrix star2(12,3,1);
int vOvni2 = 50;
int dispOvniint2[40][2];
int dispOvnist2 = 40;
int dispAOvni2 = 0;
bool finish2 = false;
bool finishOvni2 = false;
bool quitStar2 = false;
bool flag2 = true;

bool primera = false;

AnsiString nivel = "";

int ovnisdown = 0;



int disaux = 0;
int ndisp = 10;
Matrix m2(3,3,1);

bool playing = false;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{

        MP->FileName = "intro.wav";
        MP->Open();
        MP->Play();

        MP2->FileName = "exp.wav";
        MP2->Open();

        m1.SETM(0,0,0);
        m1.SETM(0,1,0);
        m1.SETM(1,0,10);
        m1.SETM(1,1,20);
        m1.SETM(2,0,20);
        m1.SETM(2,1,10);
        m1.SETM(3,0,30);
        m1.SETM(3,1,10);
        m1.SETM(4,0,40);
        m1.SETM(4,1,50);
        m1.SETM(5,0,50);
        m1.SETM(5,1,10);
        m1.SETM(6,0,60);
        m1.SETM(6,1,10);
        m1.SETM(7,0,70);
        m1.SETM(7,1,20);
        m1.SETM(8,0,80);
        m1.SETM(8,1,0);
        m1.SETM(9,0,40);
        m1.SETM(9,1,-40);

        m1.traslacion(m1,m2,0,-300);



        ovni.SETM(0,0,-100);
        ovni.SETM(0,1,100);
        ovni.SETM(1,0,-90);
        ovni.SETM(1,1,120);
        ovni.SETM(2,0,-70);
        ovni.SETM(2,1,140);
        ovni.SETM(3,0,-30);
        ovni.SETM(3,1,140);
        ovni.SETM(4,0,-10);
        ovni.SETM(4,1,120);
        ovni.SETM(5,0,0);
        ovni.SETM(5,1,100);
        ovni.SETM(6,0,-50);
        ovni.SETM(6,1,80);


        float cx = eqCentro(ovni);
        float cy = yeCentro(ovni);

        ovni.Esc(ovni,m2.Identidad(),cx,cy,3,3);
        ovni.traslacion(ovni,m2,0,300);

        ovni2.SETM(0,0,-100);
        ovni2.SETM(0,1,100);
        ovni2.SETM(1,0,-90);
        ovni2.SETM(1,1,120);
        ovni2.SETM(2,0,-70);
        ovni2.SETM(2,1,140);
        ovni2.SETM(3,0,-30);
        ovni2.SETM(3,1,140);
        ovni2.SETM(4,0,-10);
        ovni2.SETM(4,1,120);
        ovni2.SETM(5,0,0);
        ovni2.SETM(5,1,100);
        ovni2.SETM(6,0,-50);
        ovni2.SETM(6,1,80);

        cx = eqCentro(ovni2);
        cy = yeCentro(ovni2);

        ovni2.Esc(ovni2,m2.Identidad(),cx,cy,3,3);
        ovni2.traslacion(ovni2,m2,0,100);

        for(int i = 0; i < dispOvnist; i++)
                dispOvniint[i][0] = 0;

        for(int i = 0; i < dispOvnist2; i++)
                dispOvniint2[i][0] = 0;

        L=(ClientWidth) /2;
        M=ClientHeight/2;
        angulo = 90;

        /*
        disparos[0].Inicializa(4,3);
        disparos[1].Inicializa(4,3);
        disparos[2].Inicializa(4,3);
        disparos[3].Inicializa(4,3);
        disparos[4].Inicializa(4,3);*/


        disactuales = 0;

        for(int i = 0; i < ndisp; i++)
        {
                dispint[i][0] = 0;
                dispint[i][1] = 90;
        }


        for( int  i = 0; i < 5; i++)
                for( int j = 0; j < 4; j++)
                        for( int k = 0; k < 3; k++)
                                disp[i][j][k] = 1;


        for( int i = 0; i < 3; i++)
                for( int  j= 0; j < 3; j++)
                        if( i == j)
                                id[i][j] = 1;
                        else
                                id[i][j] = 0;

        u.ventana(0,0,ClientWidth,ClientHeight);
        u.puerto(0,0,(ClientWidth)/2,ClientHeight/2);

}
//---------------------------------------------------------------------------
void  TForm1::mostrar(Matrix &m, int n)
{
        u.ventana(0,0,ClientWidth,ClientHeight);
        u.puerto(0,0,(ClientWidth)/2,ClientHeight/2);

        Canvas->Pen->Color=clBlue;
        Canvas->Pen->Width=1;

        int xx1,yy1,xx2,yy2;



        u.mapeo(m.GETM(0,0),m.GETM(0,1),xx1,yy1,L,M);
        Canvas->MoveTo(xx1,yy1);

        for( int  i= 0; i < n; i++)
        {
                u.mapeo(m.GETM(i,0),m.GETM(i,1),xx2,yy2,L,M);
                Canvas->LineTo(xx2,yy2);
        }
        Canvas->LineTo(xx1,yy1);
}

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 27)
        {
                PanelQuit->Visible = true;
        }

        if( Key == VK_DOWN && !m1finish)
        {
                float tx = incEq(angulo);
                float ty = incYe(angulo);

                m1.traslacion(m1,m2,tx*-10,ty*-20);
                Repaint();
        }
        if( Key == VK_UP && !m1finish)
        {
                float tx = incEq(angulo);
                float ty = incYe(angulo);

                m1.traslacion(m1,m2,tx*10,ty*20);
                Repaint();
        }
         if( Key == VK_LEFT && !m1finish)
        {
                m1.traslacion(m1,m2,-20,0);
                Repaint();

        }
        if( Key == VK_RIGHT && !m1finish)
        {
                m1.traslacion(m1,m2,20,0);
                Repaint();
        }
        if(Key == VK_SPACE && disaux < ndisp && !m1finish)
        {

                creardisp1(disaux, (float)m1.GETM(4,0),(float)m1.GETM(4,1));
                dispint[disaux][0] = 1;
                dispint[disaux][1] = angulo;
                Repaint();
                disaux++;
                t1->Enabled = true;
        }
}
//---------------------------------------------------------------------------

float TForm1::eqCentro(Matrix &m)
{
        float suma = 0;
        for(int i = 0; i < m.numRen();i++)
        {
                suma += m.GETM(i,0);
        }
        return suma/m.numRen();
}

float TForm1::yeCentro(Matrix &m)
{
        float suma = 0;
        for(int i = 0; i < m.numRen();i++)
        {
                suma += m.GETM(i,1);
        }
        return suma/m.numRen();
}

float TForm1::incEq(int ang)
{
        float aux = cos(ang*(M_PI/180.0));
        return aux;
}

float TForm1::incYe(int ang)
{
        float aux = sin(ang*(M_PI/180.0));
        return aux;
}


void __fastcall TForm1::FormPaint(TObject *Sender)
{
        if(primera){
        general->Enabled = true;
        float cx = 0.0;
        float cy = 0.0;
        int xx1,yy1;

        if(!finishOvni && !m1quitStar && ovnisdown < 2)
        {
                mostrar(ovni,7);

                cx = eqCentro(ovni);
                cy = yeCentro(ovni);
                u.mapeo(cx,cy,xx1,yy1,L,M);
                Canvas->Brush->Color = clRed;
                Canvas->FloodFill(xx1,yy1,clBlue,fsBorder);
        }
        else
        {
                if(!quitStar)
                {
                        if(!m1quitStar){
                        mostrar(star,12);
                        cx = eqCentro(star);
                        cy = yeCentro(star);
                        xx1,yy1;
                        u.mapeo(cx,cy,xx1,yy1,L,M);
                        Canvas->Brush->Color = clYellow;
                        Canvas->FloodFill(xx1,yy1,clBlue,fsBorder); }
                }
        }

        if(!finishOvni2 && !m1quitStar && ovnisdown < 2)
        {
                mostrar(ovni2,7);

                cx = eqCentro(ovni2);
                cy = yeCentro(ovni2);
                u.mapeo(cx,cy,xx1,yy1,L,M);
                Canvas->Brush->Color = clBlue;
                Canvas->FloodFill(xx1,yy1,clBlue,fsBorder);
        }
        else
        {
                if(!quitStar2)
                {
                         if(!m1quitStar){
                        mostrar(star2,12);
                        cx = eqCentro(star2);
                        cy = yeCentro(star2);
                        u.mapeo(cx,cy,xx1,yy1,L,M);
                        Canvas->Brush->Color = clYellow;
                        Canvas->FloodFill(xx1,yy1,clBlue,fsBorder);}
                }
        }

        if(!m1finishOvni && ovnisdown <2)
        {
                mostrar(m1,10);
                cx = eqCentro(m1);
                cy = yeCentro(m1);

                u.mapeo(cx,cy,xx1,yy1,L,M);
                Canvas->Brush->Color = clWhite;
                Canvas->FloodFill(xx1,yy1,clBlue,fsBorder);
        }
        else
        {
                if(!m1quitStar)
                 {
                        mostrar(m1star,12);
                        cx = eqCentro(m1star);
                        cy = yeCentro(m1star);
                        u.mapeo(cx,cy,xx1,yy1,L,M);
                        Canvas->Brush->Color = clYellow;
                        Canvas->FloodFill(xx1,yy1,clBlue,fsBorder);
                }
        }



        Canvas->Brush->Color = clRed;

        for( int i = 0; i < ndisp; i++)
                if(dispint[i][0] == 1)
                {
                        mostrar1(disp, 4,i);



                        float a = disp[i][2][0];
                        float b = disp[i][2][1];


                        int xx1, yy1;
                        u.mapeo(a,b,xx1,yy1,L,M);

                        Canvas->Brush->Color = clGreen;
                        Canvas->FloodFill(xx1-1,yy1+1,clBlue,fsBorder);

                        if(Canvas->Pixels[xx1][yy1-2] == clRed  && !finish)
                        {

                                if( vOvni >0)
                                        vOvni -= 10;
                                else
                                {
                                        t1Ovni->Enabled = false;
                                        t1OvniMov->Enabled = false;
                                        t1giro->Enabled = true;
                                        finish = true;
                                        ovni.Esc(ovni,m2,eqCentro(ovni),yeCentro(ovni),2,2);

                                        for( int i = 0; i < dispOvnist; i++)
                                               dispOvniint[i][0] =0;
                                }

                                dispint[i][0] = 0;

                        }

                        if(Canvas->Pixels[xx1][yy1-2] == clBlue  && !finish2)
                        {

                                if( vOvni2 >0)
                                        vOvni2 -= 10;
                                else
                                {
                                        t1Ovni2->Enabled = false;
                                        t1OvniMov2->Enabled = false;
                                        t1giro2->Enabled = true;
                                        finish2 = true;
                                        ovni2.Esc(ovni2,m2,eqCentro(ovni2),yeCentro(ovni2),2,2);

                                        for( int i = 0; i < dispOvnist2; i++)
                                               dispOvniint2[i][0] =0;

                                        
                                }

                                dispint[i][0] = 0;
                        }
                }

        for( int i = 0; i < dispOvnist; i++)
                if(dispOvniint[i][0] == 1)
                {
                        mostrar1(dispOvni, 4,i);

                        float a = dispOvni[i][1][0];
                        float b = dispOvni[i][1][1];


                        int xx1, yy1;
                        u.mapeo(a,b,xx1,yy1,L,M);
                        Canvas->Brush->Color = clRed;
                        Canvas->FloodFill(xx1-1,yy1-1,clBlue,fsBorder);

                         if((Canvas->Pixels[xx1][yy1+1] == clWhite
                         || Canvas->Pixels[xx1+2][yy1] == clWhite) && !m1finish)
                        {
                                if( vM1 >0)
                                        vM1 -= dano;
                                else
                                {
                                        t1->Enabled = false;
                                        m1giro->Enabled = true;
                                        m1finish = true;
                                        m1.Esc(m1,m2,eqCentro(m1),yeCentro(m1),2,2);

                                        for( int i = 0; i < numM; i++)
                                               dispint[i][0] =0;
                                }
                                dispOvniint[i][0] = 0;
                        }
                }

        for( int i = 0; i < dispOvnist2; i++)
                if(dispOvniint2[i][0] == 1)
                {
                        mostrar1(dispOvni2, 4,i);

                        float a = dispOvni2[i][1][0];
                        float b = dispOvni2[i][1][1];


                        int xx1, yy1;
                        u.mapeo(a,b,xx1,yy1,L,M);
                        Canvas->Brush->Color = clRed;
                        Canvas->FloodFill(xx1-1,yy1-1,clBlue,fsBorder);

                         if((Canvas->Pixels[xx1][yy1+1] == clWhite
                         || Canvas->Pixels[xx1+2][yy1] == clWhite) && !m1finish)
                        {
                                if( vM1 >0)
                                        vM1 -= dano;
                                else
                                {
                                        t1->Enabled = false;
                                        m1giro->Enabled = true;
                                        m1finish = true;

                                        m1.Esc(m1,m2,eqCentro(m1),yeCentro(m1),2,2);

                                        for(int i = 0; i < numM; i++)
                                               dispint[i][0] =0;
                                }
                             dispOvniint2[i][0] = 0;
                        }
                }

        if(!m1quitStar)
        {
                Canvas->Brush->Color = clRed;
                Canvas->TextOutA(50,530,"Red ship healt = "+ (AnsiString)vOvni);
                Canvas->TextOutA(250,530,"Blue ship healt = "+ (AnsiString)vOvni2);
                Canvas->TextOutA(500,530,"Level: "+ nivel);
                Canvas->TextOutA(700,530,"Player's healt = "+(AnsiString)vM1);
        }
        }
}
//---------------------------------------------------------------------------

void  TForm1::creardisp1(int i, float x, float y)
{
        disp[i][0][0] = x;
        disp[i][0][1] = y;
        disp[i][1][0] = x+10.0;
        disp[i][1][1] = y;
        disp[i][2][0] = x+10.0;
        disp[i][2][1] = y+20.0;
        disp[i][3][0] = x;
        disp[i][3][1] = y+20.0;

        disp[i][0][2] = 1;
        disp[i][1][2] = 1;
        disp[i][2][2] = 1;
        disp[i][3][2] = 1;

}
void __fastcall TForm1::t1Timer(TObject *Sender)
{
         for( int i = 0; i < ndisp; i++)
                if(dispint[i][0] == 1)
                {
                        float tx = incEq(dispint[i][1]);
                        float ty = incYe(dispint[i][1]);
                        transdisp(disp, i,4,3,id,tx,ty);

                        //int xx1,yy1;
                        //u.mapeo(a,b,xx1,yy1,L,M);

                        if( disp[i][0][0] >= ClientWidth*2
                         || disp[i][0][1] >= ClientHeight*2)
                                dispint[i][0] = 0;

                }
         if(disaux == 9)
         {
                disaux = 0;
         }
}
//---------------------------------------------------------------------------

void TForm1::transdisp(float disp[][4][3], int  i,int ren,int col, float id[3][3], float sx, float sy)
{
   float aux[4][3];

   id[2][0] = sx*20;
   id[2][1]= sy*20;
   for( int j = 0; j < 4; j++)
        for( int k = 0; k < 3; k++)
                aux[j][k] = disp[i][j][k];

   for(int h=0; h<ren; h++)
   {
      for(int j=0; j<3; j++)
      {
         float suma=0;
        // Mat[i][j]=0;
         for(int k=0; k<col; k++)
         {
           suma+=floor(disp[i][h][k]*id[k][j]+.5);
           aux[h][j] = suma;
         }
      }
   }

   for( int h = 0; h < ren;h++)
        for(int j = 0; j < col; j++)
                disp[i][h][j] = aux[h][j];
}

void TForm1::mostrar1(float disp[][4][3], int n, int i)
{
        u.ventana(0,0,ClientWidth,ClientHeight);
        u.puerto(0,0,(ClientWidth)/2,ClientHeight/2);

        Canvas->Pen->Color=clBlue;
        Canvas->Pen->Width=1;

        int xx1,yy1,xx2,yy2;



        u.mapeo(disp[i][0][0],disp[i][0][1],xx1,yy1,L,M);
        Canvas->MoveTo(xx1,yy1);

        for( int  j= 0; j < n; j++)
        {
                u.mapeo(disp[i][j][0],disp[i][j][1],xx2,yy2,L,M);
                Canvas->LineTo(xx2,yy2);
        }
        Canvas->LineTo(xx1,yy1);
}
void __fastcall TForm1::t1OvniTimer(TObject *Sender)
{

        if(dispAOvni < dispOvnist-3)
        {
                dispOvniint[dispAOvni][0] = 1;
                dispOvniint[dispAOvni][1] =225;
                creardispOvni(dispOvni,dispAOvni++, ovni.GETM(0,0),ovni.GETM(0,1));
                dispOvniint[dispAOvni][0] = 1;
                dispOvniint[dispAOvni][1] = 270;
                creardispOvni(dispOvni,dispAOvni++, ovni.GETM(6,0), ovni.GETM(6,1));
                dispOvniint[dispAOvni][0] = 1;
                dispOvniint[dispAOvni][1] = 315;
                creardispOvni(dispOvni, dispAOvni++,ovni.GETM(5,0),ovni.GETM(5,1));
        }
     

        if(dispAOvni >= dispOvnist-3)
        {
                dispAOvni = 0;
        }


}
//---------------------------------------------------------------------------

void  TForm1::creardispOvni(float dispOvni[][4][3], int i, float x, float y)
{
        dispOvni[i][0][0] = x;
        dispOvni[i][0][1] = y;
        dispOvni[i][1][0] = x+10.0;
        dispOvni[i][1][1] = y;
        dispOvni[i][2][0] = x+10.0;
        dispOvni[i][2][1] = y+20.0;
        dispOvni[i][3][0] = x;
        dispOvni[i][3][1] = y+20.0;

        dispOvni[i][0][2] = 1;
        dispOvni[i][1][2] = 1;
        dispOvni[i][2][2] = 1;
        dispOvni[i][3][2] = 1;

}

void __fastcall TForm1::t1OvniMovTimer(TObject *Sender)
{
        if(ovni.GETM(5,0) <= ClientWidth && !flag)
                ovni.traslacion(ovni,m2,100,0);
        else
                if( ovni.GETM(5,0) >= ClientWidth)
                        flag = true;
        if( ovni.GETM(0,0) >= -ClientWidth && flag)
                ovni.traslacion(ovni,m2,-100,0);
        else
                if( ovni.GETM(0,0) <= 0)
                        flag = false;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::t1giroTimer(TObject *Sender)
{
        static int i= 0;
        ovni.Rotardos(ovni,m2,60,eqCentro(ovni),yeCentro(ovni));
        i++;
        if( i == 10)
        {
               t1giro->Enabled = false;
               float xi = eqCentro(ovni);
               float yi = yeCentro(ovni);

               star.SETM(0,0,xi);
               star.SETM(0,1,yi);
               star.SETM(1,0,xi+=15.0);
               star.SETM(1,1,yi+=5.0);
               star.SETM(2,0,xi-=15.0);
               star.SETM(2,1,yi+=5.0);
               star.SETM(3,0,xi+=15.0);
               star.SETM(3,1,yi+=5.0);
               star.SETM(4,0,xi+=5.0);
               star.SETM(4,1,yi+=15.0);
               star.SETM(5,0,xi+=5.0);
               star.SETM(5,1,yi-=15.0);
               star.SETM(6,0,xi+=15.0);
               star.SETM(6,1,yi-=5.0);
               star.SETM(7,0,xi-=15.0);
               star.SETM(7,1,yi-=5.0);
               star.SETM(8,0,xi+=15.0);
               star.SETM(8,1,yi-=5.0);
               star.SETM(9,0,xi-=15.0);
               star.SETM(9,1,yi-=5.0);
               star.SETM(10,0,xi-=5.0);
               star.SETM(10,1,yi-=15.0);
               star.SETM(11,0,xi-=5.0);
               star.SETM(11,1,yi+=15.0);

               mostrar(star,12);

               finishOvni = true;
               tStar->Enabled  = true;
               MP2->Play();
               i++;
        }
            else
                if( i > 10)
                        i = 0;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::tStarTimer(TObject *Sender)
{
        static int i = 0;
        if( i < 3)
        {

                star.Esc(star,m2,eqCentro(star),yeCentro(star),2,2);

                i++;
        }
        else
        {
                tStar->Enabled = false;
                quitStar = true;
                ovnisdown++;

                if(ovnisdown >=2)
                {

                        t1->Enabled = false;
                        for( int i = 0; i < numM; i++)
                                               dispint[i][0] =0;
                        for( int i = 0; i < dispOvnist2; i++)
                                               dispOvniint2[i][0] =0;


                        for( int i = 0; i < dispOvnist; i++)
                                               dispOvniint[i][0] =0;


                        m1quitStar = true;
                        tVelOvniDisp->Enabled = false;
                        t1Ovni->Enabled = false;
                        t1OvniMov->Enabled = false;
                        tVelOvni2Disp->Enabled = false;
                        t1Ovni2->Enabled = false;
                        t1OvniMov2->Enabled = false;


                        PanelGO->Visible = true;
                        Label2->Caption = "You Win!!";
                        primera = false;
                        MP->Stop();
                        MP->FileName = "intro.wav";
                        MP->Open();
                        MP->Play();
                        playing = true;
                }
                i = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tVelOvniDispTimer(TObject *Sender)
{
           for( int i = 0; i < dispOvnist; i++)
                if(dispOvniint[i][0] == 1)
                {
                        float tx = incEq(dispOvniint[i][1]);
                        float ty = incYe(dispOvniint[i][1]);

                        transdisp(dispOvni,i, 4,3,id,tx,ty*4);

                        if( dispOvni[i][0][0] >= ClientWidth*10000
                           || dispOvni[i][0][1] >= ClientHeight*1000)
                                dispOvniint[i][0] = 0;
                }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tVelOvni2DispTimer(TObject *Sender)
{
              for( int i = 0; i < dispOvnist2; i++)
                if(dispOvniint2[i][0] == 1)
                {
                        float tx = incEq(dispOvniint2[i][1]);
                        float ty = incYe(dispOvniint2[i][1]);

                        transdisp(dispOvni2,i, 4,3,id,tx,ty*4);

                        if( dispOvni2[i][0][0] >= ClientWidth*10000
                           || dispOvni2[i][0][1] >= ClientHeight*1000)
                                dispOvniint2[i][0] = 0;
                }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::t1Ovni2Timer(TObject *Sender)
{
        Repaint();
        if(dispAOvni2 < dispOvnist2-3)
        {
                dispOvniint2[dispAOvni2][0] = 1;
                dispOvniint2[dispAOvni2][1] =225;
                creardispOvni(dispOvni2,dispAOvni2++, ovni2.GETM(0,0),ovni2.GETM(0,1));
                dispOvniint2[dispAOvni2][0] = 1;
                dispOvniint2[dispAOvni2][1] = 270;
                creardispOvni(dispOvni2,dispAOvni2++, ovni2.GETM(6,0), ovni2.GETM(6,1));
                dispOvniint2[dispAOvni2][0] = 1;
                dispOvniint2[dispAOvni2][1] = 315;
                creardispOvni(dispOvni2,dispAOvni2++,ovni2.GETM(5,0),ovni2.GETM(5,1));
        }
        if(dispAOvni2 >= dispOvnist2-3)
        {
                dispAOvni2 = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::t1OvniMov2Timer(TObject *Sender)
{

          if( ovni2.GETM(0,0) >= -ClientWidth && flag2)
                ovni2.traslacion(ovni2,m2,-100,0);
        else
                if( ovni2.GETM(0,0) <= 0)
                        flag2 = false;

        if(ovni2.GETM(5,0) <= ClientWidth && !flag2)
                ovni2.traslacion(ovni2,m2,100,0);
        else
                if( ovni2.GETM(5,0) >= ClientWidth)
                        flag2 = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::t1giro2Timer(TObject *Sender)
{
        static int i= 0;
        ovni2.Rotardos(ovni2,m2,60,eqCentro(ovni2),yeCentro(ovni2));
        i++;
        if( i == 10)
        {
               t1giro2->Enabled = false;
               float xi = eqCentro(ovni2);
               float yi = yeCentro(ovni2);

               star2.SETM(0,0,xi);
               star2.SETM(0,1,yi);
               star2.SETM(1,0,xi+=15.0);
               star2.SETM(1,1,yi+=5.0);
               star2.SETM(2,0,xi-=15.0);
               star2.SETM(2,1,yi+=5.0);
               star2.SETM(3,0,xi+=15.0);
               star2.SETM(3,1,yi+=5.0);
               star2.SETM(4,0,xi+=5.0);
               star2.SETM(4,1,yi+=15.0);
               star2.SETM(5,0,xi+=5.0);
               star2.SETM(5,1,yi-=15.0);
               star2.SETM(6,0,xi+=15.0);
               star2.SETM(6,1,yi-=5.0);
               star2.SETM(7,0,xi-=15.0);
               star2.SETM(7,1,yi-=5.0);
               star2.SETM(8,0,xi+=15.0);
               star2.SETM(8,1,yi-=5.0);
               star2.SETM(9,0,xi-=15.0);
               star2.SETM(9,1,yi-=5.0);
               star2.SETM(10,0,xi-=5.0);
               star2.SETM(10,1,yi-=15.0);
               star2.SETM(11,0,xi-=5.0);
               star2.SETM(11,1,yi+=15.0);

               mostrar(star2,12);

               finishOvni2 = true;
               tStar2->Enabled  = true;

               MP2->Play();
               i++;
        }
        else
                if( i > 10)
                        i = 0;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::tStar2Timer(TObject *Sender)
{
        static int i = 0;
        if( i < 3)
        {

                star2.Esc(star2,m2,eqCentro(star2),yeCentro(star2),2,2);

                i++;
        }
        else
        {
                tStar2->Enabled = false;
                quitStar2 = true;
                ovnisdown++;

                if(ovnisdown >=2)
                {
                        for( int i = 0; i < dispOvnist2; i++)
                                               dispOvniint2[i][0] =0;


                        for( int i = 0; i < dispOvnist; i++)
                                               dispOvniint[i][0] =0;

                        
                        
                        m1quitStar = true;
                        t1->Enabled = false;
                        for( int i = 0; i < numM; i++)
                                               dispint[i][0] =0;
                        tVelOvniDisp->Enabled = false;
                        t1Ovni->Enabled = false;
                        t1OvniMov->Enabled = false;
                        tVelOvni2Disp->Enabled = false;
                        t1Ovni2->Enabled = false;
                        t1OvniMov2->Enabled = false;

                        general->Enabled = false;
                        PanelGO->Visible = true;
                        Label2->Caption = "You Win!!";
                        primera = false;
                        MP->Stop();
                        MP->FileName = "intro.wav";
                        MP->Open();
                        MP->Play();
                        playing = true;
                }
                i = 0;
        }
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Button1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        imagen->Top = 72;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AboutMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        imagen->Top = 112;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        imagen->Top = 152;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Enter(TObject *Sender)
{
         imagen->Top = 72;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AboutEnter(TObject *Sender)
{
        imagen->Top = 112;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button3Enter(TObject *Sender)
{
        imagen->Top = 152;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        About->Visible = false;
        Button3->Visible = false;
        Button1->Visible = false;
        imagen->Visible = false;
        Label1->Caption = "Select a level";
        manco->Visible = true;
        normal->Visible = true;
        pro->Visible = true;
        Panel1->Visible = true;
        Button9->Visible = true;
        howto->Visible = true;
        PanelA->Visible = false;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::mancoClick(TObject *Sender)
{
        tVelOvniDisp->Enabled = true;
        t1Ovni->Enabled = true;
        t1OvniMov->Enabled = true;
        tVelOvni2Disp->Enabled = true;
        t1Ovni2->Enabled = true;
        t1OvniMov2->Enabled = true;
        howto->Visible = false;

        Panel1->Visible = false;

        vOvni = 200;
        vOvni2 = 200;
        dano = 10;
        primera = true;

        MP->Stop();
        MP->FileName = "startgame.wav";
        MP->Open();
        MP->Play();

        nivel = "manco";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::normalClick(TObject *Sender)
{
        tVelOvniDisp->Enabled = true;
        t1Ovni->Enabled = true;
        t1OvniMov->Enabled = true;
        tVelOvni2Disp->Enabled = true;
        t1Ovni2->Enabled = true;
        t1OvniMov2->Enabled = true;
        Panel1->Visible = false;

        tVelOvniDisp->Interval = 200;
        t1Ovni->Interval = 800;
        t1OvniMov->Interval = 400;
        tVelOvni2Disp->Enabled = 200;
        t1Ovni2->Enabled = 800;
        t1OvniMov2->Enabled = 400;
        primera = true;
        howto->Visible = false;

        vOvni = 400;
        vOvni2 = 400;
        dano = 25;

        MP->Stop();
        MP->FileName = "startgame.wav";
        MP->Open();
        MP->Play();

        nivel = "normal";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::proClick(TObject *Sender)
{
        tVelOvniDisp->Enabled = true;
        t1Ovni->Enabled = true;
        t1OvniMov->Enabled = true;
        tVelOvni2Disp->Enabled = true;
        t1Ovni2->Enabled = true;
        t1OvniMov2->Enabled = true;
        Panel1->Visible = false;

        tVelOvniDisp->Interval = 100;
        t1Ovni->Interval = 700;
        t1OvniMov->Interval = 300;
        tVelOvni2Disp->Enabled = 100;
        t1Ovni2->Enabled = 700;
        t1OvniMov2->Enabled = 300;
        primera = true;
        howto->Visible = false;

        vOvni = 500;
        vOvni2 = 500;
        dano = 50;

        MP->Stop();
        MP->FileName = "startgame.wav";
        MP->Open();
        MP->Play();

        nivel = "pro";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::m1giroTimer(TObject *Sender)
{
        static int i= 0;
        m1.Rotardos(m1,m2,60,eqCentro(m1),yeCentro(m1));
        i++;
        if( i == 10)
        {
               m1giro->Enabled = false;
               float xi = eqCentro(m1);
               float yi = yeCentro(m1);

               m1star.SETM(0,0,xi);
               m1star.SETM(0,1,yi);
               m1star.SETM(1,0,xi+=15.0);
               m1star.SETM(1,1,yi+=5.0);
               m1star.SETM(2,0,xi-=15.0);
               m1star.SETM(2,1,yi+=5.0);
               m1star.SETM(3,0,xi+=15.0);
               m1star.SETM(3,1,yi+=5.0);
               m1star.SETM(4,0,xi+=5.0);
               m1star.SETM(4,1,yi+=15.0);
               m1star.SETM(5,0,xi+=5.0);
               m1star.SETM(5,1,yi-=15.0);
               m1star.SETM(6,0,xi+=15.0);
               m1star.SETM(6,1,yi-=5.0);
               m1star.SETM(7,0,xi-=15.0);
               m1star.SETM(7,1,yi-=5.0);
               m1star.SETM(8,0,xi+=15.0);
               m1star.SETM(8,1,yi-=5.0);
               m1star.SETM(9,0,xi-=15.0);
               m1star.SETM(9,1,yi-=5.0);
               m1star.SETM(10,0,xi-=5.0);
               m1star.SETM(10,1,yi-=15.0);
               m1star.SETM(11,0,xi-=5.0);
               m1star.SETM(11,1,yi+=15.0);

               mostrar(m1star,12);

               m1finishOvni = true;
               m1Star->Enabled  = true;
               MP2->Play();
               i++;
        }
        else
                if( i > 10)
                        i = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::m1StarTimer(TObject *Sender)
{
        static int i = 0;
        if( i < 3)
        {

                m1star.Esc(m1star,m2,eqCentro(m1),yeCentro(m1),2,2);

                i++;
        }
        else
        {
                m1Star->Enabled = false;
                m1quitStar = true;

                for( int i = 0; i < dispOvnist2; i++)
                                               dispOvniint2[i][0] =0;


                for( int i = 0; i < dispOvnist; i++)
                                               dispOvniint[i][0] =0;


                tVelOvniDisp->Enabled = false;
                t1Ovni->Enabled = false;
                t1OvniMov->Enabled = false;
                tVelOvni2Disp->Enabled = false;
                t1Ovni2->Enabled = false;
                t1OvniMov2->Enabled = false;


                PanelGO->Visible = true;
                Label2->Caption = "Game Over!!";
                general->Enabled  = false;
                
                MP->Stop();
                MP->FileName = "gameover.wav";
                MP->Open();
                MP->Play();
                primera = false;
                Repaint();
                i = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
        PanelGO->Visible = false;
        Button1->Click();
        /*
        Button2->Visible = false;
        Button3->Visible = false;
        Button1->Visible = false;
        imagen->Visible = false;
        Label1->Caption = "Selecciona el Nivel";
        manco->Visible = true;
        normal->Visible = true;
        pro->Visible = true;
        Panel1->Visible = true; */
        reset();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
        PanelQuit->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        PanelQuit->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
        PanelGO->Visible = false;
        Button1->Visible = true;
        About->Visible = true;
        Button3->Visible = true;
        imagen->Visible = true;
        manco->Visible = false;
        normal->Visible = false;
        pro->Visible = false;
        Panel1->Visible = true;
        Button9->Visible = false;

        reset();

        if(!playing)
        {
                MP->Stop();
                MP->FileName = "intro.wav";
                MP->Open();
                MP->Play();
        }
        Label1->Caption = "Mothership Attack!!";

}
//---------------------------------------------------------------------------



void __fastcall TForm1::generalTimer(TObject *Sender)
{
        Repaint();
}
//---------------------------------------------------------------------------

void TForm1::reset()
{
        m1.SETM(0,0,0);
        m1.SETM(0,1,0);
        m1.SETM(1,0,10);
        m1.SETM(1,1,20);
        m1.SETM(2,0,20);
        m1.SETM(2,1,10);
        m1.SETM(3,0,30);
        m1.SETM(3,1,10);
        m1.SETM(4,0,40);
        m1.SETM(4,1,50);
        m1.SETM(5,0,50);
        m1.SETM(5,1,10);
        m1.SETM(6,0,60);
        m1.SETM(6,1,10);
        m1.SETM(7,0,70);
        m1.SETM(7,1,20);
        m1.SETM(8,0,80);
        m1.SETM(8,1,0);
        m1.SETM(9,0,40);
        m1.SETM(9,1,-40);

        m1.traslacion(m1,m2,0,-300);



        ovni.SETM(0,0,-100);
        ovni.SETM(0,1,100);
        ovni.SETM(1,0,-90);
        ovni.SETM(1,1,120);
        ovni.SETM(2,0,-70);
        ovni.SETM(2,1,140);
        ovni.SETM(3,0,-30);
        ovni.SETM(3,1,140);
        ovni.SETM(4,0,-10);
        ovni.SETM(4,1,120);
        ovni.SETM(5,0,0);
        ovni.SETM(5,1,100);
        ovni.SETM(6,0,-50);
        ovni.SETM(6,1,80);


        float cx = eqCentro(ovni);
        float cy = yeCentro(ovni);

        ovni.Esc(ovni,m2.Identidad(),cx,cy,3,3);
        ovni.traslacion(ovni,m2,0,300);

        ovni2.SETM(0,0,-100);
        ovni2.SETM(0,1,100);
        ovni2.SETM(1,0,-90);
        ovni2.SETM(1,1,120);
        ovni2.SETM(2,0,-70);
        ovni2.SETM(2,1,140);
        ovni2.SETM(3,0,-30);
        ovni2.SETM(3,1,140);
        ovni2.SETM(4,0,-10);
        ovni2.SETM(4,1,120);
        ovni2.SETM(5,0,0);
        ovni2.SETM(5,1,100);
        ovni2.SETM(6,0,-50);
        ovni2.SETM(6,1,80);

        cx = eqCentro(ovni2);
        cy = yeCentro(ovni2);

        ovni2.Esc(ovni2,m2.Identidad(),cx,cy,3,3);
        ovni2.traslacion(ovni2,m2,0,100);

        for(int i = 0; i < dispOvnist; i++)
                dispOvniint[i][0] = 0;

        for(int i = 0; i < dispOvnist2; i++)
                dispOvniint2[i][0] = 0;

        L=(ClientWidth) /2;
        M=ClientHeight/2;
        angulo = 90;

        /*
        disparos[0].Inicializa(4,3);
        disparos[1].Inicializa(4,3);
        disparos[2].Inicializa(4,3);
        disparos[3].Inicializa(4,3);
        disparos[4].Inicializa(4,3);*/


        disactuales = 0;

        for(int i = 0; i < ndisp; i++)
        {
                dispint[i][0] = 0;
                dispint[i][1] = 90;
        }


        for( int  i = 0; i < 5; i++)
                for( int j = 0; j < 4; j++)
                        for( int k = 0; k < 3; k++)
                                disp[i][j][k] = 1;


        for( int i = 0; i < 3; i++)
                for( int  j= 0; j < 3; j++)
                        if( i == j)
                                id[i][j] = 1;
                        else
                                id[i][j] = 0;

        m1finish = false;
        m1finishOvni = false;
        m1quitStar = false;
        dispAOvni = 0;
        finish = false;
        finishOvni = false;
        quitStar = false;
        flag = false;
        dispAOvni2 = 0;
        finish2 = false;
        finishOvni2 = false;
        quitStar2 = false;
        flag2 = true;
        primera = false;
        ovnisdown = 0;
        disaux = 0;
        ndisp = 10;
        vM1= 100;
}
void __fastcall TForm1::Button7Click(TObject *Sender)
{
        this->Close();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
        PanelQuit->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
        if(Key == 27)
        {
                PanelQuit->Visible = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
        Button1->Visible = true;
        About->Visible = true;
        Button3->Visible = true;
        imagen->Visible = true;
        manco->Visible = false;
        normal->Visible = false;
        pro->Visible = false;
        Panel1->Visible = true;
        Button9->Visible = false;
        howto->Visible = false;
        Label1->Caption = "Mothership Attack!!";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        PanelA->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AboutClick(TObject *Sender)
{
        if(!PanelA->Visible)
                PanelA->Visible = true;
        else
                PanelA->Visible = false;
}
//---------------------------------------------------------------------------


