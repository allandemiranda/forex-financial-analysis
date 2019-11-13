/**
 * @file MovingAverage.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos para classe MovingAverage
 * @version 0.1
 * @date 09-11-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "MovingAverage.hpp"
#include <algorithm>

/**
 * @brief Construa um novo objeto Moving Average:: Moving Average
 *
 * @param NovoNumeroDePeriodo Núemro de periodos da média móvel
 * @param grafico Gráfico
 */
MovingAverage::MovingAverage(long NovoNumeroDePeriodo, Chart* grafico) {
#pragma omp parallel sections
  {
#pragma omp section
    { setGrafico(grafico); }
#pragma omp section
    { setNumPeriodo(&NovoNumeroDePeriodo); }
  }
}

/**
 * @brief Destrua o objeto Moving Average:: Moving Average
 *
 */
MovingAverage::~MovingAverage(void) {}

/**
 * @brief Defina o objeto Num Periodo
 *
 * @param long Número de periodos da média móvel
 */
void MovingAverage::setNumPeriodo(long* numeroPeriodo) {
  numeroDePeriodo = *numeroPeriodo;
}

/**
 * @brief Defina o objeto Num Periodo
 *
 * @return long* getNumPeriodo Número de periodos configurados
 */
long* MovingAverage::getNumPeriodo(void) { return &numeroDePeriodo; }

/**
 * @brief Defina o objeto Grafico
 *
 * @param novoGrafico Grafico a ser analisado e criado linha
 */
void MovingAverage::setGrafico(Chart* novoGrafico) { grafico = novoGrafico; }

/**
 * @brief Obter o objeto Grafico
 *
 * @return Chart* Gráfico
 */
Chart* MovingAverage::getGrafico(void) { return grafico; }

/**
 * @brief Defina o objeto SMA
 *
 * @param vela Vela a ser analisada
 * @return PointLine
 */
PointLine MovingAverage::getSMA(Candlestick* vela) {
  price_t valor = 0.0;
  time_t tempo = *vela->getDate();
  int validos = 0;
  for (int i = 0; i < (int)*getNumPeriodo(); ++i) {
    if (*vela->getStatus()) {
      valor += *vela->getClose();
#pragma omp parallel sections
      {
#pragma omp section
        { --vela; }
#pragma omp section
        { ++validos; }
      }
    } else {
#pragma omp parallel sections
      {
#pragma omp section
        { --vela; }
#pragma omp section
        { --i; }
      }
    }
    if (vela == &getGrafico()->chart.at(1)) {
      break;
    }
  }
  valor = (valor / validos);
  return PointLine(&tempo, &valor);
}

/**
 * @brief SMA
 *
 * @return Line Linha SMA
 */
Line MovingAverage::SMA(void) {
  std::string nomeLinha = "SMA(";
  nomeLinha += std::to_string(*getNumPeriodo());
  nomeLinha += ")";
  Line novaLinha(nomeLinha);
#pragma omp parallel
  {
#pragma omp for
    for (unsigned long i = *getNumPeriodo(); i < getGrafico()->chart.size();
         ++i) {
      if (*getGrafico()->chart.at(i).getStatus()) {
#pragma omp critical
        { novaLinha.linha.push_back(getSMA(&getGrafico()->chart.at(i))); }
      }
    }
  }
  std::sort(novaLinha.linha.begin(), novaLinha.linha.end());
  novaLinha.linha.shrink_to_fit();
  return novaLinha;
}

/**
 * @brief EMA
 *
 * @return Line Linha EMA
 */
Line MovingAverage::EMA(void) {
  std::string nomeLinha = "EMA(";
  nomeLinha += std::to_string(*getNumPeriodo());
   nomeLinha += ")";
  Line novaLinha(nomeLinha);
  price_t F = (2.0 / (*getNumPeriodo() + 1.0));
  unsigned long corretor = 0;
  for (unsigned long i = (*getNumPeriodo() + 1); i < getGrafico()->chart.size();
       ++i) {
    if (*getGrafico()->chart.at(i).getStatus()) {
      if (*getGrafico()->chart.at(i - 1).getStatus()) {
        price_t novoValor =
            (*getGrafico()->chart.at(i).getClose() * F) +
            ((1 - F) * (*getSMA(&getGrafico()->chart.at(i - 1)).getPrice()));
        PointLine novoPonto(getGrafico()->chart.at(i).getDate(), &novoValor);
        novaLinha.linha.push_back(novoPonto);
        corretor = i;
        ++corretor;
        break;
      }
    }
  }
  novaLinha.linha.shrink_to_fit();

  for (unsigned long i = corretor; i < getGrafico()->chart.size(); ++i) {
    if (*getGrafico()->chart.at(i).getStatus()) {
      price_t novoValor = (*getGrafico()->chart.at(i).getClose() * F) +
                          ((1 - F) * (*novaLinha.linha.back().getPrice()));
      PointLine novoPonto(getGrafico()->chart.at(i).getDate(), &novoValor);
      novaLinha.linha.push_back(novoPonto);  
    }
  }
  novaLinha.linha.shrink_to_fit();
  return novaLinha;
}