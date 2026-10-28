#ifndef ATIVIDADEAVALIATIVA_HPP
#define ATIVIDADEAVALIATIVA_HPP

#include "Data.hpp"
#include <string>

class AtividadeAvaliativa 
{
private:
    int _id;
    std::string _nome;
    Data _data;
    float _valor;
    float _notaObtida;
    bool _concluida;

public:
    AtividadeAvaliativa(int id, const std::string& nome, const std::string& data, float valorMaximo);
    AtividadeAvaliativa(int id, const std::string& nome, const std::string& data, float valorMaximo, float notaObtida, bool concluida);

    int getId() const;
    std::string getNome() const;
    const Data& getData() const;
    float getValorMaximo() const;
    float getNotaObtida() const;
    bool isConcluida() const;

    void setNome(const std::string& novoNome);
    void setData(const std::string& novaData);
    void setValorMaximo(float novoValor);
    void setNotaObtida(float novaNota);

    void removerLancamentoNota();
    float obterMedia() const;
    char obterConceito() const;

    std::string serializar() const;
};

#endif