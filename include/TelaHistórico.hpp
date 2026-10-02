/**
 * @file TelaHistorico.hpp
 * @brief Declaração da tela de gerenciamento do histórico de semestres.
 * @author SamuelFacco
 */
 
#ifndef TELAHISTORICO_HPP
#define TELAHISTORICO_HPP
 
#include "Tela.hpp"
 
/**
 * @class TelaHistorico
 * @brief Tela para gerenciar os semestres consolidados do estudante.
 *
 * Permite ver detalhes, adicionar um semestre, corrigir o NSG e remover
 * semestres do histórico, por meio de um sub-menu. Os dados ficam no
 * Curso do Estudante (lista de SemestreConsolidado).
 */
class TelaHistorico : public Tela {
public:
    /**
     * @brief Constrói a tela de histórico.
     * @param estudante Referência ao estudante manipulado.
     */
    explicit TelaHistorico(Estudante& estudante);
 
    /**
     * @brief Executa o sub-menu do histórico.
     *
     * Opções: ver detalhes / adicionar semestre / editar NSG / remover / voltar.
     *
     * @return @c true quando o usuário escolhe voltar ao menu principal.
     */
    bool executar() override;
 
    /**
     * @brief Retorna o nome identificador da tela.
     * @return A string "Histórico".
     */
    std::string getNome() const override;
 
private:
    /**
     * @brief Lista todos os semestres consolidados, com período e NSG.
     */
    void listarSemestres();
 
    /**
     * @brief Exibe as disciplinas e notas de um semestre consolidado.
     * @param indice Índice (base 0) do semestre na lista do curso.
     */
    void verDetalhes(int indice);
 
    /**
     * @brief Lê período e NSG e cria um novo SemestreConsolidado no curso.
     */
    void adicionar();
 
    /**
     * @brief Permite corrigir o NSG de um semestre existente.
     * @param indice Índice (base 0) do semestre na lista do curso.
     */
    void editarNSG(int indice);
 
    /**
     * @brief Remove um semestre consolidado após confirmação do usuário.
     * @param indice Índice (base 0) do semestre na lista do curso.
     */
    void remover(int indice);
};
 
#endif
 