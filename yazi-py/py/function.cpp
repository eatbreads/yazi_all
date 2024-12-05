#include <py/function.h>
using namespace yazi::py;

Function::Function(const Module & module, const string & name)
{
    PyObject* func = PyObject_GetAttrString(module.m_module, name.c_str());
    if (!func || !PyCallable_Check(func))
    {
        throw std::logic_error("function not found: " + name);
    }
    m_func = func;
}

Function::Function(const Object & object, const string &name)
{
    PyObject* func = PyObject_GetAttrString(object.m_object, name.c_str());
    if (!func || !PyCallable_Check(func))
    {
        throw std::logic_error("function not found: " + name);
    }
    m_func = func;
}

void Function::call()
{
    PyObject_CallObject(m_func, nullptr);
}
