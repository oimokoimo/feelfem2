int stringLength(const char *);
int strindex(const char *,const char*);
int streq( const char *a, const char *b)
{
    if(stringLength(a) != stringLength(b)) return(0);
    return(strindex(a,b));
}
