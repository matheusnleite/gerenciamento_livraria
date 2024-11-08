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

Vendas* Atribuir_ao_Vetor() {
    int i=0;
    FILE *FileVendas;
    Vendas vendas[100];
    Vendas *p_vendas = &vendas;
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
    }
    fclose(FileVendas);
    return p_vendas;
}

int main(){
    int i=0;
    Vendas *p_vendas;
    FILE *FileClientes;
    FILE *FileProdutos;

    FileClientes = fopen("clientes.txt", "r");
    if (FileClientes == NULL) {
        return 1;
    }
    FileProdutos = fopen("produtos.txt", "r");
    if (FileProdutos == NULL) {
        return 1;
    }
    p_vendas = Atribuir_ao_Vetor();
    printf("%s\n", (p_vendas+i)->cpf);
    printf("%s\n", (p_vendas+i)->codigo);
    printf("%d\n", (p_vendas+i)->quantidade_comprada);

    fclose(FileClientes);
    fclose(FileProdutos);

    return 0;
}