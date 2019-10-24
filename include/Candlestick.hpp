/**
 * @file Candlestick.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe contendo todas as informações da vela
 * @version 0.1
 * @date 29-09-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef CANDLESTICK_HPP_
#define CANDLESTICK_HPP_

#include <ctime>
#include <string>
#include <vector>
#include "Pip.hpp"
/*
 * Vela em formato puro:
 * DATE, TIME, OPEN, HIGH, LOW, CLOSE, TICKVOL, VOL, SPREAD
 */

class Candlestick {
 private:
  price_t open;  // Valor de abertura da vela
  void setOpen(price_t*);
  price_t close;  // Valor de fechamento da vela
  void setClose(price_t*);
  unsigned int type;  // Tipo de vela: 0 -> UP, 1 -> DOWN, 2 -> STABLE
  void setType(unsigned int*);
  price_t high;  // Valor mais alto da vela
  void setHigh(price_t*);
  price_t low;  // Valor mais baixo da vela
  void setLow(price_t*);
  price_t upperShandowSize;  // Volume da calda superior da vela
  void setUpperShandowSize(price_t*, price_t*);
  price_t lowerShandowSize;  // Volume da calda inferior da vela
  void setLowerShandowSize(price_t*, price_t*);
  price_t bodySize;  // Volume do corpo da vela
  void setBodySize(price_t*, price_t*);
  price_t size;  // Volume da vela
  void setSize(price_t*, price_t*);
  time_t date;  // Data da vela
  void setDate(time_t*);
  time_t time;  // Tempo da vela
  void setTime(time_t*);
  bool status;  // Status da vela: true -> OK, false -> VOID
  void setStatus(bool*);
  std::vector<std::string> explode(const std::string*, char*);
  std::string tz = "TZ=EET";   // Time Zone do banco de dados
  std::string name;            // Nome da vela  

 public:
  Candlestick(time_t*, time_t*);
  Candlestick(std::vector<std::string>*);
  Candlestick(time_t*, price_t*, price_t*, price_t*, price_t*, time_t*);
  ~Candlestick(void);
  price_t* getOpen(void);
  price_t* getClose(void);
  unsigned int* getType(void);
  price_t* getHigh(void);
  price_t* getLow(void);
  price_t* getUpperShandowSize(void);
  price_t* getLowerShandowSize(void);
  price_t* getBodySize(void);
  price_t* getSize(void);
  time_t* getDate(void);
  time_t* getTime(void);
  void addTime(time_t);
  bool* getStatus(void);
  std::string getTZ(void);
  bool operator<(Candlestick&);
  bool operator<(time_t);
  bool operator<=(Candlestick&);
  bool operator>(Candlestick&);
  bool operator>=(Candlestick&);
  bool operator==(Candlestick&);
  bool operator==(time_t);
  Candlestick operator+(Candlestick&);
  std::string* getName(void);
  void setName(std::string);
};

#endif