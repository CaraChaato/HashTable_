#include "Hash.cpp"
#include "lerArquivos.cpp"

int main() {
    char *arquivo1 = (char *)"bancoDeDados/legenda.txt";
    cidade *cities = getCidades(arquivo1);
    char *arquivo2 = (char *)"bancoDeDados/coordenadas.csv";
    gps *locais = getGps(arquivo2);
    dataItem *d = getItens(cities, locais);

    hash H;
    init(H);
    
    for (int i = 0; i < SIZE; i++) {
        inserir(H, d+i, divisao);
    }  
    //printHash(H);
    
    // Alguns testes 
    int key = buscar(H, 110007, divisao);
    printItem(H,key);
    printf("\n%d\n\n", key);
    key = buscar(H, 110001, divisao);
    printItem(H,key);
    printf("\n%d\n\n", key);
    key = buscar(H, 110008, divisao);
    printItem(H,key);
    printf("\n%d\n\n", key);
    key = buscar(H, 110015, divisao);
    printItem(H,key);
    printf("\n%d\n\n", key);

    remover(H, 110007, divisao);
    remover(H, 110001, divisao);
    remover(H, 110008, divisao);
    remover(H, 110015, divisao);
    printHash(H);

    return 0;
}