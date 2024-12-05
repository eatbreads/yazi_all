#include <py/class.h>
using namespace yazi::py;

Class::Class(const Module & module, const string & name)
{
    PyObject* cls = PyObject_GetAttrString(module.m_module, name.c_str());
    if (!cls)
    {
        throw std::logic_error("class not found: " + name);
    }
    m_class = cls;
}
