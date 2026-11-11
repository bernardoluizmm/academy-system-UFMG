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

TEST_CASE("ControleFrequencia - definir total diretamente") {
    ControleFrequencia frequencia(10);
    frequencia.setFaltasAtuais(8);
    CHECK(frequencia.getFaltasAtuais() == 8);
    frequencia.setFaltasAtuais(0);
    CHECK(frequencia.getFaltasAtuais() == 0);
    frequencia.setFaltasAtuais(10);
    CHECK(frequencia.getFaltasAtuais() == 10);
    CHECK_THROWS_AS(frequencia.setFaltasAtuais(-1), std::invalid_argument);
    CHECK_THROWS_AS(frequencia.setFaltasAtuais(11), std::invalid_argument);
    CHECK(frequencia.getFaltasAtuais() == 10);
}

TEST_CASE("ControleFrequencia - novo limite reduz faltas atuais") {
    ControleFrequencia frequencia(10);
    frequencia.setFaltasAtuais(8);
    frequencia.setMaxFaltas(6);
    CHECK(frequencia.getMaxFaltas() == 6);
    CHECK(frequencia.getFaltasAtuais() == 6);
    frequencia.setMaxFaltas(12);
    CHECK(frequencia.getMaxFaltas() == 12);
    CHECK(frequencia.getFaltasAtuais() == 6);
    CHECK_THROWS_AS(frequencia.setMaxFaltas(-2), std::invalid_argument);
    CHECK(frequencia.getMaxFaltas() == 12);
    frequencia.setMaxFaltas(0);
    CHECK(frequencia.getMaxFaltas() == 0);
    CHECK(frequencia.getFaltasAtuais() == 0);
    CHECK_THROWS_AS(frequencia.adicionarFalta(), std::invalid_argument);
}