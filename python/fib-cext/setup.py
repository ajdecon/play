from distutils.core import setup, Extension

module1 = Extension('fib', sources=['fibmodule.c'])

setup(name='FibPackage', version = 0.1, 
    description='Fibonacci numbers',
    ext_modules = [module1])
