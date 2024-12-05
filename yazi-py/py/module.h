#pragma once

#include <string>
using std::string;

#include <stdexcept>
#include <Python.h>

namespace yazi
{
    namespace py
    {
        class Module
        {
            friend class Class;
            friend class Function;
        public:
            Module() = default;
            Module(const string & name);
            ~Module() = default;

            void import(const string & name);

        private:
            PyObject * m_module = nullptr;
        };
    }
}