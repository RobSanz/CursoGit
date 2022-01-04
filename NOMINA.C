
/* Tope de cotizaci¢n en linea 541 */

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include "c:\tc\l\cursor.l"
#include "c:\tc\l\tecla.l"
#include "c:\tc\l\video.l"
#include "c:\tc\l\entracar.l"

#define EMPLE  30
#define ESC    27

/* para el curso de Git */
/* Primera mod */
#define RETURN 13

void   bajas(void),      modif(void),       aviso_baja(void);
void   elec1(void),      def_panta(void),   def_panta1(int fila,int fila1);
void   iniz_lista(void), nomina(void),      opcion_imp(void);
void   altas(void),      datos_pantalla(int t);
void   extras(unsigned long int extr,int t,char nom[]);
int    leer_arch(void),  escribir_archivo(void);

float redondeo();

struct datos {
  float desempleo;
  float comunes;
  float irpf;
  char productor[80];
  char categoria[80];
  char s_s[20];
  char tarifa[3];
  char alta[15];
  unsigned int matricula;
  unsigned long int salario_base;
  unsigned long int plus_convenio;
  unsigned long int com_vol;
} datos_emple[EMPLE];

char mes[15];
int dias;

void main()
{
  char elec;

  textmode(C80);
  textbackground(1);
  clrscr();

  iniz_lista();
  if(leer_arch()==-1) return;

  do {
    elec1();
    gotoxy(50,1);
    cprintf("Opcion: ");
    elec=tolower(getch());

    switch(elec) {
      case 'a': {
	altas();
	break;
      }
      case 'b':  {
	bajas();
	break;
      }
      case 'm':  {
	modif();
	break;
      }
      case 'n':  {
	nomina();
	break;
      }
    }
  } while (elec!='s');

  textmode(LASTMODE);
  textbackground(0); /* color negro */
  textcolor(15);  /* color blanco */
  lowvideo();
  clrscr();
}

void def_panta1(int fila,int fila1)
{
  gotoxy(3,fila);
  cprintf("Productor:\n\r");
  cprintf("  Categoria:\n\r");
  cprintf("  N§ afiliaci¢n S.S. :                   G§ tarifa:");
  cprintf("%16s\n\r","Alta:");
  cprintf("%63s","N§ matr.:");
  gotoxy(3,fila1);
  cprintf("Salario Base:\n\r");
  cprintf("  Plus Convenio:\n\r");
  cprintf("  Compl. Pers. Vol. Absor. :");
}

void def_panta(void)
{
  int fila=2,fila1=7;

  window(1,1,80,25);
  textbackground(1); /* fondo azul */
  clrscr();
  textcolor(14); /* texto amarillo */


  def_panta1(fila,fila1);
  gotoxy(3,5);
  cprintf("Periodo liquidado:              Total d¡as:\n\r");
  cprintf("  %c",'Ä'); /* ASCII 196 */
  gotoxy(3,10);
  cprintf("Nocturnidad:\n\r");
  cprintf("  Plus actividad:\n\r");
  cprintf("  Extra:\n\r");
  cprintf("  %c\n\r",'Ä');
  cprintf("  COMPUTABLE :\n\r");
  cprintf("  %c\n\r",'Ä');
  cprintf("  Prorrata pagas extraord. :\n\r");
  cprintf("  Contingencias comunes:                 al           %%\n\r");
  cprintf("  Desempleo:                             al           %%\n\r");
  cprintf("  I.R.P.F. :                             al           %%\n\r");
  cprintf("  %c\n\r",'Ä');
  cprintf("  TOTAL DEDUCCIONES :\n\r");
  cprintf("  %c\n\r",'Ä');
  cprintf("  TOTAL A PERCIBIR :\n\r");
}

void elec1()
{
  textbackground(1);  /* color azul */
  clrscr();
  window(1,1,80,1);
  textcolor(0); /* color negro */
  textbackground(15); /* color blanco */
  clrscr();

  gotoxy(3,1);
  cprintf(" ltas   ajas   odif.   ¢mina   alir");
  textcolor(4);
  gotoxy(3,1);
  cprintf("A");
  gotoxy(10,1);
  cprintf("B");
  gotoxy(17,1);
  cprintf("M");
  gotoxy(25,1);
  cprintf("N");
  gotoxy(33,1);
  cprintf("S");
}

void altas(void)
{
  int fila=10,fila1=14,t;
  char elec;
  float comunes;

  for(t=1; t<EMPLE; t++)
      if(!*datos_emple[t].productor) break;

    datos_emple[t].matricula=t;

  do {
    window(1,1,80,25);
    textbackground(1); /* fondo azul */
    clrscr();
    textcolor(14); /* texto amarillo */

    def_panta1(fila,fila1);

    gotoxy(3,18);
    cprintf("%% contingencias comunes:");
    gotoxy(3,19);
    cprintf("%% desempleo:");
    gotoxy(3,20);
    cprintf("%% I.R.P.F.:");
    gotoxy(25,4);
    cprintf("INTRODUCE DATOS");

    if(t==EMPLE) {
      gotoxy(10,24);
      cprintf("No caben m s empleados.  Pulsa %cÙ.",27);
      getch();
      return;
    }

    textcolor(4);
    gotoxy(1,13);
    delline();
    insline();
    gotoxy(3,9);
    cprintf("N§ matricula: %d",datos_emple[t].matricula);
    gotoxy(14,10);
    gets(datos_emple[t].productor);
    gotoxy(14,11);
    gets(datos_emple[t].categoria);
    gotoxy(24,12);
    gets(datos_emple[t].s_s);
    gotoxy(53,12);
    gets(datos_emple[t].tarifa);
    gotoxy(69,12);
    gets(datos_emple[t].alta);
    gotoxy(17,14);
    fscanf(stdin,"%ld%*c",&datos_emple[t].salario_base);
    gotoxy(19,15);
    fscanf(stdin,"%ld%*c",&datos_emple[t].plus_convenio);
    gotoxy(31,16);
    fscanf(stdin,"%ld%*c",&datos_emple[t].com_vol);

    gotoxy(29,18);
    fscanf(stdin,"%f%*c",&comunes);
    datos_emple[t].comunes=comunes;
    gotoxy(17,19);
    fscanf(stdin,"%f%*c",&datos_emple[t].desempleo);
    gotoxy(16,20);
    fscanf(stdin,"%f%*c",&datos_emple[t].irpf);

    gotoxy(35,22);
    cprintf("¨ Correcto ? s/n ");
    elec=tolower(getche());
  } while (elec!='s');

  cscanf("%*c");
  escribir_archivo();

}

int escribir_archivo(void)
{
  FILE *fp;
  int t;

  if((fp=fopen("nomina.bin","wb"))==NULL) {
    gotoxy(1,24);
    cprintf("No puede abrirse el archivo   (return para seguir)");
    getch();
    return(-1);
  }

  for(t=1; t<EMPLE; t++)
    if(*datos_emple[t].productor)
      if(fwrite(&datos_emple[t],sizeof(struct datos),1,fp)!=1) {
	gotoxy(1,24);
	cprintf("Error de escritura en el archivo   (return para seguir)");
	getch();
	return(-1);
    }
  fclose(fp);
  return(0);
}

int leer_arch(void)
{
  FILE *fp;
  int t;

  if((fp=fopen("nomina.bin","rb"))==NULL) {
    gotoxy(1,24);
    cprintf("No puede abrirse el archivo   (return para seguir)");
    getch();
    return(-1);
  }

  for(t=1; t<EMPLE; t++)
    if(fread(&datos_emple[t],sizeof(struct datos),1,fp)!=1) {
      if(feof(fp)) {
	fclose(fp);
	break;
    }
    gotoxy(1,24);
    cprintf("Error de lectura en el archivo   (return para seguir)");
    getch();
  }
  return(0);
}


void bajas(void)
{
  int t;
  char elec,caract[]="a dar de baja:";

  do {
    t=mod_baj(caract);
    datos_pantalla(t);
    gotoxy(1,22);
    delline();

    do {
      gotoxy(14,22);
      cprintf("ESC=menu    ");
      cprintf("Correcto s/n");
      elec=tolower(getch());

    } while (elec!='s' && elec !='n' && elec!=ESC);
  } while (elec=='n');

  if(elec=='s')  {
    strcpy(datos_emple[t].productor,"BAJA");
    escribir_archivo();
  }
}


int mod_baj(char *caract)
{
  int t=0,fila=10,fila1=14;


  window(1,1,80,25);
  textbackground(1); /* fondo azul */
  clrscr();
  textcolor(14); /* texto amarillo */

  do {

    if(*datos_emple[t].productor=='B') aviso_baja();
    clrscr();
    def_panta1(fila,fila1);

    gotoxy(3,18);
    cprintf("%% contingencias comunes:");
    gotoxy(3,19);
    cprintf("%% desempleo:");
    gotoxy(3,20);
    cprintf("%% I.R.P.F.:");

    gotoxy(10,22);
    delline();
    gotoxy(10,22);
    cprintf("Intruduce n§ matricula %s",caract);
    gotoxy(49,22);
    cscanf("%d%*c",&t);
  } while (t>EMPLE || *datos_emple[t].productor=='\0' ||
	   *datos_emple[t].productor=='B');
  return(t);
}

void aviso_baja(void)
{
  clrscr();
  gotoxy(15,12);
  cprintf("Elemento dado de baja");
  gotoxy(17,14);
  cprintf("( return)");
  getch();
}

void datos_pantalla(int t)
{
  textcolor(4);
  gotoxy(1,13);
  delline();
  insline();
  gotoxy(3,9);
  cprintf("N§ matricula: %d",datos_emple[t].matricula);
  gotoxy(14,10);
  cprintf(datos_emple[t].productor);
  gotoxy(14,11);
  cprintf(datos_emple[t].categoria);
  gotoxy(24,12);
  cprintf(datos_emple[t].s_s);
  gotoxy(53,12);
  cprintf(datos_emple[t].tarifa);
  gotoxy(69,12);
  cprintf(datos_emple[t].alta);
  gotoxy(17,14);
  cprintf("%ld",datos_emple[t].salario_base);
  gotoxy(19,15);
  cprintf("%ld",datos_emple[t].plus_convenio);
  gotoxy(31,16);
  cprintf("%ld",datos_emple[t].com_vol);

  gotoxy(29,18);
  cprintf("%3.3f",datos_emple[t].comunes);
  gotoxy(17,19);
  cprintf("%3.3f",datos_emple[t].desempleo);
  gotoxy(16,20);
  cprintf("%3.3f",datos_emple[t].irpf);
}


void modif(void)
{
  int t, a=0;
  char caract[]="a modificar :", tecla, categoria_temp[80];
  float comunes;


  while(a != 1)
  {
    t=mod_baj(caract);
    datos_pantalla(t);
    textcolor(4);

    Video(9,21,1,3,41,"ESC = men£    flecha izda.   flecha dcha.");

    strcpy(categoria_temp, Entracar(13,10,1,4,65,
	   datos_emple[t].categoria));

    if(categoria_temp[0]==ESC)  return;

    strcpy(datos_emple[t].categoria, categoria_temp);

    Video(9,21,1,3,41,"              flecha izda.   flecha dcha.");

    strcpy(datos_emple[t].tarifa, Entracar(52,11,1,4,2,
	   datos_emple[t].tarifa));

    Video(9,21,1,3,41,"                                         ");

    gotoxy(17,14);
    cprintf("            %ld",datos_emple[t].salario_base);
    gotoxy(17,14);
    fscanf(stdin,"%ld%*c",&datos_emple[t].salario_base);

    gotoxy(19,15);
    cprintf("            %ld",datos_emple[t].plus_convenio);
    gotoxy(19,15);
    fscanf(stdin,"%ld%*c",&datos_emple[t].plus_convenio);

    gotoxy(31,16);
    cprintf("            %ld",datos_emple[t].com_vol);
    gotoxy(31,16);
    fscanf(stdin,"%ld%*c",&datos_emple[t].com_vol);

    gotoxy(29,18);
    cprintf("            %3.3f",datos_emple[t].comunes);
    gotoxy(29,18);
    fscanf(stdin,"%f%*c",&comunes);
    datos_emple[t].comunes=comunes;

    gotoxy(17,19);
    cprintf("            %3.3f",datos_emple[t].desempleo);
    gotoxy(17,19);
    fscanf(stdin,"%f%*c",&datos_emple[t].desempleo);

    gotoxy(16,20);
    cprintf("            %3.3f",datos_emple[t].irpf);
    gotoxy(16,20);
    fscanf(stdin,"%f%*c",&datos_emple[t].irpf);


    gotoxy(10,22);
    cprintf("¨ M s modificaciones ? s/n                ");
    do
      {
        tecla=Tecla();
	if(tecla=='n' || tecla=='N') a=1;
      }while(tecla!='s' && tecla!='S' && tecla!='n' && tecla!='N');
  }
  escribir_archivo();
}

void nomina(void)
{
  float contin, desem,irpf;
  int t=0;
  unsigned long int nocturno,plus,computable;
  unsigned long int pror,deduc,total,extra,cont,des;
  char elec,nom[15]="\0";

  do {
    if(*datos_emple[t].productor=='B') aviso_baja();
    def_panta();
    textcolor(4);

    gotoxy(65,5);
    fscanf(stdin,"%d%*c",&t);
  } while (t>EMPLE || *datos_emple[t].productor=='\0' ||
	  *datos_emple[t].productor=='B');


  datos_emple[t].matricula=t;

  gotoxy(14,2);
  cprintf(datos_emple[t].productor);
  gotoxy(14,3);
  cprintf(datos_emple[t].categoria);
  gotoxy(24,4);
  cprintf(datos_emple[t].s_s);
  gotoxy(53,4);
  cprintf(datos_emple[t].tarifa);
  gotoxy(69,4);
  cprintf(datos_emple[t].alta);
  gotoxy(70,7);
  cprintf("%ld",datos_emple[t].salario_base);
  gotoxy(70,8);
  cprintf("%ld",datos_emple[t].plus_convenio);
  gotoxy(70,9);
  cprintf("%ld",datos_emple[t].com_vol);
  gotoxy(48,17);
  cprintf("%1.3f",datos_emple[t].comunes);
  gotoxy(48,18);
  cprintf("%1.3f",datos_emple[t].desempleo);
  gotoxy(48,19);
  cprintf("%1.3f",datos_emple[t].irpf);

  gotoxy(22,5);
  gets(mes);
  gotoxy(47,5);
  fscanf(stdin,"%d%*c",&dias);
  gotoxy(70,10);
  fscanf(stdin,"%ld%*c",&nocturno);
  gotoxy(70,11);
  fscanf(stdin,"%ld%*c",&plus);
  computable=datos_emple[t].salario_base+datos_emple[t].plus_convenio+
	     datos_emple[t].com_vol;

  gotoxy(70,12);
  fscanf(stdin,"%ld%*c",&extra);

  itoa(datos_emple[t].matricula,nom,10);

  if(extra!=0) {
    strcat((strcat(nom,mes)),".ext");
    extras(extra,t,nom);
    return;
  }

  pror=computable/4;
  gotoxy(70,16);
  cprintf("%6ld",pror);
  computable=computable+nocturno+plus;
  gotoxy(70,14);
  cprintf("%6ld",computable);

  contin=computable+pror;
  contin=contin/300;
  contin=redondeo(contin);
  contin=contin*300;
  desem=des=contin;

  if (contin>252000l) contin=252000l;  /* tope de cotizaci¢n grupo 5 */
  cont=contin;

  gotoxy(27,17);
  cprintf("%6.0f",contin);
  contin=contin*datos_emple[t].comunes/100;
  contin=redondeo(contin);

  gotoxy(70,17);
  cprintf("%6.0f",contin);

  gotoxy(27,18);
  cprintf("%6.0f",desem);
  desem=desem*datos_emple[t].desempleo/100;
  desem=redondeo(desem);

  gotoxy(70,18);
  cprintf("%6.0f",desem);

  gotoxy(27,19);
  cprintf("%6ld",computable);
  irpf=computable*datos_emple[t].irpf/100;
  irpf=redondeo(irpf);

  gotoxy(70,19);
  cprintf("%6.0f",irpf);

  deduc=contin+desem+irpf;
  gotoxy(70,21);
  cprintf("%6ld",deduc);

  total=computable-deduc;
  gotoxy(70,23);
  cprintf("%6ld",total);

  strcat((strcat(nom,mes)),".nom");

  do {
    opcion_imp();
    elec=tolower(getch());
  } while (elec<'a' || elec>'c');

  switch(elec) {
    case 'a': {
      break;
    }

    case 'b': {
      salvar_nomina(contin,desem,irpf,t,nom,nocturno,plus,computable,
		    pror,cont,des,deduc,total);
      break;
    }

    case 'c': {
      salvar_nomina(contin,desem,irpf,t,nom,nocturno,plus,computable,
		    pror,cont,des,deduc,total);
      imprimir(nom);
    }
  }
}

void extras(unsigned long int extr,int t,char nom[])
{
  float deduc1;
  unsigned long int total_extra;
  char elec;

  gotoxy(17,7);
  clreol();
  gotoxy(19,8);
  clreol();
  gotoxy(31,9);
  clreol();
  gotoxy(70,10);
  clreol();
  gotoxy(70,11);
  clreol();
  gotoxy(48,17);
  cprintf("     ");
  gotoxy(48,18);
  cprintf("     ");
  gotoxy(15,12);
  cprintf(mes);

  gotoxy(70,14);
  cprintf("%6ld",extr);
  gotoxy(27,19);
  cprintf("%6ld",extr);
  deduc1=extr*datos_emple[t].irpf/100;

  deduc1=redondeo(deduc1);

  gotoxy(70,19);
  cprintf("%6.0f",deduc1);
  gotoxy(70,21);
  cprintf("%6.0f",deduc1);
  total_extra=extr-deduc1;
  gotoxy(70,23);
  cprintf("%6ld",total_extra);

  do {
    opcion_imp();
    elec=tolower(getch());
  } while (elec<'a' || elec>'c');

  switch(elec) {
    case 'a': {
      break;
    }

    case 'b': {
      salvar_extra(extr,deduc1,total_extra,t,nom);
      break;
    }

    case 'c': {
      salvar_extra(extr,deduc1,total_extra,t,nom);
      imprimir(nom);
      break;
    }
  }
}

salvar_nomina(contin,desem,irpf,t,nom,nocturno,plus,computable,
	      pror,cont,des,deduc,total)

  float               contin;
  float               desem;
  float               irpf;
  int                 t;
  char                nom[15];
  unsigned long int   nocturno;
  unsigned long int   plus;
  unsigned long int   computable;
  unsigned long int   pror;
  unsigned long int   cont;
  unsigned long int   des;
  unsigned long int   deduc;
  unsigned long int   total;
{

  FILE *fp;
  int u;
  char fecha_pago[15]="\0";

  gotoxy(1,25);
  delline();
  gotoxy(10,25);
  printf("Introduce la fecha de pago:");
  gets(fecha_pago);

  if((fp=fopen(nom,"w"))==NULL) {
    gotoxy(1,24);
    cprintf("No puede abrirse el archivo   (return para seguir)");
    getch();
    return (-1);
  }

  fprintf(fp,"\n\n\n\n\n\n\n\r");
  fprintf(fp,"%15s%s\n\r"," ",datos_emple[t].productor);
  fprintf(fp,"%15s%s\n\r"," ",datos_emple[t].categoria);
  fprintf(fp,"%23s%s%35s\n\r"," ",datos_emple[t].s_s,datos_emple[t].tarifa);
  fprintf(fp,"%18d%24s\n\r",datos_emple[t].matricula,datos_emple[t].alta);
  fprintf(fp,"%30s%28d\n\n\n\r",mes,dias);
  fprintf(fp,"%75ld\n\n\r",datos_emple[t].salario_base);
  fprintf(fp,"%75ld\n\n\r",datos_emple[t].plus_convenio);
  fprintf(fp,"%75ld\n\n\r",datos_emple[t].com_vol);
  fprintf(fp,"%75ld\n\n\r",nocturno);
  fprintf(fp,"%75ld\n\n\n\n\n\r",plus);
  fprintf(fp,"%75ld",computable);

  for (u=0; u<15; u++)
    fprintf(fp,"\n\r");

  fprintf(fp,"%75ld\n\n\n\r",pror);
  fprintf(fp,"%37ld     %9.3f%23.0f\n\n\r",cont,
	  datos_emple[t].comunes,contin);
  fprintf(fp,"%37ld     %9.3f%23.0f\n\n\r",des,
	  datos_emple[t].desempleo,desem);
  fprintf(fp,"%37ld     %9.3f%23.0f\n\n\n\r",computable,
	  datos_emple[t].irpf,irpf);
  fprintf(fp,"%75ld\n\n\r",deduc);
  fprintf(fp,"%75ld\n\n\n\r",total);
  fprintf(fp,"%73s",fecha_pago);

  fclose(fp);
}


salvar_extra(extr,deduc1,total_extra,t,nom)

  int                 t;
  char                nom[15];
  unsigned long int   extr;
  float               deduc1;
  unsigned long int   total_extra;
{

  FILE *fp;
  int u;
  char fecha_pago[15]="\0";

  gotoxy(1,25);
  delline();
  gotoxy(10,25);
  printf("Introduce la fecha de pago:");
  gets(fecha_pago);

  if((fp=fopen(nom,"w"))==NULL) {
    gotoxy(1,24);
    cprintf("No puede abrirse el archivo   (return para seguir)");
    getch();
    return(-1);
  }

  fprintf(fp,"\n\n\n\n\n\n\n\r");
  fprintf(fp,"%15s%s\n\r"," ",datos_emple[t].productor);
  fprintf(fp,"%15s%s\n\r"," ",datos_emple[t].categoria);
  fprintf(fp,"%23s%s%35s\n\r"," ",datos_emple[t].s_s,datos_emple[t].tarifa);
  fprintf(fp,"%18d%24s\n\r",datos_emple[t].matricula,datos_emple[t].alta);
  fprintf(fp,"%30s%28d\n\n\n\r",mes,dias);

  for (u=0; u<10; u++)
    fprintf(fp,"\n\r");

  fprintf(fp,"%75ld\n\n\n\r",extr);
  fprintf(fp,"%75ld",extr);

  for (u=0; u<22; u++)
    fprintf(fp,"\n\r");

  fprintf(fp,"%37ld     %9.3f%23.0f\n\n\n\r",extr,
	  datos_emple[t].irpf,deduc1);

  fprintf(fp,"%75.0f\n\n\r",deduc1);
  fprintf(fp,"%75ld\n\n\n\r",total_extra);
  fprintf(fp,"%73s%s",fecha_pago,"       ");

  fclose(fp);
}

void iniz_lista()
{
  int t;

  for(t=1; t<EMPLE; t++)
    *datos_emple[t].productor='\0';
    /* un nombre de longitud cero significa vacio */
}

float redondeo(valor)

float valor;

{
  if((ceil(valor)-valor)>.5)
    valor=floor(valor);
  else
    valor=ceil(valor);

  return(valor);
}

void opcion_imp(void)
{
  gotoxy(2,25);
  cprintf("Opci¢n:    (a) No salvar    (b) Salvar    (c) Salvar e Imprimir");
}

imprimir(char nom[])
{
  FILE *fp1,*fp2;
  int p,q,copias;
  char lineas1[60][85],lineas2[58][85];

  clrscr();

  if((fp1=fopen("nomina.lis","rt"))==NULL) {
    gotoxy(1,24);
    cprintf("No puede abrirse el archivo 'nomina.lis'  ( return )");
    getch();
    return(-1);
  }

  for(p=0; p<60; p++)
    fgets(lineas1[p], 81, fp1);

  fclose(fp1);

  if((fp2=fopen(nom,"rt"))==NULL) {
    gotoxy(1,24);
    cprintf("No puede abrirse el archivo '%s'  ( return )",nom);
    getch();
    return(-1);
  }

  for(p=0; p<58; p++)
    fgets(lineas2[p], 81, fp2);

  fclose(fp2);


  for(p=0; p<58; p++) {
    for(q=0; lineas1[p][q]!='\0' && lineas2[p][q]!='\0'; q++) {
      if(lineas2[p][q]!=' ' && lineas2[p][q]!='\n')
	lineas1[p][q]=lineas2[p][q];
    }
  }

  clrscr();
  gotoxy(19,10);
  cprintf("¨ N£mero de copias ? : ");
  fscanf(stdin,"%d%*c",&copias);

  for(q=0; q<copias; q++) {

    gotoxy(19,10);
    cprintf("Introduce papel para %d¦ copia.\n\r",q+1);
    gotoxy(25,12);
    cprintf("Pulsa  una tecla.");

    getch();

    clrscr();


    textcolor(RED | BLINK);
    gotoxy(25,12);
    cprintf("IMPRIMIENDO %d¦ COPIA",q+1);


    for(p=0; p<60; p++) fprintf(stdprn,"%s",lineas1[p]);
    fprintf(stdprn,"\f");

    clrscr();
    textcolor(RED);

    gotoxy(10,8);
    cprintf("Al acabar de imprimir :");

  }
}