struct registroLista {
    struct listagen *cabeca;
    struct listagen *cauda;
}; typedef struct registroLista RegistroLista;

union infoLista {
    char info[20];
    struct RegistroLista lista;
};

struct listagen {
    char terminal;
    union infoLista no;
}; typedef struct listagen ListaGen;


ListaGen *CriaT(char *info)
{
    ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
    L->terminal = 1;
    strcpy(L->no.info, info);
    return L;
}

char Nula(ListaGen *L)
{
    return L==NULL;
}

char Atomo(ListaGen *L)
{
    return !Nula(L) && L->terminal;
}

ListaGen *Cons(ListaGen *H, ListaGen *T)
{
    if (Atomo(T))
    {
        printf("Cons: Segundo arqumento nao pode ser Atomo!");
        return NULL;
    }
    else
    {
        ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
        L->terminal = 0;
        L->no.lista.cabeca = H;
        L->no.lista.cauda = T;
        return L;
    }
}

ListaGen *Head(ListaGen *L)
{
    if (Nula(L) || Atomo(L))
    {
        printf("Head: argumento deve ser lista não vazia!");
        return NULL;
    }
    else
        return L->no.lista.cabeca;
}

ListaGen *Tail(ListaGen *L)
{
    if (Nula(L) || Atomo(L))
    {
        printf("Tail: argumento deve ser lista não vazia!");
        return NULL;
    }
    else
        return L->no.lista.cauda;
}

void exibirAtomos (ListaGen *lista) {
    if(!Nula(lista)) {
        if(Atomo(lista))
            printf("%s ", lista->no.info);
        else {
            exibirAtomos(Head(lista));
            exibirAtomos(Tail(lista));
        }
    }
}