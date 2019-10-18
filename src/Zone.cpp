/**
 * @file Zone.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos para classe Zone
 * @version 0.1
 * @date 18-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Zone.hpp"

/**
 * @brief Construa um novo objeto Zone:: Zone
 *
 * @param upLine Preço linha superior da zona
 * @param downLine Preço da linha inferior da zona
 * @param long Quantidade de ocorrẽncias
 */
Zone::Zone(pip_t* upLine, pip_t* downLine, unsigned long* power) {
#pragma omp parallel sections
  {
#pragma omp section
    { setUpLine(upLine); }
#pragma omp section
    { setDownLine(downLine); }
  }
#pragma omp parallel sections
  {
#pragma omp section
    { setSize(); }
#pragma omp section
    { setPower(power); }
  }
}

/**
 * @brief Destrua o objeto Zone:: Zone
 *
 */
Zone::~Zone(void) {}

/**
 * @brief Obter o objeto Up Line
 *
 * @return pip_t* Preço da linha superior da zona
 */
pip_t* Zone::getUpLine(void) { return &upLine; }

/**
 * @brief Obter o objeto Down Line
 *
 * @return pip_t* Preço da linha inferior da zona
 */
pip_t* Zone::getDownLine(void) { return &downLine; }
/**
 * @brief Obter o objeto Size
 *
 * @return pip_t* Altura (tamanho) da zona
 */
pip_t* Zone::getSize(void) { return &size; }

/**
 * @brief Obter o objeto Power
 *
 * @return unsigned* getPower Quantidade de reversões de tendências na zona
 */
unsigned long* Zone::getPower(void) { return &power; }

/**
 * @brief Defina o objeto Up Line
 *
 * @param price Preço da linha
 */
void Zone::setUpLine(pip_t* price) { upLine = *price; }

/**
 * @brief Defina o objeto Down Line
 *
 * @param price Preço da linha
 */
void Zone::setDownLine(pip_t* price) { downLine = *price; }

/**
 * @brief Defina o objeto Size
 *
 * @param priceUp Preço da linha superior
 * @param priceDown Preço da linha inferior
 */
void Zone::setSize(pip_t* priceUp, pip_t* priceDown) {
  size = *priceDown - *priceUp;
}

/**
 * @brief Defina o objeto Size
 *
 */
void Zone::setSize(void) { size = *getDownLine() - *getUpLine(); }

/**
 * @brief Defina o objeto Power
 *
 * @param long Quantidade de vezes que a zona está na reversão de tendência
 */
void Zone::setPower(unsigned long* event) { power = *event; }