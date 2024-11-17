FROM ubuntu:latest

# Instala o Valgrind
RUN apt-get update && \
    apt-get install -y valgrind g++ && \
    apt-get clean


# Define o diretório de trabalho
WORKDIR /home

# Copia o código ou o binário para dentro do container (substitua com seu caminho)
COPY . /home/gestao_inventarios

# Define o comando padrão
CMD [ "/bin/bash" ]
