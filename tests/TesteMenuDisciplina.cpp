#include "doctest.h"
#include "MenuDisciplina.hpp"
#include "SemestreAtual.hpp"
#include "Disciplina.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace 
{
    struct RedirecionadorIO 
    {
        std::stringstream entrada;
        std::stringstream saida;
        std::streambuf* cinOriginal;
        std::streambuf* coutOriginal;

        RedirecionadorIO(const std::string& textoEntrada = "") 
            : entrada(textoEntrada),
              cinOriginal(std::cin.rdbuf(entrada.rdbuf())),
              coutOriginal(std::cout.rdbuf(saida.rdbuf())) 
        {}

        ~RedirecionadorIO() 
        {
            std::cin.rdbuf(cinOriginal);
            std::cout.rdbuf(coutOriginal);
        }
    };
}

TEST_CASE("Exibicao do MenuDisciplina - Semestre vazio e com disciplinas") 
{
    SemestreAtual semestre("2026/02");
    MenuDisciplina menu(semestre);

    SUBCASE("Exibir com semestre vazio") 
    {
        RedirecionadorIO io;
        menu.exibir();

        std::string textoImpresso = io.saida.str();
        CHECK(textoImpresso.find("GERENCIAMENTO DE DISCIPLINAS") != std::string::npos);
        CHECK(textoImpresso.find("Nenhuma disciplina cadastrada no semestre atual.") != std::string::npos);
        CHECK(menu.substituirPilhaAoTransicionar() == false);
    }

    SUBCASE("Exibir com disciplina cadastrada") 
    {
        semestre.adicionarDisciplina("DCC204", "TZ1", "PDS II", "Prof", "ICEx 2010", 60, 100, "Obrigatoria", "Seg/Qua");
        RedirecionadorIO io;
        menu.exibir();

        std::string textoImpresso = io.saida.str();
        CHECK(textoImpresso.find("DCC204") != std::string::npos);
        CHECK(textoImpresso.find("TZ1") != std::string::npos);
        CHECK(textoImpresso.find("PDS II") != std::string::npos);
        CHECK(textoImpresso.find("60h") != std::string::npos);
        CHECK(textoImpresso.find("Obrigatoria") != std::string::npos);
    }
}

TEST_CASE("Processar Entrada - Navegacao basica, opcoes invalidas e EOF") 
{
    SemestreAtual semestre("2026/02");
    MenuDisciplina menu(semestre);

    SUBCASE("Opcao 0 - Voltar ao Menu Principal retorna nullptr") 
    {
        RedirecionadorIO io("0\n");
        Menu* proximoMenu = menu.processarEntrada();
        CHECK(proximoMenu == nullptr);
    }

    SUBCASE("Opcoes invalidas no menu principal repetem o laco ate ler 0") 
    {
        RedirecionadorIO io("-1\n4\nabc\n0\n");
        Menu* proximoMenu = menu.processarEntrada();

        CHECK(proximoMenu == nullptr);
        std::string textoImpresso = io.saida.str();
        CHECK(textoImpresso.find("[ERRO] Opcao invalida. Escolha entre 0 e 3.") != std::string::npos);
        CHECK(textoImpresso.find("Erro: Tipo de entrada incorreto. Tente novamente.") != std::string::npos);
    }

    SUBCASE("Excecao de Fim de Fluxo (EOF)") 
    {
        RedirecionadorIO io("");
        CHECK_THROWS_AS(menu.processarEntrada(), std::runtime_error);
    }
}

TEST_CASE("Fluxo Criar Disciplina - Happy Path, Tipos de Disciplina e Validacoes de Erro") 
{
    SemestreAtual semestre("2026/02");
    MenuDisciplina menu(semestre);

    SUBCASE("Happy Path - Criar disciplina Obrigatoria (Opcao 1)") 
    {
        std::string entradas =
            "1\n"
            "PDS II\n"
            "DCC204\n"
            "TZ1\n"
            "Professor Teste\n"
            "ICEx 2010\n"
            "60\n"
            "1\n"
            "Seg/Qua 19:00\n"
            "100\n";

        RedirecionadorIO io(entradas);
        Menu* retorno = menu.processarEntrada();

        CHECK(retorno == &menu);
        REQUIRE(semestre.getDisciplinas().size() == 1);
        const Disciplina* disc = semestre.buscarDisciplina(1);
        REQUIRE(disc != nullptr);
        CHECK(disc->getNome() == "PDS II");
        CHECK(disc->getCodigo() == "DCC204");
        CHECK(disc->getCodigoTurma() == "TZ1");
        CHECK(disc->getProfessor() == "Professor Teste");
        CHECK(disc->getSalaBloco() == "ICEx 2010");
        CHECK(disc->getCargaHoraria() == 60);
        CHECK(disc->getTipo() == "Obrigatoria");
        CHECK(disc->getHorarioDias() == "Seg/Qua 19:00");
        CHECK(disc->getDuracaoAulaMinutos() == 100);
        CHECK(io.saida.str().find("Disciplina 'PDS II' cadastrada com sucesso!") != std::string::npos);
    }

    SUBCASE("Happy Path - Criar disciplinas Optativa (2) e Formacao Livre (3)") 
    {
        std::string entradasOptativa =
            "1\n"
            "Topicos em IA\n"
            "DCC999\n"
            "TA\n"
            "Prof IA\n"
            "ICEx 1010\n"
            "60\n"
            "2\n"
            "Ter/Qui 14:00\n"
            "100\n";

        {
            RedirecionadorIO io(entradasOptativa);
            menu.processarEntrada();
        }

        std::string entradasLivre =
            "1\n"
            "Alemao I\n"
            "LET001\n"
            "TB\n"
            "Prof Letras\n"
            "FALE 300\n"
            "60\n"
            "3\n"
            "Sex 09:00\n"
            "100\n";

        {
            RedirecionadorIO io(entradasLivre);
            menu.processarEntrada();
        }

        REQUIRE(semestre.getDisciplinas().size() == 2);
        CHECK(semestre.buscarDisciplina(1)->getTipo() == "Optativa");
        CHECK(semestre.buscarDisciplina(2)->getTipo() == "Formacao Livre");
    }

    SUBCASE("Edge Cases - Erros de validacao em todos os campos antes de valores validos") 
    {
        std::string nomeLongo(23, 'A');
        std::string codigoLongo(9, 'B');
        std::string turmaLonga(7, 'C');
        std::string profLongo(101, 'D');
        std::string salaLonga(101, 'E');
        std::string horarioLongo(101, 'F');

        std::string entradas =
            "1\n" +
            nomeLongo + "\nPDS II\n" +
            codigoLongo + "\nDCC204\n" +
            turmaLonga + "\nTZ1\n" +
            profLongo + "\nProf\n" +
            salaLonga + "\nSala 1\n" +
            "50\n0\n60\n" +
            "0\n4\n1\n" +
            horarioLongo + "\nSeg/Qua\n" +
            "40\n50\n";

        RedirecionadorIO io(entradas);
        Menu* retorno = menu.processarEntrada();

        CHECK(retorno == &menu);
        REQUIRE(semestre.getDisciplinas().size() == 1);
        std::string textoImpresso = io.saida.str();
        CHECK(textoImpresso.find("O nome da disciplina deve ter entre 1 e 22 caracteres.") != std::string::npos);
        CHECK(textoImpresso.find("O codigo da disciplina deve ter entre 1 e 8 caracteres.") != std::string::npos);
        CHECK(textoImpresso.find("O codigo da turma deve ter entre 1 e 6 caracteres.") != std::string::npos);
        CHECK(textoImpresso.find("O nome do professor deve ter entre 1 e 100 caracteres.") != std::string::npos);
        CHECK(textoImpresso.find("A sala/bloco deve ter entre 1 e 100 caracteres.") != std::string::npos);
        CHECK(textoImpresso.find("A carga horaria deve ser maior que zero e divisivel por 15.") != std::string::npos);
        CHECK(textoImpresso.find("[ERRO] Opcao invalida. Escolha 1, 2 ou 3.") != std::string::npos);
        CHECK(textoImpresso.find("O horario e dias de aula devem ter entre 1 e 100 caracteres.") != std::string::npos);
        CHECK(textoImpresso.find("A duracao da aula deve ser de, no minimo, 50 minutos.") != std::string::npos);
    }
}