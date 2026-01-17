/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : getdateForPsplot.cpp
 *  Date     : 1997/10/09
 *  Modified : 2001/10/26
 *  
 *  Purpose  : getdate function (for psPlot)
 *             to make independent
 *  
 */



#include <stdio.h>
#include <stdlib.h>


/* Format 
   1234567890123456X  
   1965/09/11 17:45   */

static char datebuf[17];

char *getdateForPsplot(void)        /* Returns 17byte static string */
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
    datebuf[16] = '\0';
    return(datebuf);
  }


  /* Read buffer */
  sscanf(buf,"%s %s %d %s %s %d",whatday,month,&day,time,timezone,&year);

  /*  Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec */
  switch(month[0]) {
  case 'J': 
    if(month[1] == 'a') {         /* Jan */
      imonth = 1;
    }
    else if(month[2] == 'n') {    /* Jun */
      imonth = 6;
    }
    else {
      imonth = 7;                 /* Jul */
    }
    break;

  case 'F':                       /* Feb */
    imonth = 2;
    break;

  case 'M':                       /* Mar */
    if(month[2] == 'r') {
      imonth = 3;
    }
    else {
      imonth = 5;                 /* May */
    }
    break;

  case 'A':
    if(month[1] == 'p') {         /* Apr */
      imonth = 4;
    }
    else {
      imonth = 8;                 /* Aug */
    }
    break;

  case 'S':
    imonth = 9;                   /* Sep */
    break;

  case 'O':
    imonth = 10;                  /* Oct */
    break;
    
  case 'N':
    imonth = 11;                  /* Nov */
    break;
    
  case 'D':
    imonth = 12;                  /* Dec */
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

  datebuf[16] = '\0';
  /* return */
  return(datebuf);
}
