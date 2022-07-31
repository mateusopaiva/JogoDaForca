#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h"
#include <locale.h>

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;
char letras[26];

int letraexiste(char letra) {

    for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}

int chuteserrados() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {

        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

int enforcou() {
    return chuteserrados() >= 5;
}

int ganhou() {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}

void abertura() {
    printf("\n\tJogo de Forca\n");
    printf("\tTema: Frutas\n\n");
    
}

void chuta() {
    char chute;
    printf("\tQual letra maiúscula? ");
    scanf(" %c", &chute);

    if(letraexiste(chute)) {
        printf("\tVocê acertou: a palavra tem a letra %c\n\n", chute);
    } else {
        printf("\tVocê errou: a palavra Não tem a letra %c\n\n", chute);
    }
	
    chutes[chutesdados] = chute;
    chutesdados++;
    
    letras[chutesdados] = chute;
}

int jachutou(char letra) {
    int achou = 0;
    for(int j = 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

void desenhaforca() {

    int erros = chuteserrados();
    printf("\t  _______       \n");
    printf("\t |/      |      \n");
    printf("\t |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf("\t |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf("\t |       %c     \n", (erros>=2?'|':' '));
    printf("\t |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf("\t |              \n");
    printf("\t_|___           \n");
    printf("\n\t");

    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
		
    }
    printf("\n");

}

void escolhepalavra() {
    FILE* f;

    f = fopen("palavras.txt", "r");
    if(f == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

void adicionapalavra() {
    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo (S/N)?");
    scanf(" %c", &quer);

    if(quer == 'S') {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra, em letras maiúscula: ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);

    }

}

void vitoria() {
	printf("\n\tParabéns, você ganhou!\n\n");
	printf("\tA palavra era %s\n\n", palavrasecreta);

	printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
}

void derrota() {
	printf("\n\tPuxa, você foi enforcado!\n");
        printf("\tA palavra era %s\n\n", palavrasecreta);

        printf("       _______________         \n");
        printf("      /               \\       \n"); 
        printf("     /                 \\      \n");
        printf("   //                   \\/\\  \n");
        printf("   \\|   XXXX     XXXX   | /   \n");
        printf("    |   XXXX     XXXX   |/     \n");
        printf("    |   XXX       XXX   |      \n");
        printf("    |                   |      \n");
        printf("    \\__      XXX      __/     \n");
        printf("      |\\     XXX     /|       \n");
        printf("      | |           | |        \n");
        printf("      | I I I I I I I |        \n");
        printf("      |  I I I I I I  |        \n");
        printf("      \\_             _/       \n");
        printf("        \\_         _/         \n");
        printf("          \\_______/           \n");
}

void letraschutes() {
	printf("\nSeus chutes foram: ");
	for(int i = 0; i <= chutesdados; i ++) {
		printf("%c ", letras[i]);
	}
	printf("\n");
}

int main() {
	setlocale(LC_ALL, "Portuguese");
    abertura();
    escolhepalavra();

    do {
        desenhaforca();
        chuta(); 
        letraschutes();
        

    } while (!ganhou() && !enforcou());

    if(ganhou()) {
        vitoria();

    } else {
        derrota();
    }
    

    //adicionapalavra();
}
