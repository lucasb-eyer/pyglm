#include "Vector_wrap.hpp"

Vector::Vector(Py::PythonClassInstance *self, Py::Tuple &args, Py::Dict &kwds)
    : Py::PythonClass<Vector>::PythonClass(self, args, kwds)
    , m_vec()
{
    if(args.length() == 0) {
        // no-op.
    } else if(args.length() == 2) {
        m_vec = PyGlMath::Vector(Py::Float(args[0]), Py::Float(args[1]), 0.0f);
    } else if(args.length() == 3) {
        m_vec = PyGlMath::Vector(Py::Float(args[0]), Py::Float(args[1]), Py::Float(args[2]));
    } else if(args.length() == 4) {
        m_vec = PyGlMath::Vector(Py::Float(args[0]), Py::Float(args[1]), Py::Float(args[2]), Py::Float(args[3]));
    } else if(args.length() == 1 && args[0].isSequence()) {
        Py::Sequence s(args[0]);
        float x = Py::Float(s[0]);
        float y = s.length() > 1 ? Py::Float(s[1]) : 0.0f;
        float z = s.length() > 2 ? Py::Float(s[2]) : 0.0f;
        float w = s.length() > 3 ? Py::Float(s[3]) : 1.0f;
        m_vec = PyGlMath::Vector(x, y, z, w);
    } else {
        throw Py::ValueError("Invalid arguments to Vector constructor");
    }
}

Vector::VectorObject Vector::make_inst(const PyGlMath::Vector& v)
{
    Py::Callable type(Vector::type());
    return VectorObject(type.apply( Py::TupleN(Py::Float(v.x()), Py::Float(v.y()), Py::Float(v.z())), Py::Dict() ));
}

Vector::~Vector()
{ }

void Vector::init_type()
{
    behaviors().name("Vector");
    behaviors().doc("documentation for Vector class");
    behaviors().supportGetattro();
    behaviors().supportSetattro();
    behaviors().supportRichCompare();
    behaviors().supportRepr();
    behaviors().supportStr();
    behaviors().supportHash();
    behaviors().supportNumberType();

    PYCXX_ADD_VARARGS_METHOD(cross, cross, "Cross product of this vector with another one. Results in a new vector." );
    PYCXX_ADD_VARARGS_METHOD(dot, dot, "Dot product of this vector with another one. Results in a float." );
    PYCXX_ADD_NOARGS_METHOD(len, len, "Returns the length of the vector. (Not the dimensions.)");
    PYCXX_ADD_NOARGS_METHOD(normalize, normalize, "Normalizes (gives unit length to) the vector itself, returns nothing.");
    PYCXX_ADD_NOARGS_METHOD(normalized, normalized, "Returns a normalized (unit length) copy of this vector. Self remains unchanged.");
    PYCXX_ADD_KEYWORDS_METHOD(lerp, lerp, "Returns a new vector which is the linear interpolation between self and the first argument 'other' at the second argument 'between'.");

    // Call to make the type ready for use
    behaviors().readyType();
}

Py::Object Vector::getattro(const Py::String& name_)
{
    std::string name(name_.as_std_string("utf-8"));

    if(name == "x") {
        return Py::Float(m_vec.x());
    } else if(name == "y") {
        return Py::Float(m_vec.y());
    } else if(name == "z") {
        return Py::Float(m_vec.z());
    }

    // TODO: support swizzling?
    return genericGetAttro(name_);
}

int Vector::setattro(const Py::String& name_, const Py::Object &value)
{
    std::string name(name_.as_std_string("utf-8"));

    if(name == "x") {
        m_vec.x(Py::Float(value));
        return 0;
    } else if(name == "y") {
        m_vec.y(Py::Float(value));
        return 0;
    } else if(name == "z") {
        m_vec.z(Py::Float(value));
        return 0;
    // TODO: support swizzling?
    } else {
        return genericSetAttro(name_, value);
    }
}

Py::Object Vector::repr()
{
    std::OSTRSTREAM ss;
    ss << "Vector(" << m_vec.x() << "," << m_vec.y() << "," << m_vec.z() << ")";
    return Py::String(ss.str());
}

Py::Object Vector::str()
{
    return this->repr();
}

long Vector::hash()
{
    return Py::TupleN(Py::Float(m_vec.x()), Py::Float(m_vec.y()), Py::Float(m_vec.z())).hashValue();
}

Py::Object Vector::rich_compare(const Py::Object& other_, int op)
{
    // TODO: Vector < number type checks?
    if(Vector::check(other_)) {
        VectorObject other__(other_);
        const Vector& other = *other__.getCxxObject();
        switch(op) {
        case Py_EQ: return m_vec == other.m_vec ? Py::True() : Py::False();
        case Py_NE: return m_vec != other.m_vec ? Py::True() : Py::False();
        case Py_LT: return m_vec <  other.m_vec ? Py::True() : Py::False();
        case Py_LE: return m_vec <= other.m_vec ? Py::True() : Py::False();
        case Py_GT: return m_vec >  other.m_vec ? Py::True() : Py::False();
        case Py_GE: return m_vec >= other.m_vec ? Py::True() : Py::False();
        }
    } else {
        throw Py::TypeError("expecting Vector object for compare");
    }
}

Py::Object Vector::number_negative()
{
    return make_inst(-m_vec);
}

Py::Object Vector::number_positive()
{
    return make_inst(m_vec);
}

Py::Object Vector::number_absolute()
{
    return make_inst(m_vec.abs());
}

Py::Object Vector::number_invert()
{
    return make_inst(PyGlMath::Vector(1.0f/m_vec.x(), 1.0f/m_vec.y(), 1.0f/m_vec.z()));
}

Py::Object Vector::number_add(const Py::Object& other_)
{
    if(Vector::check(other_)) {
        VectorObject other__(other_);
        const Vector& other = *other__.getCxxObject();

        return make_inst(m_vec + other.m_vec);
    } else {
        throw Py::TypeError("expecting Vector object for addition");
    }
}

Py::Object Vector::number_subtract(const Py::Object& other_)
{
    if(Vector::check(other_)) {
        VectorObject other__(other_);
        const Vector& other = *other__.getCxxObject();

        return make_inst(m_vec - other.m_vec);
    } else {
        throw Py::TypeError("expecting Vector object for subtraction");
    }
}

Py::Object Vector::number_multiply(const Py::Object& other_)
{
    if(Vector::check(other_)) {
        VectorObject other__(other_);
        const Vector& other = *other__.getCxxObject();

        return make_inst(m_vec * other.m_vec);
    }

    try {
        Py::Float other(other_);

        return make_inst(m_vec * other);
    } catch(const Py::Exception& ) {
        throw Py::TypeError("A vector may only be muliplied by a number or element-wise by a Vector instance.");
    }
}

Py::Object Vector::cross(const Py::Tuple &args)
{
    if(args.length() != 1) {
        throw Py::TypeError("Vector.cross product takes one argument");
    }

    if(!Vector::check(args[0])) {
        throw Py::TypeError("Vector.cross product can only take a vector as argument");
    }

    VectorObject other_(args[0]);
    const Vector& other = *other_.getCxxObject();

    return make_inst(m_vec.cross(other.m_vec));
}

Py::Object Vector::dot(const Py::Tuple &args)
{
    if(args.length() != 1) {
        throw Py::TypeError("Vector.dot product takes one argument");
    }

    if(!Vector::check(args[0])) {
        throw Py::TypeError("Vector.dot product takes a Vector argument");
    }

    VectorObject other_(args[0]);
    const Vector& other = *other_.getCxxObject();

    return Py::Float(m_vec.dot(other.m_vec));
}

Py::Object Vector::len()
{
    return Py::Float(m_vec.len());
}

Py::Object Vector::normalize()
{
    m_vec.normalize();
    return Py::None();
}

Py::Object Vector::normalized()
{
    return make_inst(m_vec.normalized());
}

Py::Object Vector::lerp(const Py::Tuple& args, const Py::Dict& kwargs)
{
    if(args.length() + kwargs.length() != 2) {
        throw Py::ValueError("Vector.lerp takes two arguments: first ('other') another vector and second ('between') a number or a vector for element-wise lerp.");
    }

    Py::Object other_arg;
    if(args.length() > 0) {
        if(!Vector::check(args[0])) {
            throw Py::TypeError("Vector.lerp takes a Vector as first argument");
        }
        other_arg = args[0];
    } else {
        if(!kwargs.hasKey("other")) {
            throw Py::ValueError("Vector.lerp needs the 'other' argument");
        }
        other_arg = kwargs.getItem("other");
    }

    VectorObject other_(other_arg);
    const Vector& other = *other_.getCxxObject();

    Py::Object between_arg;
    if(args.length() == 2) {
        between_arg = args[1];
    } else if(kwargs.hasKey("between")) {
        between_arg = kwargs.getItem("between");
    } else {
        throw Py::ValueError("Vector.lerp needs the 'between' argument.");
    }

    if(Vector::check(between_arg)) {
        VectorObject between_(between_arg);
        const Vector& between = *between_.getCxxObject();

        return make_inst(m_vec.lerp(other.m_vec, between.m_vec));
    }

    try {
        Py::Float between(between_arg);

        return make_inst(m_vec.lerp(other.m_vec, between));
    } catch(const Py::Exception& ) {
        throw Py::TypeError("The second argument to Vector.lerp ('between') needs to be a numeric value or a vector.");
    }
}
