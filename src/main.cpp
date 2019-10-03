#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include "Chart.hpp"
#include "DataBase.hpp"
#include "ReadingFolderFiles.hpp"
#include "Dashboard.hpp"

int main(int argc, char const* argv[]) {
  try {
    std::string a = argv[1];
    // ReadingFolderFiles list_file(a);
    // for (auto i : list_file.getListPath()) {
    //   std::cout << i << std::endl;
    // }
    
    std::cout << "------------------" << std::endl;
    // for (auto i : list_file.getListPath()) {
      std::cout << "Lendo " << a << " ";
      DataBase novo_bd(a);
      Chart novo_grafico(novo_bd, "M1", "TESTE");
      Dashboard(&novo_grafico.chartvector, "out/teste.html", "TESTE");
      std::cout << " OK! " << std::endl;
      std::string TimeZone = "TZ=America/Recife";
      putenv(TimeZone.data());
      for (auto j : novo_grafico.getChart()) {
        char mbstr[100];
        time_t temp_time_t_ = j.getDate();
        std::strftime(mbstr, sizeof(mbstr), "%D %T",
                      std::localtime(&temp_time_t_));
        if (j.getStatus() == "OK") {
          std::cout << j.getStatus() << " " << mbstr << " " << j.getOpen()
                    << " " << j.getClose() << " " << j.getTime() << std::endl;
        } else {
          std::cout << mbstr << " " << j.getStatus() << " " << j.getTime()
                    << std::endl;
        }
      }
    // }
    // std::cout << "Open    Close   Type    High    Low   UpperSize   "
    //              "LowerSize   BodySize    Size    Data    Time    Status"
    //           << std::endl;
    // for (auto vela : novo_bd.getDBStick()) {
    //   // std::cout << vela.getOpen();
    //   // std::cout << " ";
    //   // std::cout << vela.getClose();
    //   // std::cout << " ";
    //   // std::cout << vela.getType();
    //   // std::cout << " ";
    //   // std::cout << vela.getHigh();
    //   // std::cout << " ";
    //   // std::cout << vela.getLow();
    //   // std::cout << " ";
    //   // std::cout << vela.getUpperShandowSize();
    //   // std::cout << " ";
    //   // std::cout << vela.getLowerShandowSize();
    //   // std::cout << " ";
    //   // std::cout << vela.getBodySize();
    //   // std::cout << " ";
    //   // std::cout << vela.getSize();
    //   // std::cout << " ";
    //   std::string TimeZone = "TZ=America/Recife";
    //   putenv(TimeZone.data());
    //   std::time_t result(vela.getDate());
    //   //std::cout << vela.getDate() << " ";
    //   std::cout << std::put_time(std::localtime(&result), "%c %Z");
    //   // std::cout << " ";
    //   // std::cout << vela.getTime();
    //   // std::cout << " ";
    //   // std::cout << vela.getStatus();
    //   std::cout << std::endl;
    // }
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
    return EXIT_FAILURE;
  }
  return 0;
}
