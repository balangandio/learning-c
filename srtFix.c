#include <stdio.h>
#include <conio.c>
#include <string.h>

#define COLUNA 40
#define LINHA 12
#define MIN_SEGUNDOS -3599
#define MAX_SEGUNDOS 3599
#define TAM_PATCH_ARQ 100
#define POSICAO_SEG_1 9
#define POSICAO_MIN_1 6
#define POSICAO_SEG_2 26
#define POSICAO_MIN_2 23
#define POSICAO_HORA_1 3
#define POSICAO_HORA_2 20

int leValidaInt(char *titulo, int min, int max, int coluna, int linha);
void leValidaTexto(char *titulo, char *texto, int tamanho, int minCaracteres, int coluna, int linha);
char leValidaChar(char *titulo, char *opcoes, int coluna, int linha);
char *lePatchArq(char *patchArq, int tamMax, int coluna, int linha);
void printfXY(char *texto, int coluna, int linha, int cor, int limparTela, int interromper);
int verificaPresencaArq(char *nomeArq);
int calculaQtdBytesArq(char *nomeArq);
void *obtemTodoArq(char *nomeArq, int qtdBytesArq);
int gravaArq(void *dados, char *patchArq, int qtdBytes);
void calculaMudancaSegundos(int mudanca, int *hora, int *min, int *seg);
void calculaAdicaoSeg(int adicaoSeg, int *hora, int *min, int *seg);
void calculaSubtracaoSeg(int subtracaoSeg, int *hora, int *min, int *seg);

int main(int qtdArgs, char **args){
//Declarações
    int contBytes, cont, cont2, posicaoHora, posicaoMin, posicaoSeg, contLegenda; 
    int segundosLegenda, minutosLegenda, horaLegenda, qtdBytesArq, segundos, flagArq = 0, coluna = COLUNA-35, linha = LINHA;
    char patchArq[100], aux[200], *dadosArq;
//Instruções

    if (lePatchArq(patchArq, TAM_PATCH_ARQ, COLUNA-35, LINHA) != NULL) {
        if ((qtdBytesArq = calculaQtdBytesArq(patchArq)) > 0) {
            if ((dadosArq = (char *)obtemTodoArq(patchArq, qtdBytesArq)) != NULL) {

                if ((segundos = leValidaInt("Informe a quantidade de segundos a alterar. 0 cancelar: ", MIN_SEGUNDOS, MAX_SEGUNDOS, coluna, linha)) != 0){

                    contLegenda = atoi(dadosArq);

                    for (contBytes = 0; contBytes < qtdBytesArq; ++contBytes){
                        sprintf(aux,"%d", contLegenda);
                        cont = contBytes+(strlen(aux)-1);

                        if (atoi(&dadosArq[contBytes]) == contLegenda && dadosArq[cont+17] == '-' && dadosArq[cont+18] == '>'){

                            ++contLegenda;

                            for (cont2 = 1; cont2 <= 2; ++cont2){
                                switch (cont2) {
                                    case 1:     posicaoSeg = POSICAO_SEG_1;
                                                posicaoMin = POSICAO_MIN_1;
                                                posicaoHora = POSICAO_HORA_1;
                                                break;
                                    case 2:     posicaoSeg = POSICAO_SEG_2;
                                                posicaoMin = POSICAO_MIN_2;
                                                posicaoHora = POSICAO_HORA_2;
                                }

                                segundosLegenda = atoi(&dadosArq[cont+posicaoSeg]);
                                minutosLegenda = atoi(&dadosArq[cont+posicaoMin]);
                                horaLegenda = atoi(&dadosArq[cont+posicaoHora]);

                                calculaMudancaSegundos(segundos, &horaLegenda, &minutosLegenda, &segundosLegenda);

                                sprintf(aux, "%02d", segundosLegenda);
                                dadosArq[cont+posicaoSeg] = aux[0];
                                dadosArq[cont+posicaoSeg+1] = aux[1];
                                sprintf(aux, "%02d", minutosLegenda);
                                dadosArq[cont+posicaoMin] = aux[0];
                                dadosArq[cont+posicaoMin+1] = aux[1];
                                sprintf(aux, "%02d", horaLegenda);
                                dadosArq[cont+posicaoHora] = aux[0];
                                dadosArq[cont+posicaoHora+1] = aux[1];
                            }

                            contBytes += 31;    //Pular os bytes já alterados
                        }
                    }
                    gravaArq((void *)dadosArq, patchArq, qtdBytesArq);
                }
                free(dadosArq);
            }
        }
    } 
  return 0;
}

//Objetivo: calcular a alteração de segundos sobre um tempo de relógio.
//Parâmetros: quantidade de segundos a serem incrementados no tempo( valor positivo ou negativo );
//            endereço da hora(0 a 23), minuto(0 a 59) e segundo(0 a 59) do tempo de relógio a serem atualizados.
//Retorno: sem retorno.
void calculaMudancaSegundos(int mudanca, int *hora, int *min, int *seg) {
    if (mudanca > 0)
        calculaAdicaoSeg(mudanca, hora, min, seg);
    else
        calculaSubtracaoSeg(mudanca, hora, min, seg);
}

//Objetivo: calcular a adição de segundos sobre um tempo de relógio.
//Parâmetros: quantidade de segundos a serem incrementados no tempo( valor positivo );
//            endereço da hora(0 a 23), minuto(0 a 59) e segundo(0 a 59) do tempo de relógio a serem atualizados.
//Retorno: sem retorno.
void calculaAdicaoSeg(int adicaoSeg, int *hora, int *min, int *seg) {
    int adicaoMin, adicaoHora;

    if (adicaoSeg <= 0)
        return;

    if (adicaoSeg + *seg <= 59) {               //Se a adição de seg não incrementar minutos...
        *seg += adicaoSeg;
        return;
    }

    *seg = (*seg + adicaoSeg) % 60;             //Seg atualizado!

    adicaoMin = ((int)(adicaoSeg/60));          //Qtd. de minutos a serem incrementados
    if (adicaoMin == 0)
        adicaoMin = 1;

    if (*min + adicaoMin <= 59) {               //Se a adição de min não incrementar horas...
        *min += adicaoMin;
        return;    
    }

    *min = (*min + adicaoMin) % 60;             //Min atualizado!

    adicaoHora = (int)((adicaoMin)/60);         //Qtd. de horas a serem incrementadas
    if (adicaoHora == 0)
        adicaoHora = 1;
    
    *hora = (*hora + adicaoHora) % 60;          //Hora atualizada!
}

//Objetivo: calcular a subtração de segundos sobre um tempo de relógio.
//Parâmetros: quantidade de segundos a serem decrementados no tempo( valor negativo );
//            endereço da hora(0 a 23), minuto(0 a 59) e segundo(0 a 59) do tempo de relógio a serem atualizados.
//Retorno: sem retorno.
void calculaSubtracaoSeg(int subtracaoSeg, int *hora, int *min, int *seg) {
    int subtracaoMin, subtracaoHora, aux;

    if (subtracaoSeg >= 0 || (*hora == 0 && *min == 0 && *seg == 0))
        return;

    if (*seg + subtracaoSeg >= 0) {             //Se a subtração de seg não decrementar minutos...
        *seg += subtracaoSeg;
        return;
    }

    subtracaoSeg = subtracaoSeg * (-1);         //Quantidade de subtração de segundos positiva( facilitar raciocínio )

    if (*seg - subtracaoSeg + 60 >= 0) {        //Somente um 1 minuto a ser decrementado
        subtracaoMin = 1;
        *seg = *seg - subtracaoSeg + 60;        //Seg atualizado!

    }else{                                      //Há mais de 1 minuto a ser decrementado
        subtracaoSeg -= *seg;           
        *seg = 0;                               //Semi-atualização dos seg
  
        subtracaoMin = (int)(subtracaoSeg/60);  //Qtd. de minutos a serem decrementados
        subtracaoSeg = subtracaoSeg % 60;       //Restante de seg a serem decrementados
 
        if (subtracaoSeg != 0) {                //Se há mais seg a serem decrementados e estamos no seg = 0, então menos 1 minuto
            subtracaoMin++;
            *seg = 60 - subtracaoSeg;           //Seg atualizado!
        }
    }

    if (*min - subtracaoMin >= 0) {             //Se não há alteração de hora, atualizar minuto e cair fora...
        *min = *min - subtracaoMin;
        return;         
    }
                 
    if (hora == 0) {                            //Se a hora é 0 e é necessário drecrementar hora, setar tudo no mínimo e cair fora...
        *min = *seg = 0;
        return;
    }

    subtracaoHora = (int)((subtracaoMin - *min)/60);
    if (subtracaoHora % 60 != 0)
        subtracaoHora++;
    if (*hora - subtracaoHora < 0) {
        *hora = *min = *seg = 0;
        return;
    }

    aux = 0;                                    //O cálculo para alterar a hora com minutos é o mesmo para alterar minuto com segundos,
    calculaSubtracaoSeg(subtracaoMin * (-1), &aux, hora, min);    //logo, podemos aproveitar o que já foi feito com uma recursividade:}
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

//Objetivo: ler e validar um caracter.
//Parâmetros: endereço incial da string com a instrução de entrada e das opções válidas de escolha; coluna e linha da instrução.
//Retorno: opção válida.
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

//Objetivo: ler o patch de um arquivo.
//Parâmetros: endereço para armazenamento da leitura; tamanho máximo do patch; coluna e linha de apresentação.
//Retorno: endereço armazem enviado; NULL caso o usuário cancele a entrada.
char *lePatchArq(char *patchArq, int tamMax, int coluna, int linha) {
    char aux[200];
    int flagArq;

    sprintf(aux, ">>Informe o patch do arquivo.\n%6sNulo para encerrar: ", " ");
    do {
        leValidaTexto(aux, patchArq, tamMax, 0, coluna, linha);
        if (strlen(patchArq) > 0)
            if ((flagArq = verificaPresencaArq(patchArq)) == 0)
                sprintf(aux, ">>Arquivo inacessível, informe novamente. Nulo para encerrar: ");
    }while(strlen(patchArq) > 0 && flagArq == 0);

    return (strlen(patchArq) == 0) ? NULL : patchArq;
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

//Objetivo: obter a quantidade de bytes de um arq.
//Parâmetros: endereço inicial do nome do arq.
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
                printfXY("Não foi possível posicionar-se no arquivo.", coluna, linha, 0, 1, 1);
            }
        }else{
            printfXY("Não foi possível posicionar-se no arquivo.", coluna, linha, 0, 1, 1);
        }
    }else{
        printfXY("Arquivo não pode ser aberto.", coluna, linha, 0, 1, 1);
    }
    return -1;
}

//Objetivo: obter todos os dados de um arq. para a memória.
//Parâmetros: endereço inicial do nome do arq.; qtd. de bytes do arq.
//Retorno: endereço inicial da posição onde está o arq.; NULL em caso de falha
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
                printfXY("Não foi possível ler o arquivo.", coluna, linha, 0, 1, 1);                
            }
        }else{
            printfXY("Não foi possível reservar os recursos necessários.", coluna, linha, 0, 1, 1);
        }
    }else{
        printfXY("Não foi possível acessar o arquivo.", coluna, linha, 0, 1, 1);
    }
    return NULL;
}

//Objetivo: gravar um conteúdo da memória em um novo arquivo.
//Parâmetros: endereço inicial dos dados e serem gravados, e do patch do arquivo; quantidade de bytes a serem gravados.
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
            printfXY("Não foi possível gravar os dados no novo arquivo.", coluna, linha, 0, 1, 1);
        }
        fclose(arq);
    }else{
        printfXY("Não foi possível criar um novo arquivo para os dados.", coluna, linha, 0, 1, 1);
    }
}
