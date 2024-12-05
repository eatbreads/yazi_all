#include <utility/ini_file.h>
using namespace yazi::utility;

IniFile::IniFile(const string & filename)
{
    load(filename);
}

string IniFile::trim(string s)
{
    if (s.empty())
    {
        return s;
    }//我们是支持ini文件有空格啥的,要兼容笨蛋
    s.erase(0, s.find_first_not_of(" \r\n"));//注意看,这里第一个字符是空格,就是说会删掉空格和\r\n
    s.erase(s.find_last_not_of(" \r\n") + 1);//然后这边是删掉尾后的这些字符
    return s;
}

bool IniFile::load(const string & filename)
{
    m_sections.clear();
    m_filename = filename;
    std::ifstream ifs(filename);
    if (ifs.fail())
    {
        throw std::logic_error("loading ini file failed: " + m_filename);
    }

    string name;
    string line;
    while (std::getline(ifs, line))
    {
        line = trim(line);
        if (line.empty())
        {
            continue;
        }
        if (line[0] == '#' || line[0] == ';') // it's comment
        {
            continue;
        }
        if ('[' == line[0]) // it's section
        {
            auto pos = line.find_first_of(']');
            if (pos == std::string::npos)
            {
                throw std::logic_error("invalid section: " + line);
            }
            name = trim(line.substr(1, pos - 1));   //此时0是[,所以从1开始删
            m_sections[name] = Section();
        }
        else // 如果是键值对
        {
            auto pos = line.find_first_of('=');//定位到中间,然后对前后trim,存入map
            if (pos == std::string::npos)
            {
                throw std::logic_error("invalid option: " + line);
            }
            string key = line.substr(0, pos);
            key = trim(key);
            string value = line.substr(pos + 1);
            value = trim(value);
            m_sections[name][key] = value;
        }
    }
    return true;
}

void IniFile::save(const string & filename)
{
    std::ofstream ofs(filename.c_str());
    if (ofs.fail())
    {
        throw std::logic_error("saving ini file failed: " + m_filename);
    }
    ofs << str();
    ofs.close();
} 

string IniFile::str() const
{
    std::stringstream ss;
    for (const auto & section : m_sections)
    {
        ss << "[" << section.first << "]" << std::endl;
        for (const auto & option : section.second)
        {
            ss << option.first << " = " << option.second << std::endl;
        }
        ss << std::endl;
    }
    return ss.str();
}

void IniFile::show() const
{
    std::cout << str();
}

void IniFile::clear()
{
    m_sections.clear();
}

bool IniFile::has(const string & section)
{
    return m_sections.find(section) != m_sections.end();
}

bool IniFile::has(const string & section, const string & key)
{
    auto it = m_sections.find(section);
    if (it == m_sections.end())
    {
        return false;
    }
    return it->second.find(key) != it->second.end();
}

Value & IniFile::get(const string & section, const string & key)
{
    return m_sections[section][key];
}

void IniFile::set(const string & section, const string & key, const Value & value)
{
    m_sections[section][key] = value;
}

void IniFile::remove(const string & section)
{
    m_sections.erase(section);
}

void IniFile::remove(const string & section, const string & key)
{
    auto it = m_sections.find(section);
    if (it == m_sections.end())
    {
        return;
    }
    it->second.erase(key);
}

