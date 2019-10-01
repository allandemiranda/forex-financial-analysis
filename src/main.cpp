#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include "DataBase.hpp"
#include "ReadingFolderFiles.hpp"

int main(int argc, char const* argv[]) {
  try {
    std::string a = argv[1];
    ReadingFolderFiles list_file(a);
    for (auto i : list_file.getListPath()) {
      std::cout << i << std::endl;
    }
    std::cout << "------------------" << std::endl;
    for (auto i : list_file.getListPath()) {
      std::cout << "Lendo " << i << " ";
      DataBase novo_bd(i);
      std::cout << " OK! " << std::endl;
    }
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
