/**
 * @file
 * Terminal implementation for any microcontrollers.
 *
 */

/*Include*/
/*............................................................................*/

#include "terminal.h"
#include "help/terminal_help.h"

#if TERMINAL_INCLUDE_T
#include "t/terminal_t.h"
#endif

/*____________________________________________________________________________*/


/*Private variable*/
/*............................................................................*/

char* pHelpBase[1] = {
    "Module \"Help\" version 0.2 \n"
};

char* pHelpTwo[3] = {
    "one \n",
    "two \n",
    "three \n"
};

/*____________________________________________________________________________*/


/*Public variable*/
/*............................................................................*/

struct help_struct help;

/*____________________________________________________________________________*/


/*Private declaration*/
/*............................................................................*/

extern char* pArrT[2];

/*____________________________________________________________________________*/

struct help_struct* t_add_help_struct(void) {
  
  return (struct help_struct*)malloc(sizeof(struct help_struct));
}

void t_remove_help_struct(struct help_struct* h) {
  
  free(h);
}

void t_include_help_struct(struct help_struct* pParent, char** pArr, 
                           uint8_t numArr, char* name) {
  
  if (pParent->next == NULL) {
    pParent->next = t_add_help_struct();
    pParent->next->next = NULL;
    pParent->next->head = pParent->head;
    pParent->name = name;
    
    pParent->next->names_func_module = pArr;
    pParent->next->num_arr = numArr;
  }
  else {
    t_include_help_struct(pParent->next, pArr, numArr, name);
  }
}

void t_build_help(struct help_struct* h) {
  
  h->name = "help";
  h->head = h;
  h->names_func_module = pHelpBase;
  h->num_arr = 1;
  h->next = NULL;
  
  
#if TERMINAL_INCLUDE_T
  t_include_help_struct(h, pArrT, 2, "t");
#endif
  t_include_help_struct(h, pHelpTwo, 3, "dop");
}

/******************************************************************************/
/**/
/******************************************************************************/

void t_out_name_list(struct help_struct* h) {
  
  t_transmit(strcat(h->name," \n"), strlen(h->name)+1);
  
  if(h->next != NULL) {
    t_out_name_list(h->next);
  }
}

void t_help(struct help_struct* h, uint8_t nModule) {
  
  struct help_struct n = *h;
  
  t_transmit("/**********/ \n", 14);
  
  while(1) {
    
    if (nModule == TERMINAL_HELP_NAMES_MODULES) {
      
      t_out_name_list(h);
      
      break;
    }
    
    for (int i=0; i < n.num_arr; i++) {
      t_transmit(n.names_func_module[i], strlen(n.names_func_module[i]));
      HAL_Delay(100);
    }
    
    if((nModule) && (n.next != NULL)) {
      n = *n.next;
    }
    else {
      break;
    }
  }
  
  t_transmit("/**********/ \n", 14);
}

uint8_t t_search_module(char* pNameModule, uint8_t numStr, struct help_struct* h) {
  
  uint8_t tmp = 0;
  
  if(!(strcmp(h->name, pNameModule))) {
    tmp = 1;
  }
  else {
    
    if (h->next == NULL) {
      tmp=0;
    }
    else {
      tmp = t_search_module(pNameModule, numStr, h->next);
      *h = *h->next;
    }
  }
  
  return tmp;
}

void t_help_handler(terminal_t *term) {
  
  struct help_struct tmpHelp = help;
  
  
  if (term->len_data == 0) {
    t_transmit("No argument \n", 18);
  }
  else {
    if (!(strcmp("modules", term->data))) {
      t_help(&tmpHelp, TERMINAL_HELP_NAMES_MODULES);
      return;
    }
    
    if (t_search_module(term->data, term->len_data, &tmpHelp)) {
      t_help(tmpHelp.next, TERMINAL_HELP_ONE_MODULE);
    }
    else {
      t_transmit("Module is not connected \n",25);
    }
  }
}

/*****************************END OF FILE**************************************/