################################################################################
#		Makefile - Compila um conjunto de código em C++, criado originalmente 
# por Rodrigo Siqueira, modificado por Charles Oliveira
#
#Este Makefile tem por objetivo juntar o código feito com base na seguinte 
#estrutura de arquivos:
#	- inc: Pasta que contém todos os .h do aplicativo.
#	- src: Pasta contendo todas as implementações dos arquivos .h.
#	- bin: Pasta contendo o aplicativo compilado.
#	- obj: Pasta contendo os arquivos objetos do projeto.
#Basicamente este Makefile gera todos os arquivos objetos de início e logo
#em seguida gera o arquivo binário. Vale observar que este Makefile também
#possui alvos para compilar testes unitários individualmente ou todos de uma
#vez.
#
#Exemplo:
#	$make						$make clean
#	Gera aquivos objetos		Remove todos os arquivos objetos da pasta obj
#	Gera arquivo binário		Remove os arquivos binários	da pasta bin
################################################################################

################################################################################
#######################                               ##########################
####################### Incializa as variáveis usadas ##########################
#######################                               ##########################
################################################################################
#Diretórios
PACKBIN		= 	bin
PACKINC		=	inc
PACKSRC		=	src	
PACKOBJ		=	obj
#Flags
CC			= g++
LPTHREAD	= -lpthread
SDL			= `sdl-config --libs --cflags`
CUNIT		= -lcunit
CFLAGS		= -Wall -I./$(PACKINC)
#Monta uma lista com todos os arquivos fontes em código C
CSOURCES	= $(wildcard src/*cpp)

################################################################################
##############################             #####################################
##############################    ALVOS    #####################################
##############################             #####################################
################################################################################

all: game

################################################################################
#	Alvo principal, cujo objetivo é gerar o binário do aplicativo. As
#	dependências inseridas são feitas por meio de: $(CSOURCES:src/%.c=obj/%.o)
#	*Basicamente captura todos os elementos da lista e troca os trechos
#	 com "src/%.c" por "obj/%.o".
#	 Por exemplo: incialmente temos "src/nome_do_arquivo.c", a operação faz
#		com que a mesma passe a ser "obj/nome_do_arquivo.o".
#	*Após ter feito a troca, a dependência chama o alvo inciado por obj/%.o.
################################################################################

game: $(CSOURCES:src/%.cpp=obj/%.o)
	$(CC) $(CFLAGS) $^ -o bin/$@ $(LPTHREAD) $(SDL)
	
################################################################################
#Alvo gerador de arquivos objetos.
#Este faz uso do caracter % para torna-lo o mais genérico possível. Repare que
#o alvo FSO_BANK fará uso ostensivo deste alvo, pois todas as dependências deste
#foram marcada para obj/%.o
################################################################################

obj/%.o: src/%.cpp
	$(CC) $(FLAGS) -c $< -o $@ $(CFLAGS) 

################################################################################
###############################                       ##########################
###############################   TESTES DE UNIDADE   ##########################
###############################						  ##########################
################################################################################

################################################################################
#	Alvo para executar o suite de teste do arquivo rs232.c Este alvo é bem
#	especifico, por ter a referência
#	inserida diretamente nele.
################################################################################
suiteRS232: unitaryTest/CU_rs232.c obj/rs232.o
	$(CC) $(CFLAGS) $^ -o bin/$@ $(CUNIT)

suiteRSGAMA: unitaryTest/CU_rsGama.c obj/rsGama.o
	$(CC) $(CFLAGS) $^ -o bin/$@ $(CUNIT)

## Alvo responsável por excluir arquivos gerados na pasta obj e bin
clean:
	rm -f obj/*
	rm -f bin/*

