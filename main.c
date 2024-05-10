// Definindo as bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

// Definindo a estrutura do nó da lista 
#define MAX_HOSPEDES 400 
#define MAX_NOME 50 
#define MAX_QUARTOS 100
#define MAX_HOSPEDES_POR_QUARTO 4

// Definindo a struct do Hóspede com dois atributos (nome e quarto)
typedef struct Hospede {
    char nome[MAX_NOME];
    int quarto;
} Hospede;

// Declaração da estrutura para armazenar informações dos hóspedes, juntamente com a variável para rastrear o total de hóspedes no hotel e um array para controlar a ocupação dos quartos no hotel
Hospede hotel[MAX_HOSPEDES];
int totalHospedes = 0;
int quartos[MAX_QUARTOS];

// Função para inicializar os quartos do hotel com o valor 0, indicando que estão vazios
void inicializarQuartos() {
    int i;
    for (i = 0; i < MAX_QUARTOS; i++) {
        quartos[i] = 0;
    }
}

// Função para inserir um novo hóspede no Hotel, primeiro ela verifica se o hotel está cheio, caso esteja, ela exibe uma mensagem de erro, caso esteja vazio, ela pede ao usuário o nome e o quarto do hóspede, e então insere o hóspede no hotel
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
    totalHospedes++;

    quartos[quarto]++;
}

// Função para ler o arquivo de entrada e inserir os hóspedes no Hotel
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

// Função para mostrar o quartos que estão vazios no Hotel
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

// Função para ordernar os hóspedes do Hotel pelo nome
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

// Função para mostrar os hóspedes do Hotel, ela chama primeiramente a função de ordernarHospedes para mostrar eles em ordem alfabetica.
void listarHospedes() {
    int i;

    ordenarHospedes(); 
    printf("Listando %d hóspedes:\n", totalHospedes);
    for (i = 0; i < totalHospedes; i++) {
        printf("Hóspede: %s, Quarto: %d\n", hotel[i].nome, hotel[i].quarto);
    }
}

// Função para buscar um hóspede no hotel pelo nome, caso o Hóspede esteja cadastrado, será retornado seu nome e o seu respectivo quarto, caso contrário, será exibido uma mensagem de erro.
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
}


// Função para editar um Hóspede, caso o hóspede esteja cadastrado, será solicitado o novo nome do hóspede (caso necessario, senão é só manter o nome) e o novo número do quarto (caso necessario, senão é só manter o número)
void editarHospede(char *nome, char *novoNome, int novoQuarto) {
    int i;
    int encontrado = 0;
    int temp;

    for (i = 0; i < totalHospedes; i++) {
        if (strcmp(hotel[i].nome, nome) == 0) {
            strcpy(hotel[i].nome, novoNome);
            temp = hotel[i].quarto;
            hotel[i].quarto = novoQuarto;
            quartos[temp]--;
            quartos[novoQuarto]++;

            printf("Hóspede editado: %s, Quarto: %d\n", hotel[i].nome, hotel[i].quarto);
            encontrado = 1;
            break;
        }
    }


    if (!encontrado) {
        printf("Hóspede %s não encontrado.\n", nome);
    }
}

// Função para liberar o quarto, removendo todos os hóspedes que nele estão. Primeiro ela verifica se há hospedes no quarto para depois remover.
void liberarQuarto(int quarto) {
    int i, j;
    int numHospedes = 0;
    for (i = 0; i < totalHospedes; i++) {
        if (hotel[i].quarto == quarto) {
            numHospedes++;
        } 

    }
    if (numHospedes == 0) {
        printf("Não há hóspedes no quarto %d.\n", quarto);
        return;

    }
    for (i = 0, j = 0; i < totalHospedes; i++) {
        if (hotel[i].quarto != quarto) {
            hotel[j] = hotel[i];
            j++;

        }

    }
    totalHospedes -= numHospedes;
    // define o quarto como 0
    quartos[quarto] = 0;
    printf("Todos os hóspedes do quarto %d foram removidos.\n", quarto);
}

// Função para salvar os hóspedes em um arquivo txt.
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

// Função para atualizar a lista de hóspedes no arquivo txt. É chamada toda vez que há uma atualização na estrutura de hóspedes.
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

// Função utilizada para limpar o arquivo de hóspedes toda vez que a opção 8 (sair do programa) do menu for chamada.
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
    lerHospede(); // toda vez que o programa inicia, é feito a leitura do arquivo de hóspedes e inserido no hotel.

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

  // switch case com a opção escolhida pelo usuário.
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
        case 4:
          printf("Digite o nome do hóspede a ser editado: ");
          scanf("%s", nome);
          printf("Digite o novo nome do hóspede: ");
          scanf("%s", nomeNovo);
          printf("Digite o novo número do quarto: ");
          scanf("%d", &quarto);
          editarHospede(nome, nomeNovo, quarto);
          atualizarLista();
          break;
        case 5:
          printf("Digite o número do quarto a ser liberado: ");
          scanf("%d", &quarto);
          liberarQuarto(quarto);
          atualizarLista();
          break;
        case 6:
          mostrarQuartosVazios();
          break;
        case 7:
          salvarHospedes();
          break;
        case 8:
          limparArquivo();
          printf("Saindo do sistema...\n");
          break;
          default:
          printf("Opção inválida. Tente novamente.\n");
          break; 
      } 
  } while (opcao != 8); // enquanto a opção for diferente de 8, o menu será exibido novamente.
  return 0;
}
