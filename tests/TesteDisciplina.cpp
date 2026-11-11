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