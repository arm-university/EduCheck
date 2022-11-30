import json
import io
import os
import sys
import subprocess as edu_process
import shutil
from pathlib import Path

from mbed_os_tools.test.mbed_greentea_log import gt_logger
from .html_exporter import exporter_html


def find_student_folders(student_master_dir):
    """This function scans
    student_master_dir and returns the filepath for each student folder.

    :param string student_master_dir: A full path to a directory that contains
                                        unique student folders.
    :return: A list of detected individual student folder paths.
    :rtype: list
    """
    student_folder_path_list = [
        obj for obj in os.listdir(student_master_dir)
        if os.path.isdir(os.path.join(student_master_dir, obj))
    ]

    try:
        if len(student_folder_path_list) != 0:
            print("Detected student folders:")
            print("\n".join(map(str, student_folder_path_list)))

        else:
            raise ValueError()
    except ValueError:
        print("No student folders detected in " + student_master_dir)

    return student_folder_path_list


def find_specific_student_folders(student_master_dir, specific_student_dirs):
    """This
    function scans student_master_dir and returns the filepath for each student
    folder.

    :param string student_master_dir: A full path to a directory that contains
                                        unique student folders.
    :param string listlist specific_student_dirs: A full path to a directory
                                                  that contains unique student
                                                  folders.
    :return: A list of detected individual student folder paths.
    :rtype: list
    """
    student_folder_path_list = []
    for index, dirs in enumerate(specific_student_dirs):
        student_folder_path = os.path.join(student_master_dir, dirs)
        student_folder_path_list.append(student_folder_path)

    try:
        if len(student_folder_path_list) != 0:
            print("Detected student folders:")
            print("\n".join(map(str, student_folder_path_list)))

        else:
            raise ValueError()
    except ValueError:
        print("Specified folders not detected in " + student_master_dir)

    return student_folder_path_list


def build_folders_cleanup(build_dir):
    """This function removes specific build directories after testing before
    proceeding to the next iteration

    :param string build_dir: A full path of the build directory for
                             compilation.
    :return: void
    """
    try:
        if os.path.exists(build_dir):
            folders_in_build_dir = [
                obj for obj in os.listdir(build_dir)
                if os.path.isdir(os.path.join(build_dir, obj))
            ]
            if len(folders_in_build_dir) != 0:
                for dir in folders_in_build_dir:
                    if dir != "mbed-os":
                        shutil.rmtree(os.path.join(build_dir, dir))
            print("Build clean up succesful")
        else:
            raise ValueError()
    except ValueError:
        print(build_dir + " build directory is not found.")


def path_check(student_file_path, student_code_file):
    """
    This functions takes the acquired path to the student submission and checks
    to ensure a file with the name "mp3player.cpp" exists in that location.

    :param string student_file_path: A full path to the directory that contains
                                     the students "mp3player.cpp" file
    :param string student_code_file: The name of the file expected to be in the
                                     student submission directory
    :return: file_exists
    :rtype: bool
    """
    try:
        submission_path = os.path.join(
            "..\\STUDENT_HOMEWORK\\", student_file_path, student_code_file)
        if os.path.isfile(submission_path):
            print("File found: " + submission_path)
            file_exists = True
        else:
            raise ValueError()
    except ValueError:
        print("Cannot find file: " + submission_path)
        file_exists = False
    return file_exists


def compile(target_platform, build_dir, test_spec_path, build_data_path,
            test_suite_regex, student_file_path):
    """
    This function takes multiple parameters to compile the specified code.

    :param string target_platform: The name of the target platform the code
                                   needs to be compiled for, e.g. NUCLEO_F401RE
    :param string BUILD_DIR: The location of the BUILD > batch directory
    :param string test_spec_path: The location of the "test_spec.json" object
                                  in the batch folder
    :param string build_data_path: The location of the "build_data.json"
                                   object in the batch folder
    :param string test_suite_regex: The name of the test suite we wish to run,
                                    e.g. "tests-lab7-stop_replay"
    :return: compiled
    :rtype: bool
    """
    print("Compiling...")

    print("..\\STUDENT_HOMEWORK\\" + student_file_path)
    path = os.path.join("..", "STUDENT_HOMEWORK", student_file_path)

    results_path = os.path.join("..", "GRADE_RESULT", student_file_path)
    Path(results_path).mkdir(parents=True, exist_ok=True)
    results_txt = os.path.join(results_path, "CompilationError.txt")

    try:
        print(build_dir)
        info = edu_process.check_output(
            ["mbed", "test", "-m", target_platform, "-t", "GCC_ARM", "-n",
             test_suite_regex, "--compile", "--source", ".", "--source", path])

        compiled = True
    except edu_process.CalledProcessError as info:
        print("Error code: ", info.returncode)
        file = open(results_txt, "wb")
        file.write(info.output)
        compiled = False
    return compiled


def build_files_cleanup(build_dir):
    """This function removes all *.o and *.d files in the build directory
    before proceeding to the next iteration.

    :param string build_dir: A full path of the build directory for compilation
    :return: void
    """
    try:
        if os.path.exists(build_dir):
            detected_files = [
                obj
                for obj in os.listdir(build_dir)
                if os.path.isfile(os.path.join(build_dir, obj))
            ]
            for file in detected_files:
                if file.endswith(".d") or file.endswith(".o"):
                    file_path_to_delete = os.path.join(build_dir, file)
                    os.remove(file_path_to_delete)
                    print(
                        "Removing *.d and *.o files in build folder in "
                        "preparation for next student."
                    )
        else:
            raise ValueError()
    except ValueError:
        print(build_dir + " build directory is not found.")


def copy_folder(source, destination):
    """This function copies the lab files from a specified source
    to destination. This function can be used to copy lab files from package
    to mbed files directory so that tests can be discovered

    :param string source: Path of folder to copy
    :param string destination: Path of folder to paste into
    :return: void
    """
    # check source path
    try:
        if os.path.exists(source):
            pass
        else:
            raise ValueError()
    except ValueError:
        print(source + " does not exist for copying into mbed workspace.")

    # check destination path
    if os.path.exists(destination):
        print("Recopying folder " + destination)
        shutil.rmtree(destination, ignore_errors=True)
        shutil.copytree(source, destination)
    else:
        print("Copying folder to " + destination)
        shutil.copytree(source, destination)


def run_test(test_spec_path, report_name, each_student_path):
    """This function runs the compiled tests.

    :param string test_spec_path: The location of the "test_spec.json" object
                                  in the batch folder
    :return: compiled
    :rtype: bool
    """
    results_path = os.path.join("..", "GRADE_RESULT", each_student_path)
    run_results_txt = os.path.join(results_path, "RuntimeError.txt")

    # Run Greentea and generate results in .json format
    try:
        run_results = edu_process.check_output(
            ["mbedgt", "--test-spec", test_spec_path,
             "--report-json", "json_report.json"])
        compiled = True
    except edu_process.CalledProcessError as info:
        print("Error code: ", info.returncode)

        file = open(run_results_txt, "wb")
        file.write(info.output)
        compiled = False

    # Collect data from generated .json file
    data = {}
    with open('json_report.json') as json_file:
        data = json.load(json_file)

    # Put data in HTML format
    html_report = exporter_html(data, each_student_path)

    # Remove .json file
    os.remove("json_report.json")
    results_txt = os.path.join(results_path, report_name)

    # Dump HTML data to file
    dump_report_to_text_file(results_txt, html_report)

    return compiled


def dump_report_to_text_file(filename, content):
    """This function does closure for report dumps to text files

    :param filename: Name of destination file
    :param content: Text content of the file to write
    :return: True if write was successful, else return False
    :rtype: bool
     """
    try:
        with io.open(filename, encoding="utf-8",
                     errors="backslashreplace", mode="w") as f:
            f.write(content)
    except IOError as e:
        gt_logger.gt_log_err("can't export to '%s', reason:" % filename)
        gt_logger.gt_log_err(str(e))
        return False
    return True
