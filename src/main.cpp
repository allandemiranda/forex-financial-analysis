#include <ctime>
#include <iomanip>
#include <iostream>
#include "Chart.hpp"
#include "Dashboard.hpp"
#include "LinePrice.hpp"
#include "ReadingFolderFiles.hpp"

int main(int argc, char const* argv[]) {
  try {
    std::string arquivo = argv[1];
    std::string tempo = argv[2];
    std::string nome = "TESTE";
    Chart grafico(&arquivo, &nome, &tempo);

    std::cout << grafico.chart.size() << " VELAS" << std::endl;
    std::cout
        << "DATA    TIME    STATUS    OPEN    HIGH    LOW   CLOSE   TYPE   "
           " SHANDON-UPPER-SIZE    SHANDOWN-LOWER-SIZE   BODY    SIZE"
        << std::endl;
    for (auto i : grafico.chart) {
      putenv(i.getTZ().data());
      std::cout << std::put_time(std::localtime(i.getDate()), "%F %T %Z")
                << "  ";
      std::cout << *i.getTime() << "  ";
      std::cout << *i.getStatus();
      if (*i.getStatus()) {
        std::cout << "  ";
        std::cout << *i.getOpen() << "  ";
        std::cout << *i.getHigh() << "  ";
        std::cout << *i.getLow() << "  ";
        std::cout << *i.getClose() << "  ";
        std::cout << *i.getType() << "  ";
        std::cout << *i.getUpperShandowSize() << "  ";
        std::cout << *i.getLowerShandowSize() << "  ";
        std::cout << *i.getBodySize() << "  ";
        std::cout << *i.getSize() << "  ";
      }
      std::cout << std::endl;
    }
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}
