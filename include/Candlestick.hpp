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

typedef long double pip_t;  // Unidade de medida forex
/*
 * Vela em formato puro:
 * DATE, TIME, OPEN, HIGH, LOW, CLOSE, TICKVOL, VOL, SPREAD
 */
typedef std::vector<std::string> stick_s_t;  // Vela em formato de vetor puro

class Candlestick {
 private:
  pip_t open;  // Valor de abertura da vela
  void setOpen(pip_t);
  pip_t close;  // Valor de fechamento da vela
  void setClose(pip_t);
  unsigned int type;  // Tipo de vela: 0 -> UP, 1 -> DOWN, 2 -> STABLE
  void setType(std::string);
  pip_t high;  // Valor mais alto da vela
  void setHigh(pip_t);
  pip_t low;  // Valor mais baixo da vela
  void setLow(pip_t);
  pip_t upperShandowSize;  // Volume da calda superior da vela
  void setUpperShandowSize(pip_t, pip_t);
  pip_t lowerShandowSize;  // Volume da calda inferior da vela
  void setLowerShandowSize(pip_t, pip_t);
  pip_t bodySize;  // Volume do corpo da vela
  void setBodySize(pip_t, pip_t);
  pip_t size;  // Volume da vela
  void setSize(pip_t, pip_t);
  time_t date;  // Data da vela
  void setDate(time_t);
  time_t time;  // Tempo da vela
  void setTime(time_t);
  bool status;  // Status da vela: true -> OK, false -> VOID
  void setStatus(std::string);
  std::vector<std::string> explode(const std::string, char);
  std::string tz = "TZ=EET";  // Time Zone do banco de dados

 public:
  Candlestick(time_t, time_t);
  Candlestick(stick_s_t);
  ~Candlestick(void);
  pip_t getOpen(void);
  pip_t getClose(void);
  std::string getType(void);
  pip_t getHigh(void);
  pip_t getLow(void);
  pip_t getUpperShandowSize(void);
  pip_t getLowerShandowSize(void);
  pip_t getBodySize(void);
  pip_t getSize(void);
  time_t getDate(void);
  time_t getTime(void);
  std::string getStatus(void);
};

#endif