#include "doctest.h"
#include "Disciplina.hpp"
#include <stdexcept>
#include <string>

namespace
{
    Disciplina criarDisciplina(int id = 1, int cargaHoraria = 60, int duracaoAula = 50,
                               const std::string& tipo = "Obrigatoria")
    {
        return Disciplina(id, "DCC204", "TA", "PDS II", "Douglas Macharet", "ICEx 2014",
                          cargaHoraria, duracaoAula, tipo, "Seg 10h");
    }

    void lancarNota(Disciplina& disciplina, float valorMaximo, float nota)
    {
        int idAtividade = static_cast<int>(disciplina.avaliacoes().getAtividades().size()) + 1;
        disciplina.avaliacoes().adicionarAtividade(idAtividade, "Prova", "01/05", valorMaximo, nota, true);
    }

    bool contem(const std::string& texto, const std::string& trecho)
    {
        return texto.find(trecho) != std::string::npos;
    }
}

TEST_CASE("Disciplina - construtor e getters")
{
    Disciplina disciplina(7, "DCC204", "TA", "PDS II", "Douglas Macharet", "ICEx 2014",
                          60, 50, "Obrigatoria", "Seg 10h");

    CHECK(disciplina.getId() == 7);
    CHECK(disciplina.getCodigo() == "DCC204");
    CHECK(disciplina.getCodigoTurma() == "TA");
    CHECK(disciplina.getNome() == "PDS II");
    CHECK(disciplina.getProfessor() == "Douglas Macharet");
    CHECK(disciplina.getSalaBloco() == "ICEx 2014");
    CHECK(disciplina.getCargaHoraria() == 60);
    CHECK(disciplina.getDuracaoAulaMinutos() == 50);
    CHECK(disciplina.getTipo() == "Obrigatoria");
    CHECK(disciplina.getHorarioDias() == "Seg 10h");
}

TEST_CASE("Disciplina - estado inicial de frequencia e avaliacoes")
{
    Disciplina disciplina = criarDisciplina();

    CHECK(disciplina.frequencia().getFaltasAtuais() == 0);
    CHECK(disciplina.avaliacoes().getAtividades().empty());
    CHECK(disciplina.avaliacoes().obterValorTotalPlanejado() == doctest::Approx(0.0));
}

TEST_CASE("Disciplina - limite de faltas calculado na construcao")
{
    CHECK(criarDisciplina(1, 60, 50).frequencia().getMaxFaltas() == 15);
    CHECK(criarDisciplina(1, 60, 100).frequencia().getMaxFaltas() == 7);
    CHECK(criarDisciplina(1, 90, 50).frequencia().getMaxFaltas() == 22);
    CHECK(criarDisciplina(1, 15, 50).frequencia().getMaxFaltas() == 3);
}

TEST_CASE("Disciplina - aceita os tres tipos validos")
{
    CHECK_NOTHROW(criarDisciplina(1, 60, 50, "Obrigatoria"));
    CHECK_NOTHROW(criarDisciplina(1, 60, 50, "Optativa"));
    CHECK_NOTHROW(criarDisciplina(1, 60, 50, "Formacao Livre"));
}

