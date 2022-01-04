
/************                 VIDEO.L                ********************/


/************************************************************************/
/*         Funci¢n que imprime una cadena en la pantalla                */
/*                                                                      */
/* void Video(int columna, fila, fondo, tinta, longitud, char *variable */
/************************************************************************/

void Video(int columna, int fila, int fondo, int tinta, int longitud,
	   char *variable)
{
  int atributo,offset,contador;

  atributo=(fondo<<4)|tinta;
  offset=(fila*160)+(columna*2)-1;  /* offset del primer car cter */

  for(contador=0; contador<longitud; contador++)
    {
      pokeb(0xb800, ++offset, *variable++); /* imprime el car cter */
      pokeb(0xb800, ++offset, atributo);    /* establece el atributo de */
    }                                       /* fondo y tinta            */
}