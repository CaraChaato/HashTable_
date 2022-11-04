#ifndef HASH_CPP
#define HASH_CPP

#include "cidade.cpp" // Chamada da função que contém as estuturas salvas
#include <math.h> // Biblioteca para operações matemáticas
#include <stdio.h> // Entrada e Saída de Dados
#include <stdlib.h> // Emulador do prompt do sistema 



/**
 * 3/4 do espaço será utilizado para a tabela Hash
 * Os 1/4 restantes do espaço serão empregados para o tratamento de colisão
 */
#define SIZE 64

/**
 * Criação de um vetor de ponteiros chamado 'hash' do tipo dataItem
 * Essa variável será a própria Tabela Hash
 */
typedef dataItem *hash[SIZE];

// Funções
void init(hash &H);
int inserir(hash H, dataItem *d, int (*funcHash)(dataItem *));
int buscar(hash H, int chave, int (*funcHash)(dataItem *));
int remover(hash H, int chave, int (*funcHash)(dataItem *));
int divisao(dataItem *d);
void printHash(hash dado);
void printItem(hash H, int key);

/**
 * Função que inicia a Tabela Hash
 * Ela percorre todos os espaços vagos limpando-os
 */
void init(hash &H) {
    for (int i = 0; i < SIZE; i++) {
        H[i] = 0;
    }
}

/**
 * Insere elementos na tabela Hash
 * @param H 
 * @param d 
 * @param funcHash 
 * @return int 
 */
int inserir(hash H, dataItem *d, int (*funcHash)(dataItem *)) { 
    // Variável inteira que irá receber o resultado da função Hash
    int key = funcHash(d); 

    // Se a estrutura estiver vazia, a cópia do item será guardada nela
    if (H[key] == 0 || H[key]->key == -1) {
        // Cópia do item que será inserido
        dataItem *copy = (dataItem*)malloc(sizeof(dataItem));
        *copy = *d;      
        H[key] = copy;
        return 0; // Retorna 0 se der certo
    }
    /**
     * Tratamento de Colisão Encadeado Interior
     * Ele basicamente usa uma parte da tabela como um vetor normal para alocar estruturas que tenham colidido
     */
    for(int i = ((SIZE/4) * 3); i < SIZE; i++){
        if(H[i] == 0 || H[i]->key == -1){
            // Cópia do item que será inserido
            dataItem *copy = (dataItem*)malloc(sizeof(dataItem));
            *copy = *d; 
            H[i] = copy;
            return 0; // Retorna 0 se der certo
        }
    }
    return -1; // Retorna -1 se der errado
}

/**
 * Função que busca um elemento em uma posição da Tabela
 * @param H 
 * @param key 
 * @param funcHash 
 * @return dataItem* 
 */
int buscar(hash H, int chave, int (*funcHash)(dataItem *)){

    // Checa se a chave do item está dentro dos critérios de busca
    if (chave <= 0) {
        printf("Chave Inválida para busca/n");
        return(-1);
    }

    // Cria um item com a mesma chave pesquisada
    dataItem *d = (dataItem*)malloc(sizeof(dataItem));
    d->key = chave;
    int key = funcHash(d); 

    // Se a chave buscada estiver na possisão key, retorna a posição key
    if (H[key]->key == d->key) {
        free(d);
        return key;
    }
    // Se a key for -1 ela irá buscar na segunda parte da tabela
    else if (H[key] != 0) {
        for (int i = ((SIZE/4) * 3); i < SIZE; i++){
            // Se chegar a uma posição vazia antes de achar, retorna -1 (erro)
            if (H[i] == 0){
                printf("\nItem não encontrado\n");
                free(d);
                return -1;
            }
            // Se achar a key em alguma das posições, retorna a posição i
            else if (H[i]->key == d->key){
                free(d);
                return i;
            }
        }
    }
    // Em caso de erro
    printf("\nItem não encontrado\n");
    free(d);
    return -1;
}

/**
 * Função que Remove um Elemento da Tabela
 * @param H 
 * @param d 
 * @param funcHash 
 * @return int 
 */
int remover(hash H, int chave, int (*funcHash)(dataItem *)) {
    int key = buscar(H, chave, funcHash); // Busco a posição do item na tabela
    if(key == -1){
        return -1;
    }
    // Apago o item de acordo com a posição
    dataItem *purge = H[key]; // Purge vai receber a chave do item, e limpar o local
    // delete purge; //linux
    
    free(purge); // windows e linux 
    H[key] = (dataItem*) malloc(sizeof(dataItem));
    H[key]->key = -1; // Apagar é uma palavra mt forte, tá mais pra sobrescrever
    return 0; // Retorna 0 se der tudo certo
}

/**
 * Função Hash da Divisão
 * @param d 
 * @return int 
 */
int divisao(dataItem *d) {
    // O corpo principal da tabela será até a posição 255, o restante será para tratamento
    return d->key % ((SIZE/4) * 3);
}

/**
 * Função que imprime a tabela Hash
 * @param dado 
 */
void printHash(hash dado){
    FILE *tabelinhadenoiz;
    tabelinhadenoiz = fopen("Tabela_hash_Ordenada.txt","w");
    printf("\n  ==== CORPO PRINCIPAL DA TABELA HASH ====  \n\n\n");
    for (int i = 0; i < ((SIZE/4) * 3); i++) {
        if(dado[i] == 0){
            printf("    ====   SLOT VAZIO   ====\n\n");
        }
        else if(dado[i]->key == -1){
            printf("    ====  SLOT APAGADO  ====\n\n");
        }
        else{   
            printf(" = %d =\n %s - %s %.2f - %.2f\n\n", dado[i]->key, dado[i]->city.cidade, dado[i]->city.estado, dado[i]->GPS.la, dado[i]->GPS.lo);
            fprintf(tabelinhadenoiz," = %d =\n %s - %s %.2f - %.2f\n\n", dado[i]->key, dado[i]->city.cidade, dado[i]->city.estado, dado[i]->GPS.la, dado[i]->GPS.lo);
        }
    }
    printf("\n\n  ====       TRATAMENTO DE COLISAO       ====\n\n\n");
    for (int i = ((SIZE/4) * 3); i < SIZE; i++) {
        if(dado[i] == 0){
            printf("    ====   SLOT VAZIO   ====\n\n");
        }
        else if(dado[i]->key == -1){
            printf("    ====  SLOT APAGADO  ====\n\n");
        }
        else{   
            printf(" = %d =\n %s - %s %.2f - %.2f\n\n", dado[i]->key, dado[i]->city.cidade, dado[i]->city.estado, dado[i]->GPS.la, dado[i]->GPS.lo);
            fprintf(tabelinhadenoiz," = %d =\n %s - %s %.2f - %.2f\n\n", dado[i]->key, dado[i]->city.cidade, dado[i]->city.estado, dado[i]->GPS.la, dado[i]->GPS.lo);
        }
    }
    fclose(tabelinhadenoiz);
}

void printItem(hash H, int key){
    if(H[key] == 0){
        printf("    ====   SLOT VAZIO   ====\n\n");
    }
    else if(H[key]->key == -1){
        printf("    ====  SLOT APAGADO  ====\n\n");
    }
    else{   
        printf(" = %d =\n %s - %s %.2f - %.2f\n\n", H[key]->key, H[key]->city.cidade, H[key]->city.estado, H[key]->GPS.la, H[key]->GPS.lo);
    }
}

#endif
