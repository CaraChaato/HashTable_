#ifndef HASH_CPP
#define HASH_CPP

#include "cidade.cpp" // Chamada da função que contém as estuturas salvas
#include <math.h> // Biblioteca para operações matemáticas
#include <stdio.h> // Entrada e Saída de Dados
#include <stdlib.h> // Emulador do prompt do sistema 

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
 * @brief 
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
    if (H[key] == 0) {
        H[key] = copy;
        return 0; // Retorna 0 se der certo
    }
    return -1; // Retorna -1 se der errado
}

/**
 * @brief 
 * Função que Remove um Elemento da Tabela
 * @param H 
 * @param d 
 * @param funcHash 
 * @return int 
 */
int remover(hash H, dataItem *d, int (*funcHash)(dataItem *)) {
    // Variável inteira que irá receber o resultado da função Hash
    int key = funcHash(d);
    // Se a estrutura estiver ocupada, o espaço será liberado
    if (H[key] != 0) {
        dataItem *purge = H[key];
        // delete purge; //linux
        free(purge); //windows, linux
        H[key] = 0;
        return 0; // Retorna 0 se der certo
    }
    return -1; // Retorna -1 se der errado
}

/**
 * @brief 
 * Função que busca um elemento em uma posição da Tabela
 * @param H 
 * @param key 
 * @param funcHash 
 * @return dataItem* 
 */
dataItem *buscar(hash H, int key, int (*funcHash)(dataItem *)){
    dataItem *res = (dataItem*)malloc(sizeof(dataItem));
    res->key = key;
    int pos = funcHash(res);
    res = H[pos];
    return res;
}

/**
 * @brief 
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