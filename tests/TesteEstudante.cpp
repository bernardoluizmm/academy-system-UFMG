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

TEST_CASE("Calculo de Percentuais de Integralizacao")
{
    Curso curso(Curso::OPCAO_CC, "2025/01");
    HistoricoEscolar historico("2026/01");
    Estudante estudante("Estudante Teste", curso, historico);

    SUBCASE("Estado Inicial - 0 em todas as categorias") 
    {
        CHECK(estudante.calcularPercentualObrigatorias() == doctest::Approx(0.0f));
        CHECK(estudante.calcularPercentualOptativas() == doctest::Approx(0.0f));
        CHECK(estudante.calcularPercentualFormacaoLivre() == doctest::Approx(0.0f));
        CHECK(estudante.calcularPercentualCursoCompleto() == doctest::Approx(0.0f));
    }

    SUBCASE("Progresso de metade do curso de cada tipo") 
    { 
    
        SemestreConsolidado sem1("2025/01", 85.0f, 990, 555, 60, false);
        estudante.getHistoricoEditavel().adicionarSemestreConsolidado(sem1);

        CHECK(estudante.calcularPercentualObrigatorias() == doctest::Approx(50.0f));
        CHECK(estudante.calcularPercentualOptativas() == doctest::Approx(50.0f));
        CHECK(estudante.calcularPercentualFormacaoLivre() == doctest::Approx(50.0f));
        CHECK(estudante.calcularPercentualCursoCompleto() == doctest::Approx(50.0f));
    }

    SUBCASE("Edge Case - Curso Completo") 
    {
        SemestreConsolidado sem1("2025/01", 90.0f, 1980, 1110, 120, false);
        estudante.getHistoricoEditavel().adicionarSemestreConsolidado(sem1);

        CHECK(estudante.calcularPercentualObrigatorias() == doctest::Approx(100.0f));
        CHECK(estudante.calcularPercentualOptativas() == doctest::Approx(100.0f));
        CHECK(estudante.calcularPercentualFormacaoLivre() == doctest::Approx(100.0f));
        CHECK(estudante.calcularPercentualCursoCompleto() == doctest::Approx(100.0f));
    }

    SUBCASE("Edge Case - Horas excedentes devem travar no teto de 100%") 
    {
    
        SemestreConsolidado semExcedente("2025/01", 95.0f, 2400, 1500, 240, false);
        estudante.getHistoricoEditavel().adicionarSemestreConsolidado(semExcedente);

        CHECK(estudante.calcularPercentualObrigatorias() == doctest::Approx(100.0f));
        CHECK(estudante.calcularPercentualOptativas() == doctest::Approx(100.0f));
        CHECK(estudante.calcularPercentualFormacaoLivre() == doctest::Approx(100.0f));
        CHECK(estudante.calcularPercentualCursoCompleto() == doctest::Approx(100.0f));
    }

    SUBCASE("Edge Case - Semestre trancado nao altera percentuais") 
    {
        SemestreConsolidado semTrancado("2025/01", 90.0f, 300, 120, 60, true);
        estudante.getHistoricoEditavel().adicionarSemestreConsolidado(semTrancado);

        CHECK(estudante.calcularPercentualObrigatorias() == doctest::Approx(0.0f));
        CHECK(estudante.calcularPercentualOptativas() == doctest::Approx(0.0f));
        CHECK(estudante.calcularPercentualFormacaoLivre() == doctest::Approx(0.0f));
        CHECK(estudante.calcularPercentualCursoCompleto() == doctest::Approx(0.0f));
    }

}

TEST_CASE("Serializacao do Perfil Completo") 
{
    Curso curso(Curso::OPCAO_CC, "2026/01");
    HistoricoEscolar historico("2026/02");
    Estudante estudante("Bernardo", curso, historico);

    SUBCASE("Serializacao basica - sem semestres consolidados ou disciplinas") 
    {
        std::string esperado = "ESTUDANTE|Bernardo\nCURSO|1|2026/01\nSEMESTRE_ATUAL|2026/02\n";

        CHECK(estudante.serializar() == esperado);
    }

    SUBCASE("Serializacao com semestre consolidado e com disciplina no semestre atual") 
    {
        SemestreConsolidado semPassado("2026/01", 93.0f, 300, 0, 0, false);
        estudante.getHistoricoEditavel().adicionarSemestreConsolidado(semPassado);
        estudante.getHistoricoEditavel().getSemestreAtual()->adicionarDisciplina(
            "DCC204", "TZ1", "PDS II", "Prof", "ICEx 2010", 60, 100, "Obrigatoria", "Seg/Qua"
        );

        std::string esperado = "ESTUDANTE|Bernardo\nCURSO|1|2026/01\nSEMESTRE_CONSOLIDADO|2026/01|93|300|0|0|0\nSEMESTRE_ATUAL|2026/02\nDISCIPLINA|1|DCC204|TZ1|PDS II|Prof|ICEx 2010|60|100|Obrigatoria|Seg/Qua|0\n";

        CHECK(estudante.serializar() == esperado);
    }
}
