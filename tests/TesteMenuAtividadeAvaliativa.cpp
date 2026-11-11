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
