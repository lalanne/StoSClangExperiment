
from helpers import *

def test_basic_guided():
    testFileName = "test_omp_guided.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_guided_1():
    testFileName = "test_omp_guided1.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_guided_2():
    testFileName = "test_omp_guided2.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_guided_3():
    testFileName = "test_omp_guided3.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_guided_4():
    testFileName = "test_omp_guided4.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

