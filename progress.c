/*
 * Copyright 2002 Leigh L. Klotz Jr. <klotz@graflex.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h> 
#include <getopt.h> 
#include <unistd.h> 
#include <malloc.h> 

#define DEFAULT_BUFSIZE (131072l)

const char *opts = "k:m:g:c:b:h";
char *buffer=NULL;
char progressChar='.';
ssize_t bufsize=DEFAULT_BUFSIZE;
ssize_t bytecounterinit=(1024l);
ssize_t bytecounter;

void usage(char *progname) {
  int i;
  fprintf(stderr, "usage: %s ", progname);
  for (i = 0; opts[i] != 0; i++) {
    fprintf(stderr, "[-%c", opts[i]);
    if (opts[i+1] == ':') {
      i++;
      fprintf(stderr, " n");
    }
    fprintf(stderr, "] ");
  }
  fprintf(stderr, "\n");
}

void help() {
  int i;
  fprintf(stderr, "Reads from standard input, buffers, and writes to standard output.  Writes a progress character at specified intervals.\n\n");
  for (i = 0; opts[i] != '\0'; i++) {
    if (opts[i] == ':') continue;
    fprintf(stderr, "-%c: ", opts[i]);
    switch(opts[i]) {
    case 'b':
      fprintf(stderr, "Sets buffer size for read and write.  Current value is %ld bytes.\n", bufsize);
      break;
    case 'c':
      fprintf(stderr, "Sets the character printed for progress.  Current value is '%c'\n", progressChar);
      break;
    case 'k':
      fprintf(stderr, "Print progress character every n kilobytes\n");
      break;
    case 'm':
      fprintf(stderr, "Print progress character every n megabytes\n");
      break;
    case 'g':
      fprintf(stderr, "Print progress character every n gigabytes\n");
      break;
    case 'h':
      fprintf(stderr, "Print this help\n");
      break;
    default:
      fprintf(stderr, "Bug: no help for option '%c'\n", opts[i]);
      break;
    }
  }
}

void getoptions(int argc, char **argv) {
  int c;
  
  while (1) {
    c = getopt(argc, argv, opts);
    if (c == -1) break;
    switch(c) {
    case 'b':
      bufsize = atol(optarg);
      break;
    case 'c':
      if (strlen(optarg) == 0) {
	usage(argv[0]);
	exit(-1);
      }
      progressChar = optarg[0];
      break;
    case 'k': 
      bytecounterinit = 1024l;
      bytecounterinit *= atol(optarg);
      break;
    case 'm':
      bytecounterinit = 1048576l;
      bytecounterinit *= atol(optarg);
      break;
    case 'g':
      bytecounterinit = 1048576l*1024l;
      bytecounterinit *= atol(optarg);
      break;
    case 'h':
      usage(argv[0]);
      help();
      exit(-1);
      break;
    default:
      fprintf(stderr, "unrecognized option: c=%c\n", c);
      usage(argv[0]);
      exit(-1);
    }
  }
}

void allocateBuffer() {
  buffer = malloc(bufsize);
  if (buffer == NULL) {
    fprintf(stderr, "failed to allocate buffer of size %l; exiting", bufsize);
    exit(-1);
  }
}

void copyOut() {
  ssize_t readcount;
  bytecounter = bytecounterinit;
  while ((readcount = read(0, buffer, bufsize)) > 0) {
    ssize_t writecount = write(1, buffer, readcount);
    if (writecount < 0) {
      perror("write failure");
      exit(-1);
    }
    if (writecount != readcount) {
      fprintf(stderr, "read %l but wrote %l; exiting", readcount, writecount);
    }
    bytecounter -= writecount;
    if (bytecounter <= 0) {
      fputc(progressChar, stderr);
      bytecounter = bytecounterinit;
    }
    fflush(stderr);
  }
  if (readcount < 0) {
    perror("read failure");
    exit(-1);
  }
  fputc('\n', stderr);
}

int main(int argc, char **argv) {
  char *buffer;
  getoptions(argc, argv);
  allocateBuffer();
  copyOut();
}
