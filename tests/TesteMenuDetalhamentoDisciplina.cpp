#include "doctest.h"
#include "TestHelpers.hpp"
#include "MenuDetalhamentoDisciplina.hpp"

TEST_CASE("MenuDetalhamentoDisciplina::MenuDetalhamentoDisciplina [positivo] constroi com um semestre")
{
    SemestreAtual semestre;
    CHECK_NOTHROW(MenuDetalhamentoDisciplina menu(semestre));
}

TEST_CASE("MenuDetalhamentoDisciplina::exibir [limite] semestre vazio mostra aviso")
{
    SemestreAtual semestre;
    MenuDetalhamentoDisciplina menu(semestre);

    CHECK(contem(exibirMenu(menu), "Nenhuma disciplina cadastrada no semestre atual."));
}

TEST_CASE("MenuDetalhamentoDisciplina::exibir [positivo] mostra titulo e opcoes do menu")
{
    SemestreAtual semestre;
    MenuDetalhamentoDisciplina menu(semestre);
    const std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "DETALHAMENTO DE DISCIPLINAS E ATIVIDADES AVALIATIVAS"));
    CHECK(contem(saida, "1 - Visualizar detalhamento de uma disciplina especifica"));
    CHECK(contem(saida, "2 - Visualizar detalhamento de todas as disciplinas"));
    CHECK(contem(saida, "0 - Voltar ao Menu Principal"));
}

TEST_CASE("MenuDetalhamentoDisciplina::exibir [positivo] lista ID, codigo e nome das disciplinas")
{
    Cenario c;
    MenuDetalhamentoDisciplina menu(c.semestre);
    const std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "Disciplinas disponiveis no semestre atual:"));
    CHECK(contem(saida, "[1] COD001 - Programacao"));
    CHECK_FALSE(contem(saida, "Nenhuma disciplina cadastrada"));
}

// ====================================================== processarEntrada()
TEST_CASE("MenuDetalhamentoDisciplina::processarEntrada [positivo] opcao 0 retorna nullptr")
{
    SemestreAtual semestre;
    MenuDetalhamentoDisciplina menu(semestre);

    Resultado r = executar(menu, "0\n");
    CHECK(r.proximo == nullptr);
}

TEST_CASE("MenuDetalhamentoDisciplina::processarEntrada [negativo] opcao invalida exibe erro")
{
    SemestreAtual semestre;
    MenuDetalhamentoDisciplina menu(semestre);

    Resultado r = executar(menu, "9\n0\n");
    CHECK(contem(r.saida, "[ERRO] Opcao invalida. Escolha entre 0 e 2."));
}

TEST_CASE("MenuDetalhamentoDisciplina::processarEntrada [negativo] opcao invalida pede nova entrada")
{
    SemestreAtual semestre;
    MenuDetalhamentoDisciplina menu(semestre);

    Resultado r = executar(menu, "9\n0\n");
    CHECK(r.proximo == nullptr);
}

// ================================================ opcao 1 (uma disciplina)
TEST_CASE("MenuDetalhamentoDisciplina opcao 1 [limite] sem disciplinas mostra aviso")
{
    SemestreAtual semestre;
    MenuDetalhamentoDisciplina menu(semestre);

    Resultado r = executar(menu, "1\n");
    CHECK(contem(r.saida, "[AVISO] Nenhuma disciplina cadastrada no semestre atual."));
}

TEST_CASE("MenuDetalhamentoDisciplina opcao 1 [limite] ID 0 cancela sem exibir nada")
{
    Cenario c;
    MenuDetalhamentoDisciplina menu(c.semestre);

    Resultado r = executar(menu, "1\n0\n");
    CHECK_FALSE(contem(r.saida, "Disciplina [1]"));
    CHECK_FALSE(contem(r.saida, "[ERRO]"));
}

TEST_CASE("MenuDetalhamentoDisciplina opcao 1 [negativo] ID inexistente mostra erro")
{
    Cenario c;
    MenuDetalhamentoDisciplina menu(c.semestre);

    Resultado r = executar(menu, "1\n99\n");
    CHECK(contem(r.saida, "[ERRO] Disciplina com ID 99 nao encontrada."));
}

TEST_CASE("MenuDetalhamentoDisciplina opcao 1 [positivo] permanece no menu apos detalhar")
{
    Cenario c;
    MenuDetalhamentoDisciplina menu(c.semestre);

    Resultado r = executar(menu, "1\n1\n");
    CHECK(r.proximo == &menu);
}

TEST_CASE("MenuDetalhamentoDisciplina opcao 1 [positivo] mostra os dados cadastrais")
{
    Cenario c;
    MenuDetalhamentoDisciplina menu(c.semestre);

    Resultado r = executar(menu, "1\n1\n");
    CHECK(contem(r.saida, "Disciplina [1]: Programacao"));
    CHECK(contem(r.saida, "Codigo: COD001"));
    CHECK(contem(r.saida, "Turma: T1"));
    CHECK(contem(r.saida, "Prof.: Prof. Ana"));
    CHECK(contem(r.saida, "Sala/Bloco: Sala 101"));
    CHECK(contem(r.saida, "CH: 60h"));
    CHECK(contem(r.saida, "Tipo: Obrigatoria"));
    CHECK(contem(r.saida, "Horario/Dias: Seg 10h"));
}

TEST_CASE("MenuDetalhamentoDisciplina opcao 1 [limite] disciplina sem atividades mostra cabecalho e TOTAL")
{
    Cenario c;
    MenuDetalhamentoDisciplina menu(c.semestre);

    Resultado r = executar(menu, "1\n1\n");
    CHECK(contem(r.saida, "Atividade Avaliativa"));
    CHECK(contem(r.saida, "TOTAL"));
}

TEST_CASE("MenuDetalhamentoDisciplina opcao 1 [positivo] atividade pendente aparece como Pendente")
{
    Cenario c(true);
    MenuDetalhamentoDisciplina menu(c.semestre);

    Resultado r = executar(menu, "1\n1\n");
    CHECK(contem(r.saida, "Prova 1"));
    CHECK(contem(r.saida, "15/03"));
    CHECK(contem(r.saida, "Pendente"));
}

TEST_CASE("MenuDetalhamentoDisciplina opcao 1 [positivo] atividade concluida mostra a nota obtida")
{
    Cenario c(true);
    c.atividade()->setNotaObtida(8.0f);
    MenuDetalhamentoDisciplina menu(c.semestre);

    Resultado r = executar(menu, "1\n1\n");
    CHECK(contem(r.saida, "8.00"));
    CHECK_FALSE(contem(r.saida, "Pendente"));
}

// =============================================== opcao 2 (todas)
TEST_CASE("MenuDetalhamentoDisciplina opcao 2 [limite] sem disciplinas mostra aviso")
{
    SemestreAtual semestre;
    MenuDetalhamentoDisciplina menu(semestre);

    Resultado r = executar(menu, "2\n");
    CHECK(contem(r.saida, "[AVISO] Nenhuma disciplina cadastrada no semestre atual."));
}

TEST_CASE("MenuDetalhamentoDisciplina opcao 2 [positivo] detalha todas as disciplinas")
{
    SemestreAtual semestre;
    adicionarDisciplina(semestre, 1);
    adicionarDisciplina(semestre, 2);
    MenuDetalhamentoDisciplina menu(semestre);

    Resultado r = executar(menu, "2\n");
    CHECK(contem(r.saida, "Disciplina [1]: Programacao"));
    CHECK(contem(r.saida, "Disciplina [2]: Programacao"));
}

TEST_CASE("MenuDetalhamentoDisciplina opcao 2 [positivo] permanece no menu apos detalhar")
{
    Cenario c;
    MenuDetalhamentoDisciplina menu(c.semestre);

    Resultado r = executar(menu, "2\n");
    CHECK(r.proximo == &menu);
}