# Progetto-finale-2020-Trannoi
Template progetto finale per l'esame di Programmazione Procedurale con Laboratorio a.a. 2020-2021.

Inserire

Nome: Lorenzo

Cognome: Gimona

Matricola: 332044


ed eventuali note sulla realizzazione del progetto, come nuove funzionalità aggiunte o modificate rispetto al testo del progetto assegnato.

ASPETTI FUNZIONALI

-Aggiunta colori per giocatori, errori e info di gioco
-Nel menu di gioco compaiono esclusivamente le azioni possibili al momento del suo turno 
-Se si uccide un astronauta è possibile scegliere la vittima
-Il turno di gioco viene randomizzato ad ogni round
-Dal menu principale viene data la possibilità di reimpostare il gioco 
-Al termine di una partita viene richiesto se si vuole uscire dal gioco o impostare una nuova partita 
-L'opzione termina gioco offre la'alternativa fra iniziare una nuova partita o uscire dal gioco


SCELTE IMPLEMENTATIVE

-E' stata implementata la funzione leggi_riga() per il controllo dell'input
-E' stata implementata la funzione dealloca() per liberare le allocazioni di memoria nello heap
-E' stata introdotta la compilazione condizionata per il debug di alcune funzioni
-E' stata implementata la funzione set_stanza() per centralizzare la creazione delle stanze
-I menù di gioca() si compongono dinamicamente in funzione delle azioni possibili per il giocatore mediante l'uso di un array di puntatori a funzione
-Alla struttura struct Stanza è stato aggiunto un campo "struct Stanza* ptr_next" per la realizzazione della linked list "lista_stanze", in tal modo ogni stanza    partecipa a due linked list, una cronologica in ordine di creazione (lista_stanze) ed una topografica (stanza_inizio)
-E' stata implementata la possibilità di abbandonare la partita anticipatamente attraverso la funzione esci()
-E' stata implementata una funzione specifica (stai_fermo()) fra le azioni possibili per il giocatore al fine di rimanere nella stanza in cui si trova
