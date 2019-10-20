/**
 * @file Chart.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe com as informações do gráfico
 * @version 0.1
 * @date 04-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef CHART_HPP_
#define CHART_HPP_

#include <ctime>
#include <string>
#include <vector>
#include "Candlestick.hpp"

class Chart {
 private:
  time_t timeChart;
  void setTimeChart(std::string*);
  std::string nameChart;
  void setNameChart(std::string*);
  std::vector<std::string> explode(const std::string*, char*);
  void openFile(std::string*);  // Abre o arquivo
  std::vector<std::vector<std::string>> fileVector;
  void convertingToTime(void);  // converte para o tempo do gráfico
  void convertingToTimeVector(
      time_t*,
      time_t*);  // Bote void onde precisar e some também
  void convertingToCandlestick(void);
  void cleanOutTime(void);
  std::string timeZoneChart = "TZ=EET";  // Time Zone do banco de dados
  std::vector<Candlestick>::iterator candleSearch(std::vector<Candlestick>*,
                                                  time_t);
  void convertingToTimeVectorSecond(time_t*, time_t*);
  void convertingToTimeVectorMES(time_t*, time_t*);
  void convertingToTimeVectorANO(time_t*, time_t*);
  std::string identifier(Candlestick*);
  price_t averageCandleBody;  // Média do tamanhod o corpo das velas
  void makeAverageCandleBody(std::vector<Candlestick>*);  // faça a média

 public:
  std::vector<Candlestick> chart;
  time_t* getTimeChart(void);
  std::string* getNameChart(void);
  Chart(std::string*, std::string*, std::string*);
  ~Chart(void);
};

#endif