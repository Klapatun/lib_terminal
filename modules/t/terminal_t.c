/**
 * @file
 * Terminal implementation for any microcontrollers.
 *
 */

/*Include*/
/*............................................................................*/

#include "t/terminal_t.h"

/*____________________________________________________________________________*/


/*Define*/
/*............................................................................*/

#define TERMINAL_HELP_NUM_NAME  2
   
/*____________________________________________________________________________*/

   
/*Private value*/
/*............................................................................*/

static char* pNameFunc[TERMINAL_HELP_NUM_NAME] = {
  "t/help \n",
  "echo \n"
};

/*____________________________________________________________________________*/
   
/*Private declaration*/
/*............................................................................*/
void t_help(void);
/*____________________________________________________________________________*/


void t_data_handler(terminal_t *term) {
  
  if (!(strcmp("help", term->data))) {
    t_help();
  }
  else {
    t_transmit(term->data, term->len_data);
  }
}

void t_help(void) {
  
  for(int i=0; i < TERMINAL_HELP_NUM_NAME; i++) {
    t_transmit(pNameFunc[i], strlen(pNameFunc[i]));
    HAL_Delay(100);
  }
}

/*****************************END OF FILE**************************************/
