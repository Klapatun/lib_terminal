#ifndef TERMINAL_HELP_H_
#define TERMINAL_HELP_H_

/*Include*/
/*............................................................................*/

#include "terminal.h"

/*____________________________________________________________________________*/


/*Define*/
/*............................................................................*/

#define TERMINAL_HELP_ONE_MODULE        0
#define TERMINAL_HELP_MODULES_ALL       1
#define TERMINAL_HELP_NAMES_MODULES     2

/*____________________________________________________________________________*/


/*Structs*/
/*............................................................................*/

struct help_struct {
  struct help_struct* head;
  struct help_struct* next;
  
  char* name;
  
  char** names_func_module;
  uint8_t num_arr;
};

/*____________________________________________________________________________*/

/*Function declaration*/
/*............................................................................*/

void t_build_help(struct help_struct* h);
//void t_help(struct help_struct* h);
void t_help_handler(terminal_t* term);

/*____________________________________________________________________________*/

#endif /*TERMINAL_HELP_H_*/