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


/*Extern variables*/
/*............................................................................*/

extern struct netif gnetif;

/*____________________________________________________________________________*/


/*Private variables*/
/*............................................................................*/

//ip_addr_t t_ip_addr;
struct tcp_pcb *client_pcb;
struct tcp_struct tcp_client;

/*____________________________________________________________________________*/

size_t t_parser_ip(char* ip_str, size_t len, uint8_t* ipextp) {
  
  uint16_t port=0;
  uint8_t offset = 0;
  uint8_t i;
  char ss2[5] = {0};
  char *ss1;
  int ch1 = '.';
  int ch2 = ',';
  for(i=0;i<3;i++)
  {
    ss1 = strchr(ip_str,ch1);
    offset = ss1-ip_str+1;
    strncpy(ss2,ip_str,offset);
    ss2[offset]=0;
    ipextp[i] = atoi(ss2);
    ip_str+=offset;
    len-=offset;
  }
  ss1=strchr(ip_str,ch2);
  if (ss1!=NULL)
  {
    offset=ss1-ip_str+1;
    strncpy(ss2,ip_str,offset);
    ss2[offset]=0;
    ipextp[3] = atoi(ss2);
    
    //about port
    ip_str+=offset;
    port = atoi(ip_str);
    
    return port;
  }
  
  port = 80;
  strncpy(ss2,ip_str,len);
  ss2[len]=0;
  ipextp[3] = atoi(ss2);
  
  return port;
}

static err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
  return err;
}

void t_tcp_command(char* string, size_t flagCommand, struct tcp_struct* sTcp) {
  
//  ip_addr_t ip_dest;
//  uint16_t port_dest;
  uint8_t ip_arr_dest[4] = {0};
  size_t idx=0, len;
  
  while (string[idx] == ' ') {
    idx++;
  }
  
  len = strlen(string) - idx;
  
  if (flagCommand == TERMINAL_TCP_CONNECT) {
    
    sTcp->port = t_parser_ip(string, len, ip_arr_dest);
    
    sTcp->client_pcb = tcp_new();
    
    if (client_pcb != NULL) {
      
      IP4_ADDR(&sTcp->ip_dest, 
             ip_arr_dest[0], ip_arr_dest[1], ip_arr_dest[2], ip_arr_dest[3]);
      
      tcp_connect(sTcp->client_pcb, &sTcp->ip_dest, sTcp->port, tcp_client_connected);
      t_transmit("Connect \n", 9);
    }
    
//    t_tcp_ip_extract();
//    t_transmit(&string[idx], strlen(&string[idx]));
  }
  else if (flagCommand == TERMINAL_TCP_DISCONNECT) {
    
    sTcp->port = t_parser_ip(string, len, ip_arr_dest);
    
    tcp_recv(sTcp->client_pcb, NULL);
    tcp_sent(sTcp->client_pcb, NULL);
    tcp_poll(sTcp->client_pcb, NULL,0);
    tcp_close(sTcp->client_pcb);
    
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
           t_tcp_command(&string[n+2], TERMINAL_TCP_CONNECT, &tcp_client);
           break;
         }
         case 'd': {
           t_tcp_command(&string[n+2], TERMINAL_TCP_DISCONNECT, &tcp_client);
           break;
         }
         case 'l': {
           t_tcp_command(&string[n+2], TERMINAL_TCP_LISTEN, &tcp_client);
           break;
         }
        default: {
           t_tcp_command(&string[n+2], 4, &tcp_client);
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

/******************************************************************************/
/**/
/******************************************************************************/

void t_tcp_init(struct tcp_struct* sTcp) {
  
  sTcp->port = 0;
  sTcp->ip_dest.addr = 0;
  sTcp->status = 0;
  sTcp->interface = NULL;
  sTcp->client_pcb = NULL;
}

void t_lwip_init(void) {
  
  
//  t_tcp_init();
}

/*****************************END OF FILE**************************************/