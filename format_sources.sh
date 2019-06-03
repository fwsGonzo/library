#!/bin/sh
set -e
echo "Formatting the codebase..."
find include/ -name '*.hpp' | xargs clang-format-7 -style=file -i
find library/ -name '*.cpp' | xargs clang-format-7 -style=file -i
echo "->   Completed successfully!"
