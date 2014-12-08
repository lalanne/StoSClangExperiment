import subprocess
import os

def create_output_cpp_file(nameOfFile, commandOutput):
    fileHandler = open(nameOfFile, "w")
    fileHandler.write(commandOutput)
    fileHandler.close()

def destroy_output_cpp_file(nameOfFile):
    os.remove(nameOfFile)

def execute_binary():
    args = ("/Users/lalanne/clang-llvm-omp/build/bin/sts", 
            "input/test_omp.cpp", 
            "--", 
            "-fopenmp")
    popen = subprocess.Popen(args, stdout=subprocess.PIPE)
    popen.wait()
    output = popen.stdout.read()
    return output


def test_basic_static():
    execute_binary()
    create_output_cpp_file("output.cpp", execute_binary())

    resultHandler = open('output.cpp', 'r')
    resultFile = resultHandler.read()

    expectedOutputFileHandler = open('expected_output/test_omp.cpp', 'r')
    expectedOutputFile = expectedOutputFileHandler.read()

    assert expectedOutputFile == resultFile

    resultHandler.close()
    expectedOutputFileHandler.close()

    destroy_output_cpp_file("output.cpp")

