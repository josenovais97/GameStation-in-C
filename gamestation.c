// Funções e código do jogo Snake
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>

void mgotoxy(int x, int y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x, y});
}

void verRecordes(void)
{
    system("cls");
    char texto_str[20];
    FILE *arquivo = fopen("recordes.txt", "r");

    if (arquivo != NULL) {
        printf("Listando:\n");
        while (fgets(texto_str, 20, arquivo) != NULL) {
            printf("%s", texto_str);
        }

        fclose(arquivo);
    } else {
        printf("Nenhum recorde registrado!\n");
    }

    getch();
}

void snakeGame()
{
    // Código do jogo Snake
    // ...

    system("cls");
    int x, d = 2, cx[300] = {1, 2}, cy[300] = {7, 7}, t = 1, mx, my, velo = 100, velo2 = 5;

    char tecla = 'a';
    int opcao;
    int pontos = 0;
for(x=0;x<18;x++)
 { mgotoxy(0,x); //vertical esquerda.//
 
 printf("%c",219);
 }
 for(x=0;x<50;x++)
 { mgotoxy(x,0); //horizontal ssuperior//
 printf("%c",219);
 }
 for(x=0;x<18;x++)
 { mgotoxy(50,x); //vertical direita//
 printf("%c",219);
 }
 for(x=0;x<51;x++)
 { mgotoxy(x,18); //horizontal inferior.//
 printf("%c",219);
 }
 
    void mostrarGameOver(int pontos) {
        // Implemente a função mostrarGameOver se necessário
    }

    srand(time(NULL));
    mx = (rand() % 49) + 1;
    my = (rand() % 17) + 1;

    velo = 200;

    // Ler o high score do arquivo
    int highScore = 0;
    FILE *arquivo = fopen("recordes.txt", "r");
    if (arquivo != NULL) {
        fscanf(arquivo, "%d", &highScore);
        fclose(arquivo);
    }

    while (tecla != 's') {
        while (tecla != 's' && !(tecla = kbhit())) {
            for (x = t; x > 0; x--) {
                cx[x] = cx[x - 1];
                cy[x] = cy[x - 1];
            }

            if (d == 0)
                cx[0]--;
            if (d == 1)
                cy[0]--;
            if (d == 2)
                cx[0]++;
            if (d == 3)
                cy[0]++;

            mgotoxy(cx[t], cy[t]);
            printf(" ");
            if (mx == cx[0] && my == cy[0]) {
                t++;
                pontos++;
                mx = (rand() % 25) + 1;
                my = (rand() % 17) + 1;
                velo -= 5;
                velo2 += 5;
            }

            mgotoxy(cx[0], cy[0]);
            printf("%c", 219);

            mgotoxy(mx, my);
            printf("%c", 1);
            mgotoxy(55, 10);

            printf("Pontos: %d", pontos);
            mgotoxy(55, 5);
            printf("Velocidade: %d", velo2);
            mgotoxy(3, 22);

            printf("\nTrabalho Pratico Algoritmos");
            mgotoxy(5, 24);
            printf("\nHigh score: %d", highScore);
            Sleep(velo);
            for (x = 1; x < t; x++) {
                if (cx[0] == cx[x] && cy[0] == cy[x])
                    tecla = 's';
                mostrarGameOver(pontos);
            }
            if (cy[0] == 0 || cy[0] == 18 || cx[0] == 0 || cx[0] == 50)
                tecla = 's';
            mostrarGameOver(pontos);
        }
        if (tecla != 's')
            tecla = getch();
        if (tecla == 'K')
            d = 0;
        if (tecla == 'H')
            d = 1;
        if (tecla == 'M')
            d = 2;
        if (tecla == 'P')
            d = 3;
        if (cy[0] == 0 || cy[0] == 18 || cx[0] == 0 || cx[0] == 26)
            tecla = 's';
        mostrarGameOver(pontos);
    }

    // Salvar o high score
    if (pontos > highScore) {
        highScore = pontos;
        arquivo = fopen("recordes.txt", "w");
        if (arquivo != NULL) {
            fprintf(arquivo, "%d", highScore);
            fclose(arquivo);
        }
    }

    system("cls");
    system("pause");
	printf ("\n\n\tGAME OVER\n\n");
    printf("\n\n\tConseguiste %d Pontos", pontos);
    getch();
}





// Funções e código do jogo Forca

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PAL 100

typedef struct jogador_s {
    char palavra[300];
    struct jogador_s* seg;
} jogador_t;

jogador_t* insere_lista(jogador_t contem, jogador_t* p) {
    jogador_t* aux, * aux1;
    aux = p;

    if (p == NULL) {
        p = (jogador_t*)malloc(sizeof(jogador_t));
        *p = contem;
        p->seg = NULL;
        return p;
    }

    while (aux->seg != NULL) {
        aux = aux->seg;
    }

    aux1 = (jogador_t*)malloc(sizeof(jogador_t));
    *aux1 = contem;
    aux->seg = aux1;
    aux1->seg = NULL;
    return p;
}

jogador_t* pede_dados(jogador_t* p) {
    jogador_t novo;

    printf("Inserir palavra: ");
    scanf("%s", novo.palavra);

    p = insere_lista(novo, p);
    printf("Foi adicionado com sucesso!\n\n");
    return p;
}

jogador_t* alterar(jogador_t* p) {
    jogador_t novo, velho;
    jogador_t* aux;
    int cont = 0;
    aux = p;

    do {
        cont = 0;
        p = aux;
        printf("Introduza a palavra que pretende alterar:");
        scanf("%s", velho.palavra);

        while (p != NULL) {
            if (strcmp(p->palavra, velho.palavra) == 0) {
                cont++;
            }
            p = p->seg;
        }

        if (cont == 0) {
            printf("Palavra nao existe!\n");
        }
    } while (cont != 1);

    p = aux;

    printf("Insira a palavra nova: ");
    scanf("%s", novo.palavra);

    while (p != NULL) {
        if (strcmp(p->palavra, velho.palavra) == 0) {
            strcpy(p->palavra, novo.palavra);
        }
        p = p->seg;
    }

    p = aux;
    printf("Alterado com sucesso!\n");
    return p;
}

void mostra(jogador_t* p) {
    if (p == NULL) {
        printf("Lista esta vazia!\n");
        return;
    }

    while (p != NULL) {
        printf("%s\n", p->palavra);
        p = p->seg;
    }
}

jogador_t* le_ficheiro(jogador_t* p, char ficheiro[]) {
    jogador_t existe;
    FILE* f;
    f = fopen(ficheiro, "rb");

    if (f == NULL) {
        printf("Erro ao abrir o ficheiro, tente novamente!\n\n");
        return p;
    }

    while (fread(&existe, sizeof(jogador_t), 1, f) > 0) {
        p = insere_lista(existe, p);
    }

    fclose(f);
    return p;
}

void guardar(jogador_t* p, char ficheiro[]) {
    FILE* f;
    jogador_t* aux;

    f = fopen(ficheiro, "wb");

    if (f == NULL) {
        printf("Erro ao abrir o ficheiro, tente novamente!\n\n");
        return;
    }

    aux = p;

    while (aux != NULL) {
        fwrite(aux, sizeof(jogador_t), 1, f);
        aux = aux->seg;
    }

    fclose(f);
    printf("Guardado com sucesso!\n\n");
}

void jogar(jogador_t* p) {
    int i, j, contador = 0, random, letras = 0, acertos = 0;
    char secreta[300], teste[300], palavra[300], carater;

    jogador_t* aux;

    aux = p;

    srand(time(NULL));

    while (aux != NULL) {
        contador++;
        aux = aux->seg;
    }

    random = rand() % contador;

    for (i = 0; i < random; i++) {
        p = p->seg;
    }

    strcpy(secreta, p->palavra);

    letras = strlen(secreta);

    for (i = 0; i < letras; i++) {
        teste[i] = '_';
    }

    teste[i] = '\0';

    printf("A palavra secreta tem %d letras.\n", letras);

    while (acertos != letras) {
        printf("\n\nA palavra a advinhar é: %s", teste);
        printf("\n\nEscreva uma letra: ");
        scanf(" %c", &carater);

        for (j = 0; j < letras; j++) {
            if (secreta[j] == carater) {
                acertos++;
                teste[j] = carater;
            }
        }
    }

    printf("\n\nParabens, a palavra era %s!\n\n", teste);
}

void ForcaGame(){
    jogador_t* lista = NULL;
    int opcao;
    char ficheiro[PAL];

    printf("Nome do ficheiro onde pretende guardar a lista de palavras: ");
    scanf("%s", ficheiro);

    lista = le_ficheiro(lista, ficheiro);

    do {
        printf("Escolha uma opcao:\n");
        printf("1 - Adicionar palavra a lista\n");
        printf("2 - Alterar palavra da lista\n");
        printf("3 - Mostrar lista\n");
        printf("4 - Jogar\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                lista = pede_dados(lista);
                break;
            case 2:
                lista = alterar(lista);
                break;
            case 3:
                mostra(lista);
                break;
            case 4:
                jogar(lista);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n\n");
        }
    } while (opcao != 0);

    guardar(lista, ficheiro);

    return 0;
}


// Funções e código do jogo Blackjack
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int shuff(int cards[])
{
	
	int t;
	int i;
	int desk[52];	
	for (i=0;i<52;i++)
		desk[i] = (i/13+3)*100 + i%13 + 1;

	srand(time(NULL));
	for (i = 0; i < 52; i++)
	{
		do
		{
			t = rand() % 52;
		} while (desk[t] == 0);
		cards[i] = desk[t];
		desk[t] = 0;
	}
	
	return 0;
}

int convert_jkq(int a)
{
	if ((a%100==11) ||(a%100==12) ||(a%100==13)) return (a/100)*100+10;
	else return a;
}

void pic(int num)
{
	char fl;
	int po_num;
	
	fl = num / 100;
	po_num = num % 100;
	switch (po_num)
	{
		case 1: 
		{
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", fl);
			printf("*   A *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		{
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", fl);
			printf("*  %2d *\n", po_num);
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		case 11:
		{
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", fl);
			printf("*   J *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		case 12:
		{
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", fl);
			printf("*   Q *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		case 13:
		{
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", fl);
			printf("*   K *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}

	}
}

int play(void)
{
	int i;
	int psum=0;
	int bsum=0;
	int pcards[5]={0};
	int bcards[5]={0};
	int cards[52];
	char go_on;
	char d;
	printf("\n _____\n|A _  |\n| ( ) |\n|(_'_)|\n|  |  |\n|____A|\n");
	printf("Bem vindo ao Blackjack!\n"
	"Pressiona Ctrl+C para Sair.\n");
	do{
		go_on = getchar();
	} while (go_on != '\n');
	printf("\n");
	
	//baralha as cartas
	shuff(cards);

	//da as cartas
	pcards[0]=cards[0];
	pcards[1]=cards[1];
	bcards[0]=cards[2];
	bcards[1]=cards[3];
	
	//o segundo jogardor tem:
	printf("Uma das cartas do computador\n");
	pic(bcards[0]);
	printf("\n");
	printf("As tuas cartas:\n");
	pic(pcards[0]);
	pic(pcards[1]);
	
	i=0;
	for (i=0; i<2; i++)
	{
		if (pcards[i]%100 == 1)
		{
			printf("Saiu um AS, pressiona 's' para tomar o valor de 11 ou 'n' para tomar o valor de 1 :\n", i+1);
			do{
				d = getchar();
			} while (d!='s' && d!='n');
			
			if (d == 's')
			{
				printf("Escolheste o valor de 11 para o As.\n");
				psum = psum + 11;
			}
			else if(d == 'n')
			{
				printf("Escolheste o valor de 1 para o As.\n");
				psum = psum +1;
			}
		}
		else if (convert_jkq(pcards[i]) %100 ==10) psum = psum + 10;
		else psum = psum + pcards[i]%100;
		
		if (psum > 21)
		{
			printf("Soma das tuas cartas:%d\n\n",psum);
			printf("Perdeste!\n");
			return 1;
		}
		else if (psum == 21)
		{
			printf("Soma das tuas cartas:%d\n\n",psum);
			printf("Ganhaste\n");
			return 0;
		}
	}
	printf("Soma das tuas cartas:%d\n\n",psum);
	
	//Queres mais cartas?
	i=0;
	for (i=0; i<3; i++)
	{
		char j = 'n';
		
		printf("Queres mais cartas? Pressiona s ou n:\n");
		do{
			j = getchar();
		} while (j!='s' &&j!='n');
		
		if (j=='s')
		{
			printf("Pediste outra carta.\n");
			pcards[i+2]=cards[i+4];
			printf("e a tua carta %d e:\n", i+3);
			pic(pcards[i+2]);
			
			if (pcards[i+2]%100 == 1)
			{
				printf("Saiu um AS, pressiona 's' para tomar o valor de 11 ou 'n' para tomar o valor de 1 :", i+3);
				do{
					d = getchar();
				} while (d!='s' && d!='n');	
				if (d == 's')
				{
					printf("Escolheste o valor de 11 para o As.\n");
					psum = psum + 11;
				}
				else if(d == 'n')
				{
					printf("Escolheste o valor de 1 para o As.\n");
					psum = psum +1;
				}
			}
			else if (convert_jkq(pcards[i+2]) %100 ==10) psum = psum + 10;
			else psum = psum + pcards[i+2]%100;
			
			if (psum > 21)
			{
				printf("Soma das tuas cartas:%d\n\n",psum);
				printf("O computador ganhou!\n");
				return 1;
			}
			else if (psum == 21)
			{
				printf("Soma das tuas cartas:%d\n\n",psum);
				printf("Ganhaste!\n");
				return 0;
			}		
			else printf("Soma das tuas cartas:%d\n\n",psum);
		}
		else 
		{
			printf("Soma das tuas cartas:%d\n\n",psum);
			break;
		}
	}
	if (i == 3)
	{
		printf("Ganhaste! Porque a soma das tuas cartas nao e superior a 21! Que sortudo!\n");
		return 0;
	}
	
	//As duas cartas do computador
	//i=0;
	printf("Cartas do computador:\n");
	pic(bcards[0]);
	pic(bcards[1]);

	if (bcards[0]%100 + bcards[1]%100 == 2)
	{
		bsum=12; //two A cards
		printf("A soma das cartas do computador e:%d\n\n", bsum);
	}
	else if ((convert_jkq(bcards[0]))%100 + (convert_jkq(bcards[1]))%100 ==1)
	{
		bsum=21;
		printf("A soma das cartas do computador e:%d\n\n", bsum);
		printf("O computador ganhou!\n");
		return 1;
	}
	else if (bcards[0]%100==1 || bcards[1]%100==1)
	{
		bsum=(bcards[0]+bcards[1])%100+(rand()%2)*10;
		printf("A soma das cartas do computador e:%d\n\n", bsum);
	}
	else
	{
		bsum = (convert_jkq(bcards[0]))%100 + (convert_jkq(bcards[1]))%100;
		printf("A soma das cartas do computador e:%d\n\n", bsum);
	}
	
	//O computador pede mais cartas até que a soma seja menor do que 16
	//i=0;
	for (i=0; i<3 && bsum<17; i++)
	{
		bcards[i+2]=cards[i+7];
		printf("A carta do Computador %d e:\n", i+3);
		pic(bcards[i+2]);
		
		if (bcards[i+2]%100 == 1)
		{
			if (bsum+11 <= 21)
			{
				printf("O computador escolheu A como 11\n");
				bsum = bsum+11;
				printf("A soma das cartas do computador e:%d\n\n", bsum);
			}
			else
			{
				printf("O computador escolheu A como 1\n");
				bsum = bsum+1;
				printf("A soma das cartas do computador e:%d\n\n", bsum);
			}
		}
		else
		{
			bsum = bsum + convert_jkq(bcards[i+2])%100;
			printf("A soma das cartas do computador e:%d\n\n", bsum);
		}
	}
	if (i == 3)
	{
		printf("o computador ganhou! Porque a soma das cartas dele nao e superior a 21! Que sortudo!\n");
		return 1;
	}
	
	//O vencedor
	if (bsum>21 || psum>bsum)
	{
		printf("Ganhaste!\n");
		return 0;
	}
	else if (psum == bsum)
	{
		printf("Oh, ficaste com a mesma pontuacao que o computador!\n");
		return 3;
	}
	else if (psum < bsum)
	{
		printf("O computador ganhou!\n");
		return 1;
	}
		
	return 3;
}

void blackjackGame() {
    // Código do jogo Blackjack
    // ...
	{
	char again;
  
	play();
  
	printf("\nPressiona 's' para sair.\n");
	do{
		again = getchar();
	} while (again!='s');
   
  
	return 0;
}
}
int main() {
    int choice;

    do {
		printf("\n");	
	printf("\t\t    _________         _________ 			\n");	
	printf("\t\t   /          )      /          ) 			\n");	
	printf("\t\t  /  /~~~~~|  |     /  /~~~~~|  | 			\n");	
	printf("\t\t  |  |     |  |     |  |     |  | 			\n");		
	printf("\t\t  |  |     |  |     |  |     |  | 			\n");
	printf("\t\t  |  |     |  |     |  |     |  |      /	\n");
	printf("\t\t  |  |     |  |     |  |     |  |     //	\n");
	printf("\t\t (o  o)    (  |_____/  /     (  |____/ / 	\n");
	printf("\t\t  (__/      (         /       (        / 	\n");
	printf("\t\t    |        ~~~~~~~~~         ~~~~~~~~ 		\n");
	printf("\t\t    ^											\n");
			printf("\t\t**************************************\n");
    		printf("\t\t*        Trabalho Pratico AED        *\n");
			printf("\t\t*           Jose Novais              *\n");
    		printf("\t\t*          Miguel Machado            *\n");
 			printf("\t\t*           Tiago Diogo              *\n");
    		printf("\t\t**************************************\n");
	
        printf("Escolha o jogo:\n");
        printf("1. Snake\n");
        printf("2. Forca\n");
        printf("3. Blackjack\n");
        printf("0. Sair\n");
        printf("Digite o numero correspondente ao jogo: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                snakeGame();
                break;
            case 2:
                ForcaGame();
                break;
            case 3:
                blackjackGame();
                break;
            case 0:
                printf("A sair...\n");
                break;
            default:
                printf("Opcao invalida. Por favor, escolhe novamente.\n");
                break;
        }

        printf("\n");
    } while (choice != 0);

    return 0;
}