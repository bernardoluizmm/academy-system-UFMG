#include "MenuCadastroUsuario.hpp"
#include "MenuPrincipal.hpp"
#include "Semestre.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>

MenuCadastroUsuario::MenuCadastroUsuario(std::unique_ptr<Estudante>& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(), _estudante(estudante), _gerenciadorArquivo(gerenciadorArquivo) 
{}

bool MenuCadastroUsuario::substituirPilhaAoTransicionar() const 
{
    return true;
}

void MenuCadastroUsuario::exibir() 
{
    std::cout << "\n======================================================\n";
    std::cout << "             CADASTRO DE NOVO PERFIL                  \n";
    std::cout << "======================================================\n";
    std::cout << "Atencao: Os dados informados nesta etapa sao definitivos.\n";
}

Menu* MenuCadastroUsuario::processarEntrada() 
{
    std::string nomeTemporario;
    int opcaoCurso = Curso::OPCAO_CC;
    std::string semestreIngresso;
    std::string semestreAtualId;
    std::vector<std::string> semestresAnteriores;

    while (true) 
    {
        std::cout << "\n--- Informacoes Pessoais e de Ingresso ---\n";

        while (true) 
        {
            try 
            {
                nomeTemporario = this->entradaSanitizada<std::string>("Digite o nome do estudante: ");
                Estudante::validarNome(nomeTemporario);
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
                std::cout << "\nCursos disponiveis:\n";
                std::cout << "1 - Ciencia da Computacao\n";
                std::cout << "2 - Sistemas de Informacao\n";
                opcaoCurso = this->entradaSanitizada<int>("Selecione o curso (1 ou 2): ");
                Curso::validarOpcaoCurso(opcaoCurso);
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
                Curso::validarSemestreIngresso(semestreIngresso);
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
            break;
        }
    }

    Curso cursoEscolhido(opcaoCurso, semestreIngresso);
    HistoricoEscolar historicoMontado(semestreAtualId);

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
                    historicoMontado.adicionarSemestreConsolidado(semTrancado);
                    break;
                }
                continue;
            }

            float nsgSem = 0.0f;
            int hObrig = 0;
            int hOpt = 0;
            int hLivre = 0;

            while (true) 
            {
                try 
                {
                    nsgSem = this->entradaSanitizada<float>("Informe o NSG do semestre " + idSem + " (0 a 100): ");
                    Semestre::validarNSG(nsgSem);
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
                    hObrig = this->entradaSanitizada<int>("Horas OBRIGATORIAS integralizadas em " + idSem + " (multiplo de 15): ");
                    Semestre::validarHoras(hObrig);
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
                    hOpt = this->entradaSanitizada<int>("Horas OPTATIVAS integralizadas em " + idSem + " (multiplo de 15): ");
                    Semestre::validarHoras(hOpt);
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
                    hLivre = this->entradaSanitizada<int>("Horas de FORMACAO LIVRE integralizadas em " + idSem + " (multiplo de 15): ");
                    Semestre::validarHoras(hLivre);
                    break;
                } catch (const std::invalid_argument& e) 
                {
                    std::cout << "[ERRO] " << e.what() << "\n";
                }
            }

            if (this->confirmarDadoImutavel()) 
            {
                SemestreConsolidado semCons(idSem, nsgSem, hObrig, hOpt, hLivre, false);
                historicoMontado.adicionarSemestreConsolidado(semCons);
                break;
            }
        }
    }

    this->_estudante.reset(new Estudante(nomeTemporario, cursoEscolhido, historicoMontado));
    std::cout << "\nSeja muito bem-vindo " << this->_estudante->getNome() << "!\n";
    return new MenuPrincipal(*(this->_estudante), this->_gerenciadorArquivo);
}