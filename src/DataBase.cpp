/**
 * @file DataBase.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos da classe DataBase
 * @version 0.1
 * @date 29-09-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "DataBase.hpp"
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>

/**
 * @brief Construa um novo objeto Data Base:: Data Base
 *
 * @param name_file Caminho do arquivo com os dados do MT5
 */
DataBase::DataBase(std::string name_file) {
  setDBStick(getInformation(name_file));
}

/**
 * @brief Destrua o objeto Data Base:: Data Base
 *
 */
DataBase::~DataBase(void) {}

/**
 * @brief Obter Velas processadas do arquivo MT5
 *
 * @return std::vector<Candlestick> Vetor de velas obtidas
 */
std::vector<Candlestick> DataBase::getDBStick(void) { return DBStick; }

/**
 * @brief Obter o objeto Information
 *
 * @param file_name Nome do arquivo MT5
 * @return std::vector<std::string> Dados obtido do arquivo em formato string
 */
std::vector<std::string> DataBase::getInformation(std::string file_name) {
  std::vector<std::string> text;
  try {
    std::ifstream file(file_name);
    std::string line;
    bool primeira_linha = true;
    while (std::getline(file, line)) {
      if (primeira_linha) {
        primeira_linha = false;
        continue;
      }
      text.push_back(line);
    }
  } catch (const std::ios_base::failure& e) {
    std::cerr << e.what() << '\n';
  }
  if (text.size() == 0) {
    throw "ERRO! Não foi obtido nenhuma vela do arquivo.";
  }
  return text;
}

/**
 * @brief Explodir linha de informações em um vetor de informações
 *
 * @param line Linha com informaçẽos em string
 * @return stick_s_t Vetor de informações em string
 */
stick_s_t DataBase::explode(const std::string line) {
  char c = static_cast<char>(std::bitset<8>("00001001").to_ulong());
  std::string buff{""};
  std::vector<std::string> v;
  for (auto n : line) {
    if (n != c) {
      buff += n;
    } else if (n == c && buff != "") {
      v.push_back(buff);
      buff = "";
    }
  }
  if (buff != "") {
    v.push_back(buff);
  }
  return v;
}

/**
 * @brief Definir Vetor com velas obtidas do arquivo
 *
 * @param data Dados do arquivo já em um vetor
 */
void DataBase::setDBStick(std::vector<std::string> data) {
  bool formato_um_dia = true;
  for (auto i(0u); i < data.size(); ++i) {
    if (formato_um_dia) {
      stick_s_t linha_atual = explode(data[i]);
      stick_s_t linha_seguinte = explode(data[i + 1]);
      if (linha_atual[1] == "00:00:00") {
        if (linha_atual[0] != linha_seguinte[0]) {
          if (linha_atual[1] == linha_seguinte[1]) {
            linha_atual.push_back("86400");
            Candlestick nova_vela(linha_atual);
            DBStick.push_back(nova_vela);
          } else {
            formato_um_dia = false;
            linha_atual.push_back("86400");
            Candlestick nova_vela(linha_atual);
            DBStick.push_back(nova_vela);
          }
        } else {
          if (linha_atual[1] == linha_seguinte[1]) {
            throw "ERRO! Lógica de verificação de tempo se é D1 ou M1";
          } else {
            formato_um_dia = false;
            linha_atual.push_back("60");
            Candlestick nova_vela(linha_atual);
            DBStick.push_back(nova_vela);
          }
        }
      } else {
        formato_um_dia = false;
        linha_atual.push_back("60");
        Candlestick nova_vela(linha_atual);
        DBStick.push_back(nova_vela);
      }
    } else {
      stick_s_t linha_atual = explode(data[i]);
      linha_atual.push_back("60");
      Candlestick nova_vela(linha_atual);
      DBStick.push_back(nova_vela);
    }
  }
}