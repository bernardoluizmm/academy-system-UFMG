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