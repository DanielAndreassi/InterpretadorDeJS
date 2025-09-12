#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include <conio2.h> 
//#include "conio_linux.h"
#include "listagen.h"
#include "pilhaVariaveis.h"
//#include "fila.h"
//pode ser declarado mais TAD's caso tenha necessidade


//estrutura que guarda os tokens do arquivo JS
struct pToken {
    pToken *proximo;
    char tokens[40];
}; typedef pToken pToken;
//estrutura principal
struct pProgama {
    pToken *tokens;
    pProgama *proximo, *anterior;
}; typedef pProgama pProgama;

//descritor da estrutura principal para facilitar algumas coisas
struct descritorPrograma {
    pProgama *inicio, *fim;
}; typedef struct descritorPrograma DescritorPrograma;

//descritor da estrutura de tokens
struct descritorToken {
    pToken *inicio, *fim;
}; typedef struct descritorToken DescritorToken;


//estrutura para ler o arquivo
struct arquivoJS {
    char linha[50];
}; typedef struct arquivoJS ArquivoJS;
//as duas estruturas tem descritor, usalos sempre;

//declarar funcoes (ate o momento tudo esta com void mas pode ser modificado, so sera necessario mudar aqui na declaracao)
//declarando para que tenha uma melhor organizacao das funcoes sem precisar ficar procurando elas para entendelas
//separar elas em partes, moldura, teclas, execucao, tratamento e etc
void mostrarErroNoArquivo(FILE *ponteiroArquivo); //mostrar na tela que nao deu certo abrir o arquivo e voltar a tela incial
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


//novas funcoes ver com fefe como ele quer seguir // ainda precisa ser ajustado tudo, algumas funcoes de cima foram depreciadas, e algumas aqui precisa ser trocado o parametro
pProgama* criarNoPrograma();
pToken* criarToken(char *valor);
void adicionarLinhaPrograma(DescritorPrograma *prog, DescritorToken *tokens);
int ehPalavraChave(char *palavra);
int verificarOperadorDuplo(char *linha, int i, char *operador);
int pularEspacos(char *linha, int i);
int processarString(char *linha, int i, DescritorToken *descToken);
int processarNumero(char *linha, int i, DescritorToken *descToken);
int processarPalavra(char *linha, int i, DescritorToken *descToken);
void tokenizarLinha(char *linha, DescritorPrograma *prog, int *nivelChaves);
void imprimirPrograma(DescritorPrograma *prog);
DescritorPrograma* tokenizarArquivo(ArquivoJS *arquivo, int numLinhas);
void liberarTokens(pToken *inicio);
void liberarPrograma(DescritorPrograma *prog);
void testarTokenizador();
void adicionarToken(DescritorToken *descritor, char *valor);



//usar quando precisar limpar toda a estrutura para abrir outro arquivo
void limparListas(DescritorPrograma **descritorPrograma,DescritorToken **descritorToken,PilhaVariaveis **pilha) {
    pProgama *auxPrograma = (*descritorPrograma)->inicio,*limpaPrograma;
    pToken  *auxTokens = (*descritorToken)->inicio,*limpaToken;
    //usar as outras funcoes pra limpar essa aqui sera mudada
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
        //ainda precisar limpar os descritores
    }
    else printf("Listas ja vazias");
}

void mostrarErroNoArquivo(FILE *ponteiroArquivo) {
    //essa funcao montara uma tela e exibira o erro que foi encontrada ao abrir o arquivo
}

void abrirArquivoF7(pProgama **lista) {
    char nomeArq[50];
    printf("Digite o nome do arquivo que desaja abrir: \n");
    gets(nomeArq);

    FILE *ponteiroArquivo = fopen(nomeArq,"r"); //colocar um tipo que abra se tiver e deixe editar mas nao crie caso nao tenha

    /*if(ponteiroArquivo)
        //montarEstruturaPrincipal(ponteiroArquivo,&*lista);
    else 
        mostrarErroNoArquivo(ponteiroArquivo); 
    */

}

//essa funcao ta por enquanto somente pegando as linhas do arquivo, ela ainda precisa chamar a tokenizarArquivo
void montarEstruturaPrincipal (FILE *arquivo,DescritorPrograma  **lista) {
    int i = 0,len;
    ArquivoJS linha[100];

    while(!feof(arquivo) && i<100) {

        fscanf(arquivo,"%[^\n]\n",linha[i].linha);

        len = strlen(linha[i].linha);
        
        if(len > 0 && linha[i].linha[len-1] == '\n')
            linha[i].linha[len-1] = '\0';
    
        printf("%s\n",linha[i].linha);
        i++;
    }

    *lista = tokenizarArquivo(linha,i);
    fclose(arquivo);
}

void iniciarDescritores(DescritorPrograma **descritorListaPrograma,DescritorToken **descritorListaToken) {
    if(descritorListaPrograma) {
        *descritorListaPrograma = (DescritorPrograma *)malloc(sizeof(DescritorPrograma));
        *descritorListaToken = (DescritorToken *)malloc(sizeof(DescritorToken));
    }
    else 
        printf("Descritores ja inicializado");
    
}

//criando funcoes para separar string 
//usar referencia?
pProgama* criarNoPrograma() {
    pProgama *novo = (pProgama*)malloc(sizeof(pProgama));
    if (novo != NULL) {
        novo->tokens = NULL;
        novo->proximo = NULL;
        novo->anterior = NULL;
    }
    return novo;
}
//referencia eh melhor?
pToken* criarToken(char *valor) {
    pToken *novo = (pToken*)malloc(sizeof(pToken));
    strcpy(novo->tokens, valor);
    novo->proximo = NULL;
    return novo;
}

// funcao para adicionar linha tratada nas listas
void adicionarLinhaPrograma(DescritorPrograma *prog, DescritorToken *tokens) {
    if (tokens->inicio != NULL) {
        pProgama *novo = criarNoPrograma();
        if (novo != NULL) {
            novo->tokens = tokens->inicio;
            
            if (prog->inicio == NULL) {
                prog->inicio = novo;
                prog->fim = novo;
            } else {
                novo->anterior = prog->fim;
                prog->fim->proximo = novo;
                prog->fim = novo;
            }
        }
    }
}

// funcao para verificar se é palavra-chave(loop, declaracao, funcao de array etc, pode ser adicionado mais ainda nao tenh certeza se tem tudo) do JavaScript
int ehPalavraChave(char *palavra) {
    char *palavrasChave[] = {
        "function", "return", "let", "const", "var",
        "if", "else", "while", "do", "for",
        "console.log", "parseInt", "toString", "sort",
        "push", "pop", "shift", "unshift", "length"
    };
    int total = 19;
    int i = 0;
    
    while (i < total) {
        if (strcmp(palavra, palavrasChave[i]) == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}

// funcao para verificar se eh operador de dois caracteres
int verificarOperadorDuplo(char *linha, int i, char *operador) {
    // Operadores de comparacao e logicos de 2 caracteres
    if (linha[i] == '=' && linha[i+1] == '=') {
        strcpy(operador, "==");
        return 2;
    }
    if (linha[i] == '!' && linha[i+1] == '=') {
        strcpy(operador, "!=");
        return 2;
    }
    if (linha[i] == '>' && linha[i+1] == '=') {
        strcpy(operador, ">=");
        return 2;
    }
    if (linha[i] == '<' && linha[i+1] == '=') {
        strcpy(operador, "<=");
        return 2;
    }
    if (linha[i] == '&' && linha[i+1] == '&') {
        strcpy(operador, "&&");
        return 2;
    }
    if (linha[i] == '|' && linha[i+1] == '|') {
        strcpy(operador, "||");
        return 2;
    }
    if (linha[i] == '*' && linha[i+1] == '*') {
        strcpy(operador, "**");
        return 2;
    }
    if (linha[i] == '+' && linha[i+1] == '+') {
        strcpy(operador, "++");
        return 2;
    }
    if (linha[i] == '-' && linha[i+1] == '-') {
        strcpy(operador, "--");
        return 2;
    }
    
    // operador simples (nao sei de pode usar o srtchr ver com chico)
    
    if (strchr("+-*/%(){}[]<>=!,.", linha[i]) != NULL) {
        operador[0] = linha[i];
        operador[1] = '\0';
        return 1;
    }
    
    return 0;
}

// ignora espaços em branco nao precisa estar na list a gente so tem que tratar na exibicao toda vez que for um prox coloca um " " no DOS
int pularEspacos(char *linha, int i) {
    while (linha[i] == ' ' || linha[i] == '\t' || linha[i] == '\r') {
        i++;
    }
    return i;
}

// Função para processar string entre aspas
int processarString(char *linha, int i, DescritorToken *descToken) {
    char tipoAspas = linha[i];
    char token[40];
    int j = 0;
    
    token[j++] = linha[i++];
    
    while (linha[i] != '\0' && linha[i] != tipoAspas && j < 38) {
        token[j++] = linha[i++];
    }
    
    if (linha[i] == tipoAspas) {
        token[j++] = linha[i++];
    }
    
    token[j] = '\0';
    adicionarToken(descToken, token);
    
    return i;
}


int processarNumero(char *linha, int i, DescritorToken *descToken) {
    char token[40];
    int j = 0;
    
    // Capturar dígitos e ponto decimal
    while ((isdigit(linha[i]) || linha[i] == '.') && j < 39) {
        token[j++] = linha[i++];
    }
    
    token[j] = '\0';
    adicionarToken(descToken, token);
    
    return i;
}
// Função para processar identificador ou palavra-chave
int processarPalavra(char *linha, int i, DescritorToken *descToken) {
    char token[40];
    int j = 0;
    
    // Verificar se é console.log
    if (strncmp(&linha[i], "console.log", 11) == 0) {
        adicionarToken(descToken, "console.log");
        return i + 11;
    }
    
    // Capturar letras, números e underscore
    while ((isalnum(linha[i]) || linha[i] == '_' || linha[i] == '.') && j < 39) {
        token[j++] = linha[i++];
    }
    
    token[j] = '\0';
    
    if (j > 0) {
        adicionarToken(descToken, token);
    }
    
    return i;
}


// Função principal para tokenizar uma linha
void tokenizarLinha(char *linha, DescritorPrograma *prog, int *nivelChaves) {
    DescritorToken *descToken = (DescritorToken*)malloc(sizeof(DescritorToken));
    descToken->inicio = NULL;
    descToken->fim = NULL;
    
    int i = 0;
    char operador[3];
    int tamanhoOp;
    
    while (linha[i] != '\0') {
        i = pularEspacos(linha, i);
        
        if (linha[i] != '\0') {
            // Ignorar ponto e vírgula
            if (linha[i] == ';') {
                i++;
            }
            // Processar strings
            else if (linha[i] == '"' || linha[i] == '\'') {
                i = processarString(linha, i, descToken);
            }
            // Processar números
            else if (isdigit(linha[i])) {
                i = processarNumero(linha, i, descToken);
            }
            // Verificar operadores (simples e duplos)
            else if ((tamanhoOp = verificarOperadorDuplo(linha, i, operador)) > 0) {
                // Tratamento especial para chaves
                if (operador[0] == '{') {
                    adicionarToken(descToken, operador);
                    (*nivelChaves)++;
                } else if (operador[0] == '}') {
                    adicionarToken(descToken, "fin-func");
                    (*nivelChaves)--;
                } else {
                    adicionarToken(descToken, operador);
                }
                i += tamanhoOp;
            }
            // Processar identificadores e palavras-chave
            else if (isalpha(linha[i]) || linha[i] == '_') {
                i = processarPalavra(linha, i, descToken);
            }
            // Pular caracteres desconhecidos
            else {
                i++;
            }
        }
    }
    
    // Adicionar linha ao programa se houver tokens
    if (descToken->inicio != NULL) {
        adicionarLinhaPrograma(prog, descToken);
    } else {
        free(descToken);
    }
}

// funcao para imprimir as listas na memoria
void imprimirPrograma(DescritorPrograma *prog) {
    pProgama *linhaAtual = prog->inicio;
    int numLinha = 300; //apenas para simbolizar enderecos igual na aula 
    
    printf("pPrograma\n");
    printf("  |\n");
    
    while (linhaAtual != NULL) {
        printf("[%d]", numLinha);
        
        pToken *tokenAtual = linhaAtual->tokens;
        if (tokenAtual != NULL) {
            printf(" -> ");
            while (tokenAtual != NULL) {
                printf("[%s]", tokenAtual->tokens);
                if (tokenAtual->proximo != NULL) {
                    printf(" -> ");
                }
                tokenAtual = tokenAtual->proximo;
            }
        }
        printf("\n");
        
        if (linhaAtual->proximo != NULL) {
            printf("  |\n");
        }
        
        linhaAtual = linhaAtual->proximo;
        numLinha += 12;
    }
}

// Função principal de tokenização
DescritorPrograma* tokenizarArquivo(ArquivoJS *arquivo, int numLinhas) {
    DescritorPrograma *prog = (DescritorPrograma*)malloc(sizeof(DescritorPrograma));
    prog->inicio = NULL;
    prog->fim = NULL;
    
    int nivelChaves = 0;
    int i = 0;
    
    while (i < numLinhas) {
        if (strlen(arquivo[i].linha) > 0) {
            tokenizarLinha(arquivo[i].linha, prog, &nivelChaves);
        }
        i++;
    }
    
    return prog;
}

// Função para liberar memória dos tokens
void liberarTokens(pToken *inicio) {
    pToken *atual = inicio;
    pToken *proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

// Função para liberar memória do programa
void liberarPrograma(DescritorPrograma *prog) {
    pProgama *atual = prog->inicio;
    pProgama *proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        liberarTokens(atual->tokens);
        free(atual);
        atual = proximo;
    }
    
    free(prog);
}

// Função de teste com exemplos mais complexos
void testarTokenizador() {
    printf("\n=== TESTE COM EXEMPLOS COMPLEXOS ===\n\n");
    
    ArquivoJS exemplos[] = {
        // Função com operadores
        {"function calcula_quadrado(x)"},
        {"{"},
        {"    let quadrado = x ** 2;"},
        {"    return quadrado;"},
        {"}"},
        {""},
        // Variáveis e arrays
        {"let array = ['oi', 2.0, 5, [10, 20]];"},
        {"const calc = 2 + 2;"},
        {"let svalor = '237';"},
        {""},
        // Operadores de comparação
        {"if (var1 == 1)"},
        {"    console.log('var1 igual a 1');"},
        {"else if (var1 != 1 && var2 == 2)"},
        {"    console.log('teste');"},
        {""},
        // Loops
        {"while (i < 10)"},
        {"{"},
        {"    console.log('i =', i);"},
        {"    i++;"},
        {"}"},
        {""},
        {"for(let i=0; i<10; i++)"},
        {"{"},
        {"    console.log('i = ', i);"},
        {"}"},
        {""},
        // Arrays métodos
        {"frutas.push('ameixa');"},
        {"let aux = frutas.pop();"},
        {"frutas.sort();"},
        {"console.log(frutas.length);"}
    };
    
    int numLinhas = sizeof(exemplos) / sizeof(ArquivoJS);
    
    DescritorPrograma *prog = tokenizarArquivo(exemplos, numLinhas);
    imprimirPrograma(prog);
    liberarPrograma(prog);
}

//tratando caso seja a primeira linha, se nao for insere no final e atualiza o descritor e as ligacoes
void adicionarToken(DescritorToken *descritor, char *valor) {
    pToken *novo = criarToken(valor);
    if (novo != NULL) {
        if (descritor->inicio == NULL) {
            descritor->inicio = novo;
            descritor->fim = novo;
        } else {
            descritor->fim->proximo = novo;
            descritor->fim = novo;
        }
    }
}

void executar() {
    FILE *arquivo;
    DescritorPrograma *programa;
    
    // Abrir o arquivo JavaScript
    arquivo = fopen("codigo.js", "r");
    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    
    // Montar a estrutura principal
    montarEstruturaPrincipal(arquivo, &programa);
    
    // Usar a estrutura tokenizada...
    // Por exemplo, percorrer os tokens
    pProgama *linhaAtual = programa->inicio;
    while(linhaAtual != NULL) {
        pToken *tokenAtual = linhaAtual->tokens;
        while(tokenAtual != NULL) {
            // Processar cada token
            printf("Token: %s\n", tokenAtual->tokens);
            tokenAtual = tokenAtual->proximo;
        }
        linhaAtual = linhaAtual->proximo;
    }
    
    // Liberar memória
    liberarPrograma(programa);
    
    return 0;
}

int main () {
    executar();
}