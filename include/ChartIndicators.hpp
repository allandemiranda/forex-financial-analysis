/**
 * @file ChartIndicators.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe com os indicadores de gráficos conhecidos no mercado
 * @version 0.1
 * @date 12-11-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef CHARTINDICATORS_HPP_
#define CHARTINDICATORS_HPP_

#include "Chart.hpp"
#include "Line.hpp"

class ChartIndicators
{
private:
  Chart *grafico;
  void setGrafico(Chart*);
public:
  ChartIndicators(Chart*);
  ~ChartIndicators(void);
  std::vector<Line> MACD(unsigned int, unsigned int, unsigned int);
  std::vector<Line> Stochastic(unsigned int, unsigned int);
  // RSI

};

#endif