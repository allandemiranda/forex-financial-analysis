/**
 * @file ChartGoogle.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos da classe ChartGoogle
 * @version 0.1
 * @date 02-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include <dirent.h>
#include <ChartGoogle.hpp>
#include <cstring>
#include <ctime>
#include <fstream>  // std::ifstream, std::ofstream
#include <iomanip>
#include <iostream>  // std::cerr
#include <string>    // std::string
#include <vector>    // std::vector

/**
 * @brief Construa um novo objeto Chart Google:: Chart Google
 *
 * @param data Dados do gráfico
 * @param opitions_s opções adicionais
 */
ChartGoogle::ChartGoogle(Chart &data, std::string opitions_s,
                         std::string fileName) {
  setNameChart(data.getNameChart() + " " + data.getChartTimeString());
  setOpitions(opitions_s);
  save(write(data, header, opitions, footer), fileName);
}

/**
 * @brief Destrua o objeto Chart Google:: Chart Google
 *
 */
ChartGoogle::~ChartGoogle(void) {}

/**
 * @brief escrever arquivo html
 *
 * @param data Banco de dados
 * @param cabecalho Pré definido
 * @param opcoes Opçẽos do gráfico
 * @param rodape Pré definido
 * @return std::string Html final
 */
std::string ChartGoogle::write(Chart &data, std::string cabecalho,
                               std::string opcoes, std::string rodape) {
  std::string html;
  putenv(TimeZone.data());
  html = cabecalho;
  html += "var data = google.visualization.arrayToDataTable([";
  for (auto i : data.getChart()) {
    html += "['";
    char mbstr[100];
    std::strftime(mbstr, sizeof(mbstr), "%c", std::localtime(i.getDate));
    html += mbstr;
    html += "']";
    html += ",";
    html += std::to_string(i.getLow());
    html += ",";
    html += std::to_string(i.getOpen());
    html += ",";
    html += std::to_string(i.getClose());
    html += ",";
    html += std::to_string(i.getHigh());
    html += "],";
  }
  html.pop_back();
  html += "], true);";
  html += opitions;
  html += rodape;
  return html;
}

/**
 * @brief Onde salvar página html
 *
 * @param html HTML
 * @param path Nome do arquivo
 */
void ChartGoogle::save(std::string html, std::string path) {
  try {
    char c = '/';
    std::string buff{""};
    std::vector<std::string> v;
    for (auto n : path) {
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
    DIR *dir = 0;
    struct dirent *entrada = 0;
    unsigned char isFile = 0x8;
    dir = opendir(new_p.c_str());
    if (dir == 0) {
      std::string t = "mkdir " + new_p;
      char a[t.size() + 1];
      strcpy(a, t.c_str());
      system(a);
    }
    std::ofstream newFile;
    std::string fileName = path;
    newFile.open(fileName, std::ios::trunc);
    newFile << html << std::endl;
    newFile.close();
  } catch (const std::ios_base::failure &e) {
    std::cerr << e.what() << '\n';
  }
}

/**
 * @brief Defina o objeto Opitions
 *
 * @param new_opitions Opções adicionais
 */
void ChartGoogle::setOpitions(std::string new_opitions) {
  if (opitions != "") {
    std::string t_opitions_n;
    t_opitions_n = "var options = {";
    t_opitions_n += "legend: '";
    t_opitions_n += getNameChart();
    t_opitions_n += "',";
    t_opitions_n +=
        "candlestick: {"
        "fallingColor: { strokeWidth: 0, fill: '#a52714' },"
        "risingColor: { strokeWidth: 0, fill: '#0f9d58' }"
        "},";
    t_opitions_n += new_opitions;
    t_opitions_n.pop_back();
    t_opitions_n += "};";
    opitions = t_opitions_n;
  } else {
    std::string t_opitions_n;
    t_opitions_n = "var options = {";
    t_opitions_n += "legend: '";
    t_opitions_n += getNameChart();
    t_opitions_n += "',";
    t_opitions_n +=
        "candlestick: {"
        "fallingColor: { strokeWidth: 0, fill: '#a52714' },"
        "risingColor: { strokeWidth: 0, fill: '#0f9d58' }"
        "},";
    t_opitions_n.pop_back();
    t_opitions_n += "};";
    opitions = t_opitions_n;
  }
}

/**
 * @brief Obter o objeto Opitions
 *
 * @return std::string Opições
 */
std::string ChartGoogle::getOpitions(void) { return opitions; }

/**
 * @brief Obter o objeto Name Chart
 *
 * @return std::string Título do gráfico
 */
std::string ChartGoogle::getNameChart(void) { return nameChart; }

/**
 * @brief Defina o objeto Name Chart
 *
 * @param name Título do gráfico
 */
void ChartGoogle::setNameChart(std::string name) { nameChart = name; }