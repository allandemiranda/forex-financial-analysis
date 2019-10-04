/**
 * @file DataBase.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe para obter dados dos arquivos csv
 * @version 0.1
 * @date 29-09-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <string>
#include <vector>
#include "Candlestick.hpp"
#include <ctime>

class DataBase {
 private:
  std::vector<std::vector<std::string>> getInformation(std::string*);
  void setDBStick(std::vector<std::vector<std::string>>*, time_t*);
  stick_s_t explode(const std::string*);
  time_t convertStringTimeToSeconds(std::string*);

 public:
  std::vector<Candlestick> Banco_De_Dados;
  DataBase(std::string*, std::string);
  ~DataBase(void);
};

#endif