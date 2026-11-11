#include "doctest.h"
#include "TestHelpers.hpp"
#include "CalculadorMaxFaltas.hpp"

#include <stdexcept>
#include <string>

TEST_CASE("Disciplina::Disciplina [positivo] armazena todos os dados")
{
    Disciplina d = criarDisciplinaValida(7);

    CHECK(d.getId() == 7);
    CHECK(d.getCodigo() == "COD001");
    CHECK(d.getCodigoTurma() == "T1");
    CHECK(d.getNome() == "Programacao");
    CHECK(d.getProfessor() == "Prof. Ana");
    CHECK(d.getSalaBloco() == "Sala 101");
    CHECK(d.getCargaHoraria() == 60);
    CHECK(d.getDuracaoAulaMinutos() == 50);
    CHECK(d.getTipo() == "Obrigatoria");
    CHECK(d.getHorarioDias() == "Seg 10h");
}

TEST_CASE("Disciplina::Disciplina [positivo] calcula o limite de faltas")
{
    Disciplina d = criarDisciplinaValida();
    CHECK(d.frequencia().getMaxFaltas() == CalculadorMaxFaltas::calcularDiasMaximosFalta(60, 50));
}

TEST_CASE("Disciplina::Disciplina [positivo] inicia com zero faltas")
{
    Disciplina d = criarDisciplinaValida();
    CHECK(d.frequencia().getFaltasAtuais() == 0);
}

TEST_CASE("Disciplina::Disciplina [positivo] inicia sem atividades")
{
    Disciplina d = criarDisciplinaValida();
    CHECK(d.avaliacoes().getAtividades().empty());
}

TEST_CASE("Disciplina::Disciplina [limite] ID zero e aceito")
{
    CHECK_NOTHROW(criarDisciplinaValida(0));
}


TEST_CASE("Disciplina::Disciplina [negativo] ID negativo lanca excecao")
{
    CHECK_THROWS_AS(criarDisciplinaValida(-1), std::invalid_argument);
}

TEST_CASE("Disciplina::Disciplina [negativo] carga horaria invalida lanca excecao")
{
    CHECK_THROWS_AS(Disciplina(1, "C", "T", "N", "P", "S", 0, 50, "Optativa", "H"), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina(1, "C", "T", "N", "P", "S", -15, 50, "Optativa", "H"), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina(1, "C", "T", "N", "P", "S", 40, 50, "Optativa", "H"), std::invalid_argument);
}

TEST_CASE("Disciplina::Disciplina [limite] carga horaria minima (15h) e aceita")
{
    CHECK_NOTHROW(Disciplina(1, "C", "T", "N", "P", "S", 15, 50, "Optativa", "H"));
}

TEST_CASE("Disciplina::Disciplina [negativo] duracao da aula abaixo de 50 lanca excecao")
{
    CHECK_THROWS_AS(Disciplina(1, "C", "T", "N", "P", "S", 60, 49, "Optativa", "H"), std::invalid_argument);
}

TEST_CASE("Disciplina::Disciplina [limite] duracao de 50 minutos e aceita")
{
    CHECK_NOTHROW(Disciplina(1, "C", "T", "N", "P", "S", 60, 50, "Optativa", "H"));
}

TEST_CASE("Disciplina::Disciplina [negativo] campos de texto vazios lancam excecao")
{
    CHECK_THROWS_AS(Disciplina(1, "", "T", "N", "P", "S", 60, 50, "Optativa", "H"), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina(1, "C", "", "N", "P", "S", 60, 50, "Optativa", "H"), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina(1, "C", "T", "", "P", "S", 60, 50, "Optativa", "H"), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina(1, "C", "T", "N", "", "S", 60, 50, "Optativa", "H"), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina(1, "C", "T", "N", "P", "", 60, 50, "Optativa", "H"), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina(1, "C", "T", "N", "P", "S", 60, 50, "Optativa", ""), std::invalid_argument);
}

TEST_CASE("Disciplina::Disciplina [negativo] tipo invalido lanca excecao")
{
    CHECK_THROWS_AS(Disciplina(1, "C", "T", "N", "P", "S", 60, 50, "Invalido", "H"), std::invalid_argument);
}

// ============================================== Validadores estaticos
TEST_CASE("Disciplina::validarCodigo [limite] aceita de 1 a 8 caracteres")
{
    CHECK_NOTHROW(Disciplina::validarCodigo("A"));
    CHECK_NOTHROW(Disciplina::validarCodigo(std::string(8, 'X')));
}

TEST_CASE("Disciplina::validarCodigo [negativo] rejeita vazio e mais de 8 caracteres")
{
    CHECK_THROWS_AS(Disciplina::validarCodigo(""), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina::validarCodigo(std::string(9, 'X')), std::invalid_argument);
}

TEST_CASE("Disciplina::validarCodigoTurma [limite] aceita de 1 a 6 caracteres")
{
    CHECK_NOTHROW(Disciplina::validarCodigoTurma("A"));
    CHECK_NOTHROW(Disciplina::validarCodigoTurma(std::string(6, 'T')));
}

TEST_CASE("Disciplina::validarCodigoTurma [negativo] rejeita vazio e mais de 6 caracteres")
{
    CHECK_THROWS_AS(Disciplina::validarCodigoTurma(""), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina::validarCodigoTurma(std::string(7, 'T')), std::invalid_argument);
}

TEST_CASE("Disciplina::validarNome [limite] aceita de 1 a 26 caracteres")
{
    CHECK_NOTHROW(Disciplina::validarNome("A"));
    CHECK_NOTHROW(Disciplina::validarNome(std::string(26, 'N')));
}

TEST_CASE("Disciplina::validarNome [negativo] rejeita vazio e mais de 26 caracteres")
{
    CHECK_THROWS_AS(Disciplina::validarNome(""), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina::validarNome(std::string(27, 'N')), std::invalid_argument);
}

TEST_CASE("Disciplina::validarProfessor [limite] aceita de 1 a 100 caracteres")
{
    CHECK_NOTHROW(Disciplina::validarProfessor("A"));
    CHECK_NOTHROW(Disciplina::validarProfessor(std::string(100, 'P')));
}

TEST_CASE("Disciplina::validarProfessor [negativo] rejeita vazio e mais de 100 caracteres")
{
    CHECK_THROWS_AS(Disciplina::validarProfessor(""), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina::validarProfessor(std::string(101, 'P')), std::invalid_argument);
}

TEST_CASE("Disciplina::validarSalaBloco [limite] aceita de 1 a 100 caracteres")
{
    CHECK_NOTHROW(Disciplina::validarSalaBloco("A"));
    CHECK_NOTHROW(Disciplina::validarSalaBloco(std::string(100, 'S')));
}

TEST_CASE("Disciplina::validarSalaBloco [negativo] rejeita vazio e mais de 100 caracteres")
{
    CHECK_THROWS_AS(Disciplina::validarSalaBloco(""), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina::validarSalaBloco(std::string(101, 'S')), std::invalid_argument);
}

TEST_CASE("Disciplina::validarHorarioDias [limite] aceita de 1 a 100 caracteres")
{
    CHECK_NOTHROW(Disciplina::validarHorarioDias("A"));
    CHECK_NOTHROW(Disciplina::validarHorarioDias(std::string(100, 'H')));
}
