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

