/**
 * @file ReadingFolderFiles.cpp
 * @author Allan de Miranda Silva (allandemiranda@gmail.com)
 * @brief Métodos da classe ReadingFolderFiles
 * @version 0.1
 * @date 25-09-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "ReadingFolderFiles.hpp"
#include <dirent.h>
#include <cstdlib>
#include <string>  // std::string
#include <vector>  // std::vector

/**
 * @brief Construct a new Reading Folder Files:: Reading Folder Files object
 *
 * @param loop_path Caminho para analisar
 */
ReadingFolderFiles::ReadingFolderFiles(std::string loop_path) {
  getFilesPath(loop_path);
  list_path.shrink_to_fit();
}

/**
 * @brief Destroy the Reading Folder Files:: Reading Folder Files object
 *
 */
ReadingFolderFiles::~ReadingFolderFiles(void) {}

/**
 * @brief Get the Files Path object
 *
 * @param path Caminho da pasta a ser analisada
 */
void ReadingFolderFiles::getFilesPath(std::string path) {
  DIR *dir = 0;
  struct dirent *entrada = 0;
  // unsigned char isDir = 0x4;
  unsigned char isFile = 0x8;
  if (path.back() != '/') {
    path.push_back('/');
  }
  if (path.front() == '.') {
    if (*(path.begin() + 1) == '/') {
      path.erase(0, 2);
    }
  }
  dir = opendir(path.c_str());
  if (dir == 0) {
    throw "ERRO! Não foi possivel abrir o diretório";
  } else {
    while (entrada = readdir(dir)) {
      if (entrada->d_type == isFile) {
        std::string new_file_path;
        new_file_path = path;
        new_file_path += entrada->d_name;
        list_path.push_back(new_file_path);
      } else {
        if (*entrada->d_name != '.') {
          std::string new_file_loop;
          new_file_loop = path;
          new_file_loop += entrada->d_name;
          new_file_loop.push_back('/');
          getFilesPath(new_file_loop);
        }
      }
    }
  }
  closedir(dir);
}