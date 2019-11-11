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
    std::cout << "0" << std::endl;
    Chart grafico(&arquivo, &NOME, &tempo);
    std::cout << "1" << std::endl;
    MovingAverage mv(std::stoi(periodos), &grafico);
    std::cout << "2" << std::endl;
    Line a = mv.SMA();
    std::cout << "3" << std::endl;
    Dashboard desenho(&NOME, &ARQUIVO, &grafico.chart, &a);
    std::cout << "4" << std::endl;


    

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}