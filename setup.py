#!/usr/bin/env python


from setuptools import setup, Extension

VERSION = (0, 2, 2)

setup(
    name='simhash Index',
    version=".".join([str(x) for x in VERSION]),
    keywords=('simhashindex', 'simhash'),
    description="Simhash Index Bindings for Python",
    long_description=open('README.md', 'r').read(),
    author='Veelion Chong',
    author_email='veelion@gmail.com',
    url='https://github.com/veelion/simhashindex',
    # packages=['simhashindex'],
    package_dir={'': 'src'},
    ext_modules=[
        Extension(
            'simhashindex',
            [
                'src/farmhash.cc',
                'src/simhashindex.cc',
                'src/wrap_pymod.cc'
            ],
            libraries=['boost_python'],
            extra_compile_args=["-g"]
        )
    ],
    classifiers=[
        'Development Status :: 5 - Production/Stable',
        'License :: OSI Approved :: MIT License',
        'Intended Audience :: Developers',
        'Programming Language :: C',
        'Programming Language :: Python',
        'Programming Language :: Python :: 2.6',
        'Programming Language :: Python :: 2.7',
    ],
)
