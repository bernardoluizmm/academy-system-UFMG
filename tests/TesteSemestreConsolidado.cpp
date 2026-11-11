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

TEST_CASE("SemestreConsolidado - semestre trancado devolve NSG e horas zerados")
{
    SemestreConsolidado semestre("2025/02", 80.0f, 60, 30, 15, true);

    CHECK(semestre.isTrancado() == true);
    CHECK(semestre.calcularNSG() == doctest::Approx(0.0));
    CHECK(semestre.getHorasObrigatorias() == 0);
    CHECK(semestre.getHorasOptativas() == 0);
    CHECK(semestre.getHorasFormacaoLivre() == 0);
    CHECK(semestre.getHorasIntegralizadas() == 0);
}

TEST_CASE("SemestreConsolidado - trancado ignora valores que seriam invalidos")
{
    CHECK_NOTHROW(SemestreConsolidado("2025/02", 999.0f, 7, 7, 7, true));
}

TEST_CASE("SemestreConsolidado - setTrancado altera o que os getters devolvem")
{
    SemestreConsolidado semestre("2025/01", 90.0f, 60, 0, 0);
    CHECK(semestre.calcularNSG() == doctest::Approx(90.0));

    semestre.setTrancado(true);
    CHECK(semestre.calcularNSG() == doctest::Approx(0.0));
    CHECK(semestre.getHorasIntegralizadas() == 0);

    semestre.setTrancado(false);
    CHECK(semestre.calcularNSG() == doctest::Approx(90.0));
    CHECK(semestre.getHorasIntegralizadas() == 60);
}

TEST_CASE("SemestreConsolidado - polimorfismo via ponteiro de Semestre")
{
    SemestreConsolidado semestre("2025/01", 70.0f, 45, 0, 0);
    Semestre* base = &semestre;

    CHECK(base->calcularNSG() == doctest::Approx(70.0));
    CHECK(base->getHorasObrigatorias() == 45);
    CHECK(base->getHorasIntegralizadas() == 45);
    CHECK(base->getIdentificador() == "2025/01");
}

TEST_CASE("SemestreConsolidado - serializar")
{
    SemestreConsolidado normal("2025/01", 85.5f, 60, 30, 15);
    CHECK(normal.serializar() == "SEMESTRE_CONSOLIDADO|2025/01|85.5|60|30|15|0");

    SemestreConsolidado trancado("2025/02", 80.0f, 60, 0, 0, true);
    CHECK(trancado.serializar() == "SEMESTRE_CONSOLIDADO|2025/02|0|0|0|0|1");
}