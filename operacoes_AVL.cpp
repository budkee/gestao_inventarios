/**************************************************
 *
 * Isabelle Bicudo e Kaê de Oliveira Budke
 * Trabalho 2
 * Professor: Fábio Henrique Viduani Martinez
 *
 */

// Bibliotecas
#include <iostream>
#include <cstdlib>
#include <cstdio>

// Classes
/*
    Cada Nó é um produto dotado de código e sua altura na árvore. Além disso, cada nó possui um ponteiro para o nó pai, um para o nó à esquerda e outro para o nó à direita.
*/
class No {

    friend class AVL;

private:
    
    int codigo;
    int altura;
    No *mae;
    No *esq;
    No *dir;

public:
    
    /*
        Construtor de um nó atribuindo o código e altura, além do estado do ponteiro da mãe, filho esquerdo e direito.
    */
    No(const int codigo) : 
        codigo(codigo), 
        altura(0), 
        mae(nullptr), 
        esq(nullptr), 
        dir(nullptr) 
    {}

    /*
        Destrutor de um nó.
    */

    ~No() {
        delete esq;
        delete dir;
    }

    /*
        Escreve o código do nó com um espaço como separador.
    */
    void escreve(const char *sep = "") {
        
        std::cout << codigo << sep;
        
    }
    
    /*
        Retorna se o nó é raiz.
    */
    inline bool eh_raiz() { 
        return mae == nullptr; 
    }

    /*
        Retorna se o nó é filho direito.
    */
    inline bool eh_direito() { 
        return mae && mae->dir == this; 
    }

    /*
        Retorna se o nó é filho esquerdo.
    */
    inline bool eh_esquerdo() { 
        return mae && mae->esq == this; 
    }

    /*
        Retorna o fator de balanceamento do nó.
    */
    inline int bal() {

        // Altura da subárvore esquerda: se a altura não for nula, retorna a altura, senão, retorna -1
        int alt_esq = esq ? esq->altura : -1;
        
        // Altura da subárvore direita
        int alt_dir = dir ? dir->altura : -1;

        // Retorna o fator de balanceamento do nó
        return alt_esq - alt_dir;
    }

    /*
        Atualiza a altura do nó.
    */
    inline void atualiza_altura() {
        
        // Altura da subárvore esquerda
        int alt_esq = esq ? esq->altura : -1;
        // Altura da subárvore direita
        int alt_dir = dir ? dir->altura : -1;

        // Atualiza a altura do nó
        altura = 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
            // Se a altura da subárvore esquerda for maior que a da direita, a altura do nó é a da esquerda mais 1, senão, a da direita mais 1
    }

};

class AVL
{
private:
    
    No *raiz;
    
    void insere(int codigo) {
        No *z = new No(codigo);
        insere(z);
    }   

    void insere(No *z) {
        No *y = nullptr;
        No *x = raiz;

        while (x != nullptr) {
            y = x;
            if (z->codigo < x->codigo) 
                x = x->esq;
            else 
                x = x->dir;
        }

        z->mae = y;
        if (y == nullptr) 
            raiz = z;
        else 
            if (z->codigo < y->codigo) 
                y->esq = z;
            else 
                y->dir = z;

        // Atualização dos fatores de balanceamento
        if (z->eh_raiz())
            return;
        
        do { // o laço inicia subindo imediatamente para o pai do nó inserido
            z = z->mae;
            z = ajusta_balanceamento(z, true);
        } while (!z->eh_raiz() and z->bal() != 0);
    }
    
    No *busca(No *x, int k) {
        if (x == nullptr || x->codigo == k
            return x;
        if (k < x->codigo) 
            return busca(x->esq, k);
        else
            return busca(x->dir, k);
    };

    void escreve(const string &prefixo, No *x) {
        if (x != nullptr) {
            cout << prefixo;
            cout << (x->eh_raiz() ? "Raiz -> " : "-> ");
            x->escreve("\n");
            escreve(prefixo + "   ", x->esq);
            escreve(prefixo + "   ", x->dir);
        }
    }


    No *minimo() {
        // Encontra o menor valor em toda a árvore
        return raiz ? minimo(raiz) : nullptr;
    }
    No *minimo(No *x) {
        // Encontra o menor valor a partir de um nó específico
        while (x->esq != nullptr) 
            x = x->esq;
        return x;
    };

    No *maximo() {
       return raiz ? maximo(raiz) : nullptr;
    }
   
    No *maximo(No *x) {
        while (x->dir != nullptr) 
            x = x->dir;
        return x;
    };

    void transplante(No *u, No *v) {
        if (u->mae == nullptr) 
            raiz = v;
        else 
            if (u == u->mae->esq) 
                u->mae->esq = v;
            else 
                u->mae->dir = v;
        
        if (v != nullptr) 
            v->mae = u->mae;
    }

    No *ajusta_balanceamento(No *p, bool ins) {
        
        p->atualiza_altura();
        
        int bal = p->bal();

        // Caso 1: Rotação à direita
        if (bal == 2) {
            if (p->esq->bal() >= 0) {
                // Caso 1.1: 
                if (ins) 
                    cout << ">> Rotação direita (Caso 1.1)\n";
                rotacao_dir(p);
            } else {
                // Caso 1.2: Rotação dupla direita
                if (ins) 
                    cout << ">> Rotação dupla direita (Caso 1.2)\n";
                rotacao_dupla_dir(p);
            }
            p = p->mae;
        } else 
            if (bal == -2) {
                // Caso 2: Rotação à esquerda
                if (p->dir->bal() <= 0) {
                    // Caso 2.1: Rotação à esquerda
                    if (ins) 
                        cout << ">> Rotação esquerda (Caso 2.1)\n";
                    rotacao_esq(p);
                } else {
                    // Caso 2.2: Rotação dupla esquerda
                    if (ins) 
                        cout << ">> Rotação dupla esquerda (Caso 2.2)\n";
                    rotacao_dupla_esq(p);
                }
                p = p->mae;
            }

        return p;
    }
    
    bool remove(int codigo) {
        No *z = busca(raiz, codigo);
        if (z == NULL)
            return false;

        remove(z);
        delete z;
        return true;
    }
    void remove(No *z) {
        No *p = NULL;
        
        if (z->esq == NULL) { 

            p = z->pai; 
            transplante(z, z->dir);
        }
        else {
            if (z->dir == NULL) { 
            printf("<< Remoção 2o caso\n");
            p = z->pai; 
            transplante(z, z->esq);
            }
            else { 
            No *y = minimo(z->dir);
            
            printf("<< Remoção 3o caso (a) ");
            if (y->pai != z) { 
            printf("+ (b)\n");
                p = y->pai; 
                transplante(y, y->dir); 
                y->dir = z->dir;
                y->dir->pai = y;
            }
            printf("\n");
            
            transplante(z, y); // (a)
            y->esq = z->esq;
            y->esq->pai = y;

            if (p == NULL) 
                p = y;
            }
        }

        
        if (p == NULL)
            return;
        
    
        p = ajusta_balanceamento(p, false);
        
        while (!p->eh_raiz() and p->bal() != 1 and p->bal() != -1) { 
            p = p->pai;
            p = ajusta_balanceamento(p, false);
        }
    }
    
    void AVL::limpa() {
        limpa(raiz);
        raiz = NULL;
    }
    void limpa(No *x){
        if (x == NULL)
            return;

        limpa(x->esq);
        limpa(x->dir);
        delete x;
    }; // dado um nó x, remove recursivamente todos elementos abaixo e deleta x
    
    void copia(const AVL& T){
    if (T.raiz == NULL)
        raiz = NULL;
    else {
        raiz = new No(T.raiz->chave);
        copia(raiz, T.raiz);
    }
    }; // copia uma árvore T para a atual a partir da raiz,

    void AVL::copia(No *dest, No *orig) {
        if (orig->esq) {
            dest->esq = new No(orig->esq->chave);
            dest->esq->pai = dest;
            copia(dest->esq, orig->esq);
        }
        
        if (orig->dir) {
            dest->dir = new No(orig->dir->chave);
            dest->dir->pai = dest;
            copia(dest->dir, orig->dir);
        }
    }

    void AVL::rotacao_dir(No *p) {
        No *u = p->esq;
        // arruma u e seu pai (o pai de p)
        transplante(p, u);
        // move p para a direita de u, e o filho direito de u para a esquerda de p
        p->pai = u;
        p->esq = u->dir;
        u->dir = p;
        if (p->esq) p->esq->pai = p;
        // atualiza alturas
        p->atualiza_altura();
        u->atualiza_altura();
    }

    void AVL::rotacao_esq(No *p) {
        No *u = p->dir;
        // arruma u e seu pai (o pai de p)
        transplante(p, u);
        // move p para a esquerda de u, e o filho esquerdo de u para a direita de p
        p->pai = u;
        p->dir = u->esq;
        u->esq = p;
        if (p->dir) p->dir->pai = p;
        // atualiza alturas
        p->atualiza_altura();
        u->atualiza_altura();
    }

    void AVL::rotacao_dupla_dir(No *p) {
        rotacao_esq(p->esq);
        rotacao_dir(p);
    }

    void AVL::rotacao_dupla_esq(No *p) {
        rotacao_dir(p->dir);
        rotacao_esq(p);
    }

public:
    
    AVL();
    AVL(const AVL& outro); // construtor de cópia
    ~AVL();
    AVL& operator=(const AVL& outro); // operador de atribuição
    
    void escreve();

    No *get_raiz();         // devolve a raiz
    No *busca(int k);       // devolve o ponteiro para um elemento, se achar, ou NULL
    No *minimo();           // devolve o menor elemento da árvore
    No *maximo();           // devolve o maior elemento da árvore
    No *sucessor(No *x);    // devolve o sucessor de um elemento
    No *predecessor(No *x); // devolve o predecessor de um elemento

    void insere(int codigo); // insere um código
    bool remove(int codigo); // remove uma árvore

    void limpa(); // remove todos elementos da árvore
    void rotacao_dir(No *p); // Rotação à direita: p e p->esq
    void rotacao_esq(No *p); // Rotação à esquerda: p e p->dir
    void rotacao_dupla_dir(No *p); // Rotação dupla à direita: p->esq e p->esq->dir à esquerda, então p e p->esq à direita
    void rotacao_dupla_esq(No *p); // Rotação dupla à esquerda: p->dir e p->dir->esq à direita, então p e p->dir à esquerda
};


int main(void)
{
    // Criação de dois Bancos de Dados AVL
    AVL T1, T2;

    // Conjunto de códigos de produtos
    int v1[] = {33, 5, 10, 21, 20, 23, 18, 16, 19, 15, 17, 22, 14};
    int v2[] = {3, 0, 10, 21, 20, 23, 18, 16, 19, 15, 25, 26, 13};

    /* 
        Operações Básicas 
    */
    // Insere produtos de v1 em T1
    printf("## Inserção de produtos\n\n");
    printf("T1:\n");
    for (const auto &x : v1) {
        printf("\nInserindo %d...\n", x);
        T1.insere(x); // Inicialmente, sem balanceamento
        printf("T:\n");
        T1.escreve();
    }

    // Busca de produtos em T1
    printf("\n## Busca de produtos\n\n");
    int valor_busca;

    printf("Insira um valor para buscar na árvore T1: ");
    scanf("%d", &valor_busca);

    printf("Buscando %d...\n", valor_busca);
    No *n = T1.busca(valor_busca);
    if (n != nullptr) {
        printf("Encontrado: ");
        n->escreve("\n");
    } else {
        printf("Não encontrado.\n");
    }

    // Remove produtos de v1 em T1
    printf("\n## Remoção de produtos\n\n");
    printf("T1:\n");
    T1.escreve();
    for (const auto &x : v1) {
        printf("\nRemovendo %d...\n", x);
        T1.remove(x);
        printf("T:\n");
        T1.escreve();
    }
    
    /* 
        Operações Avançadas 
    */
    // União de T1 e T2
    
    
    // Interseção de T1 e T2
    
    
    // Busca de elementos em um intervalo de T1 ou T2
    
    
    return 0;
}