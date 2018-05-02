#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int
main (int argc, char **argv)
{
   for (int i=0; i < argc; i++)
   {
      printf ("arg %d = %s\n", i, argv[i]);
   }

   for (char **env = environ; *env != 0; env++)
   {
      printf("%s\n", *env);
   }

   exit (0);
}
