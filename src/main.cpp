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

    for (unsigned long i = 0; i < grafico.chart.size(); ++i) {
      if (*grafico.chart.at(i).getStatus()) {
        bool flag = true;
#pragma omp parallel
        {
#pragma omp for
          for (unsigned long j = 0; j < velasIguais.size(); ++j) {
            if (*velasIguais.at(j).vela->getHash() ==
                *grafico.chart.at(i).getHash()) {
              if (*velasIguais.at(j).vela1->getHash() ==
                  *grafico.chart.at(i + 1).getHash()) {
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
        if (flag) {
          padroes novo;
          novo.vela = &grafico.chart.at(i);
          novo.vela1 = &grafico.chart.at(i+1);
          velasIguais.push_back(novo);
        }
      }
    }

    int a = 0;
    for (auto i : velasIguais) {
      if (i.quantidade >= 10) {
        std::cout << "Vela: " << *i.vela->getName() << " -> " << i.quantidade
                  << std::endl;
      } else {
        ++a;
      }
    }
    std::cout << "-----> " << a << std::endl;

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}