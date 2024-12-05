#pragma once

#include <string>
using std::string;

#include <py/module.h>
#include <py/object.h>
#include <py/argument.h>

namespace yazi
{
    namespace py
    {
        class Function
        {
        public:
            Function() = default;
            Function(const Module & module, const string & name);
            Function(const Object & object, const string & name);
            ~Function() = default;

            void call();

            template<typename R>
            R call();

            template<typename R, typename ...Args>
            R call(Args... args);

        private:
            PyObject * m_func = nullptr;
        };

        template<typename R>
        R Function::call()
        {
            auto arg = Argument();
            PyObject* ret = PyObject_CallObject(m_func, arg.m_args);
            return arg.parse_result<R>(ret);
        }

        template<typename R, typename ...Args>
        R Function::call(Args... args)
        {
            auto arg = Argument();
            arg.bind(args...);
            PyObject* ret = PyObject_CallObject(m_func, arg.m_args);
            return arg.parse_result<R>(ret);
        }
    }
}