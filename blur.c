#include <stdio.h>

/* P6
 * width height
 * max_value (255)
 * RGBRGBRGB... row major order
 */

#define BUF_SIZE  256
#define MAX_DIMEN 1020
int image[MAX_DIMEN][MAX_DIMEN][3];
int outimage[MAX_DIMEN][MAX_DIMEN][3];

int main() {
  FILE *fp = fopen("image.ppm", "r");
  int i, j, k, l, m, width, height, depth;
  char buf[BUF_SIZE];
  fgets(buf, BUF_SIZE, fp); /* read P6 */
  fgets(buf, BUF_SIZE, fp); /* read width height */
  sscanf(buf, "%d%d", &width, &height);
  fgets(buf, BUF_SIZE, fp); /* read depth */
  sscanf(buf, "%d", &depth);

  /* read pixel by pixel */
  for (i=0; i<height; i++)
    for (j=0; j<width; j++)
      for (k=0; k<3; k++) {
	image[i][j][k] = fgetc(fp);
      }
  fclose(fp);

  /* blur */
  for (i=1; i<(height-1); i++)
    for (j=1; j<(width-1); j++)
      for (k=0; k<3; k++) {
	/* blur [i][j][k]:
	   look at [i-1][j-1][k]
	   [i-1][j][k]
	   [i-1][j+1][k]
	   ...
	   [i+1][j+1][k]
	*/
	for (l=i-1;l<i+2;l++)
	  for (m=j-1; m<j+2; m++)
	    outimage[i][j][k] += image[l][m][k];
	outimage[i][j][k] /= 9;
      }

  fp = fopen("output.ppm", "w");
  fprintf(fp, "P6\n%d %d\n%d\n", width, height, depth);
  for (i=0; i<height; i++)
    for (j=0; j<width; j++)
      for (k=0; k<3; k++)
	fputc(outimage[i][j][k], fp);

  fclose(fp);
  

  return 0;
}
