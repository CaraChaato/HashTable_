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
 * Função que Remove um Elemento da Tabela
 * @param H 
 * @param d 
 * @param funcHash 
 * @return int 
 */
int remover(hash H, dataItem *d, int (*funcHash)(dataItem *)) {
    // Variável inteira que irá receber o resultado da função Hash
    int key = funcHash(d);

    // Se a estrutura estiver vazia, ele retorna -1
    if (H[key] == 0) {
        return -1;
    }
    /**
     * Se a chave da estrutura for igual a -1, quer dizer
     * que ela foi excluida e que o dado a ser apagado 
     * pode estar na parte do tratamento de colisão.
     */
    else if (H[key]->key == -1) {
        for (int i = (SIZE/4); i < SIZE; i++) { // Percorre a área do tratamento
            if (H[i] == 0) { // Se a estrutura na posisão i da tabela estiver vazia, retorna -1
                return -1;
            }
            else if (H[i]->key == d->key){ // Se não ele checa se a chave bate com a que deve ser apagada
                // Apaga os dados da posição
                dataItem *purge = H[i];
                free(purge);
                H[i] = 0;

                // Para posições que foram limpas, será adicionada a chave de item -1
                // Perguntar se essa parte tá bem feita 
                dataItem *aux = (dataItem*) malloc(sizeof(dataItem));
                aux->key = -1;
                H[key] = aux;
                return 0;
            }
        }
    }
    /**
     * Se a chave não for -1, 
     * eu checo se a posição está preenchida e se a chave do item é diferente de -1
     */
    else if (H[key] != 0 && H[key]->key != -1){
        // No caso da posisão da lista da tabela comum estiver ocupada, eu limpo
        dataItem *purge = H[key];
        // delete purge; //linux
        free(purge); //windows, linux
        H[key] = 0;

        // Sem esquecer de adicionar a chave -1 que avisa se a posisão já foi apagada alguma vez
        // Perguntar se essa parte tá bem feita 
        dataItem *aux = (dataItem*) malloc(sizeof(dataItem));
        aux->key = -1;
        H[key] = aux;
        return 0;
    }
    return -1; // Retorna -1 no caso de um erro (tem q ser um erro bem estranho pra n se encaixar em nenhuma das condições)
}

/**
 * Função que busca um elemento em uma posição da Tabela
 * @param H 
 * @param key 
 * @param funcHash 
 * @return dataItem* 
 */
dataItem *buscar(hash H, int key, int (*funcHash)(dataItem *)){ // Ainda falta ajeitar
    dataItem *res = (dataItem*)malloc(sizeof(dataItem));
    res->key = key;
    int pos = funcHash(res);
    res = H[pos];
    return res;
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
    printf("\n == CORPO PRINCIPAL DA TABELA HASH == \n\n\n");
    for (int i = 0; i < (SIZE/4); i++) {
        if(dado[i] == 0){
            printf("     === SLOT VAZIO ===\n\n");
        }
        
        if(dado[i]->key == -1){
            printf("     === SLOT APAGADO ===\n\n");
        }
        
        else{   
            printf(" = %d =\n %s - %s %.2f - %.2f\n\n", dado[i]->key, dado[i]->city.cidade, dado[i]->city.estado, dado[i]->GPS.la, dado[i]->GPS.lo);
        }
    }
    printf("\n\n == TRATAMENTO DE COLISAO == \n\n\n");
    for (int i = (SIZE/4); i < SIZE; i++) {
        if(dado[i] == 0){
            printf("     === SLOT VAZIO ===\n\n");
        }
        
        if(dado[i]->key == -1){
            printf("     === SLOT APAGADO ===\n\n");
        }
        
        else{   
            printf(" = %d =\n %s - %s %.2f - %.2f\n\n", dado[i]->key, dado[i]->city.cidade, dado[i]->city.estado, dado[i]->GPS.la, dado[i]->GPS.lo);
        }
    }
}