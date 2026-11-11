#include "doctest.h"
#include "Curso.hpp"
#include <string>
#include <stdexcept>

TEST_CASE("Validacao de Opcao de Curso") 
{
    SUBCASE("Happy Path - Opcoes validas") 
    {
        CHECK_NOTHROW(Curso::validarOpcaoCurso(Curso::OPCAO_CC));
        CHECK_NOTHROW(Curso::validarOpcaoCurso(Curso::OPCAO_SI));
        }

    SUBCASE("Excecoes - Opcoes fora do intervalo (0, 3, negativos)") 
    {
        CHECK_THROWS_AS(Curso::validarOpcaoCurso(0), std::invalid_argument);
        CHECK_THROWS_AS(Curso::validarOpcaoCurso(3), std::invalid_argument);
        CHECK_THROWS_AS(Curso::validarOpcaoCurso(-1), std::invalid_argument);
        
        CHECK_THROWS_AS(Curso(0, "2026/01"), std::invalid_argument);
        CHECK_THROWS_AS(Curso(3, "2026/01"), std::invalid_argument);
    }
}

TEST_CASE("Validacao de Semestre de Ingresso") 
{
    SUBCASE("Happy Path e Fronteiras de Ano (2016 a 2100, periodos 01 e 02)") 
    {
        CHECK_NOTHROW(Curso::validarSemestreIngresso("2016/01"));
        CHECK_NOTHROW(Curso::validarSemestreIngresso("2026/02"));
        CHECK_NOTHROW(Curso::validarSemestreIngresso("2100/02"));
    }

    SUBCASE("Excecoes - Formatos invalidos, caracteres incorretos e anos fora do limite") 
    {
        CHECK_THROWS_AS(Curso::validarSemestreIngresso(""), std::invalid_argument);
        CHECK_THROWS_AS(Curso::validarSemestreIngresso("2026/1"), std::invalid_argument);
        CHECK_THROWS_AS(Curso::validarSemestreIngresso("2026/001"), std::invalid_argument);
        CHECK_THROWS_AS(Curso::validarSemestreIngresso("2026-01"), std::invalid_argument);
        CHECK_THROWS_AS(Curso::validarSemestreIngresso("202A/01"), std::invalid_argument);
        CHECK_THROWS_AS(Curso::validarSemestreIngresso("2026/00"), std::invalid_argument);
        CHECK_THROWS_AS(Curso::validarSemestreIngresso("2026/03"), std::invalid_argument);
        CHECK_THROWS_AS(Curso::validarSemestreIngresso("2015/02"), std::invalid_argument);
        CHECK_THROWS_AS(Curso::validarSemestreIngresso("2101/01"), std::invalid_argument);
        CHECK_THROWS_AS(Curso(Curso::OPCAO_CC, "2015/02"), std::invalid_argument);
        CHECK_THROWS_AS(Curso(Curso::OPCAO_SI, "invalido"), std::invalid_argument);
    }
}