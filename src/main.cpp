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

    std::vector<pip_t> sup_res;
    for(auto i = (linha.line.size() - 10000); i<linha.line.size(); ++i){
      sup_res.push_back(*linha.line.at(i).getPrice());
    }
    std::sort(sup_res.begin(), sup_res.end());
    sup_res.shrink_to_fit();
    std::vector<pip_t> sup_res_a = sup_res;
    unsigned int quantidade = 0;
    pip_t valorF;
    std::unique(sup_res_a.begin(), sup_res_a.end());
    sup_res_a.shrink_to_fit();
    for(auto i(0u); i<sup_res_a.size(); ++i){
      unsigned int a = 0;
      for(auto j(0u); j<sup_res.size(); ++j){
        if(sup_res_a.at(i) == sup_res.at(j)){
          ++a;
        }
      }
      std::cout << "VALOR: " <<  sup_res_a.at(i) << " QUANTIDADE: " << a << std::endl;
      if(quantidade < a){
        quantidade = a;
        valorF = sup_res_a.at(i);
      }
    }

    auto valorFF = valorF;

    Line aaa(grafico.chart.front().getDate(),&valorF);
    Line bbb(grafico.chart.back().getDate(),&valorFF);
    std::vector<Line> fgh = {aaa,bbb};
    fgh.shrink_to_fit();

    std::vector<std::vector<Line>> asd = {linha.line, fgh};
    asd.shrink_to_fit();

    Dashboard desenhar(grafico.getNameChart(), &arquivoFinal, &grafico.chart,
                       &asd);

    std::cout << grafico.chart.size() << " VELAS" << std::endl;
    
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
  }

  return 0;
}
