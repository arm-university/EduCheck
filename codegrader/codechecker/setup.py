import os
from io import open
from setuptools import setup

repository_dir = os.path.dirname(__file__)


def readme():

    with open("README.md") as f:
        return f.read()


with open(os.path.join(repository_dir, "requirements.txt")) as fh:
    requirements = fh.readlines()

python_requires = ">=2.7.10, !=3.0.*, !=3.1.*, !=3.2.*, !=3.3.*, !=3.4.*," \
                  "!=3.8.*, !=3.9.*, <4"
setup(
    name="labcheck",  # Need a unique name to avoid clash
    version="0.0.1",
    description="Arm Education Edkit Labs code checking",
    long_description=readme(),
    long_description_content_type="text/markdown",
    classifiers=[
        "Development Status :: 5 - Production",
        # to be completed to reflect appropriate license
        "License :: ....... :: ........ License",
        "Program Language :: Python :: 3",
        "Operating System :: OS Independent",
    ],
    entry_points={
        "console_scripts": [
            "labcheck=labcheck.educheck:main",
        ],
    },
    url="",
    author="Arm Education",
    # to be changed to reflect the author
    author_email="oyinkuro.benafa@arm.com",
    keywords="grade labs check arm education mbed greantea",
    license="Apache-2.0",  # to be completed to reflect appropriate license
    packages=["labcheck"],
    zip_safe=False,
    python_requires=python_requires,
    install_requires=requirements,
)
