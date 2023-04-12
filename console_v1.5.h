#ifndef _CONSOLE
#define _CONSOLE

#include<windows.h> /* Estrutura COORD, tipo DWORD e LPSTR */

#define F1 112
#define F2 113
#define F3 114
#define F4 115
#define F5 116
#define F6 117
#define F7 118
#define F8 119
#define F9 120
#define F10 121
#define F11 122
#define F12 123

#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define ESPACO 32
#define TAB 9

/* Enhanced keys */
#define INSERT 45
#define DEL 46
#define PAGE_UP 33
#define PAGE_DOWN 34
#define END 35
#define HOME 36
#define SETA_PARA_ESQUERDA 37
#define SETA_PARA_CIMA 38
#define SETA_PARA_DIREITA 39
#define SETA_PARA_BAIXO 40



/* constantes definidas para identificar a libera��o de um determinado bot�o do mouse */
#define FROM_LEFT_1ST_BUTTON_RELEASED FROM_LEFT_1ST_BUTTON_PRESSED  
#define FROM_LEFT_2ND_BUTTON_RELEASED FROM_LEFT_2ND_BUTTON_PRESSED
#define FROM_LEFT_3RD_BUTTON_RELEASED FROM_LEFT_3RD_BUTTON_PRESSED
#define FROM_LEFT_4TH_BUTTON_RELEASED FROM_LEFT_4TH_BUTTON_PRESSED
#define RIGHTMOST_BUTTON_RELEASED RIGHTMOST_BUTTON_PRESSED

/* dar a op��o ao programador de usar constantes em portugu�s, caso queira */
#define BOTAO_ESQUERDO_PRESSIONADO FROM_LEFT_1ST_BUTTON_PRESSED  
#define BOTAO_ESQUERDO_LIBERADO FROM_LEFT_1ST_BUTTON_RELEASED
#define BOTAO_DIREITO_PRESSIONADO RIGHTMOST_BUTTON_RELEASED      
#define BOTAO_DIREITO_LIBERADO RIGHTMOST_BUTTON_RELEASED

/* constantes utilizadas pela fun��o IdentificarEvento() para definir o nivel 
   de detalhamento das informa��es a serem coletadas de um evento */
#define MINIMO 1
#define MAXIMO 2


/* estrutura para o armazenamento das cores da janela de console */
typedef struct{
               int CorTexto;      /* cor do texto da janela de prompt atual */
			   int CorFundo;      /* cor de fundo da janela de prompt atual */ 
              }CORES;
			  
/* tipo STATUS contendo os valores para ligar e desligar o curso do mouse da tela */ 			  
typedef enum{DESLIGAR, LIGAR} STATUS;

/* tipo VISIBILIDADE */
typedef enum{INVISIVEL, VISIVEL} VISIBILIDADE;

/* tipo que permite identificar que tipo de evento deve ser verificada a exist�ncia no buffer de eventos */
typedef enum{KEYBOARD_HIT, MOUSE_HIT, ALL} TYPE_HIT;

/* Detalhes desta estrutura, ver link:
http://msdn.microsoft.com/en-us/library/windows/desktop/ms684239%28v=vs.85%29.aspx */
typedef struct T_MOUSE{
                         DWORD botao_pressionado; /* FROM_LEFT_1ST_BUTTON_PRESSED, FROM_LEFT_2ND_BUTTON_PRESSED, FROM_LEFT_3RD_BUTTON_PRESSED,
                                                     FROM_LEFT_4TH_BUTTON_PRESSED, RIGHTMOST_BUTTON_PRESSED */
						 DWORD botao_clicou;      /* se o bot�o tiver sido liberado, ap�s ter sido pressionado */
                         COORD posicao; /* coordenadas (em forma de c�lulas de caracteres e n�o de pixels) do cursor do 
						                   mouse em termos do tamanho (em linhas e colunas) do buffer 
										   de console que estiver definido para a janela */
                         DWORD status_teclas_controle; /* CAPSLOCK_ON, ENHANCED_KEY (insert, delete, home, end, pg up, pg downl, 
						                                  setas de dire��o, etc), LEFT_ALT_PRESSED, LEFT_CTRL_PRESSED,
						                                  NUMLOCK_ON, RIGHT_ALT_PRESSED, RIGHT_CTRL_PRESSED, SCROLLLOCK_ON,
														  SHIFT_PRESSED */ 
						 DWORD flags_qual_evento_mouse; /* DOUBLE_CLICK, MOUSE_HWHEELED, MOUSE_MOVED, MOUSE_WHEELED */
                     } MOUSE;					   

/* Detalhes desta estrutura, ver link:					 
http://msdn.microsoft.com/en-us/library/windows/desktop/ms684166%28v=vs.85%29.aspx */
enum T_STATUS_TECLA{LIBERADA, PRESSIONADA};
typedef struct T_TECLADO{
                         enum T_STATUS_TECLA status_tecla; /* LIBERADA ou PRESSIONADA */
						 int codigo_tecla; /* c�digo num�rico que identifica uma tecla independente do tipo do teclado */
                         DWORD status_teclas_controle; /* CAPSLOCK_ON, ENHANCED_KEY (insert, delete, home, end, pg up, pg downl, 
						                                  setas de dire��o, etc), LEFT_ALT_PRESSED, LEFT_CTRL_PRESSED,
						                                  NUMLOCK_ON, RIGHT_ALT_PRESSED, RIGHT_CTRL_PRESSED, SCROLLLOCK_ON,
														  SHIFT_PRESSED */ 						 
                     } TECLADO;
					 
/* Evento que pode ter acontecido e que � identificado pela fun��o Evento() */					 
typedef struct T_EVENTO{
                        WORD tipo_evento; /* pode ser MOUSE_EVENT ou KEY_EVENT */
						TECLADO teclado; /* caso tenha ocorrido um KEY_EVENT, ent�o esta estrutura ser� prenchida
						                    com os dados correspondentes */
						MOUSE mouse;    /* caso tenha ocorrido um MOUSE_EVENT, ent�o esta estrutura ser� prenchida
						                    com os dados correspondentes */
                       }EVENTO;

/* Retorna uma estrutura contendo o tamanho da janela de console atual:
   typedef struct _COORD{
                        SHORT X;   -> Largura da janela 
                        SHORT Y;   -> Altura da janela  
                        } COORD;
                        (
*/
COORD tamanhoJanelaConsole(void);

/* Retorna a resolu��o do monitor em pixels: X = largura e Y = altura */
COORD getResolucaoMonitor(void);

/* Retorna as dimens�es m�ximas poss�veis de uma janela na resolu��o atual do monitor.
   Observa��o: necess�ria fazer uma corre��o na biblioteca do gcc: WINCON.H
               Caso n�o exista a linha, deve adicionar o seguinte prot�tipo no arquivo "wincon.h":
			   BOOL WINAPI GetCurrentConsoleFont(HANDLE, BOOL, PCONSOLE_FONT_INFO);	
               Isso para poder usar essa fun��o da API do Windows GetCurrentConsoleFont().               		   
			        Nota final 1: o arquivo "wincon.h" est� localizado dentro do diret�rio "include"
			        Nota final 2: adicionar dentro do define 
			                      #if (_WIN32_WINNT >= 0x0500)
			                      ...
			                      #endif
*/								  
COORD MaxDimensaoJanela(void);

/* Definir as novas dimens�es da janela atual.
   OBSERVACAO 1: use MaxDimensaoJanela antes de chamar esta fun��o para garantir que n�o passar�
                 valores para largura e altura que extrapolem os valores m�ximos poss�veis   
*/
void setDimensaoJanela(int largura, int altura);

/* Retorna as coordenadas do canto superior esquerdo da janela: COORD campo X = linha superior; COORD campo Y = coluna esquerda */
COORD posicaoJanela(void);

/* Definir a nova posi��o da janela atual */
void setPosicaoJanela(int top, int left);

/* Esconder ou tonar vis�vel a Barra de Tarefas do Windows.
   Valores do par�metro: VISIVEL ou INVISIVEL */
void setEstadoBarraTarefas(VISIBILIDADE);

/* Ler o t�tulo da janela do prompt de comando.
   Retorna um ponteiro para o endere�o da string contendo o t�tulo da janela, ou null se a janela
   n�o tiver um t�tulo   */
char *getTituloConsole(void);

/* Definir um titulo para a janela do prompt de comando.
   Par�metro passado deve conter a string com o novo t�tulo da janela do prompt de comando */
void setTituloConsole(char *);

/* Fun��o que liga ou desliga o cursor piscante na tela */
void setCursorStatus(STATUS);

/* Retornar as cores de fundo e do texto definidas para a janela de prompt atual */
CORES getCoresJanela(void);

/* Retornar se h� algum evento (teclado, mouse, ou redimensionamento da janela) no buffer para ser lido.
   - Se quiser verificar se h� algum evento do teclado aguardando ser lido, passe o par�metro: KEYBOARD_HIT
   - Se quiser verificar se h� algum evento do mouse aguardando ser lido, passe o par�metro: MOUSE_HIT
   - Se quiser verificar se h� qualquer tipo de evento aguardando ser lido, passe o par�metro: ALL   */
int hit(TYPE_HIT);

/* Esta fun��o permite ler tanto uma tecla digitada, quanto o clique do mouse.
   Suponha a seguinte declara��o no seu programa:
   EVENTO e;
   e = Evento();
   Passos que deve executar:
   - Identificar se foi gerado um evento do mouse ou do teclado: 
     if (e.tipo_evento == KEY_EVENT) printf("Foi pressionada uma tecla");
	 if (e.tipo_evento == MOUSE_EVENT) printf("Foi gerado um evento do mouse (clique, movimenta��o, etc.)");
	          Observa��o: maiores informa��es pode obter no link: http://msdn.microsoft.com/en-us/library/windows/desktop/ms684961%28v=vs.85%29.aspx (fun��o ReadConsoleInput())
		                  e http://msdn.microsoft.com/en-us/library/windows/desktop/ms683499%28v=vs.85%29.aspx (estrutura INPUT_RECORD).
   - Com base nessa identifica��o do evento gerado, a estrutura EVENTO tem todas as informa��es a respeito dele.
     Por exemplo, vamos analisar as informa��es que s�o coletadas para as duas situa��es identific�veis 
	 por esta fun��o: 1) evento do mouse; 2) evento do teclado.
     1) Evento do mouse. 
        - Guarda a posi��o da janela de console em que o evento ocorreu (COORD posicao);
		- Guarda se o evento foi o pressionamento de algum dos bot�es do mouse (DWORD botao_pressionado);
		- Guarda se o evento foi a libera��o de algum dos bot�es do mouse que previamente estavam pressionados, 
		  completando um clique (DWORD botao_clicou)
		  OBSERVA��O: s� d� suporte a identifica��o de cliques de mouses com at� 3 bot�es. Mouses com mais bot�es
		              � necess�rio estender o c�digo desta fun��o (API d� suporte ao reconhecimento de at� 5 bot�es).
		- Guarda se alguma das teclas de controle estava pressionada quando se deu o evento com o mouse 
		  (DWORD status_teclas_controle)
		- Guarda qual o tipo de evento que aconteceu (DWORD flags_qual_evento_mouse)
     2) Evento do teclado.
	    - Guarda o c�digo da tecla pressionada (int codigo_tecla);
		- Guarda o status da tecla: LIBERADA ou PRESSIONADA (enum T_STATUS_TECLA status_tecla);
        - Guarda se alguma das teclas de controle estava pressionada (DWORD status_teclas_controle)		
*/
EVENTO Evento(void);

/* fun��o que apresenta o detalhamento completo de todas as informa��es poss�veis de serem
   coletadas sobre um determinado evento ocorrido, cuja origem seja, ou o teclado, ou o mouse */
void IdentificarEvento(EVENTO, int);

/* imprime a mensagem LPSTR (ponteiro para uma string) no fluxo de erro (stderr) e encerra o programa */
void ErrorExit (LPSTR); 
#endif
