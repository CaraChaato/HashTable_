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
    
    // N tô sem conseguindo inserir
    inserir(H, d, divisao);
    inserir(H, d, divisao);
    inserir(H, d, divisao);
    inserir(H, d, divisao);

    printHash(H);

    return 0;
}