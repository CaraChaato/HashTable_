#include "Hash.cpp"
#include "lerArquivos.cpp"

int inserirTodos(hash H, dataItem *d, int (*funcHash)(dataItem *)) {
    for (int i = 0; i < SIZE; i++) {
        inserir(H, d+i, funcHash);
    }
    return -1;
}

int removerTodos(hash H, dataItem *d, int (*funcHash)(dataItem *)) {
    for (int i = 0; i < SIZE; i++) {
        remover(H, d[i].key, funcHash);
    }
    return -1;
}

int main() {
    char *arquivo1 = (char *)"bancoDeDados/legenda.txt";
    cidade *cities = getCidades(arquivo1);
    char *arquivo2 = (char *)"bancoDeDados/coordenadas.csv";
    gps *locais = getGps(arquivo2);
    dataItem *d = getItens(cities, locais);

    hash H;
    init(H);

    inserirTodos(H, d, divisao);
    printHash(H);

    //system("pause");
    //system("cls");

    int key = buscar(H, 110003, divisao);
    printf("\n\n  Item Buscado:\n\n");
    printItem(H, key);
    printf("\n\n");

    //system("pause");
    //system("cls");

    remover(H, 110003, divisao);
    printf("\n\n");

    printHash(H);
    
    //system("pause");
    //system("cls");

    //removerTodos(H, d, divisao);
    
    saveData(H);
    printf("\nFim da Execução!\n");

    return 0;
}
