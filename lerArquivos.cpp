#include <stdio.h> // Ler e Inserir dados
#include <stdlib.h> // Operações de prompt
#include <string> // Auxiliar com caracteres
#include "cidade.cpp" // Estrutura da cidade

dataItem *getItens(char *arquivo, char *localizacoes){
    dataItem *dados = (dataItem *)malloc(SIZE * sizeof(dataItem));

    FILE *fCity = fopen(arquivo, "r"); // Lê um arquivo
    cidade *cidades = (cidade *)malloc(SIZE * sizeof(cidade)); // Ponteiro do tipo cidade
    if (!fCity) { // Indica um erro caso o arquivo não consiga ser aberto
        perror("Arquivo Legenda nao encontrado!\n");
        return NULL;
    }
    FILE *fGps = fopen(localizacoes, "r");
    gps *local = (gps *)malloc(SIZE * sizeof(gps));
    if (!fGps) { // Apresenta um erro caso não consiga abrir o arquivo
        perror("Arquivo Coordenadas nao encontrado!\n");
        return NULL;
    }
    fscanf(fCity, "CODIGO MUNICIPIO;UF;NOME MUNICIPIO"); // Limpa a leitura da primeira linha do arquivo Cidade
    fscanf(fGps, "CODIGO MUNICIPIO;LATITUDE;LONGITUDE"); // Limpa a leitura da primeira linha do arquivo GPS

    // Variáveis Auxiliares
    latitude la; // Latitude
    longitude lo; // Longitude
    char *uf; // Ponteiro auxiliar para o Estado
    char *cid; // Ponteiro auxiliar para a Cidade
    int aux, i = 0;

    for(i = 0; i < SIZE; i++){
        uf = (char *)malloc(2 * sizeof(char)); // Aloca o estado
        cid = (char *)malloc(40 * sizeof(char)); // Aloca a Cidade
        fscanf(fCity, "%d %s ", &aux, uf); // Lê o ID e o estado
        fgets(cid, 40 * sizeof(char), fCity); // Lê o nome da cidade
        fscanf(fGps, "%u;%f;%f", &aux, &la, &lo); // Lê os dados do GPS
        
        //printf("%u;%.2f;%.2f\n", aux, la, lo);
        //printf("%d %s %s", aux, uf, cid); 

        /**
         *  Escreve as informações na estrutura
         */
        cidades[i].estado = uf; // Escreve o Estado
        cidades[i].cidade = cid; // Escreve o Nome da cidade
        local[i].la = la; // Escreve a Latitude
        local[i].lo = lo; // Escreve a Longitude
        dados[i].key = aux; // Escreve a Chave
    }
}

/**
 * @brief 
 * // Função que imprime todos os dados de uma cidade
 * @param dados 
 */
void printDataItens(dataItem *dados, int i) {
    printf("%d %d %s %.2f %.2f %s", dados[i].key, dados[i].city.estado, dados[i].GPS.la, dados[i].GPS.lo, dados[i].city.cidade);
}