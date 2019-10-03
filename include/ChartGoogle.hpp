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
  std::string write(std::vector<Candlestick>&, std::string, std::string,
                    std::string);
  void save(std::string, std::string);
  void setOpitions(std::string);
  std::string getOpitions(void);
  std::string opitions;
  std::string header =
      "<html>\n"
      "<head>\n"
      "<script type='text/javascript' "
      "src='https://www.gstatic.com/charts/loader.js'></script>\n"
      "<script type='text/javascript'>\n"
      "google.charts.load('current', { 'packages': ['corechart'] });\n"
      "google.charts.setOnLoadCallback(drawChart);\n"
      "function drawChart() {\n";
  std::string footer =
      "var chart = new "
      "google.visualization.CandlestickChart(document.getElementById('chart_"
      "div'));\n"
      "chart.draw(data, options);\n"
      "}\n"
      "</script>\n"
      "</head>\n"
      "<body>\n"
      "<div id='chart_div' style='width: 100%; height: 100%;'></div>\n"
      "</body>\n"
      "</html>\n";
  std::string TimeZone = "TZ=America/Recife";
  std::string nameChart;
  std::string getNameChart(void);
  void setNameChart(std::string);

 public:
  ChartGoogle(std::vector<Candlestick>, std::string, std::string);
  ~ChartGoogle(void);
};
#endif