//#define DEBUG_MAIN /* attiva codice debug di main */
//#define DEBUG_IMPOSTA /*attiva codice debug imposta_gioco*/
//#define DEBUG_GIOCA /*attiva codice debug gioca*/
//#define DEBUG_DEALLOCA /*attiva codice debug dealloca*/
//#define DEBUG_SET_STANZA /*attiva codice debug set_stanza*/
//#define DEBUG_GIOCATORI /* attiva codice debug stampa_giocatori*/


#include <stdbool.h>
#include <stdio.h>

#define random(x) rand() % x
#define randomize srand((unsigned)time(NULL))
#define ARANCIO "\x1b[38:5:208m"
#define BISTRO "\x1b[38:5:239m"
#define CIANO "\x1b[36m"
#define FUCSIA "\x1b[38:5:198m"
#define LILLA "\x1b[38:5:134m"
#define MAGENTA "\x1b[35m"
#define OCRA "\x1b[38:5:130m"
#define SOLIDAGO "\x1b[38:5:142m"
#define TURCHESE "\x1b[38:5:87m"
#define VERMIGLIO "\x1b[38:5:124m"
#define RED_ERROR "\x1b[38:5:9m"
#define GREEN_INFO "\x1b[38:5:10m"
#define RESET "\x1b[0m"

enum Stato_giocatore {astronauta, impostore, assassinato, defenestrato};
enum Nome_giocatore {arancio, bistro, ciano, fucsia, lilla, magenta, ocra, solidago, turchese, vermiglio};
enum Tipo_stanza {vuota, quest_semplice, quest_doppia, botola};

struct Stanza {
    struct Stanza* avanti;
    struct Stanza* sinistra;
    struct Stanza* destra;
    struct Stanza* stanza_precedente;
    struct Stanza* ptr_next;
    enum Tipo_stanza room_type;
    _Bool emergenza_chiamata;
  };

struct Giocatore {
    struct Stanza* position;
    enum Stato_giocatore stato;
    enum Nome_giocatore nome;
  };

// Funzioni non Static
int imposta_gioco ();
int gioca ();
int termina_gioco ();
int dealloca ();
int leggi_riga (int max_num, char * riga);

  _Bool gioco_impostato;
