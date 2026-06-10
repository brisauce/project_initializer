#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "build/project_initializerConfig.h"

void copyFileToBuf(buffer * buff, FILE * source_fp)
{
  assert(buff->buf);
  size_t bytes_read;
  while( (bytes_read = fread(buff->buf, 1, buff->buf_size, source_fp)) > 0 )
  {
    if (bytes_read == buff->buf_size)
    {
      buff->buf_size *= 2;
      buff->buf = realloc(buff->buf, buff->buf_size);
      assert(buff->buf);
    }
  }
}
