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

int main(int argc, char const* argv[]) {
  try {
    std::string arquivo = argv[1];
    std::string tempo = argv[2];
    std::string NOME = "TESTE";
    Chart grafico(&arquivo, &NOME, &tempo);

    struct padroes {
      Candlestick* vela1;
      Candlestick* vela2;
      Candlestick* vela3;
      Candlestick* vela4;
      Candlestick* vela5;
      unsigned int quantidade = 1;
    };

    std::vector<padroes> velasIguais;

    for (unsigned long i = 6; i < (grafico.chart.size() - 0); ++i) {
      if (*grafico.chart.at(i).getStatus() and
          *grafico.chart.at(i - 1).getStatus() and
          *grafico.chart.at(i - 2).getStatus() and
          *grafico.chart.at(i - 3).getStatus() and
          *grafico.chart.at(i - 4).getStatus()) {
        bool flag = true;
#pragma omp parallel
        {
#pragma omp for
          for (unsigned long j = 0; j < velasIguais.size(); ++j) {
            if (*velasIguais.at(j).vela1->getName() ==
                *grafico.chart.at(i - 4).getName()) {
              if (*velasIguais.at(j).vela1->getType() ==
                  *grafico.chart.at(i - 4).getType()) {
                if (*velasIguais.at(j).vela2->getName() ==
                    *grafico.chart.at(i - 3).getName()) {
                  if (*velasIguais.at(j).vela2->getType() ==
                      *grafico.chart.at(i - 3).getType()) {
                    if (*velasIguais.at(j).vela3->getName() ==
                        *grafico.chart.at(i - 2).getName()) {
                      if (*velasIguais.at(j).vela3->getType() ==
                          *grafico.chart.at(i - 2).getType()) {
                        if (*velasIguais.at(j).vela4->getName() ==
                            *grafico.chart.at(i - 1).getName()) {
                          if (*velasIguais.at(j).vela4->getType() ==
                              *grafico.chart.at(i - 1).getType()) {
                            if (*velasIguais.at(j).vela5->getName() ==
                                *grafico.chart.at(i).getName()) {
                              if (*velasIguais.at(j).vela5->getType() ==
                                  *grafico.chart.at(i).getType()) {
#pragma omp critical
                                {
                                  flag = false;
                                  velasIguais.at(j).quantidade += 1;
                                }
#pragma omp cancel for
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        if (flag) {
          padroes novo;
          novo.vela1 = &grafico.chart.at(i - 4);
          novo.vela2 = &grafico.chart.at(i - 3);
          novo.vela3 = &grafico.chart.at(i - 2);
          novo.vela4 = &grafico.chart.at(i - 1);
          novo.vela5 = &grafico.chart.at(i);
          velasIguais.push_back(novo);
        }
      }
    }

    int a = 0;
    for (auto i : velasIguais) {
      std::cout << *i.vela1->getName() << "(" << *i.vela1->getType()<<") -> "
                << *i.vela2->getName() << "(" << *i.vela2->getType()<<") -> "
                << *i.vela3->getName() << "(" << *i.vela3->getType()<<") -> "
                << *i.vela4->getName() << "(" << *i.vela4->getType()<<") -> "
                << *i.vela5->getName() << "(" << *i.vela5->getType()<<") -> "
                << i.quantidade << std::endl;
                ++a;
    }
    std::cout << std::endl;
    std::cout << "--> " << a << std::endl;

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}