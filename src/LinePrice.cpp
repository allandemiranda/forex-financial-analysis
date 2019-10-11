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

/**
 * @brief Construa um novo objeto Line Price:: Line Price
 *
 * @param chart Ponteiro para o gráfico criado
 * @param normalisation Número de velas a ser normalizadas
 */
LinePrice::LinePrice(std::vector<Candlestick>* chart,
                     unsigned int normalisation) {}

/**
 * @brief Destrua o objeto Line Price:: Line Price
 *
 */
LinePrice::~LinePrice(void) {}

/**
 * @brief Defina o objeto First Trend
 *
 * @param chart Ponteiro para o gráfico criado
 * @param normalisation Ponteiro para número de velas a ser normalizadas
 */
void LinePrice::setFirstTrend(std::vector<Candlestick>* chart,
                              unsigned int* normalisation) {
  for (unsigned long i = 1; i < chart->size(); ++i) {
    if(chart->at(i).getStatus() ==  false){
      continue;
    }
    for (unsigned int j = 0; j < *normalisation; ++j) {
      if ((i - j) < 0) {
        break;
      }
    }
  }
}
