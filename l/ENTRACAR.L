#define ESC 27

/*******************          ENTRACAR.L      ***********************/


/********************************************************************/
/*            Funci¢n de pedir datos por pantalla                   */
/*       Esta funci¢n sirve para cadenas de caracteres. Pone una    */
/*       cadena por defecto. Admite flechas izda. y dcha.           */
/*                                                                  */
/*         char *Entracar(int columna, fila, fondo, tinta,          */
/*			  numero_caracteres, char *literal)         */
/********************************************************************/

char *Entracar(int columna,int fila,int fondo,int tinta,
	       int numero_caracteres, char *literal)
{
  int atributo,contador,tecla,offset,control,ultimo_caracter;
  char cadena[80];

  atributo = (fondo<<4)|tinta;
  control=0;

  for(contador=columna; contador<(numero_caracteres+columna); contador++)
    {
      Video(contador,fila,fondo,tinta,1,"_");
    }
  Video(columna,fila,fondo,tinta,strlen(literal),literal);

  contador=0;
  ultimo_caracter=strlen(literal);
  strcpy(cadena,literal);

  while(control!=1) {
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
		   Video(columna,fila,fondo,tinta,1,"_");
		   cadena[contador]=0x00; /* finalizador de cadena */
		 }
	       break;
	       }

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
		 break;
	       }
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

  return(cadena);
}


/**********************************************************************/
/* Para usar esta funci¢n hace falta definir lo siguiente             */
/* #define ESC 27                                                     */
/**********************************************************************/
