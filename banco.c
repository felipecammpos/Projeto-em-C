#include "banco.h"

// Funções auxiliares
void ler_string(char *campo, int tamanho, const char *mensagem) {
    printf("%s", mensagem);
    fgets(campo, tamanho, stdin);
    campo[strcspn(campo, "\n")] = '\0';
}

void ler_dados_conta(Conta *conta, const char *tipo_conta) {
    ler_string(conta->agencia, sizeof(conta->agencia), "Digite a agência: ");
    ler_string(conta->numero_da_conta, sizeof(conta->numero_da_conta), "Digite o número da conta: ");
    if (strcmp(tipo_conta, "Corrente") == 0) {
        printf("Digite o limite da conta: ");
        scanf("%f", &conta->limite_da_conta);
        getchar();
        ler_string(conta->data_de_vencimento, sizeof(conta->data_de_vencimento), "Digite a data de vencimento: ");
    }
    ler_string(conta->nome_do_cliente, sizeof(conta->nome_do_cliente), "Digite o nome do cliente: ");
    ler_string(conta->cpf_do_cliente, sizeof(conta->cpf_do_cliente), "Digite o CPF do cliente: ");
    ler_string(conta->data_de_nascimento, sizeof(conta->data_de_nascimento), "Digite a data de nascimento: ");
    ler_string(conta->telefone_de_contato, sizeof(conta->telefone_de_contato), "Digite o telefone de contato: ");
    ler_string(conta->endereco_do_cliente, sizeof(conta->endereco_do_cliente), "Digite o endereço do cliente: ");
    ler_string(conta->cep, sizeof(conta->cep), "Digite o CEP do cliente: ");
    ler_string(conta->local, sizeof(conta->local), "Digite o local do cliente: ");
    ler_string(conta->numero_da_casa, sizeof(conta->numero_da_casa), "Digite o número da casa: ");
    ler_string(conta->bairro, sizeof(conta->bairro), "Digite o bairro: ");
    ler_string(conta->cidade, sizeof(conta->cidade), "Digite a cidade: ");
    ler_string(conta->estado, sizeof(conta->estado), "Digite o estado: ");
    ler_string(conta->senha_do_cliente, sizeof(conta->senha_do_cliente), "Digite a senha do cliente: ");
}

void escrever_dados_conta(FILE *arquivo, const char *tipo_conta, Conta *conta) {
    fprintf(arquivo, "Tipo de Conta: %s\n", tipo_conta);
    fprintf(arquivo, "Agência: %s\n", conta->agencia);
    fprintf(arquivo, "Número da Conta: %s\n", conta->numero_da_conta);
    fprintf(arquivo, "Nome do Cliente: %s\n", conta->nome_do_cliente);
    fprintf(arquivo, "Data de Nascimento: %s\n", conta->data_de_nascimento);
    fprintf(arquivo, "Telefone de Contato: %s\n", conta->telefone_de_contato);
    fprintf(arquivo, "CPF do Cliente: %s\n", conta->cpf_do_cliente);
    fprintf(arquivo, "Endereço do Cliente: %s\n", conta->endereco_do_cliente);
    fprintf(arquivo, "CEP do Cliente: %s\n", conta->cep);
    fprintf(arquivo, "Local do Cliente: %s\n", conta->local);
    fprintf(arquivo, "Número da Casa: %s\n", conta->numero_da_casa);
    fprintf(arquivo, "Bairro: %s\n", conta->bairro);
    fprintf(arquivo, "Cidade: %s\n", conta->cidade);
    fprintf(arquivo, "Estado: %s\n", conta->estado);
    fprintf(arquivo, "Senha do Cliente: %s\n", conta->senha_do_cliente);
    if (strcmp(tipo_conta, "Corrente") == 0) {
        fprintf(arquivo, "Limite da Conta: %.2f\n", conta->limite_da_conta);
        fprintf(arquivo, "Data de Vencimento: %s\n", conta->data_de_vencimento);
    }
    fprintf(arquivo, "\n");
}

void escrever_dados_cliente(FILE *arquivo, Cliente *cliente) {
    fprintf(arquivo, "CPF: %s\n", cliente->cpf_do_cliente);
    fprintf(arquivo, "Telefone: %s\n", cliente->telefone);
    fprintf(arquivo, "Endereço: %s\n", cliente->endereco);
    fprintf(arquivo, "Número da Casa: %s\n", cliente->numero_da_casa);
    fprintf(arquivo, "CEP: %s\n", cliente->cep);
    fprintf(arquivo, "Bairro: %s\n", cliente->bairro);
    fprintf(arquivo, "Cidade: %s\n", cliente->cidade);
    fprintf(arquivo, "Estado: %s\n", cliente->estado);
    fprintf(arquivo, "Saldo: %.2f\n", cliente->saldo);
    fprintf(arquivo, "Senha do Cliente: %s\n", cliente->senha_do_cliente);
}

// Funções do funcionário
void cadastro_de_contas() {
    printf("\n=========== Abertura de Conta ===========\n");
    Conta novaConta;
    int opcao;
    FILE *arquivo = fopen("contas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    printf("Digite 1 para abrir conta poupança\n");
    printf("Digite 2 para abrir conta corrente\n");
    printf("Digite 3 para voltar ao menu\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar(); // Consumir o newline deixado por scanf

    switch (opcao) {
        case 1:
            printf("\n>>> Abrindo conta poupança <<<\n");
            ler_dados_conta(&novaConta, "Poupança");
            escrever_dados_conta(arquivo, "Poupança", &novaConta);
            break;
        case 2:
            printf("\n>>> Abrindo conta corrente <<<\n");
            ler_dados_conta(&novaConta, "Corrente");
            escrever_dados_conta(arquivo, "Corrente", &novaConta);
            break;
        case 3:
            printf("Voltando ao menu...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }

    fclose(arquivo);
}

void encerramento_de_conta() {
    printf("\n=========== Encerramento de Conta ===========\n");
    char numero_conta[20];
    char senha_admin[20];

    printf("Digite a senha de administrador: ");
    scanf("%s", senha_admin);

    if (strcmp(senha_admin, "senha_admin") != 0) {
        printf("Senha incorreta. Retornando ao menu do funcionário.\n");
        return;
    }

    printf("Digite o número da conta a ser encerrada: ");
    scanf("%s", numero_conta);

    FILE *arquivo = fopen("contas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    FILE *temp_arquivo = fopen("temp_contas.txt", "w");
    if (temp_arquivo == NULL) {
        printf("Erro na criação do arquivo temporário!\n");
        fclose(arquivo);
        return;
    }

    Conta conta;
    char tipo_de_conta[20];
    int conta_encerrada = 0;

    while (fscanf(arquivo, "Tipo de Conta: %[^\n]\n", tipo_de_conta) != EOF) {
        fscanf(arquivo, "Agência: %[^\n]\n", conta.agencia);
        fscanf(arquivo, "Número da Conta: %[^\n]\n", conta.numero_da_conta);
        fscanf(arquivo, "Nome do Cliente: %[^\n]\n", conta.nome_do_cliente);
        fscanf(arquivo, "Data de Nascimento: %[^\n]\n", conta.data_de_nascimento);
        fscanf(arquivo, "Telefone de Contato: %[^\n]\n", conta.telefone_de_contato);
        fscanf(arquivo, "CPF do Cliente: %[^\n]\n", conta.cpf_do_cliente);
        fscanf(arquivo, "Endereço do Cliente: %[^\n]\n", conta.endereco_do_cliente);
        fscanf(arquivo, "CEP do Cliente: %[^\n]\n", conta.cep);
        fscanf(arquivo, "Local do Cliente: %[^\n]\n", conta.local);
        fscanf(arquivo, "Número da Casa: %[^\n]\n", conta.numero_da_casa);
        fscanf(arquivo, "Bairro: %[^\n]\n", conta.bairro);
        fscanf(arquivo, "Cidade: %[^\n]\n", conta.cidade);
        fscanf(arquivo, "Estado: %[^\n]\n", conta.estado);
        fscanf(arquivo, "Senha do Cliente: %[^\n]\n", conta.senha_do_cliente);
        if (strcmp(tipo_de_conta, "Corrente") == 0) {
            fscanf(arquivo, "Limite da Conta: %f\n", &conta.limite_da_conta);
            fscanf(arquivo, "Data de Vencimento: %[^\n]\n", conta.data_de_vencimento);
        }

        if (strcmp(conta.numero_da_conta, numero_conta) != 0) {
            escrever_dados_conta(temp_arquivo, tipo_de_conta, &conta);
        } else {
            conta_encerrada = 1;
        }
    }

    fclose(arquivo);
    fclose(temp_arquivo);

    remove("contas.txt");
    rename("temp_contas.txt", "contas.txt");

    if (conta_encerrada) {
        printf("Conta encerrada com sucesso!\n");
    } else {
        printf("Conta não encontrada!\n");
    }
}

void consultar_dados_conta(const char *numero_conta) {
    printf("\n=========== Consulta de Dados de Conta ===========\n");

    FILE *arquivo = fopen("contas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    Conta conta;
    char tipo_de_conta[20];
    int conta_encontrada = 0;

    while (fscanf(arquivo, "Tipo de Conta: %[^\n]\n", tipo_de_conta) != EOF) {
        fscanf(arquivo, "Agência: %[^\n]\n", conta.agencia);
        fscanf(arquivo, "Número da Conta: %[^\n]\n", conta.numero_da_conta);
        fscanf(arquivo, "Nome do Cliente: %[^\n]\n", conta.nome_do_cliente);
        fscanf(arquivo, "Data de Nascimento: %[^\n]\n", conta.data_de_nascimento);
        fscanf(arquivo, "Telefone de Contato: %[^\n]\n", conta.telefone_de_contato);
        fscanf(arquivo, "CPF do Cliente: %[^\n]\n", conta.cpf_do_cliente);
        fscanf(arquivo, "Endereço do Cliente: %[^\n]\n", conta.endereco_do_cliente);
        fscanf(arquivo, "CEP do Cliente: %[^\n]\n", conta.cep);
        fscanf(arquivo, "Local do Cliente: %[^\n]\n", conta.local);
        fscanf(arquivo, "Número da Casa: %[^\n]\n", conta.numero_da_casa);
        fscanf(arquivo, "Bairro: %[^\n]\n", conta.bairro);
        fscanf(arquivo, "Cidade: %[^\n]\n", conta.cidade);
        fscanf(arquivo, "Estado: %[^\n]\n", conta.estado);
        fscanf(arquivo, "Senha do Cliente: %[^\n]\n", conta.senha_do_cliente);
        if (strcmp(tipo_de_conta, "Corrente") == 0) {
            fscanf(arquivo, "Limite da Conta: %f\n", &conta.limite_da_conta);
            fscanf(arquivo, "Data de Vencimento: %[^\n]\n", conta.data_de_vencimento);
        }

        if (strcmp(conta.numero_da_conta, numero_conta) == 0) {
            conta_encontrada = 1;
            printf("Tipo de Conta: %s\n", tipo_de_conta);
            printf("Nome do Cliente: %s\n", conta.nome_do_cliente);
            printf("CPF do Cliente: %s\n", conta.cpf_do_cliente);
            if (strcmp(tipo_de_conta, "Corrente") == 0) {
                printf("Limite da Conta: %.2f\n", conta.limite_da_conta);
                printf("Data de Vencimento: %s\n", conta.data_de_vencimento);
            }
            break;
        }
    }

    fclose(arquivo);

    if (!conta_encontrada) {
        printf("Conta não encontrada!\n");
    }
}

void consultar_dados_funcionario(const char *codigo_funcionario) {
    printf("\n=========== Consulta de Dados de Funcionário ===========\n");

    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    Funcionario funcionario;
    int funcionario_encontrado = 0;

    while (fscanf(arquivo, "Código do Funcionário: %[^\n]\n", funcionario.codigo_funcionario) != EOF) {
        fscanf(arquivo, "Cargo: %[^\n]\n", funcionario.cargo);
        fscanf(arquivo, "Nome do Funcionário: %[^\n]\n", funcionario.nome_do_funcionario);
        fscanf(arquivo, "CPF do Funcionário: %[^\n]\n", funcionario.cpf_do_funcionario);
        fscanf(arquivo, "Data de Nascimento: %[^\n]\n", funcionario.data_de_nascimento);
        fscanf(arquivo, "Telefone de Contato: %[^\n]\n", funcionario.telefone_de_contato);
        fscanf(arquivo, "Endereço do Funcionário: %[^\n]\n", funcionario.endereco_do_funcionario);
        fscanf(arquivo, "CEP: %[^\n]\n", funcionario.cep);
        fscanf(arquivo, "Local: %[^\n]\n", funcionario.local);
        fscanf(arquivo, "Número da Casa: %[^\n]\n", funcionario.numero_da_casa);
        fscanf(arquivo, "Bairro: %[^\n]\n", funcionario.bairro);
        fscanf(arquivo, "Cidade: %[^\n]\n", funcionario.cidade);
        fscanf(arquivo, "Estado: %[^\n]\n", funcionario.estado);
        fscanf(arquivo, "Senha do Funcionário: %[^\n]\n", funcionario.senha_do_funcionario);

        if (strcmp(funcionario.codigo_funcionario, codigo_funcionario) == 0) {
            funcionario_encontrado = 1;
            printf("Código do Funcionário: %s\n", funcionario.codigo_funcionario);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Nome do Funcionário: %s\n", funcionario.nome_do_funcionario);
            printf("CPF do Funcionário: %s\n", funcionario.cpf_do_funcionario);
            printf("Data de Nascimento: %s\n", funcionario.data_de_nascimento);
            printf("Telefone de Contato: %s\n", funcionario.telefone_de_contato);
            printf("Endereço do Funcionário: %s\n", funcionario.endereco_do_funcionario);
            printf("CEP: %s\n", funcionario.cep);
            printf("Local: %s\n", funcionario.local);
            printf("Número da Casa: %s\n", funcionario.numero_da_casa);
            printf("Bairro: %s\n", funcionario.bairro);
            printf("Cidade: %s\n", funcionario.cidade);
            printf("Estado: %s\n", funcionario.estado);
            printf("Senha do Funcionário: %s\n", funcionario.senha_do_funcionario);
            break;
        }
    }

    fclose(arquivo);

    if (!funcionario_encontrado) {
        printf("Funcionário não encontrado!\n");
    }
}

void consultar_dados_cliente(const char *cpf_cliente) {
    printf("\n=========== Consulta de Dados de Cliente ===========\n");

    FILE *arquivo = fopen("contas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    Conta conta;
    char tipo_de_conta[20];
    int cliente_encontrado = 0;

    while (fscanf(arquivo, "Tipo de Conta: %[^\n]\n", tipo_de_conta) != EOF) {
        fscanf(arquivo, "Agência: %[^\n]\n", conta.agencia);
        fscanf(arquivo, "Número da Conta: %[^\n]\n", conta.numero_da_conta);
        fscanf(arquivo, "Nome do Cliente: %[^\n]\n", conta.nome_do_cliente);
        fscanf(arquivo, "Data de Nascimento: %[^\n]\n", conta.data_de_nascimento);
        fscanf(arquivo, "Telefone de Contato: %[^\n]\n", conta.telefone_de_contato);
        fscanf(arquivo, "CPF do Cliente: %[^\n]\n", conta.cpf_do_cliente);
        fscanf(arquivo, "Endereço do Cliente: %[^\n]\n", conta.endereco_do_cliente);
        fscanf(arquivo, "CEP do Cliente: %[^\n]\n", conta.cep);
        fscanf(arquivo, "Local do Cliente: %[^\n]\n", conta.local);
        fscanf(arquivo, "Número da Casa: %[^\n]\n", conta.numero_da_casa);
        fscanf(arquivo, "Bairro: %[^\n]\n", conta.bairro);
        fscanf(arquivo, "Cidade: %[^\n]\n", conta.cidade);
        fscanf(arquivo, "Estado: %[^\n]\n", conta.estado);
        fscanf(arquivo, "Senha do Cliente: %[^\n]\n", conta.senha_do_cliente);
        if (strcmp(tipo_de_conta, "Corrente") == 0) {
            fscanf(arquivo, "Limite da Conta: %f\n", &conta.limite_da_conta);
            fscanf(arquivo, "Data de Vencimento: %[^\n]\n", conta.data_de_vencimento);
        }

        if (strcmp(conta.cpf_do_cliente, cpf_cliente) == 0) {
            cliente_encontrado = 1;
            printf("Nome do Cliente: %s\n", conta.nome_do_cliente);
            printf("CPF do Cliente: %s\n", conta.cpf_do_cliente);
            printf("Data de Nascimento: %s\n", conta.data_de_nascimento);
            printf("Telefone de Contato: %s\n", conta.telefone_de_contato);
            printf("Endereço do Cliente: %s\n", conta.endereco_do_cliente);
            printf("CEP do Cliente: %s\n", conta.cep);
            printf("Local do Cliente: %s\n", conta.local);
            printf("Número da Casa: %s\n", conta.numero_da_casa);
            printf("Bairro: %s\n", conta.bairro);
            printf("Cidade: %s\n", conta.cidade);
            printf("Estado: %s\n", conta.estado);
            break;
        }
    }

    fclose(arquivo);

    if (!cliente_encontrado) {
        printf("Cliente não encontrado!\n");
    }
}

void cadastro_funcionarios() {
    Funcionario funcionario;
    char senha_admin[20];
    int opcao;
    FILE *arquivo = fopen("funcionarios.txt", "a");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!");
        return;
    }

    printf("\nDigite a senha de administrador: ");
    scanf("%s", senha_admin);

    if (strcmp(senha_admin, "senha_admin") == 0) {
        do {
            printf("\n================ Cadastro de Funcionário ================\n");
            printf("1 - Cadastrar novo funcionário\n");
            printf("2 - Sair\n");
            printf("Digite a opção desejada: ");
            scanf("%d", &opcao);
            getchar();  
            switch (opcao) {
                case 1:
                    printf("\n>>> Cadastro de novo funcionário <<<\n");
                    ler_string(funcionario.codigo_funcionario, sizeof(funcionario.codigo_funcionario), "Digite o código do funcionário: ");
                    ler_string(funcionario.cargo, sizeof(funcionario.cargo), "Informe o cargo do funcionário: ");
                    ler_string(funcionario.nome_do_funcionario, sizeof(funcionario.nome_do_funcionario), "Digite o nome do funcionário: ");
                    ler_string(funcionario.cpf_do_funcionario, sizeof(funcionario.cpf_do_funcionario), "Digite o CPF do funcionário: ");
                    ler_string(funcionario.data_de_nascimento, sizeof(funcionario.data_de_nascimento), "Digite a data de nascimento do funcionário: ");
                    ler_string(funcionario.telefone_de_contato, sizeof(funcionario.telefone_de_contato), "Digite o telefone de contato do funcionário: ");
                    ler_string(funcionario.endereco_do_funcionario, sizeof(funcionario.endereco_do_funcionario), "Informe o endereço do funcionário: ");
                    ler_string(funcionario.cep, sizeof(funcionario.cep), "Informe o CEP do funcionário: ");
                    ler_string(funcionario.local, sizeof(funcionario.local), "Informe o local do funcionário: ");
                    ler_string(funcionario.numero_da_casa, sizeof(funcionario.numero_da_casa), "Informe o número da casa: ");
                    ler_string(funcionario.bairro, sizeof(funcionario.bairro), "Informe o bairro: ");
                    ler_string(funcionario.cidade, sizeof(funcionario.cidade), "Informe a cidade: ");
                    ler_string(funcionario.estado, sizeof(funcionario.estado), "Digite o estado: ");
                    ler_string(funcionario.senha_do_funcionario, sizeof(funcionario.senha_do_funcionario), "Digite a senha do funcionário: ");

                    fprintf(arquivo, "Código do Funcionário: %s\n", funcionario.codigo_funcionario);
                    fprintf(arquivo, "Cargo: %s\n", funcionario.cargo);
                    fprintf(arquivo, "Nome do Funcionário: %s\n", funcionario.nome_do_funcionario);
                    fprintf(arquivo, "CPF do Funcionário: %s\n", funcionario.cpf_do_funcionario);
                    fprintf(arquivo, "Data de Nascimento: %s\n", funcionario.data_de_nascimento);
                    fprintf(arquivo, "Telefone de Contato: %s\n", funcionario.telefone_de_contato);
                    fprintf(arquivo, "Endereço do Funcionário: %s\n", funcionario.endereco_do_funcionario);
                    fprintf(arquivo, "CEP: %s\n", funcionario.cep);
                    fprintf(arquivo, "Local: %s\n", funcionario.local);
                    fprintf(arquivo, "Número da Casa: %s\n", funcionario.numero_da_casa);
                    fprintf(arquivo, "Bairro: %s\n", funcionario.bairro);
                    fprintf(arquivo, "Cidade: %s\n", funcionario.cidade);
                    fprintf(arquivo, "Estado: %s\n", funcionario.estado);
                    fprintf(arquivo, "Senha do Funcionário: %s\n\n", funcionario.senha_do_funcionario);

                    printf("\nFuncionário cadastrado com sucesso!\n");
                    break;
                case 2:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opção inválida. Tente novamente.\n");
                    break;
            }
        } while (opcao != 2);
    } else {
        printf("Senha incorreta. Retornando ao menu do funcionário.\n");
    }

    fclose(arquivo);
}

void alterar_dados_conta() {
    printf("\n=========== Alterar Dados de Conta ===========\n");
    char numero_conta[20];
    char tipo_de_conta[20];
    char novo_dado[100];

    printf("Digite o número da conta: ");
    scanf("%s", numero_conta);
    getchar(); // Consumir o newline deixado por scanf

    FILE *arquivo = fopen("contas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    FILE *temp_arquivo = fopen("temp_contas.txt", "w");
    if (temp_arquivo == NULL) {
        printf("Erro na criação do arquivo temporário!\n");
        fclose(arquivo);
        return;
    }

    Conta conta;
    int conta_encontrada = 0;

    while (fscanf(arquivo, "Tipo de Conta: %[^\n]\n", tipo_de_conta) != EOF) {
        fscanf(arquivo, "Agência: %[^\n]\n", conta.agencia);
        fscanf(arquivo, "Número da Conta: %[^\n]\n", conta.numero_da_conta);
        fscanf(arquivo, "Nome do Cliente: %[^\n]\n", conta.nome_do_cliente);
        fscanf(arquivo, "Data de Nascimento: %[^\n]\n", conta.data_de_nascimento);
        fscanf(arquivo, "Telefone de Contato: %[^\n]\n", conta.telefone_de_contato);
        fscanf(arquivo, "CPF do Cliente: %[^\n]\n", conta.cpf_do_cliente);
        fscanf(arquivo, "Endereço do Cliente: %[^\n]\n", conta.endereco_do_cliente);
        fscanf(arquivo, "CEP do Cliente: %[^\n]\n", conta.cep);
        fscanf(arquivo, "Local do Cliente: %[^\n]\n", conta.local);
        fscanf(arquivo, "Número da Casa: %[^\n]\n", conta.numero_da_casa);
        fscanf(arquivo, "Bairro: %[^\n]\n", conta.bairro);
        fscanf(arquivo, "Cidade: %[^\n]\n", conta.cidade);
        fscanf(arquivo, "Estado: %[^\n]\n", conta.estado);
        fscanf(arquivo, "Senha do Cliente: %[^\n]\n", conta.senha_do_cliente);
        if (strcmp(tipo_de_conta, "Corrente") == 0) {
            fscanf(arquivo, "Limite da Conta: %f\n", &conta.limite_da_conta);
            fscanf(arquivo, "Data de Vencimento: %[^\n]\n", conta.data_de_vencimento);
        }

        if (strcmp(conta.numero_da_conta, numero_conta) == 0) {
            conta_encontrada = 1;
            printf("Dados atuais da conta %s:\n", numero_conta);
            printf("Agência: %s\n", conta.agencia);
            printf("Número da Conta: %s\n", conta.numero_da_conta);
            printf("Nome do Cliente: %s\n", conta.nome_do_cliente);
            printf("Data de Nascimento: %s\n", conta.data_de_nascimento);
            printf("Telefone de Contato: %s\n", conta.telefone_de_contato);
            printf("CPF do Cliente: %s\n", conta.cpf_do_cliente);
            printf("Endereço do Cliente: %s\n", conta.endereco_do_cliente);
            printf("CEP do Cliente: %s\n", conta.cep);
            printf("Local do Cliente: %s\n", conta.local);
            printf("Número da Casa: %s\n", conta.numero_da_casa);
            printf("Bairro: %s\n", conta.bairro);
            printf("Cidade: %s\n", conta.cidade);
            printf("Estado: %s\n", conta.estado);
            printf("Senha do Cliente: %s\n", conta.senha_do_cliente);
            if (strcmp(tipo_de_conta, "Corrente") == 0) {
                printf("Limite da Conta: %.2f\n", conta.limite_da_conta);
                printf("Data de Vencimento: %s\n", conta.data_de_vencimento);
            }

            printf("Digite os novos dados (pressione Enter para manter o atual):\n");
            printf("Agência (%s): ", conta.agencia);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.agencia, strtok(novo_dado, "\n"));
            printf("Número da Conta (%s): ", conta.numero_da_conta);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.numero_da_conta, strtok(novo_dado, "\n"));
            printf("Nome do Cliente (%s): ", conta.nome_do_cliente);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.nome_do_cliente, strtok(novo_dado, "\n"));
            printf("Data de Nascimento (%s): ", conta.data_de_nascimento);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.data_de_nascimento, strtok(novo_dado, "\n"));
            printf("Telefone de Contato (%s): ", conta.telefone_de_contato);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.telefone_de_contato, strtok(novo_dado, "\n"));
            printf("CPF do Cliente (%s): ", conta.cpf_do_cliente);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.cpf_do_cliente, strtok(novo_dado, "\n"));
            printf("Endereço do Cliente (%s): ", conta.endereco_do_cliente);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.endereco_do_cliente, strtok(novo_dado, "\n"));
            printf("CEP do Cliente (%s): ", conta.cep);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.cep, strtok(novo_dado, "\n"));
            printf("Local do Cliente (%s): ", conta.local);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.local, strtok(novo_dado, "\n"));
            printf("Número da Casa (%s): ", conta.numero_da_casa);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.numero_da_casa, strtok(novo_dado, "\n"));
            printf("Bairro (%s): ", conta.bairro);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.bairro, strtok(novo_dado, "\n"));
            printf("Cidade (%s): ", conta.cidade);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.cidade, strtok(novo_dado, "\n"));
            printf("Estado (%s): ", conta.estado);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.estado, strtok(novo_dado, "\n"));
            printf("Senha do Cliente (%s): ", conta.senha_do_cliente);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.senha_do_cliente, strtok(novo_dado, "\n"));
            if (strcmp(tipo_de_conta, "Corrente") == 0) {
                printf("Limite da Conta (%.2f): ", conta.limite_da_conta);
                fgets(novo_dado, 100, stdin);
                if (strcmp(novo_dado, "\n") != 0) conta.limite_da_conta = atof(strtok(novo_dado, "\n"));
                printf("Data de Vencimento (%s): ", conta.data_de_vencimento);
                fgets(novo_dado, 100, stdin);
                if (strcmp(novo_dado, "\n") != 0) strcpy(conta.data_de_vencimento, strtok(novo_dado, "\n"));
            }

            escrever_dados_conta(temp_arquivo, tipo_de_conta, &conta);
        } else {
            escrever_dados_conta(temp_arquivo, tipo_de_conta, &conta);
        }
    }

    fclose(arquivo);
    fclose(temp_arquivo);

    remove("contas.txt");
    rename("temp_contas.txt", "contas.txt");

    if (conta_encontrada) {
        printf("Dados da conta alterados com sucesso!\n");
    } else {
        printf("Conta não encontrada!\n");
    }
}

void alterar_dados_funcionario() {
    printf("\n=========== Alterar Dados de Funcionário ===========\n");
    char codigo_funcionario[20];
    char novo_dado[100];

    printf("Digite o código do funcionário: ");
    scanf("%s", codigo_funcionario);
    getchar(); // Consumir o newline deixado por scanf

    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    FILE *temp_arquivo = fopen("temp_funcionarios.txt", "w");
    if (temp_arquivo == NULL) {
        printf("Erro na criação do arquivo temporário!\n");
        fclose(arquivo);
        return;
    }

    Funcionario funcionario;
    int funcionario_encontrado = 0;

    while (fscanf(arquivo, "Código do Funcionário: %[^\n]\n", funcionario.codigo_funcionario) != EOF) {
        fscanf(arquivo, "Cargo: %[^\n]\n", funcionario.cargo);
        fscanf(arquivo, "Nome do Funcionário: %[^\n]\n", funcionario.nome_do_funcionario);
        fscanf(arquivo, "CPF do Funcionário: %[^\n]\n", funcionario.cpf_do_funcionario);
        fscanf(arquivo, "Data de Nascimento: %[^\n]\n", funcionario.data_de_nascimento);
        fscanf(arquivo, "Telefone de Contato: %[^\n]\n", funcionario.telefone_de_contato);
        fscanf(arquivo, "Endereço do Funcionário: %[^\n]\n", funcionario.endereco_do_funcionario);
        fscanf(arquivo, "CEP: %[^\n]\n", funcionario.cep);
        fscanf(arquivo, "Local: %[^\n]\n", funcionario.local);
        fscanf(arquivo, "Número da Casa: %[^\n]\n", funcionario.numero_da_casa);
        fscanf(arquivo, "Bairro: %[^\n]\n", funcionario.bairro);
        fscanf(arquivo, "Cidade: %[^\n]\n", funcionario.cidade);
        fscanf(arquivo, "Estado: %[^\n]\n", funcionario.estado);
        fscanf(arquivo, "Senha do Funcionário: %[^\n]\n", funcionario.senha_do_funcionario);

        if (strcmp(funcionario.codigo_funcionario, codigo_funcionario) == 0) {
            funcionario_encontrado = 1;
            printf("Dados atuais do funcionário %s:\n", codigo_funcionario);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Nome do Funcionário: %s\n", funcionario.nome_do_funcionario);
            printf("CPF do Funcionário: %s\n", funcionario.cpf_do_funcionario);
            printf("Data de Nascimento: %s\n", funcionario.data_de_nascimento);
            printf("Telefone de Contato: %s\n", funcionario.telefone_de_contato);
            printf("Endereço do Funcionário: %s\n", funcionario.endereco_do_funcionario);
            printf("CEP: %s\n", funcionario.cep);
            printf("Local: %s\n", funcionario.local);
            printf("Número da Casa: %s\n", funcionario.numero_da_casa);
            printf("Bairro: %s\n", funcionario.bairro);
            printf("Cidade: %s\n", funcionario.cidade);
            printf("Estado: %s\n", funcionario.estado);
            printf("Senha do Funcionário: %s\n", funcionario.senha_do_funcionario);

            printf("Digite os novos dados (pressione Enter para manter o atual):\n");
            printf("Cargo (%s): ", funcionario.cargo);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.cargo, strtok(novo_dado, "\n"));
            printf("Nome do Funcionário (%s): ", funcionario.nome_do_funcionario);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.nome_do_funcionario, strtok(novo_dado, "\n"));
            printf("CPF do Funcionário (%s): ", funcionario.cpf_do_funcionario);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.cpf_do_funcionario, strtok(novo_dado, "\n"));
            printf("Data de Nascimento (%s): ", funcionario.data_de_nascimento);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.data_de_nascimento, strtok(novo_dado, "\n"));
            printf("Telefone de Contato (%s): ", funcionario.telefone_de_contato);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.telefone_de_contato, strtok(novo_dado, "\n"));
            printf("Endereço do Funcionário (%s): ", funcionario.endereco_do_funcionario);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.endereco_do_funcionario, strtok(novo_dado, "\n"));
            printf("CEP (%s): ", funcionario.cep);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.cep, strtok(novo_dado, "\n"));
            printf("Local (%s): ", funcionario.local);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.local, strtok(novo_dado, "\n"));
            printf("Número da Casa (%s): ", funcionario.numero_da_casa);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.numero_da_casa, strtok(novo_dado, "\n"));
            printf("Bairro (%s): ", funcionario.bairro);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.bairro, strtok(novo_dado, "\n"));
            printf("Cidade (%s): ", funcionario.cidade);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.cidade, strtok(novo_dado, "\n"));
            printf("Estado (%s): ", funcionario.estado);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.estado, strtok(novo_dado, "\n"));
            printf("Senha do Funcionário (%s): ", funcionario.senha_do_funcionario);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(funcionario.senha_do_funcionario, strtok(novo_dado, "\n"));

            fprintf(temp_arquivo, "Código do Funcionário: %s\n", funcionario.codigo_funcionario);
            fprintf(temp_arquivo, "Cargo: %s\n", funcionario.cargo);
            fprintf(temp_arquivo, "Nome do Funcionário: %s\n", funcionario.nome_do_funcionario);
            fprintf(temp_arquivo, "CPF do Funcionário: %s\n", funcionario.cpf_do_funcionario);
            fprintf(temp_arquivo, "Data de Nascimento: %s\n", funcionario.data_de_nascimento);
            fprintf(temp_arquivo, "Telefone de Contato: %s\n", funcionario.telefone_de_contato);
            fprintf(temp_arquivo, "Endereço do Funcionário: %s\n", funcionario.endereco_do_funcionario);
            fprintf(temp_arquivo, "CEP: %s\n", funcionario.cep);
            fprintf(temp_arquivo, "Local: %s\n", funcionario.local);
            fprintf(temp_arquivo, "Número da Casa: %s\n", funcionario.numero_da_casa);
            fprintf(temp_arquivo, "Bairro: %s\n", funcionario.bairro);
            fprintf(temp_arquivo, "Cidade: %s\n", funcionario.cidade);
            fprintf(temp_arquivo, "Estado: %s\n", funcionario.estado);
            fprintf(temp_arquivo, "Senha do Funcionário: %s\n\n", funcionario.senha_do_funcionario);
        } else {
            fprintf(temp_arquivo, "Código do Funcionário: %s\n", funcionario.codigo_funcionario);
            fprintf(temp_arquivo, "Cargo: %s\n", funcionario.cargo);
            fprintf(temp_arquivo, "Nome do Funcionário: %s\n", funcionario.nome_do_funcionario);
            fprintf(temp_arquivo, "CPF do Funcionário: %s\n", funcionario.cpf_do_funcionario);
            fprintf(temp_arquivo, "Data de Nascimento: %s\n", funcionario.data_de_nascimento);
            fprintf(temp_arquivo, "Telefone de Contato: %s\n", funcionario.telefone_de_contato);
            fprintf(temp_arquivo, "Endereço do Funcionário: %s\n", funcionario.endereco_do_funcionario);
            fprintf(temp_arquivo, "CEP: %s\n", funcionario.cep);
            fprintf(temp_arquivo, "Local: %s\n", funcionario.local);
            fprintf(temp_arquivo, "Número da Casa: %s\n", funcionario.numero_da_casa);
            fprintf(temp_arquivo, "Bairro: %s\n", funcionario.bairro);
            fprintf(temp_arquivo, "Cidade: %s\n", funcionario.cidade);
            fprintf(temp_arquivo, "Estado: %s\n", funcionario.estado);
            fprintf(temp_arquivo, "Senha do Funcionário: %s\n\n", funcionario.senha_do_funcionario);
        }
    }

    fclose(arquivo);
    fclose(temp_arquivo);

    remove("funcionarios.txt");
    rename("temp_funcionarios.txt", "funcionarios.txt");

    if (funcionario_encontrado) {
        printf("Dados do funcionário alterados com sucesso!\n");
    } else {
        printf("Funcionário não encontrado!\n");
    }
}

void alterar_dados_cliente() {
    printf("\n=========== Alterar Dados de Cliente ===========\n");
    char cpf_cliente[20];
    char novo_dado[100];

    printf("Digite o CPF do cliente: ");
    scanf("%s", cpf_cliente);
    getchar(); // Consumir o newline deixado por scanf

    FILE *arquivo = fopen("contas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    FILE *temp_arquivo = fopen("temp_contas.txt", "w");
    if (temp_arquivo == NULL) {
        printf("Erro na criação do arquivo temporário!\n");
        fclose(arquivo);
        return;
    }

    Conta conta;
    char tipo_de_conta[20];
    int cliente_encontrado = 0;

    while (fscanf(arquivo, "Tipo de Conta: %[^\n]\n", tipo_de_conta) != EOF) {
        fscanf(arquivo, "Agência: %[^\n]\n", conta.agencia);
        fscanf(arquivo, "Número da Conta: %[^\n]\n", conta.numero_da_conta);
        fscanf(arquivo, "Nome do Cliente: %[^\n]\n", conta.nome_do_cliente);
        fscanf(arquivo, "Data de Nascimento: %[^\n]\n", conta.data_de_nascimento);
        fscanf(arquivo, "Telefone de Contato: %[^\n]\n", conta.telefone_de_contato);
        fscanf(arquivo, "CPF do Cliente: %[^\n]\n", conta.cpf_do_cliente);
        fscanf(arquivo, "Endereço do Cliente: %[^\n]\n", conta.endereco_do_cliente);
        fscanf(arquivo, "CEP do Cliente: %[^\n]\n", conta.cep);
        fscanf(arquivo, "Local do Cliente: %[^\n]\n", conta.local);
        fscanf(arquivo, "Número da Casa: %[^\n]\n", conta.numero_da_casa);
        fscanf(arquivo, "Bairro: %[^\n]\n", conta.bairro);
        fscanf(arquivo, "Cidade: %[^\n]\n", conta.cidade);
        fscanf(arquivo, "Estado: %[^\n]\n", conta.estado);
        fscanf(arquivo, "Senha do Cliente: %[^\n]\n", conta.senha_do_cliente);
        if (strcmp(tipo_de_conta, "Corrente") == 0) {
            fscanf(arquivo, "Limite da Conta: %f\n", &conta.limite_da_conta);
            fscanf(arquivo, "Data de Vencimento: %[^\n]\n", conta.data_de_vencimento);
        }

        if (strcmp(conta.cpf_do_cliente, cpf_cliente) == 0) {
            cliente_encontrado = 1;
            printf("Dados atuais do cliente %s:\n", cpf_cliente);
            printf("Nome do Cliente: %s\n", conta.nome_do_cliente);
            printf("CPF do Cliente: %s\n", conta.cpf_do_cliente);
            printf("Data de Nascimento: %s\n", conta.data_de_nascimento);
            printf("Telefone de Contato: %s\n", conta.telefone_de_contato);
            printf("Endereço do Cliente: %s\n", conta.endereco_do_cliente);
            printf("CEP do Cliente: %s\n", conta.cep);
            printf("Local do Cliente: %s\n", conta.local);
            printf("Número da Casa: %s\n", conta.numero_da_casa);
            printf("Bairro: %s\n", conta.bairro);
            printf("Cidade: %s\n", conta.cidade);
            printf("Estado: %s\n", conta.estado);
            printf("Senha do Cliente: %s\n", conta.senha_do_cliente);
            if (strcmp(tipo_de_conta, "Corrente") == 0) {
                printf("Limite da Conta: %.2f\n", conta.limite_da_conta);
                printf("Data de Vencimento: %s\n", conta.data_de_vencimento);
            }

            printf("Digite os novos dados (pressione Enter para manter o atual):\n");
            printf("Nome do Cliente (%s): ", conta.nome_do_cliente);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.nome_do_cliente, strtok(novo_dado, "\n"));
            printf("CPF do Cliente (%s): ", conta.cpf_do_cliente);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.cpf_do_cliente, strtok(novo_dado, "\n"));
            printf("Data de Nascimento (%s): ", conta.data_de_nascimento);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.data_de_nascimento, strtok(novo_dado, "\n"));
            printf("Telefone de Contato (%s): ", conta.telefone_de_contato);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.telefone_de_contato, strtok(novo_dado, "\n"));
            printf("Endereço do Cliente (%s): ", conta.endereco_do_cliente);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.endereco_do_cliente, strtok(novo_dado, "\n"));
            printf("CEP do Cliente (%s): ", conta.cep);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.cep, strtok(novo_dado, "\n"));
            printf("Local do Cliente (%s): ", conta.local);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.local, strtok(novo_dado, "\n"));
            printf("Número da Casa (%s): ", conta.numero_da_casa);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.numero_da_casa, strtok(novo_dado, "\n"));
            printf("Bairro (%s): ", conta.bairro);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.bairro, strtok(novo_dado, "\n"));
            printf("Cidade (%s): ", conta.cidade);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.cidade, strtok(novo_dado, "\n"));
            printf("Estado (%s): ", conta.estado);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.estado, strtok(novo_dado, "\n"));
            printf("Senha do Cliente (%s): ", conta.senha_do_cliente);
            fgets(novo_dado, 100, stdin);
            if (strcmp(novo_dado, "\n") != 0) strcpy(conta.senha_do_cliente, strtok(novo_dado, "\n"));

            escrever_dados_conta(temp_arquivo, tipo_de_conta, &conta);
        } else {
            escrever_dados_conta(temp_arquivo, tipo_de_conta, &conta);
        }
    }

    fclose(arquivo);
    fclose(temp_arquivo);

    remove("contas.txt");
    rename("temp_contas.txt", "contas.txt");

    if (cliente_encontrado) {
        printf("Dados do cliente alterados com sucesso!\n");
    } else {
        printf("Cliente não encontrado!\n");
    }
}

void menuAlterarDados() {
    char senha[20];
    int opcao;

    printf("Digite a senha do administrador: ");
    scanf("%s", senha);

    if (strcmp(senha, "admin") != 0) {
        printf("Senha incorreta!\n");
        return;
    }

    do {
        printf("\n=========== Alterar Dados ===========\n");
        printf("1 - Alterar Conta\n");
        printf("2 - Alterar Funcionário\n");
        printf("3 - Alterar Cliente\n");
        printf("4 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Consumir o newline deixado por scanf

        switch (opcao) {
            case 1:
                alterar_dados_conta();
                break;
            case 2:
                alterar_dados_funcionario();
                break;
            case 3:
                alterar_dados_cliente();
                break;
            case 4:
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);
}

void exportar_relatorio_csv() {
    FILE *arquivo = fopen("contas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    FILE *arquivo_csv = fopen("relatorio_movimentacao.csv", "w");
    if (arquivo_csv == NULL) {
        printf("Erro na criação do arquivo CSV!\n");
        fclose(arquivo);
        return;
    }

    Conta conta;
    char tipo_de_conta[20];

    // Cabeçalho do arquivo CSV
    fprintf(arquivo_csv, "Tipo de Conta;Agência;Número da Conta;Nome do Cliente;Data de Nascimento;Telefone de Contato;CPF do Cliente;Endereço do Cliente;CEP do Cliente;Local do Cliente;Número da Casa;Bairro;Cidade;Estado;Limite da Conta;Data de Vencimento\n");

    // Leitura e escrita dos dados
    while (fscanf(arquivo, "Tipo de Conta: %[^\n]\n", tipo_de_conta) != EOF) {
        fscanf(arquivo, "Agência: %[^\n]\n", conta.agencia);
        fscanf(arquivo, "Número da Conta: %[^\n]\n", conta.numero_da_conta);
        fscanf(arquivo, "Nome do Cliente: %[^\n]\n", conta.nome_do_cliente);
        fscanf(arquivo, "Data de Nascimento: %[^\n]\n", conta.data_de_nascimento);
        fscanf(arquivo, "Telefone de Contato: %[^\n]\n", conta.telefone_de_contato);
        fscanf(arquivo, "CPF do Cliente: %[^\n]\n", conta.cpf_do_cliente);
        fscanf(arquivo, "Endereço do Cliente: %[^\n]\n", conta.endereco_do_cliente);
        fscanf(arquivo, "CEP do Cliente: %[^\n]\n", conta.cep);
        fscanf(arquivo, "Local do Cliente: %[^\n]\n", conta.local);
        fscanf(arquivo, "Número da Casa: %[^\n]\n", conta.numero_da_casa);
        fscanf(arquivo, "Bairro: %[^\n]\n", conta.bairro);
        fscanf(arquivo, "Cidade: %[^\n]\n", conta.cidade);
        fscanf(arquivo, "Estado: %[^\n]\n", conta.estado);
        fscanf(arquivo, "Senha do Cliente: %[^\n]\n", conta.senha_do_cliente);
        if (strcmp(tipo_de_conta, "Corrente") == 0) {
            fscanf(arquivo, "Limite da Conta: %f\n", &conta.limite_da_conta);
            fscanf(arquivo, "Data de Vencimento: %[^\n]\n", conta.data_de_vencimento);
        }

        fprintf(arquivo_csv, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s", tipo_de_conta, conta.agencia, conta.numero_da_conta, conta.nome_do_cliente, conta.data_de_nascimento, conta.telefone_de_contato, conta.cpf_do_cliente, conta.endereco_do_cliente, conta.cep, conta.local, conta.numero_da_casa, conta.bairro, conta.cidade, conta.estado);
        if (strcmp(tipo_de_conta, "Corrente") == 0) {
            fprintf(arquivo_csv, ";%.2f;%s\n", conta.limite_da_conta, conta.data_de_vencimento);
        } else {
            fprintf(arquivo_csv, ";;\n");
        }
    }

    fclose(arquivo);
    fclose(arquivo_csv);
    printf("Relatório exportado para relatorio_movimentacao.csv com sucesso!\n");
}

void menuFuncionario() {
    int opcao;
    do {
        printf("\n================ Menu do Funcionário ================\n");
        printf("1 - Abertura de contas\n");
        printf("2 - Encerramento de conta\n");
        printf("3 - Consultar dados\n");
        printf("4 - Alterar dados\n");
        printf("5 - Cadastro de funcionários\n");
        printf("6 - Gerar relatórios\n");
        printf("7 - Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar(); // Consumir o newline deixado por scanf

        switch (opcao) {
            case 1:
                cadastro_de_contas();
                break;
            case 2:
                encerramento_de_conta();
                break;
            case 3: {
                int consulta_opcao;
                printf("\n--- Consultar Dados ---\n");
                printf("1 - Consultar conta\n");
                printf("2 - Consultar funcionário\n");
                printf("3 - Consultar cliente\n");
                printf("4 - Voltar\n");
                printf("Opção: ");
                scanf("%d", &consulta_opcao);
                getchar(); // Consumir o newline deixado por scanf
                switch (consulta_opcao) {
                    case 1: {
                        char numero_conta[20];
                        printf("Digite o número da conta: ");
                        scanf("%s", numero_conta);
                        consultar_dados_conta(numero_conta);
                        break;
                    }
                    case 2: {
                        char codigo_funcionario[20];
                        printf("Digite o código do funcionário: ");
                        scanf("%s", codigo_funcionario);
                        consultar_dados_funcionario(codigo_funcionario);
                        break;
                    }
                    case 3: {
                        char cpf_cliente[20];
                        printf("Digite o CPF do cliente: ");
                        scanf("%s", cpf_cliente);
                        consultar_dados_cliente(cpf_cliente);
                        break;
                    }
                    case 4:
                        printf("Voltando ao menu...\n");
                        break;
                    default:
                        printf("Opção inválida!\n");
                        break;
                }
                break;
            }
            case 4:
                menuAlterarDados();
                break;
            case 5:
                cadastro_funcionarios();
                break;
            case 6:
                exportar_relatorio_csv();
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 7);
}

void saldo() {
    float saldo = 0.0;
    FILE *arquivo_saldo;

    arquivo_saldo = fopen("saldo.txt", "r");
    if (arquivo_saldo == NULL) {
        printf("Erro ao abrir o arquivo de saldo!\n");
        return;
    }
    fscanf(arquivo_saldo, "%f", &saldo);
    fclose(arquivo_saldo);

    printf("Seu saldo atual é: R$ %.2f\n", saldo);
}

// Funções do cliente
void depositar() {
    float saldo = 0.0;
    float valor;
    FILE *arquivo_extrato;
    FILE *arquivo_saldo;
    
    arquivo_saldo = fopen("saldo.txt", "r+");
    if (arquivo_saldo == NULL) {
        arquivo_saldo = fopen("saldo.txt", "w+");
    }
    fscanf(arquivo_saldo, "%f", &saldo);
    
    printf("Informe o valor que deseja depositar: ");
    scanf("%f", &valor);

    if (valor > 0) {
        saldo += valor;
        printf("O valor de R$: %.2f foi depositado com sucesso!\n", valor);

        arquivo_extrato = fopen("extrato.txt", "a");
        fprintf(arquivo_extrato, "Depósito: R$ %.2f\n", valor);
        fclose(arquivo_extrato);

        rewind(arquivo_saldo);
        fprintf(arquivo_saldo, "%.2f", saldo);
    } else {
        printf("Valor informado inválido! Tente novamente.\n");
    }
    fclose(arquivo_saldo);
}

void sacar() {
    float saldo = 0.0;
    float valor;
    float limite = 1000.0; // Definindo um limite para saque
    int numero_saques = 0;
    int LIMITE_SAQUE = 3;
    FILE *arquivo_extrato;
    FILE *arquivo_saldo;
    FILE *arquivo_saques;

    arquivo_saldo = fopen("saldo.txt", "r+");
    if (arquivo_saldo == NULL) {
        printf("Erro ao abrir o arquivo de saldo!\n");
        return;
    }
    fscanf(arquivo_saldo, "%f", &saldo);
    
    arquivo_saques = fopen("saques.txt", "r+");
    if (arquivo_saques == NULL) {
        arquivo_saques = fopen("saques.txt", "w+");
        fprintf(arquivo_saques, "0");
        rewind(arquivo_saques);
    }
    fscanf(arquivo_saques, "%d", &numero_saques);

    printf("Informe o valor para saque: ");
    scanf("%f", &valor);

    if (valor > 0 && valor <= saldo && valor <= limite && numero_saques < LIMITE_SAQUE) {
        saldo -= valor;
        numero_saques++;
        printf("O valor de R$: %.2f foi sacado com sucesso!\n", valor);

        arquivo_extrato = fopen("extrato.txt", "a");
        fprintf(arquivo_extrato, "Saque: R$ %.2f\n", valor);
        fclose(arquivo_extrato);

        rewind(arquivo_saldo);
        fprintf(arquivo_saldo, "%.2f", saldo);

        rewind(arquivo_saques);
        fprintf(arquivo_saques, "%d", numero_saques);
    } else {
        if (valor <= 0) {
            printf("Operação falhou. O valor informado é inválido.\n");
        } else if (valor > saldo) {
            printf("Você não possui saldo suficiente!\n");
        } else if (valor > limite) {
            printf("O Valor do saque ultrapassou o limite disponível em conta. Tente novamente.\n");
        } else if (numero_saques >= LIMITE_SAQUE) {
            printf("Limite de saques diário excedido. Tente novamente mais tarde.\n");
        }
    }
    fclose(arquivo_saldo);
    fclose(arquivo_saques);
}

void mostrar_extrato() {
    char senha_cliente[20];
    int senha_correta = 0;

    printf("Digite a senha do cliente: ");
    scanf("%s", senha_cliente);

    FILE *arquivo = fopen("contas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo de contas!\n");
        return;
    }

    Conta conta;
    char tipo_de_conta[20];
    while (fscanf(arquivo, "Tipo de Conta: %[^\n]\n", tipo_de_conta) != EOF) {
        fscanf(arquivo, "Agência: %[^\n]\n", conta.agencia);
        fscanf(arquivo, "Número da Conta: %[^\n]\n", conta.numero_da_conta);
        fscanf(arquivo, "Nome do Cliente: %[^\n]\n", conta.nome_do_cliente);
        fscanf(arquivo, "Data de Nascimento: %[^\n]\n", conta.data_de_nascimento);
        fscanf(arquivo, "Telefone de Contato: %[^\n]\n", conta.telefone_de_contato);
        fscanf(arquivo, "CPF do Cliente: %[^\n]\n", conta.cpf_do_cliente);
        fscanf(arquivo, "Endereço do Cliente: %[^\n]\n", conta.endereco_do_cliente);
        fscanf(arquivo, "CEP do Cliente: %[^\n]\n", conta.cep);
        fscanf(arquivo, "Local do Cliente: %[^\n]\n", conta.local);
        fscanf(arquivo, "Número da Casa: %[^\n]\n", conta.numero_da_casa);
        fscanf(arquivo, "Bairro: %[^\n]\n", conta.bairro);
        fscanf(arquivo, "Cidade: %[^\n]\n", conta.cidade);
        fscanf(arquivo, "Estado: %[^\n]\n", conta.estado);
        fscanf(arquivo, "Senha do Cliente: %[^\n]\n", conta.senha_do_cliente);
        if (strcmp(tipo_de_conta, "Corrente") == 0) {
            fscanf(arquivo, "Limite da Conta: %f\n", &conta.limite_da_conta);
            fscanf(arquivo, "Data de Vencimento: %[^\n]\n", conta.data_de_vencimento);
        }

        if (strcmp(conta.senha_do_cliente, senha_cliente) == 0) {
            senha_correta = 1;
            break;
        }
    }

    fclose(arquivo);

    if (senha_correta) {
        FILE *arquivo_extrato = fopen("extrato.txt", "r");
        if (arquivo_extrato == NULL) {
            printf("Erro ao abrir o arquivo de extrato!\n");
            return;
        }

        char linha[100];
        printf("\n=========== Extrato Bancário ===========\n");
        while (fgets(linha, sizeof(linha), arquivo_extrato) != NULL) {
            printf("%s", linha);
        }
        fclose(arquivo_extrato);
    } else {
        printf("Senha incorreta. Acesso negado.\n");
    }
}

void consultar_limite() {
    FILE *arquivo;
    Conta conta;
    char senha_cliente[20];
    char tipo_de_conta[20];
    int senha_correta = 0;

    printf("Digite a senha do cliente: ");
    scanf("%s", senha_cliente);

    arquivo = fopen("contas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    while (fscanf(arquivo, "Tipo de Conta: %[^\n]\n", tipo_de_conta) != EOF) {
        fscanf(arquivo, "Agência: %[^\n]\n", conta.agencia);
        fscanf(arquivo, "Número da Conta: %[^\n]\n", conta.numero_da_conta);
        fscanf(arquivo, "Nome do Cliente: %[^\n]\n", conta.nome_do_cliente);
        fscanf(arquivo, "Data de Nascimento: %[^\n]\n", conta.data_de_nascimento);
        fscanf(arquivo, "Telefone de Contato: %[^\n]\n", conta.telefone_de_contato);
        fscanf(arquivo, "CPF do Cliente: %[^\n]\n", conta.cpf_do_cliente);
        fscanf(arquivo, "Endereço do Cliente: %[^\n]\n", conta.endereco_do_cliente);
        fscanf(arquivo, "CEP do Cliente: %[^\n]\n", conta.cep);
        fscanf(arquivo, "Local do Cliente: %[^\n]\n", conta.local);
        fscanf(arquivo, "Número da Casa: %[^\n]\n", conta.numero_da_casa);
        fscanf(arquivo, "Bairro: %[^\n]\n", conta.bairro);
        fscanf(arquivo, "Cidade: %[^\n]\n", conta.cidade);
        fscanf(arquivo, "Estado: %[^\n]\n", conta.estado);
        fscanf(arquivo, "Senha do Cliente: %[^\n]\n", conta.senha_do_cliente);
        if (strcmp(tipo_de_conta, "Corrente") == 0) {
            fscanf(arquivo, "Limite da Conta: %f\n", &conta.limite_da_conta);
            fscanf(arquivo, "Data de Vencimento: %[^\n]\n", conta.data_de_vencimento);
        }

        if (strcmp(conta.senha_do_cliente, senha_cliente) == 0) {
            senha_correta = 1;
            break;
        }
    }

    fclose(arquivo);

    if (senha_correta) {
        if (strcmp(tipo_de_conta, "Corrente") == 0) {
            printf("Seu limite da conta é: R$ %.2f\n", conta.limite_da_conta);
            printf("Data de vencimento: %s\n", conta.data_de_vencimento);
        } else {
            printf("Sua conta não é corrente e não possui limite de crédito.\n");
        }
    } else {
        printf("Senha incorreta. Acesso negado.\n");
    }
}

void menuCliente() {
    int opcao;

    do {
        printf("\n================ Menu do Cliente ================\n");
        printf("1 - Consultar saldo\n");
        printf("2 - Fazer depósito\n");
        printf("3 - Fazer saque\n");
        printf("4 - Mostrar extrato\n");
        printf("5 - Consultar limite\n");
        printf("6 - Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                saldo();
                break;
            case 2:
                depositar();
                break;
            case 3:
                sacar();
                break;
            case 4:
                mostrar_extrato();
                break;
            case 5:
                consultar_limite();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 6);
}

void menuPrincipal() {
    int opcao;
    do {
        printf("\n================ Menu Principal ================\n");
        printf("1 - Menu do Funcionário\n");
        printf("2 - Menu do Cliente\n");
        printf("3 - Sair\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcao);
        getchar(); // Consumir o newline deixado por scanf

        switch (opcao) {
            case 1:
                menuFuncionario();
                break;
            case 2:
                menuCliente();
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 3);
}

