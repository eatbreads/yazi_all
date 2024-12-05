#pragma once

namespace yazi
{
    namespace utility
    {
        template <typename T>
        class Singleton
        {
        public:
            static T * instance()
            {
                static T instance;
                return &instance;
            }

        private:
            Singleton() = default;
            Singleton(const Singleton<T> &) = delete;
            Singleton<T> & operator = (const Singleton<T> &) = delete;
            ~Singleton() = default;
        };
        //在每个类 里面声明这个,就可以实现单例模式
        #define SINGLETON(classname)                                    \
            friend class Singleton<classname>;                          \
            private:                                                    \
                classname() = default;                                  \
                classname(const classname &) = delete;                  \
                classname & operator = (const classname &) = delete;    \
                ~classname() = default
    }
}