from distutils.core import setup

files = ["PyBattleship.py", "README.txt"]

setup(name = "PyBattleship" , version = "1.0" , description = "A game played on a grid against the AI.", author = "James Grabowski", author_email = "james.grabowski@wsu.edu", url = "http://users.tricity.wsu.edu/~bobl/cpts481/", packages = ['PyBattleship'], package_data = {'PyBattleship' : files})
