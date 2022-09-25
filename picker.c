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

#define CHANNEL_RED 1
#define CHANNEL_GREEN 2
#define CHANNEL_BLUE 3

/*
 * Creates a PPM file containing a colour picker with chroma on the
 * horizontal axis and intensity on the vertical axis. A cut-off line
 * of constant HSI saturation is shown; this will be a straight line
 * in (chroma, intensity) space.
 */

int main(int argc, char **argv)
{
  FILE *f1;
  int width = 512;
  int height = 512;
  int depth = 255;
  int i;
  int j;
  int r;
  int g;
  int b;
  int t;
  double intensity;
  double chroma;
  double saturation;
  int channel = CHANNEL_BLUE;
  double threshold = -0.4;

  f1 = fopen("picker.ppm", "w");

  fprintf(f1, "P6\n");
  fprintf(f1, "%d %d\n", width, height);
  fprintf(f1, "%d\n", depth);

  for (i=0; i<height; i++)
  {
    for (j=0; j<width; j++)
    {
      intensity = (double) (256 + 128 - i);
      chroma = (double) 2*(j - 256);
      if ((intensity < 0.0) || (intensity >= 256.0)
        || (chroma < -256.0) || (chroma > 256.0))
      {
        r = 64;
	g = 64;
	b = 64;
      }
      else
      {
        r = (int) floor(intensity + chroma*2.0/3.0);
	g = (int) floor(intensity - chroma*1.0/3.0);
	b = g;
	if ((r < 0) || (r > 255) || (g < 0) || (g > 255))
        {
          r = 64;
	  g = 64;
	  b = 64;
	}
	else
	{
	  saturation = 1.0 - ((double) g)/intensity;
	  /* if ((double) r < threshold*intensity) */
	  if (saturation < threshold)
	  {
	    r = 256;
	    g = 256;
	    b = 256;
  	  }
        }
      }
      switch (channel)
      {
        case CHANNEL_RED:
	  break;
	case CHANNEL_GREEN:
	  t = g;
	  g = r;
	  r = t;
	  break;
	case CHANNEL_BLUE:
	  t = b;
	  b = r;
	  r = t;
	  break;
      }
      fprintf(f1, "%c%c%c", r, g, b);
    }
  }

  fclose(f1);
  return 0;
}
