#include <stdio.h>
#include <stdlib.h>

#include "program_arena.h"
#include "check_overwrite.h"

void genDebugScript(arena * program_arena) 
{
  char * filename = "debug.sh";

  if (!canOverwrite(filename))
  {
    return;
  }

  FILE * fp = fopen(filename, "w");

  if (!fp)
  {
    printf("[%-20s] ERROR: failed to open file. Exiting", __func__);
    freeArena(program_arena);
    exit(EXIT_FAILURE);
  }

  fprintf(fp, "\
#!/usr/bin/sh\n\
PROGRAM_NAME=\"%s\"\n\
\n\
\n\
run_gdbgui() {\n\
  gdbgui -g \"gdb --q\" --args ./$PROGRAM_NAME\n\
}\n\
\n\
\n\
cd build\n\
\n\
if [ -e $PROGRAM_NAME ]; then\n\
  run_gdbgui\n\
else\n\
  echo \"$PROGRAM_NAME not found. please run configure.sh then build.sh\"\
fi", program_arena->project_name);

  fclose(fp);
}

