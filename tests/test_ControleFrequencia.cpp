#include "doctest.h"
#include "ControleFrequencia.hpp"

TEST_CASE("ControleFrequencia - Construtor e Getters (Casos Base)") {
    ControleFrequencia freq(15);

    CHECK(freq.getFaltasPermitidas() == 15);
    CHECK(freq.getFaltasAtuais() == 0);
   
    CHECK(freq.calcularPercentualFrequencia() == doctest::Approx(100.0));
}

TEST_CASE("ControleFrequencia - Incrementar e Decrementar Faltas (Caminho Feliz)") {
    ControleFrequencia freq(10);

    freq.incrementarFalta();
    CHECK(freq.getFaltasAtuais() == 1);
    
    freq.incrementarFalta();
    freq.incrementarFalta();
    CHECK(freq.getFaltasAtuais() == 3);

    freq.decrementarFalta();
    CHECK(freq.getFaltasAtuais() == 2);
}

TEST_CASE("ControleFrequencia - Casos Limite e Invalidos") {
    ControleFrequencia freq(10);

    SUBCASE("Nao deve permitir faltas atuais negativas ao decrementar do zero") {
        freq.decrementarFalta();
        CHECK(freq.getFaltasAtuais() >= 0);
        CHECK(freq.getFaltasAtuais() == 0);
    }

    SUBCASE("Calculo de percentual conforme faltas aumentam") {
        ControleFrequencia f(20);
        // Ex: 20 faltas permitidas equivalem a 25% de um total de 80 horas (ou 100 - (atuais/permitidas)*25, etc.)
        // Em qualquer modelo padrão, com 0 faltas a frequência é 100%
        CHECK(f.calcularPercentualFrequencia() == doctest::Approx(100.0));
        
        f.incrementarFalta();
        CHECK(f.calcularPercentualFrequencia() < 100.0);
    }
}
