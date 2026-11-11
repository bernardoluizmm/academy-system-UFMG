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
