/**
 * @file
 * Terminal implementation for any microcontrollers.
 *
 */


#include "terminal.h"


void terminal_init(terminal_t *term) {

  term->len_command=0;
  term->len_data=0;
  term->msg = (char*)malloc(TERMINAL_SIZE_MESSAGE);
  term->command = (char*)malloc(TERMINAL_SIZE_COMMAND);
  term->data = (char*)malloc(TERMINAL_SIZE_DATA);
  term->state = TERMINAL_STATE_FREE;
}

/*****************************END OF FILE**************************************/