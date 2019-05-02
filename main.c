#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//\\\\\\\\COMENTÁRIOS GERAIS\\\\\\\
//Probs vai ter de se usar listas ligadas par afazer a lista de pdi's escolhidos pelo user, ja que podem ser ilimitadas(o pdi hot pode ser apenas um elemento da struct, ja que e unico).
//^ainda e preciso fazer funcao que verifique a existencia de cidades/pdi's, porem e facil(?) tendo em conta o inicio da frase, o problema vai ser o programa nao permitir mudanças na pontuacao.
//ainda e preciso ver se e possivel criar structs com nomes definidos pelo user/ ficheiro, de forma a criar structs para users/cidades(e pdi's) atraves do ficheiro sem interaçao manual da nossa parte.

//tem de ser lista ligada
typedef struct PDI * lPDI;
typedef struct PDI {
    char n_pdi[50];
    char descricao[256];
    char horario[50];
    //struct PDI* next;
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

CIDADE Paris;
CIDADE Roma;


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



/*
lPDI cria_lista_PDIS(char* n_PDI, char* descricao, char* horario) {
    lPDI aux;
    aux = (lPDI) malloc (sizeof (lPDI));
    if (aux != NULL) {
        strcpy(aux->n_pdi, n_PDI);
        strcpy(aux->descricao, descricao);
        strcpy(aux->horario, horario);
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
        aux->PDIS = cria_lista_PDIS;
        aux->cidades = NULL;
    }
    return aux;
}

int lista_vazia_CIDADES(lCIDADE lista) {
    return(lista->cidades == NULL ? 2 : 0);
}

void procura_lista_CIDADES(lCIDADE lista, char chave, lCIDADE *ant, lCIDADE *actual) {
    *ant = lista;
    *actual = lista->cidades;
    while ((*actual) != NULL && strcmp((*actual)->n_cidade, chave)){
        *ant = *actual;
        *actual = (*actual)->cidades;
    }
    if ((*actual) != NULL && strcmp((*actual)->n_cidade, chave))
        *actual = NULL;
}

lCIDADE insere_lista_CIDADES(lCIDADE lista, char it[]) {
    lCIDADE no;
    lCIDADE ant, inutil;
    no = (lCIDADE) malloc (sizeof(lCIDADE));    //reserva espaço para o nó
    if (no != NULL) {
        strcpy(no->n_cidade, it);
        procura_lista_CIDADES (lista, it, &ant, &inutil);
        no->PDIS = cria_lista_PDIS;
        no->cidades = ant->cidades;
        ant->cidades = no;
    }
    return no;
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
*/
int ler_ficheiro() {
    FILE *teste;
    FILE *teste2;
    char linha[20];
    char* copy_linha;
    char nome_cidade[50];
    //int lista[10];
    //int i = 0; //arcaico, era ra funçao de lista abandonada
    int count = 1; //counter do numero do pdi, reseta sempre que se vai para uma cidade diferente
    /*
    //cria ficheiro
    teste = fopen("teste.txt", "w");
    fprintf(teste, "*Paris\n");
    fclose(teste);
     */

    //le linha e retira marcador(neste caso asterisco(*))
    teste2 = fopen("D:\\Documentos\\Uni\\1a2s\\PPP\\projeto_ppp\\cmake-build-debug\\project.txt", "r");
    while(fgets(linha, 20, teste2)!= NULL) {
        //printf("%s", linha);

        if (linha[0]=='*') {
            count = 1; //reseta o counter de pdi
            strcpy(copy_linha, &linha[1]);

            printf("%s", copy_linha);

            //strcpy(Paris.n_cidade, copy_linha);

            //assign(&Paris, copy_linha, Paris.n_cidade); meter tamanhos nas strings a pedido da stora quebrou a funlçao assign

            //lista[i] = copy_linha;
            //i += 1;

        }


        if (linha[0]=='#') {
            strcpy(copy_linha, &linha[1]);
            // strcpy(Paris -> pdi1, linha[1]);

            printf("PDI nr. %d -> %s", count, copy_linha); //legit esta merda nao tava a dar print de nada e taa a lixar o programa e do nada funcionou, nao sei que magia negra e mas nao mexas muito nisto.
            count++; //incrementa o counter do pdi
        }
    }

    /*
    fclose(teste2);
    for(int j = 0; j < sizeof lista; j++)
        printf("%s\n", lista[j]);
*/
    printf("\n%s", Paris.n_cidade); // da print do nome da cidade (usa FUck agr pois e a mais recente, e necessario arranjar metodo de criar struct para todos os paises)(pra que raio queria eu isto?)(UPDATE!!! acho que era so pra manutenao e verificar se a struct recebia como argumento a string, e possivel que se tenha de repetir manualmente para cada argumento)mais uma vitima de ainda nao saber criar novas structs com o nome do ficheiro.
    //printf("%s %s", Paris -> n_cidade, Paris -> pdi1);


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

    printf("\nnome: %s", nome);
    //printf("\napelido: %s", apelido);
    printf("\ndata de nascimento: %s", nascimento);
    printf("\nnr. telefone: %s", telefone);
    printf("\nmorada: %s", morada);

    printf("\ntudo novamente: %s %s %s %s \n", nome, nascimento, telefone, morada); //para teste, verificar que tudo ficou dividido em diferentes variaveis

    //atribuiçao de dados a struct do user. sera que invalida a necessidade da funcao assign?
    //USER user_atual = {nome, nascimento, telefone, morada}; //probs vai ser usada mais para ler do ficheiro e preencher a struct do que a criar o user, mas fica aqui por motivos de testing.
    USER user_atual;
    strcpy(user_atual.nome, nome);
    strcpy(user_atual.nascimento, nascimento);
    strcpy(user_atual.nr_telefone, telefone);
    strcpy(user_atual.morada, morada);
    //testes da struct, parece atribuir bem os elementos, mas ja falhou uma vez, necessita de testing posterior

    printf("\nnome_struct: %s\nidade_struct: %s\nnrtelefone_struct: %s\nmorada_struct: %s", user_atual.nome, user_atual.nascimento, user_atual.nr_telefone, user_atual.morada);


    //cria ficheiro
    FILE* users; //criar var do ficheiro
    users = fopen("utilizadores.txt", "a"); //abrir documento texto
    fprintf(users, "£%s\n§%s\n@%s\n!%s\n", nome, nascimento, telefone, morada); //escrever os dados do user, £ para o nome, § para a idade, @ para o telefone
    fclose(users); //fechar ficheiro


    return 0;
}

int main() {
    ler_ficheiro();
    //criar_user();     //-> testado, funciona ao escrever o user no file
    return 0;
}
