/**
 * @file Pip.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos para a classe Pip
 * @version 0.1
 * @date 18-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Pip.hpp"

/**
 * @brief Obter o objeto Price
 *
 * @return price_t* Valor
 */
price_t* Pip::getPrice(void) { return &valor; }

/**
 * @brief Obter o objeto Pip
 *
 * @return pip_t* Valor
 */
pip_t* Pip::getPip(void) { return &pip; }

/**
 * @brief Obter o objeto Pip J P Y
 *
 * @return pip_JPY_t* Valor
 */
pip_JPY_t* Pip::getPipJPY(void) { return &pipJPY; }

/**
 * @brief Construa um novo objeto Pip:: Pip
 *
 * @param value valor
 */
Pip::Pip(price_t value) {
  valor = value;
  pip = value / 0.0001;
  pipJPY = value / 0.01;
}

/**
 * @brief Construa um novo objeto Pip:: Pip
 *
 * @param value valor
 * @param a false -> JPY
 */
Pip::Pip(pip_t value, bool a = true) {
  if (a) {
    valor = value * 0.0001;
    pip = value;
    pipJPY = (value * 0.0001) / 0.01;
  } else {
    valor = value * 0.01;
    pip = (value * 0.01) / 0.0001;
    pipJPY = value;
  }
}

/**
 * @brief Destrua o objeto Pip:: Pip
 *
 */
Pip::~Pip(void) {}