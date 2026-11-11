#include "doctest.h"
#include "AtividadeAvaliativa.hpp"
#include <stdexcept>

TEST_CASE("AtividadeAvaliativa - construtor simples e getters") {
    AtividadeAvaliativa prova(1, "Prova 1", "10/04", 30.0f);
    CHECK(prova.getId() == 1);
    CHECK(prova.getNome() == "Prova 1");
    CHECK(prova.getData().getDataValidada() == "10/04");
    CHECK(prova.getValorMaximo() == doctest::Approx(30.0f));
    CHECK(prova.getNotaObtida() == doctest::Approx(0.0f));
    CHECK(prova.isConcluida() == false);
    CHECK(prova.obterMedia() == doctest::Approx(18.0f));
    CHECK(prova.obterConceito() == '-');
    CHECK(prova.serializar() == "ATIVIDADE|1|Prova 1|10/04|30|0|0");
}

TEST_CASE("AtividadeAvaliativa - construtor com nota e situacao") {
    AtividadeAvaliativa concluida(2, "Trabalho", "15/05", 20.0f, 16.0f, true);
    CHECK(concluida.getNotaObtida() == doctest::Approx(16.0f));
    CHECK(concluida.isConcluida() == true);
    CHECK(concluida.obterConceito() == 'B');
    CHECK(concluida.serializar() == "ATIVIDADE|2|Trabalho|15/05|20|16|1");
    AtividadeAvaliativa pendente(3, "TP", "16/05", 20.0f, 12.0f, false);
    CHECK(pendente.isConcluida() == false);
    CHECK(pendente.getNotaObtida() == doctest::Approx(0.0f));
    CHECK_THROWS_AS(AtividadeAvaliativa(4, "TP", "16/05", 20.0f, 21.0f, true), std::invalid_argument);
}

TEST_CASE("AtividadeAvaliativa - validadores e construtor invalido") {
    AtividadeAvaliativa::validarNome("A");
    AtividadeAvaliativa::validarNome(std::string(24, 'A'));
    AtividadeAvaliativa::validarValorMaximo(0.01f);
    CHECK_THROWS_AS(AtividadeAvaliativa::validarNome(""), std::invalid_argument);
    CHECK_THROWS_AS(AtividadeAvaliativa::validarNome(std::string(25, 'A')), std::invalid_argument);
    CHECK_THROWS_AS(AtividadeAvaliativa::validarValorMaximo(0.0f), std::invalid_argument);
    CHECK_THROWS_AS(AtividadeAvaliativa::validarValorMaximo(-1.0f), std::invalid_argument);
    CHECK_THROWS_AS(AtividadeAvaliativa(1, "", "10/04", 30.0f), std::invalid_argument);
    CHECK_THROWS_AS(AtividadeAvaliativa(1, "OK", "30/02", 30.0f), std::invalid_argument);
    CHECK_THROWS_AS(AtividadeAvaliativa(1, "OK", "10/04", -1.0f), std::invalid_argument);
}

TEST_CASE("AtividadeAvaliativa - setters e restricoes") {
    AtividadeAvaliativa atividade(5, "TP", "10/04", 20.0f);
    atividade.setNome("TP Final");
    CHECK(atividade.getNome() == "TP Final");
    CHECK_THROWS_AS(atividade.setNome(""), std::invalid_argument);
    CHECK(atividade.getNome() == "TP Final");
    atividade.setData("12/05");
    CHECK(atividade.getData().getDataValidada() == "12/05");
    CHECK_THROWS_AS(atividade.setData("31/02"), std::invalid_argument);
    CHECK(atividade.getData().getDataValidada() == "12/05");
    atividade.setValorMaximo(25.0f);
    CHECK(atividade.getValorMaximo() == doctest::Approx(25.0f));
    CHECK_THROWS_AS(atividade.setValorMaximo(0.0f), std::invalid_argument);
    atividade.setNotaObtida(20.0f);
    CHECK(atividade.isConcluida() == true);
    CHECK(atividade.getNotaObtida() == doctest::Approx(20.0f));
    CHECK_THROWS_AS(atividade.setNotaObtida(-1.0f), std::invalid_argument);
    CHECK_THROWS_AS(atividade.setNotaObtida(26.0f), std::invalid_argument);
    CHECK_THROWS_AS(atividade.setValorMaximo(19.0f), std::invalid_argument);
    CHECK(atividade.getValorMaximo() == doctest::Approx(25.0f));
    atividade.removerLancamentoNota();
    CHECK(atividade.getNotaObtida() == doctest::Approx(0.0f));
    CHECK(atividade.isConcluida() == false);
    CHECK(atividade.obterConceito() == '-');
}
