/**
 * @file LinePrice.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos para a classe LinePrice
 * @version 0.1
 * @date 11-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "LinePrice.hpp"
#include <algorithm>
#include <iostream>

/**
 * @brief Construa um novo objeto Line Price:: Line Price
 *
 * @param chart Ponteiro para o gráfico criado
 * @param normalisation Número de velas a ser normalizadas
 * @param nomeLinha Nome da linha
 */
LinePrice::LinePrice(Chart* chart, unsigned int normalisation,
                     std::string nomeLinha) {
  setFirstTrend(chart, &normalisation);
  setFinal(&nomeLinha);
}

/**
 * @brief Destrua o objeto Line Price:: Line Price
 *
 */
LinePrice::~LinePrice(void) {}

/**
 * @brief Defina o objeto Final
 * 
 * @param nomeLinha nome da linha
 */
void LinePrice::setFinal(std::string* nomeLinha) {
  setNome(*nomeLinha);
  last = &firstTrend.at(0);
  if (last->trend == 2) {
    trend = true;
  } else {
    trend = false;
  }
  for (unsigned long i = 1; i < firstTrend.size(); ++i) {
#pragma omp parallel sections
    {
#pragma omp section
      {
        if ((firstTrend.at(i).trend >= 2) and
            (firstTrend.at(i).trend == last->trend)) {
          if (trend) {
            if (*firstTrend.at(i).candle->getClose() >=
                *last->candle->getClose()) {
              last = &firstTrend.at(i);
            }
          } else {
            if (*firstTrend.at(i).candle->getClose() <=
                *last->candle->getClose()) {
              last = &firstTrend.at(i);
            }
          }
        }
      }
#pragma omp section
      {
        if ((firstTrend.at(i).trend >= 2) and
            (firstTrend.at(i).trend != last->trend)) {
          trend = !trend;
          PointLine novo_ponto(last->candle->getDate(),
                               last->candle->getClose());
          linha.push_back(novo_ponto);
          last = &firstTrend.at(i);
        }
      }
    }
  }
  PointLine novo_ponto(last->candle->getDate(), last->candle->getClose());
  linha.push_back(novo_ponto);
#pragma omp parallel sections
  {
#pragma omp section
    { linha.shrink_to_fit(); }
#pragma omp section
    {
      firstTrend.clear();
      firstTrend.shrink_to_fit();
    }
  }
}

/**
 * @brief Defina o objeto First Trend
 *
 * @param chart Ponteiro para o gráfico criado
 * @param normalisation Ponteiro para número de velas a ser normalizadas
 */
void LinePrice::setFirstTrend(Chart* chart_a, unsigned int* normalisation) {
#pragma omp parallel
  {
#pragma omp for
    for (unsigned long i = 0; i < chart_a->chart.size(); ++i) {
      if (*chart_a->chart.at(i).getStatus()) {
        std::vector<bool> lineCompar;
        int normalisation_a = *normalisation;
        for (int j = 1; j <= normalisation_a; ++j) {
          if (((int)i - (j)) < 0) {
            break;
          }
          if (*chart_a->chart.at(i - j).getStatus()) {
            if (*chart_a->chart.at(i).getClose() >
                *chart_a->chart.at(i - j).getClose()) {
              lineCompar.push_back(true);
            } else {
              if (*chart_a->chart.at(i).getClose() <
                  *chart_a->chart.at(i - j).getClose()) {
                lineCompar.push_back(false);
              } else {
                if (lineCompar.size() != 0) {
                  lineCompar.push_back(lineCompar.back());
                } else {
                  lineCompar.push_back(true);
                }
              }
            }
          } else {
            ++normalisation_a;
          }
        }
        if (lineCompar.size() != 0) {
          lineCompar.shrink_to_fit();
          bool max = true;
          if (lineCompar.end() != std::find(lineCompar.begin(),
                                            lineCompar.end(),
                                            !lineCompar.front())) {
            max = false;
          }
          trendFlag flagFinal;
          flagFinal.candle = &chart_a->chart.at(i);
          if (lineCompar.front() and max) {
            flagFinal.trend = 2;
          } else {
            if (!lineCompar.front() and max) {
              flagFinal.trend = 3;
            } else {
              if (lineCompar.front() and !max) {
                flagFinal.trend = 0;
              } else {
                if (!lineCompar.front() and !max) {
                  flagFinal.trend = 1;
                }
              }
            }
          }
#pragma omp critical
          { firstTrend.push_back(flagFinal); }
        }
      }
    }
  }
  firstTrend.shrink_to_fit();
  std::sort(firstTrend.begin(), firstTrend.end());
  firstTrend.shrink_to_fit();
}
