#ifndef MENUCARREGARUSUARIO_HPP
#define MENUCARREGARUSUARIO_HPP

#include <memory>
#include "Menu.hpp"
#include "Estudante.hpp"
#include "GerenciadorArquivo.hpp"

/**
 * @file MenuCarregarUsuario.hpp
 * @brief Declaracao da tela de carregamento de um perfil de estudante ja salvo.
 */

/**
 * @class MenuCarregarUsuario
 * @brief Tela que carrega o perfil do estudante a partir do arquivo de perfil em um std::unique_ptr.
 */
class MenuCarregarUsuario : public Menu 
{
private:
    std::unique_ptr<Estudante>& _estudante;  ///< Ponteiro inteligente que recebera o estudante carregado.
    GerenciadorArquivo& _gerenciadorArquivo; ///< Gerenciador usado para ler o perfil.

public:
    MenuCarregarUsuario(std::unique_ptr<Estudante>& estudante, GerenciadorArquivo& gerenciadorArquivo);

    virtual void exibir() override;
    virtual Menu* processarEntrada() override;
    virtual bool substituirPilhaAoTransicionar() const override;
};

#endif