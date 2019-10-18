/**
 * @file Pip.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief classe contendo as converções de índices forex
 * @version 0.1
 * @date 18-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef PIP_HPP_
#define PIP_HPP_

typedef long double price_t;  // Unidade de valor da moeda
typedef unsigned long pip_t;  // Unidade de valor forex (índice) 0.0001
typedef unsigned long
    pip_JPY_t;  // Unidade de valor forex (índice) para JPY 0.01

class Pip {
 private:
  price_t valor;
  pip_t pip;
  pip_JPY_t pipJPY;

 public:
  price_t* getPrice(void);
  pip_t* getPip(void);
  pip_JPY_t* getPipJPY(void);
  Pip(price_t);
  Pip(pip_t, bool);
  // Pip(pip_JPY_t);
  ~Pip(void);
};

#endif