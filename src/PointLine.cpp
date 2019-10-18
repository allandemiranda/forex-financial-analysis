/**
 * @file PointLine.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Arquivo com os métodos da classe PointLine
 * @version 0.1
 * @date 18-10-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "PointLine.hpp"

/**
 * @brief Construa um novo objeto PointLine:: PointLine
 *
 * @param date Ponteiro da Data do ponto
 * @param price Ponteiro da Cotação no ponto
 */
PointLine::PointLine(time_t* date, price_t* price) {
#pragma omp parallel sections
  {
#pragma omp section
    { setDate(date); }
#pragma omp section
    { setPrice(price); }
  }
}

/**
 * @brief Destrua o objeto PointLine:: PointLine
 *
 */
PointLine::~PointLine(void) {}

/**
 * @brief Obter o objeto Date
 *
 * @return time_t* Data do ponto
 */
time_t* PointLine::getDate(void) { return &date; }

/**
 * @brief Obter o objeto Price
 *
 * @return price_t* Cotação do ponto
 */
price_t* PointLine::getPrice(void) { return &price; }

/**
 * @brief Defina o objeto Date
 *
 * @param new_date Data do ponto
 */
void PointLine::setDate(time_t* new_date) { date = *new_date; }

/**
 * @brief Defina o objeto Price
 *
 * @param new_price Cotação do ponto
 */
void PointLine::setPrice(price_t* new_price) { price = *new_price; }

/**
 * @brief Operador <
 *
 * @param a
 * @return true Preço menor
 * @return false Preço maior
 */
bool PointLine::operator<(PointLine& a) { return price < a.price; }