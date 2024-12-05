#pragma once

namespace yazi
{
    namespace serialize
    {
        class DataStream;

        class Serializable
        {
        public:
            virtual void serialize(DataStream & stream) const = 0;
            virtual bool unserialize(DataStream & stream) = 0;
        };//这个类就这么几行,特别简单,这些序列化接口是需要继承的类自己实现的
        //本来应该是要使用者自己override虚函数(这俩serialize)的,但是现在提供了宏就可以简化操作,在类的public使用这个宏即可
        //这个宏里面的write_args和read_args的设计很巧妙,支持可变参数
        //ps:反射要求数据成员是public的,但是序列化不需要,因为serialize是成员函数
        #define SERIALIZE(...)                              \
            void serialize(DataStream & stream) const       \
            {                                               \
                char type = DataStream::CUSTOM;             \
                stream.write((char *)&type, sizeof(char));  \
                stream.write_args(__VA_ARGS__);             \
            }                                               \
                                                            \
            bool unserialize(DataStream & stream)           \
            {                                               \
                char type;                                  \
                stream.read(&type, sizeof(char));           \
                if (type != DataStream::CUSTOM)             \
                {                                           \
                    return false;                           \
                }                                           \
                stream.read_args(__VA_ARGS__);              \
                return true;                                \
            }
    }
}                                           