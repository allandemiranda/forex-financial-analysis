/**
 * @file Candlestick.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos para classe Candlestick
 * @version 0.1
 * @date 29-09-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Candlestick.hpp"
#include <iomanip>
#include <iostream>
#include "omp.h"

/**
 * @brief Construa um novo objeto Candlestick:: Candlestick
 *
 * @param time Tempo da vela em segundos
 * @param date Data da abertura da vela em Epoch
 */
Candlestick::Candlestick(time_t time, time_t date) {
#pragma omp parallel sections
  {
#pragma omp section
    { setTime(time); }
#pragma omp section
    { setDate(date); }
#pragma omp section
    { setStatus("VOID"); }
  }
}

/**
 * @brief Construa um novo objeto Candlestick:: Candlestick
 *
 * @param stick Vela com os dados
 */
Candlestick::Candlestick(stick_s_t stick) {
#pragma omp parallel sections
  {
#pragma omp section
    { setStatus("OK"); }
#pragma omp section
    { setOpen(std::stold(stick[2])); }
#pragma omp section
    { setClose(std::stold(stick[5])); }
#pragma omp section
    { setHigh(std::stold(stick[3])); }
#pragma omp section
    { setLow(std::stold(stick[4])); }
  }
  if (getOpen() >= getClose()) {
#pragma omp parallel sections
    {
#pragma omp section
      { setType("DOWN"); }
#pragma omp section
      { setUpperShandowSize(getHigh(), getOpen()); }
#pragma omp section
      { setLowerShandowSize(getClose(), getLow()); }
#pragma omp section
      { setBodySize(getOpen(), getClose()); }
    }
  } else {
    if (getOpen() < getClose()) {
#pragma omp parallel sections
      {
#pragma omp section
        { setType("UP"); }
#pragma omp section
        { setUpperShandowSize(getHigh(), getClose()); }
#pragma omp section
        { setLowerShandowSize(getOpen(), getLow()); }
#pragma omp section
        { setBodySize(getClose(), getOpen()); }
      }
    } else {
      if (getOpen() == getClose()) {
#pragma omp parallel sections
        {
#pragma omp section
          { setType("STABLE"); }
#pragma omp section
          { setUpperShandowSize(getHigh(), getOpen()); }
#pragma omp section
          { setLowerShandowSize(getClose(), getLow()); }
#pragma omp section
          { setBodySize(0.0, 0.0); }
        }
      } else {
        throw "ERRO! Abertura e Fechamento de vela inderetminado na criação da vela";
      }
    }
  }
#pragma omp parallel sections
  {
#pragma omp section
    { setSize(getHigh(), getLow()); }
#pragma omp section
    {
      putenv(tz.data());
      struct std::tm tm;
      std::vector<std::string> date_v = explode(stick[0], '.');
      tm.tm_year = std::stoi(date_v[0]) - 1900;
      tm.tm_mon = std::stoi(date_v[1]) - 1;
      tm.tm_mday = std::stoi(date_v[2]);
      std::vector<std::string> time_v = explode(stick[1], ':');
      tm.tm_hour = std::stoi(time_v[0]);
      tm.tm_min = std::stoi(time_v[1]);
      tm.tm_sec = std::stoi(time_v[2]);
      tm.tm_isdst = -1;
      setDate(std::mktime(&tm));
    }
#pragma omp section
    { setTime(std::stol(stick[9])); }
  }
}

/**
 * @brief Destrua o objeto Candlestick:: Candlestick
 *
 */
Candlestick::~Candlestick(void) {}

/**
 * @brief Explodir uma string
 *
 * @param line String
 * @param c Caracter de quebra
 * @return std::vector<std::string> Vetor com as partes
 */
std::vector<std::string> Candlestick::explode(const std::string line, char c) {
  std::string buff{""};
  std::vector<std::string> v;
  for (auto n : line) {
    if (n != c) {
      buff += n;
    } else if (n == c && buff != "") {
      v.push_back(buff);
      buff = "";
    }
  }
  if (buff != "") {
    v.push_back(buff);
  }
  return v;
}

/**
 * @brief Obter o objeto Open
 *
 * @return pip_t Valor de abertura
 */
pip_t Candlestick::getOpen(void) {
  if (getStatus() == "VOID") {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getOpen.";
  }
  return open;
}

/**
 * @brief Obter o objeto Close
 *
 * @return pip_t Valor de fechamento
 */
pip_t Candlestick::getClose(void) {
  if (getStatus() == "VOID") {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getClose.";
  }
  return close;
}

/**
 * @brief Obter o objeto Type
 *
 * @return std::string Tipo de vela
 */
std::string Candlestick::getType(void) {
  if (getStatus() == "VOID") {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getType.";
  }
  if (type == 0) {
    return "UP";
  } else {
    if (type == 1) {
      return "DOWN";
    } else {
      if (type == 2) {
        return "STABLE";
      } else {
        throw "ERRO! Ao obter tipo da vela, tipo está indisponível";
      }
    }
  }
}

/**
 * @brief Obter o objeto High
 *
 * @return pip_t Valor mais alto da vela
 */
pip_t Candlestick::getHigh(void) {
  if (getStatus() == "VOID") {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getHigh.";
  }
  return high;
}

/**
 * @brief Obter o objeto Low
 *
 * @return pip_t Valor mais baixo da vela
 */
pip_t Candlestick::getLow(void) {
  if (getStatus() == "VOID") {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getLow.";
  }
  return low;
}

/**
 * @brief Obter o objeto Upper Shandow Size
 *
 * @return pip_t Tamanho da calda superior
 */
pip_t Candlestick::getUpperShandowSize(void) {
  if (getStatus() == "VOID") {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getUpperShandowSize.";
  }
  return upperShandowSize;
}

/**
 * @brief Obter o objeto Lower Shandow Size
 *
 * @return pip_t Tamanho da calda inferior
 */
pip_t Candlestick::getLowerShandowSize(void) {
  if (getStatus() == "VOID") {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getLowerShandowSize.";
  }
  return lowerShandowSize;
}

/**
 * @brief Obter o objeto Body Size
 *
 * @return pip_t Tamanho do corpo
 */
pip_t Candlestick::getBodySize(void) {
  if (getStatus() == "VOID") {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getBodySize.";
  }
  return bodySize;
}

/**
 * @brief Obter o objeto Size
 *
 * @return pip_t Tamanho total da vela
 */
pip_t Candlestick::getSize(void) {
  if (getStatus() == "VOID") {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getSize.";
  }
  return size;
}

/**
 * @brief Obter o objeto Date
 *
 * @return time_t Data da abertura da vela em
 */
time_t Candlestick::getDate(void) { return date; }

/**
 * @brief Obter o objeto Time
 *
 * @return time_t Tempo da vela em segundos
 */
time_t Candlestick::getTime(void) { return time; }

/**
 * @brief Obter o objeto Status
 *
 * @return std::string Status da vela
 */
std::string Candlestick::getStatus(void) {
  if (status) {
    return "OK";
  } else {
    return "VOID";
  }
}

/**
 * @brief Defina o objeto Open
 *
 * @param new_pip Novo valor de abertura
 */
void Candlestick::setOpen(pip_t new_pip) { open = new_pip; }

/**
 * @brief Defina o objeto Close
 *
 * @param new_pip Novo valor de fechamento
 */
void Candlestick::setClose(pip_t new_pip) { close = new_pip; }

/**
 * @brief Defina o objeto Type
 *
 * @param new_type Novo valor de tipo
 */
void Candlestick::setType(std::string new_type) {
  if (new_type == "UP") {
    type = 0;
  } else {
    if (new_type == "DOWN") {
      type = 1;
    } else {
      if (new_type == "STABLE") {
        type = 2;
      } else {
        throw "ERRO! Ao definir valor da vela, informação é incompatível com os tipos possíveis";
      }
    }
  }
}

/**
 * @brief Defina o objeto High
 *
 * @param new_pip Novo valor mais alto
 */
void Candlestick::setHigh(pip_t new_pip) { high = new_pip; }

/**
 * @brief Defina o objeto Low
 *
 * @param new_pip Novo valor mais baixo
 */
void Candlestick::setLow(pip_t new_pip) { low = new_pip; }

/**
 * @brief Defina o objeto Upper Shandow Size
 *
 * @param pip_high Valor mais alto a vela
 * @param number Valor inferior da calda alta
 */
void Candlestick::setUpperShandowSize(pip_t pip_high, pip_t number) {
  upperShandowSize = pip_high - number;
}

/**
 * @brief Defina o objeto Lower Shandow Size
 *
 * @param number Valor superior da calda baixa
 * @param pip_low Valor mais baixo da vela
 */
void Candlestick::setLowerShandowSize(pip_t number, pip_t pip_low) {
  lowerShandowSize = number - pip_low;
}

/**
 * @brief Defina o objeto Body Size
 *
 * @param number_high Valor mais alto do corpo
 * @param number_low Valor mais baixo do corpo
 */
void Candlestick::setBodySize(pip_t number_high, pip_t number_low) {
  bodySize = number_high - number_low;
}

/**
 * @brief Defina o objeto Size
 *
 * @param pip_high Valor mais alto da vela
 * @param pip_low Valor mais baixo da vela
 */
void Candlestick::setSize(pip_t pip_high, pip_t pip_low) {
  size = pip_high - pip_low;
}

/**
 * @brief Defina o objeto Date
 *
 * @param new_date Data em
 */
void Candlestick::setDate(time_t new_date) {
  if (new_date == -1) {
    // throw "ERRO! Foi definida uma data como -1";
  }
  date = new_date;
}

/**
 * @brief Defina o objeto Time
 *
 * @param new_time Tempo da vela em segundos
 */
void Candlestick::setTime(time_t new_time) { time = new_time; }

/**
 * @brief Defina o objeto Status
 *
 * @param new_status Status da vela
 */
void Candlestick::setStatus(std::string new_status) {
  if (new_status == "OK") {
    status = true;
  } else {
    if (new_status == "VOID") {
      status = false;
    } else {
      throw "ERRO! Ao definir status da vela, informação é incompatível com os status possíveis";
    }
  }
}