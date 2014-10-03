#include <stdio.h>
#include "arbol.h"
#include <string.h>

typedef struct			//estructura de matriz contiene nro de filas columnas, y puntero doble
{
  int n;
  int **m;
  int inicial;
} matriz;


void
cargaMatrizCeros (matriz m)	//llena de ceros una matriz
{
  int i, j;
  for (i = 0; i < m.n; i++)
    {
      for (j = 0; j < m.n; j++)
	m.m[i][j] = 0;
    }
}

matriz
creaMatriz (int n)		//inicializa una matriz de f filas y c columnas, con cada elemento en 0
{
  printf ("creando matriz de %d filas y columnas\n", n);
  int i, j;
  matriz m;
  m.n = n;
  m.m = (int **) malloc (m.n * sizeof (int *));



  for (i = 0; i < m.n; i++)
    {
      m.m[i] = (int *) malloc (m.n * sizeof (int));
    }
  printf ("antes de cargar ceros\n");
  cargaMatrizCeros (m);
  printf ("matriz creada\n");
  return m;
}

int
getMax(char archivo[20]){

	FILE *fp;
	fp = fopen (archivo, "r");
	char line[1000];
  char *res;
  res = NULL;
  int max=0;
  char delim[2] = " ";
  if (!fp)
    {
      printf ("No se encuentra archivo [%s], no se cargan datos\n", archivo);

      return 0;
    }
  while (fgets (line, sizeof (line), fp))
    {
      res = strtok (line, delim);
      while (res != NULL)
				{
	  			if (max<atoi(res))
	  			{
	  				max=atoi(res);
	  			}
	  			res = strtok (NULL, delim);
	}
    }
return max;
}


matriz
leeMatriz (char archivo[20])	//lee matriz desde archivo separado por espacios
{
  printf ("iniciandooo\n");
  matriz m = creaMatriz (getMax(archivo)+1);
  printf ("creando matriz\n");
  FILE *fp;
  fp = fopen (archivo, "r");
  char line[1000];
  char *res;
  res = NULL;
  char delim[2] = " ";
  int i, nline = 0, count = 0;
  int n;
  if (!fp)
    {
      printf ("No se encuentra archivo [%s], no se cargan datos\n", archivo);

      return creaMatriz (0);
    }


  while (fgets (line, sizeof (line), fp))
    {
      printf ("%s\n", line);
      res = strtok (line, delim);
      printf ("%s\n", res);
      nline = atoi (res);
      if (count==0)
      {
      	m.inicial=nline;
      }
      printf ("nline %d\n", nline);
      res = strtok (NULL, delim);

      printf ("nro de id:%d\n", nline);
      while (res != NULL)
				{
	  			printf ("leyendo linea %d\n", nline);
	  			m.m[nline][atoi (res)] = 1;
	  			res = strtok (NULL, delim);
	}
	count++;
    }


  fclose (fp);
  return m;
}


void
imprimir (matriz m)		//imprime matriz por pantalla
{
  int i, j;
  for (i = 0; i < m.n; i++)
    {
      for (j = 0; j < m.n; j++)
			{
	  		printf ("%10d ", (int) m.m[i][j]);
			}
      printf ("\n");

    }
  printf ("\n");
}


int
main ()
{
  printf ("Numero %d\n", N);
  matriz M = leeMatriz ("../build/pt");
  imprimir (M);
printf("%d\n",M.inicial );
}
