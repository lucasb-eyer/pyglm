#include "Vector.hpp"

#include "CXX/Objects.hxx"
#include "CXX/Extensions.hxx"

class Vector : public Py::PythonClass<Vector>
{
public:
    Vector(Py::PythonClassInstance *self, Py::Tuple &args, Py::Dict &kwds);
    virtual ~Vector();

    static void init_type();

    typedef Py::PythonClassObject<Vector> VectorObject;
    static VectorObject make_inst(const PyGlMath::Vector& v);

private:
    Py::Object getattro(const Py::String& name_);
    int setattro(const Py::String& name_, const Py::Object &value);

    Py::Object repr();
    Py::Object str();
    long hash();
    Py::Object rich_compare(const Py::Object& other_, int op);

    Py::Object number_negative();
    Py::Object number_positive();
    Py::Object number_absolute();
    Py::Object number_invert();
    Py::Object number_add(const Py::Object& other_);
    Py::Object number_subtract(const Py::Object& other_);
    Py::Object number_multiply(const Py::Object& other_);

    Py::Object cross(const Py::Tuple &args);
    PYCXX_VARARGS_METHOD_DECL(Vector, cross);
    Py::Object dot(const Py::Tuple &args);
    PYCXX_VARARGS_METHOD_DECL(Vector, dot);
    Py::Object len();
    PYCXX_NOARGS_METHOD_DECL(Vector, len);
    Py::Object normalize();
    PYCXX_NOARGS_METHOD_DECL(Vector, normalize);
    Py::Object normalized();
    PYCXX_NOARGS_METHOD_DECL(Vector, normalized);
    Py::Object lerp(const Py::Tuple& args, const Py::Dict& kwargs);
    PYCXX_KEYWORDS_METHOD_DECL(Vector, lerp);

    PyGlMath::Vector m_vec;
};

