#!/bin/bash
echo " Cleaning the temporaries and outputs"
echo "========================================"

make clean
array_path="compiler_tests/array"
default_path="compiler_tests/default"
control_flow_path="compiler_tests/control_flow"
functions_path="compiler_tests/functions"
integer_path="compiler_tests/integer"
local_var_path="compiler_tests/local_var"
misc_path="compiler_tests/misc"
programs_path="compiler_tests/programs"
float_path="compiler_tests/float"
pointer_path="compiler_tests/pointer"
strings_path="compiler_tests/string"
struct_path="compiler_tests/struct"
types_path="compiler_tests/types"



test_path=$programs_path

rm -f working

rm -rf $test_path/assembly
rm -rf $test_path/exe
rm -rf $test_path/objects



echo "========================================"

echo " Force building compiler"
echo "========================================"
make 
echo "========================================"

if [[ "$?" -ne "0" ]]; then
    echo "Error while building compiler."
    exit 1;
fi

echo "========================================="

PASSED=0
CHECKED=0
NO=1

##mkdir -p compiler_tests/default/working
mkdir -p $test_path/assembly
mkdir -p $test_path/exe
mkdir -p $test_path/objects

for i in $test_path/tests/*; do
  b=$(basename ${i});

  echo " : $b"

  name=$(basename ${i} .c);
  
  echo "name : $name"

  echo "========================================="
  echo "Input file : ${i}"
  echo "${NO}. Test $b"


  echo "Running $b on COMPILER"
  bin/c_compiler -S $i -o $test_path/assembly/${name}.s
  ##cat $i/$b.c | ./bin/c_compiler $i/$b.c > working/$b/$b.s

  echo "Running ${name} Assembly into executable"
  mips-linux-gnu-gcc -mfp32 -o $test_path/objects/${name}.o -c $test_path/assembly/${name}.s
  mips-linux-gnu-gcc -mfp32 -static -o $test_path/exe/${name} $test_path/objects/${name}.o $test_path/drivers/${name}_driver.c
  ##mips-linux-gnu-gcc -static working/$b/$b.s -o working/$b/$b

  echo "Running ${name} MY EXECUTABLE"
  qemu-mips $test_path/exe/${name}

  RESULT=$?;

  echo "${name} : ${RESULT}"> $test_path/${name}_working.txt

  if [[ "${RESULT}" -eq "0" ]]; then
      PASSED=$(( ${PASSED}+1 ));
  fi

  CHECKED=$(( ${CHECKED}+1 ));

  NO=$(( ${NO}+1 ));

  echo "========================================="
  echo ""
done

echo "########################################"
echo "Passed ${PASSED} out of ${CHECKED}".
echo "########################################"