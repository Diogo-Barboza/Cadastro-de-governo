#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

#define TAM_CPF 15
#define TAM_NOME 50
#define TAM_DATA 11
#define TAM_UF 3
#define TAM_LINHA 90
#define TAM_S 5

void clear_buff(){ // FUNCAO LIMPA BUFFER
    int ch;
    do{
        ch = fgetc(stdin);

    } while(ch != EOF && ch != '\n');
}

void menu(){ // INTERFACE DO MENU PRINCIPAL
    printf("===============================================\n\n");
    printf("  Sistema de Gestao de Beneficio Social (SGBS) \n\n");
    printf("===============================================\n\n");
    printf("                Menu de Opcoes\n\n");
    printf("        [1] Cadastrar pessoa\n");
    printf("        [2] Consultar pessoa\n");
    printf("        [3] Listar pessoas por cidade\n");
    printf("        [4] Gerar relatorio\n");
    printf("        [5] Excluir pessoa\n");
    printf("        [6] Encerrar programa\n\n");
    printf("===============================================\n\n");

}

void menu_opcao3(){ // INTERFACE DA OPCAO 3
    printf("======== LISTAR NOMES POR CIDADE ========\n");
    printf("   CIDADE COM PRIMEIRA LETRA MAIUSCULA\n");
    printf("               E SEM ACENTOS              \n");
    printf("       UF COM LETRAS MAIUSCULAS\n");
    printf("=========================================\n\n");

}

void menu_opcao2(){ // INTERFACE DA OPCAO 2
    printf("============ CONSULTA POR CPF ============\n");
    printf("     MODELO DE CPF: [XXX.XXX.XXX-XX] \n");
    printf("==========================================\n\n");
}

void menu_opcao5(){ // INTERFACE DA OPCAO 5
    printf("============= APAGAR CADASTRO =============\n");
    printf("     MODELO DE CPF: [XXX.XXX.XXX-XX] \n");
    printf("===========================================\n\n");
}

void menu_opcao1(){ // INTERFACE DA OPCAO 1
    printf("============== CADASTRO DE PESSOAS ==============\n\n");
    printf("  Sistema de Gestao de Beneficio Social (SGBS) \n\n");
    printf("=================================================\n\n");
}

void pausaTELA(){ // PAUSA A TELA POR 1,25 SEGUNDOS
    Sleep(1250);
}

void limpaTELA(){ //LIMPA A TELA
    system("cls");
}

void menu_opcao6(){ // INTERFACE DA OPCAO 6
    printf("=================================================\n\n");
    printf("  Sistema de Gestao de Beneficio Social (SGBS) \n\n");
    printf("      OBRIGADO POR USAR NOSSOS SERVICOS.\n");
    printf("                 ATE BREVE!\n\n");
    printf("       PROGRAMA FINALIZADO COM SUCESSO\n");
    printf("=================================================\n\n");

    pausaTELA();
    limpaTELA();
}

void consultaCPF(char x[]){ // Consulta o cpf (OPCAO 2) E PRINTA AS INFORMACOES
    FILE *cadastro = fopen("CADASTRO.txt", "r");

    char cidade[TAM_NOME];
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char uf[TAM_UF];
    int dia, mes, ano;
    char sexo[TAM_S];

    if(cadastro != NULL){
        fseek(cadastro, 0, SEEK_SET);
        while(!feof(cadastro)){
            fscanf(cadastro, "%[^\n]\n%[^\n]\n%[^\n]\n%d/%d/%d\n%[^\n]\n%[^\n]\n", cpf, nome, sexo, &dia, &mes, &ano, cidade, uf);
            if(strcmp(cpf, x) == 0){
                printf("\nCPF: %s\nNOME: %s\nSEXO: %s\nDATA DE NASCIMENTO: %.02d/%.02d/%.04d\nCIDADE/UF: %s-%s\n", cpf, nome, sexo, dia, mes, ano, cidade, uf);
            }
        }
    }
    else{
        printf("Erro: AO ABRIR O ARQUIVO!");
    }

    fclose(cadastro);

}

void listaCIDADE(char x[], char y[]){ // LISTA NOMES POR CIDADE

    char cidade[TAM_NOME];
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char uf[TAM_UF];
    int dia, mes, ano;
    char sexo[TAM_S];
    int quantidade_nomes = 0;
    char NOMES_SALVOS[TAM_NOME][TAM_NOME];
    char aux[TAM_NOME];

    int i = 0, j = 0;
 
    FILE *cadastro = fopen("CADASTRO.txt", "r");

    fseek(cadastro, 0, SEEK_SET);

    if(cadastro != NULL){
        while(!feof(cadastro)){
            fscanf(cadastro, "%[^\n]\n%[^\n]\n%[^\n]\n%d/%d/%d\n%[^\n]\n%[^\n]\n", cpf, nome, sexo, &dia, &mes, &ano, cidade, uf);
            if(strcmp(cidade, x) == 0){
                strcpy(NOMES_SALVOS[quantidade_nomes], nome);
                quantidade_nomes++;
            }
        }
        for (i = 0; i < quantidade_nomes; i++){
            for (j = i + 1; j < quantidade_nomes; j++){
                if(strcmp(NOMES_SALVOS[i], NOMES_SALVOS[j]) > 0){
                    strcpy(aux, NOMES_SALVOS[i]);
                    strcpy(NOMES_SALVOS[i], NOMES_SALVOS[j]);
                    strcpy(NOMES_SALVOS[j], aux);
                }
            }
        }
    }

    printf("================= %s-%s =================\n", x, y);
    for(i = 0; i < quantidade_nomes; i++){
        printf("    - %s\n", NOMES_SALVOS[i]);
    }

    fclose(cadastro);

}

int verificaCIDADE(char x[]){ // VERIFICA SE TEM A CIDADE ESCOLHIDA NO ARQUIVO

    char cidade[TAM_NOME];
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char uf[TAM_UF];
    int dia, mes, ano;
    char sexo[TAM_S];
    int achado = 0;
    
 
    FILE *cadastro = fopen("CADASTRO.txt", "r");

    fseek(cadastro, 0, SEEK_SET);

    if(cadastro != NULL){
        while(!feof(cadastro)){
            fscanf(cadastro, "%[^\n]\n%[^\n]\n%[^\n]\n%d/%d/%d\n%[^\n]\n%[^\n]\n", cpf, nome, sexo, &dia, &mes, &ano, cidade, uf);
            if(strcmp(cidade, x) == 0){
                achado = 1;
            }
        }
    }
    if(!achado){
        achado = 0;
    }
    return achado;
}

void salvaARQUIVO(char cpf[], char nome[], char sexo, int dia, int mes, int ano, char cidade[], char uf[]){ // CRIA UM ARQUIVO E SALVA TODOS OS DADOS NELE
    FILE *cadastro = fopen("CADASTRO.txt", "a+");

    fseek(cadastro, 0, SEEK_END);
    fprintf(cadastro, "%s\n%s\n%c\n%.02d/%.02d/%.04d\n%s\n%s\n\n", cpf, nome, toupper(sexo), dia, mes, ano, cidade, uf);
    fclose(cadastro);

}

int verificaCPF(char x[]){ // VERIFICA SE JA FOI CADASTRADO O CPF NO ARQUIVO
    FILE *cadastro = fopen("CADASTRO.txt", "a+");

    char linha[TAM_LINHA];
    int achado = 0;

    if(cadastro != NULL){
        while(fgets(linha, TAM_CPF, cadastro) != NULL){
            if(strstr(linha, x) != NULL){
                achado = 1;
            }
        }
        fseek(cadastro, 0, SEEK_SET);
        fclose(cadastro);
    }
    if(!achado){
        fseek(cadastro, 0, SEEK_SET);
        fclose(cadastro);
        achado = 0;
    }
    return achado;
}

int validaCPF(char x[]){ //VERIFICA SE O CPF E VALIDO OU INVALIDO
    int num, cont, resultado, soma = 0;
    char digito12, digito13;

    // VERIFICA ESTRUTURA
    if(!(x[0] >= '0' && x[0] <= '9' && x[1] >= '0' && x[1] <= '9' && x[2] >= '0' && x[2] <= '9' && x[3] =='.' && x[4] >= '0' && x[4] <= '9' && x[5] >= '0' && x[5] <= '9' && x[6] >= '0' && x[6] <= '9' && x[7] == '.' && x[8] >= '0' && x[8] <= '9' && x[9] >= '0' && x[9] <= '9' && x[10] >= '0' && x[10] <= '9' && x[11] == '-' && x[12] >= '0' && x[12]<= '9' && x[13] >= '0' && x[13] <= '9' && strlen(x) == 14)){
        return 0; 
    }
    //TIRA NUMEROS IGUAIS
    else if(x[0] == x[1] && x[1] == x[2] && x[2] == x[4] && x[4] == x[5] && x[5] == x[6] && x[6] == x[8] && x[8] == x[9] && x[9] == x[12] && x[12] == x[13] && x[13] == x[0]){ 
        return 0;
    }
    else{
        //PRIMEIRA VALIDACAO
        for(cont = 0; cont <= 2; cont++){ 
            num = x[cont] - 48;
            soma = soma + (num * (10 - cont));
        }
        for(cont = 4; cont <= 6; cont++){
            num = x[cont] - 48;
            soma = soma + (num * (11 - cont));
        }
        for(cont = 8; cont <= 10; cont++){
            num = x[cont] - 48;
            soma = soma + (num * (12 - cont));
        }
        resultado = 11 - (soma % 11);
        if ((resultado == 10) || (resultado == 11))
        {
            digito12 = '0';
        }
        else
        {
            digito12 = resultado + 48;
        }

        // SEGUNDA VALIDACAO
        soma = 0;
        resultado = 0;

        for(cont = 0; cont <= 2; cont++){ 
            num = x[cont] - 48;
            soma = soma + (num * (11 - cont));
        }
        for(cont = 4; cont <= 6; cont ++){
            num = x[cont] - 48;
            soma = soma + (num * (12 - cont));
        }
        for(cont = 8; cont <= 10; cont++){
            num = x[cont] - 48;
            soma = soma + (num * (13 - cont));
        }
        num = x[12] - 48;
        soma = soma + (num * 2);
        resultado = 11 - (soma % 11);
        if ((resultado == 10) || (resultado == 11))
        {
            digito13 = '0';
        }
        else
        {
            digito13 = resultado + 48;
        }

        // RETORNA VALIDO = 1 OU NAO VALIDO == 0
        if ((digito12 == x[12] && digito13 == x[13])) 
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int validaNOME(char x[]){ //VERIFICA SE O NOME E MAIOR QUE 1 LETRA
    if(strlen(x) == 1){
        return 0;
    }
    else{
        return 1;
    }
}

int validaSEXO(char x){ //VERIFICA SE O SEXO ESTA EM (M/F)
    if(!(x == 'M' || x == 'F' || x == 'm' || x == 'f')){
        return 0;
    }
    else{
        return 1;
    }
}

int validaDATA(int dia, int mes, int ano){ //VALIDA DATA
    if(dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && ano >= 0){
        if(((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) && ano > 0 && dia <= 29 && mes == 2){
            return 1;
        }
        else if(mes == 2 && dia <= 28){
            return 1;
        }
        else if((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) && dia <= 31){
            return 1;
        }
        else if((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia <= 30){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

int validaCIDADE(char cidade[], char uf[]){ //VERIFICA SE A CIDADE EXISTE NO ARQUIVO DISPONIBILIZADO PELO PROFESSOR

    int retorna = 0;
    int cod_municipio;
    char UF[TAM_UF];
    char linha[TAM_LINHA];
    char cidade_acento[TAM_LINHA];
    char CIDADE[TAM_LINHA];

    FILE *municipio = fopen("Municipios-Brasil.csv", "r");

    if(municipio == NULL){
        printf("Erro : AO ABRIR O ARQUIVO!");
    }
    else{
        fgets(linha, TAM_LINHA, municipio);
        while(!feof(municipio)){
            fscanf(municipio, "%d;%[^;];%[^;];%[^\n]\n", &cod_municipio, UF, cidade_acento, CIDADE);
            if(strcmp(cidade, CIDADE) == 0 && strcmp(uf, UF) == 0){
                retorna = 1;
                break;
            }
        }
    }

    fseek(municipio, 0, SEEK_SET);
    fclose(municipio);

    return retorna;
}

void apagaPESSOA(char x[]){ // APAGA PESSOA DO ARQUIVO

    char cidade[TAM_NOME];
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char uf[TAM_UF];
    int dia, mes, ano;
    char sexo;
    char apagar;

    FILE *cadastro = fopen("CADASTRO.txt", "r");
    rewind(cadastro);
    if(verificaCPF(x) == 1){ // VERIFICA SE O CPF ESTA NO ARQUIVO 
        consultaCPF(x); // SE JA FOI CADASTRADO MOSTRA OS DADOS E CONFIRMA SE QUER APAGAR
        clear_buff();
        printf("\nDESEJA APAGAR PESSOA [S/N]: "); //CONFIRMACAO PARA APAGAR
        scanf("%c", &apagar);
        while(apagar != 'S' && apagar != 's' && apagar != 'N' && apagar != 'n'){ //SE NAO FOR DIGITADO SIM OU NAO ELE ENTRA EM LOOP ATE SER VALIDO
        clear_buff();
        printf("ESCOLHA INVALIDA. USE (S) PARA SIM E (N) PARA NAO!\n");
        printf("\nDESEJA APAGAR PESSOA [S/N]: ");
        scanf("%c", &apagar);
        clear_buff();
        }
    }
    if(apagar == 'S' || apagar == 's'){ // SE FOR SIM, ELE CRIA OUTRO ARQUIVO COM COM TODOS OS DADOS MENOS O QUE FOI PEDIDO PRA APAGAR
        FILE *CADASTRONOVO = fopen("CADASTRONOVO.txt", "w");
        rewind(CADASTRONOVO);
        if(cadastro != NULL){
            while(!feof(cadastro)){
                fscanf(cadastro, "%[^\n]\n%[^\n]\n%[^\n]\n%d/%d/%d\n%[^\n]\n%[^\n]\n", cpf, nome, &sexo, &dia, &mes, &ano, cidade, uf);
                if(strcmp(cpf, x) != 0){
                    fprintf(CADASTRONOVO, "%s\n%s\n%c\n%.02d/%.02d/%.04d\n%s\n%s\n\n", cpf, nome, sexo, dia, mes, ano, cidade, uf);
                }
            }
            fclose(cadastro);
            fclose(CADASTRONOVO);
        }
        else{
            printf("Erro: AO ABRIR O ARQUIVO!");
        }

        remove("CADASTRO.txt"); // APAGA O ARQUIVO ANTIGO
        rename("CADASTRONOVO.txt", "CADASTRO.txt"); //RENOMEIA O ARQUIVO COM O MESMO NOME DO ANTIGO
        printf("\nPESSOA APAGADA COM SUCESSO!\n\n");

    }
    else if(apagar == 'N' || apagar == 'n'){ // SE FOR NAO ELE NAO APAGA E VOLTA AO MENU
        printf("\nPESSOA NAO APAGADA!\nVOLTANDO AO MENU!\n\n");
    }
    else{ // SE O CPF NAO FOI CADASTRADO NO ARQUIVO MOSTRA AO USUARIO QUE NAO FOI CADASTRADO ESSE CPF
        printf("\nPESSOA NAO CADASTRADA NO BANCO DE DADOS!\nVOLTANDO AO MENU...\n\n");
    }
    pausaTELA();
    limpaTELA();
    
    //VERIFICA SE TODOS OS CADASTRO FORAM APAGADOS DO ARQUIVO - SE SIM APAGA O ARQUIVO
    cadastro = fopen("CADASTRO.txt", "r");

    int contador = 0;
    char linha[TAM_LINHA];

    while(fgets(linha, TAM_CPF, cadastro) != NULL){
        contador++;
    }
    fclose(cadastro);
    if(contador == 0){
        remove("CADASTRO.txt");
    }
}

void relatorio(){ // CRIA RELATORIO OPCAO 4
    FILE *cadastro = fopen("CADASTRO.txt", "r");
    rewind(cadastro);

    struct tm *data;
    time_t segundos;
    time(&segundos);
    data = localtime(&segundos);

    int ano_atual = data->tm_year + 1900;
    int mes_atual = data->tm_mon + 1;
    int dia_atual = data->tm_mday;

    char cidade[TAM_NOME];
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char uf[TAM_UF];
    int dia, mes, ano;
    char sexo;
    char sair_consulta;

    int idade = 0;
    float pessoas_cadastradas = 0;
    int M = 0, F = 0;

    int ATE15 = 0; // CONTADOR DE PESSOAS DE 0 A 15 ANOS
    int ATE29 = 0; // CONTADOR DE PESSOAS DE 16 A 29 ANOS
    int ATE49 = 0; // CONTADOR DE PESSOAS DE 30 A 49 ANOS
    int ATE60 = 0; // CONTADOR DE PESSOAS DE 50 A 60 ANOS
    int MAIS60 = 0;// CONTADOR DE PESSOAS ACIMA DE 60 ANOS

    if(cadastro != NULL){
        while(!feof(cadastro)){
            fscanf(cadastro, "%[^\n]\n%[^\n]\n%[^\n]\n%d/%d/%d\n%[^\n]\n%[^\n]\n", cpf, nome, &sexo, &dia, &mes, &ano, cidade, uf);
            pessoas_cadastradas++;
            if(sexo == 'M'){ // SE FOR MASCULINO SOMA UM A CONTAGEM
                M++;
            }
            else if(sexo == 'F'){ // SE FOR FEMININO SOMA UM PRA CONTAGEM
                F++;
            }
            //CALCULA A IDADE 
            if(dia_atual >= dia && mes_atual >= mes){ // SE A DATA ATUAL FOR IGUAL OU DEPOIS DO ANIVERSARIO DELA IDADE E A SUBTRACAO DO ANO ATUAL COM O ANO DE NASCIMENTO
                idade = ano_atual - ano;
            }
            else{ // SE A DATA ATUAL FOR MENOR QUE O ANVIERSARIO, IDADE E IGUAL A SUBTRACAO DO ANO ATUAL COM O ANO DE NASCIMENTO MENOS UM
                idade = (ano_atual - ano) - 1;
            }
            //VAI SOMANDO QUANTIDADE DE PESSOAS POR IDADE
            if(idade >= 0 && idade <= 15){
                ATE15++;
            }
            if(idade >= 16 && idade <= 29){
                ATE29++;
            }
            if(idade >= 30 && idade <= 49){
                ATE49++;
            }
            if(idade >= 50 && idade <= 60){
                ATE60++;
            }
            if(idade > 60){
                MAIS60++;
            }            
        }

        fclose(cadastro);

        // VARIAVEIS DAS PORCENTAGENS E CALCULO DAS PORCENTAGENS DE IDADES
        float PORCENTO_ATE15 = (ATE15 * 100) / pessoas_cadastradas; 
        float PORCENTO_ATE29 = (ATE29 * 100) / pessoas_cadastradas;
        float PORCENTO_ATE49 = (ATE49 * 100) / pessoas_cadastradas;
        float PORCENTO_ATE60 = (ATE60 * 100) / pessoas_cadastradas;
        float PORCENTO_MAIS60 = (MAIS60 * 100) / pessoas_cadastradas;

        //VARIAVEIS PORCENTAGEM POR SEXO
        float PORCENTO_M = (M * 100) / pessoas_cadastradas;
        float PORCENTO_F = (F * 100) / pessoas_cadastradas;

        printf("============== RELATORIO DE PESSOAS ==============\n\n");
        printf("  Sistema de Gestao de Beneficio Social (SGBS) \n\n");
        printf("==================================================\n\n");

        printf("TOTAL DE PESSOAS BENEFICIADAS: %.0f\n", pessoas_cadastradas);
        printf("    0 a 15 anos...........: %.2f%%\n", PORCENTO_ATE15);
        printf("    16 a 29 anos..........: %.2f%%\n", PORCENTO_ATE29);
        printf("    30 a 49 anos..........: %.2f%%\n", PORCENTO_ATE49);
        printf("    50 a 60 anos..........: %.2f%%\n", PORCENTO_ATE60);
        printf("    Acima de 60 anos......: %.2f%%\n\n", PORCENTO_MAIS60);
        printf("Percentual de pessoas por sexo:\n");
        printf("    Masculino.............: %.2f%%\n", PORCENTO_M);
        printf("    Feminino..............: %.2f%%\n\n", PORCENTO_F);

        printf("==================================================\n\n");
        
        printf("DIGITE UMA LETRA PARA SAIR: ");
        scanf("%c", &sair_consulta);
        if(sair_consulta == 'S'){
            limpaTELA();
            return;
        }
        else{
            limpaTELA();
            return;
        }

    }
    else{
        printf("IMPOSSIVEL GERAR RELATORIO: NAO HA CADASTRO NO BANCO DE DADOS!");
        Sleep(2000);
        limpaTELA();
    }

}

void limpaDISCO(){
    FILE *cadastro = fopen("CADASTRO.txt", "r");

    int contador = 0;
    char linha[TAM_LINHA];

    while(fgets(linha, TAM_CPF, cadastro) != NULL){
        contador++;
    }
    fclose(cadastro);
    if(contador == 0){
        remove("CADASTRO.txt");
    }
}