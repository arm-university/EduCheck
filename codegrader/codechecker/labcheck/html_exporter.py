# Copyright (c) 2018, Arm Limited and affiliates.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


html_template = """
<!DOCTYPE html>
<html>
    <head>
        <title>EduCheck Grader Results Report</title>
        <script type="text/javascript">
            function toggleOverlay(elemStr) {
                var elem = document.getElementById(elemStr);
                    if (elem) {
                        if (elem.style.display == "") {
                            document.getElementsByTagName("body")[0].style.overflowY = "hidden";
                            elem.style.display = "block";
                        } else {
                            document.getElementsByTagName("body")[0].style.overflowY = "auto";
                            elem.style.display = "";
                        }
                    }
            }

            function toggleDropdown(elemStr) {
                var elem = document.getElementById(elemStr);
                    if (elem) {
                        if (elem.style.height == "0px" || elem.style.height == "") {
                            elem.style.height = "auto";
                            elem.previousElementSibling.textContent = elem.previousElementSibling.textContent.replace("\u25B2", "\u25BC");
                        } else {
                            elem.style.height = 0;
                            elem.previousElementSibling.textContent = elem.previousElementSibling.textContent.replace("\u25BC", "\u25B2");
                        }
                    }
            }
        </script>
        <style type="text/css">

            div.container {
                width: 100%%;
                border: none;
            }

            div.results_table {
                width: 50%%;
            }

            header, footer {
                padding: 1em;
                color: white;
                background-color: #159ab5;
                clear: left;
                text-align: center;
            }

            body {
                margin: 0;
            }

            article {
                padding: 1em;
                overflow: hidden;
            }

            table {
                font-family: arial, sans-serif;
                border-collapse: collapse;
                width: 100%%;
            }

            td.level_header {
                background-color: #bbbbbb;
            }

            td, th {
                border: none;
                text-align: left;
                padding: 8px;
            }

            tr:nth-child(even) {
                background-color: #eeeeee;
            }

            .test-column {
                padding-right: 15px;
            }

            .overlay {
                width: 100%%;
                height: 100%%;
                position: fixed;
                z-index: 1;
                top: 0;
                left: 0;
                background-color: rgb(0,0,0);
                background-color: rgba(0,0,0, 0.7);
                overflow-y: scroll;
                display: none;
            }

            .overlay-content {
                position: relative;
                top: 20px;
                height: auto;
                width: 80%%;
                margin-left: 10%%;
                margin-right: 10%%;
                margin-top: 30px;
                padding: 20px;
                background-color: white;
                cursor: default;
                font-family: "Courier New", Courier, monospace;
                font-size: 14px;
                white-space: pre-line;
            }

            .no-space {
                margin: 0;
                padding: 0;
            }

            .dropdown {
                border: solid thin black;
                border-radius: 5px;
                padding: 8px;
                margin: 0;
                cursor: pointer;
            }

            .dropdown-content {
                height: 0;
                max-height: 500px;
                transition: 0.5s;
                white-space: pre-line;
                overflow-y: auto;
            }

            .sub-dropdown-content {
                margin-left: 2%%;
                margin-right: 2%%;
                max-height: inherit;
            }

            .output-text {
                overflow-y: scroll;
                background-color: #f7f7f7;
                max-height: 500px;
            }

            .result {
                cursor: pointer;
                border-radius: 15px;
                padding: 2px 6px 2px 6px;
            }

            .nowrap {
                white-space: nowrap;
            }

            .close-button {
                color: black;
                float: right;
                cursor: pointer;
                font-size: 20pt;
            }

            .close-button:hover {
                color: darkgrey;
            }

            .test-title-font {
                font-size: 20pt;
            }

            .test-result-title-font {
                font-size: 16pt;
            }%s
        </style>
    </head>
    <body>




        <div class="container">

        <header>
           <h1>EduCheck Grader Results Report</h1>
        </header>

        <p style="color:blue;text-align:center;font-size:20px;font-family: "Times New Roman" New, sans-serif">
        <var style="font-size:25px">%s</var>
        </p>

        <article>

            <div style="width: 50%%; margin: 0 auto;">
                <table>
                <colgroup>
                    <col width="auto">
                    <col span="%d" width="50%%">
                </colgroup>
                    %s
                </table>
            </div>

        </article>

        </div>

        <p style="text-align:center;font-size:25px;font-family: "Times New Roman" New, sans-serif">
        <var style ="font-size:25px">%s</var>
        </p>


    </body>


</html>"""

TEST_RESULT_COLOURS = {
    'OK': "limegreen",
    'FAIL': "darkorange",
    'ERROR': "orangered",
    'SKIPPED': "lightsteelblue",
    'UNDEF': "Red",
    'IOERR_COPY': "DarkSalmon",
    'IOERR_DISK': "DarkSalmon",
    'IOERR_SERIAL': "DarkSalmon",
    'TIMEOUT': "DarkKhaki",
    'NO_IMAGE': "DarkSalmon",
    'NOT_RAN': 'grey'
    # 'MBED_ASSERT': "",
    # 'BUILD_FAILED': "",
}

TEST_RESULT_DEFAULT_COLOUR = "lavender"

def get_result_colour_class_css():
    """! Get the CSS for the colour classes
    @details Returns a string of the CSS classes that are used to colour the different results
    @return String containing the CSS classes
    """

    colour_class_template = """

            .%s {
                background-color: %s;
            }"""

    # Create CSS classes for all of the allocated colours
    css = ""
    for result, colour in TEST_RESULT_COLOURS.items():
        css += colour_class_template % ("result-%s" % result.lower().replace("_", "-"),
                                        colour)

    css += colour_class_template % ("result-other",
                                    TEST_RESULT_DEFAULT_COLOUR)

    return css

def get_result_colour_class(result):
    """! Get the CSS colour class representing the result
    @param result The result of the test
    @details Returns a string of the CSS colour class of the result, or returns the default if the result is not found
    @return String containing the CSS colour class
    """

    if result in TEST_RESULT_COLOURS:
        return "result-%s" % result.lower().replace("_", "-")
    else:
        return "result-other"

def get_dropdown_html(div_id, dropdown_name, content, title_classes="", output_text=False, sub_dropdown=False):
    """! Get the HTML for a dropdown menu
    @param title_classes A space separated string of css classes on the title
    @param div_id The id of the dropdowns menus inner div
    @param dropdown_name The name on the dropdown menu
    @param dropdown_classes A space separated string of css classes on the inner div
    @param content The content inside of the dropdown menu
    @details This function will create the HTML for a dropdown menu
    @return String containing the HTML of dropdown menu
    """

    dropdown_template = """
                                <div class="nowrap">
                                    <p class="dropdown no-space %s" onclick="toggleDropdown('%s')">&#9650 %s</p>
                                    <div id="%s" class="dropdown-content%s">%s
                                    </div>
                                </div>"""

    dropdown_classes = ""
    if output_text:
        dropdown_classes += " output-text"
    if sub_dropdown:
        dropdown_classes += " sub-dropdown-content"

    return dropdown_template % (title_classes,
                                div_id,
                                dropdown_name,
                                div_id,
                                dropdown_classes,
                                content)

def get_result_overlay_testcase_dropdown(result_div_id, index, testcase_result_name, testcase_result):
    """! Get the HTML for an individual testcase dropdown
    @param result_div_id The div id used for the test
    @param index The index of the testcase for the divs unique id
    @param testcase_result_name The name of the testcase
    @param testcase_result The results of the testcase
    @details This function will create the HTML for a testcase dropdown
    @return String containing the HTML of the testcases dropdown
    """

    import datetime

    testcase_result_template = """Result: %s
                                        Elapsed Time: %.2f
                                        Start Time: %s
                                        End Time: %s
                                        Failed: %d
                                        Passed: %d
                                        <br>%s"""

    # Create unique ids to reference the divs
    testcase_div_id = "%s_testcase_result_%d" % (result_div_id, index)
    testcase_utest_div_id = "%s_testcase_result_%d_utest" % (result_div_id, index)

    testcase_utest_log_dropdown = get_dropdown_html(testcase_utest_div_id,
                                                    "uTest Log",
                                                    "\n".join(testcase_result.get('utest_log', 'n/a')).rstrip("\n"),
                                                    output_text=True,
                                                    sub_dropdown=True)

    time_start = 'n/a'
    time_end = 'n/a'
    if 'time_start' in testcase_result.keys():
        time_start = datetime.datetime.fromtimestamp(testcase_result['time_start']).strftime('%d-%m-%Y %H:%M:%S.%f')
    if 'time_end' in testcase_result.keys():
        time_end = datetime.datetime.fromtimestamp(testcase_result['time_end']).strftime('%d-%m-%Y %H:%M:%S.%f')

    testcase_info = testcase_result_template % (testcase_result.get('result_text', 'n/a'),
                                                testcase_result.get('duration', 'n/a'),
                                                time_start,
                                                time_end,
                                                testcase_result.get('failed', 'n/a'),
                                                testcase_result.get('passed', 'n/a'),
                                                testcase_utest_log_dropdown)

    testcase_class = get_result_colour_class(testcase_result['result_text'])
    testcase_dropdown = get_dropdown_html(testcase_div_id,
                                          "Testcase: %s<br>" % testcase_result_name,
                                          testcase_info,
                                          title_classes=testcase_class,
                                          sub_dropdown=True)
    return testcase_dropdown


def get_result_overlay_testcases_dropdown_menu(result_div_id, test_results):
    """! Get the HTML for a test overlay's testcase dropdown menu
    @param result_div_id The div id used for the test
    @param test_results The results of the test
    @details This function will create the HTML for the result overlay's testcases dropdown menu
    @return String containing the HTML test overlay's testcase dropdown menu
    """

    testcase_results_div_id = "%s_testcase" % result_div_id
    testcase_results_info = ""

    # Loop through the test cases giving them a number to create a unique id
    for index, (testcase_result_name, testcase_result) in enumerate(test_results['testcase_result'].items()):
        testcase_results_info += get_result_overlay_testcase_dropdown(result_div_id, index, testcase_result_name, testcase_result)

    result_testcases_dropdown = get_dropdown_html(testcase_results_div_id,
                                                  "Testcase Results",
                                                  testcase_results_info,
                                                  sub_dropdown=True)

    return result_testcases_dropdown

def get_result_overlay_dropdowns(result_div_id, test_results):
    """! Get the HTML for a test overlay's dropdown menus
    @param result_div_id The div id used for the test
    @param test_results The results of the test
    @details This function will create the HTML for the dropdown menus of an overlay
    @return String containing the HTML test overlay's dropdowns
    """

    # The HTML for the dropdown containing the ouput of the test
    result_output_div_id = "%s_output" % result_div_id
    result_output_dropdown = get_dropdown_html(
        result_output_div_id, "Test Output",
        test_results['single_test_output'].rstrip("\n"),
        output_text=True
    )

    # Add a dropdown for the testcases if they are present
    if len(test_results) > 0:
        result_overlay_dropdowns = result_output_dropdown + get_result_overlay_testcases_dropdown_menu(result_div_id, test_results)
    else:
        result_overlay_dropdowns = result_output_dropdown

    return result_overlay_dropdowns

def get_result_overlay(result_div_id, test_name, platform, toolchain, test_results):
    """! Get the HTML for a test's overlay
    @param result_div_id The div id used for the test
    @param test_name The name of the test the overlay is for
    @param platform The name of the platform the test was performed on
    @param toolchain The name of toolchain the test was performed on
    @param test_results The results of the test
    @details This function will create the HTML of an overlay to display additional information on a test
    @return String containing the HTML test overlay
    """

    overlay_template = """<div id="%s" class="overlay">
                            <div class="overlay-content" onclick="event.stopPropagation()">
                                <p class="no-space">
                                    <span class="no-space test-title-font"><b>Test: %s <a class="close-button" onclick="toggleOverlay('%s')">x</a></b></span>
                                    <span class="no-space test-result-title-font">Result: %s</span><br>
                                    <b>Platform: %s - Toolchain: %s</b>
                                    Elapsed Time: %.2f seconds
                                    Build Path: %s
                                    Absolute Build Path: %s
                                    Copy Method: %s
                                    Image Path: %s
                                </p>%s
                            </div>
                        </div>"""

    overlay_dropdowns = get_result_overlay_dropdowns(result_div_id, test_results)

    return overlay_template % (result_div_id,
                               test_name,
                               result_div_id,
                               test_results['single_test_result'],
                               platform,
                               toolchain,
                               test_results['elapsed_time'],
                               test_results['build_path'],
                               test_results['build_path_abs'],
                               test_results['copy_method'],
                               test_results['image_path'],
                               overlay_dropdowns)

def exporter_html(test_result_ext, each_student_path, test_suite_properties=None):
    test_count=0
    test_results_overall=0
   # print(test_result_ext)

    """! Export test results as HTML
    @param test_result_ext Extended report from Greentea
    @details This function will create a user friendly HTML report
    @return String containing the HTML output
    """

    result_cell_template = """
                <td>
                    <div class="result %s" onclick="toggleOverlay('%s')">
                        <center>%s  -  %s&#37; (%s/%s)</center>
                        %s
                    </div>
                </td>"""
    platform_template = """<tr>
                <td rowspan="2" class="level_header">
                    <center>Tests</center>
                </td>%s
            </tr>
            <tr>
                %s
            </tr>"""



    grade_format = """
                    <p style="text-align:center;font-size:25px;font-family: "Times New Roman" New, sans-serif">Grade:<var style="font-size:25px">%s</var>%%
                    </p>
                    """
    unique_test_names = set()
    platforms_toolchains = {}
   # value = input("Please enter a string:\n")
    # Populate a set of all of the unique tests
    for platform_toolchain, test_list in test_result_ext.items():
        # Format of string is <PLATFORM>-<TOOLCHAIN>
        # <PLATFORM> can however contain '-' such as "frdm-k64f"
        # <TOOLCHAIN> is split with '_' fortunately, as in "gcc_arm"
        toolchain = platform_toolchain.split('-')[-1]
        platform = platform_toolchain.replace('-%s'% toolchain, '')
        if platform in platforms_toolchains:
            platforms_toolchains[platform].append(toolchain)
        else:
            platforms_toolchains[platform] = [toolchain]

        for test_name in test_list:
            unique_test_names.add(test_name)

    table = ""
    platform_row = ""
    toolchain_row = ""
    grade=""
    platform_cell_template = """
                <td colspan="%s" class="level_header">
                    <center>%s</center>
                </td>"""
    center_cell_template = """
                <td class="level_header">
                    <center>%s</center>
                </td>"""

    for platform, toolchains in platforms_toolchains.items():
        platform_row += platform_cell_template % (len(toolchains), platform)
        for toolchain in toolchains:
            toolchain_row += center_cell_template % toolchain
    table += platform_template % (platform_row, toolchain_row)

    test_cell_template = """
                <td class="test-column">%s</td>"""
    row_template = """
            <tr>%s
            </tr>"""

    # Loop through the tests and get the results for the different platforms and toolchains
    for test_name in unique_test_names:
        this_row = test_cell_template % test_name
        for platform, toolchains in platforms_toolchains.items():
            for toolchain in toolchains:
                test_results = None

                if test_name in test_result_ext["%s-%s" % (platform, toolchain)]:
                    test_results = test_result_ext["%s-%s" % (platform, toolchain)][test_name]
                else:
                    test_results = {
                        'single_test_result': 'NOT_RAN',
                        'elapsed_time': 0.0,
                        'build_path': 'N/A',
                        'build_path_abs': 'N/A',
                        'copy_method': 'N/A',
                        'image_path': 'N/A',
                        'single_test_output': 'N/A',
                        'platform_name': platform,
                        'test_bin_name': 'N/A',
                        'testcase_result': {}
                    }

                test_results['single_test_passes'] = 0
                test_results['single_test_count'] = 0



                result_div_id = "target_%s_toolchain_%s_test_%s" % (platform, toolchain, test_name.replace('-', '_'))

                result_overlay = get_result_overlay(result_div_id,
                                                    test_name,
                                                    platform,
                                                    toolchain,
                                                    test_results)

                # Loop through the test cases and count the passes and failures
                for index, (testcase_result_name, testcase_result) in enumerate(test_results['testcase_result'].items()):
                    test_results['single_test_passes'] += testcase_result['passed']
                    test_count=test_count+1
                    test_results_overall += testcase_result['passed']
                    test_results['single_test_count'] += 1


                result_class = get_result_colour_class(test_results['single_test_result'])
                try:
                    percent_pass = int((test_results['single_test_passes']*100.0)/test_results['single_test_count'])
                except ZeroDivisionError:
                    percent_pass = 100



                this_row += result_cell_template % (result_class,
                                                    result_div_id,
                                                    test_results['single_test_result'],
                                                    percent_pass,
                                                    test_results['single_test_passes'],
                                                    test_results['single_test_count'],
                                                    result_overlay)

        table += row_template % this_row



    try:
        overall_percent_pass = float((test_results_overall/test_count)*100)
    except ZeroDivisionError:
        overall_percent_pass = 100
    #print(overall_percent_pass)
    #print(count)
    grade=grade_format % overall_percent_pass
    # Add the numbers of columns to make them have the same width
    return html_template % (get_result_colour_class_css(),each_student_path,len(test_result_ext), table,grade)

"""
student_info(): To get student_info from atext file
"""
def student_info():
    student_info_file=open("info.txt","r+")
    student_info_file.seek(0)
    display_info=student_info_file.readline()
   # print(display_info)
    info=""
    info_template="""
                 <p style="text-align:center;font-size:25px;font-family:Arial,sans-serif">
                 <var style="font-size:25px">%s</var>
                 </p>
                 """
    info=info_template % (display_info)
    return info
