#include "doctest.h"
#include "MenuAtividadeAvaliativa.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace
{
    struct Resultado
    {
        std::string saida;
        Menu* proximo;
    };

    
    struct RedirecionadorDeTerminal
    {
        std::streambuf* bufferEntrada;
        std::streambuf* bufferSaida;
        std::ios::fmtflags formato;
        std::streamsize precisao;

        RedirecionadorDeTerminal(std::istringstream& entrada, std::ostringstream& saida)
            : bufferEntrada(std::cin.rdbuf(entrada.rdbuf())),
              bufferSaida(std::cout.rdbuf(saida.rdbuf())),
              formato(std::cout.flags()),
              precisao(std::cout.precision())
        {
        }

        ~RedirecionadorDeTerminal()
        {
            std::cin.rdbuf(bufferEntrada);
            std::cout.rdbuf(bufferSaida);
            std::cout.flags(formato);
            std::cout.precision(precisao);
            std::cin.clear();
        }
    };
Resultado executar(Menu& menu, const std::string& entrada)
    {
        std::istringstream entradaFalsa(entrada);
        std::ostringstream saidaFalsa;
        Resultado resultado;
        resultado.proximo = nullptr;
        {
            RedirecionadorDeTerminal redirecionador(entradaFalsa, saidaFalsa);
            resultado.proximo = menu.processarEntrada();
        }
        resultado.saida = saidaFalsa.str();
        return resultado;
    }

    std::string exibirMenu(Menu& menu)
    {
        std::istringstream entradaFalsa("");
        std::ostringstream saidaFalsa;
        {
            RedirecionadorDeTerminal redirecionador(entradaFalsa, saidaFalsa);
            menu.exibir();
        }
        return saidaFalsa.str();
    }

    bool contem(const std::string& texto, const std::string& trecho)
    {
        return texto.find(trecho) != std::string::npos;
    }
     struct Cenario
    {
        SemestreAtual semestre;

        explicit Cenario(bool comAtividade = false)
            : semestre("2026/01")
        {
            semestre.adicionarDisciplina("COD001", "T1", "Programacao", "Prof. Ana", "Sala 101",
                                         60, 50, "Obrigatoria", "Seg 10h");
            if (comAtividade)
            {
                disciplina()->avaliacoes().adicionarAtividade(1, "Prova 1", "15/03", 10.0f, 0.0f, false);
            }
        }

        Disciplina* disciplina()
        {
            return semestre.buscarDisciplina(1);
        }

        AtividadeAvaliativa* atividade()
        {
            return disciplina()->avaliacoes().buscarAtividade(1);
        }

        int totalAtividades()
        {
            return static_cast<int>(disciplina()->avaliacoes().getAtividades().size());
        }
    };
}
TEST_CASE("MenuAtividadeAvaliativa - constroi com um semestre")
{
    SemestreAtual semestre("2026/01");
    CHECK_NOTHROW(MenuAtividadeAvaliativa menu(semestre));
}
TEST_CASE("MenuAtividadeAvaliativa - exibir mostra titulo e opcoes")
{
    SemestreAtual semestre("2026/01");
    MenuAtividadeAvaliativa menu(semestre);
    std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "GERENCIAMENTO DE ATIVIDADES AVALIATIVAS"));
    CHECK(contem(saida, "1 - Criar nova atividade avaliativa"));
    CHECK(contem(saida, "2 - Lancar / Atualizar nota obtida em atividade"));
    CHECK(contem(saida, "3 - Editar atividade avaliativa existente"));
    CHECK(contem(saida, "4 - Apagar atividade avaliativa existente"));
    CHECK(contem(saida, "0 - Voltar ao Menu Principal"));
}
TEST_CASE("MenuAtividadeAvaliativa - exibir com semestre vazio mostra aviso")
{
    SemestreAtual semestre("2026/01");
    MenuAtividadeAvaliativa menu(semestre);

    CHECK(contem(exibirMenu(menu), "Nenhuma disciplina cadastrada no semestre atual."));
}
TEST_CASE("MenuAtividadeAvaliativa - exibir disciplina sem atividades mostra aviso")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);
    std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "Disciplina [1] COD001 - Programacao"));
    CHECK(contem(saida, "(Nenhuma atividade avaliativa cadastrada)"));
}
TEST_CASE("MenuAtividadeAvaliativa - exibir atividade pendente aparece na tabela")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);
    std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "Nota Obtida"));
    CHECK(contem(saida, "Prova 1"));
    CHECK(contem(saida, "15/03"));
    CHECK(contem(saida, "10.00"));
    CHECK(contem(saida, "Pendente"));
}
TEST_CASE("MenuAtividadeAvaliativa - exibir atividade concluida mostra a nota")
{
    Cenario c(true);
    c.atividade()->setNotaObtida(7.5f);
    MenuAtividadeAvaliativa menu(c.semestre);
    std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "7.50"));
    CHECK_FALSE(contem(saida, "Pendente"));
}
TEST_CASE("MenuAtividadeAvaliativa - opcao 0 encerra o menu")
{
    SemestreAtual semestre("2026/01");
    MenuAtividadeAvaliativa menu(semestre);

    Resultado r = executar(menu, "0\n");
    CHECK(r.proximo == nullptr);
}
TEST_CASE("MenuAtividadeAvaliativa - opcao invalida mostra erro e pede nova entrada")
{
    SemestreAtual semestre("2026/01");
    MenuAtividadeAvaliativa menu(semestre);

    Resultado r = executar(menu, "9\n0\n");

    CHECK(contem(r.saida, "[ERRO] Opcao invalida. Escolha entre 0 e 4."));
    CHECK(r.proximo == nullptr);
}
TEST_CASE("MenuAtividadeAvaliativa - selecionar disciplina com semestre vazio mostra aviso")
{
    SemestreAtual semestre("2026/01");
    MenuAtividadeAvaliativa menu(semestre);

    Resultado r = executar(menu, "1\n");
    CHECK(contem(r.saida, "[AVISO] Cadastre pelo menos uma disciplina antes de gerenciar atividades."));
}
TEST_CASE("MenuAtividadeAvaliativa - selecionar disciplina lista as disciplinas")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n0\n");

    CHECK(contem(r.saida, "Disciplinas do semestre atual:"));
    CHECK(contem(r.saida, "[1] COD001 - Programacao"));
}
TEST_CASE("MenuAtividadeAvaliativa - selecionar disciplina com ID 0 cancela sem erro")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n0\n");

    CHECK_FALSE(contem(r.saida, "[ERRO]"));
    CHECK(c.totalAtividades() == 0);
}
TEST_CASE("MenuAtividadeAvaliativa - selecionar disciplina inexistente mostra erro")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n99\n");
    CHECK(contem(r.saida, "[ERRO] Disciplina com ID 99 nao encontrada."));
}
TEST_CASE("MenuAtividadeAvaliativa - criar atividade com dados validos")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n1\nProva 1\n15/03\n10\n");

    REQUIRE(c.totalAtividades() == 1);
    CHECK(r.proximo == &menu);
    CHECK(contem(r.saida, "Atividade 'Prova 1' adicionada com sucesso!"));

    const AtividadeAvaliativa& a = c.disciplina()->avaliacoes().getAtividades()[0];
    CHECK(a.getNome() == "Prova 1");
    CHECK(a.getData().getDataValidada() == "15/03");
    CHECK(a.getValorMaximo() == doctest::Approx(10.0f));
    CHECK_FALSE(a.isConcluida());
}
TEST_CASE("MenuAtividadeAvaliativa - criar atividade pede de novo um nome invalido")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);
    std::string nomeLongo(200, 'N');

    Resultado r = executar(menu, "1\n1\n" + nomeLongo + "\nProva 1\n15/03\n10\n");

    CHECK(contem(r.saida, "[ERRO]"));
    REQUIRE(c.totalAtividades() == 1);
    CHECK(c.disciplina()->avaliacoes().getAtividades()[0].getNome() == "Prova 1");
}
TEST_CASE("MenuAtividadeAvaliativa - criar atividade pede de novo uma data invalida")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n1\nProva 1\n32/13\n15/03\n10\n");

    CHECK(contem(r.saida, "[ERRO]"));
    REQUIRE(c.totalAtividades() == 1);
    CHECK(c.disciplina()->avaliacoes().getAtividades()[0].getData().getDataValidada() == "15/03");
}
TEST_CASE("MenuAtividadeAvaliativa - criar atividade pede de novo um valor invalido")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "1\n1\nProva 1\n15/03\n-5\n10\n");

    CHECK(contem(r.saida, "[ERRO]"));
    REQUIRE(c.totalAtividades() == 1);
    CHECK(c.disciplina()->avaliacoes().getAtividades()[0].getValorMaximo() == doctest::Approx(10.0f));
}
TEST_CASE("MenuAtividadeAvaliativa - lancar nota em disciplina sem atividades mostra aviso")
{
    Cenario c;
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "2\n1\n");
    CHECK(contem(r.saida, "[AVISO] Esta disciplina nao possui atividades cadastradas."));
}
TEST_CASE("MenuAtividadeAvaliativa - lancar nota com ID 0 cancela")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    executar(menu, "2\n1\n0\n");
    CHECK_FALSE(c.atividade()->isConcluida());
}
TEST_CASE("MenuAtividadeAvaliativa - lancar nota em atividade inexistente mostra erro")
{
    Cenario c(true);
    MenuAtividadeAvaliativa menu(c.semestre);

    Resultado r = executar(menu, "2\n1\n999\n");
    CHECK(contem(r.saida, "[ERRO] Atividade com ID 999 nao encontrada."));
}