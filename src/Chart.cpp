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

/**
 * @brief Construa um novo objeto Chart:: Chart
 *
 * @param data_base Banco de velas
 * @param time_chart Tempo do gráfico
 * @param name_chart Nome do gráfico
 */
Chart::Chart(DataBase data_base, std::string time_chart,
             std::string name_chart) {}

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
void setNameChart(std::string name_chart) {}

/**
 * @brief Defina o objeto Chart Time String
 *
 * @param time Tempo do gráfico (M1, H2, W1, M1, Y1)
 */
void setChartTimeString(std::string time) {}

/**
 * @brief Defina o objeto Chart Time
 *
 * @param time Tempo do gráfico (M1, H2, W1, M1, Y1)
 */
void setChartTime(std::string time) {}

/**
 * @brief Converter tempo gráfico em string para segundos
 *
 * @param time Tempo gráfico em strings
 * @return time_t Tempo em segundos
 */
time_t convertStringTimeToSeconds(std::string time) {}

/**
 * @brief Obter o objeto Older Candle Time
 *
 * @param data_base Banco de velas
 * @param tempo Tempo da vela requerida
 * @return time_t Data da vela mais velha
 */
time_t getOlderCandleTime(DataBase& data_base, time_t tempo) {}

/**
 * @brief Criar uma vela VOID
 *
 * @param time Tempo da vela em segundos
 * @param date Data da abertura da vela em Epoch
 * @return Candlestick Nova vela VOID
 */
Candlestick newVoidCandle(time_t time, time_t date) {}

/**
 * @brief Obter o objeto Chart Time
 *
 * @return time_t Tempo gráfico em segundos
 */
time_t getChartTime(void) {}

/**
 * @brief Obter o objeto Chart Time String
 *
 * @return std::string Tempo gráfico em String
 */
std::string getChartTimeString(void) {}

/**
 * @brief Obter o objeto Chart
 *
 * @return chart_t Vetor gráfico
 */
chart_t getChart(void) {}

/**
 * @brief Obter o objeto Name Chart
 *
 * @return std::string Nome do gráfico
 */
std::string getNameChart(void) {}