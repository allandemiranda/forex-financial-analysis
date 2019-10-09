/**
 * @file Chart.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos da classe Chart
 * @version 0.1
 * @date 04-10-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Chart.hpp"
#include <omp.h>
#include <algorithm>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>

/**
 * @brief Construa um novo objeto Chart:: Chart
 *
 * @param file_name Nome do arquivo
 * @param chart_name Nome do gráfico
 * @param chart_time Tempo do grafico
 */
Chart::Chart(std::string* file_name, std::string* chart_name,
             std::string* chart_time) {
  setTimeChart(chart_time);
  setNameChart(chart_name);
  /****/
  std::string tZ = "TZ=America/Recife";
  putenv(tZ.data());
  std::time_t t = std::time(nullptr);
  std::cout << "Iniciando Gráfico: " << std::endl;
  std::cout << "  "
            << "Arquivo: " << *file_name << std::endl;
  std::cout << "  "
            << "Início às " << std::put_time(std::localtime(&t), "%T %D %Z")
            << std::endl;
  std::cout << "  "
            << "Lendo arquivo..." << std::endl;
  /****/
  openFile(file_name);
  /****/
  t = std::time(nullptr);
  std::cout << "  "
            << "Lido " << fileVector.size() << " linhas do arquivo às "
            << std::put_time(std::localtime(&t), "%T %D %Z") << std::endl;
  std::cout << "  "
            << "Limpando linhas desnecessárias..." << std::endl;
  /****/
  cleanOutTime();
  /****/
  t = std::time(nullptr);
  std::cout << "  "
            << "Pós limpesa restaram " << fileVector.size()
            << " linhas do arquivo às "
            << std::put_time(std::localtime(&t), "%T %D %Z") << std::endl;
  std::cout << "  "
            << "Convertendo linhas para Velas..." << std::endl;
  /****/
  convertingToCandlestick();
  /****/
  t = std::time(nullptr);
  std::cout << "  "
            << "Linhas convertidas em " << chart.size() << " Velas às "
            << std::put_time(std::localtime(&t), "%T %D %Z") << std::endl;
  std::cout << "  "
            << "Convertendo Velas para o tempo do gráfico..." << std::endl;
  /****/
  convertingToTime();
  /****/
  putenv(tZ.data());
  t = std::time(nullptr);
  std::cout << "  "
            << "Gráfico pronto com " << chart.size() << " velas às "
            << std::put_time(std::localtime(&t), "%T %D %Z") << std::endl;
  /****/
}

/**
 * @brief Destrua o objeto Chart:: Chart
 *
 */
Chart::~Chart(void) {}

/**
 * @brief Defina o objeto Time Chart
 *
 * Tempos permitidos: "M1", "M2", "M3", "M4", "M5", "M6", "M10", "M12", "M15",
 * "M20", "M20","H1", "H2", "H3", "H4", "H6", "H8", "H12", "D1",  "W1",  "J1",
 * "Y1"
 *
 * @param time Tempo do gráfico
 */
void Chart::setTimeChart(std::string* time) {
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
    for (unsigned long i = 0; i < tempos_permitidos.size(); ++i) {
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
        if (time->at(0) == 'W') {
#pragma omp critical
          {
            time->erase(0, 1);
            time_final =
                (unsigned long)(604800 * (unsigned long)std::stoi(*time));
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
  timeChart = time_final;
}

/**
 * @brief Defina o objeto Name Chart
 *
 * @param name Nome do gráfico
 */
void Chart::setNameChart(std::string* name) { nameChart = *name; }

/**
 * @brief Difidir vetor
 *
 * @param line Linha a ser dividida
 * @param c Caracter divisor
 * @return std::vector<std::string> Vetor dividido
 */
std::vector<std::string> Chart::explode(const std::string* line, char* c) {
  std::string buff{""};
  std::vector<std::string> v;
  for (auto n : *line) {
    if (n != *c) {
      buff += n;
    } else if (n == *c && buff != "") {
      v.push_back(buff);
      v.shrink_to_fit();
      buff = "";
    }
  }
  if (buff != "") {
    v.push_back(buff);
    v.shrink_to_fit();
  }
  return v;
}

/**
 * @brief Abrir arquivo csv
 *
 * @param name_file Nome do arquivo
 */
void Chart::openFile(std::string* name_file) {
  try {
    std::ifstream file(*name_file);
    std::string line;
    bool primeira_linha = true;
    char divisor = static_cast<char>(std::bitset<8>("00001001").to_ulong());
    unsigned long cont = 0;
    while (std::getline(file, line)) {
      if (primeira_linha) {
        primeira_linha = false;
      } else {
        fileVector.push_back(explode(&line, &divisor));
        auto apagar_inicio = fileVector.back().begin();
        std::advance(apagar_inicio, 6);
        fileVector.back().erase(apagar_inicio, fileVector.back().end());
        // for (auto i(0u); i < 3; ++i) {
        //   fileVector.back().pop_back();
        // }
        fileVector.back().shrink_to_fit();
        if ((++cont % 100000) == 0) {
          fileVector.shrink_to_fit();
        }
      }
    }
  } catch (const std::ios_base::failure& e) {
    std::cerr << e.what() << '\n';
  }
  if (fileVector.size() == 0) {
    throw "ERRO! Não foi obtido nenhuma vela do arquivo.";
  }
  fileVector.shrink_to_fit();
}
/**
 * @brief Limpe do velor de arquivo as velas fora do tempo se necessário
 *
 */
void Chart::cleanOutTime(void) {
  if (*getTimeChart() < 86400) {
    int final(-1);
    for (auto i(0u); i < fileVector.size(); ++i) {
      if (fileVector[i][1] == "00:00:00") {
        if (fileVector[i + 1][1] == "00:00:00") {
          final = i;
        } else {
          if (fileVector[i][0] == fileVector[i + 1][0]) {
            break;
          } else {
            final = i;
            break;
          }
        }
      }
    }
    if (final != -1) {
      auto vi = fileVector.begin();
      std::advance(vi, (final + 1));
      fileVector.erase(fileVector.begin(), vi);
    }
    fileVector.shrink_to_fit();
#pragma omp parallel
    {
#pragma omp for
      for (unsigned long i = 0; i < fileVector.size(); ++i) {
        fileVector[i].push_back("60");
        fileVector[i].shrink_to_fit();
      }
    }
  }
}

/**
 * @brief Converte vetor do gráfico para tempo do gráfico
 * Usar antes de finalizar as operações
 *
 */
void Chart::convertingToTime(void) {
  putenv(timeZoneChart.data());
  time_t um_minuto = 60;       // segundos
  time_t uma_hora = 3600;      // segundos
  time_t um_dia = 86400;       // segundos
  time_t uma_semana = 604800;  // segundos
  time_t um_mes = 2592000;     // segundos (30 dias)
  time_t um_ano = 31536000;    // segundos (365 dias)
  bool flag = true;
  if (*getTimeChart() < uma_hora) {
    flag = false;
    time_t data_inicial = *chart.front().getDate();
    time_t data_final = *chart.back().getDate();
    char mbstr_inicial[5];
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%M",
                         std::localtime(&data_inicial))) {
      // Voltar para minuto 00
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      time_a.push_back(mbstr_inicial[1]);
      if (time_a == "00") {
        break;
      } else {
        data_inicial -= (um_minuto);  // Diminua um minuto
      }
    }
    data_final += (um_minuto);  // Aumente um minuto
    // Avançar até o próximo 0 minutos
    char mbstr_final[5];
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%M",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      time_a.push_back(mbstr_final[1]);
      if (time_a == "00") {
        break;
      } else {
        data_final += (um_minuto);  // Aumente um minuto
      }
    }
    convertingToTimeVector(&data_inicial, &data_final);
  }
  if ((*getTimeChart() >= uma_hora) and (*getTimeChart() <= um_dia)) {
    flag = false;
    time_t data_inicial = *chart.front().getDate();
    time_t data_final = *chart.back().getDate();
    char mbstr_inicial[5];
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%M",
                         std::localtime(&data_inicial))) {
      // Voltar para minuto 00
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      time_a.push_back(mbstr_inicial[1]);
      if (time_a == "00") {
        break;
      } else {
        data_inicial -= (um_minuto);  // Diminua um minuto
      }
    }
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%H",
                         std::localtime(&data_inicial))) {
      // Voltar para horas 00
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      time_a.push_back(mbstr_inicial[1]);
      if (time_a == "00") {
        break;
      } else {
        data_inicial -= (uma_hora);  // Diminua uma hora
      }
    }
    data_final += (um_minuto);  // Aumente um minuto
    // Avançar até o próximo 0 minutos
    char mbstr_final[5];
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%M",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      time_a.push_back(mbstr_final[1]);
      if (time_a == "00") {
        break;
      } else {
        data_final += (um_minuto);  // Aumente um minuto
      }
    }
    // Avançar até o próximo 00 horas
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%H",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      time_a.push_back(mbstr_final[1]);
      if (time_a == "00") {
        break;
      } else {
        data_final += (uma_hora);  // Aumente uma hora
      }
    }
    convertingToTimeVector(&data_inicial, &data_final);
  }
  if (*getTimeChart() == uma_semana) {
    flag = false;
    time_t data_inicial = *chart.front().getDate();
    time_t data_final = *chart.back().getDate();
    char mbstr_inicial[5];
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%M",
                         std::localtime(&data_inicial))) {
      // Voltar para minuto 00
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      time_a.push_back(mbstr_inicial[1]);
      if (time_a == "00") {
        break;
      } else {
        data_inicial -= (um_minuto);  // Diminua um minuto
      }
    }
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%H",
                         std::localtime(&data_inicial))) {
      // Voltar para horas 00
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      time_a.push_back(mbstr_inicial[1]);
      if (time_a == "00") {
        break;
      } else {
        data_inicial -= (uma_hora);  // Diminua uma hora
      }
    }
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%w",
                         std::localtime(&data_inicial))) {
      // Voltar para semana 0 -> domingo
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      if (time_a == "0") {
        break;
      } else {
        data_inicial -= (um_dia);  // Diminua um dia
      }
    }
    data_final += (um_minuto);  // Aumente um minuto
    // Avançar até o próximo 0 minutos
    char mbstr_final[5];
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%M",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      time_a.push_back(mbstr_final[1]);
      if (time_a == "00") {
        break;
      } else {
        data_final += (um_minuto);  // Aumente um minuto
      }
    }
    // Avançar até o próximo 00 horas
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%H",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      time_a.push_back(mbstr_final[1]);
      if (time_a == "00") {
        break;
      } else {
        data_final += (uma_hora);  // Aumente uma hora
      }
    }
    // Avançar até o próximo semana 0
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%w",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      if (time_a == "0") {
        break;
      } else {
        data_final += (um_dia);  // Aumente uma hora
      }
    }
    convertingToTimeVector(&data_inicial, &data_final);
  }
  if (*getTimeChart() == um_mes) {
    flag = false;
    time_t data_inicial = *chart.front().getDate();
    time_t data_final = *chart.back().getDate();
    char mbstr_inicial[5];
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%M",
                         std::localtime(&data_inicial))) {
      // Voltar para minuto 00
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      time_a.push_back(mbstr_inicial[1]);
      if (time_a == "00") {
        break;
      } else {
        data_inicial -= (um_minuto);  // Diminua um minuto
      }
    }
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%H",
                         std::localtime(&data_inicial))) {
      // Voltar para horas 00
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      time_a.push_back(mbstr_inicial[1]);
      if (time_a == "00") {
        break;
      } else {
        data_inicial -= (uma_hora);  // Diminua uma hora
      }
    }
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%d",
                         std::localtime(&data_inicial))) {
      // Voltar para dia 01 do mês
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      time_a.push_back(mbstr_inicial[1]);
      if (time_a == "01") {
        break;
      } else {
        data_inicial -= (um_dia);  // Diminua um dia
      }
    }
    data_final += (um_minuto);  // Aumente um minuto
    // Avançar até o próximo 0 minutos
    char mbstr_final[5];
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%M",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      time_a.push_back(mbstr_final[1]);
      if (time_a == "00") {
        break;
      } else {
        data_final += (um_minuto);  // Aumente um minuto
      }
    }
    // Avançar até o próximo 00 horas
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%H",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      time_a.push_back(mbstr_final[1]);
      if (time_a == "00") {
        break;
      } else {
        data_final += (uma_hora);  // Aumente uma hora
      }
    }
    // Avançar até o próximo dia 01 do mês seguinte
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%d",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      time_a.push_back(mbstr_final[1]);
      if (time_a == "01") {
        break;
      } else {
        data_final += (um_dia);  // Aumente uma hora
      }
    }
    convertingToTimeVector(&data_inicial, &data_final);
  }
  if (*getTimeChart() == um_ano) {
    flag = false;
    time_t data_inicial = *chart.front().getDate();
    time_t data_final = *chart.back().getDate();
    char mbstr_inicial[5];
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%M",
                         std::localtime(&data_inicial))) {
      // Voltar para minuto 00
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      time_a.push_back(mbstr_inicial[1]);
      if (time_a == "00") {
        break;
      } else {
        data_inicial -= (um_minuto);  // Diminua um minuto
      }
    }
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%H",
                         std::localtime(&data_inicial))) {
      // Voltar para horas 00
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      time_a.push_back(mbstr_inicial[1]);
      if (time_a == "00") {
        break;
      } else {
        data_inicial -= (uma_hora);  // Diminua uma hora
      }
    }
    while (std::strftime(mbstr_inicial, sizeof(mbstr_inicial), "%j",
                         std::localtime(&data_inicial))) {
      // Voltar para dia 001 do ano
      std::string time_a;
      time_a.push_back(mbstr_inicial[0]);
      time_a.push_back(mbstr_inicial[1]);
      time_a.push_back(mbstr_inicial[2]);
      if (time_a == "001") {
        break;
      } else {
        data_inicial -= (um_dia);  // Diminua um dia
      }
    }
    data_final += (um_minuto);  // Aumente um minuto
    // Avançar até o próximo 0 minutos
    char mbstr_final[5];
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%M",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      time_a.push_back(mbstr_final[1]);
      if (time_a == "00") {
        break;
      } else {
        data_final += (um_minuto);  // Aumente um minuto
      }
    }
    // Avançar até o próximo 00 horas
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%H",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      time_a.push_back(mbstr_final[1]);
      if (time_a == "00") {
        break;
      } else {
        data_final += (uma_hora);  // Aumente uma hora
      }
    }
    // Avançar até o próximo dia 001 do ano seguinte
    while (std::strftime(mbstr_final, sizeof(mbstr_final), "%j",
                         std::localtime(&data_final))) {
      std::string time_a;
      time_a.push_back(mbstr_final[0]);
      time_a.push_back(mbstr_final[1]);
      time_a.push_back(mbstr_final[2]);
      if (time_a == "001") {
        break;
      } else {
        data_final += (um_dia);  // Aumente uma hora
      }
    }
    convertingToTimeVector(&data_inicial, &data_final);
  }
  if (flag) {
    throw "ERRO! Impossivel converter para o tempo necessário";
  }
}

/**
 * @brief Obtenha tempo inicial e final, organize o vetor do gráfico
 *
 * @param data_inicial Data de início da organização
 * @param data_final Data Final da organização
 */
void Chart::convertingToTimeVector(time_t* data_inicial, time_t* data_final) {
  unsigned long numeroInteracoes =
      ((*data_final - *data_inicial) / *getTimeChart());
  std::vector<Candlestick> novo_chart;
#pragma omp parallel
  {
#pragma omp for
    for (unsigned long i = 0; i < numeroInteracoes; ++i) {
      time_t intervalo_inicial = (i * (*getTimeChart())) + (*data_inicial);
      time_t intervalo_final = intervalo_inicial + (*getTimeChart()) - 1;
      auto novo_vt = candleSearch(&chart, intervalo_inicial);
      if (chart.end() == novo_vt) {
        time_t minuto = 60;
        Candlestick temporario_(&minuto, &intervalo_inicial);
        intervalo_inicial += minuto;
        auto vt = candleSearch(&chart, intervalo_inicial);
        while (intervalo_inicial < intervalo_final) {
          if (chart.end() == vt) {
            Candlestick temporario_dois(&minuto, &intervalo_inicial);
            temporario_ = temporario_ + temporario_dois;
            intervalo_inicial += minuto;
          } else {
            temporario_ = temporario_ + *vt;
            intervalo_inicial += *vt->getTime();
          }
          std::advance(vt, 1);
          if (vt == chart.end()) {
            if (*temporario_.getTime() < *getTimeChart()) {
              temporario_.addTime(*getTimeChart() - *temporario_.getTime());
            }
            break;
          }
          if (*vt->getDate() != intervalo_inicial) {
            if (*vt->getDate() >= intervalo_final) {
              if (*temporario_.getTime() < *getTimeChart()) {
                temporario_.addTime(*getTimeChart() - *temporario_.getTime());
              }
              break;
            } else {
              vt = chart.end();
            }
          }
        }
#pragma omp critical
        { novo_chart.push_back(temporario_); }
      } else {
        time_t minuto = 60;
        intervalo_inicial += minuto;
        auto vt = candleSearch(&chart, intervalo_inicial);
        while (intervalo_inicial < intervalo_final) {
          if (chart.end() == vt) {
            Candlestick temporario_dois(&minuto, &intervalo_inicial);
            *novo_vt = *novo_vt + temporario_dois;
            intervalo_inicial += minuto;
          } else {
            *novo_vt = *novo_vt + *vt;
            intervalo_inicial += *vt->getTime();
          }
          std::advance(vt, 1);
          if (vt == chart.end()) {
            if (*novo_vt->getTime() < *getTimeChart()) {
              novo_vt->addTime(*getTimeChart() - *novo_vt->getTime());
            }
            break;
          }
          if (*vt->getDate() != intervalo_inicial) {
            if (*vt->getDate() >= intervalo_final) {
              if (*novo_vt->getTime() < *getTimeChart()) {
                novo_vt->addTime(*getTimeChart() - *novo_vt->getTime());
              }
              break;
            } else {
              vt = chart.end();
            }
          }
        }
#pragma omp critical
        { novo_chart.push_back(*novo_vt); }
      }
    }
  }
#pragma omp parallel sections
  {
#pragma omp section
    { std::sort(novo_chart.begin(), novo_chart.end()); }
#pragma omp section
    {
      chart.clear();
      chart.shrink_to_fit();
    }
  }
  chart = novo_chart;
}

/**
 * @brief Buscar vela pela data
 *
 * @param vetor Vetor de velas
 * @param data Data a procurar
 * @return std::vector<Candlestick>::iterator Ponteiro para o valor achado
 */
std::vector<Candlestick>::iterator Chart::candleSearch(
    std::vector<Candlestick>* vetor, time_t data) {
  std::vector<Candlestick>::iterator it =
      std::lower_bound(vetor->begin(), vetor->end(), data);
  if ((it == vetor->end()) or (*it->getDate() != data)) {
    return vetor->end();
  } else {
    return it;
  }
}

/**
 * @brief Converter Vetor de arquivo em um vetor de velas
 *
 */
void Chart::convertingToCandlestick(void) {
#pragma omp parallel
  {
#pragma omp for
    for (unsigned long i = 0; i < fileVector.size(); ++i) {
      Candlestick nova_vela(&fileVector[i]);
#pragma omp critical
      { chart.push_back(nova_vela); }
    }
  }
  chart.shrink_to_fit();
#pragma omp parallel sections
  {
#pragma omp section
    {
      fileVector.clear();
      fileVector.shrink_to_fit();
    }
#pragma omp section
    { std::sort(chart.begin(), chart.end()); }
  }
  chart.shrink_to_fit();
}

/**
 * @brief Obter o objeto Time Chart
 *
 * @return time_t* Aponta para o tempo do gráfico
 */
time_t* Chart::getTimeChart(void) { return &timeChart; }

/**
 * @brief Obter o objeto Name Chart
 *
 * @return std::string* Aponta para o nome do gráfico
 */
std::string* Chart::getNameChart(void) { return &nameChart; }