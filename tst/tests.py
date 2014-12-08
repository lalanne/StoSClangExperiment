import subprocess
import os

def test_basic_static():
    args = ("/Users/lalanne/clang-llvm-omp/build/bin/sts", 
            "input/test_omp.cpp", 
            "--", 
            "-fopenmp")
    popen = subprocess.Popen(args, stdout=subprocess.PIPE)
    popen.wait()
    output = popen.stdout.read()

    outputFileHandler = open("output.cpp", "w")
    outputFileHandler.write(output)
    outputFileHandler.close()

    resultHandler = open('output.cpp', 'r')
    resultFile = resultHandler.read()

    expectedOutputFileHandler = open('expected_output/test_omp.cpp', 'r')
    expectedOutputFile = expectedOutputFileHandler.read()

    assert expectedOutputFile == resultFile

    resultHandler.close()
    os.remove("output.cpp")

