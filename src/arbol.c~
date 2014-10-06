#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct			//estructura de matriz contiene nro de filas columnas, y puntero doble
{
  int n;
  int **m;
  int inicial;
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
creaMatriz (int n)		//inicializa una matriz de n filas y n columnas, con cada elemento en 0
{
  int i, j;
  matriz m;
  m.n = n;
  m.m = (int **) malloc (m.n * sizeof (int *));

  for (i = 0; i < m.n; i++)
    {
      m.m[i] = (int *) malloc (m.n * sizeof (int));
    }
  cargaMatrizCeros (m);
  return m;
}

int
getMax (char archivo[20])	//selecciona el id de proceso mayor presente en el archivo
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
      printf ("No se encuentra archivo \"%s\", no se cargan datos\n",
	      archivo);
      exit (1);
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

matriz
leeMatriz (char archivo[20])	//lee matriz desde archivo separado por espacios
{
  matriz m = creaMatriz (getMax (archivo) + 1);
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
      res = strtok (line, delim);
      nline = atoi (res);
      if (count == 0)
	{
	  m.inicial = nline;
	}
      res = strtok (NULL, delim);

      while (res != NULL)
	{

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
creaProc (proc new, int id, int padre)	//crea un proceso hijo + pipe desde el proceso padre
{
  if (padre == new.id && new.id != id)	//Si el proceso no es el que buscamos no hace nada
    {
      pipe (new.pipePH);
      new.hpid = fork ();
      new.pid = getpid ();

      if (new.hpid > 0)		//Si es el padre cierra pipe lectura y escribe acumulación de pids
	{
	  close (new.pipePH[0]);
	  write (new.pipePH[1], &new.acPid, sizeof (new.acPid));
	  return new;
	}
      if (new.hpid == 0)	//Si es hijo actualiza id, cierre pipe de escritura y lee acumulación de pids desde el padre
	{
	  new.id = id;
	  close (new.pipePH[1]);
	  read (new.pipePH[0], &new.acPid, sizeof (new.acPid));
	  new.acPid = new.acPid + getpid ();
	  return new;
	}
    }
  else
    return new;
}


int
creaArbol (char *nArchivo)	//Crea arbol de procesos a partir de un archivo de texto
{
  int i, j;
  matriz M = leeMatriz (nArchivo);
  proc proceso;
  proceso.id = M.inicial;
  proceso.acPid = getpid ();

  for (i = 0; i < M.n; i++)
    {
      for (j = 0; j < M.n; j++)
	{
	  if (M.m[i][j] == 1)
	    {
	      proceso = creaProc (proceso, j, i);
	    }
	}
    }

  wait (0);

  printf ("Proceso %4d. PID: %5d Suma de PIDs: %10d\n", proceso.id, getpid (),
	  proceso.acPid);
}

void
modoDeUso ()
{
  printf ("Modo de uso:\n");
  printf ("arbol -f [nombre de archivo]\n");
}

int
main (int argc, char *argv[])
{
  int c;

  while ((c = getopt (argc, argv, "f:")) != -1)
    {
      switch (c)
	{
	case 'f':
	  creaArbol (optarg);
	  return 0;

	case '?':
	  if (optopt == 'f')
	    {
	      fprintf (stderr, "La opcion -%c requiere un argumento.\n",
		       optopt);
	      break;
	    }
	  else if (isprint (optopt))
	    {
	      fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
	      break;
	    }
	  else
	    {
	      fprintf (stderr, "La opcion `\\x%x'. no existe\n", optopt);
	      break;
	    }
	  modoDeUso ();
	  return 1;
	default:
	  modoDeUso ();

	  exit (1);
	}
    }
  modoDeUso ();
}
