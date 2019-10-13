/**
 * @file Dashboard.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe contendo as funçẽos para desenhar um gráfico
 * @version 0.1
 * @date 03-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef DASHBOARD_HPP_
#define DASHBOARD_HPP_

#include <string>
#include <vector>
#include "Candlestick.hpp"
#include "Line.hpp"

class Dashboard {
 private:
  std::string header = 
    "<!DOCTYPE HTML>\n"
    "<html>\n"
    "<head>\n";
  std::string scriptHeader = 
    "<script>\n"
    "window.onload = function () {\n"
    "\n"
    "var chart = new CanvasJS.Chart('chartContainer', {\n";
  std::string scriptOpitons = 
    "zoomEnabled: true,\n"
    "animationEnabled: true,\n"
    "theme: 'light2',\n"
    "exportEnabled: true,\n"
    "axisX: {\nvalueFormatString: 'DD.MM.YYYY HH:mm'\n},\n"
    "axisY: {\nincludeZero: false,\nprefix: '',\ntitle: 'Pip',\nprefix: '',\ngridDashType: 'dot'\n},\n"
    "toolTip: {\nshared: true\n},\n"
    "legend: {\nreversed: true,\ncursor: 'pointer',\nitemclick: toggleDataSeries\n},\n";
  void setTitle(std::string*);
  std::string scriptFooter =
    "]});\n"
    "chart.render();\n"
    "\n"
    "function toggleDataSeries(e) {\n"
    "if (typeof (e.dataSeries.visible) === 'undefined' || e.dataSeries.visible) {\n"
    "e.dataSeries.visible = false;\n"
    "} else {\n"
    "e.dataSeries.visible = true;\n"
    "}\n"
    "e.chart.render();\n"
    "}\n"
    "\n"
    "}\n"
    "</script>\n";
  std::string footer =
    "</head>\n"
    "\n"
    "<body>\n"
    "<div id='chartContainer' style='height: 100%; width: 100%;'></div>\n"
    "<script type='text/javascript' src='https://canvasjs.com/assets/script/canvasjs.min.js'></script>\n"
    "</body>\n"
    "\n"
    "</html>\n";
  std::string dataCandleHeader =
  "data: [{\n"
  "type: 'candlestick',\n"
  "showInLegend: true,\n"
  "name: 'Candlestick',\n"
  "risingColor: 'green',\n"
  "fallingColor: 'red',\n"
  "yValueFormatString: '#########.#########',\n"
  "xValueFormatString: 'DD.MM.YYYY HH:mm',\n"
  "dataPoints: [\n";
  std::string dataCandleFooter = 
  "]},\n"
  "\n"
  ;
  std::string TimeZone = "TZ=America/Recife";
  std::string dataLineHeader = 
  "{\n"
  "type: 'line',\n"
  "showInLegend: true,\n"
  "name: 'Line',\n"
  "yValueFormatString: '#########.#########',\n"
  "xValueFormatString: 'DD.MM.YYYY HH:mm',\n"
  "dataPoints: [\n";
  std::string dataLineFooter =
  "]\n"
  "},\n";

 public:
  Dashboard(std::string*, std::string*, std::vector<Candlestick>*);
  //Dashboard(std::string*, std::string*, std::vector<pip_t>*);
  Dashboard(std::string*, std::string*, std::vector<Candlestick>*, std::vector<Line>*);
  ~Dashboard(void);
};

#endif