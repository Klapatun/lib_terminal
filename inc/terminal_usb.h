#ifndef TERMINAL_USB_
#define TERMINAL_USB_

//#include "terminal.h"
#include "usbd_cdc_if.h"

/*Macros*/
/*............................................................................*/

#define terminal_transmit(pBuf, len)    CDC_Transmit_FS((uint8_t*)(pBuf), (uint16_t)(len))

/*____________________________________________________________________________*/

#endif /*TERMINAL_USB_*/