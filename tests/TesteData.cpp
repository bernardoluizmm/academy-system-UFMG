#include "doctest.h"
#include "Data.hpp"
#include <sstream>
#include <stdexcept>

TEST_CASE("Data - construcao e getter") {
    Data data("05/03");
    CHECK(data.getDataValidada() == "05/03");
    CHECK(Data("29/02").getDataValidada() == "29/02");
    CHECK(Data("31/12").getDataValidada() == "31/12");
    CHECK(Data("01/01").getDataValidada() == "01/01");
}

TEST_CASE("Data - formatos incorretos") {
    CHECK_THROWS_AS(Data(""), std::invalid_argument);
    CHECK_THROWS_AS(Data("1/01"), std::invalid_argument);
    CHECK_THROWS_AS(Data("01-01"), std::invalid_argument);
    CHECK_THROWS_AS(Data("01/001"), std::invalid_argument);
    CHECK_THROWS_AS(Data("2a/11"), std::invalid_argument);
    CHECK_THROWS_AS(Data("20/1a"), std::invalid_argument);
    CHECK_THROWS_AS(Data("ab/cd"), std::invalid_argument);
}

TEST_CASE("Data - dias e meses inexistentes") {
    CHECK_THROWS_AS(Data("00/01"), std::invalid_argument);
    CHECK_THROWS_AS(Data("01/00"), std::invalid_argument);
    CHECK_THROWS_AS(Data("01/13"), std::invalid_argument);
    CHECK_THROWS_AS(Data("32/01"), std::invalid_argument);
    CHECK_THROWS_AS(Data("31/04"), std::invalid_argument);
    CHECK_THROWS_AS(Data("30/02"), std::invalid_argument);
}

TEST_CASE("Data - comparacao por mes e depois por dia") {
    CHECK(Data("31/01") < Data("01/02"));
    CHECK(Data("02/03") < Data("10/03"));
    CHECK((Data("10/03") < Data("02/03")) == false);
    CHECK((Data("10/03") < Data("10/03")) == false);
}

TEST_CASE("Data - escrita em fluxo") {
    std::ostringstream saida;
    saida << Data("09/11");
    CHECK(saida.str() == "09/11");
}
