#include "Quaternion_wrap.hpp"
#include "Vector_wrap.hpp"
#include "Util.hpp"

Quaternion::Quaternion(Py::PythonClassInstance *self, Py::Tuple &args, Py::Dict &kwds)
    : Py::PythonClass<Quaternion>::PythonClass(self, args, kwds)
    , m_quat()
{
    int nkwd = kwds.length();
    int narg = args.length();
    if(narg == 0 && nkwd == 0) {
        // no-op.
    } else if(narg == 3 && nkwd == 0) {
        m_quat = PyGlMath::Quaternion(Py::Float(args[0]), Py::Float(args[1]), Py::Float(args[2]));
    } else if(narg == 4 && nkwd == 0) {
        m_quat = PyGlMath::Quaternion(Py::Float(args[0]), Py::Float(args[1]), Py::Float(args[2]), Py::Float(args[3]));
    } else if(narg == 1 && nkwd == 0 && args[0].isSequence()) {
        Py::Sequence s(args[0]);
        float x = Py::Float(s[0]);
        float y = s.length() > 1 ? Py::Float(s[1]) : 0.0f;
        float z = s.length() > 2 ? Py::Float(s[2]) : 0.0f;
        float w = s.length() > 3 ? Py::Float(s[3]) : 1.0f;
        m_quat = PyGlMath::Quaternion(x, y, z, w);
    } else if(narg + nkwd == 2) {
        // Axis-angle notation
        Py::Object axis_obj;
        Py::Float angle_obj;
        bool angle_is_degrees = false;
        if(narg == 2) {
            axis_obj = args[0];
            angle_obj = args[1];
        } else {
            if(narg == 1) {
                axis_obj = args[0];
            } else if(kwds.hasKey("axis")) {
                axis_obj = kwds.getItem("axis");
            } else {
                throw Py::ValueError("Quaternion takes an axis in the form of a Vector or an iterable (tuple, list, ...) as first argument or as argument named 'axis'.");
            }
            if(kwds.hasKey("degrees")) {
                angle_obj = kwds.getItem("degrees");
                angle_is_degrees = true;
            } else if(kwds.hasKey("deg")) {
                angle_obj = kwds.getItem("deg");
                angle_is_degrees = true;
            } else if(kwds.hasKey("radians")) {
                angle_obj = kwds.getItem("radians");
            } else if(kwds.hasKey("rad")) {
                angle_obj = kwds.getItem("rad");
            } else if(kwds.hasKey("angle")) {
                angle_obj = kwds.getItem("angle");
            } else {
                throw Py::ValueError("Quaternion takes one of 'degrees', 'deg', 'radians', 'rad' or 'angle' as keyword arguments for specifying the rotation angle.");
            }
        }

        float rad = angle_is_degrees ? float(angle_obj)*PyGlMath::deg2rad : float(angle_obj);
        if(Vector::check(axis_obj)) {
            Vector::VectorObject axis_obj_(axis_obj);
            const PyGlMath::Vector& axis = axis_obj_.getCxxObject()->m_vec;
            m_quat = PyGlMath::Quaternion::rotation(axis, rad);
        } else if(axis_obj.isSequence()) {
            Py::Sequence s(axis_obj);
            float x = s.length() > 0 ? Py::Float(s[0]) : 0.0f;
            float y = s.length() > 1 ? Py::Float(s[1]) : 0.0f;
            float z = s.length() > 2 ? Py::Float(s[2]) : 0.0f;
            m_quat = PyGlMath::Quaternion::rotation(x, y, z, rad);
        } else {
            throw Py::ValueError("Quaternion takes an axis in the form of a Vector or an iterable (tuple, list, ...) as first argument or as argument named 'axis'.");
        }
    } else {
        throw Py::ValueError("Invalid arguments to Quaternion constructor");
    }
}

Quaternion::QuaternionObject Quaternion::make_inst(const PyGlMath::Quaternion& v)
{
    Py::Callable type(Quaternion::type());
    return QuaternionObject(type.apply( Py::TupleN(Py::Float(v.x()), Py::Float(v.y()), Py::Float(v.z()), Py::Float(v.w())), Py::Dict() ));
}

Quaternion::~Quaternion()
{ }

void Quaternion::init_type()
{
    behaviors().name("Quaternion");
    behaviors().doc("documentation for Quaternion class");
    behaviors().supportGetattro();
    behaviors().supportSetattro();
    behaviors().supportRichCompare();
    behaviors().supportRepr();
    behaviors().supportStr();
    behaviors().supportHash();
    behaviors().supportNumberType();

    PYCXX_ADD_VARARGS_METHOD(dot, dot, "Dot product of this vector with another one. Results in a float." );
    PYCXX_ADD_NOARGS_METHOD(len, len, "Returns the length of the vector. (Not the dimensions.)");
    PYCXX_ADD_NOARGS_METHOD(normalize, normalize, "Normalizes (gives unit length to) the vector itself, returns nothing.");
    PYCXX_ADD_NOARGS_METHOD(normalized, normalized, "Returns a normalized (unit length) copy of this vector. Self remains unchanged.");
//     PYCXX_ADD_KEYWORDS_METHOD(lerp, lerp, "Returns a new vector which is the linear interpolation between self and the first argument 'other' at the second argument 'between'.");

    // Call to make the type ready for use
    behaviors().readyType();
}

Py::Object Quaternion::getattro(const Py::String& name_)
{
    std::string name(name_.as_std_string("utf-8"));

    if(name == "x") {
        return Py::Float(m_quat.x());
    } else if(name == "y") {
        return Py::Float(m_quat.y());
    } else if(name == "z") {
        return Py::Float(m_quat.z());
    } else if(name == "w") {
        return Py::Float(m_quat.w());
    } else if(name == "angle" || name == "rad" || name == "radians") {
        return Py::Float(m_quat.angle());
    } else if(name == "deg" || name == "degrees") {
        return Py::Float(m_quat.angle()*PyGlMath::rad2deg);
    } else if(name == "axis") {
        return Vector::make_inst(m_quat.axis());
    }

    // TODO: support swizzling?
    return genericGetAttro(name_);
}

int Quaternion::setattro(const Py::String& name_, const Py::Object &value)
{
    std::string name(name_.as_std_string("utf-8"));

    if(name == "x") {
        m_quat.x(Py::Float(value));
    } else if(name == "y") {
        m_quat.y(Py::Float(value));
    } else if(name == "z") {
        m_quat.z(Py::Float(value));
    } else if(name == "w") {
        m_quat.w(Py::Float(value));
    // TODO: support swizzling?
    } else if(name == "axis") {
        if(Vector::check(value)) {
            Vector::VectorObject axis_obj(value);
            const PyGlMath::Vector& axis = axis_obj.getCxxObject()->m_vec;
            m_quat = PyGlMath::Quaternion::rotation(axis, m_quat.angle());
        } else {
            Vector::VectorObject axis_obj(Py::Callable(Vector::type()).apply(value, Py::Dict()));
            const PyGlMath::Vector& axis = axis_obj.getCxxObject()->m_vec;
            m_quat = PyGlMath::Quaternion::rotation(axis, m_quat.angle());
        }
    } else if(name == "angle" || name == "rad" || name == "radians") {
        m_quat = PyGlMath::Quaternion::rotation(m_quat.axis(), Py::Float(value));
    } else if(name == "deg" || name == "degrees") {
        m_quat = PyGlMath::Quaternion::rotation(m_quat.axis(), float(Py::Float(value))*PyGlMath::deg2rad);
    } else {
        return genericSetAttro(name_, value);
    }

    return 0;
}

Py::Object Quaternion::repr()
{
    std::OSTRSTREAM ss;
    ss << "Quaternion(" << m_quat.x() << "," << m_quat.y() << "," << m_quat.z() << "," << m_quat.w() << ")";
    return Py::String(ss.str());
}

Py::Object Quaternion::str()
{
    return this->repr();
}

long Quaternion::hash()
{
    return Py::TupleN(Py::Float(m_quat.x()), Py::Float(m_quat.y()), Py::Float(m_quat.z()), Py::Float(m_quat.w())).hashValue();
}

Py::Object Quaternion::rich_compare(const Py::Object& other_, int op)
{
    // TODO: Quaternion < number type checks?
    if(Quaternion::check(other_)) {
        QuaternionObject other__(other_);
        const Quaternion& other = *other__.getCxxObject();
        switch(op) {
        case Py_EQ: return m_quat == other.m_quat ? Py::True() : Py::False();
        case Py_NE: return m_quat != other.m_quat ? Py::True() : Py::False();
        case Py_LT: return m_quat <  other.m_quat ? Py::True() : Py::False();
        case Py_LE: return m_quat <= other.m_quat ? Py::True() : Py::False();
        case Py_GT: return m_quat >  other.m_quat ? Py::True() : Py::False();
        case Py_GE: return m_quat >= other.m_quat ? Py::True() : Py::False();
        }
    } else {
        throw Py::TypeError("expecting Quaternion object for compare");
    }
}

Py::Object Quaternion::number_negative()
{
    return make_inst(-m_quat);
}

Py::Object Quaternion::number_positive()
{
    return make_inst(m_quat);
}

Py::Object Quaternion::number_invert()
{
    return make_inst(PyGlMath::Quaternion(1.0f/m_quat.x(), 1.0f/m_quat.y(), 1.0f/m_quat.z()));
}

Py::Object Quaternion::number_add(const Py::Object& other_)
{
    if(Quaternion::check(other_)) {
        QuaternionObject other__(other_);
        const Quaternion& other = *other__.getCxxObject();

        return make_inst(m_quat + other.m_quat);
    } else {
        throw Py::TypeError("expecting Quaternion object for addition");
    }
}

Py::Object Quaternion::number_subtract(const Py::Object& other_)
{
    if(Quaternion::check(other_)) {
        QuaternionObject other__(other_);
        const Quaternion& other = *other__.getCxxObject();

        return make_inst(m_quat - other.m_quat);
    } else {
        throw Py::TypeError("expecting Quaternion object for subtraction");
    }
}

Py::Object Quaternion::number_multiply(const Py::Object& other_)
{
    if(Quaternion::check(other_)) {
        QuaternionObject other__(other_);
        const Quaternion& other = *other__.getCxxObject();

        return make_inst(m_quat * other.m_quat);
    }

    try {
        Py::Float other(other_);

        return make_inst(m_quat * other);
    } catch(const Py::Exception& ) {
        throw Py::TypeError("A vector may only be muliplied by a number or element-wise by a Quaternion instance.");
    }
}

Py::Object Quaternion::dot(const Py::Tuple &args)
{
    if(args.length() != 1) {
        throw Py::TypeError("Quaternion.dot product takes one argument");
    }

    if(!Quaternion::check(args[0])) {
        throw Py::TypeError("Quaternion.dot product takes a Quaternion argument");
    }

    QuaternionObject other_(args[0]);
    const Quaternion& other = *other_.getCxxObject();

    return Py::Float(m_quat.dot(other.m_quat));
}

Py::Object Quaternion::len()
{
    return Py::Float(m_quat.len());
}

Py::Object Quaternion::normalize()
{
    m_quat.normalize();
    return Py::None();
}

Py::Object Quaternion::normalized()
{
    return make_inst(m_quat.normalized());
}

// Py::Object Quaternion::lerp(const Py::Tuple& args, const Py::Dict& kwargs)
// {
//     if(args.length() + kwargs.length() != 2) {
//         throw Py::ValueError("Quaternion.lerp takes two arguments: first ('other') another vector and second ('between') a number or a vector for element-wise lerp.");
//     }
// 
//     Py::Object other_arg;
//     if(args.length() > 0) {
//         if(!Quaternion::check(args[0])) {
//             throw Py::TypeError("Quaternion.lerp takes a Quaternion as first argument");
//         }
//         other_arg = args[0];
//     } else {
//         if(!kwargs.hasKey("other")) {
//             throw Py::ValueError("Quaternion.lerp needs the 'other' argument");
//         }
//         other_arg = kwargs.getItem("other");
//     }
// 
//     QuaternionObject other_(other_arg);
//     const Quaternion& other = *other_.getCxxObject();
// 
//     Py::Object between_arg;
//     if(args.length() == 2) {
//         between_arg = args[1];
//     } else if(kwargs.hasKey("between")) {
//         between_arg = kwargs.getItem("between");
//     } else {
//         throw Py::ValueError("Quaternion.lerp needs the 'between' argument.");
//     }
// 
//     if(Quaternion::check(between_arg)) {
//         QuaternionObject between_(between_arg);
//         const Quaternion& between = *between_.getCxxObject();
// 
//         return make_inst(m_quat.lerp(other.m_quat, between.m_quat));
//     }
// 
//     try {
//         Py::Float between(between_arg);
// 
//         return make_inst(m_quat.lerp(other.m_quat, between));
//     } catch(const Py::Exception& ) {
//         throw Py::TypeError("The second argument to Quaternion.lerp ('between') needs to be a numeric value or a vector.");
//     }
// }
