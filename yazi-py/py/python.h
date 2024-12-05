#pragma once

#include <string>
using std::string;

#include <stdexcept>

#include <Python.h>
#include <py/module.h>
#include <py/class.h>
#include <py/object.h>
#include <py/function.h>
#include <py/argument.h>

namespace yazi
{
    namespace py
    {
        class Python
        {
        public:
            Python();
            ~Python();

            void run(const string & str);
        };
    }
}