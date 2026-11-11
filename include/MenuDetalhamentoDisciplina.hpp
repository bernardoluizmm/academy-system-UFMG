/**
 * @file MenuDetalhamentoDisciplina.hpp
 * @brief Declaracao do menu de detalhamento de disciplinas.
 */
#ifndef MENUDETALHAMENTODISCIPLINA_HPP
#define MENUDETALHAMENTODISCIPLINA_HPP

#include "Menu.hpp"
#include "SemestreAtual.hpp"
#include "Disciplina.hpp"

/**
 * @class MenuDetalhamentoDisciplina
 * @brief Menu somente-leitura responsavel por exibir informacoes detalhadas das disciplinas do semestre atual.
 */
class MenuDetalhamentoDisciplina : public Menu
{
private:
    const SemestreAtual& _semestreAtual; ///< Referencia constante ao semestre atual (somente leitura).

    /**
     * @brief Exibe o detalhamento completo de uma disciplina.
     *
     * Mostra os dados cadastrais (codigo, turma, professor, sala, carga horaria, tipo e horario),
     * a tabela de atividades avaliativas e uma linha de totais (valor concluido, nota obtida,
     * conceito e media parciais).
     *
     * @param disciplina Disciplina a ser detalhada.
     */
    void exibirDetalhamentoDisciplina(const Disciplina& disciplina) const;

    /**
     * @brief Pede o ID de uma disciplina e exibe o seu detalhamento.
     *
     * Exibe um aviso se nao houver disciplinas ou se o ID nao existir. O ID 0 cancela a operacao.
     */
    void fluxoDetalharDisciplinaEspecifica();

    /**
     * @brief Exibe o detalhamento de todas as disciplinas do semestre atual.
     *
     * Exibe um aviso se nao houver disciplinas cadastradas.
     */
    void fluxoDetalharTodasDisciplinas() const;

public:
    /**
     * @brief Constroi o menu de detalhamento recebendo apenas referencia constante ao SemestreAtual.
     * @param semestreAtual Semestre atual cujas disciplinas serao consultadas.
     */
    explicit MenuDetalhamentoDisciplina(const SemestreAtual& semestreAtual);

    /**
     * @copydoc Menu::exibir
     */
    virtual void exibir() override;

    /**
     * @brief Le a opcao do usuario e executa o fluxo de detalhamento correspondente.
     * @return @c this apos exibir um detalhamento (permanece na tela);
     *         @c nullptr ao escolher "0 - Voltar" (retorna ao menu anterior).
     */
    virtual Menu* processarEntrada() override;
};

#endif