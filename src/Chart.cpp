/**
 * @file Chart.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos da classe Chart
 * @version 0.1
 * @date 01-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Chart.hpp"
#include "omp.h"

/**
 * @brief Construa um novo objeto Chart:: Chart
 *
 * @param data_base Banco de velas
 * @param time_chart Tempo do gráfico
 * @param name_chart Nome do gráfico
 */
Chart::Chart(DataBase data_base, std::string time_chart,
             std::string name_chart) {
#pragma omp parallel sections
  {
#pragma omp section
    { setNameChart(name_chart); }
#pragma omp section
    { setChartTime(time_chart); }
#pragma omp section
    { setChartTimeString(time_chart); }
  }
  if (getChartTime() < (24 * 60 * 60)) {
    time_t data_inicial = getOlderCandleTime(data_base, 60);
    time_t data_inicial_too = data_inicial;  // Para a segunda parte
    for (int i(0); i < data_base.getDBStick().size(); ++i) {
      if (data_base.getDBStick()[i].getDate() < data_inicial) {
        data_base.getDBStick().erase(data_base.getDBStick().begin() + i);
        --i;
      } else {
        break;
      }
    }
    time_t data_final = getNewestCandleTime(data_base, 60);
    data_final += (60 * 60);  // Adicione um dia
    while (data_inicial < data_final) {
      if (data_base.getDBStick().size() > 0) {
        if (data_base.getDBStick().front().getDate() == data_inicial) {
          chartvector.push_back(data_base.getDBStick().front());
          data_base.getDBStick().erase(data_base.getDBStick().begin());
        } else {
          chartvector.push_back(newVoidCandle(60, data_inicial));
        }
      } else {
        chartvector.push_back(newVoidCandle(60, data_inicial));
      }
      data_inicial += 60;
    }
    if (getChartTime() > 60) {
      while (data_inicial_too <= data_final) {
        //
      }
    }
  }
}

/**
 * @brief Transformar um tempo gráfico de 1 minuto apra um tempo gráfico de mais
 * minutos
 *
 * @param data_inicial Data inicial da análise
 * @param data_final Data final da análise
 * @param tempoG Tempo do gráfico fulturo
 */
void Chart::transformMinutToMaxMinut(time_t data_inicial, time_t data_final,
                                     time_t tempoG) {
  tempoG = tempoG / 60;
  while (data_inicial <= data_final) {
    stick_s_t temp_nova_vela;
    for (auto i(0); i < tempoG; ++i) {
      
    }
  }
}

/**
 * @brief Destrua o objeto Chart:: Chart
 *
 */
Chart::~Chart(void) {}

/**
 * @brief Defina o objeto Name Chart
 *
 * @param name_chart Nome do gráfico
 */
void Chart::setNameChart(std::string name_chart) { name = name_chart; }

/**
 * @brief Defina o objeto Chart Time String
 *
 * @param time Tempo do gráfico (M1, H2, W1, M1, Y1)
 */
void Chart::setChartTimeString(std::string time) { chartTime_S = time; }

/**
 * @brief Defina o objeto Chart Time
 *
 * @param time Tempo do gráfico (M1, H2, W1, M1, Y1)
 */
void Chart::setChartTime(std::string time) {
  chartTime = convertStringTimeToSeconds(time);
}

/**
 * @brief Converter tempo gráfico em string para segundos
 *
 * @param time Tempo gráfico em strings
 * @return time_t Tempo em segundos
 */
time_t Chart::convertStringTimeToSeconds(std::string time) {
#pragma omp parallel sections
  {
#pragma omp section
    {
      if (time[0] == 'M') {
        time.erase(0, 1);
        int new_time = std::stoi(time);
        if (new_time > 0) {
          return (unsigned long)(60 * (unsigned long)new_time);
        } else {
          throw "ERRO! Formato do tempo gráfico de M está incorreto";
        }
      }
    }
#pragma omp section
    {
      if (time[0] == 'H') {
        time.erase(0, 1);
        int new_time = std::stoi(time);
        if (new_time > 0) {
          return (unsigned long)(60 * 60 * (unsigned long)new_time);
        } else {
          throw "ERRO! Formato do tempo gráfico de H está incorreto";
        }
      }
    }
#pragma omp section
    {
      if (time[0] == 'D') {
        time.erase(0, 1);
        int new_time = std::stoi(time);
        if (new_time > 0) {
          return (unsigned long)(24 * 60 * 60 * (unsigned long)new_time);
        } else {
          throw "ERRO! Formato do tempo gráfico de D está incorreto";
        }
      }
    }
#pragma omp section
    {
      if (time[0] == 'W') {
        time.erase(0, 1);
        int new_time = std::stoi(time);
        if (new_time > 0) {
          return (unsigned long)(7 * 24 * 60 * 60 * (unsigned long)new_time);
        } else {
          throw "ERRO! Formato do tempo gráfico de W está incorreto";
        }
      }
    }
#pragma omp section
    {
      if (time[0] == 'J') {
        time.erase(0, 1);
        int new_time = std::stoi(time);
        if (new_time == 1) {
          return (unsigned long)(4 * 7 * 24 * 60 * 60 *
                                 (unsigned long)new_time);
        } else {
          throw "ERRO! Formato do tempo gráfico de J está incorreto";
        }
      }
    }
#pragma omp section
    {
      if (time[0] == 'Y') {
        time.erase(0, 1);
        int new_time = std::stoi(time);
        if (new_time == 1) {
          return (unsigned long)(12 * 4 * 7 * 24 * 60 * 60 *
                                 (unsigned long)new_time);
        } else {
          throw "ERRO! Formato do tempo gráfico de Y está incorreto";
        }
      }
    }
  }
}

/**
 * @brief Obter o objeto Older Candle Time
 *
 * @param data_base Banco de velas
 * @param tempo Tempo da vela requerida
 * @return time_t Data da vela mais velha
 */
time_t Chart::getOlderCandleTime(DataBase& data_base, time_t tempo) {
  for (auto i : data_base.getDBStick()) {
    if (i.getTime() == tempo) {
      putenv(i.getTZ().data());
      std::time_t at = i.getDate();
      std::tm atm = *std::localtime(&at);
      atm.tm_hour = 0;
      atm.tm_min = 0;
      atm.tm_sec = 0;
      time_t final = std::mktime(&atm);
      if (final == -1) {
        throw "ERRO! Ao tentar encontrar o dia inicial, não foi possivel criar o dia";
      }
      return final;
    }
  }
  throw "ERRO! Não foi possivel detectar vela mais velha para o tempo";
}

/**
 * @brief Obter o objeto Newest Candle Time
 *
 * @param data_base Banco de velas
 * @param tempo Tempo da vela requerida
 * @return time_t Data da vela mais nova
 */
time_t getNewestCandleTime(DataBase& data_base, time_t tempo) {
  if (data_base.getDBStick().back().getTime() == tempo) {
    putenv(data_base.getDBStick().back().getTZ().data());
    std::time_t at = data_base.getDBStick().back().getDate();
    std::tm atm = *std::localtime(&at);
    atm.tm_hour = 0;
    atm.tm_min = 0;
    atm.tm_sec = 0;
    time_t final = std::mktime(&atm);
    if (final == -1) {
      throw "ERRO! Ao tentar encontrar o dia final, não foi possivel criar o dia";
    }
    return final;
  }
  throw "ERRO! Não foi possivel detectar vela mais nova para o tempo";
}

/**
 * @brief Criar uma vela VOID
 *
 * @param time Tempo da vela em segundos
 * @param date Data da abertura da vela em Epoch
 * @return Candlestick Nova vela VOID
 */
Candlestick Chart::newVoidCandle(time_t time, time_t date) {
  Candlestick new_void_candle(time, date);
  return new_void_candle;
}

/**
 * @brief Obter o objeto Chart Time
 *
 * @return time_t Tempo gráfico em segundos
 */
time_t Chart::getChartTime(void) { return chartTime; }

/**
 * @brief Obter o objeto Chart Time String
 *
 * @return std::string Tempo gráfico em String
 */
std::string Chart::getChartTimeString(void) { return chartTime_S; }

/**
 * @brief Obter o objeto Chart
 *
 * @return chart_t Vetor gráfico
 */
chart_t Chart::getChart(void) { return chartvector; }

/**
 * @brief Obter o objeto Name Chart
 *
 * @return std::string Nome do gráfico
 */
std::string Chart::getNameChart(void) { return name; }