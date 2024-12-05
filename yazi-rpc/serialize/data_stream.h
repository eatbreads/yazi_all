#pragma once

#include <iostream>
#include <string>
using std::string;

#include <cstring>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <serialize/serializable.h>

namespace yazi
{
    namespace serialize
    {
        class DataStream
        {
        public:
            enum DataType       //这边表示每一种类型的枚举,用于传递的时候放在每份字节前面
            {
                BOOL = 0,       //比如bool传输是2字节(有一位来表示数据的类型)int传输是5字节
                CHAR,
                INT32,
                INT64,
                FLOAT,
                DOUBLE,
                STRING,
                VECTOR,
                LIST,
                MAP,
                SET,
                CUSTOM          //这个应该就是自定义类型了
            };

            enum ByteOrder          
            {
                BigEndian = 0,
                LittleEndian
            };

            DataStream();
            DataStream(const string & data);
            ~DataStream() = default;

            void show() const;
            void write(const char * data, int len);
            void write(bool value);
            void write(char value);
            void write(int32_t value);
            void write(int64_t value);
            void write(float value);
            void write(double value);
            void write(const char * value);
            void write(const string & value);
            void write(const Serializable & value);

            template <typename T>
            void write(const std::vector<T> & value);

            template <typename T>
            void write(const std::list<T> & value);

            template <typename K, typename V>
            void write(const std::map<K, V> & value);

            template <typename T>
            void write(const std::set<T> & value);

            template <typename T, typename ...Args>
            void write_args(const T & head, const Args&... args);

            void write_args() {}

            bool read(char * data, int len);
            bool read(bool & value);
            bool read(char & value);
            bool read(int32_t & value);
            bool read(int64_t & value);
            bool read(float & value);
            bool read(double & value);
            bool read(string & value);
            bool read(Serializable & value);

            template <typename T>
            bool read(std::vector<T> & value);

            template <typename T>
            bool read(std::list<T> & value);

            template <typename K, typename V>
            bool read(std::map<K, V> & value);

            template <typename T>
            bool read(std::set<T> & value);

            template <typename T, typename ...Args>
            bool read_args(T & head, Args&... args);

            bool read_args() { return true; }

            const char * data() const;
            int size() const;
            void clear();
            void reset();
            void save(const string & filename);
            void load(const string & filename);

            DataStream & operator << (bool value);
            DataStream & operator << (char value);
            DataStream & operator << (int32_t value);
            DataStream & operator << (int64_t value);
            DataStream & operator << (float value);
            DataStream & operator << (double value);
            DataStream & operator << (const char * value);
            DataStream & operator << (const string & value);
            DataStream & operator << (const Serializable & value);

            template <typename T>
            DataStream & operator << (const std::vector<T> & value);

            template <typename T>
            DataStream & operator << (const std::list<T> & value);

            template <typename K, typename V>
            DataStream & operator << (const std::map<K, V> & value);

            template <typename T>
            DataStream & operator << (const std::set<T> & value);

            DataStream & operator >> (bool & value);
            DataStream & operator >> (char & value);
            DataStream & operator >> (int32_t & value);
            DataStream & operator >> (int64_t & value);
            DataStream & operator >> (float & value);
            DataStream & operator >> (double & value);
            DataStream & operator >> (string & value);
            DataStream & operator >> (Serializable & value);

            template <typename T>
            DataStream & operator >> (std::vector<T> & value);

            template <typename T>
            DataStream & operator >> (std::list<T> & value);

            template <typename K, typename V>
            DataStream & operator >> (std::map<K, V> & value);

            template <typename T>
            DataStream & operator >> (std::set<T> & value);

        private:
            void reserve(int len);
            ByteOrder byteorder();

        private:                                                            
            std::vector<char> m_buf;                //内部的实际存储缓冲区,存放单个字节
            int m_pos;                              //这里是存储解码时候操作到哪个位置了          
            ByteOrder m_byteorder;                  
        };

        template <typename T>
        void DataStream::write(const std::vector<T> & value)        //这边vector的序列化使用了模板
        {                                                           //然后它的写入的操作也是直接用之前的write,就是对每一个类型的元素都单独写入
            char type = DataType::VECTOR;
            write((char *)&type, sizeof(char));
            int len = value.size();
            write(len);
            for (int i = 0; i < len; i++)
            {
                write(value[i]);                //如果vector是int的,就会调用int的write,我们要保证T本身是可以序列化的才可以
            }
        }

        template <typename T>
        void DataStream::write(const std::list<T> & value)
        {
            char type = DataType::LIST;
            write((char *)&type, sizeof(char));
            int len = value.size();
            write(len);
            for (auto it = value.begin(); it != value.end(); it++)
            {
                write((*it));
            }
        }

        template <typename K, typename V>
        void DataStream::write(const std::map<K, V> & value)
        {
            char type = DataType::MAP;
            write((char *)&type, sizeof(char));
            int len = value.size();
            write(len);
            for (auto it = value.begin(); it != value.end(); it++)//这个map也是很直白,就是之前一起序列化即可,反正到时
            {                                                     //候read的时候参数也会传进来类型,直接对应读取即可
                write(it->first);
                write(it->second);
            }
        }

        template <typename T>
        void DataStream::write(const std::set<T> & value)
        {
            char type = DataType::SET;
            write((char *)&type, sizeof(char));
            int len = value.size();
            write(len);
            for (auto it = value.begin(); it != value.end(); it++)
            {
                write(*it);
            }
        }

        template <typename T, typename ...Args>     //这个的设计很巧妙,别人传进来一串args,每调用一次args就会分离出去一个head
        void DataStream::write_args(const T & head, const Args&... args)  //然后最终就会只剩一个空的args,然后我们上面也已经实现了空的版本  
        {                                                                 //就是啥都不做
            write(head);
            write_args(args...);
        }

        template <typename T>
        bool DataStream::read(std::vector<T> & value)
        {
            value.clear();
            if (m_buf[m_pos] != DataType::VECTOR)
            {
                return false;
            }
            ++m_pos;
            int len;
            read(len);
            for (int i = 0; i < len; i++)
            {
                T v;
                read(v);
                value.push_back(v);
            }
            return true;
        }

        template <typename T>
        bool DataStream::read(std::list<T> & value)
        {
            value.clear();
            if (m_buf[m_pos] != DataType::LIST)
            {
                return false;
            }
            ++m_pos;
            int len;
            read(len);
            for (int i = 0; i < len; i++)
            {
                T v;
                read(v);
                value.push_back(v);
            }
            return true;
        }

        template <typename K, typename V>
        bool DataStream::read(std::map<K, V> & value)
        {
            value.clear();
            if (m_buf[m_pos] != DataType::MAP)
            {
                return false;
            }
            ++m_pos;
            int len;
            read(len);
            for (int i = 0; i < len; i++)
            {
                K k;
                read(k);

                V v;
                read(v);
                value[k] = v;
            }
            return true;
        }

        template <typename T>
        bool DataStream::read(std::set<T> & value)
        {
            value.clear();
            if (m_buf[m_pos] != DataType::SET)
            {
                return false;
            }
            ++m_pos;
            int len;
            read(len);
            for (int i = 0; i < len; i++)
            {
                T v;
                read(v);
                value.insert(v);
            }
            return true;
        }

        template <typename T, typename ...Args>
        bool DataStream::read_args(T & head, Args&... args)
        {
            read(head);
            return read_args(args...);
        }

        template <typename T>
        DataStream & DataStream::operator << (const std::vector<T> & value)
        {
            write(value);
            return *this;
        }

        template <typename K, typename V>
        DataStream & DataStream::operator << (const std::map<K, V> & value)
        {
            write(value);
            return *this;
        }

        template <typename T>
        DataStream & DataStream::operator << (const std::set<T> & value)
        {
            write(value);
            return *this;
        }

        template <typename T>
        DataStream & DataStream::operator >> (std::vector<T> & value)
        {
            read(value);
            return *this;
        }

        template <typename T>
        DataStream & DataStream::operator >> (std::list<T> & value)
        {
            read(value);
            return *this;
        }

        template <typename K, typename V>
        DataStream & DataStream::operator >> (std::map<K, V> & value)
        {
            read(value);
            return *this;
        }

        template <typename T>
        DataStream & DataStream::operator >> (std::set<T> & value)
        {
            read(value);
            return *this;
        }
    }
}