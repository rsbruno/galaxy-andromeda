# Use a imagem oficial do GCC C++ como base
FROM gcc:latest

# Defina o diretório de trabalho como /app
WORKDIR /app

COPY . /app/

# Comando padrão para compilar e executar o programa
CMD ["bash"]