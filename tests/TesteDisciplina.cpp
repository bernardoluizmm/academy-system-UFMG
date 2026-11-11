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

TEST_CASE("Disciplina::validarHorarioDias [negativo] rejeita vazio e mais de 100 caracteres")
{
    CHECK_THROWS_AS(Disciplina::validarHorarioDias(""), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina::validarHorarioDias(std::string(101, 'H')), std::invalid_argument);
}

TEST_CASE("Disciplina::validarCargaHoraria [positivo] aceita multiplos positivos de 15")
{
    CHECK_NOTHROW(Disciplina::validarCargaHoraria(15));
    CHECK_NOTHROW(Disciplina::validarCargaHoraria(60));
}

TEST_CASE("Disciplina::validarCargaHoraria [negativo] rejeita zero, negativo e nao multiplo de 15")
{
    CHECK_THROWS_AS(Disciplina::validarCargaHoraria(0), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina::validarCargaHoraria(-15), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina::validarCargaHoraria(16), std::invalid_argument);
}

TEST_CASE("Disciplina::validarDuracaoAulaMinutos [limite] aceita 50 e rejeita 49")
{
    CHECK_NOTHROW(Disciplina::validarDuracaoAulaMinutos(50));
    CHECK_THROWS_AS(Disciplina::validarDuracaoAulaMinutos(49), std::invalid_argument);
}

TEST_CASE("Disciplina::validarTipo [positivo] aceita os tres tipos validos")
{
    CHECK_NOTHROW(Disciplina::validarTipo("Obrigatoria"));
    CHECK_NOTHROW(Disciplina::validarTipo("Optativa"));
    CHECK_NOTHROW(Disciplina::validarTipo("Formacao Livre"));
}

TEST_CASE("Disciplina::validarTipo [negativo] rejeita vazio e tipo desconhecido (case-sensitive)")
{
    CHECK_THROWS_AS(Disciplina::validarTipo(""), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina::validarTipo("optativa"), std::invalid_argument);
    CHECK_THROWS_AS(Disciplina::validarTipo("Qualquer"), std::invalid_argument);
}

TEST_CASE("Disciplina::setCodigo [positivo] altera o codigo")
{
    Disciplina d = criarDisciplinaValida();
    d.setCodigo("NOVO");
    CHECK(d.getCodigo() == "NOVO");
}

TEST_CASE("Disciplina::setCodigo [negativo] valor invalido lanca excecao e preserva o anterior")
{
    Disciplina d = criarDisciplinaValida();
    CHECK_THROWS_AS(d.setCodigo(""), std::invalid_argument);
    CHECK(d.getCodigo() == "COD001");
}

TEST_CASE("Disciplina::setCodigoTurma [positivo] altera a turma")
{
    Disciplina d = criarDisciplinaValida();
    d.setCodigoTurma("T2");
    CHECK(d.getCodigoTurma() == "T2");
}

TEST_CASE("Disciplina::setCodigoTurma [negativo] valor invalido lanca excecao e preserva o anterior")
{
    Disciplina d = criarDisciplinaValida();
    CHECK_THROWS_AS(d.setCodigoTurma(std::string(7, 'T')), std::invalid_argument);
    CHECK(d.getCodigoTurma() == "T1");
}

TEST_CASE("Disciplina::setNome [positivo] altera o nome")
{
    Disciplina d = criarDisciplinaValida();
    d.setNome("Algoritmos");
    CHECK(d.getNome() == "Algoritmos");
}

TEST_CASE("Disciplina::setNome [negativo] valor invalido lanca excecao e preserva o anterior")
{
    Disciplina d = criarDisciplinaValida();
    CHECK_THROWS_AS(d.setNome(std::string(27, 'N')), std::invalid_argument);
    CHECK(d.getNome() == "Programacao");
}

TEST_CASE("Disciplina::setProfessor [positivo] altera o professor")
{
    Disciplina d = criarDisciplinaValida();
    d.setProfessor("Prof. Bruno");
    CHECK(d.getProfessor() == "Prof. Bruno");
}


TEST_CASE("Disciplina::setProfessor [negativo] valor invalido lanca excecao e preserva o anterior")
{
    Disciplina d = criarDisciplinaValida();
    CHECK_THROWS_AS(d.setProfessor(""), std::invalid_argument);
    CHECK(d.getProfessor() == "Prof. Ana");
}

TEST_CASE("Disciplina::setSalaBloco [positivo] altera a sala")
{
    Disciplina d = criarDisciplinaValida();
    d.setSalaBloco("Bloco B");
    CHECK(d.getSalaBloco() == "Bloco B");
}

TEST_CASE("Disciplina::setSalaBloco [negativo] valor invalido lanca excecao e preserva o anterior")
{
    Disciplina d = criarDisciplinaValida();
    CHECK_THROWS_AS(d.setSalaBloco(""), std::invalid_argument);
    CHECK(d.getSalaBloco() == "Sala 101");
}

TEST_CASE("Disciplina::setHorarioDias [positivo] altera o horario")
{
    Disciplina d = criarDisciplinaValida();
    d.setHorarioDias("Ter 08h");
    CHECK(d.getHorarioDias() == "Ter 08h");
}

TEST_CASE("Disciplina::setHorarioDias [negativo] valor invalido lanca excecao e preserva o anterior")
{
    Disciplina d = criarDisciplinaValida();
    CHECK_THROWS_AS(d.setHorarioDias(""), std::invalid_argument);
    CHECK(d.getHorarioDias() == "Seg 10h");
}

TEST_CASE("Disciplina::setTipo [positivo] altera o tipo")
{
    Disciplina d = criarDisciplinaValida();
    d.setTipo("Optativa");
    CHECK(d.getTipo() == "Optativa");
}

TEST_CASE("Disciplina::setTipo [negativo] valor invalido lanca excecao e preserva o anterior")
{
    Disciplina d = criarDisciplinaValida();
    CHECK_THROWS_AS(d.setTipo("Qualquer"), std::invalid_argument);
    CHECK(d.getTipo() == "Obrigatoria");
}

// ================================ Setters numericos (atualizarLimiteFaltas)
TEST_CASE("Disciplina::setCargaHoraria [positivo] altera a carga horaria")
{
    Disciplina d = criarDisciplinaValida();
    d.setCargaHoraria(90);
    CHECK(d.getCargaHoraria() == 90);
}

TEST_CASE("Disciplina::setCargaHoraria [positivo] recalcula o limite de faltas")
{
    Disciplina d = criarDisciplinaValida();
    d.setCargaHoraria(90);
    CHECK(d.frequencia().getMaxFaltas() == CalculadorMaxFaltas::calcularDiasMaximosFalta(90, 50));
}

TEST_CASE("Disciplina::setCargaHoraria [negativo] valor invalido lanca excecao e preserva carga e limite")
{
    Disciplina d = criarDisciplinaValida();
    const int limiteAntes = d.frequencia().getMaxFaltas();

    CHECK_THROWS_AS(d.setCargaHoraria(20), std::invalid_argument);
    CHECK(d.getCargaHoraria() == 60);
    CHECK(d.frequencia().getMaxFaltas() == limiteAntes);
}

TEST_CASE("Disciplina::setDuracaoAulaMinutos [positivo] altera a duracao")
{
    Disciplina d = criarDisciplinaValida();
    d.setDuracaoAulaMinutos(100);
    CHECK(d.getDuracaoAulaMinutos() == 100);
}

TEST_CASE("Disciplina::setDuracaoAulaMinutos [positivo] recalcula o limite de faltas")
{
    Disciplina d = criarDisciplinaValida();
    d.setDuracaoAulaMinutos(100);
    CHECK(d.frequencia().getMaxFaltas() == CalculadorMaxFaltas::calcularDiasMaximosFalta(60, 100));
}

TEST_CASE("Disciplina::setDuracaoAulaMinutos [negativo] valor invalido lanca excecao e preserva duracao e limite")
{
    Disciplina d = criarDisciplinaValida();
    const int limiteAntes = d.frequencia().getMaxFaltas();

    CHECK_THROWS_AS(d.setDuracaoAulaMinutos(49), std::invalid_argument);
    CHECK(d.getDuracaoAulaMinutos() == 50);
    CHECK(d.frequencia().getMaxFaltas() == limiteAntes);
}

TEST_CASE("Disciplina::frequencia [positivo] versao nao const permite alterar o controle")
{
    Disciplina d = criarDisciplinaValida();
    d.frequencia().setMaxFaltas(10);
    CHECK(d.frequencia().getMaxFaltas() == 10);
}

TEST_CASE("Disciplina::frequencia [positivo] versao const permite leitura")
{
    Disciplina d = criarDisciplinaValida();
    d.frequencia().setMaxFaltas(10);
    const Disciplina& cd = d;
    CHECK(cd.frequencia().getMaxFaltas() == 10);
}

TEST_CASE("Disciplina::avaliacoes [positivo] versao nao const permite adicionar atividade")
{
    Disciplina d = criarDisciplinaValida();
    d.avaliacoes().adicionarAtividade("Prova 1", "15/03", 10.0f);
    CHECK(d.avaliacoes().getAtividades().size() == 1);
}

TEST_CASE("Disciplina::avaliacoes [positivo] versao const permite leitura")
{
    Disciplina d = criarDisciplinaValida();
    d.avaliacoes().adicionarAtividade("Prova 1", "15/03", 10.0f);
    const Disciplina& cd = d;
    REQUIRE(cd.avaliacoes().getAtividades().size() == 1);
    CHECK(cd.avaliacoes().getAtividades()[0].getNome() == "Prova 1");
}

