#ifndef TERMINAL_H_
#define TERMINAL_H_

/*Include*/
/*,,,,,,,.....................................................................*/
#include "terminal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
/*____________________________________________________________________________*/


/*Define*/
/*............................................................................*/
#define TERMINAL_SIZE_MESSAGE        64
#define TERMINAL_SIZE_COMMAND        16
#define TERMINAL_SIZE_DATA           ((TERMINAL_SIZE_MESSAGE)-(TERMINAL_SIZE_COMMAND))

#define TERMINAL_STATE_BUSY          0
#define TERMINAL_STATE_FREE          1
#define TERMINAL_STATE_OVERFLOW      2
/*____________________________________________________________________________*/


/*Struct*/
/*............................................................................*/

typedef struct terminal_struct{
  uint8_t state;
  char* msg;
  uint8_t len_command;
  uint8_t len_data;
  char* command;
  char* data;
}terminal_t ;

/*____________________________________________________________________________*/


/*function declaration*/
/*............................................................................*/

void terminal_init(terminal_t *term);

/*____________________________________________________________________________*/

#endif /*TERMINAL_H_*/