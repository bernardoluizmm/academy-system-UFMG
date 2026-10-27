#include "MenuCadastroUsuario.hpp"
#include "MenuPrincipal.hpp"
#include "Semestre.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>

MenuCadastroUsuario::MenuCadastroUsuario(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{}

MenuCadastroUsuario::~MenuCadastroUsuario() 
{}
void MenuCadastroUsuario::exibir() 
{
    std::cout << "\n======================================================\n";
    std::cout << "             CADASTRO DE NOVO PERFIL                  \n";
    std::cout << "======================================================\n";
    std::cout << "Atencao: Os dados informados nesta etapa sao definitivos.\n";
}
Menu* MenuCadastroUsuario::processarEntrada() 
{
    Estudante novoEstudante;
    std::vector<std::string> semestresAnteriores;
    std::string semestreIngresso;
    std::string semestreAtualId;

    while (true) 
    {
        std::cout << "\n--- Informacoes Pessoais e de Ingresso ---\n";

        while (true) 
        {
            try 
            {
                std::string nomeInput = this->entradaSanitizada<std::string>("Digite o nome do estudante: ");
                novoEstudante.setNome(nomeInput);
                break;
            } catch (const std::invalid_argument& e) 
            {
                std::cout << "[ERRO] " << e.what() << "\n";
            }
        }

        Curso cursoEscolhido;
        int opcaoCurso = 1;
        while (true) 
        {
            try 
            {
                std::cout << "\nCursos disponiveis:\n";
                std::cout << "1 - Ciencia da Computacao\n";
                std::cout << "2 - Sistemas de Informacao\n";
                opcaoCurso = this->entradaSanitizada<int>("Selecione o curso (1 ou 2): ");
                cursoEscolhido.setOpcaoCurso(opcaoCurso);
                break;
            } catch (const std::invalid_argument& e) 
            {
                std::cout << "[ERRO] " << e.what() << "\n";
            }
        }

        while (true) 
        {
            try 
            {
                semestreIngresso = this->entradaSanitizada<std::string>("Informe o semestre de ingresso (formato AAAA/01 ou AAAA/02): ");
                cursoEscolhido.setSemestreIngresso(semestreIngresso);
                break;
            } catch (const std::invalid_argument& e) 
            {
                std::cout << "[ERRO] " << e.what() << "\n";
            }
        }

        while (true) 
        {
            try 
            {
                semestreAtualId = this->entradaSanitizada<std::string>("Informe o semestre atual (formato AAAA/01 ou AAAA/02): ");
                semestresAnteriores = Semestre::gerarSemestresAnteriores(semestreIngresso, semestreAtualId);
                break;
            } catch (const std::invalid_argument& e) 
            {
                std::cout << "[ERRO] " << e.what() << "\n";
            }
        }

        if (this->confirmarDadoImutavel()) 
        {
            cursoEscolhido.inicializarCurso(opcaoCurso, semestreIngresso);
            novoEstudante.setCurso(cursoEscolhido);
            novoEstudante.getHistoricoEditavel().definirSemestreAtual(semestreAtualId);
            break;
        }
    }

    novoEstudante.getHistoricoEditavel().limparSemestresPassados();

    if (!semestresAnteriores.empty()) 
    {
        std::cout << "\nForam identificados " << semestresAnteriores.size()
                  << " semestre(s) consolidado(s) entre " << semestreIngresso
                  << " e " << semestreAtualId << ".\n";
    }

    for (size_t i = 0; i < semestresAnteriores.size(); ++i) 
    {
        const std::string& idSem = semestresAnteriores[i];

        while (true) 
        {
            std::cout << "\n--- Dados do Semestre Consolidado " << idSem << " ---\n";

            bool trancado = false;
            while (true) 
            {
                int opTrancado = this->entradaSanitizada<int>("O semestre " + idSem + " foi trancado? (1 - Sim / 2 - Nao): ");
                if (opTrancado == 1 || opTrancado == 2) 
                {
                    trancado = (opTrancado == 1);
                    break;
                }
                std::cout << "[ERRO] Escolha 1 para Sim ou 2 para Nao.\n";
            }

            if (trancado) 
            {
                if (this->confirmarDadoImutavel()) 
                {
                    SemestreConsolidado semTrancado(idSem, 0.0f, 0, 0, 0, true);
                    novoEstudante.getHistoricoEditavel().adicionarSemestreConsolidado(semTrancado);
                    break;
                }
                continue;
            }

            SemestreConsolidado semCons(idSem, 0.0f, 0, 0, 0, false);

            while (true) 
            {
                try 
                {
                    float nsgSem = this->entradaSanitizada<float>("Informe o NSG do semestre " + idSem + " (0 a 100): ");
                    semCons.setNSGFixo(nsgSem);
                    break;
                } catch (const std::invalid_argument& e) 
                {
                    std::cout << "[ERRO] " << e.what() << "\n";
                }
            }

            while (true) 
            {
                try 
                {
                    int hObrig = this->entradaSanitizada<int>("Horas OBRIGATORIAS integralizadas em " + idSem + " (multiplo de 15): ");
                    semCons.setHorasObrigatorias(hObrig);
                    break;
                } catch (const std::invalid_argument& e) 
                {
                    std::cout << "[ERRO] " << e.what() << "\n";
                }
            }

            while (true) 
            {
                try 
                {
                    int hOpt = this->entradaSanitizada<int>("Horas OPTATIVAS integralizadas em " + idSem + " (multiplo de 15): ");
                    semCons.setHorasOptativas(hOpt);
                    break;
                } catch (const std::invalid_argument& e) 
                {
                    std::cout << "[ERRO] " << e.what() << "\n";
                }
            }

            while (true) 
            {
                try 
                {
                    int hLivre = this->entradaSanitizada<int>("Horas de FORMACAO LIVRE integralizadas em " + idSem + " (multiplo de 15): ");
                    semCons.setHorasFormacaoLivre(hLivre);
                    break;
                } catch (const std::invalid_argument& e) 
                {
                    std::cout << "[ERRO] " << e.what() << "\n";
                }
            }

            if (this->confirmarDadoImutavel()) 
            {
                novoEstudante.getHistoricoEditavel().adicionarSemestreConsolidado(semCons);
                break;
            }
        }
    }

    this->_estudante = novoEstudante;
    std::cout << "\nSeja muito bem-vindo " << this->_estudante.getNome() << "!\n";
    return new MenuPrincipal(this->_estudante, this->_gerenciadorArquivo);
}