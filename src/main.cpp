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
#include "ChartIndicators.hpp"
#include "Intermarket.hpp"

int main(int argc, char const* argv[]) {
  try {
    std::string arquivo = argv[1];
    std::string tempo = argv[2];
    std::string tempo1 = argv[2];
    std::string caminho = argv[3];
    std::string NOME = "EUR/USD";
    Chart grafico(&arquivo, &NOME, &tempo);
    ReadingFolderFiles lista(caminho);
    Intermarket teste(&grafico,&lista,tempo1);
  teste.getResults();
    


    

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}