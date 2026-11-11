#include "doctest.h"
#include "CalculadorMedia.hpp"
#include "CalculadorConceito.hpp"
#include "CalculadorMaxFaltas.hpp"
#include <stdexcept>

TEST_CASE("CalculadorMedia - 60 por cento do valor") {
    CHECK(CalculadorMedia::calcular(100.0f) == doctest::Approx(60.0f));
    CHECK(CalculadorMedia::calcular(30.0f) == doctest::Approx(18.0f));
    CHECK(CalculadorMedia::calcular(0.0f) == doctest::Approx(0.0f));
}

TEST_CASE("CalculadorConceito - limites de cada conceito") {
    CHECK(CalculadorConceito::calcular(100.0f) == 'A');
    CHECK(CalculadorConceito::calcular(90.0f) == 'A');
    CHECK(CalculadorConceito::calcular(89.9f) == 'B');
    CHECK(CalculadorConceito::calcular(80.0f) == 'B');
    CHECK(CalculadorConceito::calcular(79.9f) == 'C');
    CHECK(CalculadorConceito::calcular(70.0f) == 'C');
    CHECK(CalculadorConceito::calcular(69.9f) == 'D');
    CHECK(CalculadorConceito::calcular(60.0f) == 'D');
    CHECK(CalculadorConceito::calcular(59.9f) == 'E');
    CHECK(CalculadorConceito::calcular(40.0f) == 'E');
    CHECK(CalculadorConceito::calcular(39.9f) == 'F');
    CHECK(CalculadorConceito::calcular(0.0f) == 'F');
}

TEST_CASE("CalculadorMaxFaltas - calculos com divisao inteira") {
    CHECK(CalculadorMaxFaltas::calcularDiasMaximosFalta(60, 100) == 7);
    CHECK(CalculadorMaxFaltas::calcularDiasMaximosFalta(60, 50) == 15);
    CHECK(CalculadorMaxFaltas::calcularDiasMaximosFalta(90, 150) == 7);
    CHECK(CalculadorMaxFaltas::calcularDiasMaximosFalta(15, 50) == 3);
    CHECK(CalculadorMaxFaltas::calcularDiasMaximosFalta(60, 120) == 7);
}

TEST_CASE("CalculadorMaxFaltas - entradas invalidas") {
    CHECK_THROWS_AS(CalculadorMaxFaltas::calcularDiasMaximosFalta(0, 50), std::invalid_argument);
    CHECK_THROWS_AS(CalculadorMaxFaltas::calcularDiasMaximosFalta(-15, 50), std::invalid_argument);
    CHECK_THROWS_AS(CalculadorMaxFaltas::calcularDiasMaximosFalta(61, 50), std::invalid_argument);
    CHECK_THROWS_AS(CalculadorMaxFaltas::calcularDiasMaximosFalta(60, 49), std::invalid_argument);
}
