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

void mostrarQuartosVazios() {
    int i;
    printf("Quartos vazios: ");
    for (i = 0; i < MAX_QUARTOS; i++) {
        if (quartos[i] == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void ordenarHospedes() {
    int i, j;
    Hospede temp;

    for (i = 0; i < totalHospedes - 1; i++) {
        for (j = i + 1; j < totalHospedes; j++) {
            if (strcmp(hotel[i].nome, hotel[j].nome) > 0) { 
                temp = hotel[i];
                hotel[i] = hotel[j];
                hotel[j] = temp;
            }
        }
    }
}

void listarHospedes() {
    int i;

    ordenarHospedes(); 
    printf("Listando %d hóspedes:\n", totalHospedes);
    for (i = 0; i < totalHospedes; i++) {
        printf("Hóspede: %s, Quarto: %d\n", hotel[i].nome, hotel[i].quarto);
    }

void buscarHospede(char *nome) {
    int i;
    int encontrado = 0;

    for (i = 0; i < totalHospedes; i++) {
        if (strcmp(hotel[i].nome, nome) == 0) {
            printf("Hóspede encontrado: %s, Quarto: %d\n", hotel[i].nome, hotel[i].quarto);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Hóspede %s não encontrado.\n", nome);
    }


void editarHospede(char *nome, char *novoNome, int novoQuarto) {
    int i;
    int encontrado = 0;

    for (i = 0; i < totalHospedes; i++) {
        if (strcmp(hotel[i].nome, nome) == 0) {
            strcpy(hotel[i].nome, novoNome);
            hotel[i].quarto = novoQuarto;
            printf("Hóspede editado: %s, Quarto: %d\n", hotel[i].nome, hotel[i].quarto);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Hóspede %s não encontrado.\n", nome);
    }
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

void atualizarLista() {
    FILE *file = fopen("hospedes.txt", "w");
    int i;

    if (file == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    for (i = 0; i < totalHospedes; i++) {
        fprintf(file, "Hóspede: %s, Quarto: %d\n", hotel[i].nome, hotel[i].quarto);
    }

    fclose(file);

    printf("Lista de hóspedes atualizada.\n");
}

void limparArquivo() {
    FILE *file = fopen("hospedes.txt", "w");

    if (file == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    fclose(file);
    printf("Limpando a lista de hóspedes...");
    printf("Dados do arquivo 'hospedes.txt' foram apagados.\n");
}

int main() {
    char nome[MAX_NOME];
    int quarto;
    char nomeNovo[MAX_NOME];
    int opcao;
    lerHospede();
do {
      printf("Menu do Sistema de Registro de Hóspedes:\n");
      printf("1. Inserir hóspede\n"); 
      printf("2. Listar hóspedes por ordem alfabética\n");
      printf("3. Buscar hóspede\n");
      printf("4. Editar hóspede\n");
      printf("5. Liberar quarto\n");
      printf("6. Mostrar quartos vazios\n");
      printf("7. Salvar lista de hóspedes em arquivo\n");
      printf("8. Sair\n");
      printf("Escolha uma opção: ");
      scanf("%d", &opcao);
      getchar();

switch (opcao) {
        case 1:
          printf("Digite o nome do hóspede: ");
          scanf("%s", nome);
          printf("Digite o número do quarto: ");
          scanf("%d", &quarto);
          inserirHospede(nome, quarto);
          atualizarLista();
          break;
        case 2:
          listarHospedes();
          break;
        case 3:
          printf("Digite o nome do hóspede a ser buscado: ");
          scanf("%s", nome);
          buscarHospede(nome);
          break;
