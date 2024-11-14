#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    // Lê os dados do arquivo até o final e armazena no vetor de clientes
    while(fscanf(FileClientes,"%s",(p_clientes+i)->cpf) != EOF) {
        fscanf(FileClientes,"%s",(p_clientes+i)->nome);
        fscanf(FileClientes,"%s",(p_clientes+i)->telefone);
        fscanf(FileClientes,"%s",(p_clientes+i)->endereco.rua);
        fscanf(FileClientes,"%s",(p_clientes+i)->endereco.numero);
        fscanf(FileClientes,"%s",(p_clientes+i)->endereco.cidade);
        fscanf(FileClientes,"%s",(p_clientes+i)->endereco.estado);
        fscanf(FileClientes,"%s",(p_clientes+i)->data.dia);
        fscanf(FileClientes,"%s",(p_clientes+i)->data.mes);
        fscanf(FileClientes,"%s",(p_clientes+i)->data.ano);
        i++;
    }
    fclose(FileClientes);
}

// Função para carregar os dados dos produtos a partir de um arquivo
void Atribuir_ao_Vetor_Produtos(Produtos *p_produtos) {
    int i=0;
    FILE *FileProdutos;
    FileProdutos = fopen("produtos.txt", "r");
    if (FileProdutos == NULL) { // Verifica se o arquivo abriu corretamente
        printf("Erro ao abrir arquivo produtos\n");
        return;
    }
    // Lê os dados do arquivo até o final e armazena no vetor de produtos
    while(fscanf(FileProdutos,"%s",(p_produtos+i)->codigo) != EOF) {
        fscanf(FileProdutos,"%s",(p_produtos+i)->nome);
        fscanf(FileProdutos,"%s",(p_produtos+i)->autor);
        fscanf(FileProdutos,"%f",&(p_produtos+i)->preco);
        fscanf(FileProdutos,"%d",&(p_produtos+i)->quantidade_em_estoque);
        i++;
    }
    fclose(FileProdutos);
}

//Funcao para listar as vendas carregadas
void ListarVendas(Vendas *p_vendas, int *quantidade){
    int escolha;
    do{
        //menu dentro da funcao vendas
        printf("\n=== Menu de Vendas ===\n");
        printf("1. Adicionar venda\n");
        printf("2. Alterar venda\n");
        printf("3. Consultar vendas\n");
        printf("4. Deletar venda\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            system("cls");
            Adicionar_Vendas(quantidade, p_vendas); // chama a funcao para adicionar venda
            break;
        case 2:
            printf("Ainda estamos implementando essa funcao!\n");
            sleep(1);
            system("cls");
            break;
        case 3:
            system("cls");
            printf("===Lista de vendas====\n");
            for(int i = 0; i < *quantidade;i++){
                printf("Cpf: %s\n", (p_vendas+i)->cpf);
                printf("Codigo: %s\n", (p_vendas+i)->codigo);
                printf("Quantidade comprada: %d\n\n", (p_vendas+i)->quantidade_comprada);
            }
            break;
        case 4:
            printf("Ainda estamos implementando essa funcao!\n");
            sleep(1);
            system("cls");
            break;
        case 5:
            printf("Saindo...\n");
            sleep(1);
            system("cls");
            break;
        }
    }while(escolha != 5);

}

// Função para listar clientes carregados 
void ListarClientes(Clientes *p_clientes, int *quantidade){
    int escolha;
    do{
        //menu dentro da funcao Clientes
        printf("\n=== Menu de Clientes ===\n");
        printf("1. Adicionar cliente\n");
        printf("2. Alterar cliente\n");
        printf("3. Consultar clientes\n");
        printf("4. Deletar cliente\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            system("cls");
            Adicionar_Clientes(quantidade, p_clientes); // chama a funcao para adicionar cliente
            break;
        case 2:
            printf("Ainda estamos implementando essa funcao!\n");
            sleep(1);
            system("cls");
            break;
        case 3:
            system("cls");
            printf("===Lista de Clientes====\n");
            //Aqui vai exibir cada cliente do vetor clientes
            for(int i = 0; i < *quantidade;i++){
                printf("Cpf: %s\n", (p_clientes + i)->cpf);
                printf("Nome do Cliente: %s\n", (p_clientes + i)->nome);
                printf("Telefone: %s\n", (p_clientes + i)->telefone);
                printf("Cidade: %s\n\n", (p_clientes + i)->endereco.cidade);
            }
            break;
        case 4:
            printf("Ainda estamos implementando essa funcao!\n");
            sleep(1);
            system("cls");
            break;
        case 5:
            printf("Saindo...\n");
            sleep(1);
            system("cls");
            break;
        }
    }while(escolha != 5);

}

//// Função para listar produtos carregados
void ListarProdutos(Produtos *p_produtos, int *variedade_produtos) {
    int escolha;
    do{
        //menu dentro da funcao Clientes
        printf("\n=== Menu de Produtos ===\n");
        printf("1. Adicionar produto\n");
        printf("2. Alterar produto\n");
        printf("3. Consultar produtos\n");
        printf("4. Deletar produto\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            system("cls");
            Adicionar_Produto(variedade_produtos, p_produtos);
            break;
        case 2:
            printf("Ainda estamos implementando essa funcao!\n");
            sleep(1);
            system("cls");
            break;
        case 3:
            system("cls");
            printf("=== Lista de Produtos ===\n");
            //Exibe cada produto do vetor de produtos
            for (int i = 0; i < *variedade_produtos; i++) {
                printf("Codigo: %s\n", (p_produtos + i)->codigo);
                printf("Nome: %s\n", (p_produtos + i)->nome);
                printf("Preco: %.2f\n", (p_produtos + i)->preco);
                printf("Quantidade em Estoque: %d\n\n", (p_produtos + i)->quantidade_em_estoque);
            }
            break;
        case 4:
            printf("Ainda estamos implementando essa funcao!\n");
            sleep(1);
            system("cls");
            break;
        case 5:
            printf("Saindo...\n");
            sleep(1);
            system("cls");
            break;
        }
    }while(escolha != 5);


}

void Adicionar_Produto(int *variedade_produtos, Produtos *p_produtos){
    FILE *FileProdutos;
    FileProdutos = fopen("produtos.txt", "a");
    if (FileProdutos == NULL) {
        printf("Erro ao abrir arquivo produtos\n");
    }
    char codigo[6];
    char nome[50];
    char autor[20];
    float preco;
    int quantidade_em_estoque;
    int result = 0;
    printf("Digite o codigo do livro:");
    scanf("%s",codigo);
    printf("Digite o nome do livro:");
    scanf("%s",nome);
    printf("Digite o nome do autor:");
    scanf("%s",autor);
    printf("Digite o preço do livro:");
    scanf("%f",&preco);
    printf("Digite a quantidade em estoque do livro:");
    scanf("%d",&quantidade_em_estoque);
    result = fprintf(FileProdutos,"%s ",codigo);
    fprintf(FileProdutos,"%s ",nome);
    fprintf(FileProdutos,"%s ",autor);
    fprintf(FileProdutos,"%.2f ",preco);
    fprintf(FileProdutos,"%d ",quantidade_em_estoque);
    fprintf(FileProdutos, "\n");
    if(result == EOF){
        printf("Erro na Gravacao\n");
    }
    fclose(FileProdutos);
    (*variedade_produtos)++;
    Atribuir_ao_Vetor_Produtos(p_produtos);
}

void Adicionar_Clientes(int *quantidade, int *p_clientes){
    FILE *FileClientes;
    FileClientes = fopen("clientes.txt", "a");
    if (FileClientes == NULL) {
        printf("Erro ao abrir arquivo clientes\n");
    }
    int result;
    char cpf[13];
    char nome[20];
    char telefone[13];
    Endereco endereco;
    Data data;
    printf("Digite o cpf do cliente:");
    scanf("%s",cpf);
    printf("Digite o nome do cliente:");
    scanf("%s",nome);
    printf("Digite o telefone do cliente:");
    scanf("%s",telefone);
    printf("Digite a rua do cliente:");
    scanf("%s",&endereco.rua);
    printf("Digite o numero da casa do cliente:");
    scanf("%s",&endereco.numero);
    printf("Digite a cidade do cliente:");
    scanf("%s",&endereco.cidade);
    printf("Digite o estado do cliente:");
    scanf("%s",&endereco.estado);
    printf("Digite a data de nascimento do cliente:");
    scanf("%s",data.dia);
    printf("Digite o mes de nascimento do cliente:");
    scanf("%s",data.mes);
    printf("Digite o ano de nascimento do cliente:");
    scanf("%s",data.ano);
    result = fprintf(FileClientes,"%s ",cpf);
    fprintf(FileClientes,"%s ",nome);
    fprintf(FileClientes,"%s ",telefone);
    fprintf(FileClientes,"%s ",endereco.rua);
    fprintf(FileClientes,"%s ",endereco.numero);
    fprintf(FileClientes,"%s ",endereco.cidade);
    fprintf(FileClientes,"%s ",endereco.estado);
    fprintf(FileClientes,"%s ",data.dia);
    fprintf(FileClientes,"%s ",data.mes);
    fprintf(FileClientes,"%s ",data.ano);
    fprintf(FileClientes, "\n");
    if(result == EOF){
        printf("Erro na Gravacao\n");
    }
    fclose(FileClientes);
    (*quantidade)++;
    Atribuir_ao_Vetor_Clientes(p_clientes);
}

void Adicionar_Vendas(int *quantidade, int *p_vendas){
    FILE *FileVendas;
    FileVendas = fopen("vendas.txt", "a");
    if (FileVendas == NULL) {
        printf("Erro ao abrir arquivo vendas\n");
    }
    int result;
    char cpf[13];
    char codigo[6];
    int quantidade_comprada;
    printf("Digite o cpf do cliente:");
    scanf("%s",cpf);
    printf("Digite o codigo do produto comprado:");
    scanf("%s",codigo);
    printf("Digite a quantidade comprada:");
    scanf("%d",&quantidade_comprada);
    result = fprintf(FileVendas,"%s ",cpf);
    fprintf(FileVendas,"%s ",codigo);
    fprintf(FileVendas,"%d ",quantidade_comprada);
    fprintf(FileVendas, "\n");
    if(result == EOF){
        printf("Erro na Gravacao\n");
    }
    fclose(FileVendas);
    (*quantidade)++;
    Atribuir_ao_Vetor_Vendas(p_vendas);
}

int main(){
    int qtdclientes,qtdvendas,variedade_produtos; //variaveis para saber a quantidade de cada uma das informacoes nos vetores
    qtdclientes=1;
    qtdvendas=3;
    variedade_produtos=4;

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
        printf("\n=== Menu Principal ===\n");
        printf("1. Listar Vendas\n");
        printf("2. Listar Clientes\n");
        printf("3. Listar Produtos\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            system("cls");
            ListarVendas(vendas, &qtdvendas);
            break;
        case 2:
            system("cls");
            ListarClientes(clientes, &qtdclientes);
            break;
        case 3:
            system("cls");
            ListarProdutos(produtos, &variedade_produtos);
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Nao lembro de ter posto essa opcao nao irmao, larga de ser burro!\n");
            break;
        }
    }while(escolha != 4);

    return 0;
}