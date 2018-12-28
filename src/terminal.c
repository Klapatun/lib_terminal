/**
 * @file
 * Terminal implementation for any microcontrollers.
 *
 */

/*Include*/
/*............................................................................*/

#include "terminal.h"
   
#if TERMINAL_INCLUDE_T
#include "t/terminal_t.h"
#endif
   
#if TERMINAL_INCLUDE_HELP
#include "help/terminal_help.h"
#endif
   
#if TERMINAL_INCLUDE_LWIP
#include "lwip/terminal_lwip.h"
#endif

/*____________________________________________________________________________*/

   
/*Private value*/
/*............................................................................*/

static terminal_t* trm_local;
extern struct help_struct help;
static uint32_t timTick;

/*____________________________________________________________________________*/


/*Private declaration*/
/*............................................................................*/
//void t_help(void);
void t_definition(terminal_t *term);
void t_data_handler(terminal_t *term);
/*____________________________________________________________________________*/


void t_init(terminal_t* out_term) {
  
  t_definition(out_term);
  t_definition(trm_local);
  
#if TERMINAL_INCLUDE_T
  t_build_help(&help);
#endif
#if TERMINAL_INCLUDE_LWIP
  t_lwip_init();
#endif
}


uint8_t t_check(terminal_t *term) {
  
  uint32_t tmpTim = HAL_GetTick();
  
  if ((term->state == TERMINAL_STATE_BUSY) || 
      ((timTick+1000 <= tmpTim) && (term->state == TERMINAL_STATE_WAIT))) {
    
    t_interrupt_off();    
    trm_local->len_command = term->len_command;
    trm_local->len_data = term->len_data;
    memcpy(trm_local->data, term->data, sizeof(term->data));
    memcpy(trm_local->command, term->command, sizeof(term->command)); 
    t_interrupt_on();
        
    
    if (!(strcmp("echo", trm_local->command))) {
      t_transmit(trm_local->data, trm_local->len_data);
    }
#if TERMINAL_INCLUDE_HELP
    else if (!(strcmp("help", trm_local->command))) {
      t_help_handler(term);
    }
#endif
#if TERMINAL_INCLUDE_T
    else if (!(strcmp("t", trm_local->command))) {
      t_data_handler(term);
    }
#endif
#if TERMINAL_INCLUDE_LWIP
    else if (!(strcmp("lwip", trm_local->command))) {
      t_lwip_handler(term);
    }
#endif
    else {
      t_transmit("Error: bad command: ", 20);
    }
    
    timTick = 0;
    
    trm_local->state = TERMINAL_STATE_FREE;
  }
  
  
  return 0;
}

void t_recive(terminal_t *term, char* Buf, uint16_t Len) {
  
  static uint8_t idx=0, separator=0;
  
  if (timTick == 0) {
    timTick = HAL_GetTick();
  }
  
  if (strchr(Buf, ':')) {
    /*Command*/
    term->state = TERMINAL_STATE_WAIT;
    strncpy(term->command, term->msg, idx);
    term->command[idx] = '\0';
    term->len_command = idx;
    separator = idx;
  }
  else if (strchr(Buf, ';')) {
    /*Data*/
    
    if (separator == 0) {
      strncpy(term->command, term->msg, idx);
      term->command[idx] = '\0';
      term->len_command = idx;
      term->state = TERMINAL_STATE_BUSY;
      return;
    }
    
    while (term->msg[separator] == ' ') {
      separator++;
    }
    
    if (separator == idx-1) {
      separator++;
    }
    
    strncpy(term->data, &term->msg[separator], idx-separator);
    term->data[idx-separator] = '\0';
    term->len_data = idx-separator;
    term->msg[idx] = '\0';
    term->len_msg = idx;
    separator = idx = 0;
    term->state = TERMINAL_STATE_BUSY;
  }
  else {
    term->state = TERMINAL_STATE_WAIT;
    strncpy(&term->msg[idx], (char*)Buf, Len);
    idx += Len;
    if (idx >= TERMINAL_SIZE_MESSAGE) {
      term->state = TERMINAL_STATE_OVERFLOW;
    }
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


/*****************************END OF FILE**************************************/