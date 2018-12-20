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

uint8_t terminal_check(terminal_t *term) {
  char arr[32] = {0};
  if (term->state == TERMINAL_STATE_BUSY) {
    
    strcpy(arr, term->command);
    if (!(strcmp("ip_addr", term->command))) {
//      ip_addr_trm(term);
    }
    else {
      terminal_transmit("Error: bad command", 18);
    }
    term->state = TERMINAL_STATE_FREE;
  }
  
  return 0;
}

void terminal_recive(terminal_t *term, char* Buf, uint16_t Len) {
  
  static uint8_t idx=0, separator=0;
  
  if (strchr(Buf, ':')) {
    /*Command*/
    strncpy(term->command, term->msg, idx);
    term->command[idx] = '\0';
    term->len_command = idx;
    separator = idx+1;
  }
  else if (strchr(Buf, ';')) {
    /*Data*/
    strncpy(term->data, &term->msg[separator], idx-separator);
    term->data[idx-separator] = '\0';
    term->len_data = idx-separator;
    separator = idx = 0;
    term->state = TERMINAL_STATE_BUSY;
  }
  else {
    strncpy(&term->msg[idx], (char*)Buf, Len);
//    term->msg[idx] = Buf[0];
//    idx += 1; 
    idx += Len;
    if (idx >= TERMINAL_SIZE_MESSAGE) {
      term->state = TERMINAL_STATE_OVERFLOW;
    }
  }
  
}

/*****************************END OF FILE**************************************/