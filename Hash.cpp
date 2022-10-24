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
    return d->key % SIZE/4;
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

void printHash(hash dado){
    printf(" == CORPO PRINCIPAL DA TABELA HASH == \n\n");
    for (int i = 0; i < (SIZE/4); i++) {
        if(dado[i] == 0){
            printf("\n     === Linha Vazia ===\n\n");
        }else{   
            printf(" = %d =\n %s - %s %.2f - %.2f\n\n", dado[i]->key, dado[i]->city.cidade, dado[i]->city.estado, dado[i]->GPS.la, dado[i]->GPS.lo);
        }
    }
    printf("\n == TRATAMENTO DE COLISAO == \n\n");
    for (int i = (SIZE/4); i < SIZE; i++) {
        if(dado[i] == 0){
            printf("\n     === Linha Vazia ===\n\n");
        }else{   
            printf(" = %d =\n %s - %s %.2f - %.2f\n\n", dado[i]->key, dado[i]->city.cidade, dado[i]->city.estado, dado[i]->GPS.la, dado[i]->GPS.lo);
        }
    }
}