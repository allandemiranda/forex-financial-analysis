#include <ctime>
#include <iomanip>
#include <iostream>
#include "Chart.hpp"
#include "Dashboard.hpp"
#include "ReadingFolderFiles.hpp"

std::vector<std::string> explode(const std::string* line, char* c) {
  std::string buff{""};
  std::vector<std::string> v;
  for (auto n : *line) {
    if (n != *c) {
      buff += n;
    } else if (n == *c && buff != "") {
      v.push_back(buff);
      v.shrink_to_fit();
      buff = "";
    }
  }
  if (buff != "") {
    v.push_back(buff);
    v.shrink_to_fit();
  }
  return v;
}

int main(int argc, char const* argv[]) {
  try {
    std::string a = argv[1];
    ReadingFolderFiles lista_arquivos(a);
    for (auto i : lista_arquivos.list_path) {
      std::vector<std::string> tempos_permitidos = {
          "M5", "M6", "M10", "M12", "M15", "M20",
          "M20", "H1", "H2", "H3", "H4", "H6", "H8", "H12", "D1",  "W1",
          "J1",  "Y1"};
      // std::vector<std::string> tempos_permitidos = {"H1"};
      for (auto j : tempos_permitidos) {
        std::cout << "TEMPO: " << j << std::endl;
        std::string b = j;
        char barra = '/';
        char ponto = '.';
        std::string titulo_1 = explode(&explode(&i, &barra).back(), &ponto)[0];
        Chart grafico(&i, &titulo_1, &b);
        std::string localSalvar = "/media/allandemiranda/ALLAN/testes-g/";
        localSalvar += explode(&explode(&i, &barra).back(), &ponto)[0];
        localSalvar += "-";
        localSalvar += j;
        localSalvar += ".html";
        // std::string localSalvar = "out/teste.html";
        std::string titulo = *grafico.getNameChart() + " - " + j;
        std::cout << "Elaborando gráfico..." << std::endl;
        std::cout << localSalvar << std::endl;
        Dashboard(&titulo, &localSalvar, &grafico.chart);
        std::cout << "Gráfico pronto !" << std::endl;
      }
    }

  } catch (const char* msg) {
    std::cerr << msg << std::endl;
    return EXIT_FAILURE;
  }
  return 0;
}
