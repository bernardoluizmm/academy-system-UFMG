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

TEST_CASE("Disciplina - construtor rejeita dados invalidos")
{
    SUBCASE("id negativo")
    {
        CHECK_THROWS_AS(criarDisciplina(-1), std::invalid_argument);
    }

    SUBCASE("carga horaria")
    {
        CHECK_THROWS_AS(criarDisciplina(1, 0), std::invalid_argument);
        CHECK_THROWS_AS(criarDisciplina(1, -60), std::invalid_argument);
        CHECK_THROWS_AS(criarDisciplina(1, 100), std::invalid_argument);
    }

    SUBCASE("duracao da aula")
    {
        CHECK_THROWS_AS(criarDisciplina(1, 60, 49), std::invalid_argument);
        CHECK_THROWS_AS(criarDisciplina(1, 60, 0), std::invalid_argument);
    }

    SUBCASE("tipo")
    {
        CHECK_THROWS_AS(criarDisciplina(1, 60, 50, "Extensao"), std::invalid_argument);
        CHECK_THROWS_AS(criarDisciplina(1, 60, 50, ""), std::invalid_argument);
        CHECK_THROWS_AS(criarDisciplina(1, 60, 50, "obrigatoria"), std::invalid_argument);
    }

    SUBCASE("textos vazios")
    {
        CHECK_THROWS_AS(Disciplina(1, "", "TA", "PDS II", "Prof", "Sala", 60, 50, "Optativa", "Seg"), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina(1, "DCC204", "", "PDS II", "Prof", "Sala", 60, 50, "Optativa", "Seg"), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina(1, "DCC204", "TA", "", "Prof", "Sala", 60, 50, "Optativa", "Seg"), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina(1, "DCC204", "TA", "PDS II", "", "Sala", 60, 50, "Optativa", "Seg"), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina(1, "DCC204", "TA", "PDS II", "Prof", "", 60, 50, "Optativa", "Seg"), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina(1, "DCC204", "TA", "PDS II", "Prof", "Sala", 60, 50, "Optativa", ""), std::invalid_argument);
    }
}

TEST_CASE("Disciplina - validadores estaticos")
{
    SUBCASE("codigo de 1 a 8 caracteres")
    {
        CHECK_NOTHROW(Disciplina::validarCodigo("A"));
        CHECK_NOTHROW(Disciplina::validarCodigo("12345678"));
        CHECK_THROWS_AS(Disciplina::validarCodigo(""), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina::validarCodigo("123456789"), std::invalid_argument);
    }

    SUBCASE("turma de 1 a 6 caracteres")
    {
        CHECK_NOTHROW(Disciplina::validarCodigoTurma("A"));
        CHECK_NOTHROW(Disciplina::validarCodigoTurma("123456"));
        CHECK_THROWS_AS(Disciplina::validarCodigoTurma(""), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina::validarCodigoTurma("1234567"), std::invalid_argument);
    }

    SUBCASE("nome de 1 a 26 caracteres")
    {
        CHECK_NOTHROW(Disciplina::validarNome(std::string(26, 'a')));
        CHECK_THROWS_AS(Disciplina::validarNome(""), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina::validarNome(std::string(27, 'a')), std::invalid_argument);
    }

    SUBCASE("professor, sala e horario de 1 a 100 caracteres")
    {
        CHECK_NOTHROW(Disciplina::validarProfessor(std::string(100, 'a')));
        CHECK_NOTHROW(Disciplina::validarSalaBloco(std::string(100, 'a')));
        CHECK_NOTHROW(Disciplina::validarHorarioDias(std::string(100, 'a')));
        CHECK_THROWS_AS(Disciplina::validarProfessor(std::string(101, 'a')), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina::validarSalaBloco(std::string(101, 'a')), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina::validarHorarioDias(std::string(101, 'a')), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina::validarProfessor(""), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina::validarSalaBloco(""), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina::validarHorarioDias(""), std::invalid_argument);
    }

    SUBCASE("carga horaria positiva e multipla de 15")
    {
        CHECK_NOTHROW(Disciplina::validarCargaHoraria(15));
        CHECK_NOTHROW(Disciplina::validarCargaHoraria(90));
        CHECK_THROWS_AS(Disciplina::validarCargaHoraria(0), std::invalid_argument);
        CHECK_THROWS_AS(Disciplina::validarCargaHoraria(20), std::invalid_argument);
    }

    SUBCASE("duracao da aula de no minimo 50 minutos")
    {
        CHECK_NOTHROW(Disciplina::validarDuracaoAulaMinutos(50));
        CHECK_NOTHROW(Disciplina::validarDuracaoAulaMinutos(100));
        CHECK_THROWS_AS(Disciplina::validarDuracaoAulaMinutos(49), std::invalid_argument);
    }

    SUBCASE("tipo")
    {
        CHECK_NOTHROW(Disciplina::validarTipo("Optativa"));
        CHECK_THROWS_AS(Disciplina::validarTipo("Outro"), std::invalid_argument);
    }
}

