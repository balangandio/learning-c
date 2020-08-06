#include <stdio.h>
#define MAX_TAM_MATRIX 6//6x6
void apresentaMatriz(float matriz[][MAX_TAM_MATRIX], int nLinhas, int nColunas);
void defineDimensoesMatriz(int *nLinhas, int *nColunas);
void defineValoresMatriz(float matriz[][MAX_TAM_MATRIX], int nLinhas, int nColunas);
void operacao2(float matriz[][MAX_TAM_MATRIX], int nColunas, int nLinhas);
void operacao3(float matriz[][MAX_TAM_MATRIX], int nColunas, int nLinhas);
float leFloatFracao();
int leValidaInt(char *titulo, int min, int max);
void obtemFracao(float matriz[][MAX_TAM_MATRIX], int nColunas, int nLinhas);

int main(void){
//Declarações
    float matriz[MAX_TAM_MATRIX][MAX_TAM_MATRIX];
    int nLinhas, nColunas;
    char opcaoMenu; 
//Instruções
    defineDimensoesMatriz(&nLinhas, &nColunas);
    defineValoresMatriz(matriz, nLinhas, nColunas);
    do{
        system("cls");
        apresentaMatriz(matriz, nLinhas, nColunas);
        printf("\n1: redefinir matriz\n");
        printf("2: operacao 2\n");
        printf("3: operacao 3\n");
        printf("4: obter fracao\n");
        printf("5: sair\n\n");
        printf("Escolha uma opcao: ");
        opcaoMenu = getch();
        system("cls");  
        switch(opcaoMenu){
            case '1': defineDimensoesMatriz(&nLinhas, &nColunas); 
                      defineValoresMatriz(matriz, nLinhas, nColunas); break;
            case '2': operacao2(matriz, nColunas, nLinhas); break;
            case '3': operacao3(matriz, nColunas, nLinhas); break;
            case '4': obtemFracao(matriz, nColunas, nLinhas);
        }
    }while(opcaoMenu != '5');
  return 0;
}

// Objetivo: apresentar a matriz.
// Parâmetros: referências a matriz; quantidade de linhas e colunas.
// Retorno: sem retorno.
void apresentaMatriz(float matriz[][MAX_TAM_MATRIX], int nLinhas, int nColunas){
    int contLinha, contColuna;
    printf("%24s", "--- Matriz ---\n");
    for (contLinha = 0; contLinha < nLinhas; ++contLinha) {
        for (contColuna = 0; contColuna < nColunas; ++contColuna)
            printf("%12f |", matriz[contLinha][contColuna]);
        printf("\n");
    }
}

// Objetivo: ler os valores para uma matriz
// Parâmetros: referências a matriz; quantidade de linhas e colunas.
// Retorno: sem retorno.
void defineValoresMatriz(float matriz[][MAX_TAM_MATRIX], int nLinhas, int nColunas){
    int contLinha, contColuna;
    for (contLinha = 0; contLinha < nLinhas; ++contLinha) {
        for (contColuna = 0; contColuna < nColunas; ++contColuna) {
            system("cls");
            printf("Informe o valor L%d-C%d: ", contLinha+1, contColuna+1);
            matriz[contLinha][contColuna] = leFloatFracao();
        }
    }
}

// Objetivo: ler as dimenções da matriz
// Parâmetros: referências para armazenamento do nº de linhas e colunas.
// Retorno: sem retorno.
void defineDimensoesMatriz(int *nLinhas, int *nColunas){
    system("cls");
    *nLinhas = leValidaInt("Informe o numero de linhas: ", 1, MAX_TAM_MATRIX);
    *nColunas = leValidaInt("Informe o numero de colunas: ", 1, MAX_TAM_MATRIX);
}

// Objetivo: calcular a operação 2.
// Parâmetros: referência a matriz; quantidade de colunas e de linhas.
// Retorno: sem retorno.
void operacao2(float matriz[][MAX_TAM_MATRIX], int nColunas, int nLinhas){
    int cont, linha;
    float multiplicador;

    linha = leValidaInt("Informe a linha alvo: ", 1, nLinhas);

    printf("Informe o multiplicador: "); multiplicador = leFloatFracao();

    system("cls");
    printf("\n\n\n\nResultado:");
    for (cont = 0; cont < nColunas; ++cont){
        matriz[linha-1][cont] = matriz[linha-1][cont] * multiplicador;
        printf("%12f |", matriz[linha-1][cont]);
    }
    printf("\n\n\n");
    system("pause");
}

// Objetivo: calcular a operação 3.
// Parâmetros: referência a matriz; quantidade de colunas e de linhas.
// Retorno: sem retorno.
void operacao3(float matriz[][MAX_TAM_MATRIX], int nColunas, int nLinhas){
    int cont, linhaAlvo, linhaUsada;
    float multiplicador;

    linhaAlvo = leValidaInt("Informe a linha alvo: ", 1, nLinhas);
    linhaUsada = leValidaInt("Informe a linha usada: ", 1, nLinhas);

    printf("Informe o multiplicador: "); multiplicador = leFloatFracao();

    system("cls");
    printf("\n\n\n\nResultado:");
    for (cont = 0; cont < nColunas; ++cont){
        matriz[linhaAlvo-1][cont] = matriz[linhaAlvo-1][cont] + multiplicador * matriz[linhaUsada-1][cont];
        printf("%12f |", matriz[linhaAlvo-1][cont]);
    }
    printf("\n\n\n");
    system("pause");

}

//Objetivo: ler uma valor real em forma de fração ou não.
//Parâmetros: sem parâmetros.
//Retorno: valor real.
float leFloatFracao(){
    int numerador, denominador;
    float valor;
    char opcao;
    for (printf("\nCom ou sem fracao(F/S): "), opcao = toupper(getch()); opcao != 'F' && opcao != 'S'; opcao = toupper(getch()))
        printf("\nOpcao invalida. Informe novamente: ");

    if (opcao == 'F'){
        numerador = leValidaInt("\nInforme o numerador: ", -999999, 999999);
        denominador = leValidaInt("Informe o denominador: ", -999999, 999999);
        valor = ((float)numerador/denominador);
    }else{
        do{
            fflush(stdin);
	        printf("\nValor: ");
	    }while(scanf("%f",&valor) == 0);
    }
    return valor;
}

// Objetivo: ler e validar um valor inteiro.
// Parâmetros: referência da instrução de entrada; valor mínimo e máximo para validação.
// Retorno: valor válido.
int leValidaInt(char *titulo, int min, int max){
	int valor;
	do{
       do{
            fflush(stdin);
	        printf(titulo);
	   }while(scanf("%d",&valor) == 0);
       if (valor < min || valor > max) 
           printf("Valor nao compreendido entre %d e %d. ", min, max);
	}while (valor < min || valor > max);
	return valor;
}

// Objetivo: obter a fração de uma valor da matriz.
// Parâmetros: endereço inicial da matriz; quantidade de colunas e de linhas.
// Retorno: sem retorno.
void obtemFracao(float matriz[][MAX_TAM_MATRIX], int nColunas, int nLinhas){
    float valor, valorCont;
    int contNumerador, contDenominador, flag, linha, coluna;

    linha = leValidaInt("Informe a linha do valor: ", 1, nLinhas);
    coluna = leValidaInt("Informe a coluna do valor: ", 1, nColunas);

    valor = matriz[linha-1][coluna-1];
    if (valor < 0) valor *= -1;

    for (contNumerador = 1; contNumerador <= 10000; ++contNumerador){
        for (contDenominador = 2; contDenominador <= 10000; ++contDenominador){
            valorCont = (float)contNumerador/contDenominador;
            if ((int)(valorCont*100000) == (int)(valor*100000)){
                system("cls");
                printf("Encontrado: %f\n",(float)contNumerador/contDenominador);
                printf("Fracao: %5d\n%13d\n", contNumerador, contDenominador);
                printf("\nTecle E para encerrar operacao: ");
                if(toupper(getch()) == 'E'){
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 1) break;
    }
}
