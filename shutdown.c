
#include <stdio.h>
#include <conio.c>
//Prot�tipos
void printfXY(char *texto, int coluna, int linha, int cor, int limparTela, int interromper);

int main(){
//Declara��es
    int min, hora, seg, segundos;
//Instru��es
    printfXY("Informe o tempo antes do computador se desligar.", 10, 10, 0, 0, 0);
    printfXY("Informe no formato: XhXmXs - Ex. 1h4m2s: ", 10, 11, 0, 0, 0);
    
    scanf("%dh%dm%ds", &hora, &min, &seg);
    
    segundos = getSegundos(hora, min, seg);

    printf("\n%9s%d horas %d minutos %d segundos = %ds\n\n", " ", hora, min, seg, segundos);

    printf("Execute: shutdown -s -f -t %d\n", segundos);
    printf("Execute: shutdown -a  para interromper\n\n");

  system("pause");
  return 0;
}

//Objetivo: obter a quantidade de segundos de um determinado tempo.
//Par�metros: hora, minutos, segundos.
//Retorno: quantidade de segundos.
int getSegundos(int hora, int min, int seg) {
    int ret = seg;

    ret += min * 60;

    return hora * 60 * 60 + ret;
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
