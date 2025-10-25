#ifndef PROGRAM_ARENA_H
#define PROGRAM_ARENA_H

typedef struct {
  char project_name[100];
}arena;

void freeArena (arena * program_arena);

#endif // !PROGRAM_ARENA_H
