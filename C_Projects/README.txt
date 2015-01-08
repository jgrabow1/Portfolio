DISCLAIMER: Please keep in mind this is one of my first major C projects that I ever created. It is not the most efficient or the most documented program. It is simply meant to be a demonstration of my knowledge of C.

This is a virtual file system that I created using C language.
type 'menu' for list of commands.
Commands:
'pwd' -> shows you the path you are currently in.
'ls' -> shows all directories and files in your current directory or whichever directory you enter as parameter.
'mkdir' -> Creates a directory.
'rmdir' -> Removes a directory.
'creat' -> Creates a file.
'rm' -> Removes a file.
'save' -> Saves current state to text file.
'load' -> Loads state from text file.

List of known bugs:
'cd ..' has not been implemented.
trying to remove a directory using 'rm' breaks code.
trying to remove a file using 'rmdir' breaks code.
