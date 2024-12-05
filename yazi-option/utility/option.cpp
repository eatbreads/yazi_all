#include <utility/option.h>
using namespace yazi::utility;

void Option::add(const string & name, Type type)
{
    m_opts[name] = type;
}

Option::Type Option::type(const string & opt) const
{
    auto it = m_opts.find(opt);
    if (it == m_opts.end())
    {
        return OPT_UNKNOWN; 
    }
    return it->second;
}

void Option::parse(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i];
        if (arg.substr(0, 1) != "-")
        {
            // 忽略普通参数,如-a -b 123 --hello这种,123就是普通参数,实际上是-b的值,所以不能在这里解析
            continue;
        }
        if (arg.substr(0, 2) == "--")
        {
            // 长参数解析
            string str = arg.substr(2);
            auto pos = str.find('=');
            if (pos != std::string::npos)
            {
                // 选项可能是必选参数, 或者是可选参数
                string opt = str.substr(0, pos);
                string val = str.substr(pos + 1);
                switch (type(opt))
                {
                    case OPT_NO:
                    {
                        throw std::logic_error("no argument option: " + opt);
                    }
                    case OPT_OPTIONAL:
                    case OPT_REQUIRED:
                    {
                        m_args[opt] = val;
                        break;
                    }
                    default:
                        break;
                }
            }
            else
            {
                // 选项可能是必选参数, 或者是可选参数, 或者无参数
                switch (type(str))
                {
                    case OPT_NO:
                    case OPT_OPTIONAL:
                    {
                        m_args[str] = "";
                    
                        break;
                    }
                    case OPT_REQUIRED:
                    {
                        if (i + 1 >= argc)
                        {
                            throw std::logic_error("option required argument: " + str);
                        }
                        string val = argv[i + 1];
                        if (val.substr(0, 1) == "-")
                        {
                            throw std::logic_error("option missing argument: " + str);
                        }
                        m_args[str] = val;
                        i++;
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        else
        {
            // 短参数解析
            string opt = arg.substr(1, 1);
            switch (type(opt))
            {
                case OPT_NO:
                {
                    if (arg.length() >= 2)
                    {
                        // 合并参数
                        for (size_t k = 1; k < arg.length(); k++)
                        {
                            string o(1, arg[k]);
                            if (type(o) != OPT_NO)
                            {
                                continue;
                            }
                            m_args[o] = "";
                        }
                    }
                    break;
                }
                case OPT_OPTIONAL:
                {
                    if (arg.length() > 2)
                    {
                        m_args[opt] = arg.substr(2);
                    }
                    else
                    {
                        m_args[opt] = "";
                    }
                    break;
                }
                case OPT_REQUIRED:
                {
                    if (i + 1 >= argc)
                    {
                        throw std::logic_error("option required argument: " + opt);
                    }
                    string val = argv[i + 1];
                    if (val.substr(0, 1) == "-")
                    {
                        throw std::logic_error("option missing argument: " + opt);
                    }
                    m_args[opt] = val;
                    i++;
                    break;
                }
                default:
                    break;
            }
        }
    }
}

bool Option::has(const string & opt) const
{
    auto it = m_opts.find(opt);
    if (it == m_opts.end())
    {
        return false;
    }
    return m_args.find(opt) != m_args.end();
}

Value Option::get(const string & opt)
{
    auto it = m_opts.find(opt);
    if (it == m_opts.end())
    {
        return Value("");
    }
    switch (it->second)
    {
        case OPT_NO:
        {
            return Value(m_args.find(opt) != m_args.end());
        }
        case OPT_OPTIONAL:
        case OPT_REQUIRED:
        {
            return Value(m_args[opt]);
        }
        default:
            break;
    }
    return Value("");
}


void Option::show() const
{
    for (const auto & pair : m_args)
    {
        std::cout << pair.first << ":" << pair.second << std::endl;
    }
}