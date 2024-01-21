# Nome do executável a ser gerado
TARGET = labyrinth

# Compilador a ser utilizado
CC = gcc

# Flags de compilação
# CFLAGS = -Wall -Wextra -Werror -std=c99
CFLAGS = -Wall -Wextra -std=c99

# Arquivos fonte
SRCS = $(TARGET).c

# Objetos gerados pela compilação
OBJS = $(SRCS:.c=.o)

# Regra de compilação padrão
all: $(TARGET)

# Regra para compilar os arquivos objeto
$(TARGET): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Regra para compilar os arquivos fonte em arquivos objeto
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados pela compilação
clean:
		rm -f $(OBJS) $(TARGET)
