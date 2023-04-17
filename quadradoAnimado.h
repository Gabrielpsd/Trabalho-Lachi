#ifndef quadradoAnimado
#define quadradoAnimado

#include <Windows.h> /* COORD */ 

#define TITULO "Quadrado Animado"  
#define TAMANHO 16
/* --------------------------- Declaracoes de variaveis e constantes ------------------------------------*/ 
typedef enum
{
	DESATIVAR,
	ATIVAR
}ATIVIDADE;

typedef enum
{	
	CIMA,
	DIREITA,
	BAIXO,
	ESQUERDA,
}DIRECAO;


typedef struct _tela
{
	COORD dimensao_inicial;
	COORD posicao_inicial;
	COORD dimensao_maxima;
	
}CONSOLE;

/* estrutura que guarda as informações apresentadas na tela */ 

typedef struct _informacao
{
	char *titulo;
	char nome[TAMANHO], direcao[TAMANHO], tecla[TAMANHO]; 
	
}INFO_TELA;

typedef struct _Janela
{
	COORD *ponto1, ref1;
	COORD *ponto2, ref2;
	COORD *centro, refC;
	
	int linha, coluna;
	
}JANELA;

	/*
	|-------------------  quadrado interno -------------|
	|	Nessa estrutura sera armazenada o quadrado		|
	|	que ficara se movimentando no centro 			|
	|	da janela 										|
	|													|
	|---------------------------------------------------|
	*/

typedef struct _quadrado{
	int cor;
	COORD *centro , refCentro;
	
}QUADRADO;

/* -------------------------------------FIM DAS DECLARAÇÕES DAS VARIAVEIS E COSNTANTES-------------------*/ 

/* -------------------------------------DECLARAÇÕES DE FUNCOES-------------------------------------------*/ 
	/*
	|---------------  inicia jogo  -------------------------|
	|	unica funcao fora da ordem alfabetica  				|
	|	essa funcao ira realizar a chamada das outras  		|
	|	funcoes do programa 					 			|
	|-------------------------------------------------------|
	*/
	
void inicia_jogo();

	/*
	|---------------  Cria quadrado ------------------------|
	|	 O qudrado central tera uma configuração  			|
	|	padrão, essa funcção serve para colocar 	  		|
	|	a configuração padrão  					 			|
	|-------------------------------------------------------|
	*/
	
void cria_quadrado(QUADRADO *, JANELA);

	/*
	|---------------  cria ponto ---------------------------|
	|	ira criar os pontos principais a qual 				|
	|	o programa ira utilizar como referencia para 		|
	|	realizar as configurações e movimentações 			|
	|-------------------------------------------------------|
	*/

void cria_ponto(JANELA *, CONSOLE);


void fim_programa();

	/*
	|---------------  Janela ---------------------------|
	|	Ira criar a janela principal do jogo			|
	|		Tamanho da janela e posicao da janela		|
	|		Tamanho Maximo;								|
	|---------------------------------------------------|
	*/	
	
void gerencia_janela(JANELA *, int,CONSOLE);

	/*
	|---------------  movimenta_quadrado ---------------|
	|	 Ira realizar a movimentação do quadrado 		|	
	|	interno do programa								|
	|---------------------------------------------------|
	*/

void movimenta_quadrado(QUADRADO *, JANELA, DIRECAO);

void imprime_informacao(INFO_TELA, CONSOLE);

void imprime_quadrado(QUADRADO, ATIVIDADE);


	/*
	|---------------  Ambiente -------------------------|
	|	Ira criar a definição do prompt do jogo			|
	|		Tamanho da janela e posicao da janela		|
	|		Tamanho Maximo;								|
	|---------------------------------------------------|
	*/
void set_ambiente(CONSOLE *);



void depuracao(JANELA, CONSOLE,int);

/*------------------------------------------FIM DAS DECLARACOES DAS FUNCOES -----------------------------*/ 

#endif /* quadradoAnimado */ 