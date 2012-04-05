#include "Vector_wrap.hpp"
//#include "Quaternion_wrap.hpp"

#include "CXX/Objects.hxx"
#include "CXX/Extensions.hxx"

class pyglm_module : public Py::ExtensionModule<pyglm_module>
{
public:
    pyglm_module()
        : Py::ExtensionModule<pyglm_module>("pyglm") // this must be name of the file on disk e.g. simple.so or simple.pyd
    {
        Vector::init_type();
//        Quaternion::init_type();

        initialize("documentation for pyglm module");

        moduleDictionary()["Vector"] = Vector::type();
    }

    virtual ~pyglm_module()
    { }
};

#if defined( _WIN32 )
#define EXPORT_SYMBOL __declspec( dllexport )
#else
#define EXPORT_SYMBOL
#endif

extern "C" EXPORT_SYMBOL PyObject *PyInit_pyglm()
{
#if defined(PY_WIN32_DELAYLOAD_PYTHON_DLL)
    Py::InitialisePythonIndirectPy::Interface();
#endif

    static pyglm_module* pyglm = new pyglm_module;
    return pyglm->module().ptr();
}

// symbol required for the debug version
extern "C" EXPORT_SYMBOL PyObject *PyInit_pyglm_d()
{ 
    return PyInit_pyglm();
}

