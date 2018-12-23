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


/*Private value*/
/*............................................................................*/

static char** pHelpBase = {
    "Module \"Help\" version 0.1"
};

/*____________________________________________________________________________*/


/*Private declaration*/
/*............................................................................*/



/*____________________________________________________________________________*/


void t_include_help_struct(struct help_struct* pParent, char** pArrNameChilde) {
  
  struct help_struct local_struct;

  pParent->next = local_struct;
  local_struct.head = pParent->head;
  
  local_struct.names_func_module = pArrNameChilde;
}


struct help_struct* t_build_help() {
  
  struct help_struct h;
  h.head = &h;
  h.names_func_module = pHelpBase;

  t_include_help_struct(&h, pNameFunc);
}

/*****************************END OF FILE**************************************/