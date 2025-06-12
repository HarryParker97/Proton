"""python setup.py build_ext --inplace"""
from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

ext_modules = [
    Pybind11Extension(
        "results_dict", 
        ["src/main.cpp"]
    ),
]

setup(
    name="results_dict",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)
