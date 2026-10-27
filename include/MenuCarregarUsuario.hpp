#ifndef MENUCARREGARUSUARIO_HPP
#define MENUCARREGARUSUARIO_HPP

#include "Menu.hpp"

/**
 * @file MenuCarregarUsuario.hpp
 * @brief Declaração da tela de carregamento de um perfil de estudante já salvo.
 */

/**
 * @class MenuCarregarUsuario
 * @brief Tela que carrega o perfil do estudante a partir do arquivo de perfil.
 *
 * Não pede nenhuma entrada ao usuário: ao processar, lê o arquivo usando o
 * GerenciadorArquivo. Se der certo, segue para o menu principal; se falhar,
 * mostra o erro e volta para o menu inicial.
 */
class MenuCarregarUsuario : public Menu 
{
public:
    /**
     * @brief Constrói a tela de carregamento.
     * @param estudante          Estudante que receberá os dados carregados (deve viver mais que o Menu).
     * @param gerenciadorArquivo Gerenciador usado para ler o perfil (deve viver mais que o Menu).
     */
    MenuCarregarUsuario(Estudante& estudante, GerenciadorArquivo& gerenciadorArquivo);

    /**
     * @brief Destrutor.
     */
    virtual ~MenuCarregarUsuario() override;

    /**
     * @brief Exibe o título da tela de carregamento.
     */
    virtual void exibir() override;

    /**
     * @brief Carrega o perfil do arquivo e decide a próxima tela.
     *
     * Em caso de sucesso, o estudante do menu é substituído pelo carregado e
     * é exibida uma mensagem de boas-vindas. Qualquer exceção do carregamento
     * (por exemplo, arquivo não encontrado) é tratada aqui: a mensagem de erro é
     * exibida e nenhuma exceção é propagada.
     *
     * @return MenuPrincipal se o perfil foi carregado; MenuInicial se houve erro.
     *         O objeto é alocado com new, e quem recebe o ponteiro passa a ser
     *         responsável por liberá-lo.
     */
    virtual Menu* processarEntrada() override;
};

#endif
