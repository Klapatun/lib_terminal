/**
 * @file
 * Terminal implementation for any microcontrollers.
 *
 */

/*Include*/
/*............................................................................*/

#include "terminal.h"
#include "help/terminal_help.h"

#if TERMINAL_INCLUDE_T
#include "t/terminal_t.h"
#endif

/*____________________________________________________________________________*/


/*Private variable*/
/*............................................................................*/

char* pHelpBase[1] = {
    "Module \"Help\" version 0.2 \n"
};

/*____________________________________________________________________________*/


/*Public variable*/
/*............................................................................*/

struct help_struct help;

/*____________________________________________________________________________*/


/*Private declaration*/
/*............................................................................*/

extern char* pArrT[2];

/*____________________________________________________________________________*/

struct help_struct* t_add_help_struct(void) {
  
  return (struct help_struct*)malloc(sizeof(struct help_struct));
}

void t_remove_help_struct(struct help_struct* h) {
  
  free(h);
}

void t_include_help_struct(struct help_struct* pParent, char** pArr, uint8_t numArr) {
  
  if (pParent->next == NULL) {
    pParent->next = t_add_help_struct();
    pParent->next->next = NULL;
    pParent->next->head = pParent->head;
    
    pParent->next->names_func_module = pArr;
    pParent->next->num_arr = numArr;
  }
  else {
    t_include_help_struct(pParent->next, pArr, numArr);
  }
}

void t_help(struct help_struct* h) {
  
  struct help_struct n = *h;
  
  while(1) {
    
    for (int i=0; i < n.num_arr; i++) {
      t_transmit(n.names_func_module[i], strlen(n.names_func_module[i]));
      HAL_Delay(100);
    }
    
    if(n.next != NULL) {
      n = *n.next;
    }
    else {
      break;
    }
      
  }
}

void t_build_help(struct help_struct* h) {
  
  h->head = h;
  h->names_func_module = pHelpBase;
  h->num_arr = 1;
  h->next = NULL;
  
#if TERMINAL_INCLUDE_T
  t_include_help_struct(h, pArrT, 2);
#endif
  
}

/*****************************END OF FILE**************************************/