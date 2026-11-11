#include "doctest.h"
#include "HistoricoEscolar.hpp"
#include <stdexcept>
#include <string>

namespace
{
    void adicionar(SemestreAtual& semestre, const std::string& nome, int cargaHoraria,
                   const std::string& tipo = "Obrigatoria")
    {
        semestre.adicionarDisciplina("COD", "T1", nome, "Professor", "ICEx 101",
                                     cargaHoraria, 50, tipo, "Seg 10h");
    }

    void lancarNota(SemestreAtual& semestre, int idDisciplina, float valorMaximo, float nota)
    {
        Disciplina* disciplina = semestre.buscarDisciplina(idDisciplina);
        REQUIRE(disciplina != nullptr);
        int idAtividade = static_cast<int>(disciplina->avaliacoes().getAtividades().size()) + 1;
        disciplina->avaliacoes().adicionarAtividade(idAtividade, "Prova", "01/05", valorMaximo, nota, true);
    }
}

TEST_CASE("HistoricoEscolar - construtor cria o semestre atual informado")
{
    HistoricoEscolar historico("2026/01");

    REQUIRE(historico.getSemestreAtual() != nullptr);
    CHECK(historico.getSemestreAtual()->getIdentificador() == "2026/01");
    CHECK(historico.getSemestresPassados().empty());
}

TEST_CASE("HistoricoEscolar - construtor rejeita identificador invalido")
{
    CHECK_THROWS_AS(HistoricoEscolar("2026/3"), std::invalid_argument);
    CHECK_THROWS_AS(HistoricoEscolar(""), std::invalid_argument);
}

TEST_CASE("HistoricoEscolar - historico novo tem NSG e horas zerados")
{
    HistoricoEscolar historico("2026/01");

    CHECK(historico.calcularNSGMedio() == doctest::Approx(0.0));
    CHECK(historico.calcularNSGGlobal() == doctest::Approx(0.0));
    CHECK(historico.calcularTotalHorasObrigatorias() == 0);
    CHECK(historico.calcularTotalHorasOptativas() == 0);
    CHECK(historico.calcularTotalHorasFormacaoLivre() == 0);
    CHECK(historico.calcularTotalHorasIntegralizadas() == 0);
}

TEST_CASE("HistoricoEscolar - consolidar avanca para o proximo semestre")
{
    HistoricoEscolar historico("2026/01");
    historico.consolidarSemestreAtual();

    REQUIRE(historico.getSemestresPassados().size() == 1);
    CHECK(historico.getSemestresPassados()[0].getIdentificador() == "2026/01");
    CHECK(historico.getSemestreAtual()->getIdentificador() == "2026/02");

    historico.consolidarSemestreAtual();
    CHECK(historico.getSemestresPassados().size() == 2);
    CHECK(historico.getSemestreAtual()->getIdentificador() == "2027/01");  
}

TEST_CASE("HistoricoEscolar - consolidar leva NSG e horas do semestre atual")
{
    HistoricoEscolar historico("2026/01");
    SemestreAtual* atual = historico.getSemestreAtual();
    adicionar(*atual, "Aprovada", 60, "Obrigatoria");
    adicionar(*atual, "Reprovada", 30, "Optativa");
    lancarNota(*atual, 1, 100.0f, 80.0f);
    lancarNota(*atual, 2, 100.0f, 50.0f);

    historico.consolidarSemestreAtual();

    REQUIRE(historico.getSemestresPassados().size() == 1);
    const SemestreConsolidado& consolidado = historico.getSemestresPassados()[0];
    CHECK(consolidado.calcularNSG() == doctest::Approx(70.0));  
    CHECK(consolidado.getHorasObrigatorias() == 60);
    CHECK(consolidado.getHorasOptativas() == 0);                 
    CHECK(consolidado.getHorasIntegralizadas() == 60);
    CHECK(historico.getSemestreAtual()->getDisciplinas().empty());
}

TEST_CASE("HistoricoEscolar - consolidar como trancado zera os valores")
{
    HistoricoEscolar historico("2026/01");
    SemestreAtual* atual = historico.getSemestreAtual();
    adicionar(*atual, "Aprovada", 60);
    lancarNota(*atual, 1, 100.0f, 90.0f);

    historico.consolidarSemestreAtual(true);

    REQUIRE(historico.getSemestresPassados().size() == 1);
    const SemestreConsolidado& consolidado = historico.getSemestresPassados()[0];
    CHECK(consolidado.isTrancado() == true);
    CHECK(consolidado.calcularNSG() == doctest::Approx(0.0));
    CHECK(consolidado.getHorasIntegralizadas() == 0);
    CHECK(historico.getSemestreAtual()->getIdentificador() == "2026/02");
}

TEST_CASE("HistoricoEscolar - consolidar com proximo semestre invalido nao altera o historico")
{
    HistoricoEscolar historico("2100/02");  

    CHECK_THROWS_AS(historico.consolidarSemestreAtual(), std::invalid_argument);

   
    CHECK(historico.getSemestresPassados().empty());
    REQUIRE(historico.getSemestreAtual() != nullptr);
    CHECK(historico.getSemestreAtual()->getIdentificador() == "2100/02");
}

TEST_CASE("HistoricoEscolar - definirSemestreAtual")
{
    HistoricoEscolar historico("2026/01");
    adicionar(*historico.getSemestreAtual(), "PDS2", 60);

    SUBCASE("substitui por um semestre novo e vazio")
    {
        historico.definirSemestreAtual("2027/02");
        CHECK(historico.getSemestreAtual()->getIdentificador() == "2027/02");
        CHECK(historico.getSemestreAtual()->getDisciplinas().empty());
    }

    SUBCASE("identificador invalido lanca excecao e mantem o semestre atual")
    {
        CHECK_THROWS_AS(historico.definirSemestreAtual("2027/9"), std::invalid_argument);
        CHECK(historico.getSemestreAtual()->getIdentificador() == "2026/01");
        CHECK(historico.getSemestreAtual()->getDisciplinas().size() == 1);
    }
}

TEST_CASE("HistoricoEscolar - adicionarSemestreConsolidado e limparSemestresPassados")
{
    HistoricoEscolar historico("2027/01");
    historico.adicionarSemestreConsolidado(SemestreConsolidado("2026/01", 80.0f, 60, 0, 0));
    historico.adicionarSemestreConsolidado(SemestreConsolidado("2026/02", 70.0f, 30, 0, 0));

    CHECK(historico.getSemestresPassados().size() == 2);

    historico.limparSemestresPassados();
    CHECK(historico.getSemestresPassados().empty());
    CHECK(historico.getSemestreAtual()->getIdentificador() == "2027/01"); 
}

TEST_CASE("HistoricoEscolar - NSG medio e NSG global")
{
    HistoricoEscolar historico("2027/01");
    historico.adicionarSemestreConsolidado(SemestreConsolidado("2026/01", 80.0f, 270, 0, 0));
    historico.adicionarSemestreConsolidado(SemestreConsolidado("2026/02", 60.0f, 90, 0, 0));

    CHECK(historico.calcularNSGMedio() == doctest::Approx(70.0));    
    CHECK(historico.calcularNSGGlobal() == doctest::Approx(75.0));  
}

TEST_CASE("HistoricoEscolar - semestre trancado nao entra nos NSGs")
{
    HistoricoEscolar historico("2027/01");
    historico.adicionarSemestreConsolidado(SemestreConsolidado("2026/01", 80.0f, 60, 0, 0));
    historico.adicionarSemestreConsolidado(SemestreConsolidado("2026/02", 0.0f, 0, 0, 0, true));

    CHECK(historico.calcularNSGMedio() == doctest::Approx(80.0));
    CHECK(historico.calcularNSGGlobal() == doctest::Approx(80.0));
}

TEST_CASE("HistoricoEscolar - NSG global e 0 quando nao ha horas integralizadas")
{
    HistoricoEscolar historico("2027/01");
    historico.adicionarSemestreConsolidado(SemestreConsolidado("2026/01", 50.0f, 0, 0, 0));

    CHECK(historico.calcularNSGMedio() == doctest::Approx(50.0));
    CHECK(historico.calcularNSGGlobal() == doctest::Approx(0.0));  
}

TEST_CASE("HistoricoEscolar - totais de horas somam todos os semestres passados")
{
    HistoricoEscolar historico("2027/02");
    historico.adicionarSemestreConsolidado(SemestreConsolidado("2026/01", 80.0f, 60, 30, 15));
    historico.adicionarSemestreConsolidado(SemestreConsolidado("2026/02", 70.0f, 45, 15, 0));
    historico.adicionarSemestreConsolidado(SemestreConsolidado("2027/01", 0.0f, 90, 90, 90, true)); 

    CHECK(historico.calcularTotalHorasObrigatorias() == 105);
    CHECK(historico.calcularTotalHorasOptativas() == 45);
    CHECK(historico.calcularTotalHorasFormacaoLivre() == 15);
    CHECK(historico.calcularTotalHorasIntegralizadas() == 165);
}

