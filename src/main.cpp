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
      Candlestick* vela;
      Candlestick* vela1;
      unsigned int quantidade = 1;
    };

    std::vector<padroes> velasIguais;

    for (unsigned long i = 0; i < (grafico.chart.size() - 1); ++i) {
      if (*grafico.chart.at(i).getStatus() and
          (*grafico.chart.at(i).getName() != "NONE")) {
        bool flag = true;
#pragma omp parallel
        {
#pragma omp for
          for (unsigned long j = 0; j < velasIguais.size(); ++j) {
            if (*velasIguais.at(j).vela->getName() ==
                *grafico.chart.at(i).getName()) {
              if (*velasIguais.at(j).vela1->getName() != "NONE") {
                if (*velasIguais.at(j).vela1->getName() ==
                    *grafico.chart.at(i + 1).getName()) {
#pragma omp critical
                  {
                    flag = false;
                    velasIguais.at(j).quantidade += 1;
                  }
#pragma omp cancel for
                }
              } else {
                flag = false;
              }
            }
          }
        }
        if (flag) {
          padroes novo;
          novo.vela = &grafico.chart.at(i);
          novo.vela1 = &grafico.chart.at(i + 1);
          velasIguais.push_back(novo);
        }
      }
    }

    for (auto i : velasIguais) {
      std::cout << "Vela: " << *i.vela->getName() << " -> "
                << *i.vela->getName() << " -> " << i.quantidade << std::endl;
    }

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}