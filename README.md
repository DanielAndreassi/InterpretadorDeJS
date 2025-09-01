# 🚀 Interpretador JavaScript

Um interpretador (simulador de execução) para programas JavaScript desenvolvido como projeto da disciplina **Estruturas de Dados II** na **Universidade do Oeste de Santa Catarina (UNOESTE)**.

## 📋 Sobre o Projeto

Este projeto implementa um interpretador completo para um subconjunto da linguagem JavaScript, capaz de executar programas passo a passo com visualização da memória RAM e controle de escopo através de estruturas de dados dinâmicas.

### 🎯 Funcionalidades Principais

- **Execução passo a passo**: Navegação linha por linha com visualização da linha atual
- **Gerenciamento de memória**: Pilha dinâmica para variáveis e controle de escopo
- **Interface visual**: Tela do interpretador com destaque da linha em execução
- **Controles interativos**:
  - `F7` - Abrir arquivo JavaScript
  - `F8` - Executar programa
  - `F9` - Visualizar memória RAM
  - `F10` - Exibir tela de saída
  - `ENTER` - Executar linha atual e avançar

### ⚠️ Importante: Validação de Código

**O interpretador assume que o código JavaScript está correto e não realiza verificação de erros.** 

- **Não há tratamento de erros**: O interpretador executa o código sem validar sintaxe ou semântica
- **Código deve estar correto**: Programas com erros podem causar comportamento inesperado
- **Responsabilidade do programador**: Garantir que o código está sintaticamente correto antes da execução
- **Foco na execução**: O objetivo é simular a execução, não detectar erros de programação

## 🛠️ Estruturas de Dados Implementadas

### Lista de Listas (Tokenização)
```
pPrograma → [300] → function → calcula → ( → x → y → )
              ↓
            [312] → return → x → + → y
              ↓
            [324] → fim-func
              ⋮
```

### Pilha de Variáveis (Memória RAM)
```
┌────┬─────────────┬────────┬──────────┐
│ &  │identificador│ valor  │ ponteiro │
├────┼─────────────┼────────┼──────────┤
│120 │     y       │   10   │   NULL   │
│116 │     x       │    5   │   NULL   │
│112 │ [endereço]  │   -    │  [372]   │
│108 │     c       │    0   │   NULL   │
│104 │     b       │   10   │   NULL   │
│100 │     a       │    5   │   NULL   │
└────┴─────────────┴────────┴──────────┘
```

### Lista Generalizada (Expressões Aritméticas)
Sistema de resolução de expressões com prioridades utilizando union para diferentes tipos de nodos:
- **V** (Value): Nodo terminal com valor
- **O** (Operator): Nodo com operador aritmético  
- **F** (Function): Nodo com função matemática

## 💻 Comandos e Estruturas Suportadas

### ✅ Funções
- Declaração de funções com parâmetros
- Chamadas de função com passagem por valor
- Retorno de valores com `return`
- Funções aninhadas

### ✅ Variáveis
- Declaração com `let` e `const`
- Atribuição e reatribuição
- Escopo local e global

### ✅ Operadores

| Aritméticos | Comparação | Lógicos |
|-------------|------------|---------|
| `+` `-` `*` `/` | `==` `!=` | `&&` `||` `!` |
| `%` `**` | `>` `<` `>=` `<=` | |

### ✅ Estruturas de Controle

#### Condicional (if/else)
```javascript
if (condição) {
    comando(s);
} else if (condição) {
    comando(s);
} else {
    comando(s);
}
```

#### Laços de Repetição
```javascript
// While
while (condição) {
    comando(s);
}

// Do-While  
do {
    comando(s);
} while (condição);

// For
for (let i = 0; i < 10; i++) {
    comando(s);
}
```

### ✅ Arrays JavaScript
```javascript
let array = ['oi', 2.0, 5, [10, 20]];
console.log(array[0]);     // oi
console.log(array[3][1]);  // 20

// Métodos suportados
array.push(elemento);      // Adicionar ao final
array.pop();              // Remover do final  
array.unshift(elemento);  // Adicionar ao início
array.shift();            // Remover do início
array.sort();             // Ordenar
array.length;             // Tamanho
```

### ✅ Funções Built-in
- `console.log()` - Saída de dados
- `console.table()` - Exibição tabular
- `Math.sqrt()` - Raiz quadrada
- `Math.abs()` - Valor absoluto
- `parseInt()` - Conversão para inteiro
- `toString()` - Conversão para string

## 📁 Estrutura do Projeto

```
InterpretadorDeJS/
├── README.md              # Este arquivo
├── src/                   # Código fonte
│   ├── main.c            # Função principal
│   ├── parser.c          # Analisador léxico/sintático
│   ├── interpreter.c     # Motor de interpretação
│   ├── memory.c          # Gerenciamento de memória
│   ├── expressions.c     # Avaliação de expressões
│   └── structures/       # Estruturas de dados
│       ├── lista.c       # Lista encadeada
│       ├── pilha.c       # Pilha dinâmica
│       └── generalizada.c # Lista generalizada
├── tests/                # Programas de teste
│   ├── exemplo1.js       # Função básica
│   ├── exemplo2.js       # Laços while
│   ├── exemplo3.js       # Laços for
│   ├── exemplo4.js       # Funções matemáticas
│   └── exemplo5.js       # Arrays e busca
├── docs/                 # Documentação
│   └── estruturas.docx   # Desenho das estruturas
└── Makefile             # Compilação
```

## 🔧 Como Compilar e Executar

### Pré-requisitos
- Compilador GCC
- Sistema operacional Linux/Unix ou Windows com MinGW

### Compilação
```bash
# Clone o repositório
git clone <url-do-repositorio>
cd InterpretadorDeJS

# Compile o projeto
make

# Ou compile manualmente
gcc -o interpretador src/*.c src/structures/*.c -lm
```

### Execução
```bash
# Execute o interpretador
./interpretador

# Na interface:
# F7 - Selecione um arquivo .js para carregar
# F8 - Inicie a execução  
# ENTER - Execute linha por linha
# F9 - Visualize a memória RAM
# F10 - Veja a saída do console.log()
```

## 📝 Exemplos de Programas

### Exemplo 1: Funções Básicas
```javascript
function calcula(x, y) {
    return x + y;
}

let a = 5;
let b = 10;
let c = calcula(a, b);
console.log("Resultado:", c);
```

### Exemplo 2: Laços e Arrays
```javascript
function ordenarFrutas() {
    let frutas = ['laranja', 'banana', 'abacaxi'];
    frutas.sort();
    console.log(frutas);
    console.log("Tamanho:", frutas.length);
}

ordenarFrutas();
```

### Exemplo 3: Estruturas Condicionais
```javascript
function verificaIdade(idade) {
    if (idade >= 18) {
        console.log("Maior de idade");
    } else {
        console.log("Menor de idade");
    }
}

verificaIdade(20);
```

## 🎮 Interface do Usuario

```
┌┤ C:\prog1.js ├────────────────────────────────┐
│function calcula(x, y)                         │ 
│{                                              │
│    return x + y;                              │
│}                                              │ 
│let a = 5;                                     │
│let b = 10;                                    │
│let c = 0;                                     │
│c = calcula(a, b); __________________________ │ ← Linha atual
│console.log(a, b, c);                          │
│a = calcula(7, a+b+c);                         │
│console.log("7", a+b+c, a);                    │ 
│c = calcula(a*b, a/b);                         │
│console.log(a*b, a/b, c);                      │
│a = calcula(b, b+b);                           │
│let msg = 'resultado = ';                      │
│console.log(msg, a, b, c);                     │
└───────────────────────────────────────────────┘
F7-Abrir  F8-Executar  F9-Memória RAM  F10-Tela
```

## 🧪 Testes

O projeto inclui uma suíte completa de testes cobrindo:

- **Exemplo 1**: Chamadas de função e escopo
- **Exemplo 2**: Estruturas de repetição while
- **Exemplo 3**: Estruturas de repetição for  
- **Exemplo 4**: Funções matemáticas e expressões
- **Exemplo 5**: Manipulação de arrays e estruturas condicionais

Execute os testes:
```bash
make test
# ou
./interpretador tests/exemplo1.js
./interpretador tests/exemplo2.js
# ... etc
```

## 🏗️ Arquitetura Técnica

### Tokenização (Parser)
O código JavaScript é parseado em uma estrutura de **Lista de Listas**, onde:
- Lista vertical: representa as linhas do programa
- Lista horizontal: contém os tokens de cada linha

### Gerenciamento de Memória
- **Pilha dinâmica**: Gerencia variáveis e escopo
- **Heap**: Armazena ponteiros para linhas de execução
- **Union structures**: Suporte a múltiplos tipos de dados

### Avaliação de Expressões
Sistema baseado em **Lista Generalizada** que:
1. Constrói árvore de expressão respeitando precedência
2. Resolve operações "podando" nodos da lista
3. Utiliza duas pilhas auxiliares (valores e operadores)

### Controle de Execução
- **Program Counter**: Ponteiro para linha atual
- **Call Stack**: Gerencia chamadas de função
- **Scope Chain**: Controla visibilidade de variáveis

## 🚫 Restrições Técnicas

- **Sem bibliotecas prontas**: Implementação from scratch
- **Sem strtok()**: Parser customizado para tokenização
- **Estruturas próprias**: Listas, pilhas e árvores implementadas manualmente
- **Uso de union**: Para suporte a tipos heterogêneos nos nodos

## 👥 Desenvolvimento

**Disciplina**: Estruturas de Dados II  
**Professor**: Francisco Assis da Silva  
**Instituição**: UNOESTE - Universidade do Oeste de Santa Catarina

### Entregáveis
- [ ] Código-fonte completo
- [ ] Programas JavaScript de teste
- [ ] Documentação das estruturas (estruturas.docx)
- [ ] Apresentação em dupla

## 📚 Referências Técnicas

- Estruturas de Dados e Algoritmos em C

## 🤝 Contribuição

Este é um projeto acadêmico. Para melhorias ou correções:

1. Fork o repositório
2. Crie uma branch para sua feature
3. Commit suas mudanças
4. Push para a branch
5. Abra um Pull Request

---

**⚡ Um interpretador JavaScript completo implementado com estruturas de dados fundamentais!**
