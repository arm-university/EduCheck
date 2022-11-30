import argparse
import subprocess as edu_process
import sys
import os
import shutil
from .educheck_api import *


def parse_args():
    """This function takes a list of command line arguments when the labcheck
    program is called. All arguments are optional. So the labcheck can be called
    without them.
    """
    parser = argparse.ArgumentParser(description="EduCheck Interface")
    parser.add_argument(
        "--board", "-b", type=str,
        help="Enter the development board used for the test"
    )
    parser.add_argument("--result", "-res", type=str, help="Output file format")
    parser.add_argument(
        "--grade",
        "-g",
        type=str,
        nargs="+",
        help="List students to grade. Default, all students will be graded or"
             "list select student using format <student1, student2, ...>",
    )
    parser.add_argument(
        "--requirements",
        "-req",
        action="store_true",
        help="Check mbed version, GCC_ARM and connected board",
    )
    args = parser.parse_args()
    return args


def requirements():
    """This function deals with the requirements argument as a switch if
    passed in the command prompt.
    :print: Installed/Detected Mbed version, Default Toolchain and Detected
            Mbed enabled board.
    :rtype: bytes
    """
    inputs = parse_args()
    if inputs.requirements:
        print("Checking mbed version, GCC_ARM and connected board")
        print(
            "-----------------------------------------------------------------------------------------------------------------"
        )

        print("Your Mbed Verison is:")
        try:
            edu_process.run(["mbed", "--version"])
        except:
            print("Mbed not detected")
        print(
            "-----------------------------------------------------------------------------------------------------------------"
        )

        print("Default Toolchain")
        try:
            edu_process.run(["mbed", "toolchain"])
        except:
            print("Toolchain not detected")
        print(
            "-----------------------------------------------------------------------------------------------------------------"
        )

        print("Detected Board")
        try:
            edu_process.run(["mbedls"])
        except:
            print("Mbed enabled board not detected")
        print(
            "-----------------------------------------------------------------------------------------------------------------"
        )

        exit()
    else:
        pass


def board_detect():
    """This function checks if an Mbed enabled board is connected to the
    computer. If an Mbed enabled board is connected, data in byte format is
    returned, which is converted to string.
    The string is then stripped of " " and the board name is selected with
    index 1.
    :return: Board anme.
    :rtype: string
    """
    board = ""
    try:
        board_details = edu_process.run(["mbedls", "--simple"],
                                        capture_output=True)
        board_to_string = board_details.stdout.decode()
        board_name = board_to_string.split(" ")
        if len(board_to_string) != 0:
            board = board_name[1]
        else:
            raise ValueError()
    except ValueError:
        print("Mbed enabled board not detected or set")

    return board


def board():
    """This function checks if the board argument is set and sets the board
    name to this argument else it set the board name to the detected board.
    :return: Board anme.
    :rtype: string
    """
    inputs = parse_args()
    if inputs.board:
        board = inputs.board
    else:
        board = board_detect()
    return board


def results_format():
    """This function checks if the results argument is set. This argument sets
    the result output file format. When not set, the default is html.
    :return: result file format.
    :rtype: string
    """
    inputs = parse_args()
    if inputs.result:
        result_format = inputs.result
    else:
        result_format = "html"
    return result_format


def grade():
    """This function checks if the grade argument is set. This argument sets a
    list of students to be graded from inputs in the command line.
    If not set, the list is empty and all reuslts will be graded.
    :return: student list.
    :rtype: list
    """

    inputs = parse_args()
    if inputs.grade:
        grade = inputs.grade
    else:
        grade = []
    return grade


def main():
    """This function is the main function that calls the APIs"""

    # Parse options
    BOARD = board()
    requirements()
    SPECIFIC_STUDENT_DIRS = grade()

    # Specify Educheck tests
    TESTSUITE_REGEX = "lab_files-tests-lab_7*"

    # Internal Option Defaults
    mbed_folder_name = "mbed_files"
    student_code_directory_name = "STUDENT_HOMEWORK"
    BUILD_DIR = "BUILD\\tests\\" + BOARD + "\\GCC_ARM"
    TEST_SPEC_PATH = "BUILD\\tests\\" + BOARD + "\\GCC_ARM\\test_spec.json"
    BUILD_DATA_PATH = "BUILD\\tests\\" + BOARD + "\\GCC_ARM\\build_data.json"

    STUDENT_MASTER_DIR_PATH = os.path.join(
        os.getcwd(), "..", student_code_directory_name
    )
    BUILD_PATH = os.getcwd()
    COMPILER = "GCC_ARM"  # this should be default unless specified by user

    # Folder names
    test_build_folder_name = "TESTS"
    package_top_level_name = "codechecker"
    package_lab_folder_name = "LAB_FILES"

    # Construct full path for lab files
    lab_files_path = os.path.join(
        os.getcwd(), "..", package_top_level_name, package_lab_folder_name
    )

    mbed_folder_path = os.getcwd()

    # Construct full path of build_dir
    build_dir = os.path.join(BUILD_PATH, "BUILD", "tests", BOARD, COMPILER)

    # Choose function depending if user specified option (if user did
    # not specify option, the SPECTIFIC_STUDENT_DIRS list is empty)
    if len(SPECIFIC_STUDENT_DIRS) == 0:
        student_folders_list = find_student_folders(STUDENT_MASTER_DIR_PATH)
    else:
        student_folders_list = find_specific_student_folders(
            STUDENT_MASTER_DIR_PATH, SPECIFIC_STUDENT_DIRS
        )

    # Copy lab and test files into mbed folder - can be commented off if
    # mbed test can run for separate folders - Mark please look into this
    copy_folder(lab_files_path, os.path.join(mbed_folder_path,
                package_lab_folder_name))

    # start loop to iterate each student folder
    for each_student_path in student_folders_list:
        report_name = each_student_path+"_report.html"
        print("Processing student folder : " + each_student_path)

        # Compile student code with supporting files and tests
        compile(
            BOARD,
            build_dir,
            TEST_SPEC_PATH,
            BUILD_DATA_PATH,
            TESTSUITE_REGEX,
            each_student_path,
        )

        # Run compiled test files and generate report
        run_test(
                TEST_SPEC_PATH,
                report_name,
                each_student_path)

        # Do clean up before proceeding to the next student
        build_folders_cleanup(build_dir)
        build_files_cleanup(build_dir)


if __name__ == "__main__":
    main()
