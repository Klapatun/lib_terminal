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

void t_tcp_command(char* string, size_t flagCommand) {
  
  size_t idx=0;
  
  while (string[idx] == ' ') {
    idx++;
  }
  
  if (flagCommand == TERMINAL_TCP_CONNECT) {
    t_transmit("Connect \n", 9);
  }
  else if (flagCommand == TERMINAL_TCP_DISCONNECT) {
    t_transmit("Disconnect \n", 12);
  }
  else if (flagCommand == TERMINAL_TCP_LISTEN) {
    t_transmit("Listen \n", 8);
  }
  else {
    
  }
    
}

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
       
       n = strcspn(string, "-");
       switch(string[n+1]) {
         case 'c': {
           t_tcp_command(&string[n+2], TERMINAL_TCP_CONNECT);
           break;
         }
         case 'd': {
           t_tcp_command(&string[n+2], TERMINAL_TCP_DISCONNECT);
           break;
         }
         case 'l': {
           t_tcp_command(&string[n+2], TERMINAL_TCP_LISTEN);
           break;
         }
        default: {
           t_tcp_command(&string[n+2], 4);
        }
       }
//       t_tcp_command();
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