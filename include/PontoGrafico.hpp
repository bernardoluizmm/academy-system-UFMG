/**
 * @file PontoGrafico.hpp
 * @brief Estrutura que representa um par de dados (período, NSG) para gráficos.
 */
#ifndef PONTO_GRAFICO_HPP
#define PONTO_GRAFICO_HPP

#include <string>

/**
 * @struct PontoGrafico
 * @brief Armazena os dados de um ponto do gráfico de evolução de desempenho.
 */
struct PontoGrafico {
    std::string periodo; ///< Identificador do período letivo (ex: "2024/1").
    double nsg;          ///< Nota Semestral Global consolidada no período.
};

#endif // PONTO_GRAFICO_HPP