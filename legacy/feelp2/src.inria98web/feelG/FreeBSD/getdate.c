/*
 *  getdat.c function for UNIX system to get current date by 'date' command
 *
 *  Date          1997/10/09 16:30
 *  Programmed by Hidehiro FUJIO
 *
 *  It returns character*16 pointer, and this is allocated local memory
 *  in this file.
 *
 */ 


#include <stdio.h>
#include <stdlib.h>


/* Format 
   1234567890123456X  
   1965/09/11 17:45   */

void getdate_(datebuf)        /* Returns 16byte string */
char *datebuf;
{
  FILE *pfp;
  char  buf[BUFSIZ];

  char  whatday[11];
  char  month[11];
  int   imonth;
  int   day;
  char  time[11];
  char  timezone[11];
  int   year;

  int   ret;


  /* use date command to get date */
  pfp = (FILE *)popen("date","r");
  fgets(buf,sizeof(buf),pfp);
  ret = pclose(pfp);


  if(pfp == NULL || ret != 0) {
    sprintf(datebuf,"----/--/-- --:--");
    return;
  }


  /* Read buffer */
  sscanf(buf,"%s %s %d %s %s %d",whatday,month,&day,time,timezone,&year);



  /*  Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec */
  switch(month[0]) {
  case 'J': 
    if(month[1] == 'a') {
      imonth = 1;
    }
    else if(month[2] == 'n') {
      imonth = 6;
    }
    else {
      imonth = 7;
    }
    break;

  case 'F':
    imonth = 2;
    break;

  case 'M':
    if(month[2] == 'r') {
      imonth = 3;
    }
    else {
      imonth = 5;
    }
    break;

  case 'A':
    if(month[1] == 'p') {
      imonth = 4;
    }
    else {
      imonth = 8;
    }
    break;

  case 'S':
    imonth = 9;
    break;

  case 'O':
    imonth = 10;
    break;
    
  case 'N':
    imonth = 11;
    break;
    
  case 'D':
    imonth = 12;
    break;

  }

  /* time */
  time[5] = '\0';

  /*   Again, the format is
       1234567890123456X  
       1965/09/11 17:45     */
  
  sprintf(datebuf,"%4d/%2d/%2d %s",year,imonth,day,time);


  /* add 0 if space in month and day */
  if(*(datebuf+5) == ' ') *(datebuf+5) = '0';
  if(*(datebuf+8) == ' ') *(datebuf+8) = '0';

  /* return */
  return;
}
