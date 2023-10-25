<h1> Implementation of a Watch Folder </h1>

<h2> Description </h2>
This progect is an implementation of a watch folder script that runs the different versions of the C programs on files, with a specific expention (.dat), that are added to the watch folder. There are three different versions of the C program that can be ran. The C programs take in fiels with the .dat extension. These files contain terminal commands that the program redirects to an output file. 

- Version 1 (progV1.c)
    - This version of the program takes at least two inputs: an output folder path and one or more paths to .dat files. The program loops over these input files and calls the system() function on each line of every file. It redirects the output of the termial command from stdout to a unique file in the specified output folder.
- Version 2 (progV2.c)
    - This program takes the same inputs as, and is very similar to, the first except that it creates a child process, instead of looping, to handle every line in each input file. This program also uses the system() command 
- Version 3 (progV3.c)
    - This version of the program is quite similar to the previous one except that it uses the exec() function insetad of system() to call each of the terminal commands from each line of each file
- Script (watch.sh)
    - This is a script that takes three parameters: a path to a watch folder, an index for which version of the C program to run, and a path to an output folder. If the watch folder does not exist then the script creates one at the provided file path. Then the script searches through the watch folder and saves whats currently in it. This is compared the the current state of the folder (which is checked every 10 seconds), if the contents of the folder change it then searches for all new .dat files in both the watch folder and an subfolders. Lastly it runs the specified version of the C program with the .dat files found and then the process repeats until the script is ended.
  
<h2> Languages Used </h2>

- <b> C </b>
- <b> Bash </b>
