#!/bin/bash

# Check if an argument (C source code file) is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <c_source_file>"
    exit 1
fi

# Extract the filename without the extension
file_without_extension="${1%.*}"

# Check if GCC is installed
if ! command -v gcc &>/dev/null; then
    echo "GCC (GNU Compiler Collection) is not installed. Please install it first."
    exit 1
fi

# Compile the C source code to assembly
gcc -S -o "$file_without_extension.asm" "$1"

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo -e "Compilation successful. Generating an executable...\n"
    
    # Compile the C source code to an executable
    gcc -o "$file_without_extension.out" "$1"

    # Check if executable compilation was successful
    if [ $? -eq 0 ]; then
        echo -e "Executable generated successfully. Running the program...\n"
        
        # Run the compiled program
        "./$file_without_extension.out"
        
        # Clean up the generated files
        rm "$file_without_extension.asm" "$file_without_extension.out"
        
        echo -e "\nRemoved extra files."
    else
        echo -e "\nERROR: Executable generation failed."
    fi
else
    echo -e "\nERROR: Compilation to assembly code failed."
fi
