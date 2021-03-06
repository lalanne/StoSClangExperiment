import subprocess
import os

RESULT_CPP_FILE_NAME = "real_result.cpp"
INPUT_FILES_RELATIVE_PATH = "input/"
EXPECTED_OUTPUT_FILES_RELATIVE_PATH = "expected_output/"


def create_output_cpp_file(nameOfFile, commandOutput):
    fileHandler = open(nameOfFile, "w")
    fileHandler.write(commandOutput)
    fileHandler.close()

def destroy_output_cpp_file(nameOfFile):
    os.remove(nameOfFile)

def execute_binary(inputFile):
    args = ("/Users/lalanne/clang-llvm-omp/build/bin/sts", 
            INPUT_FILES_RELATIVE_PATH + inputFile, 
            "--", 
            "-fopenmp",
            "-I",
            "/usr/local/Cellar/gcc49/4.9.2/lib/gcc/x86_64-apple-darwin14.0.0/4.9.2/include/")
    popen = subprocess.Popen(args, stdout=subprocess.PIPE)
    popen.wait()
    output = popen.stdout.read()
    return output

def read_result_file():
    resultHandler = open(RESULT_CPP_FILE_NAME, 'r')
    resultFile = resultHandler.read()
    resultHandler.close()
    return resultFile

def read_expected_result_file(testFileName):
    expectedOutputFileHandler = open(EXPECTED_OUTPUT_FILES_RELATIVE_PATH + testFileName, 
                                    'r')
    expectedOutputFile = expectedOutputFileHandler.read()
    expectedOutputFileHandler.close()
    return expectedOutputFile

