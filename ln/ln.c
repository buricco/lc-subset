/*
 * ln(1) - link files
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
 * System V Unix will delete an existing link before creating a new one, by
 * default.  This behavior is bogus, braindead and dangerous and will not be 
 * implemented.
 */

#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * -f Delete an existing link silently before initiating link call
 * -s Generate a symbolic link, not a hard link
 * -L Enable using realpath before initiating link call
 * -P Disable using realpath before initiating link call
 */

static char *argv0;

static char buf1[PATH_MAX];
static char buf2[PATH_MAX];

void usage (void)
{
 fprintf (stderr, "%s: usage: %s [-fs] [-L | -P] source target\n"
                  "%s: usage: %s [-fs] [-L | -P] source ... target_dir\n",
          argv0, argv0);
 exit(1);
}

int main (int argc, char **argv)
{
 struct stat sb;
 char *target;
 int e, f, s, L, r, t;
 
 argv0=argv[0];
 
 e=0;
 f=s=L=0;
 while (-1!=(e=getopt(argc, argv, "fsLP")))
 {
  switch (e)
  {
   case 'f':
    f=1;
    break;
   case 's':
    s=1;
    break;
   case 'L':
    L=1;
    break;
   case 'P':
    L=0;
    break;
   default:
    usage();
  }
 }
 
 if ((argc-optind)<2) usage();
 target=argv[argc-1];
 
 e=0;
 if ((argc-optind)==2)
 {
  /* See if target exists and is a directory. */
  e=stat(target,&sb);
  if (e) /* for example, if the file doesn't exist */
   r=0;
  else
   r=(!(sb.st_mode & S_IFDIR));
  
  /* Not a directory, so go ahead. */
  if (r)
  {
   if (L)
   {
    if (!realpath(argv[optind], buf1))
    {
     perror(argv[optind]);
     return 1;
    }
   }
   else
    strcpy(buf1, argv[optind]);
  
   /* Silently attempt to unlink the target. */
   if (f) unlink(target);
  
   /* Generate the appropriate type of link. */
   if (s)
    e=symlink(buf1, target);
   else
    e=link(buf1, target);
  
   if (e) perror(target);

   return e;
  }
 }
 
 e=0;
 for (t=optind; t<(argc-1); t++)
 {
  char *p;
  
  /* Create actual target filename. */
  p=strrchr(argv[t], '/');
  if (p) p++; else p=argv[t];
  memset(buf2, 0, PATH_MAX);
  snprintf(buf2, PATH_MAX-1, "%s/%s", target, p);
  
  /* Same process as above. */
  if (L)
  {
   if (!realpath(argv[t], buf1))
   {
    perror(argv[t]);
    continue;
   }
   else
    strcpy(buf1, argv[t]);
   
   if (f) unlink(buf2);
   if (s)
    r=symlink(buf1, buf2);
   else
    r=link(buf1, buf2);
   
   if (r) perror(buf2);
   e+=r;
  }
 }
 
 return e;
}
