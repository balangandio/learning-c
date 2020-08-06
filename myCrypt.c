//Objetivo: embaralhar um arquivo texto mediante a uma determinada senha.
//Entrada: o patch do arquivo texto a ser embaralhado e uma senha de aux�lio.
//Sa�da: a novo arquivo com texto do informado embaralhado.
//Feito por... humanos...

#include <stdio.h>
#include <conio.c>
#include <string.h>
#define LINHA 20
#define COLUNA 40
#define TAM_PATCH_ARQ 100
#define TAM_MAX_SENHA 11
#define TAM_MIN_SENHA 5
#define TAM_ID_ARQ 9 //Atualiza no tamanho de string gravada

void leValidaTexto(char *titulo, char *texto, int tamanho, int minCaracteres, int coluna, int linha);
char leValidaChar(char *titulo, char *opcoes, int coluna, int linha);
void printfXY(char *texto, int coluna, int linha, int cor, int limparTela, int interromper);
int verificaPresencaArq(char *nomeArq);
int calculaQtdBytesArq(char *nomeArq);
void *obtemTodoArq(char *nomeArq, int qtdBytesArq);
void ordenaChar(char *v1, char *v2);
void embaralharArq(char *patchArq, char *senha);
void desembaralharArq(char *patchArq, char *senha);
int gravaArq(void *dados, char *patchArq, int qtdBytes);
void brutalForce(char *patchArq);
int desembalhaDadosMemoria(char *dadosArq, int qtdBytesArq, char *senha);

int main(int qtdArgs, char **args){
//Declara��es
    int cont, tamSenha, flagArq = 0, flagEncerrar = 0, coluna = COLUNA-35, linha = LINHA-8;
    char opcao, patchArq[TAM_PATCH_ARQ], senha[TAM_MAX_SENHA], auxTitulo[200];
//Instru��es
    if (qtdArgs < 3){//Caso n�o seja passados par�metros suficientes...
        sprintf(auxTitulo, ">>Informe o patch do arquivo. Nulo para encerrar: ");
        do {
            leValidaTexto(auxTitulo, patchArq, TAM_PATCH_ARQ, 0, coluna, linha);//Leitura e valida��o do patch do arquivo
            if (strlen(patchArq) > 0)
                if ((flagArq = verificaPresencaArq(patchArq)) == 0)
                    sprintf(auxTitulo, ">>Arquivo inacess�vel, informe novamente. Nulo para encerrar: ");
        }while(strlen(patchArq) > 0 && flagArq == 0);

        if (strlen(patchArq) > 0) {
            sprintf(auxTitulo, ">>Informe a senha, %d a %d caracteres. Nulo para encerrar: ", TAM_MIN_SENHA, TAM_MAX_SENHA-1);
            do {
                leValidaTexto(auxTitulo, senha, TAM_MAX_SENHA, 0, coluna, linha); //Leitura e valida��o da senha
                tamSenha = strlen(senha);
                if (tamSenha > 0 && (tamSenha < TAM_MIN_SENHA || tamSenha > TAM_MAX_SENHA-1))
                    sprintf(auxTitulo, ">>Inv�lida, informe novamente. %d a %d caracteres. Nulo para encerrar: ", TAM_MIN_SENHA, TAM_MAX_SENHA-1);
            }while(tamSenha > 0 && (tamSenha < TAM_MIN_SENHA || tamSenha > TAM_MAX_SENHA-1));
            if (!(tamSenha > 0)) flagEncerrar = 1;
        }else{
            flagEncerrar = 1;
        }   
    }else{
        strcpy(patchArq, args[1]);
        strcpy(senha, args[2]);
    }

    if (flagEncerrar != 1){
        sprintf(auxTitulo, "Arquivo: %s", patchArq);//Apresenta��o das informa��es e leitura da op��o de gerenciamento do arq.
        printfXY(auxTitulo, coluna, linha-1, 0, 1, 0);
        sprintf(auxTitulo, "Senha: %s", senha);
        printfXY(auxTitulo, coluna, linha, 0, 0, 0);
        if ((opcao = leValidaChar("Embaralhar(E), desembaralhar(D), brutal force(B) ou encerrar(Q)?", "edqb", coluna, linha+3)) != 'Q'){
            system("cls");
            if (opcao == 'E') {
                embaralharArq(patchArq, senha);
            }else{
                (opcao == 'D') ? desembaralharArq(patchArq, senha) : brutalForce(patchArq);
            }
        }
    }
  return 0;
}

//Objetivo: ler e validar um texto.
//Par�metros: endere�o inicial da instru��o de entrada e do armazenamento; tamanho do armazenamento;
//            qtd. m�nima de caracteres; coluna e linha da instru��o.
//Retorno: sem retorno.
void leValidaTexto(char *titulo, char *texto, int tamanho, int minCaracteres, int coluna, int linha){
    int cont, tamTexto, flag = 0;
    char tituloCopia[200]; strcpy(tituloCopia, titulo);

    system("cls");
    do{
        printfXY(tituloCopia,coluna,linha,0,0,0);
        fflush(stdin);
        fgets(texto, tamanho, stdin);
        if (texto[strlen(texto)-1] == '\n')
            texto[strlen(texto)-1] = '\0';
        tamTexto = strlen(texto);
        for (flag = cont = 0; cont < tamTexto; ++cont) 
            if (*(texto+cont) == ' ') ++flag;
        if (tamTexto < minCaracteres || (flag == tamTexto && tamTexto > 0)){
            printfXY("",coluna,linha+1,0,1,0);    
            printf("Nulo ou curto. ");
            strcpy(tituloCopia,">>Informe novamente: ");
        }
    }while(tamTexto < minCaracteres || (flag == tamTexto && tamTexto > 0));
    fflush(stdin);
}

//Objetivo: ler e validar um caracter.
//Par�metros: endere�o incial da string com a instru��o de entrada e das op��es v�lidas de escolha; coluna e linha da instru��o.
//Retorno: op��o v�lida.
char leValidaChar(char *titulo, char *opcoes, int coluna, int linha){
    int cont, flag;
    char opcao;
    printfXY(titulo,coluna,linha,0,0,0);
    do{
        fflush(stdin);
        opcao = toupper(getch());
        for (flag = cont = 0; cont < strlen(opcoes); ++cont)
            if (opcao == toupper(opcoes[cont])) flag = 1;
    }while(flag != 1);
    fflush(stdin);
    return opcao;
}

//Objetivo: imprimir uma mensagem em um coordenada.
//Par�metros: endere�o inicial da string a ser apresentada; coluna e linha da apresenta��o;
//           op��o para limpar a tela(0, mant�m; 1, limpa); op��o para interromper execu��o(0, n�o; 1, interromper);
//Retorno: sem retorno
void printfXY(char *texto, int coluna, int linha, int cor, int limparTela, int interromper){
    int cont, tamTexto = strlen(texto);
    char c, auxCor[10], *textoCopia;

    if (limparTela == 1) system("cls");
    sprintf(auxCor,"color 0%d", cor); system(auxCor);
    gotoxy(coluna, linha);
    if (strlen(texto) > 0){
        if ((textoCopia = (char *)malloc(tamTexto+1)) != NULL){
            strcpy(textoCopia, texto);
            for (cont = 0; cont < tamTexto; ++cont){
                c = textoCopia[cont];
                switch (c){
                    case '�': c = 136; break;
                    case '�': c = 130; break;
                    case '�': c = 160; break;
                    case '�': c = 133; break;
                    case '�': c = 131; break;
                    case '�': c = 135; break;
                    case '�': c = 198; break;
                    case '�': c = 167; break;
                    case '�': c = 161; break;
                    case '�': c = 163; break;
                    case '�': c = 162; break;
                    case '�': c = 228; break;
                    case '�': c = 166; break;
                    case '>': if(textoCopia[cont+1] == '>'){
                                 c = 175;
                                 textoCopia[cont+1] = ' ';
                              }
                }
                textoCopia[cont] = c;
            }       
            printf("%s", textoCopia);
            free(textoCopia);
        }else{
            printf("N%co foi poss�vel alocar os recursos necessarios.",198);
        }
    }
    if (interromper == 1){
        gotoxy(coluna,linha+3);
        system("pause");
    }
}

//Objetivo: verificar se um arq. est� acess�vel.
//Par�metros: endere�o inicial do nome do arquivo.
//Retorno: 0, arquivo inacess�vel; 1, arquivo acess�vel.
int verificaPresencaArq(char *nomeArq){
    FILE *arq;
    if ((arq = fopen(nomeArq, "r")) != NULL){
        fclose(arq);
        return 1;
    }
    return 0;
}

//Objetivo: obter a quantidade de bytes de um arq.
//Par�metros: endere�o inicial do nome do arq.
//Retorno: quantidade de bytes, -1 em caso de falha.
int calculaQtdBytesArq(char *nomeArq){
    int ret, coluna = 5, linha = 15;
    FILE *arq;

    if ((arq = fopen(nomeArq, "r")) != NULL){
        if (fseek(arq, 0, SEEK_END) == 0){ 
            if ((ret = ftell(arq)) != EOF){
                fclose(arq);
                return ret;
            }else{
                printfXY("N�o foi poss�vel posicionar-se no arquivo.", coluna, linha, 0, 1, 1);
            }
        }else{
            printfXY("N�o foi poss�vel posicionar-se no arquivo.", coluna, linha, 0, 1, 1);
        }
    }else{
        printfXY("Arquivo n�o pode ser aberto.", coluna, linha, 0, 1, 1);
    }
    return -1;
}

//Objetivo: obter todos os dados de um arq. para a mem�ria.
//Par�metros: endere�o inicial do nome do arq.; qtd. de bytes do arq.
//Retorno: endere�o inicial da posi��o onde est� o arq.; NULL em caso de falha
void *obtemTodoArq(char *nomeArq, int qtdBytesArq){
    int coluna = 5, linha = 10;
    FILE *arq;
    void *dados = NULL;

    if ((arq = fopen(nomeArq, "rb")) != NULL){
        if ((dados = malloc(qtdBytesArq)) != NULL){
            if (fread(dados, qtdBytesArq, 1, arq) == 1){
                fclose(arq);
                return dados;
            }else{
                printfXY("N�o foi poss�vel ler o arquivo.", coluna, linha, 0, 1, 1);                
            }
        }else{
            printfXY("N�o foi poss�vel reservar os recursos necess�rios.", coluna, linha, 0, 1, 1);
        }
    }else{
        printfXY("N�o foi poss�vel acessar o arquivo.", coluna, linha, 0, 1, 1);
    }
    return NULL;
}

//Objetivo: ordenar dois caracteres.
//Par�metros: endere�o das posi��es a serem trocadas.
//Retorno: sem retorno.
void ordenaChar(char *v1, char *v2){
    char auxOrdenacao;
    auxOrdenacao = *v1;
    *v1 = *v2;
    *v2 = auxOrdenacao;
}

//Objetivo: embaralhar arquivo.
//Par�metros: endere�o inicial do patch do arquivo; endere�o inicial da senha.
//Retorno: sem retorno.
void embaralharArq(char *patchArq, char *senha){
    long idArq = 0;
    char auxIdArq[30], *dadosArq, *pAux, *senhaCopia = senha;
    int aux, cont, contSenha = 1, caracterParaSubstituir, decimalCaracter, qtdBytesArq, tamSenha = strlen(senha), coluna = COLUNA, linha = LINHA;

    if ((qtdBytesArq = calculaQtdBytesArq(patchArq)) > 0) {//Obten��o da qtd. de bytes/caracteres do arq.
        if ((dadosArq = (char *)obtemTodoArq(patchArq, qtdBytesArq)) != NULL) { //Obten��o dos dados do arq. para mem�ria 

            if (qtdBytesArq > 1){
                for (cont = 0; cont < qtdBytesArq; ++cont) { //Para cada byte/caracter do arq.
                    decimalCaracter = *senhaCopia;//Obten��o do valor em decimal do caracter da senha(em ASCII)
                    idArq += decimalCaracter;

                    if (decimalCaracter + cont > qtdBytesArq){//Caso n�o haja posi��o apartir do contador no arq. para se trocar...
                        caracterParaSubstituir = decimalCaracter - (decimalCaracter/(qtdBytesArq-cont))*(qtdBytesArq-cont);//Obter posi��o a partir do in�cio do arq.
                    }else{
                        caracterParaSubstituir = decimalCaracter + cont;//Opter posi��o a partir do contador atual
                    }

                    ordenaChar(&dadosArq[caracterParaSubstituir], &dadosArq[cont]);//Troca de posi��o dos caracteres 

                    if (contSenha < tamSenha){//Regulador do contador da senha
                        contSenha++;//Indica o caracter sequencial da senha que est� sendo processado
                        senhaCopia++;//Aponta para o caracter que est� sendo processado
                    }else{
                        contSenha = 1;
                        senhaCopia = senha;
                    }
                }
            }
            sprintf(auxIdArq, "%09ld", idArq);
            if ((pAux = (char *)realloc(dadosArq, qtdBytesArq+strlen(auxIdArq))) != NULL) {//Reserva de espa�o para a ID do arq.
                dadosArq = pAux;
                for (cont = 0; cont < strlen(auxIdArq); ++cont)//Grava��o da ID do arquivo
                    dadosArq[qtdBytesArq+cont] = auxIdArq[cont];
                gravaArq((void *)dadosArq, patchArq, qtdBytesArq+strlen(auxIdArq));
            }else{
                printfXY("N�o foi poss�vel gerar os recursos necess�rios.", coluna, linha, 0, 1, 1);
            }
            free(dadosArq);
        }
    }else{
        if (qtdBytesArq != -1) printfXY("Arquivo vazio.", coluna, linha, 0, 1, 1);
    }
}

//Objetivo: desembaralhar arquivo.
//Par�metros: endere�o inicial do patch do arquivo; endere�o inicial da senha.
//Retorno: sem retorno.
void desembaralharArq(char *patchArq, char *senha){
    long idArqAux = 0;
    int tamIdArq = TAM_ID_ARQ;
    int caracterParaSubstituir, qtdBytesArq, decimalCaracter, cont, contSenha, tamSenha = strlen(senha), coluna = 5, linha = 15;
    char *senhaCopia, *dadosArq;

    if ((qtdBytesArq = calculaQtdBytesArq(patchArq)) > 0) {//Obten��o da qtd. de bytes/caracteres do arq.
        if ((dadosArq = (char *)obtemTodoArq(patchArq, qtdBytesArq)) != NULL) { //Obten��o dos dados do arq. para mem�ria 
            qtdBytesArq = qtdBytesArq - tamIdArq;//Tamanho do arq. sem sua ID
            if (qtdBytesArq > 1){
                contSenha = (qtdBytesArq%strlen(senha) != 0) ? qtdBytesArq%strlen(senha) : strlen(senha); //Obten��o do �ltimo caracter processado da senha
                senhaCopia = &senha[(qtdBytesArq%strlen(senha) != 0) ? qtdBytesArq%strlen(senha)-1 : strlen(senha)-1];
            
                for (cont = qtdBytesArq-1; cont >= 0; --cont) { //Para cada byte/caracter do arq.(do �ltimo byte ao primeiro)
                    decimalCaracter = *senhaCopia;
                    idArqAux += decimalCaracter;                

                    if (decimalCaracter + cont > qtdBytesArq){
                        caracterParaSubstituir = decimalCaracter - (decimalCaracter/(qtdBytesArq-cont))*(qtdBytesArq-cont);
                    }else{
                        caracterParaSubstituir = decimalCaracter + cont;
                    }
                
                    ordenaChar(&dadosArq[caracterParaSubstituir], &dadosArq[cont]);
                
                    if (contSenha > 1){
                        contSenha--;
                        senhaCopia--;
                    }else{
                        contSenha = tamSenha;
                        senhaCopia = &senha[strlen(senha)-1];
                    }
                }
            }
            gravaArq((void *)dadosArq, patchArq, qtdBytesArq);
            if (atoi(&dadosArq[qtdBytesArq+1]) != idArqAux) //Verifica��o se senha est� correta
                printfXY("Possivelmente a senha est� errada ou o arq. n�o estava embaralhado.",coluna,linha, 0, 1, 1);
            free(dadosArq);
        }
    }else{
        if (qtdBytesArq != -1) printfXY("Arquivo vazio.", coluna, linha, 0, 1, 1);
    }
}

//Objetivo: gravar um conte�do da mem�ria em um novo arquivo.
//Par�metros: endere�o inicial dos dados e serem gravados, e do patch do arquivo; quantidade de bytes a serem gravados.
//Retorno: 0, sem falhas; 1, falha.
int gravaArq(void *dados, char *patchArq, int qtdBytes){
    FILE *arq;
    int coluna = 5, linha = 15;

    strcat(patchArq, ".novo");
    if ((arq = fopen(patchArq, "wb")) != NULL){
        if (fwrite(dados, qtdBytes, 1, arq) == 1){
            gotoxy(coluna,linha);
            printf("Dados gravados em: %s\n\n",patchArq);
            gotoxy(coluna,linha+2);
            system("pause");
        }else{
            printfXY("N�o foi poss�vel gravar os dados no novo arquivo.", coluna, linha, 0, 1, 1);
        }
        fclose(arq);
    }else{
        printfXY("N�o foi poss�vel criar um novo arquivo para os dados.", coluna, linha, 0, 1, 1);
    }
}

//Objetivo: realizar um ataque brutal force por dicion�rio para obter a senha de um arquivo embaralhado.
//Par�metros: endere�o inicial do patch do arquivo.
//Retorno: sem retorno.
void brutalForce(char *patchArq){
    FILE *arqDict;
    int tamIdArq = TAM_ID_ARQ;
    int cont, id, idArq, qtdBytesArq, flag = 0, somaQtdTentativas = 0, flagArq = 0, coluna = COLUNA-35, linha = LINHA-10;
    char auxTitulo[100], dict[200], *dados, *dadosCopia, senhaDict[50];

    sprintf(auxTitulo, ">>Informe o patch do dicion�rio. Nulo para encerrar: ");
    do {
        leValidaTexto(auxTitulo, dict, TAM_PATCH_ARQ, 0, coluna, linha);//Leitura e valida��o do patch do arquivo
        if (strlen(dict) > 0)
            if ((flagArq = verificaPresencaArq(dict)) == 0)
                sprintf(auxTitulo, ">>Arquivo inacess�vel, informe novamente. Nulo para encerrar: ");
    }while(strlen(dict) > 0 && flagArq == 0);
    system("cls");

    if (strlen(dict) > 0) {
        if ((qtdBytesArq = calculaQtdBytesArq(patchArq)) > 0) {//Obten��o da qtd. de bytes/caracteres do arq.
            if ((dados = (char *)obtemTodoArq(patchArq, qtdBytesArq)) != NULL) { //Obten��o dos dados do arq. para mem�ria
                qtdBytesArq = qtdBytesArq - tamIdArq;//Tamanho do arq. sem sua ID
                idArq = atoi(&dados[qtdBytesArq+1]);
                if ((dadosCopia = (char *)malloc(qtdBytesArq)) != NULL) {//Espa�o para a c�pia dos dados

                    if ((arqDict = fopen(dict, "rt")) != NULL){
                        while(fgets(senhaDict, 20, arqDict) != NULL){//Para cada palavra do dicion�rio...
                            if (senhaDict[strlen(senhaDict)-1] == '\n' && strlen(senhaDict) > 1) senhaDict[strlen(senhaDict)-1] = '\0';
                            memcpy(dadosCopia, dados, qtdBytesArq);
                            id = desembalhaDadosMemoria(dadosCopia, qtdBytesArq, senhaDict);
                            somaQtdTentativas++;
                            if (idArq != id){ //Verifica��o se senha est� correta
                                gotoxy(5,15);
                                printf("Total = %d | Tentando senha: %s                                  ", somaQtdTentativas, senhaDict);
                            }else{
                                system("cls");
                                gotoxy(coluna,linha-2);
                                printf("Senha possivelmente obtida: %s, apos %d tentativas.", senhaDict, somaQtdTentativas);
                                gotoxy(coluna,linha-1);
                                system("pause");
                                flag = 1;
                                break;
                            }
                        }
                        if (!feof(arqDict) && flag == 0) { 
                            printfXY("Houve um erro ao ler o arquivo de dicion�rio.",coluna,linha,0,1,1);
                        }else{
                            if (flag == 0) {
                                printfXY("Foram tentadas: ",coluna,linha,0,1,0); printf("%d senhas",somaQtdTentativas);
                                printfXY("E n�o houve sucesso.", coluna, linha+1,0,0,1);
                            }
                        }
                        fclose(arqDict);               
                    }else{
                        printfXY("N�o foi poss�vel acessar o arquivo de dicion�rio.",coluna,linha,0,1,1);
                    }    
                    free(dadosCopia);
                }else{
                    printfXY("N�o foi poss�vel reservar os recursos necess�rios.", coluna, linha, 0, 1, 1);
                }
                free(dados);
            }else{
                printfXY("N�o foi poss�vel reservar os recursos necess�rios.", coluna, linha, 0, 1, 1);
            }
        }else{
            if (qtdBytesArq != -1) printfXY("Arquivo vazio.", coluna, linha, 0, 1, 1);
        }
    }
}

//Objetivo: desembaralhar os dados em mem�ria.
//Par�metros: endere�o inicial dos dados; qtd. de bytes; endere�o inicial da senha a ser aplicada.
//Retorno: ID do dados.
int desembalhaDadosMemoria(char *dadosArq, int qtdBytesArq, char *senha){
    int idArqAux = 0;
    int caracterParaSubstituir, decimalCaracter, cont, contSenha, tamSenha = strlen(senha);
    char *senhaCopia;

    contSenha = (qtdBytesArq%strlen(senha) != 0) ? qtdBytesArq%strlen(senha) : strlen(senha); //Obten��o do �ltimo caracter processado da senha
    senhaCopia = &senha[(qtdBytesArq%strlen(senha) != 0) ? qtdBytesArq%strlen(senha)-1 : strlen(senha)-1];

    for (cont = qtdBytesArq-1; cont >= 0; --cont) { //Para cada byte/caracter do arq.(do �ltimo byte ao primeiro)
        decimalCaracter = *senhaCopia;
        idArqAux += decimalCaracter;                

        if (decimalCaracter + cont > qtdBytesArq){
            caracterParaSubstituir = decimalCaracter - (decimalCaracter/(qtdBytesArq-cont))*(qtdBytesArq-cont);
        }else{
            caracterParaSubstituir = decimalCaracter + cont;
        }
    
        ordenaChar(&dadosArq[caracterParaSubstituir], &dadosArq[cont]);
    
        if (contSenha > 1){
            contSenha--;
            senhaCopia--;
        }else{
            contSenha = tamSenha;
            senhaCopia = &senha[strlen(senha)-1];
        }
    }
    return idArqAux;
}
