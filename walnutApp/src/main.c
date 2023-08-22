/**
 * Copyright (C) 2023 Devin Rockwell
 *
 * walnut is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * walnut is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with walnut. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdio.h>
#include <walnut/debug.h>
#include <walnut/walnut.h>

typedef struct
{
  size_t len;
  uint64_t *contents;
} File;

File
readfile(const char *fileName)
{
  FILE *fd = fopen(fileName, "rb");
  if (!fd)
    {
      fprintf(stderr, "ERROR: cannot open file for reading: %s\n", fileName);
      exit(EXIT_FAILURE);
    }
  fseek(fd, 0, SEEK_END);
  long len = ftell(fd);
  rewind(fd);

  File file;
  file.len      = len / 8;
  file.contents = malloc(len);
  if (!file.contents)
    {
      fprintf(stderr, "ERROR: cannot allocate space for file\n");
      exit(EXIT_FAILURE);
    }
  const int one = 1;

  if (*(char *)&one == 1)
    {
      uint8_t *temp = malloc(len);
      if (!temp)
        {
          fprintf(stderr, "ERROR: cannot allocate space for file\n");
          exit(EXIT_FAILURE);
        }
      fread(temp, 1, len, fd);
      for (int i = 0; i < len / 8; i++)
        {
          file.contents[i] = (uint64_t)temp[i * 8 + 7]
                             | (uint64_t)temp[i * 8 + 6] << 8
                             | (uint64_t)temp[i * 8 + 5] << 16
                             | (uint64_t)temp[i * 8 + 4] << 24
                             | (uint64_t)temp[i * 8 + 3] << 32
                             | (uint64_t)temp[i * 8 + 2] << 40
                             | (uint64_t)temp[i * 8 + 1] << 48
                             | (uint64_t)temp[i * 8 + 0] << 56;
        }
      free(temp);
    }
  else
    {
      fread(file.contents, 8, len, fd);
    }

  fclose(fd);
  return file;
}

int
main(int argc, const char **argv)
{
  if (argc != 2)
    {
      fprintf(stderr, "Usage: walnut [path]\n");
      return EXIT_FAILURE;
    }
  File file = readfile(argv[1]);
  Walnut walnut;
  walnutInit(&walnut, file.contents, file.len);
  walnutDisassemble(file.contents, file.len);
  walnutRun(&walnut);
  walnutDumpRegisterFile(&walnut);
  walnutFree(&walnut);

  free(file.contents);
  return 0;
}