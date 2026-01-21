/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_ecal_elem_div.c 
 *      Date:   1994/12/7
 *  Modified:   2001/06/12
 *   
 *   Purpose:    Divide too many line in element calculation routine
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"


void make_ecal_elem_div(buf,fp)
char *buf;
FILE *fp;
{
      int   first_flag;
      char *nowp;
      char *next_plus();  /* next plus returns + no hitotsu saki */
      char *next;

      nowp = buf;
      first_flag = YES;

      
      while(strlen(nowp)>LIMIT_LINE+1) {
        next = next_plus(nowp,LIMIT_LINE);
        if(next == NULL) break;   /* pittari ka atoni + ga nakereba NULL */
        *(next - 1) = '\0';    /* plus mark no ichi */
    
        if(first_flag == YES) {
          PUT(fp,"      dt = %s\n",nowp);
          first_flag = NO;
        }
        else {
          PUT(fp,"      dt=dt+%s\n",nowp);
        }
        nowp = next;
      }
      if(first_flag == YES) {
        PUT(fp,"      dt=%s\n",nowp);
      }
      else {
        PUT(fp,"      dt=dt+%s\n",nowp);
      }
  return;
} 
        
char *next_plus(s,len)
  char *s;
  int   len;
{
  /*  int plus; 
      char *plus_ptr;
      char *plus_second_ptr;


      plus_ptr = s + len;
      while(*plus_ptr != '+' && *plus_ptr != '\0') plus_ptr++;
      if(*plus_ptr == '\0') return(NULL);

      plus_second_ptr = plus_ptr+1;
      while(*plus_second_ptr != '+' &&  *plus_second_ptr != '\0') plus_second_ptr++;
      if(*plus_second_ptr == '\0') return(NULL);
 
      plus_ptr++;  
      // this function returns the pointer next to the plus address 

      return(plus_ptr); */


  char *plus_ptr;
  int   nest_counter;
  int   current_length;

  if(strlen(s) < len) {

    return(NULL);              /* formula is short enough */
    
  }

  /* initialize */
  nest_counter   = 0;
  current_length = 0;


  plus_ptr = s;

  while(1) {

    current_length++;
    
    if(*plus_ptr == '(') {
      nest_counter++;
    }
    if(*plus_ptr == ')') {
      nest_counter--;
    }

    if(*plus_ptr == '\0') {
      return(NULL);
    }

    if(current_length >= len && 
       *plus_ptr      == '+' && 
       nest_counter   ==  0     ) {
      
      return(plus_ptr+1);
    }

    plus_ptr++;
  }

  fprintf(stderr,"NEVER HAPPEN!!! (make_ecal_elem_div.c)\n");
  exit(1);

}
