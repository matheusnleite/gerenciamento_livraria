#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
    while (fscanf(FileVendas, "%12s %5s %d", p_vendas[i].cpf, p_vendas[i].codigo, &p_vendas[i].quantidade_comprada) != EOF) {
        i++; //Os numeros sao para definir o espaco que a string ira ocupar
    }
    fclose(FileVendas);
}
// Função para carregar os dados dos clientes a partir de um arquivo
void Atribuir_ao_Vetor_Clientes(Clientes *p_clientes) {
    int i = 0;
    FILE *FileClientes;
    FileClientes = fopen("clientes.txt", "r");
    if (FileClientes == NULL) {
        printf("Erro ao abrir arquivo clientes\n");
        return;
    }
    
    char linha[200];
    while (fgets(linha, sizeof(linha), FileClientes) != NULL) {//fgets para ler uma linha do arquivo 'FileClientes' e armazená-la na variável 'linha' até o fim da linha ou tamanho máximo definido

        sscanf(linha, "%12s %19s %12s %39s %5s %29s %29s %2s %2s %4s", //sscanf para extrair valores formatados de uma string e armazená-los em variáveis específicas
            p_clientes[i].cpf,
            p_clientes[i].nome,
            p_clientes[i].telefone,
            p_clientes[i].endereco.rua,
            p_clientes[i].endereco.numero,
            p_clientes[i].endereco.cidade,
            p_clientes[i].endereco.estado,
            p_clientes[i].data.dia,
            p_clientes[i].data.mes,
            p_clientes[i].data.ano);
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
    while (fscanf(FileProdutos, "%5s %49s %19s %f %d", p_produtos[i].codigo, p_produtos[i].nome, p_produtos[i].autor, &p_produtos[i].preco, &p_produtos[i].quantidade_em_estoque) != EOF) {
        i++;
    }
    fclose(FileProdutos);
}

//Funcao para identificar quantas informacões tem em cada arquivo
int Contar_Registros(char *arquivo){
    FILE *file = fopen(arquivo,"r");
    if(file == NULL){
        printf("Erro ao abrir arquivo %s!\n", arquivo);
        return 0;
    }
    int contador=0; //contador que vai salvar a quantidade de informações encontradas
    char linha[200]; //variavel que vai salvar todas as informacoes de uma linha do arquivo
    while(fgets(linha, sizeof(linha), file)!= NULL){ //fgets le uma linha, se chegar no final do arquivo ele retorna null
        contador++;
    }
    fclose(file);
    return contador;
}

//Funcao para alterar vendas
void AlterarVendas(Vendas *p_vendas, int quantidade) {
    char cpfBusca[13];
    int campo;
    char novoValor[50];

    printf("\nDigite o CPF da venda que deseja alterar: ");
    scanf("%s", cpfBusca);

    // Encontrar a venda à ser alterada com o CPF informado
    int indice = -1;
    for (int i = 0; i < quantidade; i++) {
        if (strcmp((p_vendas+i)->cpf, cpfBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("\nVenda nao encontrada!\n");
        return;
    }
    printf("\n=== ALTERACOES ===\n");
    printf("1. CPF\n");
    printf("2. Codigo do produto\n");
    printf("3. Quantidade comprada\n");
    printf("Escolha o campo a ser alterado:");
    scanf("%d", &campo);

    switch (campo) {
        case 1:
            printf("\nDigite o novo CPF: ");
            scanf("%s", novoValor);
            strcpy((p_vendas+indice)->cpf, novoValor);
            break;
        case 2:
            printf("\nDigite o novo codigo do produto: ");
            scanf("%s", novoValor);
            strcpy((p_vendas+indice)->codigo, novoValor);
            break;
        case 3:
            printf("\nDigite a nova quantidade comprada: ");
            scanf("%d", &(p_vendas+indice)->quantidade_comprada);
            break;
        default:
            printf("\nOpção invalida!\n");
            return;
    }
    
    //salvando a alteracao no arquivo
    FILE *File = fopen("vendas.txt", "w"); // Abre o arquivo no modo escrita, sobrescrevendo o conteúdo existente

    if (File == NULL) {
        perror("Erro ao abrir arquivo vendas para escrita\n"); // usando perror para mensagens de erro automáticas.
        return;
     }

    for (int i = 0; i < quantidade; i++) {
        fprintf(File, "%s %s %d", (p_vendas+i)->cpf, (p_vendas+i)->codigo, (p_vendas+i)->quantidade_comprada);
        if(i != (quantidade-1))
            fprintf(File,"\n");
    }

    fclose(File);
    printf("Venda alterada com sucesso!\n");
    sleep(2);
    system("cls");
    return;    
}

//Funcao para alterar clientes
void AlterarClientes(Clientes *p_clientes, int quantidade) {
    char cpfBusca[13];
    int campo;
    char novoValor[50];

    printf("\nDigite o CPF do cliente que deseja alterar: ");
    scanf("%12s", cpfBusca);

    // Encontrar o cliente à ser alterado com o CPF informado
    int indice = -1;
    for (int i = 0; i < quantidade; i++) {
        if (strcmp((p_clientes+i)->cpf, cpfBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("\nCliente não encontrado!\n");
        return;
    }

    printf("\n=== ALTERACOES ===\n");
    printf("1. Nome\n");
    printf("2. Telefone\n");
    printf("3. Endereco\n");
    printf("4. Data\n");
    printf("Escolha o campo a ser alterado:");
    scanf("%d", &campo);

    switch (campo) {
        case 1:
            printf("\nDigite o novo nome: ");
            scanf("%s", novoValor);
            strcpy((p_clientes+indice)->nome, novoValor);
            break;
        case 2:
            printf("\nDigite o novo telefone: ");
            scanf("%s", novoValor);
            strcpy((p_clientes+indice)->telefone, novoValor);
            break;
        case 3:
            // Alterar endereço:
            printf("\nDigite a nova rua: ");
            scanf("%s", (p_clientes+indice)->endereco.rua);
            printf("\nDigite o novo numero: ");
            scanf("%s", (p_clientes+indice)->endereco.numero);
            printf("\nDigite a nova cidade: ");
            scanf("%s", (p_clientes+indice)->endereco.cidade);
            printf("\nDigite o novo estado: ");
            scanf("%s", (p_clientes+indice)->endereco.estado);
            break;
        case 4:
        // Alterar data:
        printf("\nDigite o novo dia: ");
            scanf("%s", &(p_clientes+indice)->data.dia);
            printf("\nDigite o novo mes: ");
            scanf("%s", (p_clientes+indice)->data.mes);
            printf("\nDigite o novo ano: ");
            scanf("%s", (p_clientes+indice)->data.ano);
            break;
        default:
            printf("\nOpção inválida!\n");
            return;
    }

    // Salvando as alterações no arquivo clientes.txt
    FILE *File = fopen("clientes.txt", "w"); // Abre o arquivo no modo escrita, sobrescrevendo o conteúdo existente

    if (File == NULL) {
        perror("Erro ao abrir arquivo clientes para escrita\n"); //perror() function is designed to print a descriptive error message to the standard error
        return;
    }

    // Escrevendo os dados atualizados no arquivo 
    for (int i = 0; i < quantidade; i++) {
        fprintf(File, "%s %s %s %s %s %s %s %s %s", (p_clientes+i)->cpf, (p_clientes+i)->nome, (p_clientes+i)->telefone, (p_clientes+i)->endereco.rua, (p_clientes+i)->endereco.numero, (p_clientes+i)->endereco.cidade, (p_clientes+i)->endereco.estado, (p_clientes+i)->data.dia, (p_clientes+i)->data.ano);
        if(i != (quantidade-1))
            fprintf(File,"\n");
    }

    fclose(File);
    printf("Cliente alterado com sucesso!\n");
    sleep(2);
    system("cls");
    return;
}

//Funcao para alterar produtos
// Função para alterar produtos
void AlterarProdutos(Produtos *p_produtos, int quantidade) {
    char codigoBusca[6];
    int campo;
    char novoValor[50];

    printf("\nDigite o codigo do produto que deseja alterar: ");
    scanf("%s", codigoBusca);

    // Encontrar o produto a ser alterado com o código informado
    int indice = -1;
    for (int i = 0; i < quantidade; i++) {
        if (strcmp((p_produtos+i)->codigo, codigoBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("\nProduto não encontrado!\n");
        return;
    }

    printf("\n=== ALTERACOES ===\n");
    printf("1. Codigo\n");
    printf("2. Nome\n");
    printf("3. Autor\n");
    printf("4. Preco\n");
    printf("5. Quantidade em Estoque\n");
    printf("Escolha o campo a ser alterado: ");
    scanf("%d", &campo);

    switch (campo) {
        case 1:
            printf("\nDigite o novo código: ");
            scanf("%s", novoValor);
            strcpy((p_produtos+indice)->codigo, novoValor);
            break;
        case 2:
            printf("\nDigite o novo nome: ");
            scanf("%s", novoValor);
            strcpy((p_produtos+indice)->nome, novoValor);
            break;
        case 3:
            printf("\nDigite o novo autor: ");
            scanf("%s", novoValor);
            strcpy((p_produtos+indice)->autor, novoValor);
            break;
        case 4:
            printf("\nDigite o novo preço: ");
            scanf("%f", &(p_produtos+indice)->preco);
            break;
        case 5:
            printf("\nDigite a nova quantidade em estoque: ");
            scanf("%d", &(p_produtos+indice)->quantidade_em_estoque);
            break;
        default:
            printf("\nOpção inválida!\n");
            return;
    }

    // Salvando a alteração no arquivo produtos.txt
    FILE *FileProdutos;
    FileProdutos = fopen("produtos.txt", "w");

    if (FileProdutos == NULL) {
        printf("Erro ao abrir arquivo produtos para escrita\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(FileProdutos, "%s %s %s %.2f %d",
                (p_produtos+i)->codigo,
                (p_produtos+i)->nome,
                (p_produtos+i)->autor,
                (p_produtos+i)->preco,
                (p_produtos+i)->quantidade_em_estoque);
        if (i != (quantidade-1))
            fprintf(FileProdutos, "\n");
    }

    fclose(FileProdutos);
    printf("Produto alterado com sucesso!\n");
    sleep(2);
    system("cls");
}

//Funcao para listar as vendas carregadas
void ListarVendas(Vendas *p_vendas, int *quantidade, Clientes *p_clientes, Produtos *p_produtos){
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
            Adicionar_Vendas(quantidade, p_vendas, p_clientes, p_produtos); // chama a funcao para adicionar vendas
            break;
        case 2:
            AlterarVendas(p_vendas, *quantidade);
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
void ListarClientes(Clientes *p_clientes, int *quantidade, Vendas *p_vendas){
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
            AlterarClientes(p_clientes, *quantidade);
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
            system("cls");
            RemoverClientes("clientes.txt",p_clientes,p_vendas);
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
void ListarProdutos(Produtos *p_produtos, int *variedade_produtos, Vendas *p_vendas) {
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
            AlterarProdutos(p_produtos, *variedade_produtos);
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
            system("cls");
            Remover("produtos.txt",p_produtos,p_vendas);
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
    printf("Digite o preco do livro:");
    scanf("%f",&preco);
    printf("Digite a quantidade em estoque do livro:");
    scanf("%d",&quantidade_em_estoque);
    result = fprintf(FileProdutos, "\n");
    fprintf(FileProdutos,"%s ",codigo);
    fprintf(FileProdutos,"%s ",nome);
    fprintf(FileProdutos,"%s ",autor);
    fprintf(FileProdutos,"%.2f ",preco);
    fprintf(FileProdutos,"%d ",quantidade_em_estoque);
    if(result == EOF){
        printf("Erro na Gravacao\n");
    }
    fclose(FileProdutos);
    (*variedade_produtos)++;
    Atribuir_ao_Vetor_Produtos(p_produtos);
}

void Adicionar_Clientes(int *quantidade, Clientes *p_clientes){
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
    result = fprintf(FileClientes, "\n");
    fprintf(FileClientes,"%s ",cpf);
    fprintf(FileClientes,"%s ",nome);
    fprintf(FileClientes,"%s ",telefone);
    fprintf(FileClientes,"%s ",endereco.rua);
    fprintf(FileClientes,"%s ",endereco.numero);
    fprintf(FileClientes,"%s ",endereco.cidade);
    fprintf(FileClientes,"%s ",endereco.estado);
    fprintf(FileClientes,"%s ",data.dia);
    fprintf(FileClientes,"%s ",data.mes);
    fprintf(FileClientes,"%s ",data.ano);    
    if(result == EOF){
        printf("Erro na Gravacao\n");
    }
    fclose(FileClientes);
    (*quantidade)++;
    Atribuir_ao_Vetor_Clientes(p_clientes);
}

void Adicionar_Vendas(int *quantidade, Vendas *p_vendas, Clientes *p_clientes, Produtos *p_produtos){
    FILE *FileVendas;
    FileVendas = fopen("vendas.txt", "a");
    if (FileVendas == NULL) {
        printf("Erro ao abrir arquivo vendas\n");
    }
    int result,i,aux=0;
    char cpf[13];
    char codigo[6];
    int quantidade_comprada;
    printf("Digite o cpf do cliente:");
    scanf("%s",cpf);
    for(i=0; i<100; i++){   //verifica o cpf digitado se esta no vetor de clientes
            if (cpf == p_clientes[i].cpf)
        {
            aux = 1;
        }
    }
    if(aux==0){
        printf("\nCPF nao cadastrado");
        return;
    }
    printf("Digite o codigo do produto comprado:");
    scanf("%s",codigo);

    int indice = -1;
    for (int i = 0; i < quantidade; i++) { //verifica se o codigo digitado esta no vetor de produtos
        if (strcmp((p_produtos+i)->codigo, codigo) == 0) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        printf("\nProduto não encontrado!\n");
        return;
    }

    printf("Digite a quantidade comprada:");
    scanf("%d",&quantidade_comprada);

    if(quantidade_comprada > (p_produtos + indice)->quantidade_em_estoque){ //verifica se a quanidade comprada é maior que a quantidade em estoque
        printf("\nQuantidade maior que o estoque");
        return;
    }
    (p_produtos  + indice)->quantidade_em_estoque = (p_produtos  + indice)->quantidade_em_estoque - quantidade_comprada;
    result = fprintf(FileVendas, "\n");
    fprintf(FileVendas,"%s ",cpf);
    fprintf(FileVendas,"%s ",codigo);
    fprintf(FileVendas,"%d ",quantidade_comprada);
    if(result == EOF){
        printf("Erro na Gravacao\n");
    }
    fclose(FileVendas);
    (*quantidade)++;
    Atribuir_ao_Vetor_Vendas(p_vendas);
}

void RemoverClientes(char *arquivo, Clientes *p_clientes, Vendas *p_vendas) {
    int aux=0,num_linha,i;
    char cpf[13];
    printf("Digite o cpf do cliente:");
    scanf("%s",cpf);
    for(i=0; i<100; i++){   //verifica o cpf digitado se esta no vetor de clientes
            if (strcmp(cpf, p_clientes[i].cpf) == 0)
        {
            aux = 1;
            num_linha = i;
        }
    }
    if(aux==0){
        printf("\nCPF nao cadastrado");
        return;
    }
    FILE *arquivo_original = fopen(arquivo, "r");
    if (arquivo_original == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    FILE *arquivo_temp = fopen("temp.txt", "w");
    if (arquivo_temp == NULL) {
        perror("Erro ao criar arquivo temporário");
        fclose(arquivo_original);
        return;
    }

    char linha[1024];
    int contador = 1;

    // Lê cada linha do arquivo original
    while (fgets(linha, sizeof(linha), arquivo_original) != NULL) {
        // Escreve no arquivo temporário apenas as linhas que não correspondem à linha a ser apagada
        if (contador != num_linha) {
            fputs(linha, arquivo_temp);
        }
        contador++;
    }

    fclose(arquivo_original);
    fclose(arquivo_temp);

    // Substitui o arquivo original pelo temporário
    remove(arquivo);
    rename("temp.txt", arquivo);

    printf("Cliente removido com sucesso.\n");
}

void RemoverProdutos(char *arquivo, Produtos *p_produtos, Vendas *p_vendas) {
    int aux=0,num_linha,i;
    char codigo[6];
    printf("Digite o codigo do produto:");
    scanf("%s",codigo);
    for(i=0; i<100; i++){   //verifica se o codigo digitado esta no vetor de clientes
            if (strcmp(codigo, p_produtos[i].codigo) == 0)
        {
            aux = 1;
            num_linha = i;
        }
    }
    if(aux==0){
        printf("\nCodigo nao cadastrado");
        return;
    }
    FILE *arquivo_original = fopen(arquivo, "r");
    if (arquivo_original == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    FILE *arquivo_temp = fopen("temp.txt", "w");
    if (arquivo_temp == NULL) {
        perror("Erro ao criar arquivo temporário");
        fclose(arquivo_original);
        return;
    }

    char linha[1024];
    int contador = 1;

    // Lê cada linha do arquivo original
    while (fgets(linha, sizeof(linha), arquivo_original) != NULL) {
        // Escreve no arquivo temporário apenas as linhas que não correspondem à linha a ser apagada
        if (contador != num_linha) {
            fputs(linha, arquivo_temp);
        }
        contador++;
    }

    fclose(arquivo_original);
    fclose(arquivo_temp);

    // Substitui o arquivo original pelo temporário
    remove(arquivo);
    rename("temp.txt", arquivo);

    printf("Produto removido com sucesso.\n");
}

void RemoverVendas(char *arquivo, Vendas *p_vendas) {
    int aux=0,num_linha,i;
    char cpf[13];
    char codigo[6];
    printf("Digite o cpf do cliente:");
    scanf("%s",cpf);
    printf("Digite o codigo:");
    scanf("%s",codigo);
    for(i=0; i<100; i++){   //verifica o cpf digitado se esta no vetor de clientes
            if (strcmp(cpf, p_vendas[i].cpf) == 0 && strcmp(codigo, p_vendas[i].codigo) == 0)
        {
            aux = 1;
            num_linha = i;
        }
    }
    if(aux==0){
        printf("\nCPF ou/e Codigo nao associados a venda");
        return;
    }
    FILE *arquivo_original = fopen(arquivo, "r");
    if (arquivo_original == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    FILE *arquivo_temp = fopen("temp.txt", "w");
    if (arquivo_temp == NULL) {
        perror("Erro ao criar arquivo temporário");
        fclose(arquivo_original);
        return;
    }

    char linha[1024];
    int contador = 1;

    // Lê cada linha do arquivo original
    while (fgets(linha, sizeof(linha), arquivo_original) != NULL) {
        // Escreve no arquivo temporário apenas as linhas que não correspondem à linha a ser apagada
        if (contador != num_linha) {
            fputs(linha, arquivo_temp);
        }
        contador++;
    }

    fclose(arquivo_original);
    fclose(arquivo_temp);

    // Substitui o arquivo original pelo temporário
    remove(arquivo);
    rename("temp.txt", arquivo);

    printf("Venda removida com sucesso.\n");
}

int main(){
    int qtdclientes,qtdvendas,variedade_produtos; //variaveis para saber a quantidade de cada uma das informacoes nos vetores
    qtdclientes= Contar_Registros("clientes.txt");
    qtdvendas= Contar_Registros("vendas.txt");
    variedade_produtos= Contar_Registros("produtos.txt");

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
            ListarVendas(vendas, &qtdvendas, &clientes, &produtos);
            break;
        case 2:
            system("cls");
            ListarClientes(clientes, &qtdclientes, vendas);
            break;
        case 3:
            system("cls");
            ListarProdutos(produtos, &variedade_produtos, vendas);
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            sleep(2);
            system("cls");
            break;
        }
    }while(escolha != 4);

    printf("%s", clientes[1].cpf);

    return 0;
}