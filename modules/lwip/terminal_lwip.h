#ifndef TERMINAL_LWIP_H_
#define TERMINAL_LWIP_H_

/*Define*/
/*............................................................................*/

#define TERMINAL_TCP_CONNECT            0
#define TERMINAL_TCP_DISCONNECT         1
#define TERMINAL_TCP_LISTEN             2

/*____________________________________________________________________________*/


/*Function declaration*/
/*............................................................................*/

void t_lwip_handler(terminal_t *term);

/*____________________________________________________________________________*/

#endif