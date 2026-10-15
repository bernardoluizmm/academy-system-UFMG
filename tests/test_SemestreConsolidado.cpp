#include "doctest.h"
#include "SemestreConsolidado.hpp"

TEST_CASE("SemestreConsolidado - Construtor e Getters (Casos Base)") {
    Disciplina d1("Calculo I", "MAT001", "Prof", "ICEx", CategoriaDisciplina::OBRIGATORIA, 60, 15);
    Disciplina d2("Algebra Linear", "MAT038", "Prof", "ICEx", CategoriaDisciplina::OBRIGATORIA, 60, 15);
    std::vector<Disciplina> discList = {d1, d2};

    SemestreConsolidado consolidado("2025/2", 85.5, discList);

    CHECK(consolidado.getPeriodo() == "2025/2");
    CHECK(consolidado.getNSG() == doctest::Approx(85.5));
    CHECK(consolidado.getDisciplinas().size() == 2);
    CHECK(consolidado.calcularTotalHoras() == 120);
}

TEST_CASE("SemestreConsolidado - Alterar NSG e Polimorfismo") {
    std::vector<Disciplina> vazias;
    SemestreConsolidado consolidado("2024/1", 70.0, vazias);

    consolidado.setNSG(90.0);
    CHECK(consolidado.getNSG() == doctest::Approx(90.0));


    Semestre* semPtr = &consolidado;
    CHECK(semPtr->getNSG() == doctest::Approx(90.0));
    CHECK(semPtr->getPeriodo() == "2024/1");
}

TEST_CASE("SemestreConsolidado - Semestre sem disciplinas (Casos Limite)") {
    std::vector<Disciplina> vazias;
    SemestreConsolidado consolidado("2023/1", 0.0, vazias);

    CHECK(consolidado.calcularTotalHoras() == 0);
    CHECK(consolidado.getDisciplinas().empty());
}
