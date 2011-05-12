/* loggeredirect.cpp 
  redirects stdin to a logger.
  On Linux, install log4c and compile with:
    gcc -std=c99 logredirect.c -llog4c -o logredirect

  On Windows, create a project.
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "log4c.h"

#define ERR_FAILED_INIT -1
#define ERR_WRONG_PARAMETERS -2

// this flag is kept true while we need to run. Ctl-C breaks the loop and exits the program.
static int run = 1;

void handler_goaway(int sigcode)
{
  fprintf(stderr, "Received signal %d . Exitting...\n", sigcode);
  run=0;
}

int main(int argc, char** argv)
{

  int rc = 0;
  log4c_category_t* category = NULL;
  const unsigned buffer_size = 1024*10;
  size_t buffer_len = 0;

  if(argc<2)
  {
    fprintf(stderr, "ERROR: missing output category/filename. \n\tUsage: logredirect <category/output> \n");
    return ERR_WRONG_PARAMETERS;
  }

  char * buffer = (char*) malloc(buffer_size);

  signal(SIGINT,  handler_goaway);
  signal(SIGQUIT, handler_goaway);

  if (log4c_init())
  {
    fprintf(stderr, "log4c_init() failed\n");
    rc = ERR_FAILED_INIT;
    goto hell;
  }

  category = log4c_category_get(argv[1]);

  while(run && !feof(stdin))
  {
    fgets(buffer, buffer_size, stdin);
    buffer_len = strlen(buffer);
    if ('\n' == buffer[buffer_len-1]) buffer[buffer_len-1] = 0; // remove extra newline: log4c already adds a \n for us.
    // in the future, put here some regex to differentiate INFO, DEBUG, ERROR, etc.
    log4c_category_log(category, LOG4C_PRIORITY_INFO, buffer);
    buffer[0]=0; // "reset" buffer
  }

hell:

  // here we check program's state to proper cleanup things.

  if (buffer) free(buffer); 
  if (category && rc!=ERR_FAILED_INIT) log4c_fini();

  return 0;
}
