
/**
 * @file TelaDisciplinas.hpp
 * @brief Declaração da tela de gerenciamento de disciplinas.
 * @author SamuelFacco
 */
 
#ifndef TELADISCIPLINAS_HPP
#define TELADISCIPLINAS_HPP
 
#include "Tela.hpp"
 
/**
 * @class TelaDisciplinas
 * @brief Tela que permite cadastrar, editar e remover disciplinas do semestre atual.
 *
 * A própria tela lê os dados digitados pelo usuário,
 * cria os objetos Disciplina e os insere/remove no SemestreAtual do
 * Estudante (acessado por @c estudante_, herdado de Tela).
 *
 * Fluxo: exibe um sub-menu (cadastrar / editar / remover / voltar).
 */
class TelaDisciplinas : public Tela {
public:
    /**
     * @brief Constrói a tela de disciplinas.
     * @param estudante Referência ao estudante manipulado (a tela não é dona dele).
     */
    explicit TelaDisciplinas(Estudante& estudante);
 
    /**
     * @brief Executa o sub-menu de disciplinas.
     * @return @c true quando o usuário escolhe voltar ao menu principal.
     */
    bool executar() override;
 
    /**
     * @brief Retorna o nome identificador da tela.
     * @return A string "Disciplinas".
     */
    std::string getNome() const override;
 
private:
    /**
     * @brief Lê os dados da nova disciplina e a adiciona ao semestre atual.
     *
     * Valida os campos obrigatórios (nome e código) antes de cadastrar.
     * Exibe mensagem de sucesso ou erro ao usuário.
     */
    void cadastrar();
 
    /**
     * @brief Lista as disciplinas numeradas e pede ao usuário que escolha uma.
     * @return Índice (base 0) da disciplina escolhida, ou -1 se o usuário
     *         cancelar ou não houver disciplinas.
     */
    int listarEscolher();
 
    /**
     * @brief Edita os campos de uma disciplina já existente.
     * @param indice Índice da disciplina no vetor do semestre atual.
     */
    void editar(int indice);
 
    /**
     * @brief Lista as disciplinas, pede confirmação e remove a escolhida.
     */
    void remover();
};
 
#endif
 