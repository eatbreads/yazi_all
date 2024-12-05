#include <py/object.h>
using namespace yazi::py;

Object::Object(const Class & cls)
{
    m_object = PyEval_CallObject(cls.m_class, nullptr);
}