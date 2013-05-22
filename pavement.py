import os
from paver.easy import task


@task
def buildmodule():
    """build module"""
    os.system('phpize')
    os.system('./configure')
    os.system('make')


@task
def allclean():
    """clean and rollback default constitution"""
    os.system('rm -rf ./* .deps .libs')
    os.system('git reset --hard HEAD')


@task
def fresh():
    """clean and build"""
    allclean()
    buildmodule()

@task
def exec_examples():
    """execute all examples"""
    os.chdir('examples')
    os.system('php example.php')
