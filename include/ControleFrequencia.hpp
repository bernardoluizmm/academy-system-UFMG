#ifndef CONTROLE_FREQUENCIA_HPP
#define CONTROLE_FREQUENCIA_HPP

class ControleFrequencia {

 private:
    int _faltas_permitidas; 
    int _faltas_atuais;

 public:
    ControleFrequencia(int faltas_permitidas);
    int getFaltasPermitidas() const;
    int getFaltasAtuais() const;
    void incrementarFalta();
    void decrementarFalta();
    double calcularPercentualFrequencia() const;
}

#endif