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

#include <string>
#include <vector>
#include "Chart.hpp"
#include "Line.hpp"

class LinePrice : public Line{
 private:
  struct trendFlag {
    Candlestick *candle;
    short int trend;  // 0-> UP, 1-> DOWN, 2-> MAXUP, 3-> MAXDOWN
    bool operator<(trendFlag &a) {
      return *candle->getDate() < *a.candle->getDate();
    }
  };
  bool trend;  // true-> UP, false-> DOWN
  trendFlag *last;
  std::vector<trendFlag> firstTrend;
  void setFirstTrend(Chart *, unsigned int *);
  void setFinal(std::string*);

 public:
  LinePrice(Chart *, unsigned int, std::string);
  ~LinePrice(void);
};

#endif