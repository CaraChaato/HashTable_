#include "Hash.cpp"
#include "lerArquivos.cpp"

int main() {
    char *arquivo1 = (char *)"bancoDeDados/legenda.txt";
    cidade *todasCidades = getCidades(arquivo1);
    char *arquivo2 = (char *)"bancoDeDados/coordenadas.csv";
    gps *locais = getGps(arquivo2);
    dataItem *d = getItens(todasCidades, locais);
    hash H;
    int info;

    // Teste de inserção de elemento
    for(int i = 0; i < 1024; i++){
        info = inserir(H, d, divisao);
        if(info == -1){
            printf("ERRO!\n");
        }
    }
    return 0;
}