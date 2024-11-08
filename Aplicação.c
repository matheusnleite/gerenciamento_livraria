#include <stdio.h>

typedef struct{
    char codigo[6];
    char nome[50];
    char autor[20];
    int quantidade_em_estoque;
    float preco;
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

void Atribuir_ao_Vetor_Clientes(Vendas *p_vendas) {
    int i=0;
    FILE *FileVendas;
    FileVendas = fopen("vendas.txt", "r");
    if (FileVendas == NULL) {
        printf("Erro ao abrir arquivo vendas\n");
    }
    while(fscanf(FileVendas,"%s",(p_vendas+i)->cpf) != EOF) {
        fscanf(FileVendas,"%s",(p_vendas+i)->codigo);
        fscanf(FileVendas,"%d",&(p_vendas+i)->quantidade_comprada);

        printf("%s\n",(p_vendas+i)->cpf);
        printf("%s\n",(p_vendas+i)->codigo);
        printf("%d\n",(p_vendas+i)->quantidade_comprada);
        i++;
    }
    fclose(FileVendas);
}

int main(){
    int i=0;
    Vendas vendas[100];
    Vendas *p_vendas;
    p_vendas = &vendas;
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
    Atribuir_ao_Vetor_Clientes(p_vendas);
    for(i=0;i<2;i++) {
        printf("%s\n", (p_vendas+i)->cpf);
        printf("%s\n", (p_vendas+i)->codigo);
        printf("%d\n", (p_vendas+i)->quantidade_comprada);
    }
    fclose(FileClientes);
    fclose(FileProdutos);

    return 0;
}