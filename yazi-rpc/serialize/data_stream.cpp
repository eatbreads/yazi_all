#include <serialize/data_stream.h>
using namespace yazi::serialize;

DataStream::DataStream() : m_pos(0)
{
    m_byteorder = byteorder();      //在构造函数内部设置大小端
}

DataStream::DataStream(const string & str) : m_pos(0)
{
    m_byteorder = byteorder();
    m_buf.clear();
    reserve(str.size());
    write(str.data(), str.size());
}

void DataStream::reserve(int len)
{
    int size = m_buf.size();
    int cap = m_buf.capacity();
    if (size + len > cap)
    {
        while (size + len > cap)
        {
            if (cap == 0)
            {
                cap = 1;
            }
            else
            {
                cap *= 2;
            }
        }
        m_buf.reserve(cap);
    }
}

DataStream::ByteOrder DataStream::byteorder()       //这边是检测大小端,如果是大端统一成小端来操作
{
    int n = 0x12345678;
    char str[4] = {0};
    memcpy(str, &n, sizeof(int));
    if (str[0] == 0x12)
    {
        return ByteOrder::BigEndian;
    }
    else
    {
        return ByteOrder::LittleEndian;
    }
}

void DataStream::show() const                   //这里其实就是一个打印内部信息的函数 
{
    int size = m_buf.size();
    std::cout << "data size = " << size << std::endl;
    int i = 0;
    while (i < size)
    {
        switch ((DataType)m_buf[i])
        {
        case DataType::BOOL:
            if ((int)m_buf[++i] == 0)
            {
                std::cout << "false";
            }
            else
            {
                std::cout << "true";
            }
            ++i;
            break;
        case DataType::CHAR:
            std::cout << m_buf[++i];
            ++i;
            break;
        case DataType::INT32:
            std::cout << *((int32_t *)(&m_buf[++i]));       //中间++i一次跳过标志位,然后最后跳过整个长度
            i += 4;
            break;
        case DataType::INT64:
            std::cout << *((int64_t *)(&m_buf[++i]));
            i += 8;
            break;
        case DataType::FLOAT:
            std::cout << *((float *)(&m_buf[++i]));
            i += 4;
            break;
        case DataType::DOUBLE:
            std::cout << *((double *)(&m_buf[++i]));
            i += 8;
            break;
        case DataType::STRING:
            if ((DataType)m_buf[++i] == DataType::INT32)
            {
                int len = *((int *)(&m_buf[++i]));
                i += 4;
                std::cout << string(&m_buf[i], len);
                i += len;
            }
            else
            {
                throw std::logic_error("parse string error");
            }
            break;
        case DataType::VECTOR:
            if ((DataType)m_buf[++i] == DataType::INT32)
            {
                int len = *((int *)(&m_buf[++i]));
                i += 4;
            }
            else
            {
                throw std::logic_error("parse vector error");
            }
            break;
        case DataType::MAP:
            if ((DataType)m_buf[++i] == DataType::INT32)
            {
                int len = *((int *)(&m_buf[++i]));
                i += 4;
            }
            else
            {
                throw std::logic_error("parse map error");
            }
            break;
        case DataType::SET:
            if ((DataType)m_buf[++i] == DataType::INT32)
            {
                int len = *((int *)(&m_buf[++i]));
                i += 4;
            }
            else
            {
                throw std::logic_error("parse set error");
            }
            break;
        case DataType::CUSTOM:
            break;
        default:
            break;
        }
    }
    std::cout << std::endl;
}

void DataStream::write(const char * data, int len)  //这个是通用的write,后续的write全都是使用这个
{
    reserve(len);
    int size = m_buf.size();
    m_buf.resize(m_buf.size() + len);       //要先使用resize调整size之后再memcpy
    std::memcpy(&m_buf[size], data, len);
}

void DataStream::write(bool value)
{
    char type = DataType::BOOL;                 //使用char来接收枚举(char可以承接256位)
    write((char *)&type, sizeof(char));         //进行强转,使用char*来写入
    write((char *)&value, sizeof(char));
}

void DataStream::write(char value)
{
    char type = DataType::CHAR;
    write((char *)&type, sizeof(char));
    write((char *)&value, sizeof(char));
}

void DataStream::write(int32_t value)
{
    char type = DataType::INT32;
    write((char *)&type, sizeof(char));
    if (m_byteorder == ByteOrder::BigEndian)        //这些有长度的统一判断字节序然后转换成小端序操作123
    {
        char * first = (char *)&value;
        char * last = first + sizeof(int32_t);
        std::reverse(first, last);
    }
    write((char *)&value, sizeof(int32_t));
}

void DataStream::write(int64_t value)
{
    char type = DataType::INT64;
    write((char *)&type, sizeof(char));
    if (m_byteorder == ByteOrder::BigEndian)
    {
        char * first = (char *)&value;
        char * last = first + sizeof(int64_t);
        std::reverse(first, last);
    }
    write((char *)&value, sizeof(int64_t));
}

void DataStream::write(float value)
{
    char type = DataType::FLOAT;
    write((char *)&type, sizeof(char));
    if (m_byteorder == ByteOrder::BigEndian)
    {
        char * first = (char *)&value;
        char * last = first + sizeof(float);
        std::reverse(first, last);
    }
    write((char *)&value, sizeof(float));
}

void DataStream::write(double value)
{
    char type = DataType::DOUBLE;
    write((char *)&type, sizeof(char));
    if (m_byteorder == ByteOrder::BigEndian)
    {
        char * first = (char *)&value;
        char * last = first + sizeof(double);
        std::reverse(first, last);
    }
    write((char *)&value, sizeof(double));
}

void DataStream::write(const char * value)
{
    char type = DataType::STRING;
    write((char *)&type, sizeof(char));
    int len = strlen(value);
    write(len);                 //这边和下面的string都会调用上面的int32_t的write
    write(value, len);          //所以这两个字符串的是会额外写入5字节的(1标志位,4字节int)
}

void DataStream::write(const string & value)
{
    char type = DataType::STRING;
    write((char *)&type, sizeof(char));
    int len = value.size();
    write(len);
    write(value.data(), len);       //这里应该是直接操纵了string的内部的地址了,直接传入const char*那个通用write
}

void DataStream::write(const Serializable & value)      //这个是支持对Serialize基类直接调用(用来给<<调用的)
{
    value.serialize(*this);         //如果已经通过宏重载了serialize,就可以执行这个函数(参数传入this指针)
}

bool DataStream::read(char * data, int len)   //这边是最基础的读码,是不涉及先读取一个标志位的操作
{                                             //同上面的write的基础操作
    std::memcpy(data, (char *)&m_buf[m_pos], len);
    m_pos += len;
    return true;
}

bool DataStream::read(bool & value)     //这边就是解码操作,要先判断标志位是否合法
{
    if (m_buf[m_pos] != DataType::BOOL)
    {
        return false;
    }
    ++m_pos;
    value = m_buf[m_pos];
    ++m_pos;
    return true;
}

bool DataStream::read(char & value)
{
    if (m_buf[m_pos] != DataType::CHAR)
    {
        return false;
    }
    ++m_pos;
    value = m_buf[m_pos];
    ++m_pos;
    return true;
}

bool DataStream::read(int32_t & value)      //这边是一个读取int,后续读取string会用到
{
    if (m_buf[m_pos] != DataType::INT32)
    {
        return false;
    }
    ++m_pos;
    value = *((int32_t *)(&m_buf[m_pos]));
    if (m_byteorder == ByteOrder::BigEndian)
    {
        char * first = (char *)&value;
        char * last = first + sizeof(int32_t);
        std::reverse(first, last);
    }
    m_pos += 4;
    return true;
}

bool DataStream::read(int64_t & value)
{
    if (m_buf[m_pos] != DataType::INT64)
    {
        return false;
    }
    ++m_pos;
    value = *((int64_t *)(&m_buf[m_pos]));
    if (m_byteorder == ByteOrder::BigEndian)
    {
        char * first = (char *)&value;
        char * last = first + sizeof(int64_t);
        std::reverse(first, last);
    }
    m_pos += 8;
    return true;
}

bool DataStream::read(float & value)
{
    if (m_buf[m_pos] != DataType::FLOAT)
    {
        return false;
    }
    ++m_pos;
    value = *((float *)(&m_buf[m_pos]));
    if (m_byteorder == ByteOrder::BigEndian)
    {
        char * first = (char *)&value;
        char * last = first + sizeof(float);
        std::reverse(first, last);
    }
    m_pos += 4;
    return true;
}

bool DataStream::read(double & value)
{
    if (m_buf[m_pos] != DataType::DOUBLE)
    {
        return false;
    }
    ++m_pos;
    value = *((double *)(&m_buf[m_pos]));
    if (m_byteorder == ByteOrder::BigEndian)
    {
        char * first = (char *)&value;
        char * last = first + sizeof(double);
        std::reverse(first, last);
    }
    m_pos += 8;
    return true;
}

bool DataStream::read(string & value)
{
    if (m_buf[m_pos] != DataType::STRING)
    {
        return false;
    }
    ++m_pos;
    int len;
    read(len);
    if (len < 0)
    {
        return false;
    }
    value.assign((char *)&(m_buf[m_pos]), len);
    m_pos += len;
    return true;
}

bool DataStream::read(Serializable & value)
{
    return value.unserialize(*this);
}

const char * DataStream::data() const
{
    return m_buf.data();
}

int DataStream::size() const
{
    return m_buf.size();
}

void DataStream::clear()
{
    m_buf.clear();
}

void DataStream::reset()
{
    m_pos = 0;
}

void DataStream::save(const string & filename)          
{//这里两个是文件操作,其实文件操作也挺简单的,就是把缓冲区写入文件
    std::ofstream ofs(filename);
    ofs.write(data(), size());
    ofs.flush();        //刷新缓冲区
    ofs.close();
}

void DataStream::load(const string & filename)
{
    std::ifstream ifs(filename);
    std::ostringstream oss;
    oss << ifs.rdbuf();                 //这个函数返回的是一个文件缓冲区
    const string & str = oss.str();     //这样可以直接拿到对应的拷贝(有点奇怪,const&会发生什么构造?)
    m_buf.clear();
    reserve(str.size());
    write(str.data(), str.size());      //然后就是正常写入(这边的write是我们自己写的write,写进m_buf的)
}
//下方一堆重载其实很简单,就是调用write或者read然后返回this引用而已
DataStream & DataStream::operator << (bool value)
{
    write(value);
    return *this;
}
DataStream & DataStream::operator << (char value)
{
    write(value);
    return *this;
}
DataStream & DataStream::operator << (int32_t value)
{
    write(value);
    return *this;
}
DataStream & DataStream::operator << (int64_t value)
{
    write(value);
    return *this;
}
DataStream & DataStream::operator << (float value)
{
    write(value);
    return *this;
}
DataStream & DataStream::operator << (double value)
{
    write(value);
    return *this;
}
DataStream & DataStream::operator << (const char * value)
{
    write(value);
    return *this;
}
DataStream & DataStream::operator << (const string & value)
{
    write(value);
    return *this;
}
DataStream & DataStream::operator << (const Serializable & value)
{
    write(value);
    return *this;
}
DataStream & DataStream::operator >> (bool & value)
{
    read(value);
    return *this;
}
DataStream & DataStream::operator >> (char & value)
{
    read(value);
    return *this;
}
DataStream & DataStream::operator >> (int32_t & value)
{
    read(value);
    return *this;
}
DataStream & DataStream::operator >> (int64_t & value)
{
    read(value);
    return *this;
}
DataStream & DataStream::operator >> (float & value)
{
    read(value);
    return *this;
}
DataStream & DataStream::operator >> (double & value)
{
    read(value);
    return *this; 
}
DataStream & DataStream::operator >> (string & value)
{
    read(value);
    return *this; 
}
DataStream & DataStream::operator >> (Serializable & value)
{
    read(value);
    return *this;
}