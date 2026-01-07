int stringLength(const char *s)
{
   int length = 0;

   while(*s) {
     s++;
     length++;
   }
   return(length);
}
