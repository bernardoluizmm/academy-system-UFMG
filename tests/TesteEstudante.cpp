#include "doctest.h"
#include "Estudante.hpp"
#include "Curso.hpp"
#include "HistoricoEscolar.hpp"

TEST_CASE("Inicialização do Construtor Parametrizado")
{
    Curso curso(Curso::OPCAO_CC, "2026/01");
    HistoricoEscolar historico("2026/02");
    Estudante estudante("Bernardo Luiz", curso, historico);

    SUBCASE("Happy Path - Nome comum valido")
    {
    CHECK(estudante.getNome() == "Bernardo Luiz");
    CHECK(estudante.getCurso().getOpcaoCurso() == Curso::OPCAO_CC);
    CHECK(estudante.getHistorico().getSemestreAtual()->getIdentificador() == "2026/02");
    }

    SUBCASE("Edge Case - Limite inferior")
    {
        std::string nomeUmChar = "B";
        CHECK_NOTHROW(Estudante::validarNome(nomeUmChar));
        Estudante estudante(nomeUmChar, curso, historico);
        CHECK(estudante.getNome() == "B");
    }

    SUBCASE("Edge Case - Limite superior")
    {
        std::string nomeCemCaracteres(100, 'A');
            CHECK_NOTHROW(Estudante::validarNome(nomeCemCaracteres));
            Estudante estudante(nomeCemCaracteres, curso, historico);
            CHECK(estudante.getNome().length() == 100);
            CHECK(estudante.getNome() == nomeCemCaracteres);
    }

    SUBCASE("Excecao - Nome vazio")
    {
        std::string nomeVazio = "";
        CHECK_THROWS_AS(Estudante::validarNome(nomeVazio), std::invalid_argument);
        CHECK_THROWS_AS(Estudante(nomeVazio, curso, historico), std::invalid_argument);
    }
    
    SUBCASE("Excecao - Nome acima do limite")
    {
        std::string nomeCentoUmCaracteres(101, 'A');
        CHECK_THROWS_AS(Estudante::validarNome(nomeCentoUmCaracteres), std::invalid_argument);
        CHECK_THROWS_AS(Estudante(nomeCentoUmCaracteres, curso, historico), std::invalid_argument);
    }
}

TEST_CASE("Métodos Getters")
{
    Curso curso(Curso::OPCAO_SI, "2025/01");
    HistoricoEscolar historico("2025/02");
    Estudante estudante("Luana", curso, historico);

    CHECK(estudante.getNome() == "Luana");
    CHECK(estudante.getCurso().getOpcaoCurso() == Curso::OPCAO_SI);
    CHECK(estudante.getCurso().getNome() == "Sistemas de Informacao");
    CHECK(estudante.getCurso().getSemestreIngresso() == "2025/01");

    SemestreConsolidado semestre("2025/01", 88.5f, 300, 60, 0, false);
    estudante.getHistoricoEditavel().adicionarSemestreConsolidado(semestre);

    CHECK(estudante.getHistorico().getSemestresPassados().size() == 1);
    CHECK(estudante.getHistorico().calcularTotalHorasIntegralizadas() == 360);
}

