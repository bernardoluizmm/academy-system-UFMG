#include "doctest.h"
#include "Disciplina.hpp"

TEST_CASE("Disciplina - Construtor e Getters") 
{
    Disciplina d(
        "Programacao e Desenvolvimento de Software II",
        "DCC204",
        "Douglas Macharet",
        "ICEx - Sala 2014",
        CategoriaDisciplina::OBRIGATORIA,
        60,
        15
    );

    CHECK(d.getNome() == "Programacao e Desenvolvimento de Software II");
    CHECK(d.getCodigo() == "DCC204");
    CHECK(d.getProfessor() == "Douglas Macharet");
    CHECK(d.getSalaBloco() == "ICEx - Sala 2014");
    CHECK(d.getCategoria() == CategoriaDisciplina::OBRIGATORIA);
    CHECK(d.getCargaHoraria() == 60);
    CHECK(d.getFrequencia().getFaltasPermitidas() == 15);
    CHECK(d.getAtividades().empty());
    CHECK(d.validarCamposObrigatorios() == true);
}

TEST_CASE("Disciplina - Gerenciamento de Atividades") 
{
    Disciplina d("Estruturas de Dados", "DCC205", "Professor X", "ICEx",
                 CategoriaDisciplina::OBRIGATORIA, 60, 15);

    AtividadeAvaliativa a1("TP1", "2026-04-10", 20.0);
    AtividadeAvaliativa a2("TP2", "2026-05-10", 30.0);

    d.adicionarAtividade(a1);
    CHECK(d.getAtividades().size() == 1);
    CHECK(d.getAtividades()[0].getNome() == "TP1");

    d.adicionarAtividade(a2);
    CHECK(d.getAtividades().size() == 2);

    SUBCASE("Editar atividade existente") 
    {
        AtividadeAvaliativa novaA1("TP1 - Revisado", "2026-04-12", 25.0);
        CHECK(d.editarAtividade(0, novaA1) == true);
        CHECK(d.getAtividades()[0].getNome() == "TP1 - Revisado");
        CHECK(d.getAtividades()[0].getValorMaximo() == doctest::Approx(25.0));
    }

    SUBCASE("Editar atividade em indice invalido") 
    {
        AtividadeAvaliativa nova("Invalida", "2026-04-12", 10.0);
        CHECK(d.editarAtividade(-1, nova) == false);
        CHECK(d.editarAtividade(2, nova) == false);
        CHECK(d.editarAtividade(10, nova) == false);
    }

    SUBCASE("Remover atividade valida") 
    {
        CHECK(d.removerAtividade(0) == true);
        CHECK(d.getAtividades().size() == 1);
        CHECK(d.getAtividades()[0].getNome() == "TP2");
    }

    SUBCASE("Remover atividade em indice invalido") 
    {
        CHECK(d.removerAtividade(-1) == false);
        CHECK(d.removerAtividade(5) == false);
        CHECK(d.getAtividades().size() == 2);
    }
}

TEST_CASE("Disciplina - Soma de Pontos, Notas e Conceitos (A, B, C, D, E, F)") 
{
    Disciplina d("Calculo I", "MAT001", "Prof. Y", "ICEx",
                 CategoriaDisciplina::OBRIGATORIA, 60, 15);

    SUBCASE("Verificar soma de 100 pontos") 
    {
        AtividadeAvaliativa p1("P1", "2026-04-01", 30.0);
        AtividadeAvaliativa p2("P2", "2026-05-01", 30.0);
        AtividadeAvaliativa p3("P3", "2026-06-01", 40.0);

        d.adicionarAtividade(p1);
        d.adicionarAtividade(p2);
        CHECK(d.verificarSomaPontos() == false);

        d.adicionarAtividade(p3);
        CHECK(d.verificarSomaPontos() == true);
    }

    SUBCASE("Calculo de nota total e conceitos (A >= 90, B >= 80, C >= 70, D >= 60, 40 <= E < 60, F < 40)") 
    {
        AtividadeAvaliativa prova("Prova Final", "2026-06-30", 100.0);
        
       
        prova.registrarNota(95.0);
        Disciplina dA("A", "C1", "P", "S", CategoriaDisciplina::OBRIGATORIA, 60, 15);
        dA.adicionarAtividade(prova);
        CHECK(dA.calcularNotaTotal() == doctest::Approx(95.0));
        CHECK(dA.determinarConceitoParcial() == 'A');
        CHECK(dA.estaAprovado() == true);

        
        prova.registrarNota(85.0);
        Disciplina dB("B", "C2", "P", "S", CategoriaDisciplina::OBRIGATORIA, 60, 15);
        dB.adicionarAtividade(prova);
        CHECK(dB.determinarConceitoParcial() == 'B');
        CHECK(dB.estaAprovado() == true);

        prova.registrarNota(72.0);
        Disciplina dC("C", "C3", "P", "S", CategoriaDisciplina::OBRIGATORIA, 60, 15);
        dC.adicionarAtividade(prova);
        CHECK(dC.determinarConceitoParcial() == 'C');
        CHECK(dC.estaAprovado() == true);

        prova.registrarNota(60.0);
        Disciplina dD("D", "C4", "P", "S", CategoriaDisciplina::OBRIGATORIA, 60, 15);
        dD.adicionarAtividade(prova);
        CHECK(dD.determinarConceitoParcial() == 'D');
        CHECK(dD.estaAprovado() == true);

        prova.registrarNota(50.0);
        Disciplina dE("E", "C5", "P", "S", CategoriaDisciplina::OBRIGATORIA, 60, 15);
        dE.adicionarAtividade(prova);
        CHECK(dE.determinarConceitoParcial() == 'E');
        CHECK(dE.estaAprovado() == false);


        prova.registrarNota(35.0);
        Disciplina dF("F", "C6", "P", "S", CategoriaDisciplina::OBRIGATORIA, 60, 15);
        dF.adicionarAtividade(prova);
        CHECK(dF.determinarConceitoParcial() == 'F');
        CHECK(dF.estaAprovado() == false);
    }
}

TEST_CASE("Disciplina - Validacao de Campos Obrigatorios") 
{
    SUBCASE("Disciplina com nome ou codigo vazio") {
        Disciplina semNome("", "DCC001", "Prof", "Sala", CategoriaDisciplina::OPTATIVA, 60, 15);
        CHECK(semNome.validarCamposObrigatorios() == false);

        Disciplina semCodigo("Algoritmos", "", "Prof", "Sala", CategoriaDisciplina::OPTATIVA, 60, 15);
        CHECK(semCodigo.validarCamposObrigatorios() == false);
    }
}