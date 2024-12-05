#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
using std::string;

#include <sstream>
using std::stringstream;

#include <fstream>
using std::ifstream;
using std::ofstream; 

#include <utility/value.h>

namespace yazi
{
    namespace utility
    {
        class IniFile
        {
            typedef std::map<string, Value> Section;
        public:  
            IniFile() = default;
            IniFile(const string & filename);
            ~IniFile() = default;

            bool load(const string & filename);//可以重复载入,在构造函数内部会调用
            void save(const string & filename);
            string str() const; //拿到内部实际的值,会拼接起来
            void show() const;
            void clear();

            Value & get(const string & section, const string & key);
            void set(const string & section, const string & key, const Value & value);

            bool has(const string & section);
            bool has(const string & section, const string & key);

            void remove(const string & section);
            void remove(const string & section, const string & key);

            Section & operator [] (const string & section)
            {
                return m_sections[section]; //这个就是简易调用,和上面get没区别
            }

        private:
            string trim(string s);

        private:
            string m_filename;
            std::map<string, Section> m_sections;
        };
    }
}
