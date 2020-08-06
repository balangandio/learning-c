#include <stdio.h>
#include <conio.c>
void limpaTela(void);
float leFloatFracao(void);
int leValidaInt(char titulo[], int min, int max);

int main(void){
//Declarações
    float valor, valorCont;
    int contNumerador, contDenominador, flag;  
//Instruções
    do{
        flag = 0;
        system("cls");
        printf("Informe o valor a verificar: ");
        valor = leFloatFracao();

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
        system("cls");
        printf("Done! Sair ou continuar(S/C): ");
        if (toupper(getch()) == 'S') break;
    }while(1);
  return 0;
}

//Objetivo: limpar a tela.
//Parâmetros: sem parâmetros.
//Retorno: sem retorno.
void limpaTela(void){
    int contColuna, contLinha;
    for (contLinha = 20; contLinha >= 1; --contLinha){
        for (contColuna = 40; contColuna >= 1; --contColuna){
            gotoxy(contColuna,contLinha);
            printf(" ");
        }        
    }
    gotoxy(1,1);
}

//Objetivo: ler uma valor real em forma de fração ou não.
//Parâmetros: sem parâmetros.
//Retorno: valor real.
float leFloatFracao(void){
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
int leValidaInt(char titulo[], int min, int max){
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
