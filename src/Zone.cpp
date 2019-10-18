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
#include "PointLine.hpp"

/**
 * @brief Construa um novo objeto Zone:: Zone
 *
 * @param upLine Preço linha superior da zona
 * @param downLine Preço da linha inferior da zona
 * @param long Quantidade de ocorrẽncias
 * @param dataInicial Data inicial da zona
 * @param dataFinal Data final da zona
 */
Zone::Zone(price_t* upLine, price_t* downLine, unsigned long* power,
           time_t* dataInicial, time_t* dataFinal) {
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
#pragma omp section
    {
      PointLine a(dataInicial, getUpLine());
      PointLine b(dataFinal, getUpLine());
      linhas[0].linha.push_back(a);
      linhas[0].linha.push_back(b);
      linhas[0].linha.shrink_to_fit();
    }
#pragma omp section
    {
      PointLine c(dataInicial, getDownLine());
      PointLine d(dataFinal, getDownLine());
      linhas[1].linha.push_back(c);
      linhas[1].linha.push_back(d);
      linhas[1].linha.shrink_to_fit();
    }
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
 * @return price_t* Preço da linha superior da zona
 */
price_t* Zone::getUpLine(void) { return &upLine; }

/**
 * @brief Obter o objeto Down Line
 *
 * @return price_t* Preço da linha inferior da zona
 */
price_t* Zone::getDownLine(void) { return &downLine; }
/**
 * @brief Obter o objeto Size
 *
 * @return price_t* Altura (tamanho) da zona
 */
price_t* Zone::getSize(void) { return &size; }

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
void Zone::setUpLine(price_t* price) { upLine = *price; }

/**
 * @brief Defina o objeto Down Line
 *
 * @param price Preço da linha
 */
void Zone::setDownLine(price_t* price) { downLine = *price; }

/**
 * @brief Defina o objeto Size
 *
 * @param priceUp Preço da linha superior
 * @param priceDown Preço da linha inferior
 */
void Zone::setSize(price_t* priceUp, price_t* priceDown) {
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

/**
 * @brief Operador power < power
 *
 * @param a Operado
 * @return true Este < a
 * @return false Este >= a
 */
bool Zone::operator<(Zone& a) { return power < a.power; }

/**
 * @brief Obter o objeto Linha Superior
 *
 * @return Line Linha superior
 */
Line Zone::getLinhaSuperior(void) { return linhas[0]; }

/**
 * @brief Obter o objeto Linha Inferior
 *
 * @return Line Linha inferior
 */
Line Zone::getLinhaInferior(void) { return linhas[1]; }