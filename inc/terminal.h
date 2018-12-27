#ifndef TERMINAL_H_
#define TERMINAL_H_

/*Include*/
/*............................................................................*/

#include "main.h"
#include "terminal_user_opt.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#if TERMINAL_USB
#include "terminal_usb.h"
#endif

//#include "help/terminal_help.h"

/*____________________________________________________________________________*/


/*Define*/
/*............................................................................*/
#define TERMINAL_SIZE_MESSAGE        64
#define TERMINAL_SIZE_COMMAND        16
#define TERMINAL_SIZE_DATA           ((TERMINAL_SIZE_MESSAGE)-(TERMINAL_SIZE_COMMAND))

#define TERMINAL_STATE_BUSY          0
#define TERMINAL_STATE_FREE          1
#define TERMINAL_STATE_OVERFLOW      2
#define TERMINAL_STATE_WAIT          3
/*____________________________________________________________________________*/


/*Macros*/
/*............................................................................*/

#define t_interrupt_off()          __disable_irq (); 
#define t_interrupt_on()           __enable_irq (); 

/*____________________________________________________________________________*/


/*Struct*/
/*............................................................................*/

typedef struct terminal_struct{
  
  struct terminal_struct* next;
    
  uint8_t state;
  char* msg;
  uint8_t len_msg;
  char* command;
  uint8_t len_command;
  char* data;
  uint8_t len_data;
}terminal_t ;

/*____________________________________________________________________________*/


/*Function declaration*/
/*............................................................................*/

void t_init(terminal_t *term);

void t_recive(terminal_t *term, char* Buf, uint16_t Len);

uint8_t t_check(terminal_t *term);

/*____________________________________________________________________________*/

#endif /*TERMINAL_H_*/