#ifndef MENU_HPP
#define MENU_HPP

#include <string>

#include "Estudante.hpp"

/**
 * @file Menu.hpp
 * @brief Declaração do orquestrador do loop principal da aplicação.
 */

/**
 * @class Menu
 * @brief Orquestrador leve que contém o loop principal do sistema.
 *
 * Não herda de Tela. Cria e executa as telas de forma polimórfica,
 * de acordo com a opção escolhida em TelaMenuPrincipal.
 */
class Menu {
public:
    /**
     * @brief Constrói o menu.
     * @param estudante Referência ao estudante (o Menu não é dono do objeto).
     * @param caminhoArquivo Caminho do arquivo .txt de perfil.
     */
    Menu(Estudante& estudante, const std::string& caminhoArquivo);

    /**
     * @brief Executa a aplicação.
     *
     * Fluxo: carrega o perfil (GerenciadorPerfil::carregarPerfil); se
     * necessário, abre TelaPerfil para criá-lo; entra no loop com
     * TelaMenuPrincipal, executa a tela escolhida e, ao sair, salva o
     * perfil (GerenciadorPerfil::salvarPerfil).
     */
    void executar();

private:
    Estudante& estudante_;         ///< Referência ao estudante (não é dona).
    std::string caminhoArquivo_;   ///< Caminho do arquivo de perfil.
};

#endif  // MENU_HPP
