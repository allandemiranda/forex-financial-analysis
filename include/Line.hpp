/**
 * @file Line.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Criação de linhas
 * @version 0.1
 * @date 11-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef LINE_HPP_
#define LINE_HPP_

#include <string>
#include <vector>
#include "PointLine.hpp"

class Line {
 private:
  std::string nome;

 public:
  void setNome(std::string);
  std::vector<PointLine> linha;
  Line(std::string);
  Line(void);
  ~Line(void);
};

#endif