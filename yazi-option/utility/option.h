#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <sstream>
#include <string>
using std::string;

#include <utility/value.h>


namespace yazi
{
    namespace utility
    {
        class Option
        {
        public: 
            enum Type
            {
                OPT_UNKNOWN = 0,        //未知的选项
                OPT_NO,                 //无参的选项
                OPT_REQUIRED,           //必选的选项
                OPT_OPTIONAL,           //可选的选项
            };
            Option() = default;
            ~Option() = default;

            void add(const string & opt, Type type);
            Type type(const string & opt) const;

            void parse(int argc, char *argv[]);
            bool has(const string & opt) const;
            Value get(const string & opt);

            void show() const;

        private:
            std::map<string, Type> m_opts;
            std::map<string, string> m_args;
        };
    }
}