#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include "DataBase.hpp"
#include "Chart.hpp"
#include "Dashboard.hpp"

int main(int argc, char const* argv[]) {
    try {
    std::string a = argv[1];
    std::string b = "H1";
    std::cout << b << std::endl;
    DataBase novo_bd(a);
    std::cout << novo_bd.Banco_De_Dados.size() << std::endl;
    Chart novo_grafico(&novo_bd.Banco_De_Dados, b, "TESTE");
    std::cout << novo_grafico.Chart_Vetor.size() << std::endl;
    Dashboard(&novo_grafico.Chart_Vetor, "out/teste.html", "TESTE");
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
    return EXIT_FAILURE;
  }
  return 0;
}
