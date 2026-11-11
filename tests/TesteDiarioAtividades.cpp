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

TEST_CASE("DiarioAtividades - remover e buscar por ID") {
    DiarioAtividades diario;
    diario.adicionarAtividade("Primeira", "10/04", 10.0f);
    diario.adicionarAtividade("Segunda", "12/04", 20.0f);
    diario.removerAtividade(1);
    CHECK(diario.buscarAtividade(1) == nullptr);
    CHECK(diario.buscarAtividade(2) != nullptr);
    CHECK(diario.getAtividades().size() == 1);
    CHECK_THROWS_AS(diario.removerAtividade(1), std::invalid_argument);
    diario.adicionarAtividade("Terceira", "13/04", 20.0f);
    CHECK(diario.buscarAtividade(3) != nullptr);
}

TEST_CASE("DiarioAtividades - totais, media, percentual e conceito parcial") {
    DiarioAtividades diario;
    diario.adicionarAtividade("Prova 1", "10/04", 30.0f);
    diario.adicionarAtividade("Trabalho", "20/04", 20.0f);
    diario.adicionarAtividade("Prova 2", "30/04", 50.0f);
    diario.buscarAtividade(1)->setNotaObtida(24.0f);
    diario.buscarAtividade(2)->setNotaObtida(18.0f);
    CHECK(diario.obterValorTotalPlanejado() == doctest::Approx(100.0f));
    CHECK(diario.obterValorTotalConcluido() == doctest::Approx(50.0f));
    CHECK(diario.obterNotaTotalParcial() == doctest::Approx(42.0f));
    CHECK(diario.obterMediaParcial() == doctest::Approx(30.0f));
    CHECK(diario.calcularPercentualAproveitamento() == doctest::Approx(84.0f));
    CHECK(diario.obterConceitoParcial() == 'B');
    diario.buscarAtividade(1)->removerLancamentoNota();
    CHECK(diario.obterValorTotalConcluido() == doctest::Approx(20.0f));
    CHECK(diario.obterNotaTotalParcial() == doctest::Approx(18.0f));
    CHECK(diario.calcularPercentualAproveitamento() == doctest::Approx(90.0f));
    CHECK(diario.obterConceitoParcial() == 'A');
}
