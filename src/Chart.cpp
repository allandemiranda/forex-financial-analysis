/**
 * @file Chart.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos da classe Chart
 * @version 0.1
 * @date 01-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Chart.hpp"
#include <iostream>
#include <vector>
#include "omp.h"

/**
 * @brief Construa um novo objeto Chart:: Chart
 *
 * @param data_base Banco de velas
 * @param time_chart Tempo do gráfico
 * @param name_chart Nome do gráfico
 */
Chart::Chart(std::vector<Candlestick>* data_base, std::string time_chart,
             std::string* name_chart) {
#pragma omp parallel sections
  {
#pragma omp section
    { setNameChart(name_chart); }
#pragma omp section
    { setChartTime(&time_chart); }
#pragma omp section
    { setChartTimeString(&time_chart); }
  }

  /****/
  std::time_t result = std::time(NULL);
  std::cout << std::asctime(std::localtime(&result)) << " -> Gravando "
            << data_base->size() << " velas no gráfico " << *name_chart
            << std::endl;
  /****/

  // 1 hora = 3600 segundos
  // 1 dia = 86400 segundos
  // 1 semana = 604800 segundos
  // 1 mês (30dias) = 2592000 segundos
  // 1 ano (365dias) = 31536000 segundos

  if (*getChartTime() < (3600)) {  // menor que uma hora
    time_t data_inicial =
        getOlderCandleTime(data_base);  // pegue so barras de 60 segundos
    time_t data_final = getNewestCandleTime(data_base);
    // voltar as 0 minuto
    char mbstr[5];
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_inicial))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_inicial -= (60);  // Diminua um minuto
      }
    }
    // Avançar até o próximo 0 minutos
    data_final += (60);  // Aumente um minuto
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_final))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_final += (60);  // Aumente um minuto
      }
    }
    if (*getChartTime() > 60) {
      putDataBaseOnChartToMaxMinut(data_inicial, data_final, getChartTime(),
                                   data_base);
    } else {
      putDataBaseOnChart(data_inicial, data_final, data_base);
    }
  }

  if ((*getChartTime() < (86400)) and
      (*getChartTime() >= (3600))) {  // menor que um dia maior igual a uma hora
    time_t data_inicial =
        getOlderCandleTime(data_base);  // pegue so barras de 60 segundos
    time_t data_final = getNewestCandleTime(data_base);
    char mbstr[5];
    // voltar as 0 minuto
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_inicial))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_inicial -= (60);  // Diminua um minuto
      }
    }
    // voltar as 00 horas
    while (std::strftime(mbstr, sizeof(mbstr), "%H",
                         std::localtime(&data_inicial))) {
      std::string hora_a;
      hora_a.push_back(mbstr[0]);
      hora_a.push_back(mbstr[1]);
      if (hora_a == "00") {
        break;
      } else {
        data_inicial -= (3600);  // Diminua uma hora
      }
    }
    // Avançar até o próximo 0 minutos
    data_final += (60);  // Aumente um minuto
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_final))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_final += (60);  // Aumente um minuto
      }
    }
    // Avançar até o próximo 00 horas
    while (std::strftime(mbstr, sizeof(mbstr), "%H",
                         std::localtime(&data_final))) {
      std::string hora_a;
      hora_a.push_back(mbstr[0]);
      hora_a.push_back(mbstr[1]);
      if (hora_a == "00") {
        break;
      } else {
        data_final += (60);  // Aumente uma hora
      }
    }
    putDataBaseOnChartToMaxMinut(data_inicial, data_final, getChartTime(),
                                 data_base);
  }

  if (*getChartTime() == (86400)) {  // para um dia
    time_t data_inicial =
        getOlderCandleTime(data_base);  // pegue todas as velas
    time_t data_final = getNewestCandleTime(data_base);
    char mbstr[5];
    // voltar as 0 minuto
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_inicial))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_inicial -= (60);  // Diminua um minuto
      }
    }
    // voltar as 00 horas
    while (std::strftime(mbstr, sizeof(mbstr), "%H",
                         std::localtime(&data_inicial))) {
      std::string hora_a;
      hora_a.push_back(mbstr[0]);
      hora_a.push_back(mbstr[1]);
      if (hora_a == "00") {
        break;
      } else {
        data_inicial -= (3600);  // Diminua uma hora
      }
    }
    // Avançar até o próximo 0 minutos
    data_final += (60);  // Aumente um minuto
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_final))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_final += (60);  // Aumente um minuto
      }
    }
    // Avançar até o próximo 00 horas
    while (std::strftime(mbstr, sizeof(mbstr), "%H",
                         std::localtime(&data_final))) {
      std::string hora_a;
      hora_a.push_back(mbstr[0]);
      hora_a.push_back(mbstr[1]);
      if (hora_a == "00") {
        break;
      } else {
        data_final += (60);  // Aumente uma hora
      }
    }
    putDataBaseOnChartToMaxMinut(data_inicial, data_final, getChartTime(),
                                 data_base);
  }

  if (*getChartTime() == (604800)) {
    time_t data_inicial =
        getOlderCandleTime(data_base);  // pegue todas as velas
    time_t data_final = getNewestCandleTime(data_base);
    char mbstr[5];
    // voltar as 0 minuto
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_inicial))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_inicial -= (60);  // Diminua um minuto
      }
    }
    // voltar as 00 horas
    while (std::strftime(mbstr, sizeof(mbstr), "%H",
                         std::localtime(&data_inicial))) {
      std::string hora_a;
      hora_a.push_back(mbstr[0]);
      hora_a.push_back(mbstr[1]);
      if (hora_a == "00") {
        break;
      } else {
        data_inicial -= (3600);  // Diminua uma hora
      }
    }
    // 0 = Sunday
    while (std::strftime(mbstr, sizeof(mbstr), "%w",
                         std::localtime(&data_inicial))) {
      if (mbstr[0] == '0') {
        break;
      } else {
        data_inicial -= (86400);  // Diminua um dia
      }
    }
    // Avançar até o próximo 0 minutos
    data_final += (60);  // Aumente um minuto
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_final))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_final += (60);  // Aumente um minuto
      }
    }
    // Avançar até o próximo 00 horas
    while (std::strftime(mbstr, sizeof(mbstr), "%H",
                         std::localtime(&data_final))) {
      std::string hora_a;
      hora_a.push_back(mbstr[0]);
      hora_a.push_back(mbstr[1]);
      if (hora_a == "00") {
        break;
      } else {
        data_final += (60);  // Aumente uma hora
      }
    }
    while (std::strftime(mbstr, sizeof(mbstr), "%w",
                         std::localtime(&data_final))) {  // 0 = Sunday
      if (mbstr[0] == '0') {
        break;
      } else {
        data_final += (86400);  // Adicione um dia
      }
    }
    putDataBaseOnChartToMaxMinut(data_inicial, data_final, getChartTime(),
                                 data_base);
  }

  if (*getChartTime() == (2592000)) {  // para 1 mês
    time_t data_inicial = getOlderCandleTime(data_base);
    time_t data_final = getNewestCandleTime(data_base);
    char mbstr[5];
    // voltar as 0 minuto
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_inicial))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_inicial -= (60);  // Diminua um minuto
      }
    }
    // voltar as 00 horas
    while (std::strftime(mbstr, sizeof(mbstr), "%H",
                         std::localtime(&data_inicial))) {
      std::string hora_a;
      hora_a.push_back(mbstr[0]);
      hora_a.push_back(mbstr[1]);
      if (hora_a == "00") {
        break;
      } else {
        data_inicial -= (3600);  // Diminua uma hora
      }
    }
    // dia
    while (std::strftime(mbstr, sizeof(mbstr), "%d",
                         std::localtime(&data_inicial))) {
      std::string dia_a;
      dia_a.push_back(mbstr[0]);
      dia_a.push_back(mbstr[1]);
      if (dia_a == "01") {
        break;
      } else {
        data_inicial -= (86400);  // Diminua um dia
      }
    }
    // Avançar até o próximo 0 minutos
    data_final += (60);  // Aumente um minuto
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_final))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_final += (60);  // Aumente um minuto
      }
    }
    // Avançar até o próximo 00 horas
    while (std::strftime(mbstr, sizeof(mbstr), "%H",
                         std::localtime(&data_final))) {
      std::string hora_a;
      hora_a.push_back(mbstr[0]);
      hora_a.push_back(mbstr[1]);
      if (hora_a == "00") {
        break;
      } else {
        data_final += (60);  // Aumente uma hora
      }
    }
    while (std::strftime(mbstr, sizeof(mbstr), "%d",
                         std::localtime(&data_final))) {
      std::string dia_a;
      dia_a.push_back(mbstr[0]);
      dia_a.push_back(mbstr[1]);
      if (dia_a == "01") {
        break;
      } else {
        data_inicial += (24 * 60 * 60);  // almente um dia
      }
    }
    putDataBaseOnChartToMaxMinut(data_inicial, data_final, getChartTime(),
                                 data_base);
  }

  if (*getChartTime() == (31536000)) {
    time_t data_inicial = getOlderCandleTime(data_base);
    time_t data_final = getNewestCandleTime(data_base);
    char mbstr[5];
    // dia
    // voltar as 0 minuto
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_inicial))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_inicial -= (60);  // Diminua um minuto
      }
    }
    // voltar as 00 horas
    while (std::strftime(mbstr, sizeof(mbstr), "%H",
                         std::localtime(&data_inicial))) {
      std::string hora_a;
      hora_a.push_back(mbstr[0]);
      hora_a.push_back(mbstr[1]);
      if (hora_a == "00") {
        break;
      } else {
        data_inicial -= (3600);  // Diminua uma hora
      }
    }
    // dia
    while (std::strftime(mbstr, sizeof(mbstr), "%d",
                         std::localtime(&data_inicial))) {
      std::string dia_a;
      dia_a.push_back(mbstr[0]);
      dia_a.push_back(mbstr[1]);
      if (dia_a == "01") {
        break;
      } else {
        data_inicial -= (86400);  // Diminua um dia
      }
    }
    // Ano
    while (std::strftime(mbstr, sizeof(mbstr), "%j",
                         std::localtime(&data_inicial))) {
      std::string ano_a;
      ano_a.push_back(mbstr[0]);
      ano_a.push_back(mbstr[1]);
      if (ano_a == "001") {
        break;
      } else {
        data_inicial -= (86400);  // Diminua um dia
      }
    }
    // Avançar até o próximo 0 minutos
    data_final += (60);  // Aumente um minuto
    while (std::strftime(mbstr, sizeof(mbstr), "%M",
                         std::localtime(&data_final))) {
      std::string min_a;
      min_a.push_back(mbstr[0]);
      min_a.push_back(mbstr[1]);
      if (min_a == "00") {
        break;
      } else {
        data_final += (60);  // Aumente um minuto
      }
    }
    // Avançar até o próximo 00 horas
    while (std::strftime(mbstr, sizeof(mbstr), "%H",
                         std::localtime(&data_final))) {
      std::string hora_a;
      hora_a.push_back(mbstr[0]);
      hora_a.push_back(mbstr[1]);
      if (hora_a == "00") {
        break;
      } else {
        data_final += (60);  // Aumente uma hora
      }
    }
    while (std::strftime(mbstr, sizeof(mbstr), "%j",
                         std::localtime(&data_final))) {
      std::string ano_a;
      ano_a.push_back(mbstr[0]);
      ano_a.push_back(mbstr[1]);
      if (ano_a == "001") {
        break;
      } else {
        data_inicial += (86400);  // almente um dia
      }
    }
    putDataBaseOnChartToMaxMinut(data_inicial, data_final, getChartTime(),
                                 data_base);
  }

  /****/
  result = std::time(NULL);
  std::cout << std::asctime(std::localtime(&result)) << " -> Gravados "
            << Chart_Vetor.size() << " velas no gráfico " << *name_chart
            << std::endl;
  /****/
}

/**
 * @brief Transformar um tempo gráfico de 1 minuto apra um tempo gráfico de
 * mais minutos
 *
 * @param data_inicial Data inicial da análise
 * @param data_final Data final da análise
 * @param tempoG Tempo do gráfico fulturo
 */
void Chart::putDataBaseOnChartToMaxMinut(time_t data_inicial, time_t data_final,
                                         time_t* tempoG,
                                         std::vector<Candlestick>* data_base) {
  while (data_inicial < data_final) {
    pip_t new_open;
    pip_t new_close;
    pip_t new_high;
    pip_t new_low;
    bool ainda_void = true;
    time_t nova_data_final = data_inicial + *tempoG;
    time_t tempo_inicial_para_vela = data_inicial;
    while (data_inicial < nova_data_final) {
      if (data_base->size() > 0) {
        if (data_base->front().getDate() < nova_data_final) {
          data_inicial = data_base->front().getDate();
          if (ainda_void) {
#pragma omp parallel sections
            {
#pragma omp section
              { new_open = data_base->front().getOpen(); }
#pragma omp section
              { new_high = data_base->front().getHigh(); }
#pragma omp section
              { new_low = data_base->front().getLow(); }
#pragma omp section
              { new_close = data_base->front().getClose(); }
#pragma omp section
              { ainda_void = false; }
            }
          } else {
#pragma omp parallel sections
            {
#pragma omp section
              {
                if (data_base->front().getHigh() > new_high) {
                  new_high = data_base->front().getHigh();
                }
              }
#pragma omp section
              {
                if (data_base->front().getLow() < new_low) {
                  new_low = data_base->front().getLow();
                }
              }
#pragma omp section
              { new_close = data_base->front().getClose(); }
            }
          }
#pragma omp parallel sections
          {
#pragma omp section
            { data_base->erase(data_base->begin()); }
#pragma omp section
            { data_inicial += 60; }
          }
        } else {
          data_inicial += 60;
        }
      } else {
        data_inicial = nova_data_final;
        break;
      }
    }
#pragma omp parallel sections
    {
#pragma omp section
      {
        if (ainda_void) {
          Chart_Vetor.push_back(
              newVoidCandle(tempoG, &tempo_inicial_para_vela));
        }
      }
#pragma omp section
      {
        if (!ainda_void) {
          Candlestick nova_vela(&tempo_inicial_para_vela, &new_open, &new_close,
                                &new_high, &new_low, tempoG);
          Chart_Vetor.push_back(nova_vela);
        }
      }
    }
  }
  data_base->clear();
  data_base->shrink_to_fit();
}

/**
 * @brief Colcoar velas do banco de dados no chat de forma correta
 *
 * @param data_inicial Data inicial de criação
 * @param data_final Data final de criação
 * @param data_base Banco de dados
 */
void Chart::putDataBaseOnChart(time_t data_inicial, time_t data_final,
                               std::vector<Candlestick>* data_base) {
  time_t tempo_segundos = 60;
  while (data_inicial < data_final) {
    if (data_base->size() > 0) {
      if (data_base->front().getDate() == data_inicial) {
        Chart_Vetor.push_back(data_base->front());
        data_base->erase(data_base->begin());
      } else {
        Chart_Vetor.push_back(newVoidCandle(&tempo_segundos, &data_inicial));
      }
    } else {
      Chart_Vetor.push_back(newVoidCandle(&tempo_segundos, &data_inicial));
    }
    data_inicial += 60;
  }
}

/**
 * @brief Destrua o objeto Chart:: Chart
 *
 */
Chart::~Chart(void) {}

/**
 * @brief Defina o objeto Name Chart
 *
 * @param name_chart Nome do gráfico
 */
void Chart::setNameChart(std::string* name_chart) { name = *name_chart; }

/**
 * @brief Defina o objeto Chart Time String
 *
 * @param time Tempo do gráfico (M1, H2, W1, M1, Y1)
 */
void Chart::setChartTimeString(std::string* time) { chartTime_S = *time; }

/**
 * @brief Defina o objeto Chart Time
 *
 * @param time Tempo do gráfico (M1, H2, W1, M1, Y1)
 */
void Chart::setChartTime(std::string* time) {
  chartTime = convertStringTimeToSeconds(time);
}

/**
 * @brief Converter tempo gráfico em string para segundos
 *
 * @param time Tempo gráfico em strings
 * @return time_t Tempo em segundos
 */
time_t Chart::convertStringTimeToSeconds(std::string* time) {
  std::vector<std::string> tempos_permitidos = {
      "M1", "M2", "M3", "M4", "M5", "M6", "M10", "M12", "M15", "M20", "M20",
      "H1", "H2", "H3", "H4", "H6", "H8", "H12", "D1",  "W1",  "J1",  "Y1"};
  // OBS: J1 = Mês 1
  // 1 hora = 3600 segundos
  // 1 dia = 86400 segundos
  // 1 semana = 604800 segundos
  // 1 mês (30dias) = 2592000 segundos
  // 1 ano (365dias) = 31536000 segundos
  unsigned long time_final = 0;
#pragma omp parallel
  {
#pragma omp for
    for (unsigned int i = 0; i < tempos_permitidos.size(); ++i) {
      if (*time == tempos_permitidos[i]) {
        if (time->at(0) == 'M') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final = (unsigned long)(60 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
        if (time->at(0) == 'H') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final =
                (unsigned long)(3600 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
        if (time->at(0) == 'D') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final =
                (unsigned long)(86400 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
        if (time->at(0) == 'D') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final =
                (unsigned long)(86400 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
        if (time->at(0) == 'J') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final =
                (unsigned long)(2592000 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
        if (time->at(0) == 'Y') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final =
                (unsigned long)(31536000 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
      }
    }
  }
  if (time_final == 0) {
    throw "ERRO! Formato do tempo gráfico está incorreto";
  }
  return time_final;
}

/**
 * @brief Obter o objeto Older Candle Time
 *
 * @param data_base Banco de velas
 * @param tempo Tempo da vela requerida
 * @return time_t Data da vela mais velha
 */
time_t Chart::getOlderCandleTime(std::vector<Candlestick>* data_base) {
  return data_base->front().getDate();
}

/**
 * @brief Obter o objeto Newest Candle Time
 *
 * @param data_base Banco de velas
 * @param tempo Tempo da vela requerida
 * @return time_t Data da vela mais nova
 */
time_t Chart::getNewestCandleTime(std::vector<Candlestick>* data_base) {
  return data_base->back().getDate();
}

/**
 * @brief Criar uma vela VOID
 *
 * @param time Tempo da vela em segundos
 * @param date Data da abertura da vela em Epoch
 * @return Candlestick Nova vela VOID
 */
Candlestick Chart::newVoidCandle(time_t* time, time_t* date) {
  Candlestick new_void_candle(time, date);
  return new_void_candle;
}

/**
 * @brief Obter o objeto Chart Time
 *
 * @return time_t Tempo gráfico em segundos
 */
time_t* Chart::getChartTime(void) { return &chartTime; }

/**
 * @brief Obter o objeto Chart Time String
 *
 * @return std::string* Tempo gráfico em String
 */
std::string* Chart::getChartTimeString(void) { return &chartTime_S; }

/**
 * @brief Obter o objeto Name Chart
 *
 * @return std::string* Nome do gráfico
 */
std::string* Chart::getNameChart(void) { return &name; }