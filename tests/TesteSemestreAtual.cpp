#include "doctest.h"
#include "SemestreAtual.hpp"

TEST_CASE("SemestreAtual - Construtor e Getters (Casos Base)") {
    SemestreAtual semestre("2026/1");

    CHECK(semestre.getPeriodo() == "2026/1");
    CHECK(semestre.getDisciplinas().empty());
    CHECK(semestre.getNSG() == doctest::Approx(0.0));
}

TEST_CASE("SemestreAtual - Adicionar e Remover Disciplinas") {
    SemestreAtual semestre("2026/1");

    Disciplina d1("PDS2", "DCC204", "Douglas", "ICEx", CategoriaDisciplina::OBRIGATORIA, 60, 15);
    Disciplina d2("ED", "DCC205", "Marcus", "ICEx", CategoriaDisciplina::OBRIGATORIA, 60, 15);

    semestre.adicionarDisciplina(d1);
    CHECK(semestre.getDisciplinas().size() == 1);
    CHECK(semestre.getDisciplinas()[0].getCodigo() == "DCC204");

    semestre.adicionarDisciplina(d2);
    CHECK(semestre.getDisciplinas().size() == 2);

    SUBCASE("Remover disciplina valida") {
        CHECK(semestre.removerDisciplina(0) == true);
        CHECK(semestre.getDisciplinas().size() == 1);
        CHECK(semestre.getDisciplinas()[0].getCodigo() == "DCC205");
    }

    SUBCASE("Remover disciplina com indice invalido") {
        CHECK(semestre.removerDisciplina(-1) == false);
        CHECK(semestre.removerDisciplina(10) == false);
        CHECK(semestre.getDisciplinas().size() == 2);
    }
}

TEST_CASE("SemestreAtual - Calculo de NSG Polimorfico") {
    SemestreAtual semestre("2026/1");

    Disciplina d1("D1", "C1", "P", "S", CategoriaDisciplina::OBRIGATORIA, 60, 15);
    AtividadeAvaliativa a1("P1", "2026-05-01", 100.0);
    a1.registrarNota(80.0); 
    d1.adicionarAtividade(a1);

    Disciplina d2("D2", "C2", "P", "S", CategoriaDisciplina::OBRIGATORIA, 30, 8);
    AtividadeAvaliativa a2("P2", "2026-05-01", 100.0);
    a2.registrarNota(50.0); 
    d2.adicionarAtividade(a2);

    semestre.adicionarDisciplina(d1);
    semestre.adicionarDisciplina(d2);

    
    Semestre* semPtr = &semestre;
    CHECK(semPtr->getNSG() == doctest::Approx(70.0));
}
