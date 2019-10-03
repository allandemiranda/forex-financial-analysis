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

class Dashboard {
 private:
  std::string nomeGrafico;
  std::string cabecalho;
  std::string rodape;
  std::string dados;
  void write(std::string);
  void createDados(std::vector<Candlestick>*);
  void createCabecalho(void);
  void createRodape(void);
  std::string TimeZone = "TZ=America/Recife";

 public:
  Dashboard(std::vector<Candlestick>*, std::string, std::string);
  ~Dashboard(void);
};

#endif