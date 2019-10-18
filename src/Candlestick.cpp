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
#include <omp.h>

/**
 * @brief Construa um novo objeto Candlestick:: Candlestick
 *
 * @param time Tempo da vela em segundos
 * @param date Data da abertura da vela em Epoch
 */
Candlestick::Candlestick(time_t* time, time_t* date) {
#pragma omp parallel sections
  {
#pragma omp section
    { setTime(time); }
#pragma omp section
    { setDate(date); }
#pragma omp section
    {
      bool void_status = false;
      setStatus(&void_status);
    }
  }
}

/**
 * @brief Construa um novo objeto Candlestick:: Candlestick
 *
 * @param stick Vela com os dados
 */
Candlestick::Candlestick(std::vector<std::string>* stick) {
  struct std::tm tm;
  std::vector<std::string> date_v;
  std::vector<std::string> time_v;

#pragma omp parallel sections
  {
#pragma omp section
    {
      char ponto = '.';
      date_v = explode(&stick->at(0), &ponto);
    }
#pragma omp section
    {
      char dois_pontos = ':';
      time_v = explode(&stick->at(1), &dois_pontos);
    }
  }

#pragma omp parallel sections
  {
#pragma omp section
    {
      bool status_agora = true;
      setStatus(&status_agora);
    }
#pragma omp section
    {
      price_t open_new = std::stold(stick->at(2));
      setOpen(&open_new);
    }
#pragma omp section
    {
      price_t close_new = std::stold(stick->at(5));
      setClose(&close_new);
    }
#pragma omp section
    {
      price_t high_new = std::stold(stick->at(3));
      setHigh(&high_new);
    }
#pragma omp section
    {
      price_t low_new = std::stold(stick->at(4));
      setLow(&low_new);
    }
#pragma omp section
    { tm.tm_year = std::stoi(date_v[0]) - 1900; }
#pragma omp section
    { tm.tm_mon = std::stoi(date_v[1]) - 1; }
#pragma omp section
    { tm.tm_mday = std::stoi(date_v[2]); }
#pragma omp section
    { tm.tm_hour = std::stoi(time_v[0]); }
#pragma omp section
    { tm.tm_min = std::stoi(time_v[1]); }
#pragma omp section
    { tm.tm_sec = std::stoi(time_v[2]); }
#pragma omp section
    { tm.tm_isdst = -1; }
#pragma omp section
    {
      time_t set_new_time = std::stol(stick->back());
      setTime(&set_new_time);
    }
  }

#pragma omp parallel sections
  {
#pragma omp section
    {
      time_t new_tempo = std::mktime(&tm);
      setDate(&new_tempo);
      if (new_tempo == -1) {
        throw "ERRO! Ao trasformar data em std::tm";
      }
    }
#pragma omp section
    { setSize(getHigh(), getLow()); }
  }

  if (*getOpen() > *getClose()) {
#pragma omp parallel sections
    {
#pragma omp section
      {
        unsigned int new_type = 1;
        setType(&new_type);
      }
#pragma omp section
      { setUpperShandowSize(getHigh(), getOpen()); }
#pragma omp section
      { setLowerShandowSize(getClose(), getLow()); }
#pragma omp section
      { setBodySize(getOpen(), getClose()); }
    }
  } else {
    if (*getOpen() < *getClose()) {
#pragma omp parallel sections
      {
#pragma omp section
        {
          unsigned int new_type = 0;
          setType(&new_type);
        }
#pragma omp section
        { setUpperShandowSize(getHigh(), getClose()); }
#pragma omp section
        { setLowerShandowSize(getOpen(), getLow()); }
#pragma omp section
        { setBodySize(getClose(), getOpen()); }
      }
    } else {
      if (*getOpen() == *getClose()) {
#pragma omp parallel sections
        {
#pragma omp section
          {
            unsigned int new_type = 2;
            setType(&new_type);
          }
#pragma omp section
          { setUpperShandowSize(getHigh(), getOpen()); }
#pragma omp section
          { setLowerShandowSize(getClose(), getLow()); }
#pragma omp section
          {
            price_t num = 0.0;
            setBodySize(&num, &num);
          }
        }
      } else {
        throw "ERRO! Abertura e Fechamento de vela inderetminado na criação da vela";
      }
    }
  }
}

/**
 * @brief Construa um novo objeto Candlestick:: Candlestick
 *
 * @param new_date Data da abertura da vela (em segundos apartir de 1900)
 * @param new_open Valor de abertura da vela
 * @param new_close valor de fechamento da vela
 * @param new_high Valor mais alto da vela
 * @param new_low Valor mais baixo da vela
 * @param new_time Tempo da vela (em segundos)
 */
Candlestick::Candlestick(time_t* new_date, price_t* new_open,
                         price_t* new_close, price_t* new_high,
                         price_t* new_low, time_t* new_time) {
#pragma omp parallel sections
  {
#pragma omp section
    {
      bool new_status = true;
      setStatus(&new_status);
    }
#pragma omp section
    { setOpen(new_open); }
#pragma omp section
    { setClose(new_close); }
#pragma omp section
    { setHigh(new_high); }
#pragma omp section
    { setLow(new_low); }
#pragma omp section
    { setDate(new_date); }
#pragma omp section
    { setTime(new_time); }
  }

  setSize(getHigh(), getLow());

  if (*getOpen() > *getClose()) {
#pragma omp parallel sections
    {
#pragma omp section
      {
        unsigned int new_type = 1;
        setType(&new_type);
      }
#pragma omp section
      { setUpperShandowSize(getHigh(), getOpen()); }
#pragma omp section
      { setLowerShandowSize(getClose(), getLow()); }
#pragma omp section
      { setBodySize(getOpen(), getClose()); }
    }
  } else {
    if (*getOpen() < *getClose()) {
#pragma omp parallel sections
      {
#pragma omp section
        {
          unsigned int new_type = 0;
          setType(&new_type);
        }
#pragma omp section
        { setUpperShandowSize(getHigh(), getClose()); }
#pragma omp section
        { setLowerShandowSize(getOpen(), getLow()); }
#pragma omp section
        { setBodySize(getClose(), getOpen()); }
      }
    } else {
      if (*getOpen() == *getClose()) {
#pragma omp parallel sections
        {
#pragma omp section
          {
            unsigned int new_type = 2;
            setType(&new_type);
          }
#pragma omp section
          { setUpperShandowSize(getHigh(), getOpen()); }
#pragma omp section
          { setLowerShandowSize(getClose(), getLow()); }
#pragma omp section
          {
            price_t num = 0.0;
            setBodySize(&num, &num);
          }
        }
      } else {
        throw "ERRO! Abertura e Fechamento de vela inderetminado na criação da vela";
      }
    }
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
 * @param line* String
 * @param c* Caracter de quebra
 * @return std::vector<std::string> Vetor com as partes
 */
std::vector<std::string> Candlestick::explode(const std::string* line,
                                              char* c) {
  std::string buff{""};
  std::vector<std::string> v;
  for (auto n : *line) {
    if (n != *c) {
      buff += n;
    } else if (n == *c && buff != "") {
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
 * @return price_t* Valor de abertura
 */
price_t* Candlestick::getOpen(void) {
  if (!*getStatus()) {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getOpen.";
  }
  return &open;
}

/**
 * @brief Obter o objeto Close
 *
 * @return price_t* Valor de fechamento
 */
price_t* Candlestick::getClose(void) {
  if (!*getStatus()) {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getClose.";
  }
  return &close;
}

/**
 * @brief Obter o objeto Type
 *
 * @return unsigned int* 0 UP,
 * @return unsigned int* 1 DOWN
 * @return unsigned int* 2 STABLE
 */
unsigned int* Candlestick::getType(void) {
  if (!*getStatus()) {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getType.";
  }
  return &type;
}

/**
 * @brief Obter o objeto High
 *
 * @return price_t* Valor mais alto da vela
 */
price_t* Candlestick::getHigh(void) {
  if (!*getStatus()) {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getHigh.";
  }
  return &high;
}

/**
 * @brief Obter o objeto Low
 *
 * @return price_t* Valor mais baixo da vela
 */
price_t* Candlestick::getLow(void) {
  if (!*getStatus()) {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getLow.";
  }
  return &low;
}

/**
 * @brief Obter o objeto Upper Shandow Size
 *
 * @return price_t* Tamanho da calda superior
 */
price_t* Candlestick::getUpperShandowSize(void) {
  if (!*getStatus()) {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getUpperShandowSize.";
  }
  return &upperShandowSize;
}

/**
 * @brief Obter o objeto Lower Shandow Size
 *
 * @return price_t* Tamanho da calda inferior
 */
price_t* Candlestick::getLowerShandowSize(void) {
  if (!*getStatus()) {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getLowerShandowSize.";
  }
  return &lowerShandowSize;
}

/**
 * @brief Obter o objeto Body Size
 *
 * @return price_t* Tamanho do corpo
 */
price_t* Candlestick::getBodySize(void) {
  if (!*getStatus()) {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getBodySize.";
  }
  return &bodySize;
}

/**
 * @brief Obter o objeto Size
 *
 * @return price_t* Tamanho total da vela
 */
price_t* Candlestick::getSize(void) {
  if (!*getStatus()) {
    throw "ERRO! Vela do tipo VOID, impossivel de obter getSize.";
  }
  return &size;
}

/**
 * @brief Obter o objeto Date
 *
 * @return time_t* Data da abertura da vela em
 */
time_t* Candlestick::getDate(void) { return &date; }

/**
 * @brief Obter o objeto Time
 *
 * @return time_t* Tempo da vela em segundos
 */
time_t* Candlestick::getTime(void) { return &time; }

/**
 * @brief Obter o objeto Status
 *
 * @return bool* true OK
 * @return bool* false VOID
 */
bool* Candlestick::getStatus(void) { return &status; }

/**
 * @brief Defina o objeto Open
 *
 * @param new_pip Novo valor de abertura
 */
void Candlestick::setOpen(price_t* new_pip) { open = *new_pip; }

/**
 * @brief Defina o objeto Close
 *
 * @param new_pip Novo valor de fechamento
 */
void Candlestick::setClose(price_t* new_pip) { close = *new_pip; }

/**
 * @brief Defina o objeto Type
 *
 * @param new_type 0 UP
 * @param new_type 1 DOWN
 * @param new_type 2 STABLE
 */
void Candlestick::setType(unsigned int* new_type) {
  if ((*new_type == 0) or (*new_type == 1) or (*new_type == 2)) {
    type = *new_type;
  } else {
    throw "ERRO! Ao definir valor da vela, informação é incompatível com os tipos possíveis";
  }
}

/**
 * @brief Defina o objeto High
 *
 * @param new_pip Novo valor mais alto
 */
void Candlestick::setHigh(price_t* new_pip) { high = *new_pip; }

/**
 * @brief Defina o objeto Low
 *
 * @param new_pip Novo valor mais baixo
 */
void Candlestick::setLow(price_t* new_pip) { low = *new_pip; }

/**
 * @brief Defina o objeto Upper Shandow Size
 *
 * @param pip_high Valor mais alto a vela
 * @param number Valor inferior da calda alta
 */
void Candlestick::setUpperShandowSize(price_t* pip_high, price_t* number) {
  upperShandowSize = *pip_high - *number;
}

/**
 * @brief Defina o objeto Lower Shandow Size
 *
 * @param number Valor superior da calda baixa
 * @param pip_low Valor mais baixo da vela
 */
void Candlestick::setLowerShandowSize(price_t* number, price_t* pip_low) {
  lowerShandowSize = *number - *pip_low;
}

/**
 * @brief Defina o objeto Body Size
 *
 * @param number_high Valor mais alto do corpo
 * @param number_low Valor mais baixo do corpo
 */
void Candlestick::setBodySize(price_t* number_high, price_t* number_low) {
  bodySize = *number_high - *number_low;
}

/**
 * @brief Defina o objeto Size
 *
 * @param pip_high Valor mais alto da vela
 * @param pip_low Valor mais baixo da vela
 */
void Candlestick::setSize(price_t* pip_high, price_t* pip_low) {
  size = *pip_high - *pip_low;
}

/**
 * @brief Defina o objeto Date
 *
 * @param new_date Data de abertura da vela em segundos
 */
void Candlestick::setDate(time_t* new_date) {
  if (*new_date == -1) {
    throw "ERRO! Foi definida uma data como -1";
  }
  date = *new_date;
}

/**
 * @brief Defina o objeto Time
 *
 * @param new_time Tempo da vela
 */
void Candlestick::setTime(time_t* new_time) { time = *new_time; }

/**
 * @brief Defina o objeto Status
 *
 * @param new_status true OK
 * @param new_status false VOID
 */
void Candlestick::setStatus(bool* new_status) { status = *new_status; }

/**
 * @brief Obter Time Zone usada para gravar Vela
 *
 * @return std::string Informção da zona
 */
std::string Candlestick::getTZ(void) { return tz; }

/**
 * @brief Sobrecarga do operador < comparando duas velas
 *
 * @param a Vela à validar
 * @return true a maior que a vela
 * @return false a menor que a vela
 */
bool Candlestick::operator<(Candlestick& a) { return date < a.date; }

/**
 * @brief Sobrecarga do operador < comparando a vela com o tempo
 *
 * @param a tempo a ser comparado
 * @return true Se a vela é menor
 * @return false Se a vela é maior
 */
bool Candlestick::operator<(time_t a) { return date < a; }

/**
 * @brief Sobrecarga do operador <= comparando duas velas
 *
 * @param a Vela a ser comparada
 * @return true a maior igual que vela
 * @return false a menor que vela
 */
bool Candlestick::operator<=(Candlestick& a) { return date <= a.date; }

/**
 * @brief Sobrecarga do operador >
 *
 * @param a Vela a ser comparada
 * @return true a menor que vela
 * @return false a maior que vela
 */
bool Candlestick::operator>(Candlestick& a) { return date > a.date; }

/**
 * @brief Sobrecarga do operador >=
 *
 * @param a Vela a ser comparada
 * @return true a menor igual a vela
 * @return false a maior que vela
 */
bool Candlestick::operator>=(Candlestick& a) { return date >= a.date; }

/**
 * @brief Sobrecarga do operador ==
 *
 * @param a Vela a ser comparada
 * @return true Se as velas são iguais
 * @return false Se as velas não são iguais
 */
bool Candlestick::operator==(Candlestick& a) { return date == a.date; }

/**
 * @brief sobrecarga de operador +
 *
 * @param a Vela a somar
 * @return Candlestick Vela fundida
 */
Candlestick Candlestick::operator+(Candlestick& a) {
  if (status) {
    if (a.status) {
      price_t high_p;
      price_t low_p;
      time_t time_p;
#pragma omp parallel sections
      {
#pragma omp section
        {
          if (high > a.high) {
            high_p = high;
          }
        }
#pragma omp section
        {
          if (high <= a.high) {
            high_p = a.high;
          }
        }
#pragma omp section
        {
          if (low < a.low) {
            low_p = low;
          }
        }
#pragma omp section
        {
          if (low >= a.low) {
            low_p = a.low;
          }
        }
#pragma omp section
        { time_p = time + a.time; }
      }
      Candlestick new_p(&date, &open, &a.close, &high_p, &low_p, &time_p);
      return new_p;
    } else {
      time_t time_p = time + a.time;
      Candlestick new_p(&date, &open, &close, &high, &low, &time_p);
      return new_p;
    }
  } else {
    if (a.status) {
      time_t time_p = time + a.time;
      Candlestick new_p(&date, &a.open, &a.close, &a.high, &a.low, &time_p);
      return new_p;
    } else {
      time_t time_p = time + a.time;
      Candlestick new_p(&time_p, &date);
      return new_p;
    }
  }
}

/**
 * @brief Adicionar tempo a vela
 *
 * @param plus_time Tempo a ser adicionado
 */
void Candlestick::addTime(time_t plus_time) { time = time + plus_time; }