import os, sys
from distutils.core import setup, Extension

#support_dir = os.path.normpath(os.path.join(sys.prefix, 'share', 'python%d.%d' % (sys.version_info[0],sys.version_info[1]), 'CXX'))
support_dir = os.path.normpath(os.path.join('.', 'embedded-pycxx-6.2.4', 'Src'))

CXX_libraries = ['stdc++','m'] if os.name == 'posix' else []

setup(
    name = "pyglm",
    version = "0.1",
    maintainer = "Lucas Beyer",
    maintainer_email = "pompei2@gmail.com",
    description = "Simple, fast python OpenGL maths (matrix, vector, quaternion) library",
    url = "None yet",

    packages = ['pyglm'],
    ext_modules = [
        Extension(
            'pyglm',
            include_dirs = ['embedded-pycxx-6.2.4'],
            sources = [
                os.path.join('pyglm', 'module.cpp'),
                os.path.join('pyglm', 'Vector.cpp'),
                os.path.join('pyglm', 'Vector_wrap.cpp'),
                os.path.join('pyglm', 'Quaternion.cpp'),
                os.path.join('pyglm', 'Matrix.cpp'),
                os.path.join(support_dir,'cxxsupport.cxx'),
                os.path.join(support_dir,'cxx_extensions.cxx'),
                os.path.join(support_dir,'IndirectPythonInterface.cxx'),
                os.path.join(support_dir,'cxxextensions.c')
            ],
        )
    ]
)
