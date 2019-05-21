
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 200
#define CHUNK 1024

/*LISTAS E ESTRUTURAS*/
typedef struct pdi *Lpdi;
typedef struct pdi
{
    char nome[TAM];
    char descricao[TAM];
    int abertura;
    int fecho;
    Lpdi prox;
    int popularidade;
}pontointeresse;

typedef struct cidade *Lcidade;
typedef struct cidade{
    char nome[TAM];
    int popularidade;
    Lpdi lista_pdi;
    Lcidade prox;
}cidades;

typedef struct user *Luser;
typedef struct user
{
    char nome[TAM];
    char morada[TAM];
    char idade[TAM];
    char telefone[TAM];
    Luser prox;
    Lpdi *hot;
    Lpdi *lista_pdi_user[20];
    Lcidade *best_local[3];
}dadospessoa;



Luser ler_dadospessoa(dadospessoa p,Luser lu){
    gets(p.nome);
    printf("Introduza o seu nome:\n");
    gets(p.nome);

    printf("Introduza a sua morada:\n");
    gets(p.morada);

    printf("Introduza a sua data de nascimento (yyyymmdd):\n");
    gets(p.idade);

    printf("Introduza o seu numero de telefone:\n");
    gets(p.telefone);

    p.hot = NULL;

    insere_lista_user(lu,p);

    /*imprime_lusers(lu);*/

    return lu;

    /*printf("%s\n",p.nome);
    printf("%s\n",p.morada);
    printf("%s\n",p.idade);
    printf("%s\n",p.telefone);*/
}

Luser lista_users(void){
    Luser aux;
    aux=(Luser)malloc(sizeof(dadospessoa));
    if (aux!=NULL) {
        strcpy(aux->nome,"");
        aux->prox=NULL;
    }
    return aux;
}

Lpdi lista_pdis(void){
    Lpdi aux;
    aux=(Lpdi)malloc (sizeof(pontointeresse));
    if(aux!=NULL){
        strcpy(aux->nome,"");
        aux->prox=NULL;
    }
    return aux;
}

Lcidade lista_cidades(void){
    Lcidade aux;
    aux=(Lcidade) malloc(sizeof(cidades));
    if (aux!=NULL){
        strcpy(aux->nome,"");
        aux->lista_pdi =NULL;
        aux->prox = NULL;
    }
    return aux;
}

Lcidade insere_listac (Lcidade lista,struct cidade c)
{
    Lcidade no;
    Lcidade ant;
    Lcidade inutil;
    no =(Lcidade) malloc(sizeof(cidades));
    if (no!=NULL) {
            strcpy(no->nome,c.nome);
            no->popularidade=c.popularidade;
            procura_lcidades (lista,c.nome,&ant,&inutil);
            no->lista_pdi=lista_pdis();
            no->prox=ant->prox;
            ant->prox=no;
}
    return no;
}

void insere_lista_user(Luser lista,struct user u)
{
    Luser no;
    Luser ant;
    Luser inutil;
    no =(Luser) malloc(sizeof(dadospessoa));
    if (no!=NULL) {
        strcpy(no->nome,u.nome);
        strcpy(no->morada,u.morada);
        strcpy(no->idade,u.idade);
        strcpy(no->telefone,u.telefone);
        if (u.hot == NULL) {
            no->hot = NULL;
        }
        no->best_local[0] = NULL;
        no->best_local[1] = NULL;
        no->best_local[2] = NULL;

        no->lista_pdi_user[0] = NULL;
        /*printf("Antes de procurar na lista de user");*/
        procura_user(lista,u.nome,&ant,&inutil);
        /*printf("Depois de procurar na lista de user\n");*/
       no->prox=ant->prox;
        ant->prox=no;
   }
    return no;
}

Lpdi insere_listapdi (Lpdi lista, struct pdi p)
{
    Lpdi no;
    Lpdi ant;
    Lpdi inutil;
    no =(Lpdi) malloc(sizeof(pontointeresse));
    if (no!=NULL) {
            strcpy(no->nome,p.nome);
            strcpy(no->descricao,p.descricao);
            no->fecho=p.fecho;
            no->abertura=p.abertura;
            no->popularidade=p.popularidade;

            procura_lpdi (lista,p.nome,&ant,&inutil);
            no->prox=ant->prox;
            ant->prox=no;
}
    return no;
}


void imprime_lcidades (Lcidade lista){
    Lcidade l=lista->prox;
    while(l){
        printf("%s\n",l->nome);
        /*printf("Seus pontos de interesse:\n");*/
        imprime_lpdi(l->lista_pdi);
        printf("\n");
        l=l->prox;
    }
}

void imprime_viagem (Lcidade *lista) {
    printf("\nENTROU1\n");
    Lcidade l=(*lista)->prox;
    int sum=1;
    while (&l != NULL) {
        printf("\nENTROU2\n");
        printf("%d local a visitar : %s\n",sum,l->nome);
        printf("\nENTROU3\n");
        printf("    Pontos de interesse a visitar neste local: \n");
        printf("\nENTROU4\n");
        imprime_lpdi(l->lista_pdi);
        printf("\nENTROU5\n");
        printf("\n");
        printf("\nENTROU6\n");
        l=l->prox;
    }
}

void imprime_lcidades_popularidade (Lcidade lista) {
    Lcidade l=lista->prox;
    while(l){
        printf("%s [POPULARIDADE : %d]\n",l->nome,l->popularidade);
        /*printf("Seus pontos de interesse:\n");*/
        imprime_lpdi_popularidade(l->lista_pdi);
        printf("\n");
        l=l->prox;
    }
}

void imprime_lcidades_mais_populares (Lcidade lista) {
    Lcidade l=lista->prox;
    while (l) {
        if (l->popularidade >= 2) {
            printf("%s [POPULARIDADE : %d]\n",l->nome,l->popularidade);
            imprime_lpdi_mais_populares(l->lista_pdi);
            printf("\n");
            l=l->prox;
        } else {
            imprime_lpdi_mais_populares(l->lista_pdi);
            l=l->prox;
        }

    }
}

void imprime_lpdi_mais_populares (Lpdi lista) {
    Lpdi l=lista->prox;
    while (l) {
        if (l->popularidade>=2) {
            printf("    --> %s [POPULARIDADE : %d]\n",l->nome,l->popularidade);
            l=l->prox;
        } else {
            l=l->prox;
        }
    }
}

void imprime_lpdi_popularidade (Lpdi lista) {
    Lpdi l=lista->prox;
    while(l){
        printf("    --> %s [POPULARIDADE : %d]\n",l->nome,l->popularidade);
        l=l->prox;
    }
}



void imprime_lusers (Luser lista) {
    Luser l = lista->prox;
    while (l) {
        printf("\n");
        printf("%s\n",l->nome);
        printf("%s\n",l->morada);
        printf("%s\n",l->idade);
        printf("%s\n",l->telefone);
        if (l->hot == NULL) {
            printf("Este utilizador ainda nao definiu o seu ponto hot\n");
        } else {
            printf("Seu ponto hot: %s\n",*(l->hot));
        }
        if (l->best_local[0]==NULL) {
            printf("Este utilizador ainda nao definiu os seus locais preferidos\n");
        } else {
            printf("Locais preferidos: %s, %s, %s.\n",l->best_local[0],l->best_local[1],l->best_local[2]);
        }

        if (l->lista_pdi_user[0]==NULL) {
            printf("Este utilizador ainda nao definiu os seus pontos de interesse preferidos\n");
        } else {
            printf("Pontos de interesse preferidos:\n");
            int i;
            for (i=0;i<20;i++) {
                if (l->lista_pdi_user[i]!=NULL) {
                    printf("    ->%s\n",l->lista_pdi_user[i]);
                } else {
                    break;
                }
            }
        }
        printf("\n");
        l=l->prox;
    }
}


void procura_lcidades (Lcidade lista,char chave[],Lcidade *ant,Lcidade *actual)
{
    *ant=lista;
    *actual=lista->prox;
    while ((*actual)!=NULL && strcmp((*actual)->nome,chave))
{
    *ant=*actual;
    *actual=(*actual)->prox;
}
    if ((*actual) != NULL && strcmp((*actual)->nome,chave))
        *actual=NULL;
}

Lcidade procura_lcidades_best (Lcidade lista,char chave[],Lcidade *ant,Lcidade *actual)
{
    *ant=lista;
    *actual=lista->prox;
    while ((*actual)!=NULL && strcmp((*actual)->nome,chave))
{
    *ant=*actual;
    *actual=(*actual)->prox;
}
    if ((*actual) != NULL && strcmp((*actual)->nome,chave))
        *actual=NULL;
        return *actual;
}

Lpdi procura_phot(Lcidade lc,char chave[],Lcidade *ant,Lcidade *actual) {

    *ant=lc;
    *actual=lc->prox;
    Lpdi l1 = NULL;
    while ((*actual != NULL)) {

        l1=(*ant)->lista_pdi;

        while (l1!=NULL && strcmp(l1->nome,chave)!=0)
        {

            l1=l1->prox;

        }

        if (l1!=NULL && strcmp(l1->nome,chave)==0 ) {
            l1->popularidade++;
            return l1;
        }
        if (l1==NULL) {
            *ant=*actual;
            *actual=(*actual)->prox;
        }
    }
}



int lista_vazia_pdi(Lpdi lista)
{
    return (lista->prox== NULL ? 1 : 0);
}

Lpdi destroi_listapdi (Lpdi lista)
{
    Lpdi temp_ptr;
    while (lista_vazia_pdi(lista) == 0) {
            temp_ptr=lista;
    lista=lista->prox;
    free(temp_ptr);
    }
    free(lista);
    return NULL;
}



void procura_user (Luser lista,char chave[],Luser *ant,Luser *actual)
{

    *ant=lista;

    *actual=lista->prox;

    while ((*actual)!=NULL && strcmp((*actual)->nome,chave))
    {
        *ant=*actual;
        *actual=(*actual)->prox;
    }
    if ((*actual) != NULL && strcmp((*actual)->nome,chave))
        *actual=NULL;
}


Luser procura_user_troca (Luser lista,char chave[],Luser *ant,Luser *actual)
{

    *ant=lista;
    *actual=lista->prox;
    while ((*actual)!=NULL && strcmp((*actual)->nome,chave))
{
    *ant=*actual;
    *actual=(*actual)->prox;
}
    if ((*actual) != NULL && strcmp((*actual)->nome,chave))
        *actual=NULL;
    return *actual;
}

Luser procura_user_por_telefone_troca (Luser lista,char chave[],Luser *ant,Luser *actual)
{

    *ant=lista;
    *actual=lista->prox;
    while ((*actual)!=NULL && strcmp((*actual)->telefone,chave))
{
    *ant=*actual;
    *actual=(*actual)->prox;
}
    if ((*actual) != NULL && strcmp((*actual)->telefone,chave))
        *actual=NULL;
    return *actual;
}




void voltar_menu(Luser lu,Lcidade lc) {
    int i;
    printf("Deseja voltar ao menu principal?\n");
            printf("(1) - Sim. (2) - Nao\n");
            scanf("%d",&i);
            while ((i<1)||(i>2)){
            printf("\nIndique corretamente o que executar\n");
            scanf("%d",&i);
            }
                if (i==1) {
                    menu(lu,lc);
                } else if (i==2) {
                    system("cls");
                    printf("Sessao terminada\n");
                    return 0;
                }
}


double conta_utilizadores(Luser lu) {
    Luser l = lu->prox;
    double sum=0;

    while (l) {

        sum++;
        l=l->prox;
    }
    return sum;
}

double compara_locs (Luser lu,Luser utilizador) {
    Luser l = lu->prox;
    double sum=0;

    while (l) {

        if (l->best_local[0]==NULL) {
            l=l->prox;
            continue;
        } else if ((utilizador->best_local[0] == l->best_local[0] ) || (utilizador->best_local[0] == l->best_local[1] ) || (utilizador->best_local[0] == l->best_local[2] )) {
            sum++;
            l=l->prox;
        } else if ((utilizador->best_local[1] == l->best_local[0] ) || (utilizador->best_local[1] == l->best_local[1] ) || (utilizador->best_local[1] == l->best_local[2] )) {
            sum++;
            l=l->prox;
            } else if ((utilizador->best_local[2] == l->best_local[0] ) || (utilizador->best_local[2] == l->best_local[1] ) || (utilizador->best_local[2] == l->best_local[2] )) {
            sum++;
            l=l->prox;
            }
    }
    return sum;
}

void procura_lpdi (Lpdi lista,char chave[],Lpdi *ant,Lpdi *actual)
{
    *ant=lista;
    *actual=lista->prox;
    while ((*actual)!=NULL && strcmp((*actual)->nome,chave))
{
    *ant=*actual;
    *actual=(*actual)->prox;
}
    if ((*actual) != NULL && strcmp((*actual)->nome,chave))
        *actual=NULL;
}




void avalia_viagem(Luser lu,Lcidade lc,Luser utilizador) {

    double nu = conta_utilizadores(lu);
    double locs = compara_locs (lu,utilizador);

    double p1 = (locs/nu)*100;

    /*double hots = compara_hot (lu,utilizador);*/

   /* printf("Numero de utilizadores c o seu ponto hot na viagem criada: %f",hots);*/

    printf("Percentagem de utilizadores com pelo menos 1 local na viagem: %f\n",p1);

}



void imprime_cidade (Lcidade *cidade){
        /*printf("%s\n",lista->nome);*/
        /*printf("Seus pontos de interesse:\n");*/
        imprime_lpdi((*cidade)->lista_pdi);
        printf("\n");
}

void imprime_lpdi(Lpdi lista){
    Lpdi l=lista->prox;
    while(l){
        printf("    %s [POPULARIDADE %d]. Horario de abertura %dh, horario de fecho %dh. Descricao: %s\n",l->nome,l->popularidade,l->abertura,l->fecho,l->descricao);
        l=l->prox;
    }
}



void menu(Luser lu,Lcidade lc) {
    int i;
    system("cls");
    printf("Indique o que pretende executar\n\n");
    printf("(1) - Registar utilizadores\n");
    printf("(2) - Alterar dados de utilizador\n");
    printf("(3) - Listagem de locais com respectivo pontos de interesse e suas informacoes (por ordem alfabetica)\n");
    printf("(4) - Visualizar popularidade dos locais e respectivos pontos de interesse\n");
    printf("(5) - Definir ponto hot de um utilizador\n");
    printf("(6) - Definir os 3 locais preferidos de um utilizador\n");
    printf("(7) - Definir os seus pontos de interesse preferidos\n");
    printf("(8) - Ver utilizadores registados no sistema\n");
    printf("(9) - Criar Viagem\n");
    printf("(10) - Listagem de locais e pontos de interesse mais populares (com popularidade superior a 2)\n");
    printf("(11) - Sair\n");

    scanf("%d",&i);
    while ((i<1)||(i>11)){
        printf("\nIndique corretamente o que executar\n");
        scanf("%d",&i);
    }

    if (i==1) {
        system("cls");
        printf("Escolheu a opcao (1) - Registar utilizadores\n");
        struct user aluno;
        ler_dadospessoa(aluno,lu);
        system("cls");
        printf("O SEU REGISTO FOI EFETUADO COM SUCESSO\n\n");
        voltar_menu(lu,lc);
    } else if (i==11) {
        system("cls");
        printf("Sessao terminada\n");
        return 0;
    } else if (i==2) {
        system("cls");
        printf("Escolheu a opcao (2) - Alterar dados de utilizador\n");
        printf("Indique o numero de telefone do utilizador ao qual deseja alterar o registo\n");
        char telefone[TAM];
        gets(telefone);
        gets(telefone);
        Luser ant;
        Luser inutil;
        Luser procurado=procura_user_por_telefone_troca(lu,telefone,&ant,&inutil);
        if (procurado==NULL) {
            printf("Nao foi encontrado o utilizador indicado\n");
            voltar_menu(lu,lc);
        } else {
            system("cls");
            printf("Os dados atuais desse utilizador sao os seguintes: \n");
            printf("Nome: %s\n",procurado->nome);
            printf("Morada: %s\n",procurado->morada);
            printf("Data de nascimento: %s\n",procurado->idade);
            printf("Telefone: %s\n",procurado->telefone);
            printf("\n");
            printf("Introduza agora os dados correctos do utilizador %s\n\n",procurado->nome);


            printf("Introduza o seu nome:\n");
            gets(procurado->nome);

            printf("Introduza a sua morada:\n");
            gets(procurado->morada);

            printf("Introduza a sua data de nascimento (yyyymmdd):\n");
            gets(procurado->idade);

            printf("Introduza o seu numero de telefone:\n");
            gets(procurado->telefone);
            system("cls");
            printf("REGISTO ALTERADO COM SUCESSO\n");
            printf("\n");
            voltar_menu(lu,lc);

        }



    } else if (i==8) {
        system("cls");
        imprime_lusers(lu);
        voltar_menu(lu,lc);
    } else if (i==3) {
        system("cls");
        printf("LOCAIS DISPONIVEIS POR ORDEM ALFABETICA\n\n");
        imprime_lcidades(lc);
        printf("\n");
        printf("------------------------------------------\n");
         voltar_menu(lu,lc);
    } else if (i==4) {
        system("cls");
        imprime_lcidades_popularidade(lc);
        printf("\n");
        printf("------------------------------------------\n");
        voltar_menu(lu,lc);
    } else if (i==5) {
        system("cls");
        printf("Indique o telefone do utilizador para o qual quer definir o seu ponto hot\n");
        char telefone[TAM];
        gets(telefone);
        gets(telefone);

        Luser ant;
        Luser inutil;
        Luser procurado=procura_user_por_telefone_troca(lu,telefone,&ant,&inutil);
        if (procurado==NULL) {
            system("cls");
            printf("Nao foi encontrado o utilizador indicado\n");
            voltar_menu(lu,lc);
        } else {
               system("cls");
             printf("\n");
        printf("%s\n",procurado->nome);
        printf("%s\n",procurado->morada);
        printf("%s\n",procurado->idade);
        printf("%s\n",procurado->telefone);
        if (procurado->hot == NULL) {
            printf("Este utilizador ainda nao definiu o seu ponto hot\n");
        } else {
            printf("Seu ponto hot: %s\n",*(procurado->hot));
        }
        if (procurado->best_local[0]==NULL) {
            printf("Este utilizador ainda nao definiu os seus locais preferidos\n");
        } else {
            printf("Locais preferidos: %s, %s, %s.\n",procurado->best_local[0],procurado->best_local[1],procurado->best_local[2]);
        }

        if (procurado->lista_pdi_user[0]==NULL) {
            printf("Este utilizador ainda nao definiu os seus pontos de interesse preferidos\n");
        } else {
            printf("Pontos de interesse preferidos:\n");
            int i;
            for (i=0;i<20;i++) {
                if (procurado->lista_pdi_user[i]!=NULL) {
                    printf("    ->%s\n",procurado->lista_pdi_user[i]);
                } else {
                    break;
                }
            }
        }
            printf("\n");
            printf("Indique o nome do ponto de interesse que deseja definir como seu ponto hot\n");
            char nome[TAM];
            gets(nome);
            Lcidade ant;
            Lcidade actual;
            Lpdi procura = procura_phot(lc,nome,&ant,&actual);
            if (procura==NULL) {
                system("cls");
                printf("Nao foi encontrado o ponto de interesse indicado\n");
                voltar_menu(lu,lc);
            } else {
                 procurado->hot = &procura;
            procura->popularidade++;
            system("cls");
            printf("%s FOI DEFINIDO COMO SEU PONTO HOT\n");
            voltar_menu(lu,lc);
            }

    }
    } else if (i==6) {
        system("cls");
        printf("Indique o telefone do utilizador para o qual quer definir o seu ponto hot\n");
        char telefone[TAM];
        gets(telefone);
        gets(telefone);
        Luser ant;
        Luser inutil;
        Luser procurado=procura_user_por_telefone_troca(lu,telefone,&ant,&inutil);
        if (procurado==NULL) {
            system("cls");
            printf("Nao foi encontrado o utilizador indicado\n");
           voltar_menu(lu,lc);
        } else {
               system("cls");
             printf("\n");
        printf("%s\n",procurado->nome);
        printf("%s\n",procurado->morada);
        printf("%s\n",procurado->idade);
        printf("%s\n",procurado->telefone);
        if (procurado->hot == NULL) {
            printf("Este utilizador ainda nao definiu o seu ponto hot\n");
        } else {
            printf("Seu ponto hot: %s\n",*(procurado->hot));
        }
        if (procurado->best_local[0]==NULL) {
            printf("Este utilizador ainda nao definiu os seus locais preferidos\n");
        } else {
            printf("Locais preferidos: %s, %s, %s.\n",procurado->best_local[0],procurado->best_local[1],procurado->best_local[2]);
        }

        if (procurado->lista_pdi_user[0]==NULL) {
            printf("Este utilizador ainda nao definiu os seus pontos de interesse preferidos\n");
        } else {
            printf("Pontos de interesse preferidos:\n");
            int i;
            for (i=0;i<20;i++) {
                if (procurado->lista_pdi_user[i]!=NULL) {
                    printf("    ->%s\n",procurado->lista_pdi_user[i]);
                } else {
                    break;
                }
            }
        }
            printf("\n");
            int k;
            for(k=0;k<3;k++) {
                printf("Indique o seu %d local preferido\n",k+1);
                char nome[TAM];
                gets(nome);
                Lcidade ant;
                Lcidade actual;
                Lcidade cidade_procurada=procura_lcidades_best(lc,nome,&ant,&actual);
                if (cidade_procurada==NULL) {
                        system("cls");
                        printf("O local que indicou nao foi encontrado. Consulte a nossa lista de locais atraves do menu principal\n");
                        voltar_menu(lu,lc);

                } else {
                    cidade_procurada->popularidade++;
                    procurado->best_local[k] = cidade_procurada;
                    printf("%s foi adicionado aos seus locais preferidos\n\n",cidade_procurada->nome);
                }
            }
        }
        voltar_menu(lu,lc);
    } else if (i==7) {
        system("cls");
        printf("Indique o telefone do utilizador para o qual quer definir pontos de interesse preferidos\n");
        char telefone[TAM];
        gets(telefone);
        gets(telefone);
        Luser ant;
        Luser inutil;
        Luser procurado=procura_user_por_telefone_troca(lu,telefone,&ant,&inutil);
        if (procurado==NULL) {
            system("cls");
            printf("Nao foi encontrado o utilizador indicado\n");
           voltar_menu(lu,lc);
        } else {
            system("cls");
             printf("\n");
        printf("%s\n",procurado->nome);
        printf("%s\n",procurado->morada);
        printf("%s\n",procurado->idade);
        printf("%s\n",procurado->telefone);
        if (procurado->hot == NULL) {
            printf("Este utilizador ainda nao definiu o seu ponto hot\n");
        } else {
            printf("Seu ponto hot: %s\n",*(procurado->hot));
        }
        if (procurado->best_local[0]==NULL) {
            printf("Este utilizador ainda nao definiu os seus locais preferidos\n");
        } else {
            printf("Locais preferidos: %s, %s, %s.\n",procurado->best_local[0],procurado->best_local[1],procurado->best_local[2]);
        }

        if (procurado->lista_pdi_user[0]==NULL) {
            printf("Este utilizador ainda nao definiu os seus pontos de interesse preferidos\n");
        } else {
            printf("Pontos de interesse preferidos:\n");
            int i;
            for (i=0;i<20;i++) {
                if (procurado->lista_pdi_user[i]!=NULL) {
                    printf("    ->%s\n",procurado->lista_pdi_user[i]);
                } else {
                    break;
                }
            }
        }
            printf("\n");
            int n,i;
            printf("Indique quantos pontos de interesse quer definir como preferidos\n");
            scanf("%d",&n);

            for (i=0;i<n;i++) {
                char nome[TAM];
                if (i==0) {
                    gets(nome);
                }
                printf("Indique o seu %d ponto de interesse preferido\n",i+1);
                gets(nome);

                Lcidade ant;
                Lcidade actual;
                Lpdi procura = procura_phot(lc,nome,&ant,&actual);


                if (procura==NULL) {
                     system("cls");
                        printf("O ponto de interesse que indicou nao foi encontrada. Consulte a nossa lista de pontos de interesse atraves do menu principal\n");
                        voltar_menu(lu,lc);
                } else {
                    procurado->lista_pdi_user[i] = procura;
                    printf("%s foi adicionado aos seus pontos de interesse preferidos\n\n",procura->nome);
                }
            }
        }
        voltar_menu(lu,lc);
    } else if (i==10) {
        system("cls");
        imprime_lcidades_mais_populares(lc);
        printf("\n");
        printf("------------------------------------------\n");
        voltar_menu(lu,lc);
    } else if (i==9) {
        system("cls");
        printf("Indique o telefone do utilizador para o qual quer gerar uma viagem\n");
        char telefone[TAM];
        gets(telefone);
        gets(telefone);
        Luser ant;
        Luser inutil;
        Luser procurado=procura_user_por_telefone_troca(lu,telefone,&ant,&inutil);
        if (procurado==NULL) {
            system("cls");
            printf("Nao foi encontrado o utilizador indicado\n");
            voltar_menu(lu,lc);
        } else if (procurado->best_local[0]!=NULL) {
            system("cls");
            printf("\n");
            printf("%s\n",procurado->nome);
            printf("%s\n",procurado->morada);
            printf("%s\n",procurado->idade);
            printf("%s\n",procurado->telefone);
            if (procurado->hot == NULL) {
                printf("Este utilizador ainda nao definiu o seu ponto hot\n");
            } else {
            printf("Seu ponto hot: %s\n",*(procurado->hot));
            }
            if (procurado->best_local[0]==NULL) {
                printf("Este utilizador ainda nao definiu os seus locais preferidos\n");
            } else {
                printf("Locais preferidos: %s, %s, %s.\n",procurado->best_local[0],procurado->best_local[1],procurado->best_local[2]);
            }
            if (procurado->lista_pdi_user[0]==NULL) {
                printf("Este utilizador ainda nao definiu os seus pontos de interesse preferidos\n");
            } else {
                printf("Pontos de interesse preferidos:\n");
                int i;
                for (i=0;i<20;i++) {
                if (procurado->lista_pdi_user[i]!=NULL) {
                    printf("    ->%s\n",procurado->lista_pdi_user[i]);
                } else {
                    break;
                }
            }
        }
            printf("\n");
            printf("---A SUA VIAGEM BASEADA NAS SUAS PREFERENCIAS---\n\n");
            /*imprime_viagem(procurado->best_local);*/
            printf("1 local a visitar : %s\n",procurado->best_local[0]);
            printf("Neste local visite os seguintes pontos de interesse: \n");
            Lcidade p = procurado->best_local[0];
            Lpdi v = p->lista_pdi;
            imprime_lpdi(v);

            printf("2 local a visitar : %s\n",procurado->best_local[1]);
            printf("Neste local visite os seguintes pontos de interesse: \n");
            p = procurado->best_local[1];
            v = p->lista_pdi;
            imprime_lpdi(v);

            printf("3 local a visitar : %s\n",procurado->best_local[2]);
            printf("Neste local visite os seguintes pontos de interesse: \n");
            p = procurado->best_local[2];
            v = p->lista_pdi;
            imprime_lpdi(v);
            printf("\n-----------------\n");

            int o;
            printf("Deseja avaliar a viagem criada de acordo com a sua taxa de popularidade?\n");
            printf("(1) - Sim. (2) - Nao\n");
            scanf("%d",&o);
            while ((o<1)||(o>2)){
            printf("\nIndique corretamente o que executar\n");
            scanf("%d",&o);
            }
                if (o==1) {
                    avalia_viagem(lu,lc,procurado);
                    printf("---------------\n");
                    voltar_menu(lu,lc);
                } else if (o==2) {
                    printf("\n");
                    voltar_menu(lu,lc);
                }


    } else {
        system("cls");
        printf("O utilizador nao indicou os seus 3 locais preferidos. Impossivel gerar viagem\n");
        voltar_menu(lu,lc);
    }
}

}



