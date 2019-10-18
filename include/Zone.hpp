/**
 * @file Zone.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe para determianr zonas de suporte ou resistência
 * @version 0.1
 * @date 17-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef ZONE_HPP_
#define ZONE_HPP_

#include "Candlestick.hpp"

class Zone {
 private:
  pip_t upLine = 0.0;
  void setUpLine(pip_t*);
  pip_t downLine = 0.0;
  void setDownLine(pip_t*);
  pip_t size = 0.0;
  void setSize(pip_t*,pip_t*);
  void setSize(void);
  unsigned long power = 0;
  void setPower(unsigned long*);

 public:
  Zone(pip_t*, pip_t*, unsigned long*);
  ~Zone(void);
  pip_t* getUpLine(void);
  pip_t* getDownLine(void);
  pip_t* getSize(void);
  unsigned long* getPower(void);
};

#endif