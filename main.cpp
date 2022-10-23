#include "Hash.cpp"
#include "lerArquivos.cpp"

int main() {
    char *arquivo1 = (char *)"bancoDeDados/legenda.txt";
    char *arquivo2 = (char *)"bancoDeDados/coordenadas.csv";
    dataItem *d = getItens(arquivo1, arquivo2);
    hash H;


    return 0;
}