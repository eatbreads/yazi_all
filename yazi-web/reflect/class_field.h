#pragma once

#include <string>
using std::string;

namespace yazi
{
    namespace reflect
    {
        class ClassField        //封装了的类的字段
        {
        public:
            ClassField() : m_name(""), m_type(""), m_offset(0) {}
            ClassField(const string & name, const string & type, size_t offset) : m_name(name), m_type(type), m_offset(offset) {}
            ~ClassField() = default;

            const string & name() const
            {
                return m_name;
            }

            const string & type() const
            {
                return m_type;
            }

            size_t offset() const
            {
                return m_offset;
            }

        private:
            string m_name;      //类名
            string m_type;      //类型
            size_t m_offset;    //在类里面的偏移量
        };
    }
}