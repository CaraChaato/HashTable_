#ifndef HASH_CPP
#define HASH_CPP

#include "cidade.cpp" // Chamada da função que contém as estuturas salvas
#include <math.h> // Biblioteca para operações matemáticas
#include <stdio.h> // Entrada e Saída de Dados
#include <stdlib.h> // Emulador do prompt do sistema 
/**
 * 1/4 do espaço será utilizado para a tabela Hash
 * -> 0 ~ 255
 * Os 3/4 restantes do espaço serão empregados para o tratamento de colisão
 * -> 256 ~ 1023
 */
#define SIZE 16

/**
 * Criação de um vetor de ponteiros chamado 'hash' do tipo dataItem
 * Essa variável será a própria Tabela Hash
 */
typedef dataItem *hash[SIZE];

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
 * Função que Insere um Elemento na Tabela 
 * @param H 
 * @param d 
 * @param funcHash 
 * @return int 
 */
int inserir(hash H, dataItem *d, int (*funcHash)(dataItem *)) { 
    // Variável inteira que irá receber o resultado da função Hash
    int key = funcHash(d); 
    // Cópia do item que será inserido
    dataItem *copy = (dataItem*)malloc(sizeof(dataItem));
    *copy = *d;

    // Se a estrutura estiver vazia, a cópia do item será guardada nela
    if (H[key] == 0 || H[key]->key == -1) {
        H[key] = copy;
        return 0; // Retorna 0 se der certo
    }
    /**
     * Tratamento de Colisão Encadeado Interior
     * Ele basicamente usa uma parte da tabela como um vetor normal para alocar estruturas que tenham colidido
     */
    else{
        for(int i = (SIZE/4); i < SIZE; i++){
            if(H[i] == 0 || H[i]->key == -1){
                H[i] = copy;
                break;
            }
        }
        return 0; // Retorna 0 se der certo
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
        for (int i = (SIZE/4); i < SIZE; i++){
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
    //H[key] = 0; // Queria fzr isso mas por algum motivo dá errado
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
    return d->key % (SIZE/4);
}


// Varíavel de um número inteiro bem bem grande e sem sinal
typedef unsigned long long int bigNumber; 

/**
 * Função Hash de Multiplicação
 * Não vou nem tentar comentar isso
 * O importante é que ela também retorna uma posição na tabela com base na chave
 */
int multiplicacao(dataItem *d) {
    bigNumber key = (bigNumber)d->key;
    key *= key;
    int digits = ceil(log2((bigNumber)540000 * 540000));
    int signif = ceil(log2(SIZE - 1));
    int remover = digits - signif;
    int digitMask = (int)ceil(float(remover) / 2);
    bigNumber mask = ((SIZE-1) << digitMask);
    key = key & mask;
    key = (key >> digitMask);
    return key;
    // Vontade de chorar lendo isso (*>﹏<*)
}
#endif

/**
 * Função que imprime a tabela Hash
 * @param dado 
 */
void printHash(hash dado){
    printf("\n  ==== CORPO PRINCIPAL DA TABELA HASH ====  \n\n\n");
    for (int i = 0; i < (SIZE/4); i++) {
        if(dado[i] == 0){
            printf("       ====   SLOT VAZIO   ====\n\n");
        }
        
        if(dado[i]->key == -1){
            printf("       ====  SLOT APAGADO  ====\n\n");
        }
        
        else{   
            printf(" = %d =\n %s - %s %.2f - %.2f\n\n", dado[i]->key, dado[i]->city.cidade, dado[i]->city.estado, dado[i]->GPS.la, dado[i]->GPS.lo);
        }
    }
    printf("\n\n  ====       TRATAMENTO DE COLISAO       ====\n\n\n");
    for (int i = (SIZE/4); i < SIZE; i++) {
        if(dado[i] == 0){
            printf("       ====   SLOT VAZIO   ====\n\n");
        }
        
        if(dado[i]->key == -1){
            printf("       ====  SLOT APAGADO  ====\n\n");
        }
        
        else{   
            printf(" = %d =\n %s - %s %.2f - %.2f\n\n", dado[i]->key, dado[i]->city.cidade, dado[i]->city.estado, dado[i]->GPS.la, dado[i]->GPS.lo);
        }
    }
}

void printItem(hash H, int key){
    if(H[key] == 0){
        printf("       ====   SLOT VAZIO   ====\n\n");
    }
    if(H[key]->key == -1){
        printf("       ====  SLOT APAGADO  ====\n\n");
    }
    else{   
        printf(" = %d =\n %s - %s %.2f - %.2f\n\n", H[key]->key, H[key]->city.cidade, H[key]->city.estado, H[key]->GPS.la, H[key]->GPS.lo);
    }
}