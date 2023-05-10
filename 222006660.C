#include "222006660.h"

int main(){
    int option;
    char cpf[TAM_CPF];
    char nome[TAM_NOME];
    char buff_nome[TAM_NOME];
    char sexo;
    char cidade[TAM_NOME];
    char uf[TAM_UF];
    int dia, mes, ano;
    char sair_consulta;

    while (true)
    {
        //MENU DE OPCOES
        menu();
        printf("ESCOLHA: ");
        scanf("%d", &option);
        limpaTELA();
        clear_buff();

        while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6) //VERIFICA SE A OPCAO DIGITADA E VALIDA
        {
            printf("Escolha INVALIDA\n\n");
            pausaTELA();
            limpaTELA();
            menu();
            printf("ESCOLHA: ");
            scanf("%d", &option);
            limpaTELA();
            clear_buff();
        }
        
        if (option == 1){ // CADASTRO DE PESSOAS
            while(true){
                menu_opcao1();
                printf("CPF [XXX.XXX.XXX-XX]: ");
                scanf("%s", cpf);
                // VERIFICA E CADASTRA CPF
                while (validaCPF(cpf) == 0){
                    printf("CPF INVALIDO, TENTE NOVAMENTE\n\n");
                    printf("CPF [XXX.XXX.XXX-XX]: ");
                    scanf("%s", cpf);
                }
                if(verificaCPF(cpf) == 1){ // VERIFICA SE JA FOI CADASTRADO NO ARQUIVO
                    printf("\nESSE CPF JA FOI CADASTRADO!\n");
                    printf("VOLTANTO AO MENU INICIAL...\n");
                    pausaTELA();
                    limpaTELA();
                    break;
                }
                printf("CPF CADASTRADO COM SUCESSO!\n");
                pausaTELA();
                limpaTELA();

                // VALIDA E CADASTRA NOME
                menu_opcao1();
                printf("NOME: ");
                scanf(" %[^\n]s", nome);
                while(validaNOME(nome) == 0){
                    printf("NOME INVALIDO, TENTE NOVAMENTE\n");
                    printf("NOME: ");
                    scanf(" %[^\n]s", nome);
                }
                printf("NOME: %s FOI CADASTRADO COM SUCESSO!\n", nome);
                pausaTELA();
                limpaTELA();
                strcpy(buff_nome, nome);

                //VALIDA E CADASTRA SEXO
                menu_opcao1();
                printf("SEXO [M/F]: ");
                scanf("%s", &sexo);
                while(validaSEXO(sexo) == 0){
                    printf("SEXO INVALIDO, TENTE NOVAMENTE\n");
                    printf("SEXO [M/F]: ");
                    scanf("%s", &sexo);
                }
                printf("SEXO FOI CADASTRADO COM SUCESSO!\n");
                pausaTELA();
                limpaTELA();

                //VALIDA E CADASTRA DATA DE NASCIMENTO
                menu_opcao1();
                printf("DATA DE NASCIMENTO [dd/mm/aaaa]: ");
                scanf(" %d/%d/%d", &dia, &mes, &ano);
                clear_buff();
                while(validaDATA(dia, mes, ano) == 0){
                    printf("DATA INVALIDA. TENTE NOVAMENTE!\n");
                    printf("DATA DE NASCIMENTO [dd/mm/aaaa]: ");
                    scanf(" %d/%d/%d", &dia, &mes, &ano);
                    clear_buff();
                }
                printf("DATA DE NASCIMENTO CADASTRADA COM SUCESSO!\n");
                pausaTELA();
                limpaTELA();

                //VALIDA E CADASTRA CIDADE E UF
                menu_opcao1();
                printf("AVISO: CIDADE COM A PRIMEIRA LETRA MAIUSCULA E SEM ACENTO!\n");
                printf("AVISO: UF COM LETRAS MAISUCULAS!\n\n");
                printf("CIDADE: ");
                scanf("%[^\n]s", cidade);
                printf("UF: ");
                scanf("%s", uf);
                clear_buff();
                while(validaCIDADE(cidade, uf) == 0){
                    printf("CIDADE INVALIDA. TENTE NOVAMENTE!\n\n");
                    printf("CIDADE: ");
                    scanf("%[^\n]s", cidade);
                    printf("UF: ");
                    scanf("%s", uf);
                    clear_buff();
                }
                printf("CIDADE E UF CADASTRADA COM SUCESSO!\n");
                salvaARQUIVO(cpf, nome, sexo, dia, mes, ano, cidade, uf); // FUNCAO QUE SALVA TUDO NO ARQUIVO
                pausaTELA();
                limpaTELA();
                break;

            }
        }

        else if (option == 2){ // CONSULTA PESSOAS POR CPF
            //RECEBE O CPF DESEJADO A SER PROCURADO
            menu_opcao2(); // menu da opcao 2
            printf("CPF: ");
            scanf("%s", cpf);
            //VERIFICA SE O CPF E VALIDO
            while (validaCPF(cpf) == 0){
                printf("CPF INVALIDO, TENTE NOVAMENTE\n\n");
                printf("CPF [XXX.XXX.XXX-XX]: ");
                scanf("%s", cpf);
            }
            //PROCURA NO ARQUIVO
            if(verificaCPF(cpf) == 0){
                printf("CPF NAO ENCONTRADO NO SISTEMA!\n");
                printf("VOLTANDO AO MENU...\n\n");
                pausaTELA();
                limpaTELA();
            }
            else{
                //ESCREVE OS DADOS DO CPF ESCOLHIDO
                while(true){
                    clear_buff();
                    consultaCPF(cpf);
                    printf("\n\nDIGITE UMA LETRA PARA SAIR: ");
                    scanf("%c", &sair_consulta);
                    if(sair_consulta == 'S' || sair_consulta == 's'){ //DEIXA A MENSAGEM NA TELA ATE O USUARIO DIGITAR ALGO PARA VOLTAR AO MENU
                        limpaTELA();
                        break;
                    }
                    else{
                        limpaTELA();
                        break;
                    }
                }
            }
        }

        else if (option == 3){ // LISTA NOME POR CIDADE
            menu_opcao3(); // menu da opcao 3
            printf("CIDADE: ");
            scanf("%[^\n]s", cidade);
            printf("UF: ");
            scanf("%s", uf);
            clear_buff();
            while(validaCIDADE(cidade, uf) == 0){
                printf("CIDADE INVALIDA. TENTE NOVAMENTE!\n\n");
                printf("CIDADE: ");
                scanf("%[^\n]s", cidade);
                printf("UF: ");
                scanf("%s", uf);
                clear_buff();
            }
            limpaTELA();
            while(true){
                if(verificaCIDADE(cidade) == 0){ // VERIFICA SE A CIDADE ESTA CADASTRADA NO ARQUIVO
                    printf("NAO HA PESSOAS CADASTRADAS NA CIDADE!\n");
                    printf("VOLTANDO AO MENU...");
                    pausaTELA();
                    limpaTELA();
                    break;
                }
                else{
                    // ESCREVE OS NOMES
                    listaCIDADE(cidade, uf);
                    printf("\n\nDIGITE UMA LETRA PARA SAIR: "); //DEIXA A MENSAGEM NA TELA ATE O USUARIO DIGITAR ALGO PARA VOLTAR AO MENU
                    scanf("%c", &sair_consulta);
                    if(sair_consulta == 'S' || sair_consulta == 's'){
                        limpaTELA();
                        break;
                    }
                    else{
                        limpaTELA();
                        break;
                    }
                }
            }
        }

        else if (option == 4){ // GERAR RELATORIO
            relatorio(); // VOID QUE GERA O RELATORIO
        }

        else if (option == 5){ // APAGAR CADASTRO
            menu_opcao5();
            printf("CPF: ");
            scanf("%s", cpf);

            while(validaCPF(cpf) == 0){ // LOOP ATE O USUARIO DIGITAR UM CPF VALIDO
                printf("CPF INVALIDO, TENTE NOVAMENTE\n\n");
                printf("CPF: ");
                scanf("%s", cpf);
            }
            apagaPESSOA(cpf); // FUNCAO PARA APAGAR A PESSOA SE EXISTIR NO ARQUIVO E SE NAO TIVER RETORNA QUE NAO ESTAVA CADASTRADA!
        }

        else if (option == 6){ // FECHA O PROGRAMA
            menu_opcao6();
            break;
        }

        limpaDISCO(); // SE O ARQUIVO ESTIVER VAZIO ELE APAGA PARA NAO OCUPAR ESPACO
    }

    return 0;
    
}
