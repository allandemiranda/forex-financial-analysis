#include <iostream>
#include "Chart.hpp"
#include "Dashboard.hpp"
#include "ReadingFolderFiles.hpp"

int main(int argc, char const* argv[]) {
  try {
    std::string a = argv[1];
    // ReadingFolderFiles lista_arquivos(a);
    std::string b = argv[2];
    std::string c = "TESTE";
    // for (auto i : lista_arquivos.list_path) {
    // std::cout << i << std::endl;
    Chart grafico(&a, &c, &b);
    std::cout << grafico.chart.size() << std::endl;
    std::string localSalvar = "out/teste.html";
    Dashboard(&c, &localSalvar, &grafico.chart);
    // }

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
    return EXIT_FAILURE;
  }
  return 0;
}
