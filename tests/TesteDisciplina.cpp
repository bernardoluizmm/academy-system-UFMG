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
