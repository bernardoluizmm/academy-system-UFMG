#include "doctest.h"
#include "SemestreConsolidado.hpp"
#include <stdexcept>
#include <string>
#include <vector>


TEST_CASE("Semestre - validarFormatoIdentificador aceita identificadores validos")
{
    CHECK(Semestre::validarFormatoIdentificador("2026/01") == true);
    CHECK(Semestre::validarFormatoIdentificador("2026/02") == true);
    CHECK(Semestre::validarFormatoIdentificador("2016/01") == true);  
    CHECK(Semestre::validarFormatoIdentificador("2100/02") == true); 
}

TEST_CASE("Semestre - validarFormatoIdentificador rejeita identificadores invalidos")
{
    CHECK(Semestre::validarFormatoIdentificador("") == false);
    CHECK(Semestre::validarFormatoIdentificador("2026/1") == false);  
    CHECK(Semestre::validarFormatoIdentificador("2026/03") == false);  
    CHECK(Semestre::validarFormatoIdentificador("2026/00") == false);
    CHECK(Semestre::validarFormatoIdentificador("2026-01") == false); 
    CHECK(Semestre::validarFormatoIdentificador("26/01") == false);
    CHECK(Semestre::validarFormatoIdentificador("abcd/01") == false);  
    CHECK(Semestre::validarFormatoIdentificador("2015/02") == false);  
    CHECK(Semestre::validarFormatoIdentificador("2101/01") == false);  
}

TEST_CASE("Semestre - extrairAno e extrairPeriodo")
{
    CHECK(Semestre::extrairAno("2026/01") == 2026);
    CHECK(Semestre::extrairAno("2100/02") == 2100);
    CHECK(Semestre::extrairPeriodo("2026/01") == 1);
    CHECK(Semestre::extrairPeriodo("2026/02") == 2);
}

TEST_CASE("Semestre - proximoIdentificadorSemestre")
{
    CHECK(Semestre::proximoIdentificadorSemestre("2026/01") == "2026/02");
    CHECK(Semestre::proximoIdentificadorSemestre("2026/02") == "2027/01");  
    CHECK(Semestre::proximoIdentificadorSemestre("2099/02") == "2100/01");
}

TEST_CASE("Semestre - proximoIdentificadorSemestre pode gerar identificador invalido")
{
   
    CHECK(Semestre::proximoIdentificadorSemestre("2100/02") == "2101/01");
    CHECK(Semestre::validarFormatoIdentificador("2101/01") == false);
}

TEST_CASE("Semestre - validarNSG")
{
    CHECK_NOTHROW(Semestre::validarNSG(0.0f));
    CHECK_NOTHROW(Semestre::validarNSG(100.0f));
    CHECK_NOTHROW(Semestre::validarNSG(73.5f));
    CHECK_THROWS_AS(Semestre::validarNSG(-0.1f), std::invalid_argument);
    CHECK_THROWS_AS(Semestre::validarNSG(100.1f), std::invalid_argument);
}

TEST_CASE("Semestre - validarHoras exige valor nao negativo e multiplo de 15")
{
    CHECK_NOTHROW(Semestre::validarHoras(0));
    CHECK_NOTHROW(Semestre::validarHoras(15));
    CHECK_NOTHROW(Semestre::validarHoras(60));
    CHECK_THROWS_AS(Semestre::validarHoras(-15), std::invalid_argument);
    CHECK_THROWS_AS(Semestre::validarHoras(10), std::invalid_argument);
    CHECK_THROWS_AS(Semestre::validarHoras(100), std::invalid_argument); 
}

TEST_CASE("Semestre - validarIntervaloSemestres")
{
    CHECK_NOTHROW(Semestre::validarIntervaloSemestres("2025/01", "2025/01"));  
    CHECK_NOTHROW(Semestre::validarIntervaloSemestres("2025/01", "2026/02"));
    CHECK_NOTHROW(Semestre::validarIntervaloSemestres("2016/01", "2025/02"));  

  
    CHECK_THROWS_AS(Semestre::validarIntervaloSemestres("2026/01", "2025/02"), std::invalid_argument);
    CHECK_THROWS_AS(Semestre::validarIntervaloSemestres("2026/02", "2026/01"), std::invalid_argument);

  
    CHECK_THROWS_AS(Semestre::validarIntervaloSemestres("2016/01", "2026/01"), std::invalid_argument);


    CHECK_THROWS_AS(Semestre::validarIntervaloSemestres("2025/3", "2026/01"), std::invalid_argument);
    CHECK_THROWS_AS(Semestre::validarIntervaloSemestres("2025/01", "xxxx/01"), std::invalid_argument);
}

TEST_CASE("Semestre - gerarSemestresAnteriores")
{
    SUBCASE("ingresso igual ao atual gera lista vazia")
    {
        CHECK(Semestre::gerarSemestresAnteriores("2026/01", "2026/01").empty());
    }

    SUBCASE("do primeiro semestre ate o anterior ao atual")
    {
        std::vector<std::string> lista = Semestre::gerarSemestresAnteriores("2025/01", "2026/01");
        REQUIRE(lista.size() == 2);
        CHECK(lista[0] == "2025/01");
        CHECK(lista[1] == "2025/02");
    }

    SUBCASE("atravessando a virada de ano")
    {
        std::vector<std::string> lista = Semestre::gerarSemestresAnteriores("2025/02", "2026/02");
        REQUIRE(lista.size() == 2);
        CHECK(lista[0] == "2025/02");
        CHECK(lista[1] == "2026/01");
    }

    SUBCASE("intervalo invalido lanca excecao")
    {
        CHECK_THROWS_AS(Semestre::gerarSemestresAnteriores("2026/02", "2026/01"), std::invalid_argument);
    }
}

TEST_CASE("Semestre - construtor valida o identificador")
{
    CHECK_NOTHROW(SemestreConsolidado("2025/01", 80.0f, 60, 0, 0));
    CHECK_THROWS_AS(SemestreConsolidado("2025/3", 80.0f, 60, 0, 0), std::invalid_argument);
    CHECK_THROWS_AS(SemestreConsolidado("", 80.0f, 60, 0, 0), std::invalid_argument);
}

TEST_CASE("Semestre - getIdentificador, isTrancado e setTrancado")
{
    SemestreConsolidado s("2025/02", 80.0f, 60, 0, 0);

    CHECK(s.getIdentificador() == "2025/02");
    CHECK(s.isTrancado() == false);

    s.setTrancado(true);
    CHECK(s.isTrancado() == true);

    s.setTrancado(false);
    CHECK(s.isTrancado() == false);
}