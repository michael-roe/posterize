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
#include <math.h>

int main(int argc, char **argv)
{
  FILE *f1;
  int i;
  int j;
  int height = 512;
  int width = 512;
  int depth = 255;
  double s60;
  double blue_yellow;
  double green_red;
  int r, g, b;

  f1 = fopen("picker2.ppm", "w");

  fprintf(f1, "P6\n");
  fprintf(f1, "%d %d\n", width, height);
  fprintf(f1, "%d\n", depth);

  s60 = sin(60.0*M_PI/180.0);

  for (i=0; i<height; i++)
  {
    for (j=0; j<width; j++)
    {
      blue_yellow = ((double) (256 - i))*0.75/128.0;
      green_red = ((double) (j - 256))*0.75/(128.0*s60);

      if ((blue_yellow < -0.75) || (blue_yellow > 0.75) ||
        (green_red < -1.0) || (green_red > 1.0))
      {
        fprintf(f1, "%c%c%c", 128, 128, 128);
      }
      else
      {
        r = (int) 256.0*(0.5 - 0.5*green_red - (1.0/3.0)*blue_yellow);
	g = (int) 256.0*(0.5 + 0.5*green_red - (1.0/3.0)*blue_yellow);
	b = (int) 256.0*(0.5 + (2.0/3.0)*blue_yellow);

	if ((r < 0) || (r > 255) || (g < 0) || (g > 255) || (b < 0) || (b > 255))
        {
          fprintf(f1,"%c%c%c", 128, 128, 128);
	}
	else
        {
          fprintf(f1,"%c%c%c", r, g, b);
	}
      }
    }
  }

  fclose(f1);

  return 0;
}

