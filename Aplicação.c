#include <stdio.h>

typedef struct{
    char codigo[6];
    char nome[50];
    char autor[20];
    float preco;
    int quantidade_em_estoque;
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

//Funcao para carregar os dados de vendas a partir de um arquivo
void Atribuir_ao_Vetor_Vendas(Vendas *p_vendas) {
    int i=0;
    FILE *FileVendas;
    FileVendas = fopen("vendas.txt", "r");
    if (FileVendas == NULL) {
        printf("Erro ao abrir arquivo vendas\n");
        return;
    }
    while(fscanf(FileVendas,"%s",(p_vendas+i)->cpf) != EOF) {
        fscanf(FileVendas,"%s",(p_vendas+i)->codigo);
        fscanf(FileVendas,"%d",&(p_vendas+i)->quantidade_comprada);

        //printf("%s\n",(p_vendas+i)->cpf);
        //printf("%s\n",(p_vendas+i)->codigo);
        //printf("%d\n",(p_vendas+i)->quantidade_comprada);
        i++;
    }
    fclose(FileVendas);
}
// Função para carregar os dados dos clientes a partir de um arquivo
void Atribuir_ao_Vetor_Clientes(Clientes *p_clientes) {
    int i=0;
    FILE *FileClientes;
    FileClientes = fopen("clientes.txt", "r");
    if (FileClientes == NULL) {
        printf("Erro ao abrir arquivo clientes\n");
        return;
    }
    while(fscanf(FileClientes,"%s",(p_clientes+i)->cpf) != EOF) {
        fscanf(FileClientes,"%s",(p_clientes+i)->nome);
        fscanf(FileClientes,"%s",(p_clientes+i)->telefone);
        fscanf(FileClientes,"%s",(p_clientes)->endereco.rua);
        fscanf(FileClientes,"%s",(p_clientes)->endereco.numero);
        fscanf(FileClientes,"%s",(p_clientes)->endereco.cidade);
        fscanf(FileClientes,"%s",(p_clientes)->endereco.estado);
        fscanf(FileClientes,"%s",(p_clientes)->data.dia);
        fscanf(FileClientes,"%s",(p_clientes)->data.mes);
        fscanf(FileClientes,"%s",(p_clientes)->data.ano);


        //printf("%s\n",(p_clientes+i)->cpf);
        //printf("%s\n",(p_clientes+i)->nome);
        //printf("%s\n",(p_clientes+i)->telefone);
        //printf("%s\n",(p_clientes+i)->endereco.rua);
        //printf("%s\n",(p_clientes+i)->endereco.numero);
        //printf("%s\n",(p_clientes+i)->endereco.cidade);
        //printf("%s\n",(p_clientes+i)->endereco.estado);
        i++;
    }
    fclose(FileClientes);
}

// Função para carregar os dados dos produtos a partir de um arquivo
void Atribuir_ao_Vetor_Produtos(Produtos *p_produtos) {
    int i=0;
    FILE *FileProdutos;
    FileProdutos = fopen("produtos.txt", "r");
    if (FileProdutos == NULL) {
        printf("Erro ao abrir arquivo produtos\n");
        return;
    }
    while(fscanf(FileProdutos,"%s",(p_produtos+i)->codigo) != EOF) {
        fscanf(FileProdutos,"%s",(p_produtos+i)->nome);
        fscanf(FileProdutos,"%s",(p_produtos+i)->autor);
        fscanf(FileProdutos,"%f",&(p_produtos+i)->preco);
        fscanf(FileProdutos,"%d",&(p_produtos+i)->quantidade_em_estoque);

        //printf("%s\n",(p_produtos+i)->codigo);
        //printf("%s\n",(p_produtos+i)->nome);
        //printf("%s\n",(p_produtos+i)->autor);
        //printf("%f\n",(p_produtos+i)->preco);
        //printf("%d\n",(p_produtos+i)->quantidade_em_estoque);
        i++;
    }
    fclose(FileProdutos);
}

//Funcao para listar as vendas carregadas
void ListarVendas(Vendas *p_vendas, int quantidade){
    printf("===Lista de vendas====\n");
    for(int i = 0; i <quantidade;i++){
        printf("Cpf: %s\n", (p_vendas+i)->cpf);
        printf("Codigo: %s\n", (p_vendas+i)->codigo);
        printf("Quantidade comprada: %d\n\n", (p_vendas+i)->quantidade_comprada);
    }
}

// Função para listar clientes carregados 
void ListarClientes(Clientes *p_clientes, int quantidade){
    printf("===Lista de Clientes====\n");
    for(int i = 0; i < quantidade;i++){
        printf("Cpf: %s\n", (p_clientes + i)->cpf);
        printf("Nome do Cliente: %s\n", (p_clientes + i)->nome);
        printf("Telefone: %s\n", (p_clientes + i)->telefone);
        printf("Cidade: %s\n\n", (p_clientes + i)->endereco.cidade);
    }
}

//// Função para liosstar produtos carregad
void ListarProdutos(Produtos *p_produtos, int quantidade) {
    printf("=== Lista de Produtos ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Codigo: %s\n", (p_produtos + i)->codigo);
        printf("Nome: %s\n", (p_produtos + i)->nome);
        printf("Preco: %.2f\n", (p_produtos + i)->preco);
        printf("Quantidade em Estoque: %d\n\n", (p_produtos + i)->quantidade_em_estoque);
    }
}

int main(){
    int i=0;
    int escolha;
    Vendas vendas[100];
    Clientes clientes[100];
    Produtos produtos[100];

    //carregar dados a partir dos arquivos com as funcoes
    Atribuir_ao_Vetor_Vendas(vendas);
    Atribuir_ao_Vetor_Clientes(clientes);
    Atribuir_ao_Vetor_Produtos(produtos);

    //!!!!!!!!!!!!FIZ funcoes para ficar diminuir a quantidade codigo da main
    do{
        //Fiz um pequeno menu principal, ADICIONAR AS POSTERIORES FUNCOES PARA ADICIONAR COISAS
        printf("=== Menu Principal ===\n");
        printf("1. Listar Vendas\n");
        printf("2. Listar Clientes\n");
        printf("3. Listar Produtos\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            ListarVendas(vendas, 100);
            break;
        case 2:
            ListarClientes(clientes, 100);
            break;
        case 3:
            ListarProdutos(produtos, 100);
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Nao lembro de ter posto essa opcao nao irmao, larga de ser burro!\n");
            break;
        }
    }while(escolha != 4);
    // Atribuir_ao_Vetor_Vendas(p_vendas);
    // for(i=0;i<1;i++) {
    //     printf("Cpf:%s\n", (p_vendas+i)->cpf);
    //     printf("Codigo:%s\n", (p_vendas+i)->codigo);
    //     printf("Quantidade Comprada:%d\n\n", (p_vendas+i)->quantidade_comprada);
    // }
    // Atribuir_ao_Vetor_Clientes(p_clientes);
    // for(i=0;i<1;i++) {
    //     printf("Cpf:%s\n", (p_clientes+i)->cpf);
    //     printf("Nome do Cliente:%s\n", (p_clientes+i)->nome);
    //     printf("Telefone do CLiente:%s\n", (p_clientes+i)->telefone);
    //     printf("Rua:%s\n", (p_clientes+i)->endereco.rua);
    //     printf("Numero:%s\n", (p_clientes+i)->endereco.numero);
    //     printf("Cidade:%s\n", (p_clientes+i)->endereco.cidade);
    //     printf("Estado:%s\n", (p_clientes+i)->endereco.estado);
    //     printf("Dia:%s\n", (p_clientes+i)->data.dia);
    //     printf("Mes:%s\n", (p_clientes+i)->data.mes);
    //     printf("Ano:%s\n\n", (p_clientes+i)->data.ano);
    // }
    // Atribuir_ao_Vetor_Produtos(p_produtos);
    // for(i=0;i<1;i++) {
    //     printf("Codigo:%s\n",(p_produtos+i)->codigo);
    //     printf("Nome do Livro:%s\n",(p_produtos+i)->nome);
    //     printf("Autor do Livro:%s\n",(p_produtos+i)->autor);
    //     printf("R$:%.2f\n",(p_produtos+i)->preco);
    //     printf("Quantidade em Estoque:%d\n\n",(p_produtos+i)->quantidade_em_estoque);
    // }

    return 0;
}