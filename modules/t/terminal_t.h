#ifndef TERMINAL_T_H_
#define TERMINAL_T_H_

/*Include*/
/*............................................................................*/

#include "terminal.h"

/*____________________________________________________________________________*/


/*Public variable*/
/*............................................................................*/

/*
struct help_struct {
  struct help_struct* next;
  struct help_struct* head;
  
  char** names_func_module;
};*/

char* pNameFunc[TERMINAL_HELP_NUM_NAME] = {
  "t/help \n",
  "echo \n"
};

/*____________________________________________________________________________*/

/*Function declaration*/
/*............................................................................*/

void t_data_handler(terminal_t *term);

/*____________________________________________________________________________*/

#endif /*TERMINAL_T_H_*/