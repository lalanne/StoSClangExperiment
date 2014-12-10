
from helpers import *

def test_basic_auto():
    testFileName = "test_omp_auto.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_auto_1():
    testFileName = "test_omp_auto1.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_auto_2():
    testFileName = "test_omp_auto2.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_auto_3():
    testFileName = "test_omp_auto3.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_auto_4():
    testFileName = "test_omp_auto4.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

