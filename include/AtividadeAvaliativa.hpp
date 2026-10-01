#ifndef ATIVIDADE_AVALIATIVA_HPP
#define ATIVIDADE_AVALIATIVA_HPP
#include <string>

class AtividadeAvaliativa {

 private:
    std::string _nome;
    std::string _data_entrega;
    double _valor_maximo;
    double _nota_obtida;

 public:
    AtividadeAvaliativa(std:: string _nome, std:: string _data_entrega, double valor _valor_maximo);
    std::string getNome() const;
    std::string getDataEntrega() const;
    double getValorMaximo() const; 
    double getNotaObtida() const;
    double calcularAproveitametno() const;
    bool registrarNota(double nota);
}

#endif