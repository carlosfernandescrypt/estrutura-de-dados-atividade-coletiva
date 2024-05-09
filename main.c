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

void lerHospede() { 
    FILE *file = fopen("hospedes.txt", "r");
    char linha[MAX_NOME + 20];
    char nome[MAX_NOME];
    int quarto;

    if (file == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), file) != NULL) {
        if (sscanf(linha, "Hóspede: %[^,], Quarto: %d", nome, &quarto) == 2) {
            inserirHospede(nome, quarto);
        }
    }

    fclose(file);

    printf("Hóspedes lidos do arquivo 'hospedes.txt' e inseridos no hotel.\n");
}

void liberarQuarto(int quarto) {
    int i;
    int encontrado = 0;
    for (i = 0; i < totalHospedes; i++) {
        if (hotel[i].quarto == quarto) {
            memmove(&hotel[i], &hotel[i + 1], (totalHospedes - i - 1) * sizeof(Hospede));
            totalHospedes--;
            encontrado = 1;
        }
    }

    if (encontrado) {
        printf("Quarto %d liberado.\n", quarto);
        quartos[quarto] = 0;
    } else {
        printf("Quarto %d não está ocupado.\n", quarto);
    }
}

void salvarHospedes() {
    FILE *file = fopen("listadehospedes.txt", "w");
    int i;

    if (file == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    for (i = 0; i < totalHospedes; i++) {
        fprintf(file, "Hóspede: %s, Quarto: %d\n", hotel[i].nome, hotel[i].quarto);
    }

    fclose(file);

    printf("Lista de hóspedes salva com sucesso em 'listadehospedes.txt'.\n");
}
