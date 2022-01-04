
/**************************************************************************/
/*	GENERAL.C                                                         */
/*	Uso : Archivo base para otros programas.                          */
/*                                                                        */
/*	Autor : Roberto Sanz                                              */
/*	Fecha : 06-04-1995                                                */
/**************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <bios.h>

#define ESC 27
#define AND &&
#define OR  ||

/* Para el curso de Git y GitHub */
#define RETURN 13

int Abortar(void);

void Inicializar(int *pargc, char *pargv[], char *pfent, char *pfsal,
		 char *pferr);
void AyudaNormal(void);
void AyudaExtra(void);
void Video(int columna, int fila, int fondo, int tinta, int longitud,
	   char *variable);
void Cursor(int columna, int fila);
int  Tecla(void);
char *Entrar(int columna, int fila, int fondo, int tinta,
	     int numero_caracteres, char *literal);
FILE *Ficheros(char *nombre, char *modo);


void main(int argc, char *argv[])
{
FILE   *fent, *fsal, *ferr;

Inicializar(&argc, argv, fich_ent, fich_sal, fich_err);
fent = Ficheros(fich_ent, "rt");
fsal = Ficheros(fich_sal, "wt");
ferr = Ficheros(fich_err, "wt");
ctrlbrk(Abortar);	/* Cambiar el manejador de CONTROL-BREAK */
setcbrk(1);		/* Activar CONTROL-BREAK */

fcloseall();
}

/*************************** FUNCIONES *********************************/

int Abortar(void)
{
gotoxy(1, 10);
printf("­ Programa interrumpido por el usuario !");
return(0);
}

void Error(int error)
{
printf("\n\n\nError : %s", sys_errlist[error]);
exit(1);
}

void Inicializar(int *pargc, char *pargv[], char *pfent, char *pfsal,
		 char *pferr)
{
int contador;

switch(*pargc)
  {
  case 1:
    {
    clrscr();
    pfent[0] = pfsal[0] = 0x00;
    printf("\n\nNombre del archivo de entrada  :");
    gotoxy(66, 3);
    printf("ESC = salir");
    strcpy(pfent, Entrar(34, 2, 0, 15, 29, ""));
    gotoxy(66, 3);
    printf("           ");
    if(pfent[0] == 27)
      {
      printf("\n");
      exit(1);
      }

    for(contador=0; pfent[contador] != '.' && pfent[contador] != 0x00;
	contador++)
      {
      pfsal[contador] = pfent[contador];
      pfsal[contador+1] = 0x00;
      }
    if(pfsal[contador] == 0x00) strcat(pfent, ".fot");
    Video(34, 2, 0, 7, strlen(pfent), pfent);

    strcpy(pferr, pfsal);
    strcat(pferr, ".err");
    strcat(pfsal, ".pho");
    printf("\nNombre del archivo de salida   :");
    gotoxy(66, 4);
    printf("ESC = salir");
    strcpy(pfsal, Entrar(34, 3, 0, 15, 29, pfsal));
    gotoxy(66, 4);
    printf("           ");
    if(pfsal[0] == 27)
      {
      printf("\n");
      exit(1);
      }
    Video(34, 3, 0, 7, strlen(pfsal), pfsal);
    printf("\nNombre del archivo de errores  :");
    Video(34, 4, 0, 7, strlen(pferr), pferr);
    }
    break;

  case 2:
    {
    if(!strcmp(pargv[1], "/?"))
      {
      AyudaNormal();
      exit(1);
      }
    else if(!strcmp(pargv[1], "/e") || !strcmp(pargv[1], "/E"))
      {
      AyudaExtra();
      exit(1);
      }
    else
      {
      printf("%c", 7);
      printf("­ Formato no v lido !");
      exit(1);
      }
    }
    break;

  default:
    {
    printf("%c", 7);
    printf("­ Demasiados par metros !");
    exit(1);
    }
    break;
  }
}

FILE *Ficheros(char *nombre, char *modo)
{
FILE *fp;

if((fp=fopen(nombre,modo))==NULL)
  {
  gotoxy(5,6);
  printf("­ No se puede abrir archivo  %s !\n", nombre);
  exit(1);
  }
return(fp);
}

void AyudaNormal(void)
{
printf("Uso : Modifica archivos de foto en formato PHOCUS cambiandolos");
printf(" de formato.\n\n");
printf("Formato : REPRO\n");
printf("          REPRO [opciones]\n\n");
printf("opciones:\n");
printf("   - /?     : Presenta esta informaci¢n.\n");
printf("   - /e  /E : Presenta ayuda extendida.\n");
}

void AyudaExtra(void)
{
printf("\n");
printf("El programa REPRO.EXE lee archivos de foto en formato PHOCUS\n");
printf("y los cambia de formato.\n");
printf("Este programa pide el nombre de un archivo de entrada y otro\n");
printf("de salida. Se necesita tambien una tolerancia en micrones de\n");
printf("las diferencias de medici¢n de los puntos. Se genera un archivo\n");
printf("de errores con los puntos que sobrepasan esa tolerancia.\n");
printf("Limitaciones :\n");
printf("  - Se leer n un m ximo de 2000 fotos.\n");
printf("  - Cada foto puede estar medida un m ximo de 5 veces.\n");
printf("  - Cada foto puede tener un m ximo de 100 puntos");
printf(" ( Contando repeticiones ).\n\n");
}

char *Entrar(int columna, int fila, int fondo, int tinta,
	     int numero_caracteres, char *literal)
{
int  atributo, contador, tecla, offset, control;
int  ultimo_caracter, col_ini, col_fin, tinta_suave;
char cadena[80];

if(tinta>7) tinta_suave=tinta-8;
atributo = (fondo<<4)|tinta;
control=0;
col_ini = columna-1;
col_fin = columna+numero_caracteres;

Video(col_ini, fila, fondo, tinta_suave, 1, "[");
Video(col_fin, fila, fondo, tinta_suave, 1, "]");

for(contador=columna; contador<(numero_caracteres+columna); contador++)
  {
  Video(contador,fila,fondo,tinta_suave,1,"_");
  }
Video(columna,fila,fondo,tinta,strlen(literal),literal);

contador=0;
ultimo_caracter=strlen(literal);
strcpy(cadena,literal);

while(control!=1)
  {
  Cursor(columna,fila);
  tecla = Tecla();

  if(tecla<256)   /* si la tecla pulsada es normal o especial */
		  /*     especial > 255       normal < 256    */
    {
    switch(tecla)
      {
      case 8:     /*    se ha pulsado BS (Back Space)   */
	{
	if(contador<1)   printf("%c",7); /* sonido */
	else if(ultimo_caracter !=contador) printf("%c",7);

	else
	  {
	  columna--;
	  contador--;
	  ultimo_caracter--;
	  Video(columna,fila,fondo,tinta_suave,1,"_");
	  cadena[contador]=0x00; /* finalizador de cadena */
	  }
	}
	break;

      case 27:   /* se ha pulsado ESC */
	{
	cadena[0] = ESC;
	control=1;
	}
	break;

      case 13:   /* se ha pulsado return */
	{
	control=1;
	}
	break;

      default:   /* la tecla pulsada se imprime */
	{
	if(contador==numero_caracteres)  printf("%c",7);

	else
	  {
	  offset = (fila*160)+(columna*2);
	  pokeb(0xb800, offset, tecla);
	  cadena[contador]=peekb(0xb800, offset);
	  pokeb(0xb800, ++offset, atributo);
	  if(ultimo_caracter==contador)
	    {
	    ultimo_caracter++;
	    cadena[contador+1]=0x00; /* finalizador de cadena */
	    }
	  contador++;
	  columna++;
	  }
	}
	break;
      }            /* corresponde al switch */
    }              /* corresponde al if */

  else  /* corresponde al 1er. if */
    {
    switch(tecla)
      {
      case 331:   /* flecha izda. */
	{
	if(contador<1) printf("%c",7);
	else
	  {
	  columna--;
	  contador--;
	  Cursor(columna,fila);
	  }
	}
	break;

      case 333:   /* flecha dcha.  */
	{
	if(contador==ultimo_caracter) printf("%c",7);
	else
	  {
	  contador++;
	  columna++;
	  Cursor(columna,fila);
	  }
	}
	break;

      default:
	{
	printf("%c",7);
	}
	break;
      }
    }   /*  fin del else  */
  }       /* fin del while  */

Video(col_ini, fila, fondo, tinta, 1, " ");
Video(col_fin, fila, fondo, tinta, 1, " ");
for(control=col_ini+ultimo_caracter+1; control<col_fin; control++)
  {
  Video(control, fila, fondo, tinta, 1, " ");
  }
return(cadena);
}

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
}

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
}

void Cursor(int columna, int fila)
{
union REGS regs; /* necesario para trabajar con los registros de la CPU */

regs.h.ah = 2;       /* funci¢n de posicionamiento */
regs.h.dh = fila;
regs.h.dl = columna;
regs.h.bh = 0;       /* Pagina de video. Esto solo funciona en la 0 */

int86(0x10,&regs,&regs);
}