#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#define DIM 9
#define DIMSCHEMA 81
#define AVVIA 1
#define INSVAL 2
#define CANCVAL 3
#define VERIFICAGRIGLIA 4
#define CARICAEVERIFICA 5
#define RIAVVIA 6
#define ESCI 0
#define DIMINS 3

typedef struct {
    int num;
    int lock;
}casella_t;

/*popola la griglia con gli elementi aggiunti tramite funzione caricaStringa ad ogni riavvio*/
void popolaGriglia(char* schema, casella_t griglia[][DIM], int dim);

int acquisisciValore(int vett[], int dim);

/*aggiunge l'inserimento del valore all'interno della griglia di gioco*/
void inserisciValore(casella_t griglia[][DIM], int vett[]);

/*elimina il valore inserito dalla cella selezionate*/
void cancellaValore(casella_t griglia[][DIM], int vett[]);

/*verifica che la griglia sia coerente con le regole del sudoku*/
void verificaSoluzione(casella_t griglia[][DIM], int dim);

/*richiede e verifica l'inserimento di una stringa soluzione*/
void caricaStringa(char stringa[DIMSCHEMA], int dimSchema);

/*cancella tutti i numeri inseriti dall'utente mantenendo lo schema iniziale*/
void riavvia(casella_t griglia[][DIM], int);

/*visualizza lo stato attuale della griglia*/
void visualizzaGriglia(casella_t griglia[][DIM], int dim);

#endif //SUDOKU_SUDOKU_H
