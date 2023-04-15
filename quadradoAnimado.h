#ifndef quadradoAnimado
#define quadradoAnimado

#include <Windows.h> /* COORD */ 

#define TITULO "Quadrado Animado"  

	/* ---------   funcao que ira criar a janela inicial na tela ----------------------
		a funcao utilizara dois pontos como referencia, sendo Ponto1 o ponto da diagonal superior esquerda 
		e o Ponto2 o ponto localixado no canto inferior direito, a funcao realizaraa ligação entre os dois 
		utilizando a funcao linha da biblioteca Conio
	*/ 

	/*
	|-------------------  tela -------------------------|
	|	Guarda as informações da tela, são elas:		|
	|		Posicao inicial;							|
	|		Tamanho Maximo;								|
	|													|
	|---------------------------------------------------|
	*/
typedef enum{
	DESATIVAR,
	ATIVAR
}ATIVIDADE;

typedef struct _tela{
	COORD dimensao_inicial;
	COORD posicao_inicial;
	COORD dimensao_maxima;
}CONSOLE;

typedef struct _Janela{
	COORD *ponto1, ref1;
	COORD *ponto2, ref2;
	COORD *centro, refC;
	
	int linha, coluna;
	
}JANELA;

	/*
	|---------------  Ambiente -------------------------|
	|	Ira criar a definição do prompt do jogo			|
	|		Tamanho da janela e posicao da janela		|
	|		Tamanho Maximo;								|
	|---------------------------------------------------|
	*/
void set_ambiente(CONSOLE *, int);


	/*
	|---------------  Janela ---------------------------|
	|	Ira criar a janela principal do jogo			|
	|		Tamanho da janela e posicao da janela		|
	|		Tamanho Maximo;								|
	|---------------------------------------------------|
	*/
	
void gerencia_janela(JANELA *, int,CONSOLE);

void cria_janela1(JANELA, int, CONSOLE);

void cria_janela2(JANELA);

void cria_ponto(JANELA *, CONSOLE);

void inicia_jogo();

	/*
	|-------------------  Fim  -------------------------|
	|	Ira Remover a janela principal do jogo			|
	|	retornar Tamanho da janela e posicao da janela	|
	|													|
	|---------------------------------------------------|
	*/
void fim_jogo(CONSOLE *);

void depuracao(JANELA, CONSOLE,int);

#endif /* quadradoAnimado */ 