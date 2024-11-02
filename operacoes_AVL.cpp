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

// Classes
class No
public:
    friend class AVL;

private:
    int codigo;
    int altura;
    No *mae;
    No *esq;
    No *dir;

public:
    No(const int codigo) : 
        codigo(codigo), 
        altura(0), 
        mae(nullptr), 
        esq(nullptr), 
        dir(nullptr) 
    {}

    void escreve(const char *sep = "") {
        cout << codigo << sep;
    }
    
    inline bool eh_raiz() { 
        return mae == nullptr; 
    }
    inline bool eh_direito() { 
        return mae && mae->dir == this; 
    }
    inline bool eh_esquerdo() { 
        return mae && mae->esq == this; 
    }
    inline int bal() {
        int alt_esq = esq ? esq->altura : -1;
        int alt_dir = dir ? dir->altura : -1;
        return alt_esq - alt_dir;
    }

    inline void atualiza_altura() {
        int alt_esq = esq ? esq->altura : -1;
        int alt_dir = dir ? dir->altura : -1;
        altura = 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
    }

};

class AVL
{
private:
    No *raiz;
    
    void escreve(const string &prefixo, No *x) {
        if (x != nullptr) {
            cout << prefixo;
            cout << (x->eh_raiz() ? "Raiz -> " : "-> ");
            x->escreve("\n");
            escreve(prefixo + "   ", x->esq);
            escreve(prefixo + "   ", x->dir);
        }
    }

    No *busca(No *x, int k) {
        if (x == nullptr || x->codigo == k
            return x;
        if (k < x->codigo) 
            return busca(x->esq, k);
        else
            return busca(x->dir, k);
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

    AVL T1, T2;

    int v1[] = {33, 5, 10, 21, 20, 23, 18, 16, 19, 15, 17, 22, 14};

    int v2[] = {3, 0, 10, 21, 20, 23, 18, 16, 19, 15, 25, 26, 13};

    /* Operações Básicas */
    // Insere elementos de v1 em T1
    /* Operações Avançadas */
    // União de T1 e T2
    // Interseção de T1 e T2
    // Busca de elementos em um intervalo de T1 ou T2
    return 0;
}