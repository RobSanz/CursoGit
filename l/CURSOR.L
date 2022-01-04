
/************           CURSOR.L                ********************/


/*******************************************************************/
/*       Funci¢n que situa el cursor en la pantalla. El programa   */
/*       que use esta funci¢n necesita incluir la libreria 'dos.h' */
/*                                                                 */
/*          void Cursor(int columna, int fila)                     */
/*******************************************************************/

void Cursor(int columna, int fila)
{
  union REGS regs; /* necesario para trabajar con los registros de la CPU */

  regs.h.ah = 2;       /* funci¢n de posicionamiento */
  regs.h.dh = fila;
  regs.h.dl = columna;
  regs.h.bh = 0;       /* Pagina de video. Esto solo funciona en la 0 */

  int86(0x10,&regs,&regs);
}