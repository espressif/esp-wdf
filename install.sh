#!/usr/bin/env bash

set -e
set -u

basedir=$(dirname "$0")
IDF_PATH=$(cd "${basedir}"; pwd)
export IDF_PATH

echo "Detecting the Python interpreter"
. "${IDF_PATH}/tools/detect_python.sh"

echo "Installing ESP-WDF tools"
"${ESP_PYTHON}" "${IDF_PATH}/tools/idf_tools.py" install

echo "Installing Python environment and packages"
"${ESP_PYTHON}" "${IDF_PATH}/tools/idf_tools.py" install-python-env

echo "All done! You can now run:"
echo ""
echo "  . ${basedir}/export.sh"
echo ""
