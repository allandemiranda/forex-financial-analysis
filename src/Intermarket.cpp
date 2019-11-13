/**
 * @file Intermarket.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos para classe Intermarket
 * @version 0.1
 * @date 13-11-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Intermarket.hpp"
#include <iostream>

/**
 * @brief Construa um novo objeto Intermarket:: Intermarket
 *
 * @param grafico Gráfico a ser comparado
 * @param lista_de_graficos Lista dos gráficos a comparar
 * @param tempo_usado tempo usado nas comparações
 */
Intermarket::Intermarket(Chart* grafico, ReadingFolderFiles* lista_de_graficos,
                         std::string tempo_usado) {
  graficoPrincipal = grafico;
  lista = lista_de_graficos;
  tempo = tempo_usado;
}

/**
 * @brief Destrua o objeto Intermarket:: Intermarket
 *
 */
Intermarket::~Intermarket(void) {}

/**
 * @brief Obter o objeto Results
 *
 */
void Intermarket::getResults(void) {
  std::string tempoReal = tempo;
  for (unsigned int i = 0; i < lista->list_path.size(); ++i) {
    Chart grafico(&lista->list_path.at(i), &lista->list_path.at(i), &tempoReal);
    tempoReal = tempo;
    unsigned int up_up = 0;
    unsigned int up_down = 0;
    unsigned int down_up = 0;
    unsigned int down_down = 0;
    unsigned int analisados = 0;
    for (unsigned int j = 0; j < graficoPrincipal->chart.size(); ++j) {
      if (*graficoPrincipal->chart.at(j).getStatus() and
          (*graficoPrincipal->chart.at(j).getType() != 2)) {
        for (unsigned int k = 0; k < grafico.chart.size(); ++k) {
          if (*grafico.chart.at(k).getStatus() and
              (*grafico.chart.at(k).getType() != 2)) {
            if (*graficoPrincipal->chart.at(j).getType() == 0) {
              if (*grafico.chart.at(k).getType() == 0) {
                ++up_up;
              } else {
                ++up_down;
              }
            } else {
              if (*grafico.chart.at(k).getType() == 0) {
                ++down_up;
              } else {
                ++down_down;
              }
            }
            ++analisados;
          }
        }
      }
    }
    std::cout << std::endl;
    std::cout << *grafico.getNameChart() << " -> " << lista->list_path.at(i)
              << std::endl;
    std::cout << std::endl;
    std::cout << "UP -> UP: " << up_up << "  "
              << (float)((up_up / analisados) * 100) << "%" << std::endl;
    std::cout << "UP -> DOWN: " << up_down << "  "
              << (float)((up_down / analisados) * 100) << "%" << std::endl;
    std::cout << "DOWN -> UP: " << down_up << "  "
              << (float)((down_up / analisados) * 100) << "%" << std::endl;
    std::cout << "DOWN -> DOWN: " << down_down << "  "
              << (float)((down_down / analisados) * 100) << "%" << std::endl;
    std::cout << "ANALISADOS: " << analisados << std::endl;
    std::cout << std::endl;
    std::cout << "  --------------------  " << std::endl;
    std::cout << std::endl;
  }
}