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

/*Function declaration*/
/*............................................................................*/

void t_ip_check(struct netif *gnetif);
void t_ip_set(char* string, struct netif *gnetif);

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
    len -= offset;
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
  
  err_t err;
  uint8_t ip_arr_dest[4] = {0};
  size_t idx=0, len;
  
  while (string[idx] == ' ') {
    idx++;
  }
  
  len = strlen(string) - idx;
  
  if (flagCommand == TERMINAL_TCP_CONNECT) {
    
    sTcp->port = t_parser_ip(string, len, ip_arr_dest);
    
    if (sTcp->port != 0) {
      
      client_pcb = tcp_new();
      
      if (client_pcb != NULL) {
        
        IP4_ADDR(&sTcp->ip_dest, 
               ip_arr_dest[0], ip_arr_dest[1], ip_arr_dest[2], ip_arr_dest[3]);
        
        err = tcp_connect(sTcp->client_pcb, &sTcp->ip_dest, sTcp->port, tcp_client_connected);
        if (err == ERR_OK) {
          
          sTcp->status = TERMINAL_TCP_STATE_BUSY;
          t_transmit("Connect \n", 9);
        }
        else {
          sTcp->status = TERMINAL_TCP_STATE_NO_CONNECT;
          t_transmit("Cannot connected \n", 18);
        }
      }
      else {
        t_transmit("Error connect \n", 15);
      }
    }
  }
  else if (flagCommand == TERMINAL_TCP_DISCONNECT) {
    
    sTcp->port = t_parser_ip(string, len, ip_arr_dest);
    
    if (sTcp->status == TERMINAL_TCP_STATE_BUSY) {
      
      tcp_recv(sTcp->client_pcb, NULL);
      tcp_sent(sTcp->client_pcb, NULL);
      tcp_poll(sTcp->client_pcb, NULL,0);
      tcp_close(sTcp->client_pcb);
      
      sTcp->status = TERMINAL_TCP_STATE_FREE;
    }
    
    t_transmit("Disconnect \n", 12);
  }
  else if (flagCommand == TERMINAL_TCP_LISTEN) {
    t_transmit("Listen \n", 8);
  }
  else {
    t_transmit("Error \n", 7);
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
    else if (!(strcmp("ip", tmp_str))) {
      n = strcspn(string, "-");
      switch(string[n+1]) {
        case 'c': {
          t_ip_check(&gnetif);
          break;
        }
        case 's': {
          t_ip_set(&string[n+2], &gnetif);
          break;
        }
        default: {
        }
      }
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
/*LWIP - IP*/
/******************************************************************************/

void t_ip_check(struct netif *gnetif) {
  
  uint8_t tmp = 0;
  char ch[3] = {0};
  
  
  
  t_transmit("ip: ", 4);
  for (uint8_t i=0; i < 32; i+=8) {
    tmp = gnetif->ip_addr.addr >> i;
    
    sprintf(ch,"%d", tmp);
    t_transmit(ch, strlen(ch));
    t_transmit('.',1);
  }
  t_transmit(" \n", 2);
  
  t_transmit("mask: ", 6);
  for (uint8_t i=0; i < 32; i+=8) {
    tmp = gnetif->netmask.addr >> i;
    
    sprintf(ch,"%d", tmp);
    t_transmit(ch, strlen(ch));
    t_transmit('.',1);
  }
  t_transmit(" \n", 2);
  
  t_transmit("gateway: ", 9);
  for (uint8_t i=0; i < 32; i+=8) {
    tmp = gnetif->gw.addr >> i;
    
    sprintf(ch,"%d", tmp);
    t_transmit(ch, strlen(ch));
    t_transmit('.',1);
  }
  t_transmit(" \n", 2);
}

/*Возвращает индекс элемента конца*/
u32_t t_ip_parser(char* string, struct netif *gnetif) {
  
  uint8_t pattern[4];
  
  ip4_addr_t ipaddr;
  
  size_t n = 0, n1=0, tmp=0, ten=1;
  
  while(string[0] == ' ') {
    string++;
  }
  
  if (string[0] == '-') {
    return 0;
  }
  
  for (int i=0; i < 3; i++) {
    
    n = strcspn(string, ".");
    n1=n+1;
  
    if (n < strlen(string)) {
      
      while(n!=0){
        
        n--;
        tmp += (0x0F & string[n]) * ten;
        ten*=10;
        
      }      
      pattern[i] = tmp;
      string+= n1;      
    }
    
    ten = 1;
    tmp = 0;
  }
  
  n = strcspn(string, " ");
  n1 = n;
  
  if (n <= strlen(string)) {
    
    while(n!=0){
      
      n--;
      tmp += (0x0F & string[n]) * ten;
      ten*=10;
      
    }    
    pattern[3] = tmp;    
    string+= n1;    
  }
  
  
  /*Запись в настройки*/
  
  IP4_ADDR(&ipaddr, pattern[0], pattern[1], pattern[2], pattern[3]);
  
  return ipaddr.addr;
}

void t_ip_set(char* string, struct netif *gnetif) {
  
  size_t n = 0;
  
  ip4_addr_t ipaddr = gnetif->ip_addr;
  ip4_addr_t netmask = gnetif->netmask;
  ip4_addr_t gw = gnetif->gw;
  
  do {
    
    n = strcspn(string, "-");
    if (n < strlen(string)) {
      
      switch(string[n+1]) {
        case 'i': {
          string += n+2;
          ipaddr.addr = t_ip_parser(string, gnetif);
          continue;
        }
        case 'm': {
          string += n+2;
          netmask.addr = t_ip_parser(string, gnetif);
          continue;
        }
        case 'g': {
          string += n+2;
          gw.addr = t_ip_parser(string, gnetif);
          continue;
        }
        default: {
          t_transmit("Inviled value \n", 15);
//          break;
        }
      }
    }
    break;
    
  }while(1);
  
  netif_set_addr(gnetif, &ipaddr, &netmask, &gw);
  
}



/******************************************************************************/
/*LWIP - Initialization*/
/******************************************************************************/

void t_tcp_init(struct tcp_struct* sTcp) {
  
  sTcp->port = 0;
  sTcp->ip_dest.addr = 0;
  sTcp->status = 0;
  sTcp->interface = NULL;
  sTcp->client_pcb = NULL;
}

void t_lwip_init(void) {
  
  
  t_tcp_init(&tcp_client);
}

/*****************************END OF FILE**************************************/