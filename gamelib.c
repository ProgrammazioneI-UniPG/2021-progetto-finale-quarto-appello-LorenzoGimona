#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "gamelib.h"


int stai_fermo();
int avanza();
int esegui_quest();
int chiamata_emergenza();
int uccidi_astronauta();
int usa_botola();
int sabotaggio();
int esci();
int stampa_giocatori();
_Bool inizia_gioco();
struct Stanza* set_stanza (struct Stanza* ptr_set_stanza);
int dummy();

struct Giocatore* ptr_giocatori;
struct Stanza* ptr_stanza_inizio;
struct Stanza* ptr_lista_stanze;
struct Stanza* ptr_latest_room;
struct Stanza* ptr_new_room;
struct Stanza* ptr_curr_room;

unsigned short quest_da_finire;
int n_giocatori;
int count_malloc;
int n_stanze;
int n_botole;
int count_quest;
int curr_gio;
_Bool fine_partita = false;



char arr_nomi[10][27]={{ARANCIO"ARANCIO"RESET}, {BISTRO"BISTRO"RESET},
    {CIANO"CIANO"RESET}, {FUCSIA"FUCSIA"RESET}, {LILLA"LILLA"RESET},
    {MAGENTA"MAGENTA"RESET}, {OCRA"OCRA"RESET}, {SOLIDAGO"SOLIDAGO"RESET},
    {TURCHESE"TURCHESE"RESET}, {VERMIGLIO"VERMIGLIO"RESET}};
char arr_stato[5][28]={{GREEN_INFO"astronauta"RESET}, {GREEN_INFO"impostore"RESET},
    {GREEN_INFO"assassinato"RESET}, {GREEN_INFO"defenestrato"RESET}};
char arr_tipo_stanza[4][30]={{GREEN_INFO"Vuota"RESET},
    {GREEN_INFO"Quest semplice"RESET}, {GREEN_INFO"Quest doppia"RESET},
    {GREEN_INFO"Botola"RESET}};


int imposta_gioco()
{
  int iter;
  int numero_caratteri;
  int elementi;
  int index;
  int colore = 0;
  int n_impostori;
  int percentage;
  int rand_check[10]={10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
  _Bool start=false;

  n_stanze=0;
  n_botole=0;

  ptr_stanza_inizio = set_stanza (ptr_stanza_inizio); //creazione stanza inizio

  ptr_stanza_inizio->stanza_precedente=NULL;

  ptr_lista_stanze=ptr_stanza_inizio;
  ptr_latest_room=ptr_stanza_inizio;

 do
 {


  iter=0;
  do {                                       //ciclo inserimento giocatori
    iter++;
    if (iter>1)
    {
      printf(RED_ERROR"\nRiprova: input non valido\n"RESET);
    }
    printf("\nMenu selezione n. giocatori e numero quest\n\n");
    printf("Inserire numero giocatori (min:4 max:10): ");
    elementi=3;
    char buffer[elementi];
    numero_caratteri=leggi_riga(elementi, buffer);
    n_giocatori=atoi(buffer);
  } while((n_giocatori<4)||(n_giocatori>10)||(numero_caratteri>3)||(numero_caratteri == 0));

  printf(GREEN_INFO"Numero giocatori: %d\n"RESET, n_giocatori);

  iter=0;
  do        //ciclo inserimento quest
   {
    iter++;
    if (iter>1)
     {
      printf(RED_ERROR"\nRiprova: input non valido\n\n"RESET);
     }

    printf("inserire numero quest (min:1 max:99): ");
    elementi=3;
    char buffer[elementi];
    numero_caratteri=leggi_riga(elementi, buffer);
    quest_da_finire=(unsigned short)atoi(buffer);
   }
  while ((quest_da_finire==0)||(quest_da_finire>99)||(numero_caratteri>3)||(numero_caratteri==0));

  printf(GREEN_INFO"Numero quest da completare: %d\n"RESET, quest_da_finire);

  ptr_giocatori=calloc(n_giocatori, sizeof(struct Giocatore));                  //allocazione array giocatori
  count_malloc+=(n_giocatori*sizeof(struct Giocatore));
#ifdef DEBUG_IMPOSTA
  printf("Contatore memoria allocata: %d\n", count_malloc);
#endif

  colore=random(10);                                                            //inizializzazione randomica array giocatori
  ptr_giocatori[0].nome=colore;
  rand_check[0]=colore;
#ifdef DEBUG_IMPOSTA
  printf("Index 0= %d\n", colore);
  printf("Nome[%d]=%s\n", colore, arr_nomi[colore]);
#endif

  for (index = 1; index < n_giocatori; index++)
   {
    do {
        colore=random(10);
#ifdef DEBUG_IMPOSTA
        printf("Index %d= %d\n", index, colore);
#endif
    }while((colore==rand_check[0])||(colore==rand_check[1])||(colore==rand_check[2])||
          (colore==rand_check[3])||(colore==rand_check[4])||(colore==rand_check[5])||
          (colore==rand_check[6])||(colore==rand_check[7])||(colore==rand_check[8]));

    ptr_giocatori[index].nome=colore;
    rand_check[index]=colore;
#ifdef DEBUG_IMPOSTA
    printf("Nome[%d]=%s\n", colore, arr_nomi[colore]);
#endif
   }

  for ( index = 0; index < n_giocatori; index++)
   {
    ptr_giocatori[index].stato=astronauta;
   }

  percentage=random(100)+1;

  switch(n_giocatori)
  {
    case 4 : if (percentage<=70) {
              n_impostori=1;
              } else {
              n_impostori=2;
              }
             break;
    case 5 : if (percentage<=60) {
              n_impostori=1;
              } else if ((percentage>=61)&&(percentage<=90)) {
              n_impostori=2;
              } else {
              n_impostori=3;
              }
            break;
    case 6 : if (percentage<=30) {
              n_impostori=1;
              } else if ((percentage>=31)&&(percentage<=70)) {
              n_impostori=2;
              } else {
              n_impostori=3;
              }
            break;
    case 7 : if (percentage<=30) {
              n_impostori=1;
              } else if ((percentage>=31)&&(percentage<=60)) {
              n_impostori=2;
              } else {
              n_impostori=3;
              }
            break;
    case 8 : if (percentage<=20) {
              n_impostori=1;
              } else if ((percentage>=21)&&(percentage<=50)) {
              n_impostori=2;
              } else {
              n_impostori=3;
              }
            break;
    case 9 : if (percentage<=10) {
              n_impostori=1;
              } else if ((percentage>=11)&&(percentage<=30)) {
              n_impostori=2;
              } else {
              n_impostori=3;
              }
            break;
    case 10: if (percentage<=20) {
              n_impostori=2;
              } else {
              n_impostori=3;
              }
            break;
  } //Fine switch

  for (index = 0; index < n_impostori; index++)
     {
       ptr_giocatori[index].stato=impostore;
     }


     for (index = 0; index < n_giocatori; index++)  //posizionamento giocatori in stanza inizio
     {
       ptr_giocatori[index].position=ptr_stanza_inizio;
     }

     stampa_giocatori();
#ifdef DEBUG_IMPOSTA
     printf("Tipo stanza: %s\n", arr_tipo_stanza[ptr_stanza_inizio->room_type]);
#endif
     start = inizia_gioco();

 } while(!start);
return 0;
}             // Fine imposta_gioco



int gioca()
{

  int Round=0;
  int turno=0;
  int iter;
  int numero_caratteri;
  int elementi;
  int choice;
  int index;
  int rand_turn_index;
  int rand_check_gioca[10]={10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
  int n_astro=0;
  struct Giocatore* ptr_giocatori_temp;
  int (*ptr_func[10])();
  int func_index;
  int count_astro_morituri;


  count_quest=0;
  fine_partita=false;

  do
  {     //ciclo del round
    Round++;
    printf(GREEN_INFO"\nRound %d\n"RESET, Round);
    for (index = 0; index < n_giocatori; index++)
      {
      rand_check_gioca[index]=10;
      }
    ptr_giocatori_temp=calloc (n_giocatori, sizeof(struct Giocatore));
    count_malloc+=(n_giocatori*sizeof(struct Giocatore));

    rand_turn_index=random (n_giocatori);              //randomizzazione turni
    rand_check_gioca[0]=rand_turn_index;
    ptr_giocatori_temp[0]=ptr_giocatori[rand_turn_index];
#ifdef DEBUG_GIOCA
    printf("Indice del turno %d\n", rand_turn_index);
#endif
    for (index = 1; index < n_giocatori; index++)  //for che randomizza i turni e crea l'array temporaneo dei giocatori
      {
      do {
          rand_turn_index=random(n_giocatori);
#ifdef DEBUG_GIOCA
          printf("Indice del turno %d\n", rand_turn_index);
#endif
        } while((rand_turn_index==rand_check_gioca[0])||
                (rand_turn_index==rand_check_gioca[1])||
                (rand_turn_index==rand_check_gioca[2])||
                (rand_turn_index==rand_check_gioca[3])||
                (rand_turn_index==rand_check_gioca[4])||
                (rand_turn_index==rand_check_gioca[5])||
                (rand_turn_index==rand_check_gioca[6])||
                (rand_turn_index==rand_check_gioca[7])||
                (rand_turn_index==rand_check_gioca[8]));

      rand_check_gioca[index]=rand_turn_index;
      ptr_giocatori_temp[index]=ptr_giocatori[rand_turn_index];
      }

    turno=0;
    for (index = 0; index < n_giocatori; index++)       //for che stampa l'array giocatori randomizzato
      {
      ptr_giocatori[index]=ptr_giocatori_temp[index];
#ifdef DEBUG_GIOCA
      printf("Giocatore %s nel turno %d\n", arr_nomi[ptr_giocatori[index].nome], ++turno);
#endif
      }

      free (ptr_giocatori_temp);
      count_malloc-=(n_giocatori*sizeof(struct Giocatore));
      turno=0;

      for (index = 0; index < n_giocatori; index++)      //for dei turni
        {
          for (int i = 0; i < 10; i++)     // Inizializzazione array puntatori a funzione
          {
           ptr_func[i]=dummy;
          }
          curr_gio=index;                 // inizializzazione giocatore corrente
          ptr_curr_room=ptr_giocatori[index].position; //puntatore a stanza corrente

          switch (ptr_giocatori[index].stato)
          {
            case assassinato:
            case defenestrato:
              break;

            case astronauta:
              printf("\nE' il turno %d: l'"GREEN_INFO"astronauta"RESET" %s si trova in una stanza %s\n",
                    ++turno, arr_nomi[ptr_giocatori[index].nome],
                    arr_tipo_stanza[ptr_giocatori[index].position->room_type]);
              for (int i = 0; i < n_giocatori; i++)
                {
                 if ((ptr_giocatori[index].position==ptr_giocatori[i].position)&&(i!=index))
                   {
                    printf("Il giocatore %15s è nella stessa stanza ed ha stato: %s\n",
                            arr_nomi[ptr_giocatori[i].nome],
                            arr_stato[ptr_giocatori[i].stato]);
                   }
                }

              iter=0;
              do
                {
                iter++;
                if (iter>1)
                  {
                  printf(RED_ERROR "\nRiprova: input non valido\n\n" RESET);
                  }
                printf("\nAnd now it's up to you, %s!\n",
                       arr_nomi[ptr_giocatori[curr_gio].nome]);     //do-while della stampa del menù di gioco
                func_index=0;
                printf("%d) Stai fermo\n", func_index+1);
                ptr_func[func_index]=stai_fermo;
                func_index++;
                printf("%d) Avanza\n", func_index+1);
                ptr_func[func_index]=avanza;
                func_index++;
                if ((ptr_giocatori[index].position->room_type==quest_semplice)||(ptr_giocatori[index].position->room_type==quest_doppia))
                  {
                  printf("%d) Esegui quest\n", func_index+1);
                  ptr_func[func_index]=esegui_quest;
                  func_index++;
                  }
                if (ptr_giocatori[index].position->emergenza_chiamata==false)
                  {
                  for (int i = 0; i < n_giocatori; i++)
                    {
                    if ((ptr_giocatori[index].position==ptr_giocatori[i].position)&&
                       (ptr_giocatori[i].stato==assassinato))
                       {
                        printf("%d) Chiamata d'emergenza\n", func_index+1);
                        ptr_func[func_index]=chiamata_emergenza;
                        func_index++;
                        break;
                       }
                     }
                  }
                  printf("%d) ESCI\n", func_index+1);
                  ptr_func[func_index]=esci;
                  func_index++;

                  elementi=2;
                  char buffer[elementi];
                  numero_caratteri=leggi_riga(elementi, buffer);
                  choice=atoi(buffer);

                } while((choice<1)||(choice>func_index)||
                        (numero_caratteri>2)||(numero_caratteri==0));

                (*ptr_func[choice-1]) ();                 //chiamata funzione di gioco

                break;

            case impostore:
              printf("\nE' il turno %d: l'"GREEN_INFO"impostore"RESET" %s si trova in una stanza %s\n",
                    ++turno, arr_nomi[ptr_giocatori[index].nome],
                    arr_tipo_stanza[ptr_giocatori[index].position->room_type]);
              for (int i = 0; i < n_giocatori; i++)
                {
                 if ((ptr_giocatori[index].position==ptr_giocatori[i].position)&&
                    (i!=index))
                   {
                    printf("Il giocatore %s è nella stessa stanza ed ha stato: %s\n",
                            arr_nomi[ptr_giocatori[i].nome],
                            arr_stato[ptr_giocatori[i].stato]);
                   }
                }

              iter=0;
              do {
                 iter++;
                 if (iter>1)
                   {
                    printf(RED_ERROR "\nRiprova: input non valido\n\n" RESET);
                   }

                 printf("\nAnd now it's up to you, %s!\n",
                        arr_nomi[ptr_giocatori[curr_gio].nome]);     //do-while della stampa del menù di gioco
                 func_index=0;
                 printf("%d) Stai fermo\n", func_index+1);
                 ptr_func[func_index]=stai_fermo;
                 func_index++;
                 printf("%d) Avanza\n", func_index+1);
                 ptr_func[func_index]=avanza;
                 func_index++;
                 if (ptr_giocatori[index].position->emergenza_chiamata==false)
                   {
                    for (int i = 0; i < n_giocatori; i++)
                      {
                       if ((ptr_giocatori[index].position==ptr_giocatori[i].position)&&
                          (ptr_giocatori[i].stato==assassinato))
                         {
                          printf("%d) Chiamata d'emergenza\n", func_index+1);
                          ptr_func[func_index]=chiamata_emergenza;
                          func_index++;
                          break;
                          }
                        }
                   }
                 count_astro_morituri=0;
                 for (int i = 0; i < n_giocatori; i++)
                   {
                    if ((ptr_giocatori[index].position==ptr_giocatori[i].position)&&
                        (ptr_giocatori[i].stato==astronauta))
                      {
                       count_astro_morituri++;
                      }
                    }
                 if (count_astro_morituri>0)
                   {
                    printf("%d) Uccidi astronauta\n", func_index+1);
                    ptr_func[func_index]=uccidi_astronauta;
                    func_index++;
                    }
                 if (ptr_giocatori[index].position->room_type==botola)
                   {
                    printf("%d) Usa botola\n", func_index+1);
                    ptr_func[func_index]=usa_botola;
                    func_index++;
                   }
                 if ((ptr_giocatori[index].position->room_type==quest_semplice)||
                    (ptr_giocatori[index].position->room_type==quest_doppia))
                   {
                    printf("%d) Sabotaggio\n", func_index+1);
                    ptr_func[func_index]=sabotaggio;
                    func_index++;
                   }
                 printf("%d) ESCI\n", func_index+1);
                 ptr_func[func_index]=esci;
                 func_index++;

                 elementi=2;
                 char buffer[elementi];
                 numero_caratteri=leggi_riga(elementi, buffer);
                 choice=atoi(buffer);
              } while((choice<1)||(choice>func_index)||
                      (numero_caratteri>2)||(numero_caratteri==0));

              (*ptr_func[choice-1]) ();   //chiamata funzione di gioco

              break;
          }  // Fine switch

          n_astro=0;                 //sezione notifica vittoria

          for (int i = 0; i < n_giocatori; i++)     //for di ricerca degli astronauti
            {
            if (ptr_giocatori[i].stato==astronauta)
              {
              n_astro++;
              }
            }
          if (n_astro==0)
          {
            printf(GREEN_INFO
              "TUTTI GLI ASTRONAUTI SONO STATI ELIMINATI, GLI IMPOSTORI HANNO VINTO\n"
              RESET);
            return 0;
          }
          if (count_quest>=quest_da_finire)
          {
            printf(GREEN_INFO
              "TUTTE LE QUEST SONO STATE TERMINATE, GLI ASTRONAUTI HANNO VINTO\n"
              RESET);
            return 0;
          }
          if (fine_partita)
          {
            printf(GREEN_INFO"LA PARTITA E' TERMINATA\n"RESET);
            return 0;
          }
        }              // Fine for dei turni
      } while(true);   // Fine loop del round
  return 0;
}                  // Fine gioca


int termina_gioco()
{
  int iter;
  int numero_caratteri;
  int elementi;
  int choice;


  if (gioco_impostato)
      dealloca();

  iter=0;
  do
  {
    iter++;
    if (iter>1)
      {
        printf(RED_ERROR"\nRiprova: input non valido\n"RESET);
      }

    printf("\nAdesso si pongono due scelte\n\n");
    printf("1) Ritornare al menù principale per impostare una nuova partita\n");
    printf("2) Uscire definitivamente e dirci addio :( o arrivederci ;)\n");

    elementi=2;
    char buffer[elementi];
    numero_caratteri=leggi_riga(elementi, buffer);
    choice=atoi(buffer);

  } while((choice<1)||(choice>2)||(numero_caratteri>2)||(numero_caratteri==0));

  switch (choice)
    {
      case 1 : break;
      case 2 : exit(0);
    }

return 0;
}



int dealloca ()
{

  struct Stanza* ptr_room_cruiser;
  struct Stanza* ptr_temp;

#ifdef DEBUG_DEALLOCA
    printf("count_malloc=%d\n", count_malloc);
#endif
    free(ptr_giocatori);
    count_malloc-=sizeof(struct Giocatore) * n_giocatori;
#ifdef DEBUG_DEALLOCA
    printf("Giocatori deallocati, count_malloc=%d\n", count_malloc);
#endif

    ptr_room_cruiser=ptr_lista_stanze;

    while (ptr_room_cruiser!=NULL)
    {
      ptr_temp=ptr_room_cruiser->ptr_next;
      free(ptr_room_cruiser);
      count_malloc-=sizeof(struct Stanza);
#ifdef DEBUG_DEALLOCA
      printf("Stanza deallocata, count_malloc=%d\n", count_malloc);
#endif
      ptr_room_cruiser=ptr_temp;
    }
  return 0;
}             // Fine dealloca


int leggi_riga (int num, char * riga)
{
      int i;
      int ch;
      int n_caratteri;
      n_caratteri= 0;

      for (i=0; i<num; i++) riga[i]='1'; //inizializzazione riga
      do
      {
        ch=getchar();  //getchar rirorna un int per recepire EOF
           if (n_caratteri<num)
             {
              riga[n_caratteri]=ch;
             }
        n_caratteri++;
      }
      while (ch != '\n');

      for (i=0; i<num; i++) {
        switch (riga[i]) {
          case '0': if (i==0) return 0; // no leading 0
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9': break;
          case ' ': return 0;  // no blank in input
          case '\n':if (i==0) return 0; // no solo new line
                    break;
          default:  return 0;
        } // Fine switch
      }   // Fine for di analisi
      return n_caratteri;
}               //Fine leggi_riga



 int stampa_giocatori()
 {

   int index;
   int name;
   int status;

   if (n_giocatori == 8)
      printf("\nGli %d giocatori sono:\n", n_giocatori);
   else
      printf("\nI %d giocatori sono:\n", n_giocatori);

   for (index = 0; index < n_giocatori; index++)
   {
     name=ptr_giocatori[index].nome;
     status=ptr_giocatori[index].stato;
     printf("Giocatore %12s stato %s\n", arr_nomi[name], arr_stato[status]);
#ifdef DEBUG_GIOCATORI
     printf("posizione: %p\n", ptr_giocatori[index].position);
#endif
   }
   return 0;
 }            // Fine stampa_giocatori



 _Bool inizia_gioco()
 {
   int iter;
   int numero_caratteri;
   int elementi;
   int choice;

   iter=0;
   do
   {
     iter++;
     if (iter>1)
       {
         printf(RED_ERROR"\nRiprova: input non valido\n"RESET);
       }

     printf("\nSi vuole giocare con queste impostazioni?\n\n");
     printf("1) Sì \n");
     printf("2) No \n");

     elementi=2;
     char buffer[elementi];
     numero_caratteri=leggi_riga(elementi, buffer);
     choice=atoi(buffer);

   } while((choice<1)||(choice>2)||(numero_caratteri>2)||(numero_caratteri==0));

   switch (choice)
     {
       case 1 : return true;
       case 2 : free(ptr_giocatori);
                count_malloc-=sizeof(struct Giocatore) * n_giocatori;
     }
     return false;
 }    // Fine inizia_gioco



 struct Stanza * set_stanza (struct Stanza* ptr_set_stanza)
 {
   int percentage;

#ifdef DEBUG_SET_STANZA
   printf("Valore ptr_set_stanza %p\n", ptr_set_stanza);
#endif
   ptr_set_stanza = malloc(sizeof(struct Stanza));
#ifdef DEBUG_SET_STANZA
   printf("Valore ptr_set_stanza dopo malloc  %p\n", ptr_set_stanza);
#endif
   count_malloc+=sizeof(struct Stanza);
   n_stanze++;

#ifdef DEBUG_SET_STANZA
   printf("Contatore memoria allocata: %d\n", count_malloc);
   printf("Numero delle stanze: %d\n", n_stanze);
#endif

   percentage=random(100)+1;

   if (percentage<=25)
     {
       ptr_set_stanza->room_type=botola;
       n_botole++;
     }
   else if (percentage<=40)
      {
       ptr_set_stanza->room_type=quest_doppia;
      }
   else if (percentage<=70)
      {
        ptr_set_stanza->room_type=quest_semplice;
      }
   else
      {
        ptr_set_stanza->room_type=vuota;
      }

  ptr_set_stanza->avanti=NULL;
  ptr_set_stanza->sinistra=NULL;
  ptr_set_stanza->destra=NULL;
  ptr_set_stanza->ptr_next = NULL;
  ptr_set_stanza->emergenza_chiamata=false;

  return ptr_set_stanza;
}             // Fine set_stanza



int dummy()
{
  return 0;
}



int stai_fermo()
{
  return 0;
}



int avanza()
{

  int iter=0;
  int numero_caratteri;
  int elementi;
  int choice;


  do {

      iter++;
      if (iter>1)
       {
        printf(RED_ERROR"\nRiprova: input non valido\n\n"RESET);
       }

      printf("\nIn quale direzione si vuole procedere?\n");
      printf("1) avanti\n");
      printf("2) destra\n");
      printf("3) sinistra\n");

      elementi=2;
      char buffer[elementi];
      numero_caratteri=leggi_riga(elementi, buffer);
      choice=atoi(buffer);

    } while ((choice<1)||(choice>3)||(numero_caratteri>2)||(numero_caratteri==0));

    switch (choice)
    {
      case 1: if (ptr_curr_room->avanti==NULL)
              {
                ptr_new_room=set_stanza(ptr_new_room);
                ptr_curr_room->avanti=ptr_new_room;
              } else {
                ptr_giocatori[curr_gio].position=ptr_curr_room->avanti;
                printf("Il giocatore %s si trova in una stanza: %s\n",
                      arr_nomi[ptr_giocatori[curr_gio].nome],
                      arr_tipo_stanza[ptr_giocatori[curr_gio].position->room_type]);
                return 0;
              }
              break;
      case 2: if (ptr_curr_room->destra==NULL) {
                ptr_new_room=set_stanza(ptr_new_room);
                ptr_curr_room->destra=ptr_new_room;
              } else {
                ptr_giocatori[curr_gio].position=ptr_curr_room->destra;
                printf("Il giocatore %s si trova in una stanza: %s\n",
                      arr_nomi[ptr_giocatori[curr_gio].nome],
                      arr_tipo_stanza[ptr_giocatori[curr_gio].position->room_type]);
                return 0;
              }
                break;
      case 3: if (ptr_curr_room->sinistra==NULL)
              {
                ptr_new_room=set_stanza(ptr_new_room);
                ptr_curr_room->sinistra=ptr_new_room;
              } else {
                ptr_giocatori[curr_gio].position=ptr_curr_room->sinistra;
                printf("Il giocatore %s si trova in una stanza: %s\n",
                      arr_nomi[ptr_giocatori[curr_gio].nome],
                      arr_tipo_stanza[ptr_giocatori[curr_gio].position->room_type]);
                return 0;
              }
    }

    ptr_new_room->stanza_precedente=ptr_curr_room;      //aggiornamento lista geografica
    ptr_curr_room=ptr_new_room;

    ptr_latest_room->ptr_next=ptr_new_room;             //aggiornamento lista cronologica
    ptr_latest_room=ptr_new_room;

    ptr_giocatori[curr_gio].position=ptr_new_room;      //aggiornamento posizione giocatore
    printf(GREEN_INFO"Il giocatore %s si è spostato in una stanza: %s\n"RESET,
          arr_nomi[ptr_giocatori[curr_gio].nome],
          arr_tipo_stanza[ptr_giocatori[curr_gio].position->room_type]);

    return 0;
}                     // Fine avanza



int esegui_quest()
{
  if (ptr_curr_room->room_type==quest_semplice)
  {
    count_quest++;
    printf(GREEN_INFO"Quest semplice eseguita, completate %d quest su %d\n"RESET,
          count_quest, quest_da_finire);
  } else {
    count_quest+=2;
    printf(GREEN_INFO"Quest doppia eseguita, completate %d quest su %d\n"RESET, count_quest, quest_da_finire);
  }

  ptr_curr_room->room_type=vuota;

  return 0;
}                      // Fine esegui quest



int chiamata_emergenza()
{
  int index;
  int n_astro_presenti=0;
  int n_impo_presenti=0;
  int prob_astro;
  int prob_impo;
  int fate;

  ptr_curr_room->emergenza_chiamata=true;

  for (index = 0; index < n_giocatori; index++)
  {
    if ((ptr_giocatori[index].position==ptr_curr_room)&&(ptr_giocatori[index].stato==astronauta))
    {
      n_astro_presenti++;
    }
    if ((ptr_giocatori[index].position==ptr_curr_room)&&(ptr_giocatori[index].stato==impostore))
    {
      n_impo_presenti++;
    }
  }

  prob_astro=30+20*n_impo_presenti-30*(n_astro_presenti-1);
  prob_impo=30+20*n_astro_presenti-30*(n_impo_presenti-1);

  for (index = 0; index < n_giocatori; index++)
  {
    fate=random(100);
    if (((ptr_giocatori[index].position==ptr_curr_room)&&
        (ptr_giocatori[index].stato==astronauta)&&(fate<prob_astro))||
        ((ptr_giocatori[index].position==ptr_curr_room)&&
        (ptr_giocatori[index].stato==impostore)&&(fate<prob_impo)))
    {
      ptr_giocatori[index].stato=defenestrato;
      printf(GREEN_INFO"Il giocatore %s è stato defenestrato\n"RESET, arr_nomi[ptr_giocatori[index].nome]);
      return 0;
    }
  }

  printf(GREEN_INFO"Nessun giocatore è stato defenestrato\n"RESET);

  return 0;
}                           // Fine chiamata emergenza



int uccidi_astronauta()
{
  int iter;
  int numero_caratteri;
  int elementi;
  int choice;
  int selector;
  int n_astro_presenti;
  int n_astro_vicini=0;
  int astro_index[10];
  int fate;


  iter=0;
  do {

    iter++;
    if (iter>1)
    {
      printf(RED_ERROR"\nRiprova: input non valido\n"RESET);
    }

    selector=0;
    printf("\nQuale astronauta si vuole assassinare?\n");
    for (int index = 0; index < n_giocatori; index++)
    {
      if ((ptr_giocatori[index].position==ptr_curr_room)&&
          (ptr_giocatori[index].stato==astronauta))
      {
        astro_index[selector]=index;
        selector++;
        printf("%d) L'astronauta %s\n", selector, arr_nomi[ptr_giocatori[index].nome]);
      }
    }
    elementi=2;
    char buffer[elementi];
    numero_caratteri=leggi_riga(elementi, buffer);
    choice=atoi(buffer);
  } while((choice<1)||(choice>selector)||(numero_caratteri>2)||(numero_caratteri==0));

  ptr_giocatori[astro_index[choice-1]].stato=assassinato;
  printf(GREEN_INFO"L'astronauta %s è stato assassinato ed esce dal gioco\n"RESET,
          arr_nomi[ptr_giocatori[astro_index[choice-1]].nome]);

  n_astro_presenti=selector-1;
  for (int index = 0; index < n_giocatori; index++)
  {
    if ((ptr_giocatori[index].position==ptr_curr_room->stanza_precedente)&&(ptr_giocatori[index].stato==astronauta))
    {
      n_astro_vicini++;
    }
  }

  fate=random(100);
  if (fate<(50*n_astro_presenti+20*n_astro_vicini))
  {
    ptr_giocatori[curr_gio].stato=defenestrato;
    printf(GREEN_INFO"L'impostore %s è stato scoperto e defenestrato! Esce dal gioco\n"RESET,
          arr_nomi[ptr_giocatori[curr_gio].nome]);
  } else {
    printf(GREEN_INFO"L'impostore %s si è salvato e continuerà a boicottare il viaggio della Skelt\n"RESET,
          arr_nomi[ptr_giocatori[curr_gio].nome]);
  }
  return 0;
}                       //Fine uccidi_astronauta



int usa_botola()
{
  int room_rand;
  int max_room_rand=0;
  struct Stanza* ptr_room_cruiser;
  struct Stanza* ptr_botola;
  struct Stanza* ptr_stanza;

  ptr_room_cruiser=ptr_lista_stanze;

  if (n_stanze==1)
  {
    printf(GREEN_INFO"Non ci sono altre stanze, la posizione di %s rimane invariata\n"RESET,
          arr_nomi[ptr_giocatori[curr_gio].nome]);
    return 0;
  } else if (n_botole>1) {
    while (ptr_room_cruiser!=NULL)
    {
      if ((ptr_room_cruiser->room_type==botola)&&(ptr_room_cruiser!=ptr_curr_room))
      {
        do {
          room_rand=random(n_botole*100)+1;
        } while(room_rand==max_room_rand);

        if (room_rand>max_room_rand)
        {
          max_room_rand=room_rand;
          ptr_botola=ptr_room_cruiser;
        }
      }
      ptr_room_cruiser=ptr_room_cruiser->ptr_next;
    }
    ptr_giocatori[curr_gio].position=ptr_botola;
    printf(GREEN_INFO"Il giocatore %s si trova in un'altra stanza botola\n"RESET,
          arr_nomi[ptr_giocatori[curr_gio].nome]);
  } else {
    while (ptr_room_cruiser!=NULL)
    {
      if (ptr_room_cruiser!=ptr_curr_room)
      {
        do {
          room_rand=random(n_stanze*100)+1;
        } while(room_rand==max_room_rand);

        if (room_rand>max_room_rand)
        {
          max_room_rand=room_rand;
          ptr_stanza=ptr_room_cruiser;
        }
      }
      ptr_room_cruiser=ptr_room_cruiser->ptr_next;
    }
    ptr_giocatori[curr_gio].position=ptr_stanza;
    printf(GREEN_INFO"Il giocatore %s si trova in un'altra stanza %s\n"RESET,
    arr_nomi[ptr_giocatori[curr_gio].nome], arr_tipo_stanza[ptr_stanza->room_type]);
  }
  return 0;
}                       // Fine uccidi_astronauta



int sabotaggio()
{
  ptr_curr_room->room_type=vuota;
  printf(GREEN_INFO"Stanza sabotata con successo!\n"RESET);

  return 0;
}



int esci()
{
  fine_partita = true;
  return 0;
}
