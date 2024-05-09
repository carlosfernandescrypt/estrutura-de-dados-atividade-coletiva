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

