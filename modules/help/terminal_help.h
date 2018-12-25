#ifndef TERMINAL_HELP_H_
#define TERMINAL_HELP_H_

/*Define*/
/*............................................................................*/


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
void t_help(struct help_struct* h);

/*____________________________________________________________________________*/

#endif /*TERMINAL_HELP_H_*/