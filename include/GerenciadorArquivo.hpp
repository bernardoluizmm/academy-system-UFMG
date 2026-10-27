#ifndef GERENCIADORARQUIVO_HPP
#define GERENCIADORARQUIVO_HPP

#include <string>
#include <vector>
#include "Estudante.hpp"

class GerenciadorArquivo 
{
private:
    std::string _nomeArquivo;

    static std::vector<std::string> dividirLinha(const std::string& linha, char delimitador);

public:
    GerenciadorArquivo(const std::string& nomeArquivo = "perfil_estudante.txt");

    bool arquivoExiste() const;
    void salvar(const Estudante& estudante) const;
    Estudante carregar() const;
    std::string getNomeArquivo() const;
};

#endif