#include "CalculadorConceito.hpp"

char CalculadorConceito::calcular(float notaPercentual) 
{
    if (notaPercentual >= 90.0f) 
    {
        return 'A';
    } else if (notaPercentual >= 80.0f) 
    {
        return 'B';
    } else if (notaPercentual >= 70.0f) 
    {
        return 'C';
    } else if (notaPercentual >= 60.0f) 
    {
        return 'D';
    } else if (notaPercentual >= 40.0f) 
    {
        return 'E';
    }
    return 'F';
}