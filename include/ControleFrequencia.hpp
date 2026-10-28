#ifndef CONTROLEFREQUENCIA_HPP
#define CONTROLEFREQUENCIA_HPP

class ControleFrequencia 
{
private:
    int _maxFaltas;
    int _faltasAtuais;

public:
    ControleFrequencia(int maxFaltas);

    int getMaxFaltas() const;
    int getFaltasAtuais() const;

    void setMaxFaltas(int novoMaxFaltas);
    void setFaltasAtuais(int novasFaltas);

    void adicionarFalta();
    void removerFalta();
};

#endif