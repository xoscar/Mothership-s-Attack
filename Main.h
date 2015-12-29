//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Math.h>
#include "Unit3.h"
#include "Unit2.h"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *t1;
        TTimer *t1Ovni;
        TTimer *t1OvniMov;
        TTimer *t1giro;
        TTimer *tStar;
        TTimer *tVelOvniDisp;
        TTimer *tVelOvni2Disp;
        TTimer *t1Ovni2;
        TTimer *t1OvniMov2;
        TTimer *t1giro2;
        TTimer *tStar2;
        TPanel *Panel1;
        TLabel *Label1;
        TButton *Button1;
        TButton *About;
        TButton *Button3;
        TImage *imagen;
        TPanel *manco;
        TPanel *normal;
        TPanel *pro;
        TTimer *m1giro;
        TTimer *m1Star;
        TPanel *PanelGO;
        TLabel *Label2;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TTimer *general;
        TMediaPlayer *MP;
        TMediaPlayer *MP2;
        TPanel *PanelQuit;
        TLabel *Label3;
        TButton *Button7;
        TButton *Button8;
        TButton *Button9;
        TPanel *PanelA;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TImage *Image1;
        TPanel *howto;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label24;
        TButton *Button2;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall t1Timer(TObject *Sender);
        void __fastcall t1OvniTimer(TObject *Sender);
        void __fastcall t1OvniMovTimer(TObject *Sender);
        void __fastcall t1giroTimer(TObject *Sender);
        void __fastcall tStarTimer(TObject *Sender);
        void __fastcall tVelOvniDispTimer(TObject *Sender);
        void __fastcall tVelOvni2DispTimer(TObject *Sender);
        void __fastcall t1Ovni2Timer(TObject *Sender);
        void __fastcall t1OvniMov2Timer(TObject *Sender);
        void __fastcall t1giro2Timer(TObject *Sender);
        void __fastcall tStar2Timer(TObject *Sender);
        void __fastcall Button1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall AboutMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Button3MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Button1Enter(TObject *Sender);
        void __fastcall AboutEnter(TObject *Sender);
        void __fastcall Button3Enter(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall mancoClick(TObject *Sender);
        void __fastcall normalClick(TObject *Sender);
        void __fastcall proClick(TObject *Sender);
        void __fastcall m1giroTimer(TObject *Sender);
        void __fastcall m1StarTimer(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall generalTimer(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall AboutClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void mostrar(Matrix &m, int n);

        void mostrar1(float disp[][4][3], int n, int i);

        UnidadII u;
        int L, M, total;
        float eqCentro(Matrix &m);
        float yeCentro(Matrix &m);
        float incEq(int ang);
        float incYe(int ang);
        float angulo;
        int dispint[10][2];
        void creardispOvni(float dispOvni[][4][3],int i, float x, float y);
        void disparar();
        void creardisp1(int  i, float x, float y);
        int disactuales;

        float disp[10][4][3];
        float dispOvni[40][4][3];

        float dispOvni2[40][4][3];

        float id[3][3];

        void transdisp(float disp[][4][3], int  i,int ren, int col, float id[3][3], float sx, float sy);

        void reset();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
