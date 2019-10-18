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

#include "Pip.hpp"
#include "Line.hpp"

class Zone {
 private:
  price_t upLine = 0.0;
  void setUpLine(price_t*);
  price_t downLine = 0.0;
  void setDownLine(price_t*);
  price_t size = 0.0;
  void setSize(price_t*, price_t*);
  void setSize(void);
  unsigned long power = 0;
  void setPower(unsigned long*);
  Line linhas[2];

 public:
  Zone(price_t*, price_t*, unsigned long*, time_t*, time_t*);
  ~Zone(void);
  price_t* getUpLine(void);
  price_t* getDownLine(void);
  price_t* getSize(void);
  unsigned long* getPower(void);
  bool operator<(Zone&);
  Line getLinhaSuperior(void);
  Line getLinhaInferior(void);
};

#endif