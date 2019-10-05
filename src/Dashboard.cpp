/**
 * @file Dashboard.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos para Classe Dashboard
 * @version 0.1
 * @date 03-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Dashboard.hpp"
#include <dirent.h>
#include <cstring>
#include <fstream>
#include <iostream>

/**
 * @brief Construa um novo objeto Dashboard:: Dashboard
 *
 * @param novos_dados Dados do gráfico
 * @param caminho_salvar Caminho para salvar gráfico
 * @param nome_grafico Nome do gráfico
 */
Dashboard::Dashboard(std::vector<Candlestick>* novos_dados,
                     std::string caminho_salvar, std::string nome_grafico) {
  nomeGrafico = nome_grafico;
  createCabecalho();
  createRodape();
  createDados(novos_dados);
  write(caminho_salvar);
}

/**
 * @brief Destrua o objeto Dashboard:: Dashboard
 *
 */
Dashboard::~Dashboard(void) {}

/**
 * @brief Esquecer arquivo
 *
 * @param caminho Caminho do arquivo
 */
void Dashboard::write(std::string caminho) {
  try {
    char c = '/';
    std::string buff{""};
    std::vector<std::string> v;
    for (auto n : caminho) {
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
    std::string new_p = "";
    for (auto i(0u); i < (v.size() - 1); ++i) {
      new_p += v[i];
      new_p.push_back('/');
    }
    DIR* dir = 0;
    dir = opendir(new_p.c_str());
    if (dir == 0) {
      std::string t = "mkdir " + new_p;
      char a[t.size() + 1];
      strcpy(a, t.c_str());
      system(a);
    }
    std::ofstream newFile;
    std::string fileName = caminho;
    newFile.open(fileName, std::ios::trunc);
    newFile << cabecalho << std::endl;
    newFile << dados << std::endl;
    newFile << rodape << std::endl;
    newFile.close();
  } catch (const std::ios_base::failure& e) {
    std::cerr << e.what() << '\n';
  }
}

/**
 * @brief Crie um objeto Cabecalho
 *
 */
void Dashboard::createCabecalho(void) {
  cabecalho = "<!DOCTYPE HTML>";
  cabecalho += "\n";
  cabecalho += "<html>";
  cabecalho += "\n";
  cabecalho += "<head>";
  cabecalho += "\n";
  cabecalho += "<script>";
  cabecalho += "\n";
  cabecalho += "window.onload = function () {";
  cabecalho += "\n";
  cabecalho += "var chart = new CanvasJS.Chart('chartContainer', {";
  cabecalho += "\n";
  cabecalho += "zoomEnabled: true,";
  cabecalho += "\n";
  cabecalho += "animationEnabled: true,";
  cabecalho += "\n";
  cabecalho += "theme: 'light2',";
  cabecalho += "\n";
  cabecalho += "exportEnabled: true,";
  cabecalho += "\n";
  cabecalho += "title: {";
  cabecalho += "\n";
  cabecalho += "text: '" + nomeGrafico + "'";
  cabecalho += "\n";
  cabecalho += "},";
  cabecalho += "\n";
  cabecalho += "subtitles: [{";
  cabecalho += "\n";
  cabecalho += "text: ''";
  cabecalho += "\n";
  cabecalho += "}],";
  cabecalho += "\n";
  cabecalho += "axisX: {";
  cabecalho += "\n";
  cabecalho += "valueFormatString: 'DD.MM.YYYY HH:mm'";
  cabecalho += "\n";
  cabecalho += "},";
  cabecalho += "\n";
  cabecalho += "axisY: {";
  cabecalho += "\n";
  cabecalho += "includeZero: false,";
  cabecalho += "\n";
  cabecalho += "prefix: '',";
  cabecalho += "\n";
  cabecalho += "title: 'Pip',";
  cabecalho += "\n";
  cabecalho += "prefix: '',";
  cabecalho += "\n";
  cabecalho += "gridDashType: 'dot'";
  cabecalho += "\n";
  cabecalho += "},";
  cabecalho += "\n";
  cabecalho += "toolTip: {";
  cabecalho += "\n";
  cabecalho += "shared: true";
  cabecalho += "\n";
  cabecalho += "},";
  cabecalho += "\n";
  cabecalho += "legend: {";
  cabecalho += "\n";
  cabecalho += "reversed: true,";
  cabecalho += "\n";
  cabecalho += "cursor: 'pointer',";
  cabecalho += "\n";
  cabecalho += "itemclick: toggleDataSeries";
  cabecalho += "\n";
  cabecalho += "},";
  cabecalho += "\n";
}

/**
 * @brief Crie um objeto Dados
 *
 * @param new_dados Dados
 */
void Dashboard::createDados(std::vector<Candlestick>* new_dados) {
  // putenv(TimeZone.data());
  dados = "data: [{";
  dados += "\n";
  dados += "type: 'candlestick',";
  dados += "\n";
  dados += "showInLegend: true,";
  dados += "\n";
  dados += "name: 'Stock Price',";
  dados += "\n";
  dados += "risingColor: 'green',";
  dados += "\n";
  dados += "fallingColor: 'red',";
  dados += "\n";
  dados += "yValueFormatString: '#########.#########',";
  dados += "\n";
  dados += "xValueFormatString: 'DD.MM.YYYY HH:mm',";
  dados += "\n";
  dados += "dataPoints: [";
  dados += "\n";
  for (auto i : *new_dados) {
    if (*i.getStatus()) {
      dados += "{ x: new Date(";
      dados += std::to_string(*i.getDate() * 1000);
      dados += "), y: [";
      dados += std::to_string(*i.getOpen());
      dados += ", ";
      dados += std::to_string(*i.getHigh());
      dados += ", ";
      dados += std::to_string(*i.getLow());
      dados += ", ";
      dados += std::to_string(*i.getClose());
      dados += "], ";
      if (*i.getType() == 0) {
        dados += "color: 'green'";
      } else {
        if (*i.getType() == 1) {
          dados += "color: 'red'";
        } else {
          if (*i.getType() == 2) {
            dados += "color: 'black'";
          } else {
            throw "ERRO! ao criar gráfico tipo de vela inválido";
          }
        }
      }
      dados += " },\n";
    }
  }
  dados.pop_back();
  dados.pop_back();
  dados += "\n";
  dados += "]}]";  // naõ esquecer da virgula ao adicionar
  dados += "\n";
}

/**
 * @brief Crie um objeto Rodape
 *
 */
void Dashboard::createRodape(void) {
  rodape = "});";
  rodape += "\n";
  rodape += "chart.render();";
  rodape += "\n";
  rodape += "function toggleDataSeries(e) {";
  rodape += "\n";
  rodape +=
      "if (typeof (e.dataSeries.visible) === 'undefined' || "
      "e.dataSeries.visible) {";
  rodape += "\n";
  rodape += "e.dataSeries.visible = false;";
  rodape += "\n";
  rodape += "} else {";
  rodape += "\n";
  rodape += "e.dataSeries.visible = true;";
  rodape += "\n";
  rodape += "}";
  rodape += "\n";
  rodape += "e.chart.render();";
  rodape += "\n";
  rodape += "}";
  rodape += "\n";
  rodape += "}";
  rodape += "\n";
  rodape += "</script>";
  rodape += "\n";
  rodape += "</head>";
  rodape += "\n";
  rodape += "<body>";
  rodape += "\n";
  rodape +=
      "<div id='chartContainer' style='height: 100%; width: 100%;'></div>";
  rodape += "\n";
  rodape +=
      "<script type='text/javascript' "
      "src='https://canvasjs.com/assets/script/canvasjs.min.js'></script>";
  rodape += "\n";
  rodape += "</body>";
  rodape += "\n";
  rodape += "</html>";
  rodape += "\n";
}