# What is Educheck?
Educheck is an auto grader tool for coding exercises developed by Arm Education.

Educheck:
- Grades code functionality in the lab exercises supplied with the Arm Education Kit.
- Leverages on the Arm Mbed OS and Mbed Greentea to perform functional testing on submitted code, i.e. checks if the students' code will produce expected outputs and runs the test on a physical Mbed-enabled board.
- Assumes that an incomplete skeleton code will be provided to the students who will fill in the blanks or build their code upon.
- Does not assess code quality or plagiarism in submissions at the moment.
- Provides HTML report for student code grades, for example: </br>
    <img src="./docs/labcheck_html_result.PNG" alt="Educheck HTML report" width="60% "/>

# Requirements
## Hardware requirements:
Educheck requires the following hardware:
- An Arm Mbed-enabled board.

**Note: Educheck currently will not work if you do not connect a Mbed-enabled board while running Educheck. However you will not need any lab peripherals connected to the board itself.**

The following boards were tested with Educheck:
- STMF746G-DISCO
- NUCLEO-F401RE
- NUCLEO-F091RC
- LPC-1768

## Software requirements
The Educheck tool was tested in the following environment:
- Windows OS 10 (not WSL)
- mbed-cli 1.10.5 (Mbed Command Line Interface package)
- Mbed OS 6.5
- Mbed-Greentea 1.8.3
- Python 3.7.9
- pip 21.0.1
- Git 2.16.2.windows.1
- Mercurial 5.6.1
- GNU Compiler: GNU Arm Embedded Toolchain
(9_2020_q2_update)

**Note: See the [`Getting_Started.md`](./docs/Getting_Started.md) documentation for installation information.**

# Getting started
See the [`Getting_Started.md`](./docs/Getting_Started.md) documentation for installation information and how to
run Educheck.

# [Arm Internal only] Cloning Educheck from Git
## For first-time users (non-code contributors):
1. Ensure Git has been installed.
2. Open a command terminal and set Git username and email:
    ```
    git config --global user.name "Arm UserName, e.g. abc01"
    git config --global user.email your_arm_email_address@arm.com
    ```
3. Clone the Educheck Repo
    ```
    git clone "https://eu-gerrit-1.euhpc.arm.com/edu-research/educheck"
    ```
4. Change directory to educheck and switch branch to development-interface
    ```
    cd educheck
    git checkout development-interface
    ```
## For Arm Education code contributors:
1. Go to https://eu-gerrit-1.euhpc.arm.com/admin/repos/edu-research/educheck and make sure you are signed in (top right icon).
2. Copy the **Clone with commit-hook** command and run the command in your terminal. (the clone command should use ssh with your Arm username)
3. Change directory to educheck and switch branch to development-interface
    ```
    cd educheck
    git checkout development-interface
    ```

# Expected directory structure
**You must put unique student folders containing the code to be tested in the STUDENT_HOMEWORK folder. Each unique student folder should not have nested folders. A working example would be: *STUDENT_HOMEWORK/student1/mp3player.cpp*.** The Educheck tool expects the following directory structure.
```
.
└── educheck
    ├── codegrader
    │   ├── README.md
    │   ├── docs/                       // Documentation Folder
    │   ├── STUDENT_HOMEWORK/           // Place unique student folders in here
    │   │   ├── student1
    │   │   │   └── mp3player.cpp
    │   │   ├── student2
    │   │   ├── student3
    │   │   ├── student4
    │   │   ├── student5
    │   │   └── test.cpp                // Educheck skips this test.cpp as it is
    |   |                                   not a unique folder
    |   |
    │   ├── codechecker/                // Educheck Source Code Package
    │   └── mbed_files/                 // Educheck pulls & builds Mbed OS in here
    ├── install.bat                     // Installation file for Educheck
```

See the [`Getting_Started.md`](./docs/Getting_Started.md) for more information.

# Known issues:
Please read the [`Troubleshooting_Guide.md`](./docs/Troubleshooting_Guide.md) for more information.

# Contribution
Please contact rsh-edu-eng@arm.com if you would like to contribute or if you have any comments on Educheck.

