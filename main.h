#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HOSPEDES 400
#define MAX_NOME 50
#define MAX_QUARTOS 100
#define MAX_HOSPEDES_POR_QUARTO 4

typedef struct {
    char nome[MAX_NOME];
    int quarto;
} Hospede;

void inicializarQuartos(); // 1
void inserirHospede(char *nome, int quarto);
void lerHospede();
void mostrarQuartosVazios();
void ordenarHospedes();
void listarHospedes();
void buscarHospede(char *nome);
void editarHospede(char *nome, char *novoNome, int novoQuarto);
void liberarQuarto(int quarto);
void salvarHospedes();
void atualizarLista();
void limparArquivo();

#endif // MAIN_H
