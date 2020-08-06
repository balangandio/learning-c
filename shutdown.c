
#include <stdio.h>
#include <conio.c>
//Protótipos
void printfXY(char *texto, int coluna, int linha, int cor, int limparTela, int interromper);

int main(){
//Declarações
    int min, hora, seg, segundos;
//Instruções
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
//Parâmetros: hora, minutos, segundos.
//Retorno: quantidade de segundos.
int getSegundos(int hora, int min, int seg) {
    int ret = seg;

    ret += min * 60;

    return hora * 60 * 60 + ret;
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
