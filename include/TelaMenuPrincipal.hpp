#ifndef TELAMENUPRINCIPAL_HPP
#define TELAMENUPRINCIPAL_HPP

#include <string>

#include "Tela.hpp"

/**
 * @file TelaMenuPrincipal.hpp
 * @brief Declaração da tela do menu principal do sistema acadêmico.
 */

/**
 * @class TelaMenuPrincipal
 * @brief Tela que exibe o menu principal e armazena a opção escolhida.
 *
 * Não executa as demais telas: apenas guarda a opção selecionada, que é
 * lida pela classe Menu (via getOpcaoEscolhida()) para decidir qual tela
 * criar e executar em seguida.
 */
class TelaMenuPrincipal : public Tela {
public:
    /**
     * @brief Constrói a tela do menu principal.
     * @param estudante Referência ao estudante (a tela não é dona do objeto).
     * @post opcaoEscolhida_ é inicializada com 0 (nenhuma opção).
     */
    TelaMenuPrincipal(Estudante& estudante);

    /**
     * @brief Exibe as opções e armazena a escolha do usuário.
     *
     * Opções: 1-Painel, 2-Perfil, 3-Disciplinas, 4-Atividades,
     * 5-Frequência, 6-Histórico, 7-Sair.
     *
     * @return true para indicar que o fluxo da tela terminou.
     */
    bool executar() override;

    /**
     * @brief Retorna o nome identificador da tela.
     * @return "Menu Principal".
     */
    std::string getNome() const override;

    /**
     * @brief Retorna a opção escolhida pelo usuário.
     * @return Inteiro de 1 a 7 (0 se executar() ainda não foi chamado).
     */
    int getOpcaoEscolhida() const;

private:
    int opcaoEscolhida_;  ///< Opção selecionada pelo usuário (valor inicial 0).
};

#endif  // TELAMENUPRINCIPAL_HPP
