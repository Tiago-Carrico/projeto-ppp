#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#define CHUNK 1024

void readTextFile(Lcidade l)
{
    char buf[CHUNK];
    FILE *f = fopen("FicheiroTexto-Teste-PPP.txt","r");
    size_t nread;
    char *ptr;
    int k,t,contador=0;
    if (f) {
        while( fgets (buf, CHUNK, f)!=NULL ) {
                ptr = strtok(buf, ";");
                if (strcmp(ptr, "LOCAL")==0) {
                        while (ptr != NULL)
                        {
                           ptr = strtok(NULL, ";");
                            if (strcmp(ptr,"LOCAL")!=0) {
                                struct cidade local;
                                Lcidade aux = NULL;
                                /*DEFINIMOS O NOME DO LOCAL*/
                                strcpy(local.nome, ptr);
                                local.nome[strlen(local.nome)-1]='\0';
                                local.popularidade=0;
                                aux = insere_listac(l,local);
                                char buf[CHUNK]={0};
                                /*VAMOS LER INFO DE 3 PONTOS DE INTERESSE POR CADA LOCAL*/
                                /*PARA CADA PONTO DE INTERESSE SAO LIDOS 4 CAMPOS*/
                                for (t=0;t<3;t++) {
                                    struct pdi ponto;
                                     if(fgets(buf,CHUNK,f)!=NULL) {
                                            ptr = strtok(buf, ";");
                                            while (ptr!=NULL) {
                                                contador++;
                                                if (contador==1) {
                                                    strcpy(ponto.nome, ptr);
                                                }
                                                if (contador==2) {
                                                    /*Define a hora de abertura do ponto*/
                                                    int open = atoi(ptr);
                                                    ponto.abertura = open;
                                                }
                                                if (contador==3) {
                                                    /*Define a hora de fecho do ponto*/
                                                    int fecho = atoi(ptr);
                                                    ponto.fecho = fecho;
                                                }
                                                if (contador==4) {
                                                    /*Define descricao do ponto*/
                                                    strcpy(ponto.descricao,ptr);
                                                    ponto.descricao[strlen(ponto.descricao)-1]='\0';
                                                    ponto.popularidade=0;
                                                    insere_listapdi(aux->lista_pdi,ponto);
                                                }
                                                ptr = strtok(NULL, ";");
                                            }
                                            contador=0;
                                    }
                                }

                            }
                        }
                }
            }
        if (ferror(f)) {
                printf("Erro a ler ficheiro de texto");
        }
    fclose(f);
      /*imprime_lcidades (l);*/
    }
}

int main()
{
    Lcidade l = lista_cidades();
    readTextFile(l);
    Luser lu = lista_users();
    menu(lu,l);
}
