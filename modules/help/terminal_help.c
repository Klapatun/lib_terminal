/**
 * @file
 * Terminal implementation for any microcontrollers.
 *
 */

/*Include*/
/*............................................................................*/

#include "terminal.h"
   
#include "help/terminal_help.h"

#include "t/terminal_t.h"

/*____________________________________________________________________________*/


/*Private variable*/
/*............................................................................*/

char* pHelpBase[1] = {
    "Module \"Help\" version 0.1 \n"
};

/*____________________________________________________________________________*/


/*Private declaration*/
/*............................................................................*/

//extern char* pNameFunc[2];
extern char* pArrT[2];

/*____________________________________________________________________________*/

struct help_struct* t_add_help_struct(void) {
  
  return (struct help_struct*)malloc(1);
}

void t_remove_help_struct(struct help_struct* h) {
  
  free(h);
}

void t_include_help_struct(struct help_struct* pParent, char** pArrNameChilde, int numArr) {
  
//  struct help_struct *local_struct = t_add_help_struct();

  pParent->next = t_add_help_struct();
  pParent->next->head = pParent->head;
//  local_struct->head = pParent->head;
//  local_struct->next = NULL;
  pParent->next->num_arr = numArr;
//  local_struct->num_arr = numArr;
  
  pParent->next->names_func_module = pArrNameChilde;
//  local_struct->names_func_module = pArrNameChilde;
//  pParent = local_struct;
}


void t_build_help(struct help_struct* h) {
  
  h->head = h;
  h->names_func_module = pHelpBase;
//  h->next = NULL;
  h->num_arr = 1;

  t_include_help_struct(h, pArrT, 2);
  
  h = h->head;  
}

/*****************************END OF FILE**************************************/