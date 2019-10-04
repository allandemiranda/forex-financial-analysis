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
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

/**
 * @brief Construa um novo objeto Data Base:: Data Base
 *
 * @param name_file Caminho do arquivo com os dados do MT5
 */
DataBase::DataBase(std::string* name_file, std::string time) {
  /****/
  std::time_t result = std::time(NULL);
  std::cout << std::asctime(std::localtime(&result))
            << " -> Obtendo informações do arquivo " << *name_file << std::endl;
  /****/

  std::vector<std::vector<std::string>> info = getInformation(name_file);
  time_t n_time = convertStringTimeToSeconds(&time);

  /****/
  result = std::time(NULL);
  std::cout << std::asctime(std::localtime(&result)) << " -> Obtida "
            << info.size() << " informações do arquivo " << *name_file
            << std::endl;
  std::cout << std::asctime(std::localtime(&result))
            << " -> Transformando " << info.size() <<" informações do arquivo " << *name_file
            << " em velas" << std::endl;
  /****/

  setDBStick(&info, &n_time);

  /****/
  result = std::time(NULL);
  std::cout << std::asctime(std::localtime(&result)) << " -> Obtida "
            << Banco_De_Dados.size() << " velas do arquivo " << *name_file
            << std::endl;
  /****/
}

/**
 * @brief Destrua o objeto Data Base:: Data Base
 *
 */
DataBase::~DataBase(void) {}

/**
 * @brief Obter o objeto Information
 *
 * @param file_name Nome do arquivo MT5
 * @return std::vector<std::string> Dados obtido do arquivo em formato string
 */
std::vector<std::vector<std::string>> DataBase::getInformation(
    std::string* file_name) {
  std::vector<std::vector<std::string>> text;
  try {
    std::ifstream file(*file_name);
    std::string line;
    bool primeira_linha = true;
    while (std::getline(file, line)) {
      if (primeira_linha) {
        primeira_linha = false;
      } else {
        text.push_back(explode(&line));
      }
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
stick_s_t DataBase::explode(const std::string* line) {
  char c = static_cast<char>(std::bitset<8>("00001001").to_ulong());
  std::string buff{""};
  std::vector<std::string> v;
  for (auto n : *line) {
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
void DataBase::setDBStick(std::vector<std::vector<std::string>>* data,
                          time_t* time) {
  bool formato_um_dia = true;
  while (data->size() != 0) {
    if (formato_um_dia) {
      std::vector<std::string> linha_atual = data->at(0);
      std::vector<std::string> linha_seguinte = data->at(1);
      if (linha_atual[1] == "00:00:00") {
        if (linha_atual[0] != linha_seguinte[0]) {
          if (linha_atual[1] == linha_seguinte[1]) {
            if (*time >= 86400) {
              linha_atual.push_back("86400");
              Candlestick nova_vela(&linha_atual);
              Banco_De_Dados.push_back(nova_vela);
            }
            data->erase(data->begin());
          } else {
#pragma omp parallel sections
            {
#pragma omp section
              { formato_um_dia = false; }
#pragma omp section
              {
                if (*time >= 86400) {
                  linha_atual.push_back("86400");
                  Candlestick nova_vela(&linha_atual);
                  Banco_De_Dados.push_back(nova_vela);
                }
                data->erase(data->begin());
              }
            }
          }
        } else {
          if (linha_atual[1] == linha_seguinte[1]) {
            throw "ERRO! Lógica de verificação de tempo se é D1 ou M1";
          } else {
#pragma omp parallel sections
            {
#pragma omp section
              { formato_um_dia = false; }
#pragma omp section
              {
                linha_atual.push_back("60");
                Candlestick nova_vela(&linha_atual);
                Banco_De_Dados.push_back(nova_vela);
                data->erase(data->begin());
              }
            }
          }
        }
      } else {
#pragma omp parallel sections
        {
#pragma omp section
          { formato_um_dia = false; }
#pragma omp section
          {
            linha_atual.push_back("60");
            Candlestick nova_vela(&linha_atual);
            Banco_De_Dados.push_back(nova_vela);
            data->erase(data->begin());
          }
        }
      }
    } else {
      std::vector<std::string> linha_atual = data->at(0);
      linha_atual.push_back("60");
      Candlestick nova_vela(&linha_atual);
      Banco_De_Dados.push_back(nova_vela);
      data->erase(data->begin());
    }
  }
  data->clear();
  data->shrink_to_fit();
}

/**
 * @brief Converter tempo gráfico em string para segundos
 *
 * @param time Tempo gráfico em strings
 * @return time_t Tempo em segundos
 */
time_t DataBase::convertStringTimeToSeconds(std::string* time) {
  std::vector<std::string> tempos_permitidos = {
      "M1", "M2", "M3", "M4", "M5", "M6", "M10", "M12", "M15", "M20", "M20",
      "H1", "H2", "H3", "H4", "H6", "H8", "H12", "D1",  "W1",  "J1",  "Y1"};
  // OBS: J1 = Mês 1
  // 1 hora = 3600 segundos
  // 1 dia = 86400 segundos
  // 1 semana = 604800 segundos
  // 1 mês (30dias) = 2592000 segundos
  // 1 ano (365dias) = 31536000 segundos
  unsigned long time_final = 0;
#pragma omp parallel
  {
#pragma omp for
    for (unsigned int i = 0; i < tempos_permitidos.size(); ++i) {
      if (*time == tempos_permitidos[i]) {
        if (time->at(0) == 'M') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final = (unsigned long)(60 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
        if (time->at(0) == 'H') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final =
                (unsigned long)(3600 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
        if (time->at(0) == 'D') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final =
                (unsigned long)(86400 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
        if (time->at(0) == 'D') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final =
                (unsigned long)(86400 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
        if (time->at(0) == 'J') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final =
                (unsigned long)(2592000 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
        if (time->at(0) == 'Y') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final =
                (unsigned long)(31536000 * (unsigned long)std::stoi(*time));
          }
#pragma omp cancel for
        }
      }
    }
  }
  if (time_final == 0) {
    throw "ERRO! Formato do tempo gráfico está incorreto";
  }
  return time_final;
}