#include "MenuAtividadeAvaliativa.hpp"
#include "MenuPrincipal.hpp"
#include "SemestreAtual.hpp"
#include "AtividadeAvaliativa.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdexcept>

MenuAtividadeAvaliativa::MenuAtividadeAvaliativa(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo)
    : Menu(estudante, gerenciadorArquivo) 
{
}

MenuAtividadeAvaliativa::~MenuAtividadeAvaliativa() 
{
}

void MenuAtividadeAvaliativa::exibir() 
{
    const SemestreAtual* semAtual = this->_estudante.getHistorico().getSemestreAtual();

    std::cout << "\n========================================================================\n";
    std::cout << "                 GERENCIAMENTO DE ATIVIDADES AVALIATIVAS                \n";
    std::cout << "========================================================================\n";

    if (semAtual == nullptr || semAtual->getDisciplinas().empty()) 
    {
        std::cout << " Nenhuma disciplina cadastrada no semestre atual.\n";
    } else 
    {
        const std::vector<Disciplina>& disciplinas = semAtual->getDisciplinas();
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
            return new MenuAtividadeAvaliativa(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 2) 
        {
            this->fluxoLancarNota();
            return new MenuAtividadeAvaliativa(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 3) 
        {
            this->fluxoEditarAtividade();
            return new MenuAtividadeAvaliativa(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 4) 
        {
            this->fluxoApagarAtividade();
            return new MenuAtividadeAvaliativa(this->_estudante, this->_gerenciadorArquivo);
        } else if (opcao == 0) 
        {
            return new MenuPrincipal(this->_estudante, this->_gerenciadorArquivo);
        }
        std::cout << "[ERRO] Opcao invalida. Escolha entre 0 e 4.\n";
    }
}
Disciplina* MenuAtividadeAvaliativa::selecionarDisciplina() 
{
    SemestreAtual* semAtual = this->_estudante.getHistoricoEditavel().getSemestreAtual();
    if (semAtual == nullptr || semAtual->getDisciplinas().empty()) 
    {
        std::cout << "[AVISO] Cadastre pelo menos uma disciplina antes de gerenciar atividades.\n";
        return nullptr;
    }

    std::cout << "\nDisciplinas do semestre atual:\n";
    const std::vector<Disciplina>& disciplinas = semAtual->getDisciplinas();
    for (std::vector<Disciplina>::const_iterator it = disciplinas.begin(); it != disciplinas.end(); ++it) 
    {
        std::cout << "  [" << it->getId() << "] " << it->getCodigo() << " - " << it->getNome() << "\n";
    }

    int idDisc = this->entradaSanitizada<int>("Selecione o ID da disciplina (0 para cancelar): ");
    if (idDisc == 0) 
    {
        return nullptr;
    }

    Disciplina* disc = semAtual->buscarDisciplina(idDisc);
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
    AtividadeAvaliativa rascunho(0, "ATIV", "01/01", 1.0f);

    while (true) 
    {
        try 
        {
            rascunho.setNome(this->entradaSanitizada<std::string>("Nome da atividade avaliativa: "));
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
            rascunho.setData(this->entradaSanitizada<std::string>("Data da atividade (formato DD/MM): "));
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
            float valor = this->entradaSanitizada<float>("Valor da atividade (pontos): ");
            rascunho.setValorMaximo(valor);
            break;
        } catch (const std::invalid_argument& e) 
        {
            std::cout << "[ERRO] " << e.what() << "\n";
        }
    }

    disc->avaliacoes().adicionarAtividade(rascunho.getNome(),
                                          rascunho.getData().getDataValidada(),
                                          rascunho.getValorMaximo());
    std::cout << "Atividade '" << rascunho.getNome() << "' adicionada com sucesso!\n";
}
