#include "Quaternion.hpp"

#include "CXX/Objects.hxx"
#include "CXX/Extensions.hxx"

class Quaternion : public Py::PythonClass<Quaternion>
{
public:
    Quaternion(Py::PythonClassInstance *self, Py::Tuple &args, Py::Dict &kwds);
    virtual ~Quaternion();

    static void init_type();

    typedef Py::PythonClassObject<Quaternion> QuaternionObject;
    static QuaternionObject make_inst(const PyGlMath::Quaternion& v);

private:
    Py::Object getattro(const Py::String& name_);
    int setattro(const Py::String& name_, const Py::Object &value);

    Py::Object repr();
    Py::Object str();
    long hash();
    Py::Object rich_compare(const Py::Object& other_, int op);

    Py::Object number_negative();
    Py::Object number_positive();
    Py::Object number_invert();
    Py::Object number_add(const Py::Object& other_);
    Py::Object number_subtract(const Py::Object& other_);
    Py::Object number_multiply(const Py::Object& other_);

    Py::Object dot(const Py::Tuple &args);
    PYCXX_VARARGS_METHOD_DECL(Quaternion, dot);
    Py::Object len();
    PYCXX_NOARGS_METHOD_DECL(Quaternion, len);
    Py::Object normalize();
    PYCXX_NOARGS_METHOD_DECL(Quaternion, normalize);
    Py::Object normalized();
    PYCXX_NOARGS_METHOD_DECL(Quaternion, normalized);
//     Py::Object lerp(const Py::Tuple& args, const Py::Dict& kwargs);
//     PYCXX_KEYWORDS_METHOD_DECL(Quaternion, lerp);

    PyGlMath::Quaternion m_quat;
};
