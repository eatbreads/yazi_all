#pragma once

#include <string>
using std::string;

#include <py/module.h>

namespace yazi
{
    namespace py
    {
        class Class
        {
            friend class Object;
        public:
            Class() = default;
            Class(const Module & module, const string & name);
            ~Class() = default;

        private:
            PyObject * m_class = nullptr;
        };
    }
}