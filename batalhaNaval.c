#include <stdio.h>

// Desafio Batalha Naval - MateCheck

//declaraçao das variaveis e constante
#define TAM 10 //define quantidade de linhas e colunas do tabuleiro
int tabuleiro[TAM][TAM];
int navio1[] = {12, 13, 14};
int navio2[] = {56, 66, 76};
int navio3[] = {33, 42, 51}; //em diagonal
int navio4[] = {07, 18, 29}; //em diagonal

//constrói o tabuleiro de acordo com o tamanho informado na constante TAM
void construtorTabuleiro(void){
    //primeiro laço percorre as linhas
    for(int i = 0; i < TAM; i++){
        //segundo laço percorre as colunas
        for(int j = 0; j < TAM; j++){
            //seta a posição com valor 0
            tabuleiro[i][j] = 0;
        }
    }
}

void exibirTabuleiro(void){
    //primeiro laço percorre as linhas
    for(int i = 0; i < TAM; i++){
        //segundo laço percorre as colunas
        for(int j = 0; j < TAM; j++){
            //exibe o conteudo da posição
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int validarPosicaoNavio(int navio[]){
    //pega tamanho do tabuleiro e do navio
    int tamTabuleiro = sizeof(tabuleiro)/sizeof(tabuleiro[0][0]);
    int tamNavio = sizeof(navio)/sizeof(navio[0]);

    //verifica se cada posicao do navio é menor que 0 ou maior que o tamanho do tabuleiro
    //ou seja, se esta fora das coordenadas do tabuleiro
    for(int i = 0; i <= tamNavio; i++){
        if(navio[i] < 0){
            return 1;
        }
        if(navio[i] > (tamTabuleiro - 1)){
            return 1;
        }
    }

    //verifica se a posicao do navio ja esta ocupada
    for(int i = 0; i <= tamNavio; i++){
        //verifica se a posicao é diferente de 0, ou seja, se ja tem um navio naquela posicao
        //navio[i]/10 pega a dezena/linha e navio[i]%10 pega a unidade/coluna, ex: 12/10 = 1 e 12%10 = 2
        if(tabuleiro[navio[i]/10][navio[i]%10] != 0){
            return 2;
        }
    }

    return 0;
}

int inserirNavio(int navio[]){
    //pega tamanho do navio
    int tamNavio = sizeof(navio)/sizeof(navio[0]);

    int validacao = validarPosicaoNavio(navio);

    //0 = validacao nao encontrou problemas
    if(validacao == 0){
        for(int i = 0; i <= tamNavio; i++){
            //navio[i]/10 pega a dezena/linha e navio[i]%10 pega a unidade/coluna, ex: 12/10 = 1 e 12%10 = 2, posicao tabuleiro[1][2]
            tabuleiro[navio[i]/10][navio[i]%10] = 3; //marca posicao do navio com num 3
        }
        printf("Navio inserido com sucesso.\n\n");
    }
    
    //1 = validacao encontrou posicao fora do tabuleiro
    if(validacao == 1){
        printf("Posição inválida! O navio está fora do tabuleiro.\n\n");
    }

    //2 = validacao encontrou posicao ja ocupada
    if(validacao == 2){
        printf("Posição inválida! A posição já está ocupada por outro navio.\n\n");
    }

    return 0;
}

void construirOctaedro(void){
    //define variaveis com o meio das linhas e colunas
    int colunaInicio = TAM / 2;
    int colunaFim = TAM / 2;
    int linhaInicio = TAM / 2;
    int linhaFim = TAM / 2;

    //se for par, a coluna de inicio e a linha de fim da primeira parte precisam ser a anterior
    if(TAM % 2 == 0){
        colunaInicio = (TAM / 2) - 1;
        linhaFim = (TAM / 2) - 1;
    }

    //constrói a primeira metade das linhas
    for(int i = 0; i <= linhaFim; i++){
        //insere 1 nas posiçoes da coluna de inicio até a coluna de fim
        for(int j = colunaInicio; j <= colunaFim; j++){
            tabuleiro[i][j] = 1;
        }

        //decrementa a coluna de inicio e incrementa a coluna fim, para aumentar as posiçoes preenchidas a cada linha
        colunaInicio -= 1;
        colunaFim += 1;
    }

    //constrói a segunda metade das linhas
    for(int i = linhaInicio; i < TAM; i++){
        //agora faz-se o procedimento contrario:
        //incrementa a coluna de inicio e decrementa a coluna fim, para diminuir as posiçoes preenchidas a cada linha
        colunaInicio += 1;
        colunaFim -= 1;

        //insere 1 nas posiçoes da coluna de inicio até a coluna de fim
        for(int j = colunaInicio; j <= colunaFim; j++){
            tabuleiro[i][j] = 1;
        }
    }
}

int main(void) {
    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal

    //constrói o tabuleiro com todos as posicoes zeradas
    construtorTabuleiro();

    //insere navios no tabuleiro
    inserirNavio(navio1);
    inserirNavio(navio2);
    inserirNavio(navio3);
    inserirNavio(navio4);

    //exibe o tabuleiro com os navios posicionados
    exibirTabuleiro();

    // Nível Mestre - Habilidades Especiais com Matrizes

    //constrói um octaedro na matriz
    construtorTabuleiro();
    construirOctaedro();
    exibirTabuleiro();

    return 0;
}
