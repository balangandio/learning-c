/*
//Objetivo: remover as senhas que não estão em um determinado tamanho em uma wordlist.
//Entrada: valores mínimo e máximo de senha para o arquivo.
//Saída: novo arquivo com as senhas que obedecem ao intervalo dado.

-ler valores mínimo e máximo para o interalo(mínimo 1; máximo 50)
-ler patch da wordlist(deve existir)
-(abrir repatição)
--ler palavra da wordlist
--se a palavra estiver no intervalo, grava-la no novo arquivo
--(fim repetição, até chegar ao fim do aquivo ou erro)
*/

#include <stdio.h>
#include <conio.c>
#define COLUNA 40
#define LINHA 20
#define MAX_TAM_PALAVRA 50
#define MAX_TAM_PATCH_ARQ 200
//Protótipos
void leValidaTexto(char *titulo, char *texto, int tamanho, int minCaracteres, int coluna, int linha);
int leValidaInt(char *titulo, int min, int max, int coluna, int linha);
void printfXY(char *texto, int coluna, int linha, int cor, int limparTela, int interromper);
int verificaPresencaArq(char *nomeArq);

int main(){
//Declarações
    int cont, tamMin, tamMax, auxOrdenacao, flagArq = 0, flagErro = 0, coluna = COLUNA-35, linha = LINHA-8;
    char patchArq[MAX_TAM_PATCH_ARQ], patchArqNovo[MAX_TAM_PATCH_ARQ], palavra[MAX_TAM_PALAVRA], auxTitulo[200];
    FILE *arq, *arqNovo;
//Instruções
    sprintf(auxTitulo, ">>Informe o patch do arquivo. Nulo para encerrar: "); 
    do {
        leValidaTexto(auxTitulo, patchArq, MAX_TAM_PATCH_ARQ, 0, coluna, linha);//Leitura e validação do patch do arquivo
        if (strlen(patchArq) > 0)
            if ((flagArq = verificaPresencaArq(patchArq)) == 0)
                sprintf(auxTitulo, ">>Arquivo inacessível, informe novamente. Nulo para encerrar: ");
    }while(strlen(patchArq) > 0 && flagArq == 0);

    if (strlen(patchArq) > 0) { //Leitura dos valores máximo e mínimo de tamanho
        tamMin = leValidaInt(">>Informe o tamanho mínimo para as palavras. 0 para cancelar: ", 0, MAX_TAM_PALAVRA, coluna, linha);
    
        if (tamMin > 0){
            tamMax = leValidaInt(">>Informe o tamanho máximo para as palavras. 0 para cancelar: ", 0, MAX_TAM_PALAVRA, coluna, linha);
    
            if (tamMax > 0){
                if (tamMin > tamMax){ //Ordenação dos valores de mínimo e máximo casa não já estejam
                    auxOrdenacao = tamMin;
                    tamMin = tamMax;
                    tamMax = auxOrdenacao;
                }
                if ((arq = fopen(patchArq, "r")) != NULL){
                    sprintf(patchArqNovo, "%s.novo", patchArq);//Nome do novo arquivo
                    if ((arqNovo = fopen(patchArqNovo, "a")) != NULL){

                        while(fgets(palavra, MAX_TAM_PALAVRA, arq) != NULL){//Para cada palavra do arquivo...
                            while(palavra[strlen(palavra)] != '\0')//Caso a palavra seja maior que o armazenamento, pular ela irás
                                if(fgets(palavra, MAX_TAM_PALAVRA, arq) == NULL)
                                    flagErro = 1;                          

                            if (strlen(palavra)-1 >= tamMin && strlen(palavra)-1 <= tamMax) {//Caso a palavra esteja dentro do intervalo...
                                if (fwrite(palavra, strlen(palavra), 1, arqNovo) != 1) {//Gravação da palavra que obedece ao intervalo
                                    printfXY(">>Erro ao gravar dados no novo arquivo.", coluna, linha, 0, 1, 1);
                                    flagErro = -1;//Erro na gravação do novo arquivo
                                }
                            }

                            if(flagErro != 0) break;
                        }
                        if ((!feof(arq) && flagErro != -1) || flagErro == 1){//Erro na leitura do arquivo
                            printfXY(">>Erro ao ler arquivo.", coluna, linha, 0, 1, 1);
                        }

                        fclose(arqNovo);
                    }else{
                        printfXY(">>Não foi possível criar o novo arquivo.", coluna, linha, 0, 1, 1);
                    }

                    fclose(arq);
                }else{
                    printfXY(">>Não foi possível abrir o arquivo.", coluna, linha, 0, 1, 1);
                }
            }
        }
    }
  return 0;
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
//Parâmetros: endereço incial da instrução de entrada(string); valores mínimo e máximo para validação; coluna e linha de apresentação.
//Retorno: valor inteiro válido.
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
//Parâmetros: endereço inicial da string a ser apresentada; coluna e linha da apresentação;
//           opção para limpar a tela(0, mantém; 1, limpa); opção para interromper execução(0, não; 1, interromper);
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
                    case 'ê': c = 136; break;
                    case 'é': c = 130; break;
                    case 'á': c = 160; break;
                    case 'à': c = 133; break;
                    case 'â': c = 131; break;
                    case 'ç': c = 135; break;
                    case 'ã': c = 198; break;
                    case 'º': c = 167; break;
                    case 'í': c = 161; break;
                    case 'ú': c = 163; break;
                    case 'ó': c = 162; break;
                    case 'õ': c = 228; break;
                    case 'ª': c = 166; break;
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
            printf("N%co foi possível alocar os recursos necessarios.",198);
        }
    }
    if (interromper == 1){
        gotoxy(coluna,linha+3);
        system("pause");
    }
}

//Objetivo: verificar se um arq. está acessível.
//Parâmetros: endereço inicial do nome do arquivo.
//Retorno: 0, arquivo inacessível; 1, arquivo acessível.
int verificaPresencaArq(char *nomeArq){
    FILE *arq;
    if ((arq = fopen(nomeArq, "r")) != NULL){
        fclose(arq);
        return 1;
    }
    return 0;
}
