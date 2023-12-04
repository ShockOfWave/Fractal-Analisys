from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import os
import src


class CMakeExtension(Extension):
    def __init__(self, name, cmake_lists_dir=".", **kwa):
        Extension.__init__(self, name, sources=[], **kwa)
        self.cmake_lists_dir = os.path.abspath(cmake_lists_dir)


class cmake_build_ext(build_ext):
    def build_extensions(self):
        import subprocess

        # Ensure that CMake is present and working
        try:
            subprocess.check_output(["cmake", "--version"])
        except OSError:
            raise RuntimeError("Cannot find CMake executable")

        for ext in self.extensions:
            cfg = (
                "Debug"
                if os.environ.get("DISPTOOLS_DEBUG", "OFF") == "ON"
                else "Release"
            )

            if not os.path.exists(self.build_temp):
                os.makedirs(self.build_temp)

            # Config
            subprocess.check_call(["cmake", ext.cmake_lists_dir], cwd=self.build_temp)

            # Build
            subprocess.check_call(
                ["cmake", "--build", ".", "--config", cfg], cwd=self.build_temp
            )


if os.path.isfile("requirements.txt"):
    with open("requirements.txt", "r") as f:
        packages = f.read().split("\n")
        f.close()

else:
    packages = []

setup(
    name="TDA",
    version=src.__version__,
    packages=["lib"],
    ext_modules=[CMakeExtension(name="TDA")],
    cmdclass={"build_ext": cmake_build_ext},
    install_requires=packages,
)
