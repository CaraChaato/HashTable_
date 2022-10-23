#ifndef HASH_CPP
#define HASH_CPP

#include "cidade.cpp" // Chamada da função que contém as estuturas salvas
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * 1/4 do espaço será utilizado para a tabela Hash, da posição 0 à 255
 * Os 3/4 restantes do espaço será empregado para o tratamento de colisão, da posição 256 à 1023
 */
#define SIZE 1024


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
 * Função que insere elementos na tabela
 * Ela funciona recebendo a tabela, um item que será alocado, e uma função Hash
 */
int inserir(hash H, dataItem *d, int (*funcHash)(dataItem *)) {
    int key = funcHash(d); // A chave de alocação irá receber a posição calculada pela função Hash
    dataItem *copy = (dataItem*)malloc(sizeof(dataItem)); 
    *copy = *d; // Uma variável auxiliar de nome copy irá salvar uma copia do item a ser salvo
    if (H[key] == 0) { // Se a posição da tabela estiver vazia
        H[key] = copy; // Ela irá receber a informação 
        return 0; // Retornar 0 caso a operação der certo
    }
    return -1; // E retornar -1 em caso de colisão
    // O tratamento de colisão pode ser colocado aqui :D
}

/**
 * Função que remove um item da tabela
 * Recebe a tabela, um item, e a função hash
 */
int remover(hash H, dataItem *d, int (*funcHash)(dataItem *)) {
    int key = funcHash(d); // A chave de alocação irá receber a posição calculada pela função Hash
    if (H[key] != 0) { // Se o espaço estiver sendo usado, ele será limpo
        dataItem *purge = H[key]; // Purge vai receber a chave do item, e limpar o local
        // delete purge; //linux
        free(purge); // windows e linux 
        H[key] = 0;
        return 0; // Retorna 0 se der tudo certo
    }
    return -1; // Se o item n for encontrado, retorna um erro (-1)
    // No caso do tratamento de colisão, o item deve ser buscado também no espaço reservado
}

/**
 * Fução que busca um item na tabela
 * Recebe a tabela, um item, e a função hash
 */
dataItem *buscar(hash H, int key, int (*funcHash)(dataItem *)){
    dataItem *res = (dataItem*)malloc(sizeof(dataItem)); // Variável de nome res do tipo dataItem
    res->key = key; // Recebe a chave de um item a ser buscado
    int pos = funcHash(res); // Variável que recebe a posição do dataItem na hash
    res = H[pos]; // Checa se o item buscado está na posição
    return res; // E retorna a resposta
    // Terá que ser reavaliada no tratamento de colisão
}

int divisao(dataItem *d) { // Função divisão que retorna uma chave com base no resto da divisão da chave
    return d->key % SIZE;
}

typedef unsigned long long int bigNumber; // Varíavel de um número inteiro bem bem grande e sem sinal


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