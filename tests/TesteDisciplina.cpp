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

TEST_CASE("Disciplina - setters validam e atualizam os campos")
{
    Disciplina disciplina = criarDisciplina();

    disciplina.setCodigo("MAT001");
    disciplina.setCodigoTurma("TB");
    disciplina.setNome("Calculo I");
    disciplina.setProfessor("Prof. Y");
    disciplina.setSalaBloco("ICEx 1000");
    disciplina.setTipo("Optativa");
    disciplina.setHorarioDias("Ter 8h");

    CHECK(disciplina.getCodigo() == "MAT001");
    CHECK(disciplina.getCodigoTurma() == "TB");
    CHECK(disciplina.getNome() == "Calculo I");
    CHECK(disciplina.getProfessor() == "Prof. Y");
    CHECK(disciplina.getSalaBloco() == "ICEx 1000");
    CHECK(disciplina.getTipo() == "Optativa");
    CHECK(disciplina.getHorarioDias() == "Ter 8h");
}

TEST_CASE("Disciplina - setter invalido lanca excecao e preserva o valor anterior")
{
    Disciplina disciplina = criarDisciplina();

    CHECK_THROWS_AS(disciplina.setCodigo(""), std::invalid_argument);
    CHECK_THROWS_AS(disciplina.setCodigoTurma("1234567"), std::invalid_argument);
    CHECK_THROWS_AS(disciplina.setNome(""), std::invalid_argument);
    CHECK_THROWS_AS(disciplina.setProfessor(""), std::invalid_argument);
    CHECK_THROWS_AS(disciplina.setSalaBloco(""), std::invalid_argument);
    CHECK_THROWS_AS(disciplina.setTipo("Outro"), std::invalid_argument);
    CHECK_THROWS_AS(disciplina.setHorarioDias(""), std::invalid_argument);
    CHECK_THROWS_AS(disciplina.setCargaHoraria(100), std::invalid_argument);
    CHECK_THROWS_AS(disciplina.setDuracaoAulaMinutos(10), std::invalid_argument);

    CHECK(disciplina.getCodigo() == "DCC204");
    CHECK(disciplina.getCodigoTurma() == "TA");
    CHECK(disciplina.getNome() == "PDS II");
    CHECK(disciplina.getTipo() == "Obrigatoria");
    CHECK(disciplina.getCargaHoraria() == 60);
    CHECK(disciplina.getDuracaoAulaMinutos() == 50);
}

TEST_CASE("Disciplina - alterar carga horaria ou duracao recalcula o limite de faltas")
{
    Disciplina disciplina = criarDisciplina(1, 60, 50);
    REQUIRE(disciplina.frequencia().getMaxFaltas() == 15);

    disciplina.setCargaHoraria(90);
    CHECK(disciplina.getCargaHoraria() == 90);
    CHECK(disciplina.frequencia().getMaxFaltas() == 22);

    disciplina.setDuracaoAulaMinutos(100);
    CHECK(disciplina.getDuracaoAulaMinutos() == 100);
    CHECK(disciplina.frequencia().getMaxFaltas() == 11);
}

TEST_CASE("Disciplina - reduzir o limite nao deixa as faltas acima do maximo")
{
    Disciplina disciplina = criarDisciplina(1, 60, 50);
    disciplina.frequencia().setFaltasAtuais(14);

    disciplina.setDuracaoAulaMinutos(100);

    CHECK(disciplina.frequencia().getMaxFaltas() == 7);
    CHECK(disciplina.frequencia().getFaltasAtuais() == 7);
}

TEST_CASE("Disciplina - controle de frequencia")
{
    Disciplina disciplina = criarDisciplina(1, 15, 50);
    REQUIRE(disciplina.frequencia().getMaxFaltas() == 3);

    disciplina.frequencia().adicionarFalta();
    disciplina.frequencia().adicionarFalta();
    CHECK(disciplina.frequencia().getFaltasAtuais() == 2);

    disciplina.frequencia().removerFalta();
    CHECK(disciplina.frequencia().getFaltasAtuais() == 1);

    disciplina.frequencia().adicionarFalta();
    disciplina.frequencia().adicionarFalta();
    CHECK_THROWS_AS(disciplina.frequencia().adicionarFalta(), std::invalid_argument);
    CHECK(disciplina.frequencia().getFaltasAtuais() == 3);
}

TEST_CASE("Disciplina - acesso const a frequencia e avaliacoes")
{
    const Disciplina disciplina = criarDisciplina();

    CHECK(disciplina.frequencia().getMaxFaltas() == 15);
    CHECK(disciplina.avaliacoes().getAtividades().empty());
}

TEST_CASE("Disciplina - atividades avaliativas e conceito parcial")
{
    Disciplina disciplina = criarDisciplina();

    SUBCASE("atividades pendentes nao entram na nota")
    {
        disciplina.avaliacoes().adicionarAtividade("TP1", "10/04", 30.0f);
        disciplina.avaliacoes().adicionarAtividade("TP2", "10/05", 70.0f);

        CHECK(disciplina.avaliacoes().getAtividades().size() == 2);
        CHECK(disciplina.avaliacoes().obterValorTotalPlanejado() == doctest::Approx(100.0));
        CHECK(disciplina.avaliacoes().obterValorTotalConcluido() == doctest::Approx(0.0));
        CHECK(disciplina.avaliacoes().obterConceitoParcial() == '-');
    }

    SUBCASE("conceito A com 95 de 100")
    {
        lancarNota(disciplina, 100.0f, 95.0f);
        CHECK(disciplina.avaliacoes().obterNotaTotalParcial() == doctest::Approx(95.0));
        CHECK(disciplina.avaliacoes().obterConceitoParcial() == 'A');
    }

    SUBCASE("conceito B com 85 de 100")
    {
        lancarNota(disciplina, 100.0f, 85.0f);
        CHECK(disciplina.avaliacoes().obterConceitoParcial() == 'B');
    }

    SUBCASE("conceito C com 72 de 100")
    {
        lancarNota(disciplina, 100.0f, 72.0f);
        CHECK(disciplina.avaliacoes().obterConceitoParcial() == 'C');
    }

    SUBCASE("conceito D com 60 de 100")
    {
        lancarNota(disciplina, 100.0f, 60.0f);
        CHECK(disciplina.avaliacoes().obterConceitoParcial() == 'D');
    }

    SUBCASE("conceito E com 50 de 100")
    {
        lancarNota(disciplina, 100.0f, 50.0f);
        CHECK(disciplina.avaliacoes().obterConceitoParcial() == 'E');
    }

    SUBCASE("conceito F com 35 de 100")
    {
        lancarNota(disciplina, 100.0f, 35.0f);
        CHECK(disciplina.avaliacoes().obterConceitoParcial() == 'F');
    }

    SUBCASE("percentual de aproveitamento usa so o valor concluido")
    {
        lancarNota(disciplina, 40.0f, 30.0f);
        disciplina.avaliacoes().adicionarAtividade("Futura", "30/06", 60.0f);

        CHECK(disciplina.avaliacoes().calcularPercentualAproveitamento() == doctest::Approx(75.0));
        CHECK(disciplina.avaliacoes().obterConceitoParcial() == 'C');
    }
}

TEST_CASE("Disciplina - remover atividade por id")
{
    Disciplina disciplina = criarDisciplina();
    disciplina.avaliacoes().adicionarAtividade("TP1", "10/04", 30.0f);
    disciplina.avaliacoes().adicionarAtividade("TP2", "10/05", 70.0f);

    disciplina.avaliacoes().removerAtividade(0);

    REQUIRE(disciplina.avaliacoes().getAtividades().size() == 1);
    CHECK(disciplina.avaliacoes().getAtividades()[0].getNome() == "TP2");
    CHECK_THROWS_AS(disciplina.avaliacoes().removerAtividade(99), std::invalid_argument);
}

