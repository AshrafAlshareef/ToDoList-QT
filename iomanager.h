#pragma once

#include <string>
#include <vector>


class IOManager
   {
   public:
      IOManager();
      static std::vector<std::string*> readFile(const std::string& path);
      static void createFile(std::string path);
      static void writeFile(std::string path, std::string);
      static std::string* split(std::string l, char regex);
      static bool exists(std::string path);
   };
