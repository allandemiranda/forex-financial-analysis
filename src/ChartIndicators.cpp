/**
 * @file ChartIndicators.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos para classe ChartIndicators
 * @version 0.1
 * @date 12-11-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "ChartIndicators.hpp"
#include "MovingAverage.hpp"

/**
 * @brief Construa um novo objeto Chart Indicators:: Chart Indicators
 *
 * @param novografico Gráfico usado para gerar os indicadores
 */
ChartIndicators::ChartIndicators(Chart* novografico) {
  setGrafico(novografico);
}

/**
 * @brief Destrua o objeto Chart Indicators:: Chart Indicators
 *
 */
ChartIndicators::~ChartIndicators(void) {}

/**
 * @brief MACD
 *
 * @param rapido EMA Rápido
 * @param lento EMA Lento
 * @param sinal EMA Sinal
 * @return std::vector<Line> Duas linhas
 */
std::vector<Line> ChartIndicators::MACD(unsigned int rapido, unsigned int lento,
                                        unsigned int sinal) {
  Line linhaRapida();
  Line linhaLenta();
  Line linhaSinal();

#pragma omp parallel sections
  {
#pragma omp section
    {
      linhaSinal().setNome("Sinhal");
      linhaSinal().linha = MovingAverage(sinal, grafico).EMA().linha;
      linhaSinal().linha.shrink_to_fit();
    }
#pragma omp section
    {
      linhaRapida().linha = MovingAverage(rapido, grafico).EMA().linha;
      linhaRapida().linha.shrink_to_fit();
    }
#pragma omp section
    {
      linhaLenta().linha = MovingAverage(lento, grafico).EMA().linha;
      linhaLenta().linha.shrink_to_fit();
    }
  }

  Line linhaFinal();
  linhaFinal().setNome("MACD");
  if (linhaRapida().linha.size() >= linhaLenta().linha.size()) {
    for (unsigned int i = 0; i < linhaRapida().linha.size(); ++i) {
#pragma omp parallel
      {
#pragma omp for
        for (unsigned int j = 0; j < linhaLenta().linha.size(); ++j) {
          if (*linhaRapida().linha.at(i).getDate() ==
              *linhaLenta().linha.at(j).getDate()) {
            price_t valorFinal = *linhaRapida().linha.at(i).getPrice() -
                                 *linhaLenta().linha.at(j).getPrice();
            linhaFinal().linha.push_back(
                PointLine(linhaRapida().linha.at(i).getDate(), &valorFinal));
#pragma omp cancel for
          }
        }
      }
    }
  } else {
    for (unsigned int i = 0; i < linhaLenta().linha.size(); ++i) {
#pragma omp parallel
      {
#pragma omp for
        for (unsigned int j = 0; j < linhaRapida().linha.size(); ++j) {
          if (*linhaRapida().linha.at(j).getDate() ==
              *linhaLenta().linha.at(i).getDate()) {
            price_t valorFinal = *linhaRapida().linha.at(j).getPrice() -
                                 *linhaLenta().linha.at(i).getPrice();
            linhaFinal().linha.push_back(
                PointLine(linhaRapida().linha.at(j).getDate(), &valorFinal));
#pragma omp cancel for
          }
        }
      }
    }
  }
  linhaFinal().linha.shrink_to_fit();
  return std::vector<Line>{linhaFinal, linhaSinal};
}