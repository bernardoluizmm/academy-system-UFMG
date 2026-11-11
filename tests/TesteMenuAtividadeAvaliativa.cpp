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

TEST_CASE("MenuAtividadeAvaliativa::processarEntrada [negativo] opcao invalida pede nova entrada")
{
    SemestreAtual semestre;
    MenuAtividadeAvaliativa menu(semestre);

    Resultado r = executar(menu, "9\n0\n");
    CHECK(r.proximo == nullptr);
}

TEST_CASE("MenuAtividadeAvaliativa::selecionarDisciplina [limite] semestre vazio mostra aviso")
{
    SemestreAtual semestre;
    MenuAtividadeAvaliativa menu(semestre);

    Resultado r = executar(menu, "1\n");
    CHECK(contem(r.saida, "[AVISO] Cadastre pelo menos uma disciplina antes de gerenciar atividades."));
}

TEST_CASE("MenuAtividadeAvaliativa::selecionarDisciplina [positivo] lista as disciplinas")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n0\n");
    CHECK(contem(r.saida, "Disciplinas do semestre atual:"));
    CHECK(contem(r.saida, "[1] COD001 - Programacao"));
}

TEST_CASE("MenuAtividadeAvaliativa::selecionarDisciplina [limite] ID 0 cancela sem erro")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n0\n");
    CHECK_FALSE(contem(r.saida, "[ERRO]"));
    CHECK(c.totalAtividades() == 0);
}

TEST_CASE("MenuAtividadeAvaliativa::selecionarDisciplina [negativo] ID inexistente mostra erro")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n99\n");
    CHECK(contem(r.saida, "[ERRO] Disciplina com ID 99 nao encontrada."));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoCriarAtividade [positivo] cria atividade com dados validos")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n1\nProva 1\n15/03\n10\n");

    REQUIRE(c.totalAtividades() == 1);
    CHECK(contem(r.saida, "Atividade 'Prova 1' adicionada com sucesso!"));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoCriarAtividade [positivo] grava nome, data e valor informados")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    executar(menu, "1\n1\nProva 1\n15/03\n10\n");

    REQUIRE(c.totalAtividades() == 1);
    const AtividadeAvaliativa& a = c.disciplina()->avaliacoes().getAtividades()[0];
    CHECK(a.getNome() == "Prova 1");
    CHECK(a.getData().getDataValidada() == "15/03");
    CHECK(a.getValorMaximo() == doctest::Approx(10.0f));
    CHECK_FALSE(a.isConcluida());
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoCriarAtividade [positivo] permanece no menu")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n1\nProva 1\n15/03\n10\n");
    CHECK(r.proximo == &menu);
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoCriarAtividade [negativo] nome invalido e pedido novamente")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);
    const std::string nomeLongo(200, 'N');

    Resultado r = executar(menu, "1\n1\n" + nomeLongo + "\nProva 1\n15/03\n10\n");

    CHECK(contem(r.saida, "[ERRO]"));
    REQUIRE(c.totalAtividades() == 1);
    CHECK(c.disciplina()->avaliacoes().getAtividades()[0].getNome() == "Prova 1");
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoCriarAtividade [negativo] data invalida e pedida novamente")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n1\nProva 1\n32/13\n15/03\n10\n");

    CHECK(contem(r.saida, "[ERRO]"));
    REQUIRE(c.totalAtividades() == 1);
    CHECK(c.disciplina()->avaliacoes().getAtividades()[0].getData().getDataValidada() == "15/03");
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoCriarAtividade [negativo] valor invalido e pedido novamente")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n1\nProva 1\n15/03\n-5\n10\n");

    CHECK(contem(r.saida, "[ERRO]"));
    REQUIRE(c.totalAtividades() == 1);
    CHECK(c.disciplina()->avaliacoes().getAtividades()[0].getValorMaximo() == doctest::Approx(10.0f));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoLancarNota [limite] disciplina sem atividades mostra aviso")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "2\n1\n");
    CHECK(contem(r.saida, "[AVISO] Esta disciplina nao possui atividades cadastradas."));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoLancarNota [limite] ID 0 cancela sem lancar nota")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    executar(menu, "2\n1\n0\n");
    CHECK_FALSE(c.atividade()->isConcluida());
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoLancarNota [negativo] atividade inexistente mostra erro")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "2\n1\n999\n");
    CHECK(contem(r.saida, "[ERRO] Atividade com ID 999 nao encontrada."));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoLancarNota [positivo] lanca nota valida")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "2\n1\n" + c.id() + "\n8\n");

    CHECK(contem(r.saida, "Nota lancada com sucesso!"));
    CHECK(c.atividade()->isConcluida());
    CHECK(c.atividade()->getNotaObtida() == doctest::Approx(8.0f));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoLancarNota [negativo] nota acima do valor maximo e pedida novamente")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "2\n1\n" + c.id() + "\n15\n8\n");

    CHECK(contem(r.saida, "[ERRO]"));
    CHECK(c.atividade()->getNotaObtida() == doctest::Approx(8.0f));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [limite] disciplina sem atividades mostra aviso")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "3\n1\n");
    CHECK(contem(r.saida, "[AVISO] Esta disciplina nao possui atividades cadastradas."));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [limite] ID 0 cancela a edicao")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "3\n1\n0\n");
    CHECK_FALSE(contem(r.saida, "EDITANDO ATIVIDADE"));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [negativo] atividade inexistente mostra erro")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "3\n1\n999\n");
    CHECK(contem(r.saida, "[ERRO] Atividade com ID 999 nao encontrada."));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [positivo] exibe o submenu de edicao")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "3\n1\n" + c.id() + "\n0\n");
    CHECK(contem(r.saida, "--- EDITANDO ATIVIDADE [" + c.id() + "] Prova 1 ---"));
    CHECK(contem(r.saida, "5 - Remover lancamento de nota (marcar como Pendente)"));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [positivo] opcao 1 altera o nome")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "3\n1\n" + c.id() + "\n1\nProva Final\n0\n");

    CHECK(contem(r.saida, "Atividade atualizada com sucesso!"));
    CHECK(c.atividade()->getNome() == "Prova Final");
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [positivo] opcao 2 altera a data")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    executar(menu, "3\n1\n" + c.id() + "\n2\n20/04\n0\n");
    CHECK(c.atividade()->getData().getDataValidada() == "20/04");
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [negativo] opcao 2 com data invalida mostra erro")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "3\n1\n" + c.id() + "\n2\n32/13\n0\n");

    CHECK(contem(r.saida, "[ERRO]"));
    CHECK(c.atividade()->getData().getDataValidada() == "15/03");
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [positivo] opcao 3 altera o valor")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    executar(menu, "3\n1\n" + c.id() + "\n3\n20\n0\n");
    CHECK(c.atividade()->getValorMaximo() == doctest::Approx(20.0f));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [negativo] opcao 3 com valor invalido preserva o anterior")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "3\n1\n" + c.id() + "\n3\n-1\n0\n");

    CHECK(contem(r.saida, "[ERRO]"));
    CHECK(c.atividade()->getValorMaximo() == doctest::Approx(10.0f));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [positivo] opcao 4 lanca a nota")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    executar(menu, "3\n1\n" + c.id() + "\n4\n7\n0\n");

    CHECK(c.atividade()->isConcluida());
    CHECK(c.atividade()->getNotaObtida() == doctest::Approx(7.0f));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [positivo] submenu mostra Pendente e depois a nota")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "3\n1\n" + c.id() + "\n4\n7\n0\n");

    CHECK(contem(r.saida, "Lancar / Alterar Nota Obtida (Pendente)"));
    CHECK(contem(r.saida, "Lancar / Alterar Nota Obtida (7"));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [positivo] opcao 5 remove o lancamento de nota")
{
    Cenario c(true);
    c.atividade()->setNotaObtida(8.0f);
    MenuAtividadeAvaliativa menu(c.semestre);

    executar(menu, "3\n1\n" + c.id() + "\n5\n0\n");
    CHECK_FALSE(c.atividade()->isConcluida());
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [negativo] opcao invalida mostra erro")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "3\n1\n" + c.id() + "\n9\n0\n");
    CHECK(contem(r.saida, "[ERRO] Opcao invalida. Escolha entre 0 e 5."));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoEditarAtividade [positivo] permanece no menu")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "3\n1\n" + c.id() + "\n0\n");
    CHECK(r.proximo == &menu);
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoApagarAtividade [limite] disciplina sem atividades mostra aviso")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "4\n1\n");
    CHECK(contem(r.saida, "[AVISO] Esta disciplina nao possui atividades cadastradas."));
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoApagarAtividade [limite] ID 0 cancela sem apagar")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    executar(menu, "4\n1\n0\n");
    CHECK(c.totalAtividades() == 1);
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoApagarAtividade [negativo] atividade inexistente mostra erro")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "4\n1\n999\n");

    CHECK(contem(r.saida, "[ERRO] Atividade com ID 999 nao encontrada."));
    CHECK(c.totalAtividades() == 1);
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoApagarAtividade [positivo] confirmacao 1 apaga a atividade")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "4\n1\n" + c.id() + "\n1\n");

    CHECK(contem(r.saida, "Tem certeza que deseja apagar 'Prova 1'?"));
    CHECK(contem(r.saida, "Atividade apagada com sucesso!"));
    CHECK(c.totalAtividades() == 0);
}

TEST_CASE("MenuAtividadeAvaliativa::fluxoApagarAtividade [positivo] confirmacao 2 cancela a operacao")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "4\n1\n" + c.id() + "\n2\n");

    CHECK(contem(r.saida, "Operacao cancelada."));
    CHECK(c.totalAtividades() == 1);
}