#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <time.h>


using namespace std;

struct book{
    
    long codigo = 0; // 0 representa livro nao cadastrado
    char titulo[31];
    char autor[31];
    int ano;
    
    struct data{
        int dia = 0; // verificar se foi emprestado
        int mes;
        int ano;
        
        int dia_dev; // 7 dias depois
        int mes_dev;
        int ano_dev;
    } data;
};

struct user{

    long long CPF = 0; // 0 representa usuario nao cadastrado
    char nome_do_usuario[31];
    book emprestado;
};


// menus
void menuPrincipal(user* usuarios_cadastrados, int &qtd_usuarios, book* livros_cadastrados, int &qtd_livros);
void menuCadastroUsuario(user* usuarios_cadastrados, int &qtd_usuarios);
void menuCadastroLivro(book* livros_cadastrados, int &qtd_livros);
void menuEmprestimo(user* usuarios_cadastrados, int &qtd_usuarios);

//funcoes do menu usuarios
void cadastrar_usuario(user* usuarios_cadastrados);
void excluir_usuario(user* usuarios_cadastrados, int &qtd_usuarios);
void listar_usuarios(user* usuarios_cadastrados, int qtd_usuarios);
void bubble_sortUSUARIO(user* v, int n);

// funcoes do menu livros
void cadastrar_livro(book* livros_cadastrados);
void excluir_livro(book* livros_cadastrados, int &qtd_livros);
void listar_livros(book* livros_cadastrados, int qtd_livros);
void bubble_sortLIVRO(book* v, int n);

// funcoes do menu Emprestimo
void emprestar_livro(user* usuarios_cadastrados, book* livros_cadastrados);
void devolver_livro(user* usuarios_cadastrados, book* livros_cadastrados);
// listar_emprestimos
// bubble_sortUSUARIO


void data_hora_atual(int &dia, int &mes, int &ano) {
        time_t t = time(NULL);
        struct tm lt = *localtime(&t);
        ano = lt.tm_year + 1900;
        mes = lt.tm_mon + 1;
        dia = lt.tm_mday;
        }
        
bool bissexto(int ano)
{
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}
        
void data_devolucao(book &data_dev) // 7 dias depois
{
    int dia, mes, ano;
    data_hora_atual(dia, mes, ano);
    
    int dias_mes[] = {31, bissexto(ano) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    
    for (int i = 1; i <= 7; i++)
    {
        dia++;
        
        if(dia > dias_mes[mes-1])
        {
            dia = 1, mes++;
            
            if(mes > 12)
                mes = 1, ano++;
        }
    }
    
    data_dev.data.dia = dia;
    data_dev.data.mes = mes;
    data_dev.data.ano = ano;
}


void menuEmprestimo(user* usuarios_cadastrados, book* livros_cadastrados){

    int option;

    printf("\nMenu do Empréstimo/Devolução\n");
    printf("1-Emprestar livro\n");
    printf("2-Devolver livro\n");
    printf("3-Listar empréstimos\n");
    printf("4-Voltar\n");

    scanf("%d", &option);

    switch(option){

        case 1:   emprestar_livro(usuarios_cadastrados, livros_cadastrados);
                  break;

        case 2:   devolver_livro(usuarios_cadastrados, livros_cadastrados);
                  break;

        case 3: 
                  break;

        case 4: 
        
                  break;

        default: menuEmprestimo(usuarios_cadastrados, livros_cadastrados);
                 break;
    }
}

void menuCadastroLivro(book* livros_cadastrados, int &qtd_livros){

    int option;

    printf("\nMenu do Cadastro de Livros\n");
    printf("1-Cadastrar livro\n");
    printf("2-Excluir livro\n");
    printf("3-Listar livros\n");
    printf("4-Voltar\n");

    scanf("%d", &option);

    switch(option){

        case 1:   if(qtd_livros != 100){
                  cadastrar_livro(livros_cadastrados);
                  qtd_livros++;
                  }
                  else puts("\nERRO: Limite de livros atingido!\n");
                  
                  break;

        case 2:   if(qtd_livros != 0){
                  excluir_livro(livros_cadastrados, qtd_livros);
                  }
                  else puts("\nERRO: Nao há livros cadastrados!\n");
                  
                  break;

        case 3:   listar_livros(livros_cadastrados, qtd_livros);
                  
                  break;

        case 4: 
                  break;

        default: menuCadastroLivro(livros_cadastrados, qtd_livros);
                 break;
    }
}

void menuCadastroUsuario(user* usuarios_cadastrados, int &qtd_usuarios){

    int option;
    
   
    printf("\nMenu do Cadastro de Usuários\n");
    printf("1-Cadastrar usuário\n");
    printf("2-Excluir usuário\n");
    printf("3-Listar usuários\n");
    printf("4-Voltar\n");

    scanf("%d", &option);

    switch(option){

        case 1:   if(qtd_usuarios != 100){
                  cadastrar_usuario(usuarios_cadastrados);
                  qtd_usuarios++;
                  }
                  else puts("\nERRO: Limite de usuarios atingido!\n");
                  
                  break;

        case 2:   if(qtd_usuarios != 0){
                  excluir_usuario(usuarios_cadastrados, qtd_usuarios);
                  }
                  else puts("\nERRO: Nao há usuarios cadastrados!\n");
                  
                  break;

        case 3: listar_usuarios(usuarios_cadastrados, qtd_usuarios);
                
                  break;

        case 4: 
                  break;

        default: menuCadastroUsuario(usuarios_cadastrados, qtd_usuarios);
                 break;
    }
}

void menuPrincipal(user* usuarios_cadastrados, int &qtd_usuarios, book* livros_cadastrados, int &qtd_livros){

    int option;
    
   
    printf("\nMenu Principal\n");
    printf("1-Cadastro de usuários\n");
    printf("2-Cadastro de livros\n");
    printf("3-Emprestimo/devolucao\n");
    printf("4-Fim\n");

    scanf("%d", &option);

    switch(option){

        case 1: menuCadastroUsuario(usuarios_cadastrados, qtd_usuarios);
                  break;

        case 2: menuCadastroLivro(livros_cadastrados, qtd_livros);
                  break;

        case 3: menuEmprestimo(usuarios_cadastrados, livros_cadastrados);
                  break;

        case 4: exit(1);
                  break;

        default: menuPrincipal(usuarios_cadastrados, qtd_usuarios, livros_cadastrados, qtd_livros);
                 break;
    }
}

long long ler_CPF(long long cpf, user* usuarios_cadastrados)
{
     
    
    bool CPF_ja_cadastrado;
    do{
    printf("CPF: "); scanf("%lld", &cpf);
    
    
    if(!(cpf >= 10000000000 && cpf <= 99999999999)){
        puts("\nERRO: CPF invalido\n");
        continue;
    }
    
    CPF_ja_cadastrado = false;
    for(int i = 0; i < 100; i++)
        if(cpf == usuarios_cadastrados[i].CPF)
            CPF_ja_cadastrado = true;

    if(CPF_ja_cadastrado)
        puts("\nERRO: CPF ja cadastrado");

    else return cpf;
        
        }while(true);
}

// igual ler_CPF() so que tem um '!' em algum lugar ai
long long ler_CPF_EXCLUIR(long long cpf, user* usuarios_cadastrados)
{
     
    
    bool CPF_ja_cadastrado;
    do{
    printf("CPF: "); scanf("%lld", &cpf);
    
    
    if(!(cpf >= 10000000000 && cpf <= 99999999999)){
        puts("\nERRO: CPF invalido\n");
        continue;
    }
    
    CPF_ja_cadastrado = false;
    for(int i = 0; i < 100; i++)
        if(cpf == usuarios_cadastrados[i].CPF)
            CPF_ja_cadastrado = true;

    if(!CPF_ja_cadastrado)
        puts("\nErro: usuário não cadastrado!");

    else return cpf;
        
        }while(true);
}

void ler_palavra(char* nome, char* label)
{
    char buffer[100];
    do{
    
    printf("%s", label), gets(buffer);
    
    if(strlen(buffer) >= 4 && strlen(buffer) <= 30) break;
    
    else if(strlen(buffer) < 4) puts("ERRO: nome tem menos de 4 caracteres!\n");
        
    else puts("ERRO: digite um nome menor!\n");    
    
    }while(true); // if(strlen(buffer) >= 4 && strlen(buffer) <= 30) break;
    
    // uppercase
    
    for(int i = 0; i < strlen(buffer); i++)
    {
        buffer[i] = (char) toupper(buffer[i]);
    }
    
    strcpy(nome, buffer);
}

////////// FUNCOES menuCadastroUsuario
void cadastrar_usuario(user* usuarios_cadastrados)
{
    long long CPF;
    CPF = ler_CPF(CPF, usuarios_cadastrados);
    char nome[31];
    
    char label[10] = "Nome: ";
    getchar(); ler_palavra(nome, label);
    
    for(int i = 0; i < 100; i++)
    {
        if(usuarios_cadastrados[i].CPF == 0)
        {
            usuarios_cadastrados[i].CPF = CPF;
            strcpy(usuarios_cadastrados[i].nome_do_usuario, nome);
            break;
        }
    }
    printf("\n\nCadastro realizado com sucesso!");
    
}

void excluir_usuario(user* usuarios_cadastrados, int &qtd_usuarios) 
{
    long long cpf_excluir = ler_CPF_EXCLUIR(cpf_excluir, usuarios_cadastrados);
    
    for(int i = 0; i < 100; i++)
    {
        if(usuarios_cadastrados[i].CPF == cpf_excluir && usuarios_cadastrados[i].emprestado.codigo != 0)
        {
            printf("\n\nErro: usuário possui um empréstimo!");
            break;
        }
        
        if(usuarios_cadastrados[i].CPF == cpf_excluir)
        {
            usuarios_cadastrados[i].CPF = 0;
            printf("\n\nExclusão realizada com sucesso!");
            qtd_usuarios--;
            break;
        }
            
    }        
    
}


void bubble_sortUSUARIO(user* v, int n) 
{
    bool trocou = true;
    int k = n-1;
    
    while (k > 0 && trocou)
    {
        trocou = false;
        for (int i = 0; i < k; i++)
            if (v[i].CPF > v[i+1].CPF) 
            {
                user aux = v[i+1];
                v[i+1] = v[i];
                v[i] = aux;
                trocou = true;
            }
            k--;
    }
}


void listar_usuarios(user* usuarios_cadastrados, int qtd_usuarios)
{
    bubble_sortUSUARIO(usuarios_cadastrados, qtd_usuarios);
    
    puts("--------------------------------------------------");
    puts("CPF         Nome");
    puts("--------------------------------------------------");
    
    for(int i = 0; i < 100; i++)
        if(usuarios_cadastrados[i].CPF != 0)
        {
            printf("%-11lld %-30s\n", usuarios_cadastrados[i].CPF, usuarios_cadastrados[i].nome_do_usuario);
            if(usuarios_cadastrados[i].emprestado.codigo != 0)
            {
                book data_dev;
                data_devolucao(data_dev);
                printf("            emprestimo: %02d/%02d/%02d a %02d/%02d/%02d\n", 
                                                usuarios_cadastrados[i].emprestado.data.dia,
                                                usuarios_cadastrados[i].emprestado.data.mes,
                                                usuarios_cadastrados[i].emprestado.data.ano,
                                                data_dev.data.dia, data_dev.data.mes,
                                                data_dev.data.ano);
                printf("            Titulo: %-30s\n", usuarios_cadastrados[i].emprestado.titulo);
                printf("            Autor: %-30s\n", usuarios_cadastrados[i].emprestado.autor);
            }
        }
        puts("--------------------------------------------------");
}

////////// FUNCOES menuCadastroLivro

long ler_codigo(long codigo, book* livros_cadastrados)
{
     
    
    bool codigo_ja_cadastrado;
    do{
    printf("codigo: "); scanf("%ld", &codigo);
    
    
    if(!(codigo >= 100000 && codigo <= 999999)){
        puts("\nERRO: codigo invalido\n");
        continue;
    }
    
    codigo_ja_cadastrado = false;
    for(int i = 0; i < 100; i++)
        if(codigo == livros_cadastrados[i].codigo)
            codigo_ja_cadastrado = true;

    if(codigo_ja_cadastrado)
        puts("\nERRO: livro ja cadastrado");

    else return codigo;
        
        }while(true);
}

// igual ler_codigo() so que tem um '!' em algum lugar ai
long ler_codigoEXCLUIR(long codigo, book* livros_cadastrados)
{
     
    
    bool codigo_ja_cadastrado;
    do{
    printf("codigo: "); scanf("%ld", &codigo);
    
    
    if(!(codigo >= 100000 && codigo <= 999999)){
        puts("\nERRO: codigo invalido!\n");
        continue;
    }
    
    codigo_ja_cadastrado = false;
    for(int i = 0; i < 100; i++)
        if(codigo == livros_cadastrados[i].codigo)
            codigo_ja_cadastrado = true;

    if(!codigo_ja_cadastrado)
        puts("\nERRO: livro nao cadastrado!");

    else return codigo;
        
        }while(true);
}


int ler_ano(int ano)
{
    do{
        
        printf("Ano: "), scanf("%d", &ano);
        
        if(!(ano >= 1900 && ano <= 2050))
            puts("\nERRO: Ano invalido!\n");
            
        else return ano;
        
    }while(true);
}

void cadastrar_livro(book* livros_cadastrados) 
{
    long codigo;
    codigo = ler_codigo(codigo, livros_cadastrados);
    
    char titulo[31];
    getchar(); ler_palavra(titulo, "titulo: ");
    
    int ano;
    ano = ler_ano(ano);
    
    
    char autor[31];
    getchar(); ler_palavra(autor, "autor: ");
    
    for(int i = 0; i < 100; i++)
    {
        if(livros_cadastrados[i].codigo == 0)
        {
            livros_cadastrados[i].codigo = codigo;
            strcpy(livros_cadastrados[i].titulo, titulo);
            strcpy(livros_cadastrados[i].autor, autor);
            livros_cadastrados[i].ano = ano;
            break;
        }
    }
    printf("\n\nCadastro realizado com sucesso!");
    
}

void excluir_livro(book* livros_cadastrados, int &qtd_livros)
{
    long codigo_excluir = ler_codigoEXCLUIR(codigo_excluir, livros_cadastrados);
    
    for(int i = 0; i < 100; i++)
    {
    
        if(livros_cadastrados[i].codigo == codigo_excluir && livros_cadastrados[i].data.dia != 0)
        {
            puts("\nErro: livro está emprestado!\n");
            break;
        }
        
        if(livros_cadastrados[i].codigo == codigo_excluir)
        {
            livros_cadastrados[i].codigo = 0;
            printf("\nExclusão realizada com sucesso!\n");
            qtd_livros--;
            break;
        }
            
    }       
    
}


void bubble_sortLIVRO(book* v, int n)
{
    bool trocou = true;
    int k = n-1;
    
    while (k > 0 && trocou)
    {
        trocou = false;
        for (int i = 0; i < k; i++)
            if (strcmp(v[i].titulo, v[i+1].titulo) > 0) 
            {
                book aux = v[i+1];
                v[i+1] = v[i];
                v[i] = aux;
                trocou = true;
            }
            k--;
    }
}


void listar_livros(book* livros_cadastrados, int qtd_livros)
{
    bubble_sortLIVRO(livros_cadastrados, qtd_livros);
    
    puts("------------------------------------------------------------------------");
    puts("Codigo titulo                         Autor                         Ano ");
    puts("------------------------------------------------------------------------");
    
    for(int i = 0; i < 100; i++)
        if(livros_cadastrados[i].codigo != 0)
        {
            printf("%-6ld %-30s %-30s%-4d\n", livros_cadastrados[i].codigo,
                                               livros_cadastrados[i].titulo,
                                               livros_cadastrados[i].autor,
                                               livros_cadastrados[i].ano);
            //emprestimo livro
        }
        puts("------------------------------------------------------------------------");
}

////////// FUNCOES menuEmprestimo

void emprestar_livro(user* usuarios_cadastrados, book* livros_cadastrados)
{
    long long cpf = ler_CPF_EXCLUIR(cpf, usuarios_cadastrados);
    long codigo = ler_codigoEXCLUIR(codigo, livros_cadastrados);
    
    int i = 0, j = 0;
    bool achou = false;
    int dia_atual, mes_atual, ano_atual, hora, min, seg;
    for(i; i < 100 && !achou; i++)
        if(usuarios_cadastrados[i].CPF == cpf)
            for(j; j < 100; j++)
                if(livros_cadastrados[j].codigo == codigo)
                {
                    data_hora_atual(dia_atual, mes_atual, ano_atual);
                                    
                    livros_cadastrados[j].data.dia = dia_atual;
                    livros_cadastrados[j].data.mes = mes_atual;
                    livros_cadastrados[j].data.ano = ano_atual;
                    achou = true;
                    i--;
                    break;
                }
    
    puts("Empréstimo concedido!");
    printf("Nome: %-30s\n", usuarios_cadastrados[i].nome_do_usuario);
    printf("Titulo: %-30s\n", livros_cadastrados[j].titulo);
    printf("Data do empréstimo: %02d/%02d/%4d\n", dia_atual, mes_atual, ano_atual);
    
    livros_cadastrados[j].data.dia = dia_atual;
    livros_cadastrados[j].data.mes = mes_atual;
    livros_cadastrados[j].data.ano = ano_atual;
    
    book data_dev;
    data_devolucao(data_dev);
    printf("Data da devolução: %02d/%02d/%4d \n\n", data_dev.data.dia,
                                                    data_dev.data.mes,
                                                    data_dev.data.ano);

    livros_cadastrados[j].data.dia_dev = data_dev.data.dia;
    livros_cadastrados[j].data.mes_dev = data_dev.data.mes;
    livros_cadastrados[j].data.ano_dev = data_dev.data.ano;
    
    usuarios_cadastrados[i].emprestado = livros_cadastrados[j];
}

// verifica se data1 eh maior q data2
bool data_maior(int ano1, int mes1, int dia1, int ano2, int mes2, int dia2)
{
    if(ano1 == ano2 && mes1 == mes2 && dia1 == dia2)
        return true;
    
    return ano1 > ano2 ||
           (ano1 == ano2 && mes1 > mes2) ||
           (ano1 == ano2 && mes1 == mes2 && dia1 > dia2);
}

long ler_data(long data, user* usuarios_cadastrados, long long cpf)
{
    
    int i = 0; // localizar usuario
    for(i; i < 100; i++)
        if(usuarios_cadastrados[i].CPF == cpf)
            break;
            
    int ano_emprestimo = usuarios_cadastrados[i].emprestado.data.ano;
    int mes_emprestimo = usuarios_cadastrados[i].emprestado.data.mes;
    int dia_emprestimo = usuarios_cadastrados[i].emprestado.data.dia;
    
    int ano, mes, dia;
    do{
        printf("Data da devolução: "), scanf("%ld", &data);
    
        ano = data % 10000; 
        mes = (data / 10000) % 100; 
        dia = data / 1000000; 
        
        

        int dias_mes[] = {31, bissexto(ano) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
        if(ano < ano_emprestimo || ano > 2050)
            puts("Erro: data de devolução inválida!\n");
            
        else if((mes > 12 || mes <= 0))
            puts("Erro: data de devolução inválida!\n");
            
        else if(dia > dias_mes[mes - 1] || dia <= 0)
            puts("Erro: data de devolução inválida!\n");
            
        else if(data_maior(ano_emprestimo, mes_emprestimo, dia_emprestimo, ano, mes, dia))
            puts("Erro: data de devolução inválida!\n");
            
        else break;
        
            }while(true);
            
    
    return (dia * 1000000) + mes * (10000) + ano;
        
}


void qtd_dias_atraso(int ano_devolvido, int mes_devolvido, int dia_devolvido, int ano_dev, int mes_dev, int dia_dev)
{

    int dias_mes[] = {31, bissexto(ano_dev) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int dias_atraso = 0;
for (dias_atraso;; dias_atraso++)
    {
        dia_dev++;
        
        if(dia_dev > dias_mes[mes_dev-1])
        {
            dia_dev = 1, mes_dev++;
            
            if(mes_dev > 12)
                mes_dev = 1, ano_dev++;
        }
        
        if(ano_devolvido == ano_dev && mes_devolvido == mes_dev && dia_devolvido == dia_dev)
        {
            dias_atraso++; cout << "dias_atraso: " << dias_atraso;
            break;
        }
    }
    
    printf("Devolução realizada com atraso de %d dias!\n", dias_atraso);
}


void devolver_livro(user* usuarios_cadastrados, book* livros_cadastrados)
{
    long long cpf = ler_CPF_EXCLUIR(cpf, usuarios_cadastrados);
    
    long data = ler_data(data, usuarios_cadastrados, cpf);
    
    int ano_devolvido = data % 10000; 
    int mes_devolvido = (data / 10000) % 100; 
    int dia_devolvido = data / 1000000;
    
    int i = 0; // localizar usuario
    for(i; i < 100; i++)
        if(usuarios_cadastrados[i].CPF == cpf)
            break;
            
    int j = 0; // localizar livro
    for(j; j < 100; j++)
        if(livros_cadastrados[j].codigo == usuarios_cadastrados[i].emprestado.codigo)
            break;
    
    printf("\n\nNome: %-30s", usuarios_cadastrados[i].nome_do_usuario);
    printf("\nTitulo: %-30s\n\n", usuarios_cadastrados[i].emprestado.titulo);
    
    int ano_dev = usuarios_cadastrados[i].emprestado.data.ano_dev;
    int mes_dev = usuarios_cadastrados[i].emprestado.data.mes_dev;
    int dia_dev = usuarios_cadastrados[i].emprestado.data.dia_dev;
    
    usuarios_cadastrados[i].emprestado.codigo = 0;
    livros_cadastrados[j].data.dia = 0;
    
    
    
    
    if(!data_maior(ano_devolvido, mes_devolvido, dia_devolvido, ano_dev, mes_dev, dia_dev))
                puts("Devolução realizada com sucesso no prazo!");
                
    else qtd_dias_atraso(ano_devolvido, mes_devolvido, dia_devolvido, ano_dev, mes_dev, dia_dev);
                  
    
    
    
}

int main()
{

    user usuarios_cadastrados[100];
    book livros_cadastrados[100];
    
    int qtd_usuarios = 0;
    int qtd_livros = 0;
    
   
    while(true)
        menuPrincipal(usuarios_cadastrados, qtd_usuarios, livros_cadastrados, qtd_livros);

    
}
