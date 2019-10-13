/**
 * @file Line.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos da classe Line
 * @version 0.1
 * @date 11-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Line.hpp"

/**
 * @brief Construa um novo objeto Line:: Line
 *
 * @param date Ponteiro da Data do ponto
 * @param price Ponteiro da Cotação no ponto
 */
Line::Line(time_t* date, pip_t* price) {
  setDate(date);
  setPrice(price);
}

/**
 * @brief Destrua o objeto Line:: Line
 *
 */
Line::~Line(void) {}

/**
 * @brief Obter o objeto Date
 *
 * @return time_t* Data do ponto
 */
time_t* Line::getDate(void) { return &date; }

/**
 * @brief Obter o objeto Price
 *
 * @return pip_t* Cotação do ponto
 */
pip_t* Line::getPrice(void) { return &price; }

/**
 * @brief Defina o objeto Date
 *
 * @param new_date Data do ponto
 */
void Line::setDate(time_t* new_date) { date = *new_date; }

/**
 * @brief Defina o objeto Price
 *
 * @param new_price Cotação do ponto
 */
void Line::setPrice(pip_t* new_price) { price = *new_price; }