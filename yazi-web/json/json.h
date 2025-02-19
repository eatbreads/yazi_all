#pragma once

#include <ostream>
#include <vector>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
using std::string;


namespace yazi
{
    namespace json
    {
        class Json
        {
        public:
            enum Type       //这里就是全部json的类型了,有六个和一个空
            {
                JSON_NULL = 0,  // null value
                JSON_BOOL,      // bool value
                JSON_INT,       // integer value
                JSON_DOUBLE,    // double value
                JSON_STRING,    // string value
                JSON_ARRAY,     // array value,这边这个还支持数组
                JSON_OBJECT     // object value,这个对象就是键值对(json内部的数据存储就是键值对)
            };

            Json();
            Json(Type type);
            Json(bool value);
            Json(int value);
            Json(double value);
            Json(const char * value);
            Json(const string & value);
            Json(const Json & other);
            Json(Json && other);
            ~Json();

            Type type() const;

            bool is_null() const;
            bool is_bool() const;
            bool is_int() const;
            bool is_double() const;
            bool is_string() const;
            bool is_array() const;
            bool is_object() const;

            bool as_bool() const;
            int as_int() const;
            double as_double() const;
            string as_string() const;

            // number of values in array or object
            int size() const;

            // return true if empty array, empty object, or null, otherwise, false.
            bool empty() const;

            void clear();

            bool has(int index) const;
            bool has(const char * key) const;
            bool has(const string & key) const;

            Json get(int index) const;
            Json get(const char * key) const;
            Json get(const string & key) const;

            void remove(int index);
            void remove(const char * key);
            void remove(const string & key);

            // append value to array at the end.
            void append(const Json & value); 
            void append(Json && value);

            Json & operator = (bool value);
            Json & operator = (int value);
            Json & operator = (double value);
            Json & operator = (const char * value);
            Json & operator = (const string & value);
            Json & operator = (const Json & other);
            Json & operator = (Json && other) noexcept;

            bool operator == (const Json & other);
            bool operator != (const Json & other);

            Json & operator [] (int index);
            Json & operator [] (const char * key);
            Json & operator [] (const string & key);

            friend std::ostream & operator << (std::ostream & os, const Json & json)
            {
                os << json.str();
                return os;
            }

            operator bool();
            operator bool() const;

            operator int();
            operator int() const;

            operator double();
            operator double() const;

            operator string();
            operator string() const;  

            void load(const string & filename);
            void load(const char * buf, int len);
            string str() const;

            typedef std::vector<Json>::iterator iterator;
            iterator begin()            //这里提供了一对迭代器,但是这里应该忘记判断此时类型了
            {
                return (m_value.m_array)->begin();
            }
            iterator end()
            {
                return (m_value.m_array)->end();
            }

        private:
            void copy(const Json & other);
            void swap(Json & other);

        private:
            union Value         //这个联合体就是具体类型了
            {
                bool m_bool;
                int m_int;
                double m_double;
                std::string * m_string;     //注意string这些东西存放的是指针,他们不能放在联合体里面 
                std::vector<Json> * m_array;        //这边又一个数组,是当我们用下标[]的时候类型就会自己转化成数组了
                std::map<string, Json> * m_object;
            };

            Type m_type = JSON_NULL;
            Value m_value;
        };
    }
}