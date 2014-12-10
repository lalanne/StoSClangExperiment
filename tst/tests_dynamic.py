
from helpers import *

def test_basic_dynamic():
    testFileName = "test_omp_dynamic.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_dynamic_1():
    testFileName = "test_omp_dynamic1.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_dynamic_2():
    testFileName = "test_omp_dynamic2.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_dynamic_3():
    testFileName = "test_omp_dynamic3.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_dynamic_4():
    testFileName = "test_omp_dynamic4.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

