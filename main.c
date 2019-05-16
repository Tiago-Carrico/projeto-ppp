#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//\\\\\\\\COMENTÁRIOS GERAIS\\\\\\\


//tem de ser lista ligada
typedef struct PDI * lPDI;
typedef struct PDI {
    char n_pdi[50];
    char descricao[256];
    char horario[50];
    lPDI PDIS;
}PDI;

//substituir os pdis por lista ligada
typedef struct CIDADE * lCIDADE;
typedef struct CIDADE {
    char n_cidade[50];
    lPDI PDIS;
    lCIDADE cidades;
}CIDADE;

typedef struct USER * lUSER;
typedef struct USER {
    char nome[100];
    char nascimento[30];
    char nr_telefone[20];
    char morada[50];
    char pdi_hot[50];
    lUSER users;
}USER;



lPDI cria_lista_PDIS() {
    lPDI aux;
    aux = (lPDI) malloc (sizeof (lPDI));
    if (aux != NULL) {
        strcpy(aux->n_pdi, "");
        strcpy(aux->descricao, "");
        strcpy(aux->horario, "");
        //aux->PDIS = cria_lista_PDIS;  -> incorreto mas e melhor deixar por agr caso seja preciso
        aux->PDIS = NULL;
    }
    return aux;
}

lCIDADE cria_lista_cidade() {
    lCIDADE aux;
    aux = (lCIDADE) malloc (sizeof (lCIDADE));
    if (aux != NULL) {
        strcpy(aux->n_cidade, "");
        aux->PDIS = cria_lista_PDIS();
        aux->cidades = NULL;
    }
    return aux;
}

int lista_vazia_CIDADES(lCIDADE lista) {
    return(lista->cidades == NULL ? 2 : 0);
}

void procura_lista_CIDADES(lCIDADE lista, char chave[], lCIDADE *ant, lCIDADE *actual) {
    *ant = lista;
    *actual = lista->cidades;
    while ((*actual) != NULL && (*actual)->n_cidade < chave){
        *ant = *actual;
        *actual = (*actual)->cidades;
    }
    if ((*actual) != NULL && ((*actual)->n_cidade != chave))
        *actual = NULL;
}

void insere_lista_CIDADES(lCIDADE lista, char it[]) {
    lCIDADE no;
    lCIDADE ant, inutil;
    no = (lCIDADE) malloc (sizeof(lCIDADE));    //reserva espaço para o nó
    if (no != NULL) {
        strcpy(no->n_cidade, it);
        procura_lista_CIDADES (lista, it, &ant, &inutil);
        no->PDIS = cria_lista_PDIS();
        no->cidades = ant->cidades;
        ant->cidades = no;
    }
}

void procura_lista_PDIS(lPDI lista, char chave[], lPDI *ant, lPDI *actual) {
    *ant = lista;
    *actual = lista->PDIS;
    while ((*actual) != NULL && ((*actual)->n_pdi < chave)){
        *ant = *actual;
        *actual = (*actual)->PDIS;
    }
    if ((*actual) != NULL && ((*actual)->n_pdi != chave))
        *actual = NULL;
}

void insere_lista_PDIS_nome(lPDI lista, char it[]) {
    lPDI no;
    lPDI ant, inutil;
    no = (lPDI) malloc (sizeof(lPDI));    //reserva espaço para o nó
    if (no != NULL) {
        strcpy(no->n_pdi, it);
        procura_lista_PDIS (lista, it, &ant, &inutil);
        //no->PDIS = cria_lista_PDIS();           //em comentario pois so deve criar nova lista depois do horario
        no->PDIS = ant->PDIS;
        ant->PDIS = no;
    }
}

void insere_lista_PDIS_desc(lPDI lista, char it[]) {
    lPDI no;
    lPDI ant, inutil;
    no = (lPDI) malloc (sizeof(lPDI));    //reserva espaço para o nó
    if (no != NULL) {
        strcpy(no->descricao, it);
        procura_lista_PDIS (lista, it, &ant, &inutil);
        //no->PDIS = cria_lista_PDIS;           em comentario pois so deve criar nova lista depois do horario
        no->PDIS = ant->PDIS;
        ant->PDIS = no;
    }
}

void insere_lista_PDIS_horario(lPDI lista, char it[1000]) {
    lPDI no;
    lPDI ant, inutil;
    no = (lPDI) malloc (sizeof(lPDI));    //reserva espaço para o nó
    if (no != NULL) {
        strcpy(no->horario, it);
        procura_lista_PDIS (lista, it, &ant, &inutil);

        no->PDIS = ant->PDIS;
        ant->PDIS = no;
        no->PDIS = cria_lista_PDIS();
    }
}

void imprime_lista_PDIS(lPDI lista) {
    lPDI l = lista->PDIS; //salta o header
    while (l) {
        printf("%s ", l->n_pdi);
        imprime_lista_PDIS(l->PDIS);
        l = l->PDIS;
    }
}

void imprime_lista_cidades(lCIDADE lista) {
    lCIDADE l = lista->cidades; //salta o header
    while (l) {
        printf("%s ", l->n_cidade);
        imprime_lista_PDIS(l->PDIS);
        l = l->cidades;
    }
}

//https://stackoverflow.com/questions/33326621/c-program-sort-a-text-file-with-records-alphabetical-order


int organizar_cidade(void *pa, void *pb) {
    return strcmp(((CIDADE*)pa)->n_cidade, ((CIDADE*)pb)->n_cidade);
}

int organizar_pdi(void *pa, void *pb) {
    return strcmp(((PDI*)pa)->n_pdi, ((PDI*)pb)->n_pdi);
}




int ler_ficheiro() {
    FILE *teste;
    char linha[2000];
    char copy_linha[1000];
    char nome_cidade[50];
    char nome_pdi[50];
    char descricao[1000];
    char horario[50];

    lPDI l_pdis;     //DANGER: nao sei se funciona, ver se e assim depois(pelo menos
    lCIDADE l_cidades;
    l_cidades = cria_lista_cidade();
    int count = 1; //counter do numero do pdi, reseta sempre que se vai para uma cidade diferente

    teste = fopen("D:\\Documentos\\Uni\\1a2s\\PPP\\projeto_ppp\\cmake-build-debug\\project.txt", "r");
    while(fgets(linha, 2000, teste)!= NULL) {

        if (linha[0]=='*') {
            count = 1; //reseta o counter de pdi
            strcpy(copy_linha, &linha[1]);
            strcpy(nome_cidade, copy_linha);    //adicionar o nome da cidade ao struct
            printf("%s", copy_linha);
            insere_lista_CIDADES(l_cidades, copy_linha);
            l_pdis = cria_lista_PDIS();    //criar lista de PDIS sempre que se mudar de cidade
        }

        else if (linha[0]=='&') {
            strcpy(copy_linha, &linha[1]);
            //strcpy(nome_pdi, copy_linha);  como nao vou adicionar tudo de uma vez nao deve ser necessario
            printf("PDI nr. %d -> %s", count, copy_linha); //legit esta merda nao tava a dar print de nada e taa a lixar o programa e do nada funcionou, nao sei que magia negra e mas nao mexas muito nisto.
            count++; //incrementa o counter do pdi
            insere_lista_PDIS_nome(l_pdis, copy_linha);     //falha depois/antes disto
        }

        else if (linha[0]=='#') {
            strcpy(copy_linha, &linha[1]);
            //strcpy(descricao, copy_linha);  como nao vou adicionar tudo de uma vez nao deve ser necessario
            printf("Descricao:%s", copy_linha);
            insere_lista_PDIS_desc(l_pdis, copy_linha);
        }

        else if (linha[0]=='$') {
            strcpy(copy_linha, &linha[1]);
            //strcpy(horario, copy_linha);  como nao vou adicionar tudo de uma vez nao deve ser necessario
            printf("Horario: %s", copy_linha);
            insere_lista_PDIS_horario(l_pdis, copy_linha);
        }

        else {
            printf("O ficheiro está corrupto");
        }
    }

    return 0;
}

int criar_user() {
    //iniciar variaveis para todos os dados necessarios
    char nome[100];
    char nascimento[30];
    char telefone[20];
    char morada[50];


    printf("Nome: \n");
    gets(nome);
    printf("Data de nascimento: \n");
    gets(nascimento);
    printf("Nr. telefone: \n");
    gets(telefone);
    printf("Morada: \n");
    gets(morada);


    /*                  ///////////TESTING PURPOSES ONLY//////////////
    printf("\nnome: %s", nome);
    //printf("\napelido: %s", apelido);
    printf("\ndata de nascimento: %s", nascimento);
    printf("\nnr. telefone: %s", telefone);
    printf("\nmorada: %s", morada);

    printf("\ntudo novamente: %s %s %s %s \n", nome, nascimento, telefone, morada); //para teste, verificar que tudo ficou dividido em diferentes variaveis
    */
    //atribuiçao de dados a struct do user. sera que invalida a necessidade da funcao assign?
    //USER user_atual = {nome, nascimento, telefone, morada}; //probs vai ser usada mais para ler do ficheiro e preencher a struct do que a criar o user, mas fica aqui por motivos de testing.
    USER user_atual;
    strcpy(user_atual.nome, nome);
    strcpy(user_atual.nascimento, nascimento);
    strcpy(user_atual.nr_telefone, telefone);
    strcpy(user_atual.morada, morada);
    //testes da struct, parece atribuir bem os elementos, mas ja falhou uma vez, necessita de testing posterior

    //printf("\nnome_struct: %s\nidade_struct: %s\nnrtelefone_struct: %s\nmorada_struct: %s", user_atual.nome, user_atual.nascimento, user_atual.nr_telefone, user_atual.morada);


    //abre ficheiro
    FILE* users; //criar var do ficheiro
    users = fopen("utilizadores.txt", "a"); //abrir documento texto
    fprintf(users, "£%s\n§%s\n@%s\n!%s\n", nome, nascimento, telefone, morada); //escrever os dados do user, £ para o nome, § para a idade, @ para o telefone
    fclose(users); //fechar ficheiro


    return 0;
}

void placeholder() {
    //so placeholder para switch, etc.
}


int menu() {
    int opcao;
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("Escreva um numero de acordo com a operaçao que pretende realizar:");
    printf("\n1)Ver todos os destinos possiveis");
    printf("\n2)Criar um novo utilizador");
    printf("\n3)Selecionar preferencias para um utilizador existente");
    printf("\n4)Remover PDIS favoritos de um utilizador");
    printf("\n5)Ver os PDI's pela sua popularidade");
    printf("\n6)Construir uma viagem baseada nos gostos de um utilizador");
    printf("\n7)Acabar a sessao");
    printf("\n---------------------------------------------------------------------------------------------------------------\n");
    scanf("%c", opcao);

    switch(opcao) {
        case '1':
            ler_ficheiro();
            menu();
        case '2':
            criar_user();
            menu();
        case '3':
            placeholder();
            menu();
        case '4':
            placeholder();
            menu();
        case '5':
            placeholder();
            menu();
        case '6':
            placeholder();
            menu();
        case '7':
            return 0;
        default:
            printf("Essa não é uma opcao possivel");
            menu();
    }
}


int main() {
    //menu();           //-> devera ficar ligado no final, desligado para testes com listas ligadas e ficheiros
    ler_ficheiro();
    //criar_user();     //-> testado, funciona ao escrever o user no file


    return 0;
}


//ver linha 115
/*
int assign(CIDADE *variable, const char *str,char *membro_struct) { //como e que raio e que torno m argumento da funçao num elemento da struct, de modo a poder escolher nos argumentos o membro da struct modificado?
    if(variable) {
        variable->n_cidade=(char*)calloc(strlen(str),sizeof(char));
        strncpy(variable->n_cidade,str,strlen(str));
    }
    return 0;
}
*/
