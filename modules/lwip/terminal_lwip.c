/**
 * @file
 * Terminal implementation for any microcontrollers.
 *
 */

/*Include*/
/*............................................................................*/

#include "terminal.h"
#include "lwip/terminal_lwip.h"

/*____________________________________________________________________________*/

size_t t_parser_data(char* string, size_t numStr) {
 
  size_t n = strcspn(string, " ");
  char tmp_str[10] = {0};
  
  if (n != numStr) {
    strncpy(tmp_str, string, n);
    tmp_str[n] = '\0';
    
    if (!(strcmp("ping", tmp_str))) {
       t_transmit("Ping \n", 6);
    }
    else if (!(strcmp("tcp", tmp_str))) {
       t_transmit("Tcp \n", 5);
    }
    else {
      t_transmit("Unknown command \n", 17);
    }
  }
  else {
    t_transmit("Only command \n", 14);
  }
  
  return 0;
}

void t_lwip_handler(terminal_t *term) {
  
  
  t_parser_data(term->data, term->len_data);
  
  
}


/*****************************END OF FILE**************************************/