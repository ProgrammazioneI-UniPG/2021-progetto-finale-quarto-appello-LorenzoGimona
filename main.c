#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "gamelib.h"


int main()
{
  time_t t;
  int iter;
  int numero_caratteri;
  int elementi;
  int choice;


  srand ((unsigned)time(&t));

  gioco_impostato = false;

#ifdef DEBUG_MAIN
   printf("\nValore gioco_impostato: %d\n", gioco_impostato);
#endif

 do {
  iter=0;
  do {

      iter++;
      if (iter>1)
       {
        printf(RED_ERROR "\nRiprova: input non valido\n\n" RESET);
       }

      printf("\nMenu di gioco, per procedere premere:\n\n");
      printf("1) imposta gioco\n");
      printf("2) gioca\n");
      printf("3) termina gioco\n");

      elementi = 2;
      char buffer[elementi];
      numero_caratteri=leggi_riga(elementi, buffer);
      choice=atoi(buffer);

    } while ((choice<1)||(choice>3)||(numero_caratteri>2)||(numero_caratteri==0));

#ifdef DEBUG_MAIN
  printf("esco dal loop\n\n" );
#endif

  switch (choice)
  {
    case 1: if (gioco_impostato)
             {
              printf(GREEN_INFO"\nReimposto il gioco,,,,,,\n" RESET);
              dealloca();
              gioco_impostato = false;
             }
              imposta_gioco();
              gioco_impostato=true;


#ifdef DEBUG_MAIN
              printf("gioco_impostato= %d\n", gioco_impostato);
#endif
              printf(GREEN_INFO"\nOra si può giocare......\n"RESET);
              break;

    case 2: if (!gioco_impostato)
             {
              printf(RED_ERROR "\nBisogna PRIMA impostare il gioco\n" RESET);
              break;
             }
              gioca();
// Dopo gioca si va in continuità al caso 3
    case 3:   termina_gioco();
              gioco_impostato=false;


    }            //Fine switch
  } while(true);
 return 0;
}
