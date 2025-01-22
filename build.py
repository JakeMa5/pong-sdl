import subprocess
import os
import sys

def check_dependencies() -> None:
    try:
        subprocess.run(["cmake", "--version"], check=True)
    except subprocess.CalledProcessError:
        print("CMake is not installed or not found in PATH.")
        sys.exit(1)

def create_build_directory() -> None:
    if not os.path.exists("build"):
        os.makedirs("build")

def build() -> None:
    check_dependencies()
    create_build_directory()
    try:
        subprocess.run(["cmake", "--preset=default"], check=True)
        subprocess.run(["cmake", "--build", "build"], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Build failed: {e}")
        sys.exit(1)

if __name__ == "__main__":
    build()