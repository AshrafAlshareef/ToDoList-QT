#include "iomanager.h"
#include <fstream>
#include <iostream>
#include <sstream>


IOManager::IOManager()
   {

   }


bool IOManager::exists(std::string path)
   {
   std::ifstream infile;
   infile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

   try
      {
      infile.open(path);
      infile.close();
      return true;
      }
   catch (const std::ifstream::failure& e)
      {
      return false;
      }
   }


std::vector<std::string*> IOManager::readFile(std::string path)
   {
   std::vector<std::string*> data;
   std::string str;
   std::ifstream infile;
   infile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

   try
      {
      infile.open(path);
      while (!infile.eof())
         {
         getline(infile, str);
         if (str.length() > 0)
            {
            data.push_back(IOManager::split(str, ';'));
            }
         }
      infile.close();
      }
   catch (const std::ifstream::failure& e)
      {
      }

   return data;
   }


void IOManager::writeFile(std::string path, std::string file)
   {
   std::ofstream outfile(path);
   outfile << file;
   outfile.close();
   }


void IOManager::createFile(std::string path)
   {
   std::ofstream{path};
   }


std::string* IOManager::split(std::string l, char regex)
   {
   std::vector<std::string> vect;
   std::stringstream ss(l);
   std::string token;

   while (getline(ss,token, regex))
      {
      vect.push_back(token);
      }

   unsigned int i;
   std::string *r = new std::string[vect.size()];
   for (i = 0; i < vect.size(); i++)
      {
      r[i] = vect.at(i);
      }

   return r;
   }
