#include "CalculadorMaxFaltas.hpp"
#include <stdexcept>

int CalculadorMaxFaltas::calcularDiasMaximosFalta(int cargaHorariaHoras, int duracaoAulaMinutos) 
{
    if (cargaHorariaHoras <= 0 || cargaHorariaHoras % 15 != 0 || cargaHorariaHoras >= 180) 
    {
        throw std::invalid_argument("A carga horaria deve ser maior que zero, menor ou igual a 180 e divisivel por 15.");
    }
    if (duracaoAulaMinutos < 50) 
    {
        throw std::invalid_argument("A duracao da aula deve ser de, no minimo, 50 minutos.");
    }
    int limiteHorasAula = cargaHorariaHoras / 4;
    int horasAulaPorEncontro = duracaoAulaMinutos / 50;
    return limiteHorasAula / horasAulaPorEncontro;
}