#include <stdlib.h>

#include "program_arena.h"
void freeArena (arena * program_arena)
{
  //  Free other struct members here
  

  //  Free pointer
  
  free(program_arena);

}
