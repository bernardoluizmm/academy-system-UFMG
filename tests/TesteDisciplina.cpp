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

