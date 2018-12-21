/**
 * @file
 * Terminal implementation for any microcontrollers.
 *
 */

/*Include*/
/*............................................................................*/

#include "terminal.h"

/*____________________________________________________________________________*/

   
/*Define*/
/*............................................................................*/

#define NumNameFunc     2
   
/*____________________________________________________________________________*/
   
/*Private value*/
/*............................................................................*/

static terminal_t* trm_local;

static char* pNameFunc[NumNameFunc] = {
  "help \n",
  "echo \n"
};

/*____________________________________________________________________________*/


/*Private declaration*/
/*............................................................................*/
void t_help(void);
void t_definition(terminal_t *term);
void t_data_handler(terminal_t *term);
/*____________________________________________________________________________*/


void t_init(terminal_t* out_term) {
  
  t_definition(out_term);
  t_definition(trm_local);
}


uint8_t t_check(terminal_t *term) {
  
  if (term->state == TERMINAL_STATE_BUSY) {
    
    t_interrupt_off();
    
    trm_local->len_command = term->len_command;
    trm_local->len_data = term->len_data;
    memcpy(trm_local->data, term->data, sizeof(term->data));
    memcpy(trm_local->command, term->command, sizeof(term->command));
    
    t_interrupt_on();
        
    if (!(strcmp("t", trm_local->command))) {
      t_data_handler(trm_local);
    }
    else if (!(strcmp("echo", trm_local->command))) {
      t_transmit(trm_local->data, trm_local->len_data);
    }
    else {
      t_transmit("Error: bad command: ", 20);
    }
    
    trm_local->state = TERMINAL_STATE_FREE;
  }
  
  
  return 0;
}

void t_recive(terminal_t *term, char* Buf, uint16_t Len) {
  
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

void t_help(void) {
  
  for(int i=0; i < NumNameFunc; i++) {
    t_transmit(pNameFunc[i], strlen(pNameFunc[i]));
    HAL_Delay(100);
  }
}

void t_definition(terminal_t *term) {

  term->len_command = 0;
  term->len_data = 0;
  term->len_msg = 0;
  term->msg = (char*)malloc(TERMINAL_SIZE_MESSAGE);
  term->command = (char*)malloc(TERMINAL_SIZE_COMMAND);
  term->data = (char*)malloc(TERMINAL_SIZE_DATA);
  term->state = TERMINAL_STATE_FREE;
}


void t_data_handler(terminal_t *term) {
  
  if (!(strcmp("help", term->data))) {
    t_help();
  }
  else {
    t_transmit(term->data, term->len_data);
  }
}

/*****************************END OF FILE**************************************/