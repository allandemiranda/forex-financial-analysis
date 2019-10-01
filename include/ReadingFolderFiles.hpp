/**
 * @file ReadingFolderFiles.hpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Classe para gerenciar a leitura de todos os arquivos de todas as
 * pastas
 * @version 0.1
 * @date 25-09-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef READINGFOLDERFILES_HPP_
#define READINGFOLDERFILES_HPP_

#include <string>  // std::string
#include <vector>  // std::vector

class ReadingFolderFiles {
 private:
  std::vector<std::string> list_path;
  void getFilesPath(std::string);

 public:
  std::vector<std::string> getListPath(void);
  ReadingFolderFiles(std::string);
  ~ReadingFolderFiles(void);
};

#endif