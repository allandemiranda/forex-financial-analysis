/**
 * @file PointLine.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe contendo os pontos de uma linha
 * @version 0.1
 * @date 18-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef POINTLINE_HPP_
#define POINTLINE_HPP_

#include <ctime>
#include "Pip.hpp"

class PointLine {
  private:
  time_t date;
  void setDate(time_t*);
  price_t price;
  void setPrice(price_t*);

 public:
  time_t* getDate(void);
  price_t* getPrice(void);
  PointLine(time_t*, price_t*);
  ~PointLine(void);
  bool operator<(PointLine&);
};

#endif