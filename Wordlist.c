/*
//Objetivo: remover as senhas que n�o est�o em um determinado tamanho em uma wordlist.
//Entrada: valores m�nimo e m�ximo de senha para o arquivo.
//Sa�da: novo arquivo com as senhas que obedecem ao intervalo dado.

-ler valores m�nimo e m�ximo para o interalo(m�nimo 1; m�ximo 50)
-ler patch da wordlist(deve existir)
-(abrir repati��o)
--ler palavra da wordlist
--se a palavra estiver no intervalo, grava-la no novo arquivo
--(fim repeti��o, at� chegar ao fim do aquivo ou erro)
*/

#include <stdio.h>
#include <conio.c>
#define COLUNA 40
#define LINHA 20
#define MAX_TAM_PALAVRA 50
#define MAX_TAM_PATCH_ARQ 200
//Prot�tipos
void leValidaTexto(char *titulo, char *texto, int tamanho, int minCaracteres, int coluna, int linha);
int leValidaInt(char *titulo, int min, int max, int coluna, int linha);
void printfXY(char *texto, int coluna, int linha, int cor, int limparTela, int interromper);
int verificaPresencaArq(char *nomeArq);

int main(){
//Declara��es
    int cont, tamMin, tamMax, auxOrdenacao, flagArq = 0, flagErro = 0, coluna = COLUNA-35, linha = LINHA-8;
    char patchArq[MAX_TAM_PATCH_ARQ], patchArqNovo[MAX_TAM_PATCH_ARQ], palavra[MAX_TAM_PALAVRA], auxTitulo[200];
    FILE *arq, *arqNovo;
//Instru��es
    sprintf(auxTitulo, ">>Informe o patch do arquivo. Nulo para encerrar: "); 
    do {
        leValidaTexto(auxTitulo, patchArq, MAX_TAM_PATCH_ARQ, 0, coluna, linha);//Leitura e valida��o do patch do arquivo
        if (strlen(patchArq) > 0)
            if ((flagArq = verificaPresencaArq(patchArq)) == 0)
                sprintf(auxTitulo, ">>Arquivo inacess�vel, informe novamente. Nulo para encerrar: ");
    }while(strlen(patchArq) > 0 && flagArq == 0);

    if (strlen(patchArq) > 0) { //Leitura dos valores m�ximo e m�nimo de tamanho
        tamMin = leValidaInt(">>Informe o tamanho m�nimo para as palavras. 0 para cancelar: ", 0, MAX_TAM_PALAVRA, coluna, linha);
    
        if (tamMin > 0){
            tamMax = leValidaInt(">>Informe o tamanho m�ximo para as palavras. 0 para cancelar: ", 0, MAX_TAM_PALAVRA, coluna, linha);
    
            if (tamMax > 0){
                if (tamMin > tamMax){ //Ordena��o dos valores de m�nimo e m�ximo casa n�o j� estejam
                    auxOrdenacao = tamMin;
                    tamMin = tamMax;
                    tamMax = auxOrdenacao;
                }
                if ((arq = fopen(patchArq, "r")) != NULL){
                    sprintf(patchArqNovo, "%s.novo", patchArq);//Nome do novo arquivo
                    if ((arqNovo = fopen(patchArqNovo, "a")) != NULL){

                        while(fgets(palavra, MAX_TAM_PALAVRA, arq) != NULL){//Para cada palavra do arquivo...
                            while(palavra[strlen(palavra)] != '\0')//Caso a palavra seja maior que o armazenamento, pular ela ir�s
                                if(fgets(palavra, MAX_TAM_PALAVRA, arq) == NULL)
                                    flagErro = 1;                          

                            if (strlen(palavra)-1 >= tamMin && strlen(palavra)-1 <= tamMax) {//Caso a palavra esteja dentro do intervalo...
                                if (fwrite(palavra, strlen(palavra), 1, arqNovo) != 1) {//Grava��o da palavra que obedece ao intervalo
                                    printfXY(">>Erro ao gravar dados no novo arquivo.", coluna, linha, 0, 1, 1);
                                    flagErro = -1;//Erro na grava��o do novo arquivo
                                }
                            }

                            if(flagErro != 0) break;
                        }
                        if ((!feof(arq) && flagErro != -1) || flagErro == 1){//Erro na leitura do arquivo
                            printfXY(">>Erro ao ler arquivo.", coluna, linha, 0, 1, 1);
                        }

                        fclose(arqNovo);
                    }else{
                        printfXY(">>N�o foi poss�vel criar o novo arquivo.", coluna, linha, 0, 1, 1);
                    }

                    fclose(arq);
                }else{
                    printfXY(">>N�o foi poss�vel abrir o arquivo.", coluna, linha, 0, 1, 1);
                }
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

//Objetivo: ler e validar um valor inteiro.
//Par�metros: endere�o incial da instru��o de entrada(string); valores m�nimo e m�ximo para valida��o; coluna e linha de apresenta��o.
//Retorno: valor inteiro v�lido.
int leValidaInt(char *titulo, int min, int max, int coluna, int linha){
    int valor;
    char tituloCopia[200]; strcpy(tituloCopia, titulo);

    system("cls");
    do{
        do{
            printfXY(tituloCopia,coluna,linha,0,0,0);
            fflush(stdin);
        }while(scanf("%d",&valor) == 0);
        if (valor < min || valor > max){
            printfXY("",coluna,linha+2,0,1,0);
            printf("Valor inv%clido, n%co entre %d e %d. ", 160, 198, min, max);
            strcpy(tituloCopia,">>Informe novamente: ");
        }
    }while(valor < min || valor > max);
    fflush(stdin);
    return valor;
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
