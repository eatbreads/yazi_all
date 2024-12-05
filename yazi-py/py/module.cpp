#include <py/module.h>
using namespace yazi::py;

Module::Module(const string & name)
{
    import(name);
}

void Module::import(const string & name)
{
    m_module = PyImport_ImportModule(name.c_str());
    if (m_module == nullptr)
    {
        throw std::logic_error("module not found: " + name);
    }
}
