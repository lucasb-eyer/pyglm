#include "Vector.hpp"

#include "CXX/Objects.hxx"
#include "CXX/Extensions.hxx"

class Vector : public Py::PythonClass<Vector>
{
public:
    Vector(Py::PythonClassInstance *self, Py::Tuple &args, Py::Dict &kwds)
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

    static Py::PythonClassObject<Vector> make_inst(const PyGlMath::Vector& v)
    {
        Py::Callable type(Vector::type());
        return Py::PythonClassObject<Vector>(type.apply( Py::TupleN(Py::Float(v.x()), Py::Float(v.y()), Py::Float(v.z())), Py::Dict() ));
    }

    virtual ~Vector()
    { }

    static void init_type(void)
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

        // Call to make the type ready for use
        behaviors().readyType();
    }

    Py::Object getattro(const Py::String& name_)
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

    int setattro(const Py::String& name_, const Py::Object &value)
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

    Py::Object repr()
    {
        std::OSTRSTREAM ss;
        ss << "Vector(" << m_vec.x() << "," << m_vec.y() << "," << m_vec.z() << ")";
        return Py::String(ss.str());
    }

    Py::Object str()
    {
        return this->repr();
    }

    long hash()
    {
        return Py::TupleN(Py::Float(m_vec.x()), Py::Float(m_vec.y()), Py::Float(m_vec.z())).hashValue();
    }

    Py::Object rich_compare(const Py::Object& other_, int op)
    {
        // TODO: Vector < number type checks?
        if(Vector::check(other_)) {
            Py::PythonClassObject<Vector> other__(other_);
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
            throw Py::AttributeError("expecting Vector object for compare");
        }
    }

    Py::Object number_negative()
    {
        return make_inst(-m_vec);
    }

    Py::Object number_positive()
    {
        return make_inst(m_vec);
    }

    Py::Object number_absolute()
    {
        return make_inst(m_vec.abs());
    }

    Py::Object number_invert()
    {
        return make_inst(PyGlMath::Vector(1.0f/m_vec.x(), 1.0f/m_vec.y(), 1.0f/m_vec.z()));
    }

    Py::Object number_add(const Py::Object& other_)
    {
        if(Vector::check(other_)) {
            Py::PythonClassObject<Vector> other__(other_);
            const Vector& other = *other__.getCxxObject();

            return make_inst(m_vec + other.m_vec);
        } else {
            throw Py::AttributeError("expecting Vector object for addition");
        }
    }

    Py::Object number_subtract(const Py::Object& other_)
    {
        if(Vector::check(other_)) {
            Py::PythonClassObject<Vector> other__(other_);
            const Vector& other = *other__.getCxxObject();

            return make_inst(m_vec - other.m_vec);
        } else {
            throw Py::AttributeError("expecting Vector object for subtraction");
        }
    }

    Py::Object number_multiply(const Py::Object& other_)
    {
        try {
            Py::Float other(other_);

            return make_inst(m_vec * other);
        } catch(const Py::Exception& e) {
            throw Py::TypeError("A vector may only be muliplied by a number, i.e. scaled. Please use 'dot' and 'cross' for the dot product and the cross product of two vectors respectively.");
        }
    }

    Py::Object cross(const Py::Tuple &args)
    {
        if(args.length() != 1) {
            throw Py::ValueError("Vector.cross product can only take one vector as argument");
        }

        if(!Vector::check(args[0])) {
            throw Py::TypeError("Vector.cross product can only take a vector as argument");
        }

        Py::PythonClassObject<Vector> other_(args[0]);
        const Vector& other = *other_.getCxxObject();

        return make_inst(m_vec.cross(other.m_vec));
    }
    PYCXX_VARARGS_METHOD_DECL(Vector, cross)

    Py::Object dot(const Py::Tuple &args)
    {
        if(args.length() != 1) {
            throw Py::ValueError("Vector.dot product can only take one vector as argument");
        }

        if(!Vector::check(args[0])) {
            throw Py::TypeError("Vector.dot product can only take a vector as argument");
        }

        Py::PythonClassObject<Vector> other_(args[0]);
        const Vector& other = *other_.getCxxObject();

        return Py::Float(m_vec.dot(other.m_vec));
    }
    PYCXX_VARARGS_METHOD_DECL(Vector, dot)

    PyGlMath::Vector m_vec;
};

class pyglm_module : public Py::ExtensionModule<pyglm_module>
{
public:
    pyglm_module()
        : Py::ExtensionModule<pyglm_module>("pyglm") // this must be name of the file on disk e.g. simple.so or simple.pyd
    {
        Vector::init_type();

//        add_varargs_method("old_style_class", &simple_module::factory_old_style_class, "documentation for old_style_class()");
//        add_keyword_method("func", &simple_module::func, "documentation for func()");
//        add_keyword_method("make_instance", &simple_module::make_instance, "documentation for make_instance()");

//        add_keyword_method("decode_test", &simple_module::decode_test, "documentation for decode_test()");
//        add_keyword_method("encode_test", &simple_module::encode_test, "documentation for encode_test()");

        // after initialize the moduleDictionary will exist
        initialize("documentation for pyglm module");

/*        Py::Dict d( moduleDictionary() );
        d["var"] = Py::String( "var value" );
        Py::Object x( Vector::type() );
        d["Vector"] = x;*/
        moduleDictionary()["Vector"] = Vector::type();
//        moduleDictionary()["foo"] = Py::String("foobar");
    }

    virtual ~pyglm_module()
    { }
/*
private:
    Py::Object decode_test( const Py::Tuple &args, const Py::Dict &kwds )
    {
        Py::Bytes s( args[0] );
        return s.decode("utf-8");
    }

    Py::Object encode_test( const Py::Tuple &args, const Py::Dict &kwds )
    {
        Py::String s( args[0] );
        return s.encode("utf-8");
    }

    Py::Object func( const Py::Tuple &args, const Py::Dict &kwds )
    {
        std::cout << "func Called with " << args.length() << " normal arguments." << std::endl;
        Py::List names( kwds.keys() );
        std::cout << "and with " << names.length() << " keyword arguments:" << std::endl;
        for( Py::List::size_type i=0; i< names.length(); i++ )
        {
            Py::String name( names[i] );
            std::cout << "    " << name << std::endl;
        }

#ifdef PYCXX_DEBUG
        if( args.length() > 0 )
        {
            Py::Object x( args[0] );
            PyObject *x_p = x.ptr();
            std::cout << "func( self=0x" << std::hex << reinterpret_cast< unsigned int >( x_p ) << std::dec << " )" << std::endl;
            Py::PythonClassInstance *instance_wrapper = reinterpret_cast< Py::PythonClassInstance * >( x_p );
            new_style_class *instance = static_cast<new_style_class *>( instance_wrapper->cxx_object );
            std::cout << "    self->cxx_object=0x" << std::hex << reinterpret_cast< unsigned int >( instance ) << std::dec << std::endl;
        }

        bpt();
#endif

        return Py::None();
    }

    Py::Object make_instance( const Py::Tuple &args, const Py::Dict &kwds )
    {
        std::cout << "make_instance Called with " << args.length() << " normal arguments." << std::endl;
        Py::List names( kwds.keys() );
        std::cout << "and with " << names.length() << " keyword arguments:" << std::endl;
        for( Py::List::size_type i=0; i< names.length(); i++ )
        {
            Py::String name( names[i] );
            std::cout << "    " << name << std::endl;
        }

        Py::Callable class_type( new_style_class::type() );

        Py::PythonClassObject<new_style_class> new_style_obj( class_type.apply( args, kwds ) );

        return new_style_obj;
    }

    Py::Object factory_old_style_class( const Py::Tuple &rargs )
    {
        Py::Object obj = Py::asObject( new old_style_class );
        return obj;
    }*/
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

