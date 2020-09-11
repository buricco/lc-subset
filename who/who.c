/*
 * SPDX-License-Identifier: NCSA
 * 
 * who(1) - display who is on the system
 * 
 * Copyright 2020 S. V. Nickolas.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal with the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimers.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimers in the 
 *      documentation and/or other materials provided with the distribution.
 *   3. Neither the names of the authors nor the names of contributors may be
 *      used to endorse or promote products derived from this Software without
 *      specific prior written permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS WITH THE SOFTWARE.
 */

/*
 * This implementation has Down's syndrome.
 */

#include <sys/stat.h>
#include <errno.h>
#include <utmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static char *argv0;

int do_who (char *filename, int meonly, int showidle, int header, 
            int writable, int type)
{
 FILE *file;
 struct utmp utmp;
 struct tm *tm;
 time_t ttime;
 char datebuf[20];
 char *mytty, *p;
 struct stat s;

 if (header)
 {
  printf ("NAME     ");
  if (writable) printf ("  ");
  printf ("LINE         TIME             ");
  if (showidle) printf ("IDLE                  ");
  printf ("COMMENT\n");
  return 0;
 }
 
 mytty=ttyname(fileno(stdin));
 if (meonly&&(!mytty))
 {
  fprintf (stderr, "%s: could not obtain identity of controlling tty\n", 
           argv0);
  return 1;
 }
 if (!strncmp(mytty, "/dev/", 5))
  p=&(mytty[5]);
 else if (meonly)
 {
  fprintf (stderr, "%s: ttyname is bogus\n", argv0);
  return 1;
 }
 
 file=fopen(filename, "rb");
 if (!file)
 {
  fprintf(stderr, "%s: %s: %s", argv0, filename, strerror(errno));
  return 1;
 }
 while (1)
 {
  if (!(fread(&utmp, sizeof(utmp), 1, file))) break;
  
  ttime=utmp.ut_tv.tv_sec;
  
  if (utmp.ut_type!=type) continue;
  if (meonly)
   if (strcmp(p,utmp.ut_line)) continue;

  tm=localtime(&ttime);
  if (!tm)
  {
   fprintf (stderr, "%s: %s: bogus time\n", argv0, filename);
   continue;
  }
  strftime(datebuf, 19, "%F %R", tm);
  printf ("%-8s ", utmp.ut_name);
  if (writable)
  {
   char *b;
   
   b=malloc(UT_LINESIZE+6);
   if (!b) /* SCRAM! */
   {
    fprintf (stderr, "%s: out of memory\n", argv0);
    fclose(file);
    return 1;
   }
   sprintf(b,"/dev/%s",utmp.ut_line);
   if (stat(b, &s))
    fputc ('?', stdout);
   else
    fputc ((s.st_mode&0020)?'+':'-', stdout);
   fputc(' ',stdout);
   free(b);
  }
  printf ("%-12s %s ", (type==RUN_LVL)?utmp.ut_id:utmp.ut_line, datebuf);
  if (showidle)
  {
   char *b;
   
   b=malloc(UT_LINESIZE+6);
   if (!b) /* SCRAM! */
   {
    fprintf (stderr, "%s: out of memory\n", argv0);
    fclose(file);
    return 1;
   }
   sprintf(b,"/dev/%s",utmp.ut_line);
   if (stat(b, &s))
   {
    fprintf (stderr, "%s: stat failed on %s: %s\n", 
             argv0, b, strerror(errno));
   }
   else
   {
    long idle;
    int m,h,d;
    
    idle=time(0)-s.st_atim.tv_sec;
    d=idle/86400;
    h=(idle%86400)/3600;
    m=(idle%3600)/60;
    printf ("%5u days, %2u:%02u:%02u  ", d,h,m,idle%60);
   }
   free(b);
  }
  printf  ("(%s)\n", utmp.ut_host);
 }
 fclose(file);
 return 0;
}

void usage (void)
{
 fprintf (stderr, "%s: usage: %s [-abdHlmprstTu] [file]\n"
                  "%s: usage: %s -q [file]\n"
                  "%s: usage: who am i\n", argv0, argv0, argv0, argv0, argv0);
 exit(1);
}

int main (int argc, char **argv)
{
 int e;
 int b,d,H,l,m,p,r,s,t,T,u;
 int q;
 
 char *utmpfile="/var/run/utmp";

 argv0=argv[0];

 b=d=H=l=m=p=r=t=T=u=0;
 s=2;
 q=0;

 /*
  * Traditionally, this would take any combination of two parameters,
  * but that would require endrunning around getopt().
  * Instead, take the strict approach and ONLY support the specific pairings
  * "am i" and "am I", which POSIX requires.
  * 
  * Thus, treat these pairings as equivalent to "who -m".
  */ 
 
 if (argc==3)
 {
  if (!strcmp(argv[1],"am"))
   if (!strcasecmp(argv[2], "i"))
    return do_who(utmpfile,m,0,0,0,USER_PROCESS);
 }
 
 while (-1!=(e=getopt(argc, argv, "abdHlmpqrstTu")))
 {
  switch (e)
  {
   case 'a':
    b=d=l=p=r=s=t=T=u=1;
    break;
   case 'b':
    b=1;
    break;
   case 'd':
    d=1;
    break;
   case 'H':
    H=1;
    break;
   case 'l':
    l=1;
    break;
   case 'm':
    m=1;
    break;
   case 'p':
    p=1;
    break;
   case 'q':
    q=1;
    break;
   case 'r':
    r=1;
    break;
   case 's':
    s=1;
    break;
   case 't':
    t=1;
    break;
   case 'T':
    T=1;
    break;
   case 'u':
    u=1;
    break;
   default:
    usage();
  }
 }

 if (argc-optind>1) usage();
 if (argc-optind) utmpfile=argv[optind];
 
 if (s==2)
 {
  if (b||d||l||p||r||t) s=0;
 }
 
 e=0;

 if (H) do_who(0,0,u,1,T,0);
 if (b) e+=do_who(utmpfile,m,u,0,T,BOOT_TIME); 
 if (d) e+=do_who(utmpfile,m,u,0,T,DEAD_PROCESS);
 if (l) e+=do_who(utmpfile,m,u,0,T,LOGIN_PROCESS);
 if (p) e+=do_who(utmpfile,m,u,0,T,INIT_PROCESS);
 if (r) e+=do_who(utmpfile,m,u,0,T,RUN_LVL);
 if (t) e+=do_who(utmpfile,m,u,0,T,NEW_TIME);
 if (s) e+=do_who(utmpfile,m,u,0,T,USER_PROCESS);
 
 return e;
}
