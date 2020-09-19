/*
 * SPDX-License-Identifier: NCSA
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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *argv0;

int do_the_needful (char *filename, size_t size, int relative, int nocreate)
{
 int e;
 FILE *file;
 size_t as;
 
 if (relative)
 {  
  file=fopen(filename, "rb");
  if (file)
  {
   fseek(file,0,SEEK_END);
   as=ftell(file);
   fclose(file);
  }
  else
  {
   if (nocreate)
   {
    fprintf (stderr, "%s: %s: %s\n", argv0, filename, strerror(errno));
    return 1;
   }
   
   file=fopen(filename, "w");
   if (!file)
   {
    fprintf (stderr, "%s: %s: %s\n", argv0, filename, strerror(errno));
    return 1;
   }
   fclose(file);
   as=0;
  }
  as+=size;
 }
 else
 {
  as=size;
  file=fopen(filename, "rb");
  if (file)
  {
   fclose(file);
  }
  else
  {
   if (nocreate)
   {
    fprintf (stderr, "%s: %s: %s\n", argv0, filename, strerror(errno));
    return 1;
   }
   file=fopen(filename,"w");
   fclose(file);
  }
 }
 
 e=truncate(filename, as);
 if (e)
  fprintf (stderr, "%s: %s: %s\n", argv0, filename, strerror(errno));
 
 return e;
}

void usage (void)
{
 fprintf (stderr, 
          "%s: usage: %s [-co] [-r filename] [-s size] filename ...\n", 
          argv0, argv0);
 exit(0);
}

size_t size_by_reference (char *filename)
{
 size_t s;
 FILE *file;
 
 file=fopen(filename,"rb");
 if (!file)
 {
  fprintf (stderr, "%s: %s: %s\n", argv0, filename, strerror(errno));
  exit(1);
 }
 
 fseek(file,0,SEEK_END);
 s=ftell(file);
 fclose(file);
 return s;
}

int main (int argc, char **argv)
{
 int e;
 int c, o, r;
 size_t s;
 int szck, ock, rel;
 char *p;
 
 argv0=*argv;
 
 szck=c=o=ock=r=rel=0;
 
 while (-1!=(e=getopt(argc, argv, "cor:s:")))
 {
  switch (e)
  {
   case 'c':
    c=1;
    break;
   case 'o':
    o=1;
    break;
   case 'r':
    szck++;
    r=1;
    s=size_by_reference(optarg);
    break;
   case 's':
    szck++;
    if (*optarg=='-')
    {
     rel=-1;
     optarg++;
    }
    else if (*optarg=='+')
    {
     rel=1;
     optarg++;
    }
    s=strtoll(optarg, &p, 0);
    if (optarg==p)
    {
     fprintf (stderr, "%s: '%s' does not appear to be a size\n", 
              argv0, optarg);
     return 1;
    }
    if (*p)
    {
     ock=1;
     
     /* I am NOT accepting salesman's units. A kilobyte is 1024 bytes. */
     
     if (*p=='K') s<<=10; /* 1024 */
     if (*p=='M') s<<=20; /* 1048576 */
     if (*p=='G') s<<=30; /* 1073741824 */
     if (!p[1]) break;
     if (p[1]=='B')
      if (!p[2]) break;
     if (p[1]=='i')
      if (p[2]=='B')
       if (!p[3]) break;
     
     fprintf (stderr, "%s: '%s' does not appear to be a size multiplicand\n",
              argv0, optarg);
     return 1;
    }
    break;
   default:
    usage();
  }
 }
 
 if (!szck)
 {
  fprintf (stderr, "%s: no size specified\n", argv0);
  return 1;
 }
 
 if (o)
 {
  if (r)
  {
   fprintf (stderr, "%s: -o and -r are mutually exclusive\n", argv0);
   return 1;
  }
  if (ock)
  {
   fprintf (stderr, "%s: -o and metric suffixes are mutually exclusive\n",
            argv0);
   return 1;
  }
  s<<=9; /* 512-byte blocks */
 }
 
 if (optind==argc) usage();
 
 r=0;
 
 for (e=optind; e<argc; e++)
  r+=do_the_needful (argv[e], s, rel, c);
 
 return r;
}
