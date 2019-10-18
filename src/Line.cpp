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
 * @param novo_nome Nome da linha
 */
Line::Line(std::string novo_nome) {
  nome = novo_nome;
  nome.shrink_to_fit();
}

/**
 * @brief Destrua o objeto Line:: Line
 *
 */
Line::~Line(void) {}

/**
 * @brief Construa um novo objeto Line:: Line
 * 
 */
Line::Line(void) {
  nome = "SEM NOME";
  nome.shrink_to_fit();
}

/**
 * @brief Defina o objeto Nome
 * 
 * @param novo_nome Nome da linha
 */
void Line::setNome(std::string novo_nome){
  nome = novo_nome;
  nome.shrink_to_fit();
}