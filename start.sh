#!/bin/bash

# Check for Python installation
if command -v python3 >/dev/null 2>&1; then
  # Python is installed, run clear_code.py
  python3 clear_code.py
else
  # Check for C++ compiler
  if command -v g++ >/dev/null 2>&1; then
    # C++ compiler is installed, run a.cpp
    g++ cal_speed++.cpp -o cal_speed++.out && ./cal_speed++.out
    # Clean up the compiled executable (optional)
    rm -f cal_speed++.out
  else
    echo "Neither Python 3 nor C++ compiler found."
    apt install python3
    python3 clear_code.py
    
    

  fi
fi
