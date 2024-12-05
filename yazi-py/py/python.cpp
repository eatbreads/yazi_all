#include <py/python.h>
using namespace yazi::py;

Python::Python()
{
    // 初始化python接口
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        throw std::logic_error("python init failed");
    }
}

Python::~Python()
{
    // 结束python接口初始化
    Py_Finalize();
}

void Python::run(const string & str)
{
    PyRun_SimpleString(str.c_str());
}