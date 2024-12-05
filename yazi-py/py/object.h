#pragma once

#include <py/class.h>
#include <py/argument.h>

namespace yazi
{
    namespace py
    {
        class Object
        {
            friend class Function;
        public:
            Object() = default;

            Object(const Class & cls);

            template<typename ...Args>
            Object(const Class & cls, Args... args);

            ~Object() = default;

        private:
            PyObject * m_object = nullptr;
        };

        template<typename ...Args>
        Object::Object(const Class & cls, Args... args)
        {
            auto arg = Argument();
            arg.bind(args...);
            m_object = PyEval_CallObject(cls.m_class, arg.m_args);
            if (m_object == nullptr)
            {
                throw std::logic_error("create object failed");
            }
        }
    }
}