#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readfile.h"

char *readfile(char *filename)
{
  FILE *file;
  long length;
  char *filecontent;

  file = fopen(filename, "r");

  if (file)
  {
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    filecontent = malloc(length);
    if (filecontent)
    {
      fread(filecontent, 1, length, file);
    }
  }
  fclose(file);

  return filecontent;
}
