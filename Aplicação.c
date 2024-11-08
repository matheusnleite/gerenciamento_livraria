#include <stdio.h>

typedef struct{
    char codigo[6];
    char nome[50];
    char autor[20];
    int quantidade_em_estoque;
    float preço;
}Produtos;

typedef struct{
    char cpf[13];
    char codigo[6];
    int quantidade_comprada;
}Vendas;

typedef struct{
    char rua[40];
    char numero[6];
    char cidade[30];
    char estado[30];
}Endereco;

typedef struct {
    char dia[3];
    char mes[3];
    char ano[5];
}Data;

typedef struct{
    char cpf[13];
    char nome[20];
    char telefone[13];
    Endereco endereco;
    Data data;
}Clientes;


int main(){
    int i=0;
    Vendas vendas[100];
    FILE *FileClientes;
    FILE *FileProdutos;
    FILE *FileVendas;
    FileClientes = fopen("clientes.txt", "r");
    if (FileClientes == NULL) {
        return 1;
    }
    FileProdutos = fopen("produtos.txt", "r");
    if (FileProdutos == NULL) {
        return 1;
    }
    FileVendas = fopen("vendas.txt", "r");
    if (FileVendas == NULL) {
        printf("Erro ao abrir arquivo vendas\n");
    }
    while(fscanf(FileVendas,"%s",vendas[i].cpf) != EOF) {
        fscanf(FileVendas,"%s",vendas[i].codigo);
        fscanf(FileVendas,"%d",&vendas[i].quantidade_comprada);

        printf("%s\n",vendas[i].cpf);
        printf("%s\n",vendas[i].codigo);
        printf("%d\n",vendas[i].quantidade_comprada);
        i++;
    }

    fclose(FileClientes);
    fclose(FileProdutos);
    fclose(FileVendas);
    return 0;
}