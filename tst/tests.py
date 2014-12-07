import subprocess
import os

def func(x):
    return x+1

def test_basic():
    args = ("/Users/lalanne/clang-llvm-omp/build/bin/sts", 
            "input/test_omp.cpp", 
            "--", 
            "-fopenmp")
    popen = subprocess.Popen(args, stdout=subprocess.PIPE)
    popen.wait()
    output = popen.stdout.read()

    outputFile = open("output.cpp", "w")
    outputFile.write(output)
    outputFile.close()

    resultHandler = open('output.cpp', 'r')
    resultFile = resultHandler.read()

    expectedOutputFileHandler = open('expected_output/test_omp.cpp', 'r')
    expectedOutputFile = expectedOutputFileHandler.read()

    assert expectedOutputFile == resultFile

    resultHandler.close()
    os.remove("output.cpp")

