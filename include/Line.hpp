/**
 * @file Line.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Criação de linhas
 * @version 0.1
 * @date 11-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef LINE_HPP_
#define LINE_HPP_

#include <ctime>
#include "Candlestick.hpp"

class Line {
 private:
  time_t date;
  void setDate(time_t*);
  pip_t price;
  void setPrice(pip_t*);

 public:
  time_t* getDate(void);
  pip_t* getPrice(void);
  Line(time_t*, pip_t*);
  ~Line(void);
};

#endif