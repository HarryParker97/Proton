"""python setup.py build_ext --inplace"""
import os
from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup


def collect_cpp_files(directory):
    cpp_files = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".cpp"):
                cpp_files.append(os.path.join(root, file))
    return cpp_files

ext_modules = [
    Pybind11Extension(
        "results_dict",
        sources=collect_cpp_files("src"),  # collect all .cpp files in /src
        cxx_std=17,  # or 20, depending on your code
    )
]

setup(
    name="results_dict",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)

