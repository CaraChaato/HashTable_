#include <stdio.h> // Ler e Inserir dados
#include <stdlib.h> // Operações de prompt
#include <string> // Auxiliar com caracteres
#include "cidade.cpp" // Estrutura da cidade
#define MAX 5580 // Número máximo de cidades que podem ser lidas

dataItem *getItens(cidade *, gps *); // Ponteiro do tipo dataItem que recebe os dados de uma cidade
void printDataItens(dataItem *); // Escreve os dados de uma arvore
void saveDataItens(dataItem *); // sei n

cidade *getCidades(char *arquivo); // Ponteiro do tipo cidade que recebe um arquivo
gps *getGps(char *);
char* remover(char* text);

/**
 * @brief 
 * Função que lê um arquivos e salva suas informações na estrutura e 
 * Lê Nome, Estado e Id da cidade em um arquivo e passa para uma estrutura
 * @param arquivo 
 * @return cidade* 
 */
cidade *getCidades(char *arquivo) {
    FILE *f = fopen(arquivo, "r"); // Lê um arquivo
    cidade *cidades = (cidade *)malloc(MAX * sizeof(cidade)); // Ponteiro do tipo cidade
    if (!f) { // Indica um erro caso o arquivo não consiga ser aberto
        perror("Arquivo não existe");
        return NULL;
    }
    fscanf(f, "CODIGO MUNICIPIO;UF;NOME MUNICIPIO"); // Limpa a leitura da primeira linha do arquivo
    int cod; // Variável auxiliar para o ID
    char *uf; // Ponteiro auxiliar para o Estado
    char *cid; // Ponteiro auxiliar para a Cidade
    int i = 0;

    while (!feof(f)) {
        uf = (char *)malloc(2 * sizeof(char)); // Aloca o estado
        cid = (char *)malloc(40 * sizeof(char)); // Aloca a Cidade
        fscanf(f, "%d %s ", &cod, uf); // Lê o ID e o estado
        fgets(cid, 40 * sizeof(char), f); // Lê o nome da cidade
        //printf("%d %s %s", cod, uf, cid); // Escreve os 3 antes de salvar
        
        /**
         *  Escreve as informações na estrutura
         */
        cidades[i].id = cod; // Escreve o ID
        cidades[i].estado = uf; // Escreve o Estado
        cidades[i].cidade = cid; // Escreve o Nome da cidade
        i++;
    }
    return cidades; // Retorna as cidades Salvas
}

/**
 * @brief 
 * Função que salva a localização das cidade
 * Lê um arquivo e passa as informações para uma estrutura
 * @param localizacoes 
 * @return gps* 
 */
gps *getGps(char *localizacoes) {
    FILE *f = fopen(localizacoes, "r");
    gps *local = (gps *)malloc(MAX * sizeof(gps));
    if (!f) { // Apresenta um erro caso não consiga abrir o arquivo
        perror("Arquivo não existe");
        return NULL;
    }
    fscanf(f, "CODIGO MUNICIPIO;LATITUDE;LONGITUDE"); // Limpa a leitura da primeira linha
    int cod; // Id
    latitude la; // Latitude
    longitude lo; // Longitude
    int i = 0;
    while (!feof(f)) { // Lê todo o arquivo e salva as informações em uma estrutura
        fscanf(f, "%u;%f;%f", &cod, &la, &lo);
        //printf("%u;%.2f;%.2f\n", cod, la, lo);
        local[i].id = cod;
        local[i].la = la;
        local[i].lo = lo;
        i++;
    }
    return local;
}

/**
 * @brief 
 * // Função que imprime todos os dados de uma cidade
 * @param dados 
 */
void printDataItens(dataItem *dados) {
    for (int i = 0; i < MAX; i++) {
        printf("%d %d %s %.2f %.2f %s", i, dados[i].key, dados[i].city.estado, dados[i].GPS.la, dados[i].GPS.lo, dados[i].city.cidade);
    }
}


/**
 * @brief 
 * Função que salva todos as cidades lidas em um arquivo
 * @param dados 
 */
/*
void saveDataItens(dataItem *dados){
    FILE *f = fopen("dados.dat", "w");
    for (int i = 0; i < MAX; i++) {
        fprintf(f, "%d %d %s %.2f %.2f %s", i, dados[i].key, dados[i].city.estado, dados[i].GPS.la, dados[i].GPS.lo, dados[i].city.cidade);
    }
}
*/

/**
 * @brief
 * Função que salva os itens obtidos nos arquivos em uma só estrutura
 * @param cities 
 * @param local 
 * @return dataItem* 
 */
dataItem *getItens(cidade *cities, gps *local) {
    dataItem *dados = (dataItem *)malloc(MAX * sizeof(dataItem));
    int k = 0;
    for (size_t i = 0; i < MAX; i++) {
        dados[k].key = cities[i].id;
        for (size_t j = 0; j < MAX; j++) {
            if (cities[i].id == local[j].id) {
                dados[k].city = cities[i];
                dados[k].GPS = local[j];
                k++;
            }
        }
    }
    return dados;
}

