#include <stdio.h> // Ler e Inserir dados
#include <stdlib.h> // Operações de prompt
#include <string> // Auxiliar com caracteres
#include "cidade.cpp" // Estrutura da cidade
#define MAX 5570

dataItem *getItens(char *arquivo, char *localizacoes){
    dataItem *dados = (dataItem *)malloc(MAX * sizeof(dataItem));

    FILE *fCity = fopen(arquivo, "r"); // Lê um arquivo
    cidade *cidades = (cidade *)malloc(MAX * sizeof(cidade)); // Ponteiro do tipo cidade
    if (!fCity) { // Indica um erro caso o arquivo não consiga ser aberto
        perror("Arquivo Legenda nao encontrado!\n");
        return NULL;
    }
    FILE *fGps = fopen(localizacoes, "r");
    gps *local = (gps *)malloc(MAX * sizeof(gps));
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
    int idC, idG, i = 0, k = 0 ,j = 0;

    for(i = 0; i < MAX; i++){
        uf = (char *)malloc(2 * sizeof(char)); // Aloca o estado
        cid = (char *)malloc(40 * sizeof(char)); // Aloca a Cidade
        fscanf(fCity, "%d %s ", &idC, uf); // Lê o ID e o estado
        fgets(cid, 40 * sizeof(char), fCity); // Lê o nome da cidade
        fscanf(fGps, "%u;%f;%f", &idG, &la, &lo); // Lê os dados do GPS
        
        /**
         *  Escreve as informações na estrutura
         */
        cidades[i].estado = uf; // Escreve o Estado
        cidades[i].cidade = cid; // Escreve o Nome da cidade
        cidades[i].id = idC; // ID da cidade
        local[i].la = la; // Escreve a Latitude
        local[i].lo = lo; // Escreve a Longitude
        local[i].id = idG; // ID do GPS
        
        //printf("%d -> %d %s %s\n -> %d %.2f %.2f\n\n", i, cidades[i].id, cidades[i].cidade, cidades[i].estado, local[i].id, local[i].la, local[i].lo);
    }
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            if(cidades[i].id == local[j].id){
                dados[k].key = cidades[i].id;
                dados[k].city = cidades[i];
                dados[k].GPS = local[j];
                k++;
            }
        }
        printf("%d -> %d %s %s %.2f %.2f\n\n\n", i, dados[i].key, dados[i].city.cidade, dados[i].city.estado, dados[i].GPS.la, dados[i].GPS.lo);
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