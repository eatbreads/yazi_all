#pragma once

#include <map>
#include <functional>
#include <initializer_list>
#include <string>
using std::string;

#include <serialize/data_stream.h>
using namespace yazi::serialize;

namespace yazi
{
    namespace rpc
    {
        class Function
        {
        public:
            Function() = default;
            ~Function() = default;

            template <typename F>
            void bind(const string & name, F func);
            //call就是传进去一个序列化的对象(内置有buffer),然后接收也是用序列化接收,会在服务端解码
            //这个call不是函数模板,但是bind是,因为bind要处理很多种函数的绑定
            //这个call相对简单,不涉及模板,就是说底下那一堆模板的操作都和他没关系
            void call(const string & name, DataStream & in, DataStream & out);

        private:
            template <typename F>       //这个wrap的返回值就是void,用来适配value的function的void返回值
            void wrap(F func, DataStream & in, DataStream & out);

            template <typename R, typename ...Args>//这是wrap的具体实现,调用了下面那个impl
            void wrap_impl(R(*func)(Args...), DataStream & in, DataStream & out);

            template <typename R, typename ...Args>//真*具体实现
            void wrap_impl(std::function<R(Args...)> func, DataStream & in, DataStream & out);

            template<typename R, typename F, typename Tuple>    //下面这一整行都是返回类型
            typename std::enable_if<std::is_same<R, void>::value, int32_t>::type    //这里表示如果返回值是void,就把R设置成int
            call_impl(F func, Tuple args);

            template<typename R, typename F, typename Tuple>
            typename std::enable_if<!std::is_same<R, void>::value, R>::type         //前面加了个!,表示返回值不是void就正常使用R
            call_impl(F func, Tuple args);                                          //这边内部本质上是调用invoke

            template<typename R, typename F, typename Tuple>
            auto invoke(F && func, Tuple && t);

            template<typename R, typename F, typename Tuple, std::size_t... Index>
            auto invoke_impl(F && func, Tuple && t, std::index_sequence<Index...>);

            template<typename Tuple, std::size_t... I>  //用来逐个获取元组
            Tuple get_args(DataStream & ds, std::index_sequence<I...>);

            template<typename Tuple, std::size_t Id>    //获取单个元组
            void get_arg(DataStream & ds, Tuple & t);

        private:   //这里就是对应上面的call,第一参匹配key,后两参匹配value,但是这边返回值是void,不通用
            std::map<string, std::function<void(DataStream &, DataStream &)>> m_handlers;
        };          //但是返回值实际上不是void,后面会通过包装变成void

        template <typename F>
        void Function::bind(const string & name, F func)
        {       //这边就是bind是一层包装,用来变成function,wrap又是一层包装
            m_handlers[name] = std::bind(&Function::wrap<F>, this, func, std::placeholders::_1, std::placeholders::_2);
        }                                                   //this指针用于传入this,因为wrap是成员函数指针,第一参是this

        template <typename F>
        void Function::wrap(F func, DataStream & in, DataStream & out)
        {
            wrap_impl(func, in, out);
        }

        template <typename R, typename ...Args>     //这里都写成模板没有问题,因为我们设置远程函数确实是编译期设置的
        void Function::wrap_impl(R(*func)(Args...), DataStream & in, DataStream & out)
        {
            wrap_impl(std::function<R(Args...)>(func), in, out);//调用了下面的模板
        }
                        //R是返回类型
        template <typename R, typename ...Args>
        void Function::wrap_impl(std::function<R(Args...)> func, DataStream & in, DataStream & out)
        {   //args_type_tuple最终是一个tuple元组,元组的<>就是Args的类型
            using args_type_tuple = std::tuple<typename std::decay<Args>::type...>;//这一步操作可以获得Args的实际类型
            //这里获得参数数量,感觉等价于size...(Args),但是返回类型是这个tuple_size的value
            constexpr auto size = std::tuple_size<typename std::decay<args_type_tuple>::type>::value;
            //模板参数就是元组        这个第二参是根据传入size生成下标0-size-1列表index_sequence,用于模板元编程
            //最终参数保存在args_tuple里面了
            args_type_tuple args_tuple = get_args<args_type_tuple>(in, std::make_index_sequence<size>{});
            auto ret = call_impl<R>(func, args_tuple);      //底层使用invoke,底层返回值会到这里,然后注入进DataStream
            out << ret;
        }
        //这边直接在头文件里面写普通成员函数(非模板)所以加inline内联
        inline void Function::call(const string & name, DataStream & in, DataStream & out)
        {
            auto func = m_handlers[name];   //fun实际上是一个返回void,参数是俩DataStream的包装器
            func(in, out);
        }

        template<typename R, typename F, typename Tuple>
        typename std::enable_if<std::is_same<R, void>::value, int32_t>::type
        Function::call_impl(F func, Tuple args)     //这一层用来设置返回值
        {
            invoke<R>(func, args);
            return 0;
        }

        template<typename R, typename F, typename Tuple>
        typename std::enable_if<!std::is_same<R, void>::value, R>::type
        Function::call_impl(F func, Tuple args)
        {
            return invoke<R>(func, args);
        }

        template<typename R, typename F, typename Tuple>
        auto Function::invoke(F && func, Tuple && t)        //就也是把tuple传进来,然后用get和make_index然后解包传入fun
        {
            constexpr auto size = std::tuple_size<typename std::decay<Tuple>::type>::value;//拿到长度
            return invoke_impl<R>(std::forward<F>(func), std::forward<Tuple>(t), std::make_index_sequence<size>{});
        }

        template<typename R, typename F, typename Tuple, std::size_t... Index>
        auto Function::invoke_impl(F && func, Tuple && t, std::index_sequence<Index...>)
        {
            return func(std::get<Index>(std::forward<Tuple>(t))...);        //解包放进去,然后一层一层的返回上去
        }
        //这个I是非类型模板参数,而且是参数包形式,就是类似数组大小的N,因为这些事情要在编译期执行,所以要用这个来数值计算
        template<typename Tuple, std::size_t... Id>//这里就是表示很多个size_t(unsign int)/整数序列 ,Tuple是指定传入的,I是自己识别的
        Tuple Function::get_args(DataStream & ds, std::index_sequence<Id...>) //index<>要传入整数序列,如<1,2,3,4,5>
        {
            Tuple t;    //这个Tuple是模板参数,<>内是实际参数类型,这边...表示对I的整数序列执行都执行这个操作
            std::initializer_list<int>{((get_arg<Tuple, Id>(ds, t)), 0)...};
            return t;   //这样就对每一个元组的下标索引都执行了注入的操作,然后这个操作是通过初始化列表间接实现(生成临时初始化列表)
        }

        template<typename Tuple, std::size_t Id>
        void Function::get_arg(DataStream & ds, Tuple & t)//所有的参数其实都封装在ds里面
        {//Id是索引,表示元组中的第几个位置,返回的是引用,所以可以用ds注入
            ds >> std::get<Id>(t);          
        }
    }
}
