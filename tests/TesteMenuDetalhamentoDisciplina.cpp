#include "doctest.h"
#include "MenuDetalhamentoDisciplina.hpp"
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

    void adicionarDisciplina(SemestreAtual& semestre, const std::string& nome = "Programacao")
    {
        semestre.adicionarDisciplina("COD001", "T1", nome, "Prof. Ana", "Sala 101",
                                     60, 50, "Obrigatoria", "Seg 10h");
    }

    void adicionarAtividade(SemestreAtual& semestre, int idDisciplina, int idAtividade, float valor, float nota, bool concluida)
    {
        Disciplina* disciplina = semestre.buscarDisciplina(idDisciplina);
        REQUIRE(disciplina != nullptr);
        disciplina->avaliacoes().adicionarAtividade(idAtividade, "Prova 1", "15/03", valor, nota, concluida);
    }
}

TEST_CASE("MenuDetalhamentoDisciplina - constroi com um semestre")
{
    SemestreAtual semestre("2026/01");
    CHECK_NOTHROW(MenuDetalhamentoDisciplina menu(semestre));
}

TEST_CASE("MenuDetalhamentoDisciplina - exibir com semestre vazio mostra aviso")
{
    SemestreAtual semestre("2026/01");
    MenuDetalhamentoDisciplina menu(semestre);

    CHECK(contem(exibirMenu(menu), "Nenhuma disciplina cadastrada no semestre atual."));
}

TEST_CASE("MenuDetalhamentoDisciplina - exibir mostra titulo e opcoes")
{
    SemestreAtual semestre("2026/01");
    MenuDetalhamentoDisciplina menu(semestre);
    std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "DETALHAMENTO DE DISCIPLINAS E ATIVIDADES AVALIATIVAS"));
    CHECK(contem(saida, "1 - Visualizar detalhamento de uma disciplina especifica"));
    CHECK(contem(saida, "2 - Visualizar detalhamento de todas as disciplinas"));
    CHECK(contem(saida, "0 - Voltar ao Menu Principal"));
}

TEST_CASE("MenuDetalhamentoDisciplina - exibir lista ID, codigo e nome das disciplinas")
{
    SemestreAtual semestre("2026/01");
    adicionarDisciplina(semestre);
    MenuDetalhamentoDisciplina menu(semestre);
    std::string saida = exibirMenu(menu);

    CHECK(contem(saida, "Disciplinas disponiveis no semestre atual:"));
    CHECK(contem(saida, "[1] COD001 - Programacao"));
    CHECK_FALSE(contem(saida, "Nenhuma disciplina cadastrada"));
}

TEST_CASE("MenuDetalhamentoDisciplina - opcao 0 encerra o menu")
{
    SemestreAtual semestre("2026/01");
    MenuDetalhamentoDisciplina menu(semestre);

    Resultado r = executar(menu, "0\n");
    CHECK(r.proximo == nullptr);
}    