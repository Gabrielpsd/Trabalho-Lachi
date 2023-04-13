#ifndef quadrado_h 
#define quadrado_h

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

typedef struct _tela{
	COORD dimensao_atual;
	COORD dimensao_maxima;
	COORD inicial_tela;
}tela;

/*
|---------------  Ambiente -------------------------|
|	Ira criar a janela principal do jogo			|
|		Tamanho da janela e posicao da janela		|
|		Tamanho Maximo;								|
|---------------------------------------------------|
*/
void Set_ambiente(tela *);

void cria_janela(COORD *, COORD *, int);

/*
|-------------------  Fim  -------------------------|
|	Ira Remover a janela principal do jogo			|
|	retornar Tamanho da janela e posicao da janela	|
|													|
|---------------------------------------------------|
*/
void fim_jogo(tela *);

#endif /* quadrado_h */ 