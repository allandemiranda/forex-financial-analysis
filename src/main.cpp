#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include "Chart.hpp"
#include "Dashboard.hpp"
#include "Line.hpp"
#include "LinePrice.hpp"
#include "Pip.hpp"
#include "ReadingFolderFiles.hpp"
#include "ZoneReversal.hpp"

/**
 * @brief Função Relatório método Long Candle Plus Doji
 * Verifica se o padão é positivo ao ser identificado, com tempo de vida de
 * mais duas velas
 * @param arquivo Arquivo de velas
 * @param tempo Tempo gráfico
 */
void LongCandlePlusDoji(std::string arquivo, std::string tempo) {
  std::string nome = "Long Candle Plus Doji";
  std::string TimeFinalSalvar = tempo;
  Chart grafico(&arquivo, &nome, &tempo);
  struct relato {
    time_t* data;
    price_t ganho;
  };
  std::vector<relato> diferencaPositiva;
  std::vector<relato> diferencaNegativa;
  for (unsigned long i = 0; i < grafico.chart.size() - 4; ++i) {
    if (!*grafico.chart.at(i).getStatus() or
        !*grafico.chart.at(i + 1).getStatus() or
        !*grafico.chart.at(i + 3).getStatus()) {
      continue;
    }
    if (*grafico.chart.at(i).getName() == "WHITE MARUBOZU") {
      if ((*grafico.chart.at(i + 1).getName() == "FOUR PRICE DOJI") or
          (*grafico.chart.at(i + 1).getName() == "DRAGONFLY DOJI") or
          (*grafico.chart.at(i + 1).getName() == "GRAVESTONE DOJI") or
          (*grafico.chart.at(i + 1).getName() == "LONG-LEGGED DOJI")) {
        if (*grafico.chart.at(i).getClose() >
            *grafico.chart.at(i + 3).getClose()) {
          relato finala;
          finala.data = grafico.chart.at(i).getDate();
          finala.ganho = *grafico.chart.at(i).getClose() -
                         *grafico.chart.at(i + 3).getClose();
          diferencaPositiva.push_back(finala);
        } else {
          relato finala;
          finala.data = grafico.chart.at(i).getDate();
          finala.ganho = *grafico.chart.at(i + 3).getClose() -
                         *grafico.chart.at(i).getClose();
          diferencaNegativa.push_back(finala);
        }
      }
    } else {
      if (*grafico.chart.at(i).getName() == "BLACK MARUBOZU") {
        if ((*grafico.chart.at(i + 1).getName() == "FOUR PRICE DOJI") or
            (*grafico.chart.at(i + 1).getName() == "DRAGONFLY DOJI") or
            (*grafico.chart.at(i + 1).getName() == "GRAVESTONE DOJI") or
            (*grafico.chart.at(i + 1).getName() == "LONG-LEGGED DOJI")) {
          if (*grafico.chart.at(i).getClose() <
              *grafico.chart.at(i + 3).getClose()) {
            relato finala;
            finala.data = grafico.chart.at(i).getDate();
            finala.ganho = *grafico.chart.at(i + 3).getClose() -
                           *grafico.chart.at(i).getClose();
            diferencaPositiva.push_back(finala);
          } else {
            relato finala;
            finala.data = grafico.chart.at(i).getDate();
            finala.ganho = *grafico.chart.at(i).getClose() -
                           *grafico.chart.at(i + 3).getClose();
            diferencaNegativa.push_back(finala);
          }
        }
      }
    }
  }
  diferencaPositiva.shrink_to_fit();
  diferencaNegativa.shrink_to_fit();

  std::string tz = "TZ=America/Recife";
  putenv(tz.data());
  std::cout << "    Análise Long Candle Plus Doji   " << std::endl;
  std::cout << std::endl;
  std::cout << "Arquivo:  " << arquivo << std::endl;
  std::cout << std::endl;
  std::cout << "Tempo Gráfico: " << TimeFinalSalvar << std::endl;
  std::cout << std::endl;
  std::cout << "  ----------  " << std::endl;
  std::cout << std::endl;
  std::cout << "    Padrões Positivos   " << std::endl;
  std::cout << std::endl;

  price_t somadiferencaPositiva = 0;
  relato maiorPositivo;
  relato menorPositivo;
  if (diferencaPositiva.size() == 0) {
    std::cout << "ZERO" << std::endl;
    somadiferencaPositiva = 0;
  } else {
    maiorPositivo.ganho = diferencaPositiva.at(0).ganho;
    menorPositivo.ganho = diferencaPositiva.at(0).ganho;
    for (unsigned long i = 0; i < diferencaPositiva.size(); ++i) {
      somadiferencaPositiva += diferencaPositiva.at(i).ganho;
      std::cout << std::put_time(std::localtime(diferencaPositiva.at(i).data),
                                 "%d/%m/%Y %H:%M")
                << " " << *Pip(diferencaPositiva.at(i).ganho).getPip() << " pip"
                << std::endl;
      if (maiorPositivo.ganho <= diferencaPositiva.at(i).ganho) {
        maiorPositivo.ganho = diferencaPositiva.at(i).ganho;
        maiorPositivo.data = diferencaPositiva.at(i).data;
      }
      if (menorPositivo.ganho >= diferencaPositiva.at(i).ganho) {
        menorPositivo.ganho = diferencaPositiva.at(i).ganho;
        menorPositivo.data = diferencaPositiva.at(i).data;
      }
    }
    somadiferencaPositiva =
        somadiferencaPositiva / (float)diferencaPositiva.size();
  }

  std::cout << std::endl;
  std::cout << "  ----------  " << std::endl;
  std::cout << std::endl;
  std::cout << "    Padrões Negativos   " << std::endl;
  std::cout << std::endl;

  price_t somadiferencaNegativa = 0;
  relato maiorNegativa;
  relato menorNegativa;
  if (diferencaNegativa.size() == 0) {
    std::cout << "ZERO" << std::endl;
    somadiferencaNegativa = 0;
  } else {
    maiorNegativa.ganho = diferencaNegativa.at(0).ganho;
    menorNegativa.ganho = diferencaNegativa.at(0).ganho;
    for (unsigned long i = 0; i < diferencaNegativa.size(); ++i) {
      somadiferencaNegativa += diferencaNegativa.at(i).ganho;
      std::cout << std::put_time(std::localtime(diferencaNegativa.at(i).data),
                                 "%d/%m/%Y %H:%M")
                << " " << *Pip(diferencaNegativa.at(i).ganho).getPip() << " pip"
                << std::endl;
      if (maiorNegativa.ganho <= diferencaNegativa.at(i).ganho) {
        maiorNegativa.ganho = diferencaNegativa.at(i).ganho;
        maiorNegativa.data = diferencaNegativa.at(i).data;
      }
      if (menorNegativa.ganho >= diferencaNegativa.at(i).ganho) {
        menorNegativa.ganho = diferencaNegativa.at(i).ganho;
        menorNegativa.data = diferencaNegativa.at(i).data;
      }
    }
    somadiferencaNegativa =
        somadiferencaNegativa / (float)diferencaNegativa.size();
  }

  std::cout << std::endl;
  std::cout << "  ----------  " << std::endl;
  std::cout << std::endl;
  std::cout << "  Total de casos: "
            << (diferencaPositiva.size() + diferencaNegativa.size())
            << std::endl;
  std::cout << std::endl;

  if (diferencaPositiva.size() > 0) {
    std::cout << "Quantidade Positivo:  " << diferencaPositiva.size() << "  - "
              << ((float)diferencaPositiva.size() * (float)100) /
                     (float)(diferencaPositiva.size() +
                             diferencaNegativa.size())
              << "%" << std::endl;
    std::cout << "Maior Positivo: "
              << std::put_time(std::localtime(maiorPositivo.data),
                               "%d/%m/%Y %H:%M")
              << " " << *Pip(maiorPositivo.ganho).getPip() << " pip"
              << std::endl;
    std::cout << "Menor Positivo: "
              << std::put_time(std::localtime(menorPositivo.data),
                               "%d/%m/%Y %H:%M")
              << " " << *Pip(menorPositivo.ganho).getPip() << " pip"
              << std::endl;
    std::cout << "Média Positivo: " << *Pip(somadiferencaPositiva).getPip()
              << " pip" << std::endl;
  }
  std::cout << std::endl;
  if (diferencaNegativa.size() > 0) {
    std::cout << "Quantidade Negativo:  " << diferencaNegativa.size() << "  - "
              << ((float)diferencaNegativa.size() * (float)100) /
                     (float)(diferencaPositiva.size() +
                             diferencaNegativa.size())
              << "%" << std::endl;
    std::cout << "Maior Negativo: "
              << std::put_time(std::localtime(maiorNegativa.data),
                               "%d/%m/%Y %H:%M")
              << " -" << *Pip(maiorNegativa.ganho).getPip() << " pip"
              << std::endl;
    std::cout << "Menor Negativo: "
              << std::put_time(std::localtime(menorNegativa.data),
                               "%d/%m/%Y %H:%M")
              << " -" << *Pip(menorNegativa.ganho).getPip() << " pip"
              << std::endl;
    std::cout << "Média Negativo: " << *Pip(somadiferencaNegativa).getPip()
              << " pip" << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Quantidade de velas analisadas: " << grafico.chart.size()
            << " velas" << std::endl;
}

/**
 * @brief Função Relatório método Shot Hammer
 * Verifica seo padão é posiitivo ao ser identificado, com tempo de vida da vela
 * sequinte, levando em conta que existe uma tendência de 4 velas anteriores
 * @param arquivo Arquivo de velas
 * @param tempo Tempo Gráfico
 */
void ShotHammer(std::string arquivo, std::string tempo) {
  std::string nome = "Shot Hammer";
  std::string TimeFinalSalvar = tempo;
  Chart grafico(&arquivo, &nome, &tempo);
  struct relato {
    time_t* data;
    price_t ganho;
  };
  std::vector<relato> diferencaPositiva;
  std::vector<relato> diferencaNegativa;

  for (unsigned long i = 6; i < grafico.chart.size() - 3; ++i) {
    if (!*grafico.chart.at(i).getStatus() or
        !*grafico.chart.at(i - 1).getStatus() or
        !*grafico.chart.at(i - 2).getStatus() or
        !*grafico.chart.at(i + 1).getStatus() or
        !*grafico.chart.at(i + 2).getStatus()) {
      continue;
    }
    if (*grafico.chart.at(i).getName() == "WHITE HAMMER") {
      if (*grafico.chart.at(i - 1).getType() == 1) {
        if (*grafico.chart.at(i - 1).getClose() <
            *grafico.chart.at(i - 2).getClose()) {
              //
          if (*grafico.chart.at(i - 1).getClose() >=
              *grafico.chart.at(i).getClose()) {
            if (*grafico.chart.at(i + 1).getType() == 0) {
              if (*grafico.chart.at(i + 1).getOpen() >=
                  *grafico.chart.at(i).getClose()) {
                if (*grafico.chart.at(i + 2).getType() == 0) {
                  relato finala;
                  finala.data = grafico.chart.at(i).getDate();
                  finala.ganho = *grafico.chart.at(i + 2).getBodySize();
                  diferencaPositiva.push_back(finala);
                } else {
                  relato finala;
                  finala.data = grafico.chart.at(i).getDate();
                  if (*grafico.chart.at(i + 2).getType() == 2) {
                    finala.ganho = 0;
                  } else {
                    finala.ganho = *grafico.chart.at(i + 2).getBodySize();
                  }
                  diferencaNegativa.push_back(finala);
                }
              }
            }
          }
        }
      } else {
        if (*grafico.chart.at(i - 1).getClose() >
            *grafico.chart.at(i - 2).getClose()) {
          //
          if (*grafico.chart.at(i - 1).getClose() <=
              *grafico.chart.at(i).getOpen()) {
            if (*grafico.chart.at(i + 1).getType() == 1) {
              if (*grafico.chart.at(i + 1).getOpen() <=
                  *grafico.chart.at(i).getOpen()) {
                if (*grafico.chart.at(i + 2).getType() == 1) {
                  relato finala;
                  finala.data = grafico.chart.at(i).getDate();
                  finala.ganho = *grafico.chart.at(i + 2).getBodySize();
                  diferencaPositiva.push_back(finala);
                } else {
                  relato finala;
                  finala.data = grafico.chart.at(i).getDate();
                  if (*grafico.chart.at(i + 2).getType() == 2) {
                    finala.ganho = 0.0;
                  } else {
                    finala.ganho = *grafico.chart.at(i + 2).getBodySize();
                  }
                  diferencaNegativa.push_back(finala);
                }
              }
            }
          }
        }
      }
    } else {
      if (*grafico.chart.at(i).getName() == "BLACK HAMMER") {
        if (*grafico.chart.at(i - 1).getType() == 1) {
          if (*grafico.chart.at(i - 1).getClose() <
              *grafico.chart.at(i - 2).getClose()) {
                //
            if (*grafico.chart.at(i - 1).getClose() >=
                *grafico.chart.at(i).getOpen()) {
              if (*grafico.chart.at(i + 1).getType() == 0) {
                if (*grafico.chart.at(i + 1).getOpen() >=
                    *grafico.chart.at(i).getOpen()) {
                  if (*grafico.chart.at(i + 2).getType() == 0) {
                    relato finala;
                    finala.data = grafico.chart.at(i).getDate();
                    finala.ganho = *grafico.chart.at(i + 2).getBodySize();
                    diferencaPositiva.push_back(finala);
                  } else {
                    relato finala;
                    finala.data = grafico.chart.at(i).getDate();
                    if (*grafico.chart.at(i + 2).getType() == 2) {
                      finala.ganho = 0.0;
                    } else {
                      finala.ganho = *grafico.chart.at(i + 2).getBodySize();
                    }
                    diferencaNegativa.push_back(finala);
                  }
                }
              }
            }
          }
        } else {
          if (*grafico.chart.at(i - 1).getClose() >
              *grafico.chart.at(i - 2).getClose()) {
                //
            if (*grafico.chart.at(i - 1).getClose() <=
                *grafico.chart.at(i).getClose()) {
              if (*grafico.chart.at(i + 1).getType() == 1) {
                if (*grafico.chart.at(i + 1).getOpen() <=
                    *grafico.chart.at(i).getClose()) {
                  if (*grafico.chart.at(i + 2).getType() == 1) {
                    relato finala;
                    finala.data = grafico.chart.at(i).getDate();
                    finala.ganho = *grafico.chart.at(i + 2).getBodySize();
                    diferencaPositiva.push_back(finala);
                  } else {
                    relato finala;
                    finala.data = grafico.chart.at(i).getDate();
                    if (*grafico.chart.at(i + 2).getType() == 2) {
                      finala.ganho = 0.0;
                    } else {
                      finala.ganho = *grafico.chart.at(i + 2).getBodySize();
                    }
                    diferencaNegativa.push_back(finala);
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  diferencaPositiva.shrink_to_fit();
  diferencaNegativa.shrink_to_fit();

  std::string tz = "TZ=America/Recife";
  putenv(tz.data());
  std::cout << "    Análise Shot Hammer   " << std::endl;
  std::cout << std::endl;
  std::cout << "Arquivo:  " << arquivo << std::endl;
  std::cout << std::endl;
  std::cout << "Tempo Gráfico: " << TimeFinalSalvar << std::endl;
  std::cout << std::endl;
  std::cout << "  ----------  " << std::endl;
  std::cout << std::endl;
  std::cout << "    Padrões Positivos   " << std::endl;
  std::cout << std::endl;

  price_t somadiferencaPositiva = 0;
  relato maiorPositivo;
  relato menorPositivo;
  if (diferencaPositiva.size() == 0) {
    std::cout << "ZERO" << std::endl;
    somadiferencaPositiva = 0;
  } else {
    maiorPositivo.ganho = diferencaPositiva.at(0).ganho;
    menorPositivo.ganho = diferencaPositiva.at(0).ganho;
    for (unsigned long i = 0; i < diferencaPositiva.size(); ++i) {
      somadiferencaPositiva += diferencaPositiva.at(i).ganho;
      std::cout << std::put_time(std::localtime(diferencaPositiva.at(i).data),
                                 "%d/%m/%Y %H:%M")
                << " " << *Pip(diferencaPositiva.at(i).ganho).getPip() << " pip"
                << std::endl;
      if (maiorPositivo.ganho <= diferencaPositiva.at(i).ganho) {
        maiorPositivo.ganho = diferencaPositiva.at(i).ganho;
        maiorPositivo.data = diferencaPositiva.at(i).data;
      }
      if (menorPositivo.ganho >= diferencaPositiva.at(i).ganho) {
        menorPositivo.ganho = diferencaPositiva.at(i).ganho;
        menorPositivo.data = diferencaPositiva.at(i).data;
      }
    }
    somadiferencaPositiva =
        somadiferencaPositiva / (float)diferencaPositiva.size();
  }

  std::cout << std::endl;
  std::cout << "  ----------  " << std::endl;
  std::cout << std::endl;
  std::cout << "    Padrões Negativos   " << std::endl;
  std::cout << std::endl;

  price_t somadiferencaNegativa = 0;
  relato maiorNegativa;
  relato menorNegativa;
  if (diferencaNegativa.size() == 0) {
    std::cout << "ZERO" << std::endl;
    somadiferencaNegativa = 0;
  } else {
    maiorNegativa.ganho = diferencaNegativa.at(0).ganho;
    menorNegativa.ganho = diferencaNegativa.at(0).ganho;
    for (unsigned long i = 0; i < diferencaNegativa.size(); ++i) {
      somadiferencaNegativa += diferencaNegativa.at(i).ganho;
      std::cout << std::put_time(std::localtime(diferencaNegativa.at(i).data),
                                 "%d/%m/%Y %H:%M")
                << " " << *Pip(diferencaNegativa.at(i).ganho).getPip() << " pip"
                << std::endl;
      if (maiorNegativa.ganho <= diferencaNegativa.at(i).ganho) {
        maiorNegativa.ganho = diferencaNegativa.at(i).ganho;
        maiorNegativa.data = diferencaNegativa.at(i).data;
      }
      if (menorNegativa.ganho >= diferencaNegativa.at(i).ganho) {
        menorNegativa.ganho = diferencaNegativa.at(i).ganho;
        menorNegativa.data = diferencaNegativa.at(i).data;
      }
    }
    somadiferencaNegativa =
        somadiferencaNegativa / (float)diferencaNegativa.size();
  }

  std::cout << std::endl;
  std::cout << "  ----------  " << std::endl;
  std::cout << std::endl;
  std::cout << "  Total de casos: "
            << (diferencaPositiva.size() + diferencaNegativa.size())
            << std::endl;
  std::cout << std::endl;
  if (diferencaPositiva.size() > 0) {
    std::cout << "Quantidade Positivo:  " << diferencaPositiva.size() << "  - "
              << ((float)diferencaPositiva.size() * (float)100) /
                     (float)(diferencaPositiva.size() +
                             diferencaNegativa.size())
              << "%" << std::endl;
    std::cout << "Maior Positivo: "
              << std::put_time(std::localtime(maiorPositivo.data),
                               "%d/%m/%Y %H:%M")
              << " " << *Pip(maiorPositivo.ganho).getPip() << " pip"
              << std::endl;
    std::cout << "Menor Positivo: "
              << std::put_time(std::localtime(menorPositivo.data),
                               "%d/%m/%Y %H:%M")
              << " " << *Pip(menorPositivo.ganho).getPip() << " pip"
              << std::endl;
    std::cout << "Média Positivo: " << *Pip(somadiferencaPositiva).getPip()
              << " pip" << std::endl;
  }
  std::cout << std::endl;
  if (diferencaNegativa.size() > 0) {
    std::cout << "Quantidade Negativo:  " << diferencaNegativa.size() << "  - "
              << ((float)diferencaNegativa.size() * (float)100) /
                     (float)(diferencaPositiva.size() +
                             diferencaNegativa.size())
              << "%" << std::endl;
    std::cout << "Maior Negativo: "
              << std::put_time(std::localtime(maiorNegativa.data),
                               "%d/%m/%Y %H:%M")
              << " -" << *Pip(maiorNegativa.ganho).getPip() << " pip"
              << std::endl;
    std::cout << "Menor Negativo: "
              << std::put_time(std::localtime(menorNegativa.data),
                               "%d/%m/%Y %H:%M")
              << " -" << *Pip(menorNegativa.ganho).getPip() << " pip"
              << std::endl;
    std::cout << "Média Negativo: " << *Pip(somadiferencaNegativa).getPip()
              << " pip" << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Quantidade de velas analisadas: " << grafico.chart.size()
            << " velas" << std::endl;
}

int main(int argc, char const* argv[]) {
  try {
    std::string arquivo = argv[1];
    std::string tempo = argv[2];
    std::string delta = argv[3];
    std::string nome = "TESTE";
    std::string arquivoFinal = "out/";
    arquivoFinal += argv[4];

    // LongCandlePlusDoji(arquivo, tempo);
    ShotHammer(arquivo, tempo);

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}
