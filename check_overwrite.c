#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool canOverwrite (char * filename)
{
  //  returns true if able to overwrite, false if not
  FILE * fp = fopen(filename, "r");

  if (!fp)
  {
    return true;
  }

  printf("WARNING: file %s already exists in this directory. Would you like to overwrite it?\n[Y]es/[N]o: ", 
         filename);

  char buffer[10] = {'\0'};

  do {

    if (buffer[0] != '\0')
    {
      printf("\nSorry, try again.\n[Y]es/[N]o: ");
    }

    if (!fgets(buffer, sizeof(buffer), stdin))
    {
      puts("Failed to read terminal input. Exiting.");
      exit(EXIT_FAILURE);
    }

  } while (buffer[0] != 'y' && buffer[0] != 'Y' && buffer[0] != 'n' && buffer[0] != 'N');

  //  The difference between the upper and lower case ascii chars is 32.
  //  The OR of either an upper or lower case letter and 32 is the lower 
  //  case version of that letter.

  buffer[0] |= 32;

  printf("Chose %s overwrite file %s.\n", (buffer[0] == 'y')? "to" : "not to", filename);
  //  The first element of buffer will either be y or n at this point. Ergo, if it is y, it can be 
  //  overwritten, otherwise it cannot.

  return buffer[0] == 'y';
}

