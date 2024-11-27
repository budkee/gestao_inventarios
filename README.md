# Sistema de Gestão de Inventários
## Descrição
Este trabalho consiste na implementação de um sistema de gestão de inventários utilizando estruturas de dados avançadas. O objetivo é aplicar conceitos de árvores balanceadas (AVL) para gerenciar e organizar os itens de um inventário (árvore) de forma eficiente.

## Funcionalidades
- Adicionar itens ao inventário
- Buscar itens no inventário
- Remover itens do inventário
- Unir dois inventários
- Interseccionar dois inventários
- Busca de itens dado um intervalo

## Como Testar
1. Clone o repositório para sua máquina local:

- Via HTTPS

    ```sh
    git clone https://github.com/usuario/gestao_inventarios.git
    ```
    `ou`

- Via SSH

    ```sh
    git clone git@github.com:budkee/gestao_inventarios.git
    ```

2. Navegue até o diretório do projeto:
   
    ```sh
    cd gestao_inventarios
    ```

3. Compile o código:
    ```sh
    g++ -Wall -pedantic -std=c++11 -g -o programa.out operacoes_AVL.cpp
    ```
4. Execute o programa:
    ```sh
    ./programa.out
    ```
5. Siga as instruções exibidas no terminal para interagir com o sistema de gestão de inventários.

<<<<<<< HEAD
6. Caso queira verificar se existe vazamento de memória com o valgrind e está em um ambiente Linux, execute:

    ```sh
     valgrind --leak-check=full --show-reachable=yes --track-fds=yes ./programa.out operacoes_AVL.cpp
    ```

    1. Caso não esteja em Linux, é possível executar a imagem no Dockerfile para executar em um container Docker. 
        
        - Para isso, será necessário instalar Docker na sua máquina.
        - Dentro do diretório do projeto, execute:
        ```sh/bash/zsh
            docker build -t valgrind .
        ```
        - Isso vai fazer você construir a imagem a partir do Dockerfile.
        - Em seguida, levante um container com o seguinte comando:
        ```sh/bash/zsh
            docker run --name ubuntu_valgrind -it valgrind
        ```

=======
6. Verifique se existe vazamento no programa.
    ``` sh
    valgrind --leak-check=full --show-reachable=yes --track-fds=yes ./programa.out operacoes_AVL.cpp    
    ```

>>>>>>> ecad7ae5afe5b502310fa069cfb9482312561799
## Estrutura do Projeto

- `README.md`: Este arquivo, contendo a descrição do projeto e instruções de uso.
- `operacoes_AVL.cpp`: Código-fonte do programa.
- `T1.txt` e `T2.txt`: Código das árvores.
- `Dockerfile`: Imagem (Ubuntu) para teste com o `valgrind`.

## Requisitos

- G++
- Sistema operacional Unix-like (Linux, macOS)

## Contribuições
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests.

## Licença
Este projeto está licenciado sob a Licença MIT. Veja o arquivo `LICENSE` para mais detalhes.

