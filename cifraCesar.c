#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALFABETO "abcdefghijklmnopqrstuvwxyz"
#define MAX_MSG 1000

char getCharDeslocamento(int deslocamento, char caracter, char *alfabeto);
int getPosicaoChar(char c, char *str);
void criptografa(char *mensagem, int deslocamento, char *alfabeto);
void descriptografa(char *mensagem, int deslocamento, char *alfabeto);

//Objetivo: implementar a cifra de César.
//Entrada: mensagem qualquer e deslocamento.
//Saída: mensagem cifrada e mensagem original.
int main(void) {
//Declarações
    char mensagem[MAX_MSG];
    int deslocamento;
//Instruções
    printf("Informe a mensagem: ");
    fgets(mensagem, MAX_MSG, stdin);
    fflush(stdin);
    if (mensagem[strlen(mensagem)-1] == '\n')
        mensagem[strlen(mensagem)-1] = '\0';

    printf("Deslocamento [pode ser positivo, negativo, e dar voltas no alfabeto]: ");
    scanf("%d", &deslocamento);
    fflush(stdin);
    
    criptografa(mensagem, deslocamento, ALFABETO);
    printf("\nMensagem criptografada: %s\n\n", mensagem);

    descriptografa(mensagem, deslocamento, ALFABETO);
    printf("Mensagem descriptografada: %s\n\n", mensagem);

    system("pause");
  return 0;
}

//Objetivo: aplicar a cifra de César em uma mensagem.
//Parâmetros: mensagem; deslocamento; alfabeto;
//Retorno: sem retorno.
void criptografa(char *mensagem, int deslocamento, char *alfabeto) {
    int cont, c, tam = strlen(mensagem);

    for (cont = 0; cont < tam; cont++) 
        if ((c = getCharDeslocamento(deslocamento, mensagem[cont], alfabeto)) != -1)
            mensagem[cont] = c;
}

//Objetivo: descriptografar uma cifra de César.
//Parâmetros: mensagem; deslocamento usado para criptografar; alfabeto.
//Retorno: sem retorno.
void descriptografa(char *mensagem, int deslocamento, char *alfabeto) {
    criptografa(mensagem, deslocamento * (-1), alfabeto);
}

//Objetivo: obter o caracter de um alfabeto mediante ao deslocamento de um outro caracter.
//Parâmetros: quantidade de posições que serão saltadas a partir do caracter informado;
//            caracter a partir de onde ocorrerá o deslocamento;
//            alfabeto a ser utilizado.
//Retorno: caracter obtido no deslocamento; -1 se o caracter informado não está presente no alfabeto.
//Exemplo: params(3, a, abcd...) retorna d, pois d se encontra a 3 posições de a.
char getCharDeslocamento(int deslocamento, char caracter, char *alfabeto) {
    int posicao;    
    int tam = strlen(alfabeto);

    if ((posicao = getPosicaoChar(caracter, alfabeto)) == -1)
        return -1;

    if (deslocamento > tam || deslocamento < tam * (-1)) //Cuida se o deslocamento for maior que alfabeto
        deslocamento %= (tam);

    posicao += deslocamento;

    if (posicao > tam-1)    //Cuida se a posição resultamente for maior que o alfabeto (dá volta positiva)
        posicao = posicao - tam;
    else
        if (posicao < 0)    //Cuida se a posição resultante for menor que o alfabeto (dá volta negativa)
            posicao += tam;
      

    return alfabeto[posicao];
}

//Objetivo: obter o índice de array de um caracter numa string.
//Parâmetros: caracter a ser verificado; endereço inicial da string a ser verificada.
//Retorno: índice do caracter na string.
int getPosicaoChar(char c, char *str) {
    int cont;

    for (cont = 0; *str; cont++, str++)
        if (c == *str) 
            break;

    return (*str == 0) ? -1 : cont;
}

