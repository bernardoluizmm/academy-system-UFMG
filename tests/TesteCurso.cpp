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

TEST_CASE("Construtor e Configuracao de Horas por Curriculo") 
{
    SUBCASE("Ciencia da Computacao - Curriculo Antigo (Fronteira: 2024/02 < 2025)") 
    {
        Curso cursoCCAntigo(Curso::OPCAO_CC, "2024/02");

        CHECK(cursoCCAntigo.getOpcaoCurso() == 1);
        CHECK(cursoCCAntigo.getNome() == "Ciencia da Computacao");
        CHECK(cursoCCAntigo.getSemestreIngresso() == "2024/02");
        CHECK(cursoCCAntigo.getHorasTotaisObrigatorias() == 2040);
        CHECK(cursoCCAntigo.getHorasTotaisOptativas() == 1020);
        CHECK(cursoCCAntigo.getHorasTotaisFormacaoLivre() == 60);
        CHECK(cursoCCAntigo.getHorasAdicionais() == 120);
        CHECK(cursoCCAntigo.getHorasTotaisCurso() == 3240);
    }

    SUBCASE("Ciencia da Computacao - Curriculo Novo (Fronteira Exata: 2025/01 >= 2025)") 
    {
        Curso cursoCCNovo(Curso::OPCAO_CC, "2025/01");

        CHECK(cursoCCNovo.getOpcaoCurso() == 1);
        CHECK(cursoCCNovo.getNome() == "Ciencia da Computacao");
        CHECK(cursoCCNovo.getSemestreIngresso() == "2025/01");
        CHECK(cursoCCNovo.getHorasTotaisObrigatorias() == 1980);
        CHECK(cursoCCNovo.getHorasTotaisOptativas() == 1110);
        CHECK(cursoCCNovo.getHorasTotaisFormacaoLivre() == 120);
        CHECK(cursoCCNovo.getHorasAdicionais() == 0);
        CHECK(cursoCCNovo.getHorasTotaisCurso() == 3210);
    }

    SUBCASE("Sistemas de Informacao - Curriculo Unico") 
    {
        Curso cursoSI(Curso::OPCAO_SI, "2026/01");

        CHECK(cursoSI.getOpcaoCurso() == 2);
        CHECK(cursoSI.getNome() == "Sistemas de Informacao");
        CHECK(cursoSI.getSemestreIngresso() == "2026/01");
        CHECK(cursoSI.getHorasTotaisObrigatorias() == 2100);
        CHECK(cursoSI.getHorasTotaisOptativas() == 780);
        CHECK(cursoSI.getHorasTotaisFormacaoLivre() == 120);
        CHECK(cursoSI.getHorasAdicionais() == 0);
        CHECK(cursoSI.getHorasTotaisCurso() == 3000);
    }
}

TEST_CASE("Serializacao da Classe Curso") 
{
    SUBCASE("Serializacao de Ciencia da Computacao") 
    {
        Curso cursoCC(Curso::OPCAO_CC, "2026/01");
        CHECK(cursoCC.serializar() == "CURSO|1|2026/01");
    }

    SUBCASE("Serializacao de Sistemas de Informacao") 
    {
        Curso cursoSI(Curso::OPCAO_SI, "2023/02");
        CHECK(cursoSI.serializar() == "CURSO|2|2023/02");
    }
}