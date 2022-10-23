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
 * (Incrementar o Tratamento de colisão nela)
 */
int inserir(hash H, dataItem *d, int (*funcHash)(dataItem *)) {
    int key = funcHash(d); // A chave de alocação irá receber a posição calculada pela função Hash
    // Com base no resto da divisão de 1/4 de 1024
    dataItem *copy = (dataItem*)malloc(sizeof(dataItem)); 
    *copy = *d; // Uma variável auxiliar de nome copy irá salvar uma copia do item a ser salvo

    if (H[key] == 0 || H[key]->key == -1) { // Se a posição da tabela estiver disponivel
        H[key] = copy; // Ela irá receber a informação 
        return 0; // Retornar 0 caso a operação der certo
    }
    else{ // Acho q essa seria a estrutura base do tratamento de colisão
        int i;
        for(i = (SIZE/4) ; i < SIZE; i++){
            if(H[i] == 0 || H[i]->key == -1){
                H[i] = copy;
                break;
            }
        }
        return 0; // Retornar 0 caso a operação der certo
    }
    return -1; // E retornar -1 em caso de erro
}

/**
 * Função que remove um item da tabela
 * Recebe a tabela, um item, e a função hash
 */
int remover(hash H, dataItem *d, int (*funcHash)(dataItem *)) {
    int key = funcHash(d); // A chave de alocação irá receber a posição calculada pela função Hash
    
    // Não sei se isso tá certo, já vi tanto código hoje q tô sequelado
    if(H[key]->key == -1){
        for(int i = (SIZE/4); i < SIZE; i++){
            if(H[i] == 0){
                break;
            }
            else{
               if (H[i]->key == H[key]->key){
                    dataItem *purge = H[key]; // Purge vai receber a chave do item, e limpar o local
                    // delete purge; //linux
                    free(purge); // windows e linux 
                    H[key]->key = -1;
               }
            }
        }
    }

    if (H[key] != 0) { // Se o espaço estiver sendo usado, ele será limpo
        dataItem *purge = H[key]; // Purge vai receber a chave do item, e limpar o local
        // delete purge; //linux
        free(purge); // windows e linux 
        H[key]->key = -1;
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

// Função divisão que retorna uma chave com base no resto da divisão da chave
int divisao(dataItem *d) { 
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