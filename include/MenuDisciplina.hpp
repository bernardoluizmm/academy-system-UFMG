/**
 * @file MenuDisciplina.hpp
 * @brief Declaração da classe MenuDisciplina para gerenciamento das disciplinas do semestre atual.
 */

#ifndef MENUDISCIPLINA_HPP
#define MENUDISCIPLINA_HPP

#include "Menu.hpp"
#include "SemestreAtual.hpp"

/**
 * @class MenuDisciplina
 * @brief Menu responsável pelas operações de criação, edição, listagem e exclusão de disciplinas.
 * @details Permite ao usuário visualizar as disciplinas matriculadas no semestre atual e
 *          conduz os fluxos interativos de validação de entrada para adicionar novas
 *          disciplinas, alterar atributos cadastrais ou remover registros existentes.
 */
class MenuDisciplina : public Menu 
{
private:

    SemestreAtual& _semestreAtual; ///< Semestre em andamento cujas disciplinas sao gerenciadas.

     /**
     * @brief Fluxo de criacao de disciplina.
     *
     * Pede nome, codigo, turma, professor, sala/bloco, carga horaria, tipo, horario/dias e
     * duracao da aula. Cada dado e lido e validado em um laco de repeticao ate ser aceito;
     * ao final, a disciplina e adicionada ao semestre atual.
     */
    void fluxoCriarDisciplina();

    /**
     * @brief Fluxo de edicao de disciplina.
     *
     * Pede o ID da disciplina (0 cancela) e abre um submenu para alterar qualquer um dos
     * seus campos. Erros de validacao sao exibidos e o valor anterior e mantido.
     */
    void fluxoEditarDisciplina();

    /**
     * @brief Fluxo de exclusao de disciplina.
     *
     * Pede o ID da disciplina (0 cancela) e uma confirmacao (1 - Sim / 2 - Nao) antes de remove-la.
     */
    void fluxoApagarDisciplina();

    /**
     * @brief Exibe as opcoes de tipo de disciplina e le a escolha do usuario.
     *
     * A leitura se repete ate o usuario digitar uma opcao valida (1 a 3).
     *
     * @return "Obrigatoria", "Optativa" ou "Formacao Livre".
     */
    std::string escolherTipoDisciplina();

public:
    /**
     * @brief Construtor da classe MenuDisciplina.
     * @param semestreAtual Referencia para o objeto SemestreAtual em memoria.
     */
    MenuDisciplina(SemestreAtual& semestreAtual);

    /**
     * @brief Exibe a tabela resumida das disciplinas do semestre atual e as opções de gerenciamento.
     */
    virtual void exibir() override;

    /**
     * @brief Processa a opção escolhida pelo usuário e aciona o fluxo correspondente.
     * @return Ponteiro para uma nova instância de `MenuDisciplina` após operações de
     *         criação/edição/exclusão, ou para `MenuPrincipal` quando o usuário escolhe voltar (opção 0).
     */
    virtual Menu* processarEntrada() override;
};

#endif