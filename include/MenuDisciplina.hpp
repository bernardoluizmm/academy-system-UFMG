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

    SemestreAtual& _semestreAtual;

    /**
     * @brief Conduz o fluxo interativo para cadastrar uma nova disciplina no semestre atual.
     * @details Solicita e valida sequencialmente nome, código, turma, professor, sala/bloco,
     *          carga horária, tipo, dias/horários e duração da aula antes de inserir a disciplina.
     */
    void fluxoCriarDisciplina();

    /**
     * @brief Conduz o fluxo interativo para edição de uma disciplina já cadastrada.
     * @details Permite selecionar uma disciplina pelo seu ID e alterar individualmente
     *          qualquer um de seus campos cadastrais com validação em tempo real.
     */
    void fluxoEditarDisciplina();

    /**
     * @brief Conduz o fluxo interativo para remoção de uma disciplina do semestre atual.
     * @details Solicita o ID da disciplina e exige confirmação explícita do usuário antes
     *          de efetivar a exclusão.
     */
    void fluxoApagarDisciplina();

    /**
     * @brief Exibe um submenu para seleção da natureza curricular da disciplina.
     * @return String correspondente ao tipo escolhido ("Obrigatoria", "Optativa" ou "Formacao Livre").
     */
    std::string escolherTipoDisciplina();

public:
    
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