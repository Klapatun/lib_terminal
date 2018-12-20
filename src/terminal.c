/**
 * @file
 * Terminal implementation for any microcontrollers.
 *
 */

/*Include*/
/*............................................................................*/

#include "terminal.h"

/*____________________________________________________________________________*/

/*Private value*/
/*............................................................................*/
static terminal_t* trm_local;
/*____________________________________________________________________________*/

void terminal_definition(terminal_t *term) {

  term->len_command = 0;
  term->len_data = 0;
  term->len_msg = 0;
  term->msg = (char*)malloc(TERMINAL_SIZE_MESSAGE);
  term->command = (char*)malloc(TERMINAL_SIZE_COMMAND);
  term->data = (char*)malloc(TERMINAL_SIZE_DATA);
  term->state = TERMINAL_STATE_FREE;
}

void terminal_init(terminal_t* out_term) {
  terminal_definition(out_term);
  terminal_definition(trm_local);
}

void terminal_deinit(terminal_t *term) {
  free(term);
}


uint8_t terminal_check(terminal_t *term) {
  
  if (trm_local->state == TERMINAL_STATE_BUSY) {
    
    memcpy(trm_local, term, sizeof(term));
    if (!(strcmp("ip_addr", trm_local->command))) {
//      ip_addr_trm(term);
    }
    else if (!(strcmp("echo", trm_local->command))) {
      terminal_transmit(trm_local->data, trm_local->len_data);
    }
    else {
      terminal_transmit("Error: bad command: ", 20);
    }
    trm_local->state = TERMINAL_STATE_FREE;
  }
  
  terminal_deinit(trm_local);
  
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
    term->msg[idx] = '\0';
    term->len_msg = idx;
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