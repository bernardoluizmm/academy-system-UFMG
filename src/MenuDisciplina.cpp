#include "MenuDisciplina.hpp"
#include "Disciplina.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

MenuDisciplina::MenuDisciplina(SemestreAtual& semestreAtual)
    : Menu(), _semestreAtual(semestreAtual) 
{}

std::string MenuDisciplina::escolherTipoDisciplina() 
{
    while (true) 
    {
        std::cout << "Selecione o tipo da disciplina:\n";
        std::cout << "  1 - Obrigatoria\n";
        std::cout << "  2 - Optativa\n";
        std::cout << "  3 - Formacao Livre\n";
        int op = this->entradaSanitizada<int>("Opcao (1 a 3): ");
        if (op == 1) 
        {
            return "Obrigatoria";
        } else if (op == 2) 
        {
            return "Optativa";
        } else if (op == 3) 
        {
            return "Formacao Livre";
        }
        std::cout << "[ERRO] Opcao invalida. Escolha 1, 2 ou 3.\n";
    }
}

void MenuDisciplina::exibir() 
{
    std::cout << "\n========================================================================\n";
    std::cout << "                      GERENCIAMENTO DE DISCIPLINAS                      \n";
    std::cout << "========================================================================\n";

    if (this->_semestreAtual.getDisciplinas().empty()) 
    {
        std::cout << " Nenhuma disciplina cadastrada no semestre atual.\n";
    } else 
    {
        std::cout << std::left
                  << std::setw(4)  << "ID"
                  << std::setw(10) << "Codigo"
                  << std::setw(8)  << "Turma"
                  << std::setw(26) << "Nome"
                  << std::setw(8)  << "CH"
                  << std::setw(16) << "Tipo" << "\n";
        std::cout << "------------------------------------------------------------------------\n";

        const std::vector<Disciplina>& disciplinas = this->_semestreAtual.getDisciplinas();
        for (std::vector<Disciplina>::const_iterator it = disciplinas.begin(); it != disciplinas.end(); ++it) 
        {
            std::cout << std::left
                      << std::setw(4)  << it->getId()
                      << std::setw(10) << it->getCodigo().substr(0, 8)
                      << std::setw(8)  << it->getCodigoTurma().substr(0, 6)
                      << std::setw(26) << it->getNome().substr(0, 24)
                      << std::setw(8)  << (std::to_string(it->getCargaHoraria()) + "h")
                      << std::setw(16) << it->getTipo() << "\n";
        }
    }

    std::cout << "========================================================================\n";
    std::cout << "1 - Criar nova disciplina\n";
    std::cout << "2 - Editar disciplina existente\n";
    std::cout << "3 - Apagar disciplina existente\n";
    std::cout << "0 - Voltar ao Menu Principal\n";
    std::cout << "========================================================================\n";
}

Menu* MenuDisciplina::processarEntrada() 
{
    while (true) 
    {
        int opcao = this->entradaSanitizada<int>("Escolha uma opcao: ");
        if (opcao == 1) 
        {
            this->fluxoCriarDisciplina();
            return this;
        } else if (opcao == 2) 
        {
            this->fluxoEditarDisciplina();
            return this;
        } else if (opcao == 3) 
        {
            this->fluxoApagarDisciplina();
            return this;
        } else if (opcao == 0) 
        {
            return nullptr;
        }
        std::cout << "[ERRO] Opcao invalida. Escolha entre 0 e 3.\n";
    }
}

void MenuDisciplina::fluxoCriarDisciplina() 
{
    std::cout << "\n--- CRIAR NOVA DISCIPLINA ---\n";
    std::string nome;
    std::string codigo;
    std::string codigoTurma;
    std::string professor;
    std::string salaBloco;
    int cargaHoraria = 60;
    std::string tipo;
    std::string horarioDias;
    int duracaoAulaMinutos = 50;

    while (true) 
    {
        try 
        {
            nome = this->entradaSanitizada<std::string>("Nome da disciplina: ");
            Disciplina::validarNome(nome);
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
            codigo = this->entradaSanitizada<std::string>("Codigo da disciplina (ex: DCC204): ");
            Disciplina::validarCodigo(codigo);
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
            codigoTurma = this->entradaSanitizada<std::string>("Codigo da turma (ex: TZ1): ");
            Disciplina::validarCodigoTurma(codigoTurma);
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
            professor = this->entradaSanitizada<std::string>("Nome do professor: ");
            Disciplina::validarProfessor(professor);
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
            salaBloco = this->entradaSanitizada<std::string>("Sala/Bloco da aula (ex: ICEx 2010): ");
            Disciplina::validarSalaBloco(salaBloco);
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
            cargaHoraria = this->entradaSanitizada<int>("Carga horaria total em horas (multiplo de 15, ex: 60): ");
            Disciplina::validarCargaHoraria(cargaHoraria);
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
            tipo = this->escolherTipoDisciplina();
            Disciplina::validarTipo(tipo);
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
            horarioDias = this->entradaSanitizada<std::string>("Horario e dias da semana (ex: Seg/Qua 19:00-20:40): ");
            Disciplina::validarHorarioDias(horarioDias);
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
            duracaoAulaMinutos = this->entradaSanitizada<int>("Duracao de cada aula em minutos (minimo 50, ex: 100): ");
            Disciplina::validarDuracaoAulaMinutos(duracaoAulaMinutos);
            break;
        } catch (const std::invalid_argument& e) 
        {
            std::cout << "[ERRO] " << e.what() << "\n";
        }
    }

    this->_semestreAtual.adicionarDisciplina(codigo,
                                             codigoTurma,
                                             nome,
                                             professor,
                                             salaBloco,
                                             cargaHoraria,
                                             duracaoAulaMinutos,
                                             tipo,
                                             horarioDias);
    std::cout << "Disciplina '" << nome << "' cadastrada com sucesso!\n";
}

void MenuDisciplina::fluxoEditarDisciplina() 
{
    if (this->_semestreAtual.getDisciplinas().empty()) 
    {
        std::cout << "[AVISO] Nao ha disciplinas cadastradas para editar.\n";
        return;
    }

    int idDisc = this->entradaSanitizada<int>("Informe o ID da disciplina que deseja editar (0 para cancelar): ");
    if (idDisc == 0) 
    {
        return;
    }

    Disciplina* disc = this->_semestreAtual.buscarDisciplina(idDisc);
    if (disc == nullptr) 
    {
        std::cout << "[ERRO] Disciplina com ID " << idDisc << " nao encontrada.\n";
        return;
    }

    while (true) 
    {
        std::cout << "\n--- EDITANDO DISCIPLINA [" << disc->getId() << "] " << disc->getNome() << " ---\n";
        std::cout << "1 - Nome (" << disc->getNome() << ")\n";
        std::cout << "2 - Codigo (" << disc->getCodigo() << ")\n";
        std::cout << "3 - Codigo da Turma (" << disc->getCodigoTurma() << ")\n";
        std::cout << "4 - Professor (" << disc->getProfessor() << ")\n";
        std::cout << "5 - Sala/Bloco (" << disc->getSalaBloco() << ")\n";
        std::cout << "6 - Carga Horaria (" << disc->getCargaHoraria() << "h)\n";
        std::cout << "7 - Tipo (" << disc->getTipo() << ")\n";
        std::cout << "8 - Horario e Dias (" << disc->getHorarioDias() << ")\n";
        std::cout << "9 - Duracao da Aula (" << disc->getDuracaoAulaMinutos() << " min)\n";
        std::cout << "0 - Concluir edicao\n";

        int campo = this->entradaSanitizada<int>("Escolha o campo para editar: ");
        if (campo == 0) 
        {
            break;
        }

        try 
        {
            if (campo == 1) 
            {
                disc->setNome(this->entradaSanitizada<std::string>("Novo nome da disciplina: "));
            } else if (campo == 2) 
            {
                disc->setCodigo(this->entradaSanitizada<std::string>("Novo codigo da disciplina: "));
            } else if (campo == 3) 
            {
                disc->setCodigoTurma(this->entradaSanitizada<std::string>("Novo codigo da turma: "));
            } else if (campo == 4) 
            {
                disc->setProfessor(this->entradaSanitizada<std::string>("Novo nome do professor: "));
            } else if (campo == 5) 
            {
                disc->setSalaBloco(this->entradaSanitizada<std::string>("Nova sala/bloco: "));
            } else if (campo == 6) 
            {
                disc->setCargaHoraria(this->entradaSanitizada<int>("Nova carga horaria (multiplo de 15): "));
            } else if (campo == 7) 
            {
                disc->setTipo(this->escolherTipoDisciplina());
            } else if (campo == 8) 
            {
                disc->setHorarioDias(this->entradaSanitizada<std::string>("Novo horario e dias da semana: "));
            } else if (campo == 9) 
            {
                disc->setDuracaoAulaMinutos(this->entradaSanitizada<int>("Nova duracao da aula em minutos (minimo 50): "));
            } else 
            {
                std::cout << "[ERRO] Opcao invalida. Escolha entre 0 e 9.\n";
                continue;
            }
            std::cout << "Campo atualizado com sucesso!\n";
        } catch (const std::invalid_argument& e) 
        {
            std::cout << "[ERRO] " << e.what() << "\n";
        }
    }
}

void MenuDisciplina::fluxoApagarDisciplina() 
{
    if (this->_semestreAtual.getDisciplinas().empty()) 
    {
        std::cout << "[AVISO] Nao ha disciplinas cadastradas para apagar.\n";
        return;
    }

    int idDisc = this->entradaSanitizada<int>("Informe o ID da disciplina que deseja apagar (0 para cancelar): ");
    if (idDisc == 0) 
    {
        return;
    }

    Disciplina* disc = this->_semestreAtual.buscarDisciplina(idDisc);
    if (disc == nullptr) 
    {
        std::cout << "[ERRO] Disciplina com ID " << idDisc << " nao encontrada.\n";
        return;
    }

    int confirmacao = this->entradaSanitizada<int>("Tem certeza que deseja apagar '" + disc->getNome() + "'? (1 - Sim / 2 - Nao): ");
    if (confirmacao == 1) 
    {
        try 
        {
            this->_semestreAtual.removerDisciplina(idDisc);
            std::cout << "Disciplina apagada com sucesso!\n";
        } catch (const std::invalid_argument& e) 
        {
            std::cout << "[ERRO] " << e.what() << "\n";
        }
    } else 
    {
        std::cout << "Operacao cancelada.\n";
    }
}