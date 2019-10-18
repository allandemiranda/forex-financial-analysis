#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include "Chart.hpp"
#include "Dashboard.hpp"
#include "LinePrice.hpp"
#include "ReadingFolderFiles.hpp"
#include "ZoneReversal.hpp"

int main(int argc, char const* argv[]) {
  try {
    std::string arquivo = argv[1];
    std::string tempo = argv[2];
    std::string delta = argv[3];
    std::string zonaTamanho = argv[4];
    std::string nome = "TESTE";
    Chart grafico(&arquivo, &nome, &tempo);
    std::string arquivoFinal = "out/";
    arquivoFinal += argv[5];

    LinePrice linha(&grafico, std::stoi(delta), "Tendência");

    ZoneReversal zonas(&grafico, std::stoi(zonaTamanho), std::stoi(delta));

    std::vector<Line> final = {linha,
                               zonas.zones.at(1).getLinhaSuperior(),
                               zonas.zones.at(1).getLinhaInferior()};

    Dashboard desenhar(grafico.getNameChart(), &arquivoFinal, &grafico.chart,
                       &final);

    std::cout << grafico.chart.size() << " VELAS" << std::endl;

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}
