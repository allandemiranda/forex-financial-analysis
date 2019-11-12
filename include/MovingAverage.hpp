/**
 * @file MovingAverage.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe contendo as funções de médias móveis de um gráfico de velas
 * @version 0.1
 * @date 09-11-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef MOVINGAVERAGE_HPP_
#define MOVINGAVERAGE_HPP_

#include "Candlestick.hpp"
#include "Chart.hpp"
#include "Line.hpp"
#include "PointLine.hpp"

class MovingAverage {
 private:
  long numeroDePeriodo;
  Chart* grafico;
  void setGrafico(Chart*);
  Chart* getGrafico(void);
  void setNumPeriodo(long*);
  PointLine getSMA(Candlestick*);

 public:
  MovingAverage(long, Chart*);
  ~MovingAverage(void);
  long* getNumPeriodo(void);
  Line SMA(void);
  Line EMA(void);
};

#endif