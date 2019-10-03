/**
 * @file Chart.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe contendo o gráfico de análise
 * @version 0.1
 * @date 01-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef CHART_HPP_
#define CHART_HPP_

#include <ctime>
#include "Candlestick.hpp"
#include "DataBase.hpp"

typedef std::vector<Candlestick> chart_t;

class Chart {
 private:
  std::string name;
  void setNameChart(std::string);
  time_t chartTime;
  std::string chartTime_S;
  time_t convertStringTimeToSeconds(std::string);
  void setChartTimeString(std::string);
  void setChartTime(std::string);
  time_t getOlderCandleTime(DataBase&, time_t);
  time_t getNewestCandleTime(DataBase&, time_t);
  Candlestick newVoidCandle(time_t, time_t);
  chart_t chartvector;
  chart_t transformMinutToMaxMinut(time_t, time_t, time_t);
  void putDataBaseOnChart(time_t, time_t, std::vector<Candlestick>*);

 public:
  Chart(DataBase&, std::string, std::string);
  ~Chart(void);
  time_t getChartTime(void);
  std::string getChartTimeString(void);
  chart_t getChart(void);
  std::string getNameChart(void);
};

#endif