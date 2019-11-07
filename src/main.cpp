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
      unsigned int quantidade = 1;
    };

    std::vector<padroes> velasIguais;

    for (auto i(0u); i < grafico.chart.size(); ++i) {
      if (*grafico.chart.at(i).getStatus()) {
        bool flag = true;
        for (auto j(0u); j < velasIguais.size(); ++j) {
          if (*velasIguais.at(j).vela->getType() ==
              *grafico.chart.at(i).getType()) {
            if (*velasIguais.at(j).vela->getSize() ==
                *grafico.chart.at(i).getSize()) {
              if (*velasIguais.at(j).vela->getBodySize() ==
                  *grafico.chart.at(i).getBodySize()) {
                if (*velasIguais.at(j).vela->getUpperShandowSize() ==
                    *grafico.chart.at(i).getUpperShandowSize()) {
                  if (*velasIguais.at(j).vela->getLowerShandowSize() ==
                      *grafico.chart.at(i).getLowerShandowSize()) {
                    flag = false;
                    velasIguais.at(j).quantidade += 1;
                  }
                }
              }
            }
          }
        }
        if (flag) {
          padroes novo;
          novo.vela = &grafico.chart.at(i);
          velasIguais.push_back(novo);
        }
      }
    }

    for (auto i : velasIguais) {
      std::cout << "Vela: " << *i.vela->getName() << " -> " << i.quantidade
                << std::endl;
    }

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}