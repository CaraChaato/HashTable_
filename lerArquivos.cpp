#include <stdio.h> // Ler e Inserir dados
#include <stdlib.h> // Operações de prompt
#include <string> // Auxiliar com caracteres
#include "cidade.cpp" // Estrutura da cidade
#define MAX 5570

/**
 * @brief Recebe as Estruturas City e Gps, e retorna uma estrutura dataItem
 * @param cities 
 * @param local 
 * @return dataItem* 
 */
dataItem *getItens(cidade *cities, gps *local) {
    // Cria um dataItem do tamanho MAX
    dataItem *dados = (dataItem *)malloc(MAX * sizeof(dataItem));
    int k = 0;

    // Organiza as estruturas que foram recebidas com base no id
    for (size_t i = 0; i < MAX; i++) {
        dados[k].key = cities[i].id;
        for (size_t j = 0; j < MAX; j++) {
            if (cities[i].id == local[j].id) {
                dados[k].city = cities[i];
                dados[k].GPS = local[j];
                k++;
                break;
            }
        }
    }
    return dados;
}

/**
 * @brief Lê o arquivo passado como parametro e retorna uma estrutura City
 * @param arquivo 
 * @return cidade* 
 */
cidade *getCidades(char *arquivo) {
    // Abre o arquivo
    FILE *f = fopen(arquivo, "r");
    cidade *cidades = (cidade *)malloc(MAX * sizeof(cidade));
    // Informa se o arquivo não for aberto
    if (!f) {
        perror("Arquivo Legenda não encontrado!\n");
        return NULL;
    }
    // Limpa a primeira linha de leitura do arquivo
    fscanf(f, "CODIGO MUNICIPIO;UF;NOME MUNICIPIO");
    unsigned int cod;
    char *uf;
    char *cid;
    int i = 0;
    // Percore o arquivo salvando as informações 
    while (!feof(f)) {
        uf = (char *)malloc(2 * sizeof(char));
        cid = (char *)malloc(40 * sizeof(char));
        fscanf(f, "%d %s ", &cod, uf);
        fgets(cid, 40 * sizeof(char), f);

        //printf("%d %s %s", cod, uf, cid);

        cidades[i].id = cod; // ID da cidade
        cidades[i].estado = uf; // Estado
        cidades[i].cidade = cid; // Cidade
        i++;
    }
    return cidades; // Retorna a estrutura
}

/**
 * @brief Lê o arquivo passado como parametro e retorna uma estrutura Gps
 * @param localizacoes 
 * @return gps* 
 */
gps *getGps(char *localizacoes) {
    // Abre o arquivo
    FILE *f = fopen(localizacoes, "r");
    gps *local = (gps *)malloc(MAX * sizeof(gps));
    // Informa se o arquivo não for aberto
    if (!f) {
        perror("Arquivo Coordenadas nao encontrado!\n");
        return NULL;
    }
    // Limpa a primeira linha de leitura do arquivo
    fscanf(f, "CODIGO MUNICIPIO;LATITUDE;LONGITUDE");
    unsigned int cod;
    latitude la;
    longitude lo;
    int i = 0;
    // Percore o arquivo salvando as informações
    while (!feof(f)) {
        fscanf(f, "%u;%f;%f", &cod, &la, &lo);

        //printf("%u;%.2f;%.2f\n", cod, la, lo);

        local[i].id = cod; // Id do local
        local[i].la = la; // Latitude
        local[i].lo = lo; // Longitude
        i++;
    }

    return local;
}

// Imprime uma estrutura dataItem
void printData(dataItem *dado){
    for (int i = 0; i < MAX; i++) {
        printf("%d -> %d %s %s %.2f %.2f\n\n\n", i, dado[i].key, dado[i].city.cidade, dado[i].city.estado, dado[i].GPS.la, dado[i].GPS.lo);
    }
}