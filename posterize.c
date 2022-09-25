/*-
 * Copyright (c) 2022 Michael Roe
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpng/png.h>

int main(int argc, char **argv)
{
FILE *f1;
FILE *red_file;
FILE *blue_file;
FILE *black_file;
FILE *white_file;
FILE *grey_file;
FILE *brown_file;
FILE *other_file;
char buff[80];
int width;
int height;
int depth;
int i;
unsigned char pixel[3];
unsigned char pixel_out[3];
double r, g, b;
double intensity;
int is_red;
int is_blue;
int is_black;
int is_white;
int is_grey;
int is_brown;
int alpha;


  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return -1;
  }

  f1 = fopen(argv[1], "r");
  if (f1 == NULL)
  {
    fprintf(stderr, "Couldn't open %s\n", argv[1]);
    return -1;
  }

  fgets(buff, sizeof(buff), f1);
  if (strcmp(buff, "P6\n") != 0)
  {
    fprintf(stderr, "%s is not a PPM file.\n", argv[1]);
    return 0;
  }

  fgets(buff, sizeof(buff), f1);
  sscanf(buff, "%d %d", &width, &height);

  fgets(buff, sizeof(buff), f1);
  sscanf(buff, "%d", &depth);

  red_file = fopen("red.ppm", "w");
  fprintf(red_file, "P6\n");
  fprintf(red_file, "%d %d\n", width, height);
  fprintf(red_file, "%d\n", depth);

  blue_file = fopen("blue.ppm", "w");
  fprintf(blue_file, "P6\n");
  fprintf(blue_file, "%d %d\n", width, height);
  fprintf(blue_file, "%d\n", depth);

  black_file = fopen("black.ppm", "w");
  fprintf(black_file, "P6\n");
  fprintf(black_file, "%d %d\n", width, height);
  fprintf(black_file, "%d\n", depth);

  white_file = fopen("white.ppm", "w");
  fprintf(white_file, "P6\n");
  fprintf(white_file, "%d %d\n", width, height);
  fprintf(white_file, "%d\n", depth);

  grey_file = fopen("grey.ppm", "w");
  fprintf(grey_file, "P6\n");
  fprintf(grey_file, "%d %d\n", width, height);
  fprintf(grey_file, "%d\n", depth);

  brown_file = fopen("brown.ppm", "w");
  fprintf(brown_file, "P6\n");
  fprintf(brown_file, "%d %d\n", width, height);
  fprintf(brown_file, "%d\n", depth);

  other_file = fopen("other.pam", "w");
  fprintf(other_file, "P7\n");
  fprintf(other_file, "WIDTH %d\n", width);
  fprintf(other_file, "HEIGHT %d\n", height);
  fprintf(other_file, "DEPTH 4\n");
  fprintf(other_file, "MAXVAL 255\n");
  fprintf(other_file, "TUPLTYPE RGB_ALPHA\n");
  fprintf(other_file, "ENDHDR\n");


  for (i=0; i<width*height; i++)
  {
    fread(pixel, 1, 3, f1);
    r = (double) pixel[0];
    g = (double) pixel[1];
    b = (double) pixel[2];
    intensity = (r + g + b)/3.0;

    if ((intensity < 30) || (r < 1.2*intensity))
    {
      memset(pixel_out, 255, 3);
      is_red = 0;
    }
    else
    {
      memcpy(pixel_out, pixel, 3);
      is_red = 1;
    }
    fwrite(pixel_out, 1, 3, red_file);

    if (is_red || (intensity < 90) || (b < 1.15*intensity))
    {
      memset(pixel_out, 255, 3);
      is_blue = 0;
    }
    else
    {
      memcpy(pixel_out, pixel, 3);
      is_blue = 1;
    }
    fwrite(pixel_out, 1, 3, blue_file);

    if (is_red || is_blue || (intensity >= 130.0))
    {
      memset(pixel_out, 255, 3);
      is_black = 0;
    }
    else
    {
      memcpy(pixel_out, pixel, 3);
      is_black = 1;
    }
    fwrite(pixel_out, 1, 3, black_file);

    if ((r < 230) || (g < 240) || (b < 209))
    {
      memset(pixel_out, 255, 3);
      is_white = 0;
    }
    else
    {
      memcpy(pixel_out, pixel, 3);
      is_white = 1;
    }
    fwrite(pixel_out, 1, 3, white_file);

    if (is_black || is_red || is_blue || is_white || (intensity < 150) || (r + g > b + b))
    {
      memset(pixel_out, 255, 3);
      is_grey = 0;
    }
    else
    {
      memcpy(pixel_out, pixel, 3); 
      is_grey = 1;
    }
    fwrite(pixel_out, 1, 3, grey_file);

    if (is_black || is_red || is_blue || is_white || is_grey || (intensity < 150))
    {
      memset(pixel_out, 255, 3);
      is_brown = 0;
    }
    else
    {
      memcpy(pixel_out, pixel, 3);
      is_brown = 1;
    }
    fwrite(pixel_out, 1, 3, brown_file);

    if (is_red || is_blue || is_white || is_grey || is_brown)
    {
      memset(pixel_out, 0, 3);
      alpha = 255;
      pixel_out[0] = 255; /* random() & 0xff; */ /* 241; */
      pixel_out[1] = 255; /* random() & 0xff; */ /* 244; */
      pixel_out[2] = 255; /* random() & 0xff; */ /* 217; */
    }
    else
    {
      alpha = 255;
      memcpy(pixel_out, pixel, 3);
    }
    fwrite(pixel_out, 1, 3, other_file);
    fputc(alpha, other_file);
  }
  fclose(f1);
  fclose(red_file);
  fclose(blue_file);
  fclose(black_file);
  fclose(white_file);
  fclose(grey_file);
  fclose(brown_file);
  fclose(other_file);
  return 0;
}
