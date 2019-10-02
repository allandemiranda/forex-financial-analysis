/**
 * @file ChartGoogle.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe contendo as funções de criação de gráficos
 * @version 0.1
 * @date 02-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef CHARTGOOGLE_HPP_
#define CHARTGOOGLE_HPP_

#include <Chart.hpp>
#include <string>

class ChartGoogle {
 private:
  std::string write(Chart&, std::string, std::string, std::string);
  void save(std::string, std::string);
  void setOpitions(std::string);
  std::string getOpitions(void);
  std::string opitions;
  std::string header =
      "<html><head><script type='text/javascript' "
      "src='https://www.gstatic.com/charts/loader.js'></script><script "
      "type='text/javascript'>google.charts.load('current', {'packages' : "
      "['corechart']}); google.charts.setOnLoadCallback(drawChart);function "
      "drawChart() {";
  std::string footer =
      "var chart = new "
      "google.visualization.CandlestickChart(document.getElementById('chart_"
      "div'));"
      "chart.draw(data, options);"
      "}"
      " </script>"
      "</head>"
      "<body>"
      " <div id='chart_div' style='width: 100%; height: 100%;'></div>"
      "</body>"
      "</html>";
  std::string TimeZone = "TZ=America/Recife";
  std::string nameChart;
  std::string getNameChart(void);
  void setNameChart(std::string);

 public:
  ChartGoogle(Chart&, std::string, std::string);
  ~ChartGoogle(void);
};
#endif