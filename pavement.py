import os
from paver.easy import task


@task
def buildmodule():
    os.system('phpize')
    os.system('./configure')
    os.system('make')


@task
def allclean():
    os.system('rm -rf ./*')
    os.system('git reset --hard HEAD')
