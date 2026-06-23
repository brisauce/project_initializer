#ifndef REPLACE_WORD_H
#define REPLACE_WORD_H

#include <stdio.h>

#define REPLACE_WORD_ERROR -1
#define REPLACE_WORD_SUCCESS 1

enum copyFileStatus {
  COPYFILE_SUCCESS,
  COPYFILE_ERROR
};

enum copyFileStatus copyFile(FILE * src, long src_ptr, FILE * dest, long dest_ptr);

#endif
