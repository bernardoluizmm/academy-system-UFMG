#include "MenuAtividadeAvaliativa.hpp"
#include "SemestreAtual.hpp"
#include "AtividadeAvaliativa.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdexcept>

MenuAtividadeAvaliativa::MenuAtividadeAvaliativa(SemestreAtual& semestreAtual)
    : Menu(), _semestreAtual(semestreAtual) {}

void MenuAtividadeAvaliativa::exibir() 
{
    std::cout << "\n========================================================================\n";
    std::cout << "                 GERENCIAMENTO DE ATIVIDADES AVALIATIVAS                \n";
    std::cout << "========================================================================\n";

    if (this->_semestreAtual.getDisciplinas().empty()) 
    {
        std::cout << " Nenhuma disciplina cadastrada no semestre atual.\n";
    } else 
    {
        const std::vector<Disciplina>& disciplinas = this->_semestreAtual.getDisciplinas();
        for (std::vector<Disciplina>::const_iterator it = disciplinas.begin(); it != disciplinas.end(); ++it) 
        {
            this->exibirAtividadesDaDisciplina(*it);
        }
    }

    std::cout << "\n========================================================================\n";
    std::cout << "1 - Criar nova atividade avaliativa\n";
    std::cout << "2 - Lancar / Atualizar nota obtida em atividade\n";
    std::cout << "3 - Editar atividade avaliativa existente\n";
    std::cout << "4 - Apagar atividade avaliativa existente\n";
    std::cout << "0 - Voltar ao Menu Principal\n";
    std::cout << "========================================================================\n";
}

Menu* MenuAtividadeAvaliativa::processarEntrada() 
{
    while (true) 
    {
        int opcao = this->entradaSanitizada<int>("Escolha uma opcao: ");
        if (opcao == 1) 
        {
            this->fluxoCriarAtividade();
            return this;
        } else if (opcao == 2) 
        {
            this->fluxoLancarNota();
            return this;
        } else if (opcao == 3) 
        {
            this->fluxoEditarAtividade();
            return this;
        } else if (opcao == 4) 
        {
            this->fluxoApagarAtividade();
            return this;
        } else if (opcao == 0) 
        {
            return nullptr;
        }
        std::cout << "[ERRO] Opcao invalida. Escolha entre 0 e 4.\n";
    }
}

Disciplina* MenuAtividadeAvaliativa::selecionarDisciplina() 
{
      if (this->_semestreAtual.getDisciplinas().empty()) 
    {
        std::cout << "[AVISO] Cadastre pelo menos uma disciplina antes de gerenciar atividades.\n";
        return nullptr;
    }

    std::cout << "\nDisciplinas do semestre atual:\n";
    const std::vector<Disciplina>& disciplinas = this->_semestreAtual.getDisciplinas();
    for (std::vector<Disciplina>::const_iterator it = disciplinas.begin(); it != disciplinas.end(); ++it) 
    {
        std::cout << "  [" << it->getId() << "] " << it->getCodigo() << " - " << it->getNome() << "\n";
    }

    int idDisc = this->entradaSanitizada<int>("Selecione o ID da disciplina (0 para cancelar): ");
    if (idDisc == 0) 
    {
        return nullptr;
    }

    Disciplina* disc = this->_semestreAtual.buscarDisciplina(idDisc);
    if (disc == nullptr) 
    {
        std::cout << "[ERRO] Disciplina com ID " << idDisc << " nao encontrada.\n";
    }
    return disc;
}

void MenuAtividadeAvaliativa::exibirAtividadesDaDisciplina(const Disciplina& disciplina) const 
{
    std::cout << "\nDisciplina [" << disciplina.getId() << "] "
              << disciplina.getCodigo() << " - " << disciplina.getNome() << "\n";
    std::cout << "------------------------------------------------------------------------\n";

    const std::vector<AtividadeAvaliativa>& atividades = disciplina.avaliacoes().getAtividades();
    if (atividades.empty()) 
    {
        std::cout << "  (Nenhuma atividade avaliativa cadastrada)\n";
        return;
    }

    std::cout << std::left
              << std::setw(4)  << "ID"
              << std::setw(26) << "Nome"
              << std::setw(8)  << "Data"
              << std::setw(10) << "Valor"
              << std::setw(14) << "Nota Obtida"
              << std::setw(10) << "Conceito"
              << std::setw(8)  << "Media" << "\n";

    std::cout << std::fixed << std::setprecision(2);
    for (std::vector<AtividadeAvaliativa>::const_iterator it = atividades.begin(); it != atividades.end(); ++it) 
    {
        std::ostringstream notaStr;
        notaStr << std::fixed << std::setprecision(2);
        if (it->isConcluida()) 
        {
            notaStr << it->getNotaObtida();
        } else 
        {
            notaStr << "Pendente";
        }

        std::cout << std::left
                  << std::setw(4)  << it->getId()
                  << std::setw(26) << it->getNome().substr(0, 24)
                  << std::setw(8)  << it->getData().getDataValidada()
                  << std::setw(10) << it->getValorMaximo()
                  << std::setw(14) << notaStr.str()
                  << std::setw(10) << it->obterConceito()
                  << std::setw(8)  << it->obterMedia() << "\n";
    }
}
void MenuAtividadeAvaliativa::fluxoCriarAtividade() 
{
    Disciplina* disc = this->selecionarDisciplina();
    if (disc == nullptr) 
    {
        return;
    }

    std::cout << "\n--- NOVA ATIVIDADE EM: " << disc->getNome() << " ---\n";
    std::string nome;
    std::string dataStr;
    float valor = 0.0f;

    while (true) 
    {
        try 
        {
            nome = this->entradaSanitizada<std::string>("Nome da atividade avaliativa: ");
            AtividadeAvaliativa::validarNome(nome);
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
            std::string entradaData = this->entradaSanitizada<std::string>("Data da atividade (formato DD/MM): ");
            Data dataValidada(entradaData);
            dataStr = dataValidada.getDataValidada();
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
            valor = this->entradaSanitizada<float>("Valor da atividade (pontos): ");
            AtividadeAvaliativa::validarValorMaximo(valor);
            break;
        } catch (const std::invalid_argument& e) 
        {
            std::cout << "[ERRO] " << e.what() << "\n";
        }
    }

    disc->avaliacoes().adicionarAtividade(nome, dataStr, valor);
    std::cout << "Atividade '" << nome << "' adicionada com sucesso!\n";
}
void MenuAtividadeAvaliativa::fluxoLancarNota() 
{
    Disciplina* disc = this->selecionarDisciplina();
    if (disc == nullptr) 
    {
        return;
    }

    if (disc->avaliacoes().getAtividades().empty()) 
    {
        std::cout << "[AVISO] Esta disciplina nao possui atividades cadastradas.\n";
        return;
    }

    this->exibirAtividadesDaDisciplina(*disc);
    int idAtiv = this->entradaSanitizada<int>("Informe o ID da atividade para lancar a nota (0 para cancelar): ");
    if (idAtiv == 0) 
    {
        return;
    }

    AtividadeAvaliativa* ativ = disc->avaliacoes().buscarAtividade(idAtiv);
    if (ativ == nullptr) 
    {
        std::cout << "[ERRO] Atividade com ID " << idAtiv << " nao encontrada.\n";
        return;
    }

    while (true) 
    {
        try 
        {
            std::cout << "Atividade: " << ativ->getNome()
                      << " | Valor Maximo: " << std::fixed << std::setprecision(2) << ativ->getValorMaximo() << "\n";
            float nota = this->entradaSanitizada<float>("Digite a nota obtida: ");
            ativ->setNotaObtida(nota);
            std::cout << "Nota lancada com sucesso! Conceito: " << ativ->obterConceito() << "\n";
            break;
        } catch (const std::invalid_argument& e) 
        {
            std::cout << "[ERRO] " << e.what() << "\n";
        }
    }
}

void MenuAtividadeAvaliativa::fluxoEditarAtividade() 
{
    Disciplina* disc = this->selecionarDisciplina();
    if (disc == nullptr) 
    {
        return;
    }

    if (disc->avaliacoes().getAtividades().empty()) 
    {
        std::cout << "[AVISO] Esta disciplina nao possui atividades cadastradas.\n";
        return;
    }

    this->exibirAtividadesDaDisciplina(*disc);
    int idAtiv = this->entradaSanitizada<int>("Informe o ID da atividade que deseja editar (0 para cancelar): ");
    if (idAtiv == 0) 
    {
        return;
    }

    AtividadeAvaliativa* ativ = disc->avaliacoes().buscarAtividade(idAtiv);
    if (ativ == nullptr) 
    {
        std::cout << "[ERRO] Atividade com ID " << idAtiv << " nao encontrada.\n";
        return;
    }

    while (true) 
    {
        std::cout << "\n--- EDITANDO ATIVIDADE [" << ativ->getId() << "] " << ativ->getNome() << " ---\n";
        std::cout << "1 - Nome (" << ativ->getNome() << ")\n";
        std::cout << "2 - Data (" << ativ->getData().getDataValidada() << ")\n";
        std::cout << "3 - Valor (" << std::fixed << std::setprecision(2) << ativ->getValorMaximo() << ")\n";
        std::cout << "4 - Lancar / Alterar Nota Obtida (";
        if (ativ->isConcluida()) 
        {
            std::cout << ativ->getNotaObtida();
        } else 
        {
            std::cout << "Pendente";
        }
        std::cout << ")\n";
        std::cout << "5 - Remover lancamento de nota (marcar como Pendente)\n";
        std::cout << "0 - Concluir edicao\n";

        int op = this->entradaSanitizada<int>("Escolha o campo para editar: ");
        if (op == 0) 
        {
            break;
        }

        try 
        {
            if (op == 1) 
            {
                ativ->setNome(this->entradaSanitizada<std::string>("Novo nome da atividade: "));
            } else if (op == 2) 
            {
                ativ->setData(this->entradaSanitizada<std::string>("Nova data (DD/MM): "));
                disc->avaliacoes().ordenarAtividades();
                ativ = disc->avaliacoes().buscarAtividade(idAtiv);
            } else if (op == 3) 
            {
                ativ->setValorMaximo(this->entradaSanitizada<float>("Novo valor da atividade: "));
            } else if (op == 4) 
            {
                ativ->setNotaObtida(this->entradaSanitizada<float>("Nova nota obtida: "));
            } else if (op == 5) 
            {
                ativ->removerLancamentoNota();
            } else 
            {
                std::cout << "[ERRO] Opcao invalida. Escolha entre 0 e 5.\n";
                continue;
            }
            std::cout << "Atividade atualizada com sucesso!\n";
        } catch (const std::invalid_argument& e) 
        {
            std::cout << "[ERRO] " << e.what() << "\n";
        }
    }
}
void MenuAtividadeAvaliativa::fluxoApagarAtividade() 
{
    Disciplina* disc = this->selecionarDisciplina();
    if (disc == nullptr) 
    {
        return;
    }

    if (disc->avaliacoes().getAtividades().empty()) 
    {
        std::cout << "[AVISO] Esta disciplina nao possui atividades cadastradas.\n";
        return;
    }

    this->exibirAtividadesDaDisciplina(*disc);
    int idAtiv = this->entradaSanitizada<int>("Informe o ID da atividade que deseja apagar (0 para cancelar): ");
    if (idAtiv == 0) 
    {
        return;
    }

    AtividadeAvaliativa* ativ = disc->avaliacoes().buscarAtividade(idAtiv);
    if (ativ == nullptr) 
    {
        std::cout << "[ERRO] Atividade com ID " << idAtiv << " nao encontrada.\n";
        return;
    }

    int confirmacao = this->entradaSanitizada<int>("Tem certeza que deseja apagar '" + ativ->getNome() + "'? (1 - Sim / 2 - Nao): ");
    if (confirmacao == 1) 
    {
        try 
        {
            disc->avaliacoes().removerAtividade(idAtiv);
            std::cout << "Atividade apagada com sucesso!\n";
        } catch (const std::invalid_argument& e) 
        {
            std::cout << "[ERRO] " << e.what() << "\n";
        }
    } else 
    {
        std::cout << "Operacao cancelada.\n";
    }
}

