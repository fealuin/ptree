#include <stdio.h>
#include "arbol.h"

typedef struct			//estructura de matriz contiene nro de filas columnas, y puntero doble
{
	int n;
	int **m;
} matriz;


void
cargaMatrizCeros (matriz m) //llena de ceros una matriz
{
  int i, j;
  for (i = 0; i < m.n; i++)
    {
      for (j = 0; j < m.n; j++)
        m.m[i][j] = 0;
    }
}

matriz
creaMatriz (int n)	//inicializa una matriz de f filas y c columnas, con cada elemento en 0
{
printf("creando matriz de %d filas y columnas\n",n);
  int i, j;
  matriz m;
  m.n = n;
  m.m = (int**)malloc (m.n*sizeof (int*));


 
  for (i = 0; i < m.n; i++)
    {
      m.m[i] = (int *)malloc (m.n * sizeof (int));
    }
printf("antes de cargar ceros\n");
  cargaMatrizCeros (m);
  printf("matriz creada\n");
  return m;
}





matriz
leeMatriz (char archivo[20])	//lee matriz desde archivo separado por espacios
{
  printf("iniciandooo\n");
  matriz m=creaMatriz(9);
printf("creando matriz\n");
  FILE *fp;
  fp = fopen (archivo, "r");
  char line[1000];
  char *res = malloc (100);
  res = NULL;
  int i, nline=0;
  int n;
  if (!fp)
    {
      printf ("No se encuentra archivo [%s], no se cargan datos\n", archivo);

      return creaMatriz (0);
    }

  while (fgets (line, sizeof (line), fp))
printf("leyndo linea %s\n",line);
    {
printf("entrando a leer linea\n");
     res = strtok (line, " ");
	   nline=atoi(res);
     res=strtok (NULL, " ");
printf("nro de id:%d\n", nline);
	while (res!=NULL)
	{
printf("leyendo linea %d\n",nline);
	  m.m[nline][atoi (res)] = 1;
	  res = strtok (NULL, " ");
	}
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


int main(){
	printf("Numero %d\n",N);
  matriz M=leeMatriz("../build/pt");
  imprimir(M);
}
