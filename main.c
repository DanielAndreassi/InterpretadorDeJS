#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include <conio2.h> 
//#include "conio_linux.h"
#include "listagen.h"
#include "pilhaVariaveis.h"
#include "fila.h"
//pode ser declarado mais TAD's caso tenha necessidade

//estrutura principal
struct pProgama {
    pToken *tokens;
    pProgama *proximo, *anterior;
}; typedef pProgama *pProgama;

//estrutura que guarda os tokens do arquivo JS
struct pToken {
    pToken *proximo;
    char tokens[40];
}; typedef pToken *pToken;

//descritor da estrutura principal para facilitar algumas coisas
struct descritorPrograma {
    pProgama *inicio, *fim;
}; typedef struct descritorPrograma DescritorPrograma;

//descritor da estrutura de tokens
struct descritorToken {
    pToken *inicio, *fim;
}; typedef struct descritorToken DescritorToken;

//declarar funcoes (ate o momento tudo esta com void mas pode ser modificado, so sera necessario mudar aqui na declaracao)
//declarando para que tenha uma melhor organizacao das funcoes sem precisar ficar procurando elas para entendelas
//separar elas em partes, moldura, teclas, execucao, tratamento e etc
void mostrarErroNoArquivo(); //mostrar na tela que nao deu certo abrir o arquivo e voltar a tela incial
void molduraInicial (); //moldura de tela
void molduraTerminal(); //moldura do terminal
void molduraDaPilha(); //moldura da pilha de variaveis
void abrirArquivoF7();// procurar o asc dos F* e anotar;
void terminalF10(); //simula um terminal mostrando os "console.log()"
void mostrarMemoriaF9(); //exibi a pilha de variaveis do programa
void executarProgramaF8(); //executa tudo passa a passo sem que o usuario precise dar enter para cada linha
void executarLinhaENTER(); // executa a linha que o usuario esta
void montarEstruturaPrincipal (FILE *arquivo, pProgama **lista); // ira abrir um arquivo JS e ira montar a estrutura pPrograma e pTokens e fechar o arquivo
void limparListas(DescritorPrograma **descritorPrograma,DescritorToken **descritorToken,PilhaVariaveis **PilhaVariaveis); //limpa pPrograma e pTokens
//as duas estruturas tem descritor, usalos sempre;


//usar quando precisar limpar toda a estrutura
void limparListas(DescritorPrograma **descritorPrograma,DescritorToken **descritorToken,PilhaVariaveis **pilha) {
    pProgama *auxPrograma = (*descritorPrograma)->inicio,*limpaPrograma;
    pToken  *auxTokens = (*descritorToken)->inicio,*limpaToken;

    if(auxPrograma) {
        while(auxPrograma != NULL) {
        
        while(auxTokens != NULL) {
            limpaToken = auxTokens;
            auxTokens = auxTokens->proximo;
            free(limpaToken);
        }
        limpaPrograma = auxPrograma;
        auxPrograma = auxPrograma->proximo;
        free(limpaPrograma);
        auxTokens = auxPrograma->tokens;
        }
        limparPilha(&*pilha);
    }
    else printf("Listas ja vazias");
}

void abrirArquivoF7(pProgama **lista) {
    char nomeArq[50];
    printf("Digite o nome do arquivo que desaja abrir: \n");
    gets(nomeArq);

    FILE *ponteiroArquivo = fopen(nomeArq,""); //colocar um tipo que abra se tiver e deixe editar mas nao crie caso nao tenha

    if(ponteiroArquivo)
        montarEstruturaPrincipal(ponteiroArquivo,&*lista);
    else 
        mostrarErroNoArquivo(); 

}
void montarEstruturaPrincipal (FILE *arquivo, pProgama **lista) {
    
}

int main () {
    //a ideia sera deixar o usuario escrever o nome do arquivo antes de abrir, nao ficar algo fixo, ele so  poderar buscar na pasta onde ta o projeto;

    return 0;
}
