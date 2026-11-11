#include "doctest.h"
#include "SemestreConsolidado.hpp"
#include <stdexcept>
#include <string>

TEST_CASE("SemestreConsolidado - guarda NSG e horas validos")
{
    SemestreConsolidado semestre("2025/01", 85.5f, 60, 30, 15);

    CHECK(semestre.getIdentificador() == "2025/01");
    CHECK(semestre.isTrancado() == false);
    CHECK(semestre.calcularNSG() == doctest::Approx(85.5));
    CHECK(semestre.getHorasObrigatorias() == 60);
    CHECK(semestre.getHorasOptativas() == 30);
    CHECK(semestre.getHorasFormacaoLivre() == 15);
    CHECK(semestre.getHorasIntegralizadas() == 105);
}

TEST_CASE("SemestreConsolidado - valores limite sao aceitos")
{
    CHECK_NOTHROW(SemestreConsolidado("2025/01", 0.0f, 0, 0, 0));
    CHECK_NOTHROW(SemestreConsolidado("2025/01", 100.0f, 0, 0, 0));
}

TEST_CASE("SemestreConsolidado - rejeita NSG fora do intervalo de 0 a 100")
{
    CHECK_THROWS_AS(SemestreConsolidado("2025/01", -1.0f, 0, 0, 0), std::invalid_argument);
    CHECK_THROWS_AS(SemestreConsolidado("2025/01", 100.5f, 0, 0, 0), std::invalid_argument);
}

TEST_CASE("SemestreConsolidado - rejeita horas negativas ou nao multiplas de 15")
{
    CHECK_THROWS_AS(SemestreConsolidado("2025/01", 80.0f, 10, 0, 0), std::invalid_argument); 
    CHECK_THROWS_AS(SemestreConsolidado("2025/01", 80.0f, 0, 20, 0), std::invalid_argument);  
    CHECK_THROWS_AS(SemestreConsolidado("2025/01", 80.0f, 0, 0, 7), std::invalid_argument);  
    CHECK_THROWS_AS(SemestreConsolidado("2025/01", 80.0f, -15, 0, 0), std::invalid_argument);
}

TEST_CASE("SemestreConsolidado - rejeita identificador invalido")
{
    CHECK_THROWS_AS(SemestreConsolidado("2025/3", 80.0f, 0, 0, 0), std::invalid_argument);
    CHECK_THROWS_AS(SemestreConsolidado("", 80.0f, 0, 0, 0), std::invalid_argument);
}
