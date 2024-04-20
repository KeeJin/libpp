#! /usr/bin/bash
mkdir -p conan_venv
python3 -m venv ./conan_venv
source ./conan_venv/bin/activate

# Install conan
# Requires Python 3.6 or later
pip install conan