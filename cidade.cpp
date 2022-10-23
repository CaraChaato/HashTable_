#ifndef CIDADE_CPP
#define CIDADE_CPP // CIDADE_CPP é chamado multiplas vezes, para que esse só seja declarado uma vez usamos o #define
typedef float latitude;
typedef float longitude;

// A estrutura cidade contém um estado, uma cidade, e seu id do banco de dados
struct cidade {
    int id; // ID
    char *estado; // UF do estado
    char *cidade; // Nome da cidade
};

// A estrutura gps contém a latitude, longitude e id de uma cidade
struct gps {
    int id; // ID
    latitude la; // Latitude da cidade 
    longitude lo; // Longitude da cidade
};

// A estrutura dataItem possui uma chave que pode indereçar uma cidade nos dados, juntamente com os dados da cidade
struct dataItem {
    int key; // Chave primária de uma cidade
    cidade city; // Contém os dados da cidade 
    gps GPS; // Contém o local da cidade
};
#endif