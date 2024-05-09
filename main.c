#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define MAX_HOSPEDES 400 
#define MAX_NOME 50 
#define MAX_QUARTOS 100
#define MAX_HOSPEDES_POR_QUARTO 4

typedef struct {
    char nome[MAX_NOME];
    int quarto;
} Hospede;

void inicializarQuartos() {
    int i;
    for (i = 0; i < MAX_QUARTOS; i++) {
        quartos[i] = 0;
    }
}

void inserirHospede(char *nome, int quarto) {
    if (totalHospedes >= MAX_HOSPEDES) {
        printf("Hotel cheio, não é possível inserir mais hóspedes.\n");
        return;
    }

    if (quartos[quarto] >= MAX_HOSPEDES_POR_QUARTO) {
        printf("Quarto %d já está cheio.\n", quarto);
        return;
    }

    strcpy(hotel[totalHospedes].nome, nome);
    hotel[totalHospedes].quarto = quarto;
    totalHospedes++

    quartos[quarto]++;
}

