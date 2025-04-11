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


std::vector<std::string*> IOManager::readFile(const std::string& path)
   {
   std::vector<std::string*> data;
   std::string str;
   std::ifstream infile(path);

   if (!infile)
      {
      std::cerr << "Error opening file: " << path << std::endl;
      return data; // Return empty data on failure
      }

   while (std::getline(infile, str))
      {
      if (!str.empty())
         {
         // Replace the placeholder back to newlines
         std::string::size_type pos = 0;
         while ((pos = str.find("|n|", pos)) != std::string::npos)
            {
            str.replace(pos, 3, "\n"); // Replace "|n|" with actual newline
            pos += 1; // Move past the new character
            }
         data.push_back(IOManager::split(str, ';'));
         }
      }

   infile.close();
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
