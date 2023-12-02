#include <stdio.h>
#include <string.h>
#include "sudoku.h"



int main () {
    casella_t griglia[DIM][DIM];
    casella_t grigliaVerifcaAus[DIM][DIM];
    char stringa[DIMSCHEMA];
    int scelta, esci;
    int vettIns[DIMINS];

    /*prima di mostrare il menù carico la la tabella di gioco*/
    caricaStringa(stringa, DIMSCHEMA);
    popolaGriglia(stringa, griglia, DIM);

    esci=1;
    do {
        visualizzaGriglia(griglia, DIM);
        /*Visualizzo il menù*/
        printf("\n\nMENU: \n%d - avvia una nuova partita"
               "\n%d - inserisci valore"
               "\n%d - cancella valore"
               "\n%d - verifica soluzione attuale"
               "\n%d - carica una soluzione e verificala"
               "\n%d - riavvia partita attuale"
               "\n%d - esci",
               AVVIA, INSVAL, CANCVAL, VERIFICAGRIGLIA, CARICAEVERIFICA, RIAVVIA, ESCI);

        printf("\nScegli: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case ESCI:
                esci=0;
                break;

            case AVVIA:
                visualizzaGriglia(griglia, DIM);
                break;

            case INSVAL:
                if(acquisisciValore(vettIns, 3)){
                    inserisciValore(griglia, vettIns);
                };
                break;

            case CANCVAL:
                if(acquisisciValore(vettIns, 2)){
                    cancellaValore(griglia, vettIns);
                };
                break;

            case VERIFICAGRIGLIA:
                verificaSoluzione(griglia, DIM);
                break;

            case CARICAEVERIFICA:
                caricaStringa(stringa, DIMSCHEMA);
                popolaGriglia(stringa, griglia, DIM);
                verificaSoluzione(griglia, DIM);
                break;

            case RIAVVIA:
                riavvia(griglia, DIM);
                break;
        }
    } while(esci);
    printf("Grazie Arrivederci");

    return 0;
}

void popolaGriglia(char schema[], casella_t griglia[][DIM], int dim) {
    int i, j, k;

    for (i=0, k=0; i<DIM; i++) {
        for (j=0; j<DIM; j++) {
            if (schema[k] != '_') {
                griglia[i][j].num = schema[k] - '0'; /*FIXME chiedere STOI()*/
                griglia[i][j].lock = 1;
            } else {
                griglia[i][j].num = 0;
                griglia[i][j].lock = 0;
            }
            k++;
        }
    }
}

int acquisisciValore(int vett[], int dimIns){
    int i, corretto;

    if(dimIns == 3) {
        vett[2] = 0;
    }

    for(i=0, corretto = 1; i < dimIns && corretto; i++) {
        switch (i) {
            case 0:
                printf("Inserisci la Riga: ");
                break;
            case 1:
                printf("Inserisci la Colonna: ");
                break;
            case 2:
                printf("Inserisci il Valore: ");
                break;
        }
        scanf("%d", &vett[i]);
        if (vett[i] < 1 || vett[i] > 9){
            printf("Errore di Inserimento\n");
            corretto = 0;
        }
    }
    return  corretto;
}

void inserisciValore(casella_t griglia[][DIM], int vett[DIMINS]){
    if(griglia[vett[0]-1][vett[1]-1].lock == 0){
        griglia[vett[0]-1][vett[1]-1].num = vett[2];
    }else{
        printf("Non puoi modificare un valore Default!\n");
    }
}

void cancellaValore(casella_t griglia[][DIM], int vett[DIMINS]){
    if(griglia[vett[0]-1][vett[1]-1].lock == 0){
        griglia[vett[0]-1][vett[1]-1].num = 0;
    }else{
        printf("Non puoi cancellare un valore Default!\n");
    }
}

void verificaSoluzione(casella_t griglia[][DIM], int dim){
int i, j, k, l;
int valida;
    for (i = 0, valida = 1; i < dim && valida; i++) {
        for (j = 0; j < dim && valida; j++) {
            for (k = 1; k + j < dim && valida; k++) {
                if (griglia[i][j].num == griglia[i][k + j].num) {
                    valida = 0;
                }
            }
        }
    }
    if(valida) {
        for (i = 0, valida = 1; i < dim && valida; i++) {
            for (j = 0; j < dim && valida; j++) {
                for (k = 1; k + j < dim && valida; k++) {
                    if (griglia[j][i].num == griglia[k+j][i].num) {
                        valida = 0;
                    }
                }
            }
        }
    }

    if(valida){
        printf("Valida");
    }else{
        printf("NON VALIDA");
    }
}

void caricaStringa(char stringa[DIMSCHEMA], int dimSchema){
    int i, regolare;
    do{
        /*scanf("%s", stringa) FIXME: testi*/;
        /*Stringa Base*/
        //strcpy(stringa, "__68__2_______26_9_5_9_3____9___15____5____7_378___________6________713___7__8_46");
        /*Stringa Valida*/
        strcpy(stringa, "916874253743152689852963714294731568165489372378625491431596827689247135527318946");
        /*Stringa Non Valida*/
        //strcpy(stringa, "916874253734152689852963714294731568165489372378625491431596827689247135527318946");
        regolare = 1;
        if(strlen(stringa) == dimSchema) {
            for (i = 0, regolare = 1; stringa[i] != '\0' && regolare; i++) {
                if (!(stringa[i] >= '1' && stringa[i] <= '9') && stringa[i] != '_')
                    regolare = 0;
            }
        }else{
            regolare = 0;
        }
    }while(!regolare);
}

void riavvia(casella_t griglia[][DIM], int dim){
    int i, j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            if(griglia[i][j].lock == 0){
                griglia[i][j].num = 0;
            }
        }
    }
}

void visualizzaGriglia(casella_t griglia[][DIM], int dim){
    int i, j, k;
    printf("\n");
    for (k = 0; k < dim*3+4 ; k++) {
        if(k == 0 || k == 10 || k == 20 || k == 30){
            printf("+");
        }else{
            printf("-");
        }
    }
    printf("\n");
    for (i = 0; i < dim; i++) {
        printf("|");
        for (j = 0; j < dim; j++) {
            if (griglia[i][j].num != 0){
                printf("%d", griglia[i][j].num);
            }else{
                printf("0");
            }
            if(griglia[i][j].lock == 1){
                printf("*");
            } else {
                printf(" ");
            }
            printf(" ");
            if(j == 2 || j == 5 || j == 8){
                printf("|");
            }
        }
        printf("\n");
        if(i == 2 || i == 5 || i == 8){
            for (k = 0; k < dim*3+4 ; k++) {
                if(k == 0 || k == 10 || k == 20 || k == 30){
                    printf("+");
                }else{
                    printf("-");
                }
            }
            printf("\n");
        }

    }
}

