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
 */
LinePrice::LinePrice(std::vector<Candlestick>* chart,
                     unsigned int normalisation) {
  setFirstTrend(chart, &normalisation);
  std::cout << "---" << std::endl;
  setFinal();
}

/**
 * @brief Destrua o objeto Line Price:: Line Price
 *
 */
LinePrice::~LinePrice(void) {}

/**
 * @brief Defina o objeto Final
 *
 */
void LinePrice::setFinal(void) {
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
          last = &firstTrend.at(i);
        }
      }
#pragma omp section
      {
        if ((firstTrend.at(i).trend >= 2) and
            (firstTrend.at(i).trend != last->trend)) {
          Line nova_linha(last->candle->getDate(), last->candle->getClose());
          line.push_back(nova_linha);
          last = &firstTrend.at(i);
        }
      }
    }
  }
  Line nova_linha(last->candle->getDate(), last->candle->getClose());
  line.push_back(nova_linha);
  firstTrend.clear();
  firstTrend.shrink_to_fit();
}

/**
 * @brief Defina o objeto First Trend
 *
 * @param chart Ponteiro para o gráfico criado
 * @param normalisation Ponteiro para número de velas a ser normalizadas
 */
void LinePrice::setFirstTrend(std::vector<Candlestick>* chart,
                              unsigned int* normalisation) {
#pragma omp parallel
  {
#pragma omp for
    for (unsigned long i = 0; i < chart->size(); ++i) {
      if (*chart->at(i).getStatus()) {
        std::vector<bool> lineCompar;
        int normalisation_a = *normalisation;
        for (int j = 1; j <= normalisation_a; ++j) {
          if (((int)i - (j)) < 0) {
            break;
          }
          if (*chart->at(i - j).getStatus()) {
            if (*chart->at(i).getClose() > *chart->at(i - j).getClose()) {
              lineCompar.push_back(true);
            } else {
              if (*chart->at(i).getClose() < *chart->at(i - j).getClose()) {
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
          flagFinal.candle = &chart->at(i);
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
