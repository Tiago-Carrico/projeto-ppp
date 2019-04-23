#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//\\\\\\\\COMENTÁRIOS GERAIS\\\\\\\
//Probs vai ter de se usar listas ligadas par afazer a lista de pdi's escolhidos pelo user, ja que podem ser ilimitadas(o pdi hot pode ser apenas um elemento da struct, ja que e unico).
//^ainda e preciso fazer funcao que verifique a existencia de cidades/pdi's, porem e facil(?) tendo em conta o inicio da frase, o problema vai ser o programa nao permitir mudanças na pontuacao.
//ainda e preciso ver se e possivel criar structs com nomes definidos pelo user/ ficheiro, de forma a criar structs para users/cidades(e pdi's) atraves do ficheiro sem interaçao manual da nossa parte.

//tem de ser lista ligada
typedef struct PDI {
    char * n_pdi;
    char * descricao;
}PDI;

//substituir os pdis por lista ligada
typedef struct CIDADE {
    char * n_cidade;
    PDI pdi1;
    PDI pdi2;
    PDI pdi3;
}CIDADE;

typedef struct USER {
    char* nome_completo;
    char* data_nascimento;
    char* nr_telefone;
    char* pdi_hot;
}USER;

CIDADE Paris;


//ver linha 115
int assign(CIDADE *variable, const char *str,char *membro_struct) { //como e que raio e que torno m argumento da funçao num elemento da struct, de modo a poder escolher nos argumentos o membro da struct modificado?
    if(variable) {
        variable->n_cidade=(char*)calloc(strlen(str),sizeof(char));
        strncpy(variable->n_cidade,str,strlen(str));
    }
    return 0;
}

void criar_ficheiro() {
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
        teste2 = fopen("teste.txt", "r");
        while(fgets(linha, 20, teste2)!= NULL) {
            //printf("%s", linha);

            if (linha[0]=='*') {
                count = 1; //reseta o counter de pdi
                strcpy(copy_linha, &linha[1]);

                printf("%s", copy_linha);

                //strcpy(Paris.n_cidade, copy_linha);

                assign(&Paris, copy_linha, Paris.n_cidade);

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
}

void criar_user() {
    //iniciar variaveis para todos os dados necessarios
    char dados_basic[100]; //todos os dados juntos
    char nome[100];
    char apelido[100];
    char nome_completo[100]; //nome depois de juntar o primeiro nome e apelido
    char idade[3];
    char telefone[10];

    printf("Informaçao necessaria para criar um perfil de utilizador:\nNome \tApelido \tDada de nascimento(dia/mes/ano) \t Nr. Telefone \t"); //apenas para informar do formato a inserir pelo utilizador

    fgets(dados_basic,100, stdin); //conseguir os dados inseridos, stdin significa input do teclado

    printf("\ntodos os dados:%s", dados_basic); //para teste, mostra todos os dados inseridos

    sscanf(dados_basic, "%s %s %s %s", nome, apelido, idade, telefone); //separa os dados nas suas devidas variaveis

    printf("\nnome: %s", nome);
    printf("\napelido: %s", apelido);
    printf("\nidade: %s", idade);
    printf("\nnr. telefone: %s", telefone);

    printf("\ntudo novamente: %s %s %s %s\n", nome, apelido, idade, telefone); //para teste, verificar que tudo ficou dividido em diferentes variaveis

    strcpy(nome_completo, nome); //adicionar o primeiro nome a variavel "nome_completo"
    strcat(nome_completo, " "); //adicionar espaço entre o nome e apelido
    strcat(nome_completo, apelido); // adicionar apelido a variavel "nome_completo"
    printf("\nsim, tudo novamente: %s\t%s\t%s\t", nome_completo, idade, telefone); //teste para verificar variavel "nome_completo" e verificar tudo novamente


    //atribuiçao de dados a struct do user. sera que invalida a necessidade da funcao assign?
    //como e que raio e que posso fazer com que o programa crie uma struct com o nome do user puxada do ficheiro, e a auto preencha?
    USER user_atual = {nome_completo, idade, telefone}; //probs vai ser usada mais para ler do ficheiro e preencher a struct do que a criar o user, mas fica aqui por motivos de testing.

    //testes da struct, parece atribuir bem os elementos, mas ja falhou uma vez, necessita de testing posterior

    printf("\nnome_struct: %s\nidade_struct: %s\nnrtelefone_struct: %s", user_atual.nome_completo, user_atual.data_nascimento, user_atual.nr_telefone);


    //cria ficheiro
    FILE* users; //criar var do ficheiro
    users = fopen("utilizadores.txt", "a"); //abrir documento texto
    fprintf(users, "£%s\n§%s\n@%s\n\n", nome_completo, idade, telefone); //escrever os dados do user, £ para o nome, § para a idade, @ para o telefone
    fclose(users); //fechar ficheiro

}

int main() {
    criar_ficheiro();
   criar_user();     //-> testado, funciona ao escrever o user no file
}

/*          //funcao que copiei para fazer a PUTA DA STRUCT, so falta fazer sem especificar o nome da struct/ fazer de modo automatico
int assign(name *variable, const char *str)
{
    if(variable)
    {
        variable->array=(char*)calloc(strlen(str),sizeof(char));
        strncpy(variable->array,str,strlen(str));

    }
    return 0;
}  */