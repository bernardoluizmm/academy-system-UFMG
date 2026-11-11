#include "doctest.h"
#include "DiarioAtividades.hpp"
#include <stdexcept>

TEST_CASE("DiarioAtividades - estado inicial e calculos vazios") {
    DiarioAtividades diario;
    CHECK(diario.getAtividades().empty());
    CHECK(diario.buscarAtividade(1) == nullptr);
    CHECK(diario.obterValorTotalPlanejado() == doctest::Approx(0.0f));
    CHECK(diario.obterValorTotalConcluido() == doctest::Approx(0.0f));
    CHECK(diario.obterNotaTotalParcial() == doctest::Approx(0.0f));
    CHECK(diario.obterMediaParcial() == doctest::Approx(0.0f));
    CHECK(diario.calcularPercentualAproveitamento() == doctest::Approx(0.0f));
    CHECK(diario.obterConceitoParcial() == '-');
    CHECK_THROWS_AS(diario.removerAtividade(1), std::invalid_argument);
}

TEST_CASE("DiarioAtividades - IDs automaticos e ordem cronologica") {
    DiarioAtividades diario;
    diario.adicionarAtividade("Prova", "20/11", 30.0f);
    diario.adicionarAtividade("Trabalho", "10/11", 20.0f);
    diario.adicionarAtividade("Final", "05/12", 50.0f);
    CHECK(diario.getAtividades().size() == 3);
    CHECK(diario.getAtividades()[0].getNome() == "Trabalho");
    CHECK(diario.getAtividades()[1].getNome() == "Prova");
    CHECK(diario.getAtividades()[2].getNome() == "Final");
    CHECK(diario.buscarAtividade(1)->getNome() == "Prova");
    CHECK(diario.buscarAtividade(2)->getNome() == "Trabalho");
    CHECK(diario.buscarAtividade(3)->getNome() == "Final");
    diario.ordenarAtividades();
    CHECK(diario.getAtividades()[0].getNome() == "Trabalho");
    CHECK(diario.obterValorTotalPlanejado() == doctest::Approx(100.0f));
}

TEST_CASE("DiarioAtividades - carregar atividades e atualizar contador") {
    DiarioAtividades diario;
    diario.adicionarAtividade(12, "Carregada", "10/05", 20.0f, 15.0f, true);
    CHECK(diario.buscarAtividade(12) != nullptr);
    CHECK(diario.buscarAtividade(12)->isConcluida() == true);
    diario.adicionarAtividade("Nova", "12/05", 20.0f);
    CHECK(diario.buscarAtividade(13) != nullptr);
    CHECK(diario.buscarAtividade(13)->getNome() == "Nova");
    CHECK_THROWS_AS(diario.adicionarAtividade("", "10/05", 20.0f), std::invalid_argument);
    CHECK(diario.getAtividades().size() == 2);
}

