int CstringLength( const char *str)
{
  unsigned int length = 0;

  while(*str) {
   length++;
   str++;
  }

  return(length);
}
