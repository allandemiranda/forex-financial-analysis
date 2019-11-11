/**
 * @file MovingAverage.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos para classe MovingAverage
 * @version 0.1
 * @date 09-11-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "MovingAverage.hpp"
#include <algorithm>

/**
 * @brief Construa um novo objeto Moving Average:: Moving Average
 *
 * @param NovoNumeroDePeriodo Núemro de periodos da média móvel
 * @param grafico Gráfico
 */
MovingAverage::MovingAverage(unsigned long NovoNumeroDePeriodo,
                             Chart* grafico) {
#pragma omp parallel sections
  {
#pragma omp section
    { setGrafico(grafico); }
#pragma omp section
    { setNumPeriodo(&NovoNumeroDePeriodo); }
  }
}

/**
 * @brief Destrua o objeto Moving Average:: Moving Average
 *
 */
MovingAverage::~MovingAverage(void) {}

/**
 * @brief Defina o objeto Num Periodo
 *
 * @param long Número de periodos da média móvel
 */
void MovingAverage::setNumPeriodo(unsigned long* numeroPeriodo) {
  numeroDePeriodo = *numeroPeriodo;
}

/**
 * @brief Defina o objeto Num Periodo
 *
 * @return unsigned* getNumPeriodo Número de periodos configurados
 */
unsigned long* MovingAverage::getNumPeriodo(void) { return &numeroDePeriodo; }

/**
 * @brief Defina o objeto Grafico
 *
 * @param novoGrafico Grafico a ser analisado e criado linha
 */
void MovingAverage::setGrafico(Chart* novoGrafico) { grafico = novoGrafico; }

/**
 * @brief Obter o objeto Grafico
 *
 * @return Chart* Gráfico
 */
Chart* MovingAverage::getGrafico(void) { return grafico; }

/**
 * @brief Defina o objeto SMA
 *
 * @param vela Vela a ser analisada
 * @return PointLine
 */
PointLine MovingAverage::getSMA(Candlestick* vela) {
  price_t valor = 0.0;
  time_t tempo = *vela->getDate();
  for (int i = 0; i < (int)*getNumPeriodo(); ++i) {
    if (*vela->getStatus()) {
      valor += *vela->getClose();
      std::prev(vela, 1);
    } else {
      --i;
    }
    if(vela == &getGrafico()->chart.at(1)){
      break;
    }
  }
  valor = (valor / (*getNumPeriodo()));
  return PointLine(&tempo, &valor);
}

/**
 * @brief SMA
 *
 * @return Line Linha SMA
 */
Line MovingAverage::SMA(void) {
  std::string nomeLinha = "SMA ";
  nomeLinha += std::to_string(*getNumPeriodo());
  Line novaLinha(nomeLinha);
#pragma omp parallel
  {
#pragma omp for
    for (unsigned long i = *getNumPeriodo(); i < getGrafico()->chart.size();
         ++i) {
#pragma omp critical
      { novaLinha.linha.push_back(getSMA(&getGrafico()->chart.at(i))); }
    }
  }
  std::sort(novaLinha.linha.begin(), novaLinha.linha.end());
  return novaLinha;
}