/**************************************************
 *
 * Isabelle Bicudo e Kaê de Oliveira Budke
 * Trabalho 2
 * Professor: Fábio Henrique Viduani Martinez
 *
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>

#define MAX 100

/**
 * @class No
 * @brief Classe que representa um nó em uma árvore AVL.
 * 
 * A classe No encapsula os atributos e métodos necessários para a manipulação de um nó em uma árvore AVL, incluindo a gestão de seus filhos, altura e fator de balanceamento. 
 *
 * @details Cada Nó é um produto dotado de código e sua altura na árvore. Além disso, cada nó possui um ponteiro para o nó pai, um para o nó à esquerda e outro para o nó à direita.
 */
class No 
{
    friend class AVL;

private:

    int codigo;
    int altura;
    No *mae;
    No *esq;
    No *dir;

public:
    
    /**
     * @brief Construtor da classe No.
     * @param codigo Código do nó.
     */
    No(const int codigo) : 
        codigo(codigo), 
        altura(0), 
        mae(nullptr), 
        esq(nullptr), 
        dir(nullptr) 
    {}

    /**
     * @brief Escreve o código do nó com um espaço como separador padrão.
     * @param sep Separador a ser utilizado após o código do nó.
     */
    void escreve(const char *sep = ">> ") const {
        
        std::cout << codigo << sep;
        
    }
    

    /**
     * @brief Retorna se o nó é raiz.
     * @return true se o nó é raiz, false caso contrário.
     */
    inline bool eh_raiz() { 
        return mae == nullptr; 
    }

    /**
     * @brief Retorna se o nó é filho direito.
     * @return true se o nó é filho direito, false caso contrário.
     */
    inline bool eh_direito() { 
        return mae && mae->dir == this; 
    }

    /**
     * @brief Retorna se o nó é filho esquerdo.
     * @return true se o nó é filho esquerdo, false caso contrário.
     */
    inline bool eh_esquerdo() { 
        return mae && mae->esq == this; 
    }

    /**
     * @brief Retorna o fator de balanceamento do nó.
     * @return Fator de balanceamento do nó.
     * @details O fator de balanceamento é a diferença entre a altura da subárvore esquerda e a altura da subárvore direita.
     * @details se a altura da subárvore esquerda não for nula, retorna a altura, senão, retorna -1
     */
    inline int bal() {

        // Altura da subárvore esquerda
        int alt_esq = esq ? esq->altura : -1;
        
        // Altura da subárvore direita
        int alt_dir = dir ? dir->altura : -1;

        // Retorna o fator de balanceamento do nó
        return alt_esq - alt_dir;
    }

    /**
     * @brief Atualiza a altura do nó.
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

/**
 * @class AVL
 * @brief Classe que representa uma árvore AVL (árvore binária de busca auto-balanceada).
 * 
 * @details A árvore AVL mantém seu balanceamento realizando rotações durante inserções e remoções. Isso garante que a árvore permaneça balanceada, proporcionando complexidade de tempo O(log n) para operações de busca, inserção e remoção.
 */
class AVL
{
private:
    
    No *raiz; 

    /**
     * @brief Insere um nó na árvore AVL.
     * 
     * @param z Ponteiro para o nó a ser inserido.
     */
    void insere(No *z) {
        
        // Auxiliares
        No *y = nullptr;
        No *x = raiz;


        while (x != nullptr) {
            
            // Aponta para o nó atual
            y = x;

            // Verifica se z é menor que a raiz
            if (z->codigo < x->codigo) 
                x = x->esq;
            else 
                x = x->dir;
        }

        // Definição da mãe de z
        z->mae = y;

        // Se a árvore estiver vazia, z é a raiz
        if (y == nullptr) 
            raiz = z;
        else 
            // Verifica se z é menor que o auxiliar
            if (z->codigo < y->codigo) 
                y->esq = z;
            else 
                y->dir = z;

        // Verifica se z é raiz
        if (z->eh_raiz())
            return;
        
        // Ajusta o balanceamento da árvore
        do { 
            z = z->mae;
            z = ajusta_balanceamento(z, true);
        } while (
            !z->eh_raiz() and z->bal() != 0
        );
    };

    /**
     * @brief Busca um nó com uma chave específica na árvore AVL.
     * 
     * @param x Ponteiro para o nó de onde a busca começa.
     * @param k A chave a ser buscada.
     * @return Ponteiro para o nó com a chave especificada, ou nullptr se não encontrado.
     */
    No *busca(No *x, int k) {
        // Caso o nó inicial seja nulo ou a chave seja igual à chave do nó
        if (x == nullptr || x->codigo == k)
            return x;
        // Caso a chave seja menor que a chave do nó, busca à esquerda
        if (k < x->codigo) 
            return busca(x->esq, k);
        else
            return busca(x->dir, k);
    };

    /**
     * @brief Encontra o nó com a menor chave a partir de um nó específico.
     * 
     * @param x Ponteiro para o nó de onde a busca começa.
     * @return Ponteiro para o nó com a chave mínima.
     */
    No *minimo(No *x) {
        // Enquanto houver um nó à esquerda, o nó atual é substituído pelo filho esquerdo
        while (x->esq != nullptr) 
            x = x->esq;
        return x;
    };

    /**
     * @brief Encontra o nó com a maior chave a partir de um nó específico.
     * 
     * @param x Ponteiro para o nó de onde a busca começa.
     * @return Ponteiro para o nó com a chave máxima.
     */
    No *maximo(No *x) {
        // Enquanto houver um nó à direita, o nó atual é substituído pelo filho direito
        while (x->dir != nullptr) 
            x = x->dir;
        return x;
    };

    /**
     * @brief Transplanta uma subárvore enraizada no nó v para a posição do nó u.
     * 
     * @param u Ponteiro para o nó a ser substituído.
     * @param v Ponteiro para o nó que substituirá u.
     */
    void transplante(No *u, No *v) {
        
        if (u->eh_raiz()) 
            raiz = v;
        else if (u->eh_esquerdo()) 
            u->mae->esq = v;
        else 
            u->mae->dir = v;
        
        // Se houver um nó v
        if (v != nullptr) 
            // O nó v recebe a mãe do nó u
            v->mae = u->mae;
    };

    /**
     * @brief Ajusta o balanceamento da árvore AVL após inserção ou remoção.
     * 
     * @param p Ponteiro para o nó de onde o ajuste de balanceamento começa.
     * @param girou Booleano indicando se uma rotação ocorreu.
     * @return Ponteiro para o nó após o ajuste de balanceamento.
     */
    No *ajusta_balanceamento(No *p, bool girou) {
        
        // Atualiza a altura do nó
        p->atualiza_altura();
        
        // Obtém o balanceamento do nó
        int balance = p->bal();

        // Caso 1: Se o balanceamento de p for 2, o nó está desbalanceado para a esquerda | Rotação à direita ou dupla à direita.
        if (balance == 2) {

            // Se o fator de balanceamento do filho esquerdo for maior ou igual a zero
            if (p->esq->bal() >= 0) { 
                
                // Caso 1.1: Rotação à direita  
                if (girou) 
                    std::cout << ">> Rotação direita (Caso 1.1)\n";
                rotacao_dir(p);

            } else { // Se o fator de balanceamento do filho esquerdo for menor que zero
                
                // Caso 1.2: Rotação dupla direita
                if (girou) 
                    std::cout << ">> Rotação dupla direita (Caso 1.2)\n";
                rotacao_dupla_dir(p);

            }
            
            // Atualiza o nó mãe
            p = p->mae;

        } else
            
            // Caso 2: Se o balanceamento for -2, o nó está desbalanceado para a direita | Rotação à esquerda ou dupla à esquerda.
            if (balance == -2) {
                
                // Se o fator de balanceamento do filho direito for menor ou igual a zero
                if (p->dir->bal() <= 0) {

                    // Caso 2.1: Rotação à esquerda
                    if (girou) 
                        std::cout << ">> Rotação esquerda (Caso 2.1)\n";
                    rotacao_esq(p);
                
                } else { // Se o fator de balanceamento do filho direito for maior que zero
                    
                    // Caso 2.2: Rotação dupla esquerda
                    if (girou) 
                        std::cout << ">> Rotação dupla esquerda (Caso 2.2)\n";
                    rotacao_dupla_esq(p);
                }
                // Atualiza o nó mãe
                p = p->mae;
            }
        
        // Retorna o nó após o ajuste de balanceamento
        return p;
    };

    /**
     * @brief Remove um nó da árvore AVL.
     * 
     * @param z Ponteiro para o nó a ser removido.
     */
    void remove(No *z) {
        
        
        No *p = nullptr;
        
        if (z->esq == nullptr) { 

            p = z->mae; 
            transplante(z, z->dir);
        }
        else {
            
            if (z->dir == nullptr) { 
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

                if (p == nullptr) 
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
    };

    /**
     * @brief Limpa a árvore AVL a partir de um nó específico.
     * 
     * @param x Ponteiro para o nó de onde a limpeza começa.
     */
    void limpa(No *x) {
        if (x == NULL)
            return;

        limpa(x->esq);
        limpa(x->dir);
        delete x;
    };

    /**
     * @brief Copia uma árvore AVL para a árvore atual a partir da raiz.
     * 
     * @param T Referência para a árvore AVL a ser copiada.
     */
    void copia(const AVL& T) {
        if (T.raiz == nullptr)
            raiz = nullptr;
        else {
            raiz = new No(T.raiz->codigo);
            copia(raiz, T.raiz);
        }
    };

    /**
     * @brief Copia uma subárvore de um nó de origem para um nó de destino.
     * 
     * @param dest Ponteiro para o nó de destino.
     * @param orig Ponteiro para o nó de origem.
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
    };

    /**
     * @brief Realiza uma rotação à direita em um nó específico.
     * 
     * @param p Ponteiro para o nó a ser rotacionado.
     */
    void rotacao_dir(No *p) {
        
        No *u = p->esq;
        
        // arruma u e sua mãe (a mãe de p)
        transplante(p, u);
        
        // move p para a direita de u, e o filho direito de u para a esquerda de p
        p->mae = u;
        p->esq = u->dir;
        u->dir = p;
        
        if (p->esq) {
            // arruma a mãe do filho esquerdo de p
            p->esq->mae = p;
        }

        // atualiza alturas
        p->atualiza_altura();
        u->atualiza_altura();
    };

    /**
     * @brief Realiza uma rotação à esquerda em um nó específico.
     * 
     * @param p Ponteiro para o nó a ser rotacionado.
     */
    void rotacao_esq(No *p) {
        
        No *u = p->dir;
        
        // arruma u e sua mãe (a mãe de p)
        transplante(p, u);

        // move p para a esquerda de u, e o filho esquerdo de u para a direita de p
        p->mae = u;
        p->dir = u->esq;
        u->esq = p;
        
        if (p->dir) { 
            p->dir->mae = p;
        };

        // atualiza alturas
        p->atualiza_altura();
        u->atualiza_altura();
    };

    /**
     * @brief Realiza uma rotação dupla à direita em um nó específico.
     * 
     * @param p Ponteiro para o nó a ser rotacionado.
     */
    void rotacao_dupla_dir(No *p) {
        rotacao_esq(p->esq);
        rotacao_dir(p);
    };

    /**
     * @brief Realiza uma rotação dupla à esquerda em um nó específico.
     * 
     * @param p Ponteiro para o nó a ser rotacionado.
     */
    void rotacao_dupla_esq(No *p) {
        rotacao_dir(p->dir);
        rotacao_esq(p);
    };

    /**
     * @brief Une duas árvores AVL.
     *
     * @param x Ponteiro para o nó raiz da árvore a ser unida.
     * @param destino Referência para a árvore AVL onde o resultado será armazenado.
     */
    void uniao(No *x, AVL &destino)
    {
        if (x != nullptr)
        {
            // Insere o código do nó atual na árvore de destino
            destino.insere(x->codigo);
            // Chama recursivamente para o filho esquerdo e direito
            uniao(x->esq, destino);
            uniao(x->dir, destino);
        }
    };

    /**
     * @brief Intersecciona duas árvores AVL e armazena o resultado em uma terceira árvore.
     * 
     * @param x Ponteiro para o nó raiz da primeira árvore.
     * @param T2 Referência para a segunda árvore AVL.
     * @param T3 Referência para a árvore AVL onde o resultado será armazenado.
     */
    void intersecao(No *x, AVL &T2, AVL &T3) {
        if (x != nullptr) {
            if (T2.busca(x->codigo) != nullptr) 
                T3.insere(x->codigo);
            
            intersecao(x->esq, T2, T3);
            intersecao(x->dir, T2, T3);
        }
    };

    /**
     * @brief Busca elementos dentro de um intervalo de chaves.
     * 
     * @param x Ponteiro para o nó de onde a busca começa.
     * @param min O valor mínimo da chave.
     * @param max O valor máximo da chave.
     */
    void busca_intervalo(No *x, int min, int max) {
        
        // Verifica se existe um nó
        if (x == nullptr) {
            return;
        }

        
        // Verifica se o nó à esquerda está dentro do intervalo
        if (x->codigo > min) {
            busca_intervalo(x->esq, min, max);
        }

        // Percorre nó por nó e verifica se ele está dentro do intervalo, caso esteja, imprime o código
        if (x->codigo >= min && x->codigo <= max) {
            x->escreve("\n");
        }

        // Verifica se o nó à direita está dentro do intervalo
        if (x->codigo < max) {
            busca_intervalo(x->dir, min, max);
        }
    };
    

public:
    /**
     * @brief Construtor padrão para a árvore AVL.
     */
    AVL() {
        raiz = nullptr;
    };

    /**
     * @brief Construtor de cópia para a árvore AVL.
     * 
     * @param outro Referência para a árvore AVL a ser copiada.
     */
    AVL(const AVL& outro) {
        copia(outro);
    };

    /**
     * @brief Destrutor para a árvore AVL.
     */
    ~AVL() {
        limpa();
    };

    /**
     * @brief Operador de atribuição para a árvore AVL.
     * 
     * @param outro Referência para a árvore AVL a ser atribuída.
     * @return Referência para a árvore AVL atribuída.
     */
    AVL& operator=(const AVL& outro) {
        limpa();
        copia(outro);
        return *this;
    };

    /**
     * @brief Obtém o nó raiz da árvore AVL.
     * 
     * @return Ponteiro para o nó raiz.
     */
    No *get_raiz() {
        return raiz;
    };

    /**
     * @brief Busca um nó com uma chave específica na árvore AVL.
     * 
     * @param k A chave a ser buscada.
     * @return Ponteiro para o nó com a chave especificada, ou nullptr se não encontrado.
     */
    No *busca(int k) {
        return busca(raiz, k);
    };

    /**
     * @brief Encontra o nó com a chave mínima na árvore AVL.
     * 
     * @return Ponteiro para o nó com a chave mínima.
     */
    No *minimo() {
        return minimo(raiz);
    };

    /**
     * @brief Encontra o nó com a chave máxima na árvore AVL.
     * 
     * @return Ponteiro para o nó com a chave máxima.
     */
    No *maximo() {
        return maximo(raiz);
    };

    /**
     * @brief Encontra o sucessor de um nó específico.
     * 
     * @param x Ponteiro para o nó cujo sucessor será encontrado.
     * @return Ponteiro para o nó sucessor.
     */
    No *sucessor(No *x) {
        if (x->dir != nullptr) 
            return minimo(x->dir);
        
        No *y = x->mae;
        while (y != nullptr && x == y->dir) {
            x = y;
            y = y->mae;
        }
        return y;
    };

    /**
     * @brief Encontra o predecessor de um nó específico.
     * 
     * @param x Ponteiro para o nó cujo predecessor será encontrado.
     * @return Ponteiro para o nó predecessor.
     */
    No *predecessor(No *x) {
        if (x->esq != nullptr) 
            return maximo(x->esq);
        
        No *y = x->mae;
        while (y != nullptr && x == y->esq) {
            x = y;
            y = y->mae;
        }
        return y;
    };

    /**
     * @brief Insere um nó com uma chave específica na árvore AVL.
     * 
     * @param codigo A chave do nó a ser inserido.
     */
    void insere(int codigo) {
        No *z = new No(codigo);
        insere(z);
    };

    /**
     * @brief Remove um nó com uma chave específica da árvore AVL.
     * 
     * @param codigo A chave do nó a ser removido.
     * @return True se o nó foi removido, false caso contrário.
     */
    bool remove(int codigo) {
        No *z = busca(codigo);
        if (z == nullptr) 
            return false;
        
        remove(z);
        return true;
    };

    /**
     * @brief Limpa a árvore AVL.
     */
    void limpa() {
        limpa(raiz);
        raiz = nullptr;
    };

    /**
     * @brief Une a árvore AVL atual com outra árvore AVL.
     *
     * @param T Referência para a árvore AVL a ser unida.
     * @param destino Referência para a árvore AVL onde o resultado será armazenado.
     */
    void uniao(AVL &T, AVL &destino)
    {
        uniao(this->raiz, destino);
        uniao(T.raiz, destino);
    }

    /**
     * @brief Intersecciona duas árvores AVL e armazena o resultado em uma terceira árvore.
     * 
     * @param T1 Referência para a primeira árvore AVL.
     * @param T2 Referência para a segunda árvore AVL.
     * @param T3 Referência para a árvore AVL onde o resultado será armazenado.
     */
    void intersecao(AVL &T1, AVL &T2, AVL &T3) {
        intersecao(T1.raiz, T2, T3);
    };

    /**
     * @brief Busca elementos dentro de um intervalo de chaves.
     * 
     * @param min O valor mínimo da chave.
     * @param max O valor máximo da chave.
     */
    void busca_intervalo(int min, int max) {
        busca_intervalo(raiz, min, max);
    };

    /**
     * @brief Escreve a árvore AVL na saída padrão.
     * 
     * @param prefixo A string de prefixo para formatar a saída.
     * @param x Ponteiro para o nó de onde a escrita começa.
     */
    void escreve(const char* prefixo = "", No* x = nullptr, bool isLeft = true) {
        if (x != nullptr) {
            std::cout << prefixo;
            std::cout << (isLeft ? "├── " : "└── ");
            x->escreve("\n");

            // Cria novos prefixos para os filhos esquerdo e direito
            char novoPrefixoEsq[100];
            char novoPrefixoDir[100];

            copia_string(novoPrefixoEsq, prefixo);
            copia_string(novoPrefixoDir, prefixo);

            if (isLeft) {
                concatena_string(novoPrefixoEsq, "│   ");
                concatena_string(novoPrefixoDir, "    ");
            } else {
                concatena_string(novoPrefixoEsq, "    ");
                concatena_string(novoPrefixoDir, "    ");
            }

            escreve(novoPrefixoEsq, x->esq, true);
            escreve(novoPrefixoDir, x->dir, false);
        }
    };
    /**
     * @brief Copia uma string para outra.
     * @param destino Ponteiro para a string de destino.
     * @param origem Ponteiro para a string de origem.
     */
    void copia_string(char *destino, const char *origem) {
        while (*origem)
        {
            *destino++ = *origem++;
        }
        *destino = '\0';
    }

    /**
     * @brief Concatena uma string a outra.
     * @param destino Ponteiro para a string de destino.
     * @param origem Ponteiro para a string de origem.
     */
    void concatena_string(char *destino, const char *origem) {
        while (*destino)
        {
            destino++;
        }
        copia_string(destino, origem);
    };
};


/**
 * @brief Conta o número de linhas em um arquivo de texto.
 * 
 * @param filename O nome do arquivo de texto.
 * @return O número de linhas no arquivo.
 */
int contar_linhas(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    int linhas = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            linhas++;
        }
    }

    if (ferror(file))
    {
        std::cerr << "Erro de leitura no arquivo: " << filename << std::endl;
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    return linhas;
}

/**
 * @brief Lê um arquivo de texto e retorna um vetor de inteiros.
 * 
 * @param filename O nome do arquivo de texto.
 * @return Um vetor de inteiros lidos do arquivo.
 */
void ler_arquivo(const char *filename, int valores[], int &tamanho)
{
    tamanho = contar_linhas(filename);
    if (tamanho > MAX)
    {
        std::cerr << "O arquivo contém mais elementos do que o tamanho máximo permitido ("
                  << MAX << "). Redefina o limite.\n";
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    // Lê os valores do arquivo

    
    int i = 0;
    while (fscanf(file, "%d", &valores[i]) != EOF && i < tamanho)
    {
        i++;
    }

    if (ferror(file))
    {
        std::cerr << "Erro de leitura no arquivo: " << filename << std::endl;
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

int main(int argc, char *argv[])
{

    AVL T1, T2, T3_intersecao, T3_uniao;

    int opcao;
    do
    {

        std::cout << "\n## --------- Menu de Opções ---------\n"
                  << "1: Inserir o código dos itens\n"
                  << "2: Buscar um item em uma das duas árvores\n"
                  << "3: Remover um item em uma das duas árvores\n"
                  << "4: Unir T1 e T2\n"
                  << "5: Interseccionar T1 e T2\n"
                  << "6: Buscar elementos em um intervalo\n"
                  << "7: Sair do programa\n\n"
                  << ">> Escolha uma opção: ";
        std::cin >> opcao;

        // Verificar se a entrada falhou devido a dados inválidos
        if (opcao < 1 || opcao > 7)
        {
            std::cerr << "\n\n>> Opção inválida! Tente novamente. <<\n";
            continue; // Retorna ao menu
        };

        switch (opcao)
        {
        // --------------- Inserção ----------------
        case 1:
        {
            int v1[MAX], v2[MAX];
            int tamanho_v1, tamanho_v2;
            char arquivo1[MAX], arquivo2[MAX];
            
            std::cout << "\nDigite o nome do primeiro arquivo: ";
            std::cin >> arquivo1;
            ler_arquivo(arquivo1, v1, tamanho_v1);

            std::cout << "Digite o nome do segundo arquivo: ";
            std::cin >> arquivo2;
            ler_arquivo(arquivo2, v2, tamanho_v2);

            std::cout << "\n\n## Inserção de produtos em T1 e T2\n\n";
            for (int i = 0; i < tamanho_v1; ++i)
                T1.insere(v1[i]);
            for (int i = 0; i < tamanho_v2; ++i)
                T2.insere(v2[i]);

            std::cout << "T1:\n";
            T1.escreve("", T1.get_raiz());
            std::cout << "T2:\n";
            T2.escreve("", T2.get_raiz());

            break;
        }

        // --------------- Busca ----------------
        case 2:
        {
            int valor_busca, arvore;
            
            if (!T1.get_raiz() || !T2.get_raiz())
            {
                std::cerr << "\n>>> Árvores vazias. Insira elementos primeiro. <<<\n";
                break;
            } else {
                std::cout << "\n\n>> Insira o número da árvore (1 para T1, 2 para T2): ";
                std::cin >> arvore;
                std::cout << "\n>>> Insira um valor para buscar: ";
                std::cin >> valor_busca;

                AVL *tree = (arvore == 1) ? &T1 : &T2;
                No *n = tree->busca(valor_busca);
                if (n != nullptr)
                {
                    std::cout << "\nValor " << valor_busca << " encontrado! \n";
                    tree->escreve("", n);
                }
                else
                {
                    std::cout << "Não encontrado.\n";
                }
                break;
            }

        }

        // ----------- Remoção ------------
        case 3:
        {
            int valor_remover, arvore;  
            if (!T1.get_raiz() || !T2.get_raiz())
            {
                std::cerr << "\n>>> Árvores vazias. Insira elementos primeiro. <<<\n";
                break;
            } else {
                
                std::cout << "\nInsira o número da árvore (1 para T1, 2 para T2): ";
                std::cin >> arvore;
                
                std::cout << "\n>> Insira um valor para remover: ";
                std::cin >> valor_remover;

                AVL *tree = (arvore == 1) ? &T1 : &T2;
                std::cout << "\nÁrvore antes da remoção:\n\n";
                tree->escreve("", tree->get_raiz());
                tree->remove(valor_remover);
                std::cout << "\nÁrvore após a remoção:\n\n";
                tree->escreve("", tree->get_raiz());
                break;
            }

            break;
        }
        
        // --------------- União ----------------
        case 4:
        {
            std::cout << "\n\n## União de T1 e T2\n";
            if (!T1.get_raiz() || !T2.get_raiz())
            {
                std::cerr << "\n>>> Árvores vazias. Insira elementos primeiro. <<<\n";
                break;
            } else {
                T1.uniao(T2, T3_uniao);
                T3_uniao.escreve("", T3_uniao.get_raiz());
                break;
            }
        }
        
        // ---------------- Interseção ----------------
        case 5:
        {
            std::cout << "\n\n## Interseção de T1 e T2\n";
            if (!T1.get_raiz() || !T2.get_raiz())
            {
                std::cerr << "\n>>> Árvores vazias. Insira elementos primeiro. <<<\n";
                break;
            } else {
                    
                T3_intersecao.intersecao(T1, T2, T3_intersecao);
                T3_intersecao.escreve("", T3_intersecao.get_raiz());
                break;  
            }
        }

        // ---------------- Busca em intervalo ----------------
        case 6:
        {
            int valor_min, valor_max, arvore;
            

            if (!T1.get_raiz() || !T2.get_raiz())
            {
                std::cerr << "\n>>> Árvores vazias. Insira elementos primeiro. <<<\n";
                break;
            } else if (arvore != 1 || arvore != 2)
            {
                std::cerr << "\n>>> Opção inválida. Insira 1 para T1 ou 2 para T2. <<<\n";
                break;
            } else {
                std::cout << "\n\n>> Insira o número da árvore (1 para T1, 2 para T2): ";
                std::cin >> arvore;
                std::cout << "\n>>> Insira o valor mínimo: ";
                std::cin >> valor_min;
                std::cout << "\n>>> Insira o valor máximo: ";
                std::cin >> valor_max;

                AVL *tree = (arvore == 1) ? &T1 : &T2;
                tree->busca_intervalo(valor_min, valor_max);
                break;
            }
        }
        
        // ------------ Sair ------------
        case 7:
        {
            std::cout << "\n\n>> Saindo do programa >>\n";
            break;
        }

        // ---------------- Opção inválida ----------------
        default:
        {
            std::cerr << "\n\n>> Opção inválida! Tente novamente. <<\n";
        }
        }
    
    } while (opcao != 7);

    // Liberar toda memória nas árvores
    T1.limpa();
    T2.limpa();
    T3_intersecao.limpa();
    T3_uniao.limpa();

    return 0;
}
