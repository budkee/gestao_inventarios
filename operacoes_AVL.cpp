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

        // Ajusta os fatores de balanceamento
        if (z->eh_raiz())
            return;
        
        do { // o laço inicia subindo imediatamente para o pai do nó inserido
            z = z->mae;
            z = ajusta_balanceamento(z, true);
        } while (!z->eh_raiz() and z->bal() != 0);
    }
    
    No *busca(No *x, int k) {
        if (x == nullptr || x->codigo == k)
            return x;
        if (k < x->codigo) 
            return busca(x->esq, k);
        else
            return busca(x->dir, k);
    };
  
    /*
        Encontra o menor valor a partir de um nó específico.
    */
    No *minimo(No *x) {
        while (x->esq != nullptr) 
            x = x->esq;
        return x;
    };

    /*
        Encontra o maior valor a partir de um nó específico.
    */
    No *maximo(No *x) {
        while (x->dir != nullptr) 
            x = x->dir;
        return x;
    };

    /* 
        Transplanta v para u.     
    */
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

    /*
        Ajusta o balanceamento da árvore.
    */
    No *ajusta_balanceamento(No *p, bool girou) {
        
        p->atualiza_altura();
        
        int balance = p->bal();

        // Caso 1: Rotação à direita
        if (balance == 2) {
            if (p->esq->bal() >= 0) {
                // Caso 1.1: 
                if (girou) 
                    std::cout << ">> Rotação direita (Caso 1.1)\n";
                rotacao_dir(p);
            } else {
                // Caso 1.2: Rotação dupla direita
                if (girou) 
                    std::cout << ">> Rotação dupla direita (Caso 1.2)\n";
                rotacao_dupla_dir(p);
            }
            p = p->mae;
        } else 
            if (balance == -2) {
                // Caso 2: Rotação à esquerda
                if (p->dir->bal() <= 0) {
                    // Caso 2.1: Rotação à esquerda
                    if (girou) 
                        std::cout << ">> Rotação esquerda (Caso 2.1)\n";
                    rotacao_esq(p);
                } else {
                    // Caso 2.2: Rotação dupla esquerda
                    if (girou) 
                        std::cout << ">> Rotação dupla esquerda (Caso 2.2)\n";
                    rotacao_dupla_esq(p);
                }
                p = p->mae;
            }

        return p;
    }
    
    /*
        Remove um nó da árvore.
    */
    void remove(No *z) {
        No *p = NULL;
        
        if (z->esq == NULL) { 

            p = z->mae; 
            transplante(z, z->dir);
        }
        else {
            if (z->dir == NULL) { 
            printf("<< Remoção 2o caso\n");
            p = z->mae; 
            transplante(z, z->esq);
            }
            else { 
            No *y = minimo(z->dir);
            
            printf("<< Remoção 3o caso (a) ");
            if (y->mae != z) { 
            printf("+ (b)\n");
                p = y->mae; 
                transplante(y, y->dir); 
                y->dir = z->dir;
                y->dir->mae = y;
            }
            printf("\n");
            
            transplante(z, y); // (a)
            y->esq = z->esq;
            y->esq->mae = y;

            if (p == NULL) 
                p = y;
            }
        }

        
        if (p == NULL)
            return;
        
    
        p = ajusta_balanceamento(p, false);
        
        while (!p->eh_raiz() and p->bal() != 1 and p->bal() != -1) { 
            p = p->mae;
            p = ajusta_balanceamento(p, false);
        }
    }
    
    /*
        Limpa a árvore a partir de um nó x.
    */
    void limpa(No *x){
        if (x == NULL)
            return;

        limpa(No *x->esq);
        limpa(No *x->dir);
        delete x;
    }; // dado um nó x, remove recursivamente todos elementos abaixo e deleta x
    
    /*
        Copia uma árvore T para a atual a partir da raiz.
    */
    void copia(const AVL& T){
        if (T.raiz == NULL)
            raiz = NULL;
        else {
            raiz = new No(T.raiz->codigo);
            copia(raiz, T.raiz);
        }
    }; 
    
    /*
        Copia um nó de origem para um nó de destino.
    */
    void copia(No *dest, No *orig) {
        if (orig->esq) {
            dest->esq = new No(orig->esq->codigo);
            dest->esq->mae = dest;
            copia(dest->esq, orig->esq);
        }
        
        if (orig->dir) {
            dest->dir = new No(orig->dir->codigo);
            dest->dir->mae = dest;
            copia(dest->dir, orig->dir);
        }
    }

    /*
        Rotação à direita.
    */
    void rotacao_dir(No *p) {
        No *u = p->esq;
        // arruma u e seu pai (o pai de p)
        transplante(p, u);
        // move p para a direita de u, e o filho direito de u para a esquerda de p
        p->mae = u;
        p->esq = u->dir;
        u->dir = p;
        if (p->esq) p->esq->mae = p;
        // atualiza alturas
        p->atualiza_altura();
        u->atualiza_altura();
    }

    /*
        Rotação à esquerda.
    */
    void rotacao_esq(No *p) {
        No *u = p->dir;
        // arruma u e seu pai (o pai de p)
        transplante(p, u);
        // move p para a esquerda de u, e o filho esquerdo de u para a direita de p
        p->mae = u;
        p->dir = u->esq;
        u->esq = p;
        if (p->dir) p->dir->mae = p;
        // atualiza alturas
        p->atualiza_altura();
        u->atualiza_altura();
    }

    /*
        Rotação dupla à direita.
    */
    void rotacao_dupla_dir(No *p) {
        rotacao_esq(p->esq);
        rotacao_dir(p);
    }

    /*
        Rotação dupla à esquerda.
    */
    void rotacao_dupla_esq(No *p) {
        rotacao_dir(p->dir);
        rotacao_esq(p);
    }

    /*
        União de duas árvores AVL.
    */
    void uniao(No *x) {
        if (x != nullptr) {
            insere(x->codigo);  // Insere o código do nó atual na árvore AVL
            uniao(x->esq);      // Chama recursivamente para o filho esquerdo
            uniao(x->dir);      // Chama recursivamente para o filho direito
        }
    }

    /*
        Interseção de duas árvores AVL.
    */
    void intersecao(No *x, AVL &T2, AVL &resultado) {
        if (x != nullptr) {
            if (T2.busca(x->codigo) != nullptr) 
                resultado.insere(x->codigo);
            
            intersecao(x->esq, T2, resultado);
            intersecao(x->dir, T2, resultado);
        }
    }

    /*
        Busca de elementos em um intervalo de códigos.
    */
    void busca_intervalo(No *x, int min, int max) {
        if (x == nullptr) return;

        if (x->codigo >= min && x->codigo <= max) {
            x->escreve("\n");
        }
        
        if (x->codigo > min) busca_intervalo(x->esq, min, max);
        if (x->codigo < max) busca_intervalo(x->dir, min, max);
    }

    /*
        Escreve a árvore AVL.
    */
    void escreve(const string &prefixo, No *x) {
        if (x != nullptr) {
            std::cout << prefixo;
            std::cout << (x->eh_raiz() ? "Raiz -> " : "-> ");
            x->escreve("\n");
            escreve(prefixo + "   ", x->esq);
            escreve(prefixo + "   ", x->dir);
        }
    }

public:
    // Construtor
    AVL();
    // Construtor de cópia
    AVL(const AVL& outro){
        copia(outro);
    };
    
    // Destrutor 
    ~AVL();

    // Operador de atribuição
    AVL& operator=(const AVL& outro){
        limpa();
        copia(outro);
        return *this;
    };

    No *get_raiz(){
        return raiz;
    };         
    
    No *busca(int k) {
        return busca(raiz, k);
    }

    No *minimo() {
        return raiz ? minimo(raiz) : nullptr;
    }           
    
    No *maximo() {
       return raiz ? maximo(raiz) : nullptr;
    }   

    No *sucessor(No *x){
        if (x->dir != NULL)
            return minimo(x->dir);
        No *y = x->mae;
        while (y != NULL && x == y->dir) {
            x = y;
            y = y->mae;
        }
        return y;
    };    

    No *predecessor(No *x){
        if (x->esq != NULL)
            return maximo(x->esq);
        No *y = x->mae;
        while (y != NULL && x == y->esq) {
            x = y;
            y = y->mae;
        }
        return y;
    }; 

    void insere(int codigo) {
        No *z = new No(codigo);
        insere(z);
    }   

    bool remove(int codigo) {
        No *z = busca(raiz, codigo);
        if (z == NULL)
            return false;

        remove(z);
        delete z;
        return true;
    } 
    
    void limpa() {
        limpa(raiz);
        raiz = NULL;
    }     

    void uniao(AVL &T) {
        uniao(T.raiz);  // Chama a função auxiliar iniciando pela raiz da árvore T
    }

    void intersecao(AVL &T1, AVL &T2, AVL &resultado) {
        intersecao(T1.raiz, T2, resultado);
    }

    void busca_intervalo(int min, int max) {
        busca_intervalo(raiz, min, max);
    }   

    void escreve(){
        escreve("", raiz);
    };
};


int main(void)
{
    // Criação de três Bancos de Dados AVL
    AVL T1, T2, intersecao_T1_T2;

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
    printf("\n## União de T1 e T2\n\n");
    printf("T1:\n");
    T1.escreve();
    printf("T2:\n");
    T2.escreve();
    printf("T1 U T2:\n");
    T1.uniao(T2);  // Une T2 em T1
    T1.escreve();  // Imprime T1 com a união
    
    // Interseção de T1 e T2
    printf("\n## Interseção de T1 e T2\n\n");
    printf("T1:\n");
    T1.escreve();
    printf("T2:\n");
    T2.escreve();
    printf("T1 ∩ T2:\n");
    intersecao_T1_T2.intersecao(T1, T2, intersecao_T1_T2);
    intersecao_T1_T2.escreve();  // Imprime a árvore resultante da interseção   
    
    // Busca de elementos em um intervalo de T1 ou T2
    printf("\n## Busca de produtos em um intervalo de T2\n\n");
    int valor_min, valor_max;

    printf("Insira um valor mínimo para buscar na árvore T2: ");
    scanf("%d\n", &valor_min);
    printf("Insira um valor máximo para buscar na árvore T2: ");
    scanf("%d\n", &valor_max);

    printf("\nBuscando intervalo [%d, %d]...\n", valor_min, valor_max);
    printf("T2:\n");
    T2.busca_intervalo(valor_min, valor_max);
    
    return 0;
}