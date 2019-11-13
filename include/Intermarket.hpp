/**
 * @file Intermarket.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe para analisar a interação entre os ativos
 * @version 0.1
 * @date 13-11-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef INTERMARKET_HPP_
#define INTERMARKET_HPP_

#include "Chart.hpp"
#include "ReadingFolderFiles.hpp"

class Intermarket {
 private:
  Chart *graficoPrincipal;
  ReadingFolderFiles *lista;
  std::string tempo;

 public:
  Intermarket(Chart *, ReadingFolderFiles *, std::string);
  ~Intermarket(void);
  void getResults(void);
};

#endif