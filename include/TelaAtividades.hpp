/**
 * @file TelaAtividades.hpp
 * @brief Declaração da tela de gerenciamento de atividades avaliativas.
 * @author SamuelFacco
 */
 
#ifndef TELAATIVIDADES_HPP
#define TELAATIVIDADES_HPP
 
#include "Tela.hpp"
#include "Disciplina.hpp"
 
/**
 * @class TelaAtividades
 * @brief Tela para gerenciar as atividades avaliativas de uma disciplina.
 *
 * Primeiro o usuário escolhe uma disciplina do semestre atual; depois opera
 * sobre as atividades dela por meio de um sub-menu (adicionar / editar /
 * registrar nota / remover / voltar).
 */
class TelaAtividades : public Tela {
public:
    /**
     * @brief Constrói a tela de atividades.
     * @param estudante Referência ao estudante manipulado.
     */
    explicit TelaAtividades(Estudante& estudante);
 
    /**
     * @brief Executa o fluxo: escolher disciplina e abrir o sub-menu de atividades.
     * @return @c true quando o usuário escolhe voltar ao menu principal.
     */
    bool executar() override;
 
    /**
     * @brief Retorna o nome identificador da tela.
     * @return A string "Atividades".
     */
    std::string getNome() const override;
 
private:
    /**
     * @brief Lista as disciplinas do semestre atual e pede que o usuário escolha uma.
     * @return Índice (base 0) da disciplina escolhida, ou -1 se cancelar
     *         ou se não houver disciplinas.
     */
    int escolherDisciplina();
 
    /**
     * @brief Lê os dados de uma nova atividade e a adiciona à disciplina.
     * @param disc Disciplina que receberá a atividade (modificada).
     */
    void adicionar(Disciplina& disc);
 
    /**
     * @brief Lista as atividades da disciplina e edita a escolhida.
     * @param disc Disciplina cuja atividade será editada (modificada).
     */
    void editar(Disciplina& disc);
 
    /**
     * @brief Lista as atividades e registra a nota na escolhida.
     *
     * A nota é rejeitada (AtividadeAvaliativa::registrarNota retorna @c false)
     * se for negativa ou maior que o valor máximo da atividade.
     *
     * @param disc Disciplina cuja atividade receberá a nota (modificada).
     */
    void registrarNota(Disciplina& disc);
 
    /**
     * @brief Lista as atividades e remove a escolhida.
     * @param disc Disciplina da qual a atividade será removida (modificada).
     */
    void remover(Disciplina& disc);
};
 
#endif
 