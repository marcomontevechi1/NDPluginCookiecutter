import sys
import shutil
import os

def remove_file(filename):
    if os.path.isfile(filename):
        os.remove(filename)
    else:
        print("ERROR: file '{}' can not be deleted.".format(filename))
        sys.exit(1)

def remove_dir(dirname):
    if os.path.isdir(dirname):
        shutil.rmtree(dirname)
    else:
        print("ERROR: directory '{}' can not be deleted.".format(dirname))
        sys.exit(1)

def main():
    if '{{ cookiecutter.keep_E3_Makefile }}' == 'N':
        remove_file("{{ cookiecutter.project_name }}.Makefile")
    if '{{ cookiecutter.keep_bash_build_script }}' == 'N':
        remove_file("build")

if __name__ == '__main__':
    main()

