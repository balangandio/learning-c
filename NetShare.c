#include <stdio.h>
#include <string.h>
#include <conio.c>

//Protótipos
void printfXY(char *str, int coluna, int linha, int limpaTela, int interrompeExecucao);
void leValidaTexto(char *titulo, char *texto, int tamanho, int minCaracteres, int coluna, int linha);
char leValidaChar(char *titulo, char *opcoes, int coluna, int linha);
void configuraRede(void);
void apresentaStatusRede(void);
void apresentaInterfaces(void);
void apresentaRedesDisponiveis(void);
void iniciaOuParaRede(void);

int main(void){
//Dlecarações
    char aux[30], opcaoMenu;
    int coluna = 23, linha = 3;
//Instruções
    do{
        printfXY("Nao se esquesa do admin!",coluna+3,linha+1,1,0);
        printfXY("1. Configurar rede hospedavel.",coluna,linha+3,0,0);
        printfXY("2. Status de rede configurada.",coluna,linha+4,0,0);
        printfXY("3. Iniciar/parar rede hospedada.",coluna,linha+5,0,0);
        printfXY("4. Mostar interfaces Wi-Fi.",coluna,linha+6,0,0);
        printfXY("5. Mostar redes ao alcance.",coluna,linha+7,0,0);
        printfXY("0. Encerrar programa.",coluna,linha+8,0,0);

        opcaoMenu = leValidaChar("Informe o desejado meu caro humano: ","123450",coluna-2,linha+10);
        switch(opcaoMenu){
            case '1': configuraRede(); break;
            case '2': apresentaStatusRede(); break;
            case '3': iniciaOuParaRede(); break; 
            case '4': apresentaInterfaces(); break;
            case '5': apresentaRedesDisponiveis();
        }
    }while(opcaoMenu != '0');
  return 0;
}

//Objetivo: configurar uma rede hospedável.
//Parâmetros: sem parâmetros.
//Retorno: sem retorno.
void configuraRede(void){
    char aux[100], senha[9], nome[21];

    leValidaTexto("Nome para a rede. Nulo para cancelar: ",nome,30,0,6,10);
    if (strlen(nome) > 0){

        leValidaTexto("Senha para a rede(8 carac). Nulo para cancelar: ", senha,9,0,10,10);
        if (strlen(senha) > 0){
            sprintf(aux,"netsh wlan set hostednetwork mode=allow ssid=%s key=%s", nome, senha);        

            system(aux);
            system("cls");
            system("netsh wlan show hostednetwork");//Mostra as informações da rede
            
            if(leValidaChar("Deseja iniciar a rede?(S/N)","sn",26,20) == 'S'){//Inicia a rede caso o usuário desejar
                printf("\n");
                system("netsh wlan start hostednetwork");        
                printf("\n%19s"," ");
                system("pause");
            }
        }
    }
}

//Objetivo: apresentar o estado da rede hospedada.
//Parâmetros: sem parâmetros.
//Retorno: sem retorno.
void apresentaStatusRede(void){
    system("cls");
    system("netsh wlan show hostednetwork");//Mostra as informações da rede
    printf("\n%19s"," ");
    system("pause");
}

//Objetivo: apresentar as interfaces Wi-Fi do sistema.
//Parâmetros: sem parâmetros.
//Retorno: sem retorno.
void apresentaInterfaces(void){
    system("cls");
    system("netsh wlan show interfaces");//Mostra as informações da rede
    printf("\n%19s"," ");
    system("pause");
}

//Objetivo: apresentar as rede sem fio al alcance.
//Parâmetros: sem parâmetros.
//Retorno: sem retorno.
void apresentaRedesDisponiveis(void){
    char aux[100], aux2[50];

    leValidaTexto("Infome a interface. Nulo para usar a padrao: ", aux2,50,0,20,10);
    if (strlen(aux2) > 0){
        sprintf(aux, "netsh wlan show networks interface=\"%s\"", aux2);
    }else{
        sprintf(aux, "netsh wlan show networks");
    }

    system("cls");
    system(aux);//Mostra as informações da rede
    printf("\n%19s"," ");
    system("pause");
}

//Objetivo: iniciar ou parar a rede hospedada.
//Parâmetros: sem parâmetros.
//Retorno: sem retorno.
void iniciaOuParaRede(void){
    char opcao, aux[100], intf[50];

    system("cls");
    if ((opcao = leValidaChar("Deseja parar(P) ou iniciar(I) a rede. C para cancelar: ","pic",13,10)) == 'I'){

        leValidaTexto("Interface. Nulo para usar a padrao: ",intf,50,0,20,10);
        if (strlen(intf) > 0){
            sprintf(aux, "netsh wlan start hostednetwork interface=%s",intf);
        }else{
            sprintf(aux, "netsh wlan start hostednetwork");
        }
        system(aux);
    }else{
        if (opcao == 'P') system("netsh wlan stop hostednetwork");
    }
}

//Objetivo: ler e validar um texto.
//Parâmetros: endereço inicial da instrução de entrada e do armazenamento; tamanho do armazenamento;
//            qtd. mínima de caracteres; coluna e linha da instrução.
//Retorno: sem retorno.
void leValidaTexto(char *titulo, char *texto, int tamanho, int minCaracteres, int coluna, int linha){
    int cont, tamTexto, flag = 0;
    char tituloCopia[200]; strcpy(tituloCopia, titulo);

    system("cls");
    do{
        printfXY(tituloCopia,coluna,linha,1,0);
        fflush(stdin);
        fgets(texto, tamanho, stdin);
        if (texto[strlen(texto)-1] == '\n')
            texto[strlen(texto)-1] = '\0';
        tamTexto = strlen(texto);
        for (flag = cont = 0; cont < tamTexto; ++cont) 
            if (*(texto+cont) == ' ') ++flag;
        if (tamTexto < minCaracteres || (flag == tamTexto && tamTexto > 0)){
            printfXY("",coluna,linha+1,1,0);    
            printf("Nulo ou curto. ");
            strcpy(tituloCopia,">>Informe novamente: ");
        }
    }while(tamTexto < minCaracteres || (flag == tamTexto && tamTexto > 0));
    fflush(stdin);
}

//Objetivo: apresentar um string sob coordenada.
//Parãmetros: endereço inicial da string; coluna e linha de apresentação; opção de limpeza da tela e de interrupção(0/1).
//Retorno: sem retorno.
void printfXY(char *str, int coluna, int linha, int limpaTela, int interrompeExecucao){
    if (limpaTela == 1) system("cls");
    gotoxy(coluna, linha);
    printf(str);
    if (interrompeExecucao == 1){
        gotoxy(coluna, linha+2);
        system("pause");
    }
}

//Objetivo: ler e validar um caracter.
//Parâmetros: endereço incial da string com a instrução de entrada e das opções válidas de escolha; coluna e linha da instrução.
//Retorno: opção válida.
char leValidaChar(char *titulo, char *opcoes, int coluna, int linha){
    int cont, flag;
    char opcao;
    printfXY(titulo,coluna,linha,0,0);
    do{
        fflush(stdin);
        opcao = toupper(getch());
        for (flag = cont = 0; cont < strlen(opcoes); ++cont)
            if (opcao == toupper(opcoes[cont])) flag = 1;
    }while(flag != 1);
    fflush(stdin);
    return opcao;
}
