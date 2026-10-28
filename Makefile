CC=g++
CFLAGS=-std=c++11 -Wall -Iinclude

all: main

build/AtividadeAvaliativa.o: include/AtividadeAvaliativa.hpp include/Data.hpp include/CalculadorConceito.hpp include/CalculadorMedia.hpp src/AtividadeAvaliativa.cpp
	${CC} ${CFLAGS} -c src/AtividadeAvaliativa.cpp -o build/AtividadeAvaliativa.o

build/CalculadorConceito.o: include/CalculadorConceito.hpp src/CalculadorConceito.cpp
	${CC} ${CFLAGS} -c src/CalculadorConceito.cpp -o build/CalculadorConceito.o

build/CalculadorMaxFaltas.o: include/CalculadorMaxFaltas.hpp src/CalculadorMaxFaltas.cpp
	${CC} ${CFLAGS} -c src/CalculadorMaxFaltas.cpp -o build/CalculadorMaxFaltas.o

build/CalculadorMedia.o: include/CalculadorMedia.hpp src/CalculadorMedia.cpp
	${CC} ${CFLAGS} -c src/CalculadorMedia.cpp -o build/CalculadorMedia.o

build/ControleFrequencia.o: include/ControleFrequencia.hpp src/ControleFrequencia.cpp
	${CC} ${CFLAGS} -c src/ControleFrequencia.cpp -o build/ControleFrequencia.o

build/Curso.o: include/Curso.hpp include/Semestre.hpp src/Curso.cpp
	${CC} ${CFLAGS} -c src/Curso.cpp -o build/Curso.o

build/Data.o: include/Data.hpp src/Data.cpp
	${CC} ${CFLAGS} -c src/Data.cpp -o build/Data.o

build/DiarioAtividades.o: include/DiarioAtividades.hpp include/AtividadeAvaliativa.hpp include/CalculadorConceito.hpp include/CalculadorMedia.hpp src/DiarioAtividades.cpp
	${CC} ${CFLAGS} -c src/DiarioAtividades.cpp -o build/DiarioAtividades.o

build/Disciplina.o: include/Disciplina.hpp include/ControleFrequencia.hpp include/DiarioAtividades.hpp include/CalculadorMaxFaltas.hpp src/Disciplina.cpp
	${CC} ${CFLAGS} -c src/Disciplina.cpp -o build/Disciplina.o

build/Estudante.o: include/Estudante.hpp include/Curso.hpp include/HistoricoEscolar.hpp src/Estudante.cpp
	${CC} ${CFLAGS} -c src/Estudante.cpp -o build/Estudante.o

build/GerenciadorArquivo.o: include/GerenciadorArquivo.hpp include/Estudante.hpp src/GerenciadorArquivo.cpp
	${CC} ${CFLAGS} -c src/GerenciadorArquivo.cpp -o build/GerenciadorArquivo.o

build/HistoricoEscolar.o: include/HistoricoEscolar.hpp include/SemestreConsolidado.hpp include/SemestreAtual.hpp src/HistoricoEscolar.cpp
	${CC} ${CFLAGS} -c src/HistoricoEscolar.cpp -o build/HistoricoEscolar.o

build/Menu.o: include/Menu.hpp include/Estudante.hpp include/GerenciadorArquivo.hpp src/Menu.cpp
	${CC} ${CFLAGS} -c src/Menu.cpp -o build/Menu.o

build/MenuAtividadeAvaliativa.o: include/MenuAtividadeAvaliativa.hpp include/Menu.hpp include/Disciplina.hpp include/MenuPrincipal.hpp include/SemestreAtual.hpp include/AtividadeAvaliativa.hpp src/MenuAtividadeAvaliativa.cpp
	${CC} ${CFLAGS} -c src/MenuAtividadeAvaliativa.cpp -o build/MenuAtividadeAvaliativa.o

build/MenuCadastroUsuario.o: include/MenuCadastroUsuario.hpp include/Menu.hpp include/MenuPrincipal.hpp include/Semestre.hpp src/MenuCadastroUsuario.cpp
	${CC} ${CFLAGS} -c src/MenuCadastroUsuario.cpp -o build/MenuCadastroUsuario.o

build/MenuCarregarUsuario.o: include/MenuCarregarUsuario.hpp include/Menu.hpp include/MenuPrincipal.hpp include/MenuInicial.hpp src/MenuCarregarUsuario.cpp
	${CC} ${CFLAGS} -c src/MenuCarregarUsuario.cpp -o build/MenuCarregarUsuario.o

build/MenuDetalhamentoDisciplina.o: include/MenuDetalhamentoDisciplina.hpp include/Menu.hpp include/Disciplina.hpp include/MenuPrincipal.hpp include/SemestreAtual.hpp include/AtividadeAvaliativa.hpp src/MenuDetalhamentoDisciplina.cpp
	${CC} ${CFLAGS} -c src/MenuDetalhamentoDisciplina.cpp -o build/MenuDetalhamentoDisciplina.o

build/MenuDisciplina.o: include/MenuDisciplina.hpp include/Menu.hpp include/MenuPrincipal.hpp include/SemestreAtual.hpp include/Disciplina.hpp src/MenuDisciplina.cpp
	${CC} ${CFLAGS} -c src/MenuDisciplina.cpp -o build/MenuDisciplina.o

build/MenuFrequencia.o: include/MenuFrequencia.hpp include/Menu.hpp include/Disciplina.hpp include/MenuPrincipal.hpp include/SemestreAtual.hpp src/MenuFrequencia.cpp
	${CC} ${CFLAGS} -c src/MenuFrequencia.cpp -o build/MenuFrequencia.o

build/MenuInicial.o: include/MenuInicial.hpp include/Menu.hpp include/MenuCadastroUsuario.hpp include/MenuCarregarUsuario.hpp src/MenuInicial.cpp
	${CC} ${CFLAGS} -c src/MenuInicial.cpp -o build/MenuInicial.o

build/MenuPrincipal.o: include/MenuPrincipal.hpp include/Menu.hpp include/MenuDisciplina.hpp include/MenuAtividadeAvaliativa.hpp include/MenuFrequencia.hpp include/MenuDetalhamentoDisciplina.hpp src/MenuPrincipal.cpp
	${CC} ${CFLAGS} -c src/MenuPrincipal.cpp -o build/MenuPrincipal.o

build/SeletorMenu.o: include/SeletorMenu.hpp include/Menu.hpp include/Estudante.hpp include/GerenciadorArquivo.hpp include/MenuInicial.hpp src/SeletorMenu.cpp
	${CC} ${CFLAGS} -c src/SeletorMenu.cpp -o build/SeletorMenu.o

build/Semestre.o: include/Semestre.hpp src/Semestre.cpp
	${CC} ${CFLAGS} -c src/Semestre.cpp -o build/Semestre.o

build/SemestreAtual.o: include/SemestreAtual.hpp include/Semestre.hpp include/Disciplina.hpp src/SemestreAtual.cpp
	${CC} ${CFLAGS} -c src/SemestreAtual.cpp -o build/SemestreAtual.o

build/SemestreConsolidado.o: include/SemestreConsolidado.hpp include/Semestre.hpp src/SemestreConsolidado.cpp
	${CC} ${CFLAGS} -c src/SemestreConsolidado.cpp -o build/SemestreConsolidado.o

build/main.o: include/Estudante.hpp include/GerenciadorArquivo.hpp include/SeletorMenu.hpp src/main.cpp
	${CC} ${CFLAGS} -c src/main.cpp -o build/main.o

main: build/main.o build/AtividadeAvaliativa.o build/CalculadorConceito.o build/CalculadorMaxFaltas.o build/CalculadorMedia.o build/ControleFrequencia.o build/Curso.o build/Data.o build/DiarioAtividades.o build/Disciplina.o build/Estudante.o build/GerenciadorArquivo.o build/HistoricoEscolar.o build/Menu.o build/MenuAtividadeAvaliativa.o build/MenuCadastroUsuario.o build/MenuCarregarUsuario.o build/MenuDetalhamentoDisciplina.o build/MenuDisciplina.o build/MenuFrequencia.o build/MenuInicial.o build/MenuPrincipal.o build/SeletorMenu.o build/Semestre.o build/SemestreAtual.o build/SemestreConsolidado.o
	${CC} ${CFLAGS} build/main.o build/AtividadeAvaliativa.o build/CalculadorConceito.o build/CalculadorMaxFaltas.o build/CalculadorMedia.o build/ControleFrequencia.o build/Curso.o build/Data.o build/DiarioAtividades.o build/Disciplina.o build/Estudante.o build/GerenciadorArquivo.o build/HistoricoEscolar.o build/Menu.o build/MenuAtividadeAvaliativa.o build/MenuCadastroUsuario.o build/MenuCarregarUsuario.o build/MenuDetalhamentoDisciplina.o build/MenuDisciplina.o build/MenuFrequencia.o build/MenuInicial.o build/MenuPrincipal.o build/SeletorMenu.o build/Semestre.o build/SemestreAtual.o build/SemestreConsolidado.o -o main

clean:
	rm -f main build/*.o