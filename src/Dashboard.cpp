/**
 * @file Dashboard.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos para Classe Dashboard
 * @version 0.1
 * @date 03-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Dashboard.hpp"
#include <dirent.h>
#include <cstring>
#include <fstream>
#include <iostream>

/**
 * @brief Destrua o objeto Dashboard:: Dashboard
 * 
 */
Dashboard::~Dashboard(void){}

/**
 * @brief Construa um novo objeto Dashboard:: Dashboard
 * 
 * @param titulo Título do gráfico
 * @param arquivo Arquivo onde vai salvar
 * @param dados Dados das velas
 */
Dashboard::Dashboard(std::string* titulo, std::string* arquivo,
                     std::vector<Candlestick>* dados) {
  setTitle(titulo);
  try {    
    std::ofstream newFile;
    std::string fileName = *arquivo;
    newFile.open(fileName, std::ios::trunc);
    newFile << header;
    newFile << scriptHeader;
    newFile << scriptOpitons << std::endl;
    newFile << dataCandleHeader;
    for (long unsigned int i(0); i < dados->size(); ++i) {
      if (*dados->at(i).getStatus()) {
        newFile << "{ x: new Date(";
        newFile << std::to_string(*dados->at(i).getDate() * 1000);
        newFile << "), y: [";
        newFile << std::to_string(*dados->at(i).getOpen());
        newFile << ", ";
        newFile << std::to_string(*dados->at(i).getHigh());
        newFile << ", ";
        newFile << std::to_string(*dados->at(i).getLow());
        newFile << ", ";
        newFile << std::to_string(*dados->at(i).getClose());
        newFile << "], ";
        if (*dados->at(i).getType() == 0) {
          newFile << "color: 'green'";
        } else {
          if (*dados->at(i).getType() == 1) {
            newFile << "color: 'red'";
          } else {
            if (*dados->at(i).getType() == 2) {
              newFile << "color: 'black'";
            } else {
              throw "ERRO! ao criar gráfico tipo de vela inválido";
            }
          }
        }
        newFile << " },\n";
      }
    }
    newFile << dataCandleFooter;
    newFile << scriptFooter;
    newFile << footer;
    newFile.close();
  } catch (const std::ios_base::failure& e) {
    std::cerr << e.what() << '\n';
  }
}

/**
 * @brief Defina o objeto Title
 *
 * @param titulo Título do gráfico
 */
void Dashboard::setTitle(std::string* titulo) {
  scriptOpitons += "title: {\n";
  scriptOpitons += "text: '" + *titulo + "'\n";
  scriptOpitons += "},\n";
}