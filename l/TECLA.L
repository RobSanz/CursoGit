/*****************             TECLA.L            ******************/


/********************************************************************/
/*     Funci¢n que devuelve el c¢digo de la tecla pulsada           */
/*                                                                  */
/*                      int Tecla(void)                             */
/********************************************************************/

int Tecla(void)
{
  int tecla,arriba,abajo;

  tecla = bioskey(0);   /* pone en 'tecla' dos bytes, correspondientes
			   a la tecla pulsada */

  abajo = tecla & 0x00ff;
  arriba = (tecla & 0xff00) >> 8;

  if(abajo==0) return(arriba+256); /* si abajo==0 se ha pulsado una tecla
				      especial */
  else return(abajo);     /* si no se ha pulsado una tecla normal */
}