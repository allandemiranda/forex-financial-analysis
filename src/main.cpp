#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include "Chart.hpp"
#include "Dashboard.hpp"
#include "Line.hpp"
#include "LinePrice.hpp"
#include "ReadingFolderFiles.hpp"
#include "ZoneReversal.hpp"

int main(int argc, char const* argv[]) {
  try {
    std::string arquivo = argv[1];
    std::string tempo = argv[2];
    std::string delta = argv[3];
    std::string nome = "TESTE";
    Chart grafico(&arquivo, &nome, &tempo);
    std::string arquivoFinal = "out/";
    arquivoFinal += argv[4];



float maior = 0.0;
unsigned long delta_b = 0;
for(unsigned long delta_a = 4; delta_a<=200; ++delta_a){

    //LinePrice linha(&grafico, std::stoi(delta), "Tendência");
LinePrice linha(&grafico, delta_a, "Tendência");

    unsigned long coicidencias = 0;

#pragma omp parallel for reduction(+ : coicidencias)
    for (unsigned long i = 0; i < linha.linha.size(); ++i) {
      auto encontrou = std::lower_bound(grafico.chart.begin(), grafico.chart.end(), *linha.linha.at(i).getDate());
      if(encontrou != grafico.chart.end()){
        std::advance(encontrou, -1);
        if(*encontrou->getName() != "NONE"){
          ++coicidencias;
          continue;
        }
        std::advance(encontrou, 1);
        if(*encontrou->getName() != "NONE"){
          ++coicidencias;
          continue;
        }
        std::advance(encontrou, 1);
        if(*encontrou->getName() != "NONE"){
          ++coicidencias;
          continue;
        }
      }
    }

    float maior_a = (((float)coicidencias * (float)100)/(float)linha.linha.size());
    std::cout << delta_a << " " << maior_a << "%" << std::endl;
    if(maior < maior_a){
      maior = maior_a;
      delta_b = delta_a;
    } 
}
std::cout << std::endl;
std::cout << "Delta: " << delta_b << " - Maior: " << maior << " %" << std::endl;
    // Dashboard desenhar(grafico.getNameChart(), &arquivoFinal, &grafico.chart,
    //                    &linha);

    // std::cout << grafico.chart.size() << " VELAS" << std::endl;

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}
