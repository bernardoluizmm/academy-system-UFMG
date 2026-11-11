#include "doctest.h"
#include "AtividadeAvaliativa.hpp"

TEST_CASE("AtividadeAvaliativa - Construtor e Getters (Casos Base)") 
{
    AtividadeAvaliativa atividade("Prova 1", "2026-04-10", 30.0);

    CHECK(atividade.getNome() == "Prova 1");
    CHECK(atividade.getDataEntrega() == "2026-04-10");
    CHECK(atividade.getValorMaximo() == doctest::Approx(30.0));
    CHECK(atividade.getNotaObtida() == doctest::Approx(0.0));
    CHECK(atividade.calcularAproveitamento() == doctest::Approx(0.0));
}

TEST_CASE("AtividadeAvaliativa - Registrar Nota (Caminho Feliz e Limites)") 
{
    AtividadeAvaliativa atividade("Trabalho Pratico", "2026-05-15", 25.0);

    SUBCASE("Nota valida intermediaria") 
    {
        CHECK(atividade.registrarNota(20.0) == true);
        CHECK(atividade.getNotaObtida() == doctest::Approx(20.0));

        CHECK(atividade.calcularAproveitamento() == doctest::Approx(80.0));
    }

    SUBCASE("Nota valida no limite inferior (zero)") 
    {
        CHECK(atividade.registrarNota(0.0) == true);
        CHECK(atividade.getNotaObtida() == doctest::Approx(0.0));
        CHECK(atividade.calcularAproveitamento() == doctest::Approx(0.0));
    }

    SUBCASE("Nota valida no limite superior (valor maximo)") 
    {
        CHECK(atividade.registrarNota(25.0) == true);
        CHECK(atividade.getNotaObtida() == doctest::Approx(25.0));
        CHECK(atividade.calcularAproveitamento() == doctest::Approx(100.0));
    }
}

TEST_CASE("AtividadeAvaliativa - Registrar Nota (Casos Excepcionais / Invalidos)") 
{
    AtividadeAvaliativa atividade("Exercicio", "2026-06-01", 10.0);

    SUBCASE("Nota negativa nao deve ser aceita") 
    {
        CHECK(atividade.registrarNota(-1.0) == false);
        CHECK(atividade.getNotaObtida() == doctest::Approx(0.0));
    }

    SUBCASE("Nota superior ao valor maximo nao deve ser aceita")
     {
        CHECK(atividade.registrarNota(10.1) == false);
        CHECK(atividade.registrarNota(15.0) == false);
        CHECK(atividade.getNotaObtida() == doctest::Approx(0.0));
    }
}
