//---------------------------------------------------------------------------


#pragma hdrstop

#include "Unit2.h"
#include <math.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

void UnidadII::ventana(float WX1,float WY1, float WX2, float WY2)
{
      XWmin=WX1;
      YWmin=WY1;
      XWmax=WX2;
      YWmax=WY2;
}

void UnidadII::puerto(int VX1,int VY1, int VX2,int VY2)
{
      XPVmin=VX1;
      YPVmin=VY1;
      XPVmax=VX2;
      YPVmax=VY2;
}

void UnidadII::mapeo(float X,float Y, int &XT,int &YT, int L, int M)
{
       float sx,sy;
       sx=(XPVmax-XPVmin)/(XWmax-XWmin);
       sy=(YPVmax-YPVmin)/(YWmax-YWmin);
       XT=floor((sx*(X-XWmin)+XPVmin+L)+0.5);
       YT=floor((sy*(YWmin-Y)-YPVmin+M)+0.5);
}
