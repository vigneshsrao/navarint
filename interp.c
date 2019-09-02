#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "global.h"
#include "tokens.h"
#include "parser.h"
// #include "vm.h"

// void expression()
// {
//   return;
// }


void initialise(int argc, char const *argv[])
{
  int i,fd;

  argc--;
  argv++;
  poolsize=1024;
  scope = &symtab;

  if (argc == 1)
  {
    SOURCE = 1;
  }

  if (SOURCE)
  {
    if ((fd=open(*argv,0))<0)
    {
      die("open");
    }
    if ((old_src=src=(char*)malloc(poolsize))<0)
    {
      die("malloc");
    }

    if ((i=read(fd,src,poolsize-1))<0)
    {
      die("read");
    }

    if (!(old_text=text=(long*)malloc(poolsize)))
    {
      die("malloc");
    }
  }

  if (!(stack=(val*)malloc(poolsize)))
  {
    die("malloc");
  }

  if (!(call_stack=(long*)malloc(poolsize)))
  {
    die("malloc");
  }

  if (!(data=(char*)malloc(poolsize)))
  {
    die("malloc");
  }

  memset(stack,0,poolsize);
  memset(call_stack,0,poolsize);
  memset(data,0,poolsize);

  if (SOURCE)
  {
    memset(text,0,poolsize);
    orig=text;
    text=text-1;
    src[i]='\0';
    close(fd);
  }

  sp = bp = (val*)((long)stack+poolsize);
  cs_sp = cs_bp = (long*)((long)call_stack+poolsize);
  ax.type = 0;
  ax.data = 0;
  pc = 0;

  char* tmp = src;
  src = "func else enum if return sizeof while exit open read close printf malloc memset memcmp\0";
  i = Func;
  while (i<=While)
  {
    next();
    cur->tok = i;
    i++;
  }
  // i=EXIT;
  // while (i<=MCMP)
  // {
  //   next();
  //   cur->class = Sys;
  //   cur->value = i++;
  //   // cur->type = Int;
  // }
  src=tmp;

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

}

int main(int argc, char const *argv[])
{

  initialise(argc,argv);
  // puts(src);
  program();
  // emit(EXIT);
  // puts("");
  // eval();

  return 0;
}
