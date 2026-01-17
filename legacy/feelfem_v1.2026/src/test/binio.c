#include <stdio.h>

static   FILE *fd;
void binopen_(char *filename,int *strlength)
{
  *(filename+*strlength) = 0;
  fprintf(stderr,"BINARY FILENAME=[%s]
",filename);

  fd = fopen(filename,"wb");
  if(fd == 0) {
    fprintf(stderr,"Cannot open file %s to binary write
",filename);
    exit(1);
  }
  return;
}

void binclose_(void)
{
  fclose(fd);
  return;
}

void binwritestr_(void *str, int *byte)
{
  int ret;
  ret = fwrite(str,1,*byte,fd);
  if(ret == 0) {
    fprintf(stderr,"binwritestr failed.
");
    exit(1);
  }
  return;
}

void binwriteint_(void *ptr)
{
  int ret;
  ret = fwrite(ptr,4,1,fd);
  if(ret == 0) {
    fprintf(stderr,"binwritestr failed.
");
    exit(1);
  }
  return;
}

void binwriteints_(void *ptr, int *times)
{
  int ret;
  ret = fwrite(ptr,4,*times,fd);
  if(ret == 0) {
    fprintf(stderr,"binwriteints failed.
");
    exit(1);
  }
  return;
}

void binwritedbls_(void *ptr, int *times)
{
  int ret;
  ret = fwrite(ptr,8,*times,fd);
  if(ret == 0) {
    fprintf(stderr,"binwriteints failed.
");
    exit(1);
  }
  return;
}
