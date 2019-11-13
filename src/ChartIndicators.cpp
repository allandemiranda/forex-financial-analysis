/**
 * @file ChartIndicators.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos para classe ChartIndicators
 * @version 0.1
 * @date 12-11-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "ChartIndicators.hpp"
#include <algorithm>
#include "MovingAverage.hpp"

/**
 * @brief Construa um novo objeto Chart Indicators:: Chart Indicators
 *
 * @param novografico Gráfico usado para gerar os indicadores
 */
ChartIndicators::ChartIndicators(Chart* novografico) {
  setGrafico(novografico);
}

/**
 * @brief Destrua o objeto Chart Indicators:: Chart Indicators
 *
 */
ChartIndicators::~ChartIndicators(void) {}

/**
 * @brief Defina o objeto Grafico
 *
 * @param novo_grafico Gráfico
 */
void ChartIndicators::setGrafico(Chart* novo_grafico) {
  grafico = novo_grafico;
}

/**
 * @brief MACD
 *
 * @param rapido EMA Rápido
 * @param lento EMA Lento
 * @param sinal EMA Sinal
 * @return std::vector<Line> Duas linhas
 */
std::vector<Line> ChartIndicators::MACD(unsigned int rapido, unsigned int lento,
                                        unsigned int sinal) {
  Line linhaRapida("a");
  Line linhaLenta("b");
  std::string nomeLinhaSinal = "Sinal(";
  nomeLinhaSinal += std::to_string(sinal);
  nomeLinhaSinal += ") MACD(";
  nomeLinhaSinal += std::to_string(rapido);
  nomeLinhaSinal += ", ";
  nomeLinhaSinal += std::to_string(lento);
  nomeLinhaSinal += ")";
  Line linhaSinal(nomeLinhaSinal);

#pragma omp parallel sections
  {
#pragma omp section
    {
      linhaRapida.linha = MovingAverage(rapido, grafico).EMA().linha;
      linhaRapida.linha.shrink_to_fit();
    }
#pragma omp section
    {
      linhaLenta.linha = MovingAverage(lento, grafico).EMA().linha;
      linhaLenta.linha.shrink_to_fit();
    }
  }

  std::string nomeLinhaFinal = "MACD ";
  nomeLinhaFinal += "(";
  nomeLinhaFinal += std::to_string(rapido);
  nomeLinhaFinal += ", ";
  nomeLinhaFinal += std::to_string(lento);
  nomeLinhaFinal += ")";
  Line linhaFinal(nomeLinhaFinal);
  if (linhaRapida.linha.size() >= linhaLenta.linha.size()) {
    for (unsigned int i = 0; i < linhaRapida.linha.size(); ++i) {
#pragma omp parallel
      {
#pragma omp for
        for (unsigned int j = 0; j < linhaLenta.linha.size(); ++j) {
          if (*linhaRapida.linha.at(i).getDate() ==
              *linhaLenta.linha.at(j).getDate()) {
            price_t valorFinal = *linhaRapida.linha.at(i).getPrice() -
                                 *linhaLenta.linha.at(j).getPrice();
            linhaFinal.linha.push_back(
                PointLine(linhaRapida.linha.at(i).getDate(), &valorFinal));
#pragma omp cancel for
          }
        }
      }
    }
  } else {
    for (unsigned int i = 0; i < linhaLenta.linha.size(); ++i) {
#pragma omp parallel
      {
#pragma omp for
        for (unsigned int j = 0; j < linhaRapida.linha.size(); ++j) {
          if (*linhaRapida.linha.at(j).getDate() ==
              *linhaLenta.linha.at(i).getDate()) {
            price_t valorFinal = *linhaRapida.linha.at(j).getPrice() -
                                 *linhaLenta.linha.at(i).getPrice();
            linhaFinal.linha.push_back(
                PointLine(linhaRapida.linha.at(j).getDate(), &valorFinal));
#pragma omp cancel for
          }
        }
      }
    }
  }
  linhaFinal.linha.shrink_to_fit();

  if (linhaFinal.linha.size() <= sinal) {
    throw "ERRO! Impossivel de calcular indicador MACD";
  }
  price_t valor_um = 0.0;
  for (unsigned int i = 0; i < sinal; ++i) {
    valor_um += *linhaFinal.linha.at(i).getPrice();
  }
  valor_um = (valor_um / (float)sinal);
  linhaSinal.linha.push_back(
      PointLine(linhaFinal.linha.at(sinal - 1).getDate(), &valor_um));
  linhaSinal.linha.shrink_to_fit();
  price_t F = (2.0 / ((float)sinal + 1.0));
  for (unsigned int i = sinal; i < linhaFinal.linha.size(); ++i) {
    price_t valor_dois = (*linhaFinal.linha.at(i).getPrice() * F) +
                         ((1 - F) * (*linhaSinal.linha.back().getPrice()));
    linhaSinal.linha.push_back(
        PointLine(linhaFinal.linha.at(i).getDate(), &valor_dois));
  }
  linhaSinal.linha.shrink_to_fit();

  return std::vector<Line>{linhaFinal, linhaSinal};
}

/**
 * @brief Stochastic
 *
 * @param K Indicador Stochastic
 * @param D MMS de %K
 * @return std::vector<Line> Linhas de resultado
 */
std::vector<Line> ChartIndicators::Stochastic(unsigned int K, unsigned int D) {
  std::string nomeLinhaFinal = "Stochastic(";
  nomeLinhaFinal += K;
  nomeLinhaFinal += ")";
  Line linhaFinal(nomeLinhaFinal);
  for (unsigned int i = K; i < grafico->chart.size(); ++i) {
    if (*grafico->chart.at(i).getStatus()) {
      price_t menor_valor = *grafico->chart.at(i).getClose();
      int tmp_i = i;
      bool flag = false;
      for (int j = 0; (i - j) > (tmp_i - K); ++j) {
        if(((int)i-j) < 0){
          flag = true;
          break;
        }
        if (*grafico->chart.at(i - j).getStatus()) {
          if (*grafico->chart.at(i - j).getClose() < menor_valor) {
            menor_valor = *grafico->chart.at(i - j).getClose();
          }
        } else {
          --tmp_i;
        }
      }
      if(flag){
        continue;
      }
      price_t maior_valor = *grafico->chart.at(i).getClose();
      tmp_i = i;
      for (int j = 0; (i - j) > (tmp_i - K); ++j) {
        if(((int)i-j) < 0){
          flag = true;
          break;
        }
        if (*grafico->chart.at(i - j).getStatus()) {
          if (*grafico->chart.at(i - j).getClose() > maior_valor) {
            maior_valor = *grafico->chart.at(i - j).getClose();
          }
        } else {
          --tmp_i;
        }
      }
      if(flag){
        continue;
      }
      price_t valorFinal = ((*grafico->chart.at(i).getClose() - menor_valor) /
                            (maior_valor - menor_valor)) *
                           100;
      linhaFinal.linha.push_back(
          PointLine(grafico->chart.at(i).getDate(), &valorFinal));
    }
  }
  linhaFinal.linha.shrink_to_fit();

  std::string nomeLinhaSinal = "D(";
  nomeLinhaSinal += std::to_string(D);
  nomeLinhaSinal += " Stochastic(";
  nomeLinhaSinal += std::to_string(K);
  nomeLinhaSinal += ")";
  Line linhaSinal(nomeLinhaSinal);
#pragma omp parallel
  {
#pragma omp for
    for (unsigned int i = D; i < linhaFinal.linha.size(); ++i) {
      price_t valorFinal = 0.0;
      for (unsigned int j = (i - D); j < i; ++j) {
        valorFinal += *linhaFinal.linha.at(j).getPrice();
      }
      valorFinal = (valorFinal / D);
#pragma omp critical
      {
        linhaSinal.linha.push_back(
            PointLine(linhaFinal.linha.at(i).getDate(), &valorFinal));
      }
    }
  }
  std::sort(linhaSinal.linha.begin(), linhaSinal.linha.end());
  linhaSinal.linha.shrink_to_fit();

  return std::vector<Line>{linhaFinal, linhaSinal};
}

/**
 * @brief RSI
 *
 * @param index Valor de dias
 * @return Line Linha egrada
 */
Line ChartIndicators::RSI(unsigned int index) {
  std::string nomeLinhaFinal = "RSI(";
  nomeLinhaFinal += std::to_string(index);
  nomeLinhaFinal += ")";
  Line linhaFinal(nomeLinhaFinal);

  for (unsigned int i = index; i < grafico->chart.size(); ++i) {
    if (*grafico->chart.at(i).getStatus()) {
      price_t menor_valor = 0.0;
      int tmp_i = i;
      bool flag = false;
      for (int j = 0; (i - j) > (tmp_i - index); ++j) {
        if(((int)i-j) < 0){
          flag = true;
          break;
        }
        if (*grafico->chart.at(i - j).getStatus()) {
          if (*grafico->chart.at(i - j).getType() == 1) {
            menor_valor += *grafico->chart.at(i - j).getClose();
          }
        } else {
          --tmp_i;
        }
      }
      if(flag){
        continue;
      }
      menor_valor = (menor_valor / (float)index);

      price_t maior_valor = 0.0;
      tmp_i = i;
      for (int j = 0; (i - j) > (tmp_i - index); ++j) {
        if(((int)i-j) < 0){
          flag = true;
          break;
        }
        if (*grafico->chart.at(i - j).getStatus()) {
          if (*grafico->chart.at(i - j).getType() == 0) {
            maior_valor += *grafico->chart.at(i - j).getClose();
          }
        } else {
          --tmp_i;
        }
      }
      if(flag){
        continue;
      }
      maior_valor = (maior_valor / (float)index);

      price_t valorFinal = 100-(100/((1+maior_valor)/menor_valor));

      linhaFinal.linha.push_back(
          PointLine(grafico->chart.at(i).getDate(), &valorFinal));
    }
  }

  linhaFinal.linha.shrink_to_fit();
  return linhaFinal;
}