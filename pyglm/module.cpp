#include "Vector_wrap.hpp"
#include "Quaternion_wrap.hpp"

#include "CXX/Objects.hxx"
#include "CXX/Extensions.hxx"

class pyglm_module : public Py::ExtensionModule<pyglm_module>
{
public:
    pyglm_module()
        : Py::ExtensionModule<pyglm_module>("pyglm") // this must be name of the file on disk e.g. simple.so or simple.pyd
    {
        Vector::init_type();
        Quaternion::init_type();

        add_keyword_method("rotQ", &pyglm_module::rotationQ, "Creates a quaternion representing a rotation around an axis 'axis' by an angle of 'angle'.");

        initialize("documentation for pyglm module");

        moduleDictionary()["Vector"] = Vector::type();
        moduleDictionary()["Quaternion"] = Quaternion::type();
    }

    virtual ~pyglm_module()
    { }

    Py::Object rotationQ(const Py::Tuple& args, const Py::Dict& kwargs)
    {
        Py::Callable type(Quaternion::type());
        if(args.length() == 4 && kwargs.length() == 0) {
            return Quaternion::QuaternionObject(type.apply(Py::TupleN(Py::TupleN(args[0], args[1], args[2]), args[3]), kwargs));
        } else if(args.length() == 3 && kwargs.length() == 1) {
            return Quaternion::QuaternionObject(type.apply(Py::TupleN(args), kwargs));
        } else {
            return Quaternion::QuaternionObject(type.apply(args, kwargs));
        }
    }
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

