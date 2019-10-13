#include <iostream>
#include "Chart.hpp"
#include "Dashboard.hpp"
#include "ReadingFolderFiles.hpp"
#include "LinePrice.hpp"

int main(int argc, char const *argv[])
{
  std::string arquivo = argv[1];
  std::string tempo = argv[2];
  std::string velas = argv[3];
  std::string nome = "TESTE";
  std::string destino = "out/teste.html";
  Chart grafico(&arquivo, &nome, &tempo);
  std::cout << "FAZENDO LINHA" << std::endl;
  LinePrice tendencia(&grafico.chart,std::stoi(velas));
  std::cout << "FAZENDO GRAFICO" << std::endl;
  Dashboard painel(&nome,&destino,&grafico.chart,&tendencia.line);
  return 0;
}
