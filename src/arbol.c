#include <stdio.h>
#include "arbol.h"
#include <string.h>

typedef struct			//estructura de matriz contiene nro de filas columnas, y puntero doble
{
  int n;
  int **m;
  int inicial;
  int *orden;
} matriz;

typedef struct
{
  int hpid;
  int id;
  int ppid;
  int pipePH[2];
  int acPid;
  int pid;
} proc;

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
//  printf ("creando matriz de %d filas y columnas\n", n);
  int i, j;
  matriz m;
  m.n = n;
  m.m = (int **) malloc (m.n * sizeof (int *));
  m.orden = (int *) malloc (m.n * sizeof (int));


  for (i = 0; i < m.n; i++)
    {
      m.m[i] = (int *) malloc (m.n * sizeof (int));
    }
 // printf ("antes de cargar ceros\n");
  cargaMatrizCeros (m);
 // printf ("matriz creada\n");
  return m;
}

int
getMax (char archivo[20])
{

  FILE *fp;
  fp = fopen (archivo, "r");
  char line[1000];
  char *res;
  res = NULL;
  int max = 0;
  char delim[2] = " ";
  if (!fp)
    {
   //   printf ("No se encuentra archivo [%s], no se cargan datos\n", archivo);

      return 0;
    }
  while (fgets (line, sizeof (line), fp))
    {
      res = strtok (line, delim);
      while (res != NULL)
	{
	  if (max < atoi (res))
	    {
	      max = atoi (res);
	    }
	  res = strtok (NULL, delim);
	}
    }
  return max;
}

/*
getOrder(matriz M){
int i;
	for (i = 0; i < M.n; ++i)
	{
		matriz.orden[i]=-1;
	}


}
*/

matriz
leeMatriz (char archivo[20])	//lee matriz desde archivo separado por espacios
{
 // printf ("iniciandooo\n");
  matriz m = creaMatriz (getMax (archivo) + 1);
 // printf ("creando matriz\n");
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
   //   printf ("%s\n", line);
      res = strtok (line, delim);
    //  printf ("%s\n", res);
      nline = atoi (res);
      if (count == 0)
	{
	  m.inicial = nline;
	}
     // printf ("nline %d\n", nline);
      res = strtok (NULL, delim);

     // printf ("nro de id:%d\n", nline);
      while (res != NULL)
	{
	  // printf ("leyendo linea %d\n", nline);
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

proc
creaProc (proc new, int id, int padre)
{

  if (padre == new.id && new.id != id)
    {


      pipe (new.pipePH);
      new.hpid = fork ();
      new.pid = getpid ();
     // printf ("%d\n", new.hpid);

      if (new.hpid > 0)
	{
	  close (new.pipePH[0]);
	  write (new.pipePH[1], &new.acPid, sizeof (new.acPid));
	  return new;
	}


      if (new.hpid == 0)
	{
	 // printf ("entrando a condicion hijo, id %d\n", id);
	  new.id = id;
	  close (new.pipePH[1]);
	  read (new.pipePH, &new.acPid, sizeof (new.acPid));
	  new.acPid = new.acPid + getpid ();
	  return new;
	}


    }
  else
    return new;
}

void
creaProcFila (proc inicial, matriz M, int fila)
{
  int i;
  for (i = 0; i < M.n; i++)
    {
      if (M.m[fila][i] == 1)
	{
	  inicial = creaProc (inicial, i, fila);
	  //printf ("Procesando fila %d columna %d\n", fila, i);
	}
    }
}



int
main ()
{
  int i, j;
  //printf ("Numero %d\n", N);
  matriz M = leeMatriz ("../build/pt");
  //imprimir (M);
  //printf ("%d\n", M.inicial);


  proc uno;

  uno.id = M.inicial;
  uno.acPid = getpid ();

  //printf ("hola, soy el proceso inical %d id %d pid %d y mi padre es %d\n",getpid (), uno.id, uno.pid, getppid ());

/*
uno=creaProc(uno,2,1);
uno=creaProc(uno,3,2);
uno=creaProc(uno,4,2);
uno=creaProc(uno,5,2);
uno=creaProc(uno,6,1);
*/
  for (i = 0; i < M.n; i++)
    {
      for (j = 0; j < M.n; j++)
	{
	  if (M.m[i][j] == 1)
	    {
	      uno = creaProc (uno, j, i);
//	      printf ("Procesando fila %d columna %d\n", i, j);
	    }
	}
    }

  wait (0);

 // printf("hola, soy el proceso %d id %d pid %d, mi padre es %d y la suma de pids es: %d\n", getpid (), uno.id, uno.pid, getppid (), uno.acPid);
  printf("Proceso %4d. PID: %5d Suma de PIDs: %10d\n", uno.id,getpid(),uno.acPid);


}
