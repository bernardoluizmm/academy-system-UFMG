#ifndef TELAPERFIL_HPP
#define TELAPERFIL_HPP

#include <string>

#include "Tela.hpp"

/**
 * @file TelaPerfil.hpp
 * @brief Declaração da tela de criação e edição do perfil do estudante.
 */

/**
 * @class TelaPerfil
 * @brief Tela dual: criação do perfil (primeira execução) e edição.
 *
 * Se o perfil do estudante estiver vazio, entra em modo de criação e
 * solicita nome, semestre de ingresso e dados do curso. Caso contrário,
 * entra em modo de edição, com sub-menu para alterar nome, curso e horas
 * exigidas por categoria.
 */
class TelaPerfil : public Tela {
public:
    /**
     * @brief Constrói a tela de perfil.
     * @param estudante Referência ao estudante (a tela não é dona do objeto).
     */
    TelaPerfil(Estudante& estudante);

    /**
     * @brief Executa o fluxo da tela (criação ou edição, conforme o perfil).
     * @return true para voltar ao menu principal.
     */
    bool executar() override;

    /**
     * @brief Retorna o nome identificador da tela.
     * @return "Perfil".
     */
    std::string getNome() const override;
};

#endif  // TELAPERFIL_HPP
