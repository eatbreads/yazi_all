#pragma once

#include <Python.h>

namespace yazi
{
    namespace py
    {
        class Argument
        {
            friend class Object;
            friend class Function;
        public:
            Argument() = default;
            ~Argument() = default;

            template<typename ...Args>
            void bind(Args... args);

            template<typename R>
            R parse_result(PyObject* ret);

        protected:
            void bind_inner() {}

            template<typename T, typename ...Args>
            void bind_inner(T arg, Args... args);

            template<typename T>
            string data_flag();

        private:
            PyObject * m_args = nullptr;
            int m_num = 0;
            int m_pos = 0;
        };

        template<typename ...Args>
        void Argument::bind(Args... args)
        {
            m_num = sizeof...(Args);
            m_pos = 0;
            m_args = PyTuple_New(m_num);
            bind_inner(args...);
        }

        template<typename T, typename ...Args>
        void Argument::bind_inner(T arg, Args... args)
        {
            string flag = data_flag<T>();
            PyObject * val = Py_BuildValue(flag.c_str(), arg);
            PyTuple_SetItem(m_args, m_pos++, val);
            bind_inner(args...);
        }

        template<typename R>
        R Argument::parse_result(PyObject * ret)
        {
            R result;
            string flag = data_flag<R>();
            PyArg_Parse(ret, flag.c_str(), &result);
            return result;
        }

        template<typename T>
        string Argument::data_flag()
        {
            string flag;
            if (typeid(T) == typeid(bool))
            {
                flag = "b";
            }
            else if (typeid(T) == typeid(int))
            {
                flag = "i";
            }
            else if (typeid(T) == typeid(unsigned int))
            {
                flag = "I";
            }
            else if (typeid(T) == typeid(float))
            {
                flag = "f";
            }
            else if (typeid(T) == typeid(double))
            {
                flag = "d";
            }
            else if (typeid(T) == typeid(const char *))
            {
                flag = "s";
            }
            return flag;
        }
    }
}