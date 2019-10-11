/**
 * @file LinePrice.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe que gerencia a criação de ondas de preço
 * @version 0.1
 * @date 11-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef LINEPRICE_HPP_
#define LINEPRICE_HPP_

#include <vector>
#include "Candlestick.hpp"
#include "Line.hpp"

class LinePrice {
 private:
  time_t lastMaxDate;
  pip_t lastMaxPrice;
  bool trend;  // true-> UP, false-> DOWN
  struct trendFlag {
    Candlestick *candle;
    short int trend;  // 0-> UP, 1-> DOWN, 2-> MAXUP, 3-> MAXDOWN
  };
  std::vector<trendFlag> firstTrend;
  void setFirstTrend(std::vector<Candlestick> *, unsigned int *);

 public:
  std::vector<Line> line;
  LinePrice(std::vector<Candlestick> *, unsigned int);
  ~LinePrice(void);
};

#endif