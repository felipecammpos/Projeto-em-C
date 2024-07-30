#ifndef BANCO_H
#define BANCO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estruturas
typedef struct {
    char agencia[20];
    char numero_da_conta[20];
    char nome_do_cliente[50];
    char cpf_do_cliente[20];
    char data_de_nascimento[20];
    char telefone_de_contato[20];
    char endereco_do_cliente[50];
    char cep[10];
    char local[30];
    char numero_da_casa[10];
    char bairro[30];
    char cidade[30];
    char estado[3];
    char senha_do_cliente[20];
    float limite_da_conta;
    char data_de_vencimento[20];
} Conta;

typedef struct {
    char codigo_funcionario[20];
    char cargo[30];
    char nome_do_funcionario[50];
    char cpf_do_funcionario[20];
    char data_de_nascimento[20];
    char telefone_de_contato[20];
    char endereco_do_funcionario[50];
    char cep[10];
    char local[30];
    char numero_da_casa[10];
    char bairro[30];
    char cidade[30];
    char estado[3];
    char senha_do_funcionario[20];
} Funcionario;

typedef struct {
    char cpf_do_cliente[20];
    char telefone[20];
    char endereco[50];
    char cep[10];
    char numero_da_casa[10];
    char bairro[30];
    char cidade[30];
    char estado[3];
    float saldo;
    char senha_do_cliente[20];
} Cliente;

// Declarações de funções
void ler_string(char *campo, int tamanho, const char *mensagem);
void ler_dados_conta(Conta *conta, const char *tipo_conta);
void escrever_dados_conta(FILE *arquivo, const char *tipo_conta, Conta *conta);
void escrever_dados_cliente(FILE *arquivo, Cliente *cliente);
void cadastro_de_contas();
void encerramento_de_conta();
void consultar_dados_conta(const char *numero_conta);
void consultar_dados_funcionario(const char *codigo_funcionario);
void consultar_dados_cliente(const char *cpf_cliente);
void cadastro_funcionarios();
void alterar_dados_conta();
void alterar_dados_funcionario();
void alterar_dados_cliente();
void menuAlterarDados();
void exportar_relatorio_csv();
void menuFuncionario();
void saldo();
void depositar();
void sacar();
void mostrar_extrato();
void consultar_limite();
void menuCliente();
void menuPrincipal();

#endif // BANCO_H

