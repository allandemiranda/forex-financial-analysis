/**
 * @file ZoneReversal.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos da classe ZoneReversal
 * @version 0.1
 * @date 18-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "ZoneReversal.hpp"
#include <algorithm>
#include "Candlestick.hpp"

/**
 * @brief Construa um novo objeto Zone Reversal:: Zone Reversal
 *
 * @param chart_a Gráfico
 * @param zoneSize Tamanho da zona
 * @param normalizador Número de normalização para gráfico de tendência
 */
ZoneReversal::ZoneReversal(Chart* chart_a, pip_t zoneSize,
                           unsigned int normalizador) {
  setSizeOfZones(&zoneSize);

  LinePrice grafico_tendencia(chart_a, normalizador, "Zone Reversal");

  std::vector<price_t> valores_unicos;
  for (auto i : grafico_tendencia.linha) {
    valores_unicos.push_back(*i.getPrice());
  }
  valores_unicos.shrink_to_fit();
  std::sort(valores_unicos.begin(), valores_unicos.end());
  auto last = std::unique(valores_unicos.begin(), valores_unicos.end());
  valores_unicos.erase(last, valores_unicos.end());
  valores_unicos.shrink_to_fit();

  price_t half_zoneSize_price = *Pip(*getSizeOfZones() / 2).getPrice();

#pragma omp parallel
  {
#pragma omp for
    for (unsigned long i = 0; i < valores_unicos.size(); ++i) {
      price_t menor = valores_unicos.at(i) - half_zoneSize_price;
      price_t maior = valores_unicos.at(i) + half_zoneSize_price;
      unsigned long poder = 0;
      for (unsigned long j = 0; j < grafico_tendencia.linha.size(); ++j) {
        if ((*grafico_tendencia.linha.at(j).getPrice() >= menor) and
            (*grafico_tendencia.linha.at(j).getPrice() <= maior)) {
          ++poder;
        }
      }
      if (poder > 1) {
        Zone temporaria(&maior, &menor, &poder,
                        chart_a->chart.front().getDate(),
                        chart_a->chart.back().getDate());
#pragma omp critical
        { zones.push_back(temporaria); }
      }
    }
  }

  std::sort(zones.begin(), zones.end());
}

ZoneReversal::ZoneReversal(Chart* chart_a, pip_t zoneSize,
                           unsigned int normalizador, time_t dataInicial,
                           time_t dataFinal) {
  setSizeOfZones(&zoneSize);

  LinePrice grafico_tendencia(chart_a, normalizador, "Zone Reversal");

  std::vector<price_t> valores_unicos;
  for (auto i : grafico_tendencia.linha) {
    valores_unicos.push_back(*i.getPrice());
  }
  valores_unicos.shrink_to_fit();
  std::sort(valores_unicos.begin(), valores_unicos.end());
  auto last = std::unique(valores_unicos.begin(), valores_unicos.end());
  valores_unicos.erase(last, valores_unicos.end());
  valores_unicos.shrink_to_fit();

  price_t half_zoneSize_price = *Pip(*getSizeOfZones() / 2).getPrice();

#pragma omp parallel
  {
#pragma omp for
    for (unsigned long i = 0; i < valores_unicos.size(); ++i) {
      price_t menor = valores_unicos.at(i) - half_zoneSize_price;
      price_t maior = valores_unicos.at(i) + half_zoneSize_price;
      unsigned long poder = 0;
      for (unsigned long j = 0; j < grafico_tendencia.linha.size(); ++j) {
        if ((*grafico_tendencia.linha.at(j).getPrice() >= menor) and
            (*grafico_tendencia.linha.at(j).getPrice() <= maior)) {
          if ((*grafico_tendencia.linha.at(j).getDate() >= dataInicial) and
              (*grafico_tendencia.linha.at(j).getDate() <= dataFinal)) {
            ++poder;
          }
        }
      }
      if (poder > 1) {
        Zone temporaria(&maior, &menor, &poder, &dataInicial, &dataFinal);
#pragma omp critical
        { zones.push_back(temporaria); }
      }
    }
  }

  std::sort(zones.begin(), zones.end());
}

/**
 * @brief Destrua o objeto Zone Reversal:: Zone Reversal
 *
 */
ZoneReversal::~ZoneReversal() {}

/**
 * @brief Defina o objeto Size Of Zones
 *
 * @param new_size Tamanho da zona (número impar)
 */
void ZoneReversal::setSizeOfZones(pip_t* new_size) {
  if (*new_size % 2 == 0) {
    throw "ERRO! Determine um númro impar para o tamanho da zona";
  } else {
    sizeOfZones = *new_size;
  }
}

/**
 * @brief Obter o objeto Size Of Zones
 *
 * @return pip_t Tamanho da zona
 */
pip_t* ZoneReversal::getSizeOfZones(void) { return &sizeOfZones; }