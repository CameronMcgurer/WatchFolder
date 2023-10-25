#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void outputToFile(char* line, char* outputPath, size_t commandNum){
    // get command from line
    char* firstSpace = strchr(line, ' ');
    int commandLen = firstSpace - line;
    char* command = calloc(commandLen + 1, sizeof(char)); 
    strncpy(command, line, commandLen);

    // get time for index value
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // combine output path, command, line, and unique index for correct system call
    size_t redirectedLineLen = strlen(line) + strlen(outputPath) + commandLen + 100;
    char* redirectedLine = calloc(redirectedLineLen + 1, sizeof(char));
    snprintf(redirectedLine, (redirectedLineLen), "%s > %s%s_%d-%02d-%02d-%02d-%02d-%02d-%zd.txt", line, outputPath, command, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, commandNum);

    free(command);

    system(redirectedLine);

    free(redirectedLine);
}

void readFile(char* filePath, char* outputPath){
    // check for '/' at the end of output path, add one if not present
    size_t outputPathLen = strlen(outputPath);
    if (outputPath[outputPathLen - 1] != '/') {
        char *newOutputPath = (char *)malloc(outputPathLen + 2);
        snprintf(newOutputPath, outputPathLen + 2, "%s/", outputPath);
        outputPath = newOutputPath;
    }

	// open file via file path
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
		printf("Cannot open file \"%s\"\n", filePath);
		exit(1);
	}

    // get each line and call output function on each
    char line[100];
    int k = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        outputToFile(line, outputPath, k);
        k++;
    }

    fclose(file);
}

int main(int argc, char* argv[]){
    if (argc <  3) {
        printf("Usage: ./fibo <output file path> <input file path>.dat+\n");
        exit(1);
    }

    for (int arg = 2; arg < argc; arg++) {
        // read function also calls output function
        readFile(argv[arg], argv[1]);
    }
	
	return 0;
}
