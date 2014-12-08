import subprocess
import os

def create_output_cpp_file(nameOfFile, commandOutput):
    fileHandler = open(nameOfFile, "w")
    fileHandler.write(commandOutput)
    fileHandler.close()

def destroy_output_cpp_file(nameOfFile):
    os.remove(nameOfFile)

def execute_binary(inputFile):
    args = ("/Users/lalanne/clang-llvm-omp/build/bin/sts", 
            "input/"+inputFile, 
            "--", 
            "-fopenmp")
    popen = subprocess.Popen(args, stdout=subprocess.PIPE)
    popen.wait()
    output = popen.stdout.read()
    return output


def test_basic_static():
    create_output_cpp_file("output.cpp", execute_binary("test_omp.cpp"))

    resultHandler = open('output.cpp', 'r')
    resultFile = resultHandler.read()

    expectedOutputFileHandler = open('expected_output/test_omp.cpp', 'r')
    expectedOutputFile = expectedOutputFileHandler.read()

    assert expectedOutputFile == resultFile

    resultHandler.close()
    expectedOutputFileHandler.close()

    destroy_output_cpp_file("output.cpp")

def test_basic_static_1():
    create_output_cpp_file("output.cpp", execute_binary("test_omp1.cpp"))

    resultHandler = open('output.cpp', 'r')
    resultFile = resultHandler.read()

    expectedOutputFileHandler = open('expected_output/test_omp1.cpp', 'r')
    expectedOutputFile = expectedOutputFileHandler.read()

    assert expectedOutputFile == resultFile

    resultHandler.close()
    expectedOutputFileHandler.close()

    destroy_output_cpp_file("output.cpp")

