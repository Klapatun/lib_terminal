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

extern char* pArrT[2];

/*____________________________________________________________________________*/

struct help_struct* t_add_help_struct(void) {
  
  return (struct help_struct*)malloc(1);
}

void t_remove_help_struct(struct help_struct* h) {
  
  free(h);
}

void t_include_help_struct(struct help_struct* pParent, char** pArrNameChilde, int numArr) {
  

  pParent->next = t_add_help_struct();
  pParent->next->head = pParent->head;
  pParent->next->num_arr = numArr;
  pParent->next->next = NULL;
  
  pParent->next->names_func_module = pArrNameChilde;
}


void t_build_help(struct help_struct* h) {
  
  h->head = h;
  h->names_func_module = pHelpBase;
  h->num_arr = 1;
  h->next = NULL;

  t_include_help_struct(h, pArrT, 2);
  
  h = h->head;  
}

/*****************************END OF FILE**************************************/