
from helpers import *

def test_basic_auto_parallel_for():
    testFileName = "test_omp_auto_parallel_for.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_auto_parallel_for_1():
    testFileName = "test_omp_auto_parallel_for1.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_auto_parallel_for_2():
    testFileName = "test_omp_auto_parallel_for2.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_auto_parallel_for_3():
    testFileName = "test_omp_auto_parallel_for3.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

def test_basic_auto_parallel_for_4():
    testFileName = "test_omp_auto_parallel_for4.cpp"

    create_output_cpp_file(RESULT_CPP_FILE_NAME, execute_binary(testFileName))
    resultFile = read_result_file()
    expectedOutputFile = read_expected_result_file(testFileName)

    assert expectedOutputFile == resultFile

    destroy_output_cpp_file(RESULT_CPP_FILE_NAME)

