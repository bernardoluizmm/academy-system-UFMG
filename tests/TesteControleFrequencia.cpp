#include "doctest.h"
#include "ControleFrequencia.hpp"
#include <stdexcept>

TEST_CASE("ControleFrequencia - construtor e getters") {
    ControleFrequencia frequencia(7);
    CHECK(frequencia.getMaxFaltas() == 7);
    CHECK(frequencia.getFaltasAtuais() == 0);
    CHECK_THROWS_AS(ControleFrequencia(-1), std::invalid_argument);
}

TEST_CASE("ControleFrequencia - adicionar e remover") {
    ControleFrequencia frequencia(2);
    frequencia.adicionarFalta();
    CHECK(frequencia.getFaltasAtuais() == 1);
    frequencia.adicionarFalta();
    CHECK(frequencia.getFaltasAtuais() == 2);
    CHECK_THROWS_AS(frequencia.adicionarFalta(), std::invalid_argument);
    CHECK(frequencia.getFaltasAtuais() == 2);
    frequencia.removerFalta();
    frequencia.removerFalta();
    CHECK(frequencia.getFaltasAtuais() == 0);
    CHECK_THROWS_AS(frequencia.removerFalta(), std::invalid_argument);
}