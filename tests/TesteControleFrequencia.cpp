#include "doctest.h"
#include "ControleFrequencia.hpp"
#include <stdexcept>

TEST_CASE("ControleFrequencia - construtor e getters") {
    ControleFrequencia frequencia(7);
    CHECK(frequencia.getMaxFaltas() == 7);
    CHECK(frequencia.getFaltasAtuais() == 0);
    CHECK_THROWS_AS(ControleFrequencia(-1), std::invalid_argument);
}