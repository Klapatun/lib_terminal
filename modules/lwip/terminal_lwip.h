#ifndef TERMINAL_LWIP_H_
#define TERMINAL_LWIP_H_

/*Include*/
/*............................................................................*/

#include "lwip.h"
#include "tcp.h"

/*____________________________________________________________________________*/


/*Define*/
/*............................................................................*/

#define TERMINAL_TCP_CONNECT            0
#define TERMINAL_TCP_DISCONNECT         1
#define TERMINAL_TCP_LISTEN             2

#define TERMINAL_TCP_STATE_BUSY         0
#define TERMINAL_TCP_STATE_FREE         1

/*____________________________________________________________________________*/


/*Structs*/
/*............................................................................*/

struct tcp_struct {
  
  uint16_t port;
  ip_addr_t ip_dest;
  size_t status;
  struct netif *interface;
  struct tcp_pcb *client_pcb;
};

/*____________________________________________________________________________*/


/*Function declaration*/
/*............................................................................*/

void t_lwip_handler(terminal_t *term);
void t_lwip_init(void);

/*____________________________________________________________________________*/

#endif