#include <ctime>
#include <iomanip>
#include <iostream>
#include "Chart.hpp"
#include "Dashboard.hpp"
#include "LinePrice.hpp"
#include "ReadingFolderFiles.hpp"
#include <algorithm>

int main(int argc, char const* argv[]) {
  try {
    std::string arquivo = argv[1];
    std::string tempo = argv[2];
    std::string delta = argv[3];
    std::string nome = "TESTE";
    Chart grafico(&arquivo, &nome, &tempo);
    std::string arquivoFinal = "out/";
    arquivoFinal += argv[4];
    LinePrice linha(&grafico.chart, std::stoi(delta));

    Dashboard desenhar(grafico.getNameChart(), &arquivoFinal, &grafico.chart,
                       &linha.line);

    std::cout << grafico.chart.size() << " VELAS" << std::endl;
    
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}
