#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define CHUNK 1024

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
        /*printf("Antes de procurar na lista de user");*/
        procura_user(lista,u.nome,&ant,&inutil);
        /*printf("Depois de procurar na lista de user\n");*/
        no->prox=ant->prox;
        ant->prox=no;
    }
    /*return no;*/
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
        printf("%s\n",l->nome,l->popularidade);
        /*printf("Seus pontos de interesse:\n");*/
        imprime_lpdi(l->lista_pdi);
       /* printf("\n");*/
        l=l->prox;
    }
}

void imprime_lcidades_popularidade (Lcidade lista) {
    Lcidade l=lista->prox;
    while(l){
        printf("%s [POPULARIDADE : %d]\n",l->nome,l->popularidade);
        /*printf("Seus pontos de interesse:\n");*/
        imprime_lpdi_popularidade(l->lista_pdi);
       /* printf("\n");*/
        l=l->prox;
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



void imprime_lpdi(Lpdi lista){
    Lpdi l=lista->prox;
    while(l){
        printf("    --> %s. Horario de abertura %d, horario de fecho %d. Descricao: %s\n",l->nome,l->abertura,l->fecho,l->descricao);
        l=l->prox;
    }
}
