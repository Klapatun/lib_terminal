/**
 * @file
 * Terminal implementation for any microcontrollers.
 *
 */

/*Include*/
/*............................................................................*/

#include "t/terminal_t.h"
#include "help/terminal_help.h"

/*____________________________________________________________________________*/


/*Define*/
/*............................................................................*/


   
/*____________________________________________________________________________*/

   
/*Private variable*/
/*............................................................................*/

char* pArrT[2] = {
  "t/help \n",
  "echo \n"
};

extern struct help_struct help;

/*____________________________________________________________________________*/
   
/*Private declaration*/
/*............................................................................*/
void t_help(struct help_struct* h);
/*____________________________________________________________________________*/


void t_data_handler(terminal_t *term) {
  
  if (!(strcmp("help", term->data))) {
    t_help(&help);
  }
  else {
    t_transmit(term->data, term->len_data);
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
      n = *h->next;
    }
    else {
      break;
    }
      
  }
}

/*****************************END OF FILE**************************************/
