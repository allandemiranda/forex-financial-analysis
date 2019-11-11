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
#include "MovingAverage.hpp"

int main(int argc, char const* argv[]) {
  try {
    std::string arquivo = argv[1];
    std::string tempo = argv[2];
    std::string periodos = argv[3];
    std::string NOME = "TESTE";
    std::string ARQUIVO = "out/teste.html";
    Chart grafico(&arquivo, &NOME, &tempo);
    MovingAverage mv(std::stoi(periodos), &grafico);
    Line a = mv.SMA();
    Dashboard desenho(&NOME, &ARQUIVO, &grafico.chart, &a);


    

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}