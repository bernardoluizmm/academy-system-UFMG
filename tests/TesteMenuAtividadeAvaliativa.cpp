#include "doctest.h"
#include "TestHelpers.hpp"
#include "MenuAtividadeAvaliativa.hpp"

#include <string>

TEST_CASE("MenuAtividadeAvaliativa::MenuAtividadeAvaliativa [positivo] constroi com um semestre")
{
    SemestreAtual semestre;
    CHECK_NOTHROW(MenuAtividadeAvaliativa menu(semestre));
}

TEST_CASE("MenuAtividadeAvaliativa::exibir [positivo] mostra titulo e opcoes do menu")
{
    SemestreAtual semestre;
    MenuAtividadeAvaliativa menu(semestre);
    const std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "GERENCIAMENTO DE ATIVIDADES AVALIATIVAS"));
    CHECK(contem(saida, "1 - Criar nova atividade avaliativa"));
    CHECK(contem(saida, "2 - Lancar / Atualizar nota obtida em atividade"));
    CHECK(contem(saida, "3 - Editar atividade avaliativa existente"));
    CHECK(contem(saida, "4 - Apagar atividade avaliativa existente"));
    CHECK(contem(saida, "0 - Voltar ao Menu Principal"));
}

TEST_CASE("MenuAtividadeAvaliativa::exibir [limite] semestre vazio mostra aviso")
{
    SemestreAtual semestre;
    MenuAtividadeAvaliativa menu(semestre);

    CHECK(contem(exibirMenu(menu), "Nenhuma disciplina cadastrada no semestre atual."));
}

TEST_CASE("MenuAtividadeAvaliativa::exibir [limite] disciplina sem atividades mostra aviso")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);
    const std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "Disciplina [1] COD001 - Programacao"));
    CHECK(contem(saida, "(Nenhuma atividade avaliativa cadastrada)"));
}

TEST_CASE("MenuAtividadeAvaliativa::exibir [positivo] atividade pendente aparece na tabela")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);
    const std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "Nota Obtida"));
    CHECK(contem(saida, "Prova 1"));
    CHECK(contem(saida, "15/03"));
    CHECK(contem(saida, "10.00"));
    CHECK(contem(saida, "Pendente"));
}

TEST_CASE("MenuAtividadeAvaliativa::exibir [positivo] atividade concluida mostra a nota")
{
    Cenario c(true);
    c.atividade()->setNotaObtida(7.5f);
    MenuAtividadeAvaliativa menu(c.semestre);
    const std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "7.50"));
    CHECK_FALSE(contem(saida, "Pendente"));
}

TEST_CASE("MenuAtividadeAvaliativa::processarEntrada [positivo] opcao 0 retorna nullptr")
{
    SemestreAtual semestre;
    MenuAtividadeAvaliativa menu(semestre);

    Resultado r = executar(menu, "0\n");
    CHECK(r.proximo == nullptr);
}

TEST_CASE("MenuAtividadeAvaliativa::processarEntrada [negativo] opcao invalida exibe erro")
{
    SemestreAtual semestre;
    MenuAtividadeAvaliativa menu(semestre);

    Resultado r = executar(menu, "9\n0\n");
    CHECK(contem(r.saida, "[ERRO] Opcao invalida. Escolha entre 0 e 4."));
}

