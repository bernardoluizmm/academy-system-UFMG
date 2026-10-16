#include "doctest.h"
#include "Curso.hpp"

TEST_CASE("Curso - Construtor e Getters/Setters (Casos Base)") 
{
    Curso curso("Ciencia da Computacao", 2400, 600, 300);

    CHECK(curso.getNome() == "Ciencia da Computacao");
    CHECK(curso.getHorasObrigatorias() == 2400);
    CHECK(curso.getHorasOptativas() == 600);
    CHECK(curso.getHorasFormacaoLivre() == 300);
    CHECK(curso.getTotalHorasExigidas() == 3300);
    CHECK(curso.getSemestresConsolidados().empty());

    curso.setNome("Sistemas de Informacao");
    CHECK(curso.getNome() == "Sistemas de Informacao");

    curso.setHorasFormacaoLivre(400);
    CHECK(curso.getHorasFormacaoLivre() == 400);
    CHECK(curso.getTotalHorasExigidas() == 3400);
}

TEST_CASE("Curso - Adicionar e Remover Semestres Consolidados") 
{
    Curso curso("Engenharia de Software", 2000, 500, 200);

    std::vector<Disciplina> discs;
    SemestreConsolidado s1("2024/1", 80.0, discs);
    SemestreConsolidado s2("2024/2", 85.0, discs);

    curso.adicionarSemestreConsolidado(s1);
    CHECK(curso.getSemestresConsolidados().size() == 1);
    CHECK(curso.getSemestresConsolidados()[0].getPeriodo() == "2024/1");

    curso.adicionarSemestreConsolidado(s2);
    CHECK(curso.getSemestresConsolidados().size() == 2);

    SUBCASE("Remocao com indice valido") 
    {
        CHECK(curso.removerSemestreConsolidado(0) == true);
        CHECK(curso.getSemestresConsolidados().size() == 1);
        CHECK(curso.getSemestresConsolidados()[0].getPeriodo() == "2024/2");
    }

    SUBCASE("Remocao com indice invalido") 
    {
        CHECK(curso.removerSemestreConsolidado(-1) == false);
        CHECK(curso.removerSemestreConsolidado(10) == false);
        CHECK(curso.getSemestresConsolidados().size() == 2);
    }
}

TEST_CASE("Curso - Calculo de Percentuais de Integralizacao e Grafico") 
{
    Curso curso("Matematica Computacional", 100, 50, 50); // Total: 200 horas

    Disciplina dObr("D1", "C1", "P", "S", CategoriaDisciplina::OBRIGATORIA, 50, 10);
    Disciplina dOpt("D2", "C2", "P", "S", CategoriaDisciplina::OPTATIVA, 25, 5);
    Disciplina dLivre("D3", "C3", "P", "S", CategoriaDisciplina::FORMACAO_LIVRE, 25, 5);

    std::vector<Disciplina> s1Discs = {dObr};
    SemestreConsolidado s1("2024/1", 75.0, s1Discs);

    std::vector<Disciplina> s2Discs = {dOpt, dLivre};
    SemestreConsolidado s2("2024/2", 85.0, s2Discs);

    curso.adicionarSemestreConsolidado(s1);
    curso.adicionarSemestreConsolidado(s2);


    CHECK(curso.calcularPercentualCategoria(CategoriaDisciplina::OBRIGATORIA) == doctest::Approx(50.0));

    CHECK(curso.calcularPercentualCategoria(CategoriaDisciplina::OPTATIVA) == doctest::Approx(50.0));
  
    CHECK(curso.calcularPercentualCategoria(CategoriaDisciplina::FORMACAO_LIVRE) == doctest::Approx(50.0));

 
    CHECK(curso.calcularPercentualIntegralizacao() == doctest::Approx(50.0));

   
    std::vector<PontoGrafico> pontos = curso.gerarDadosGrafico();
    CHECK(pontos.size() == 2);
    CHECK(pontos[0].periodo == "2024/1");
    CHECK(pontos[0].nsg == doctest::Approx(75.0));
    CHECK(pontos[1].periodo == "2024/2");
    CHECK(pontos[1].nsg == doctest::Approx(85.0));
}
