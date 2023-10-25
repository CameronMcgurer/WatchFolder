#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>

void outputToFile(char* line, char* outputPath, size_t childNum){
    // get command
    char* firstSpace = strchr(line, ' ');
    int commandLen = firstSpace - line;
    char* command = calloc(commandLen + 1, sizeof(char)); 
    strncpy(command, line, commandLen);

    // get time for index value
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // create complete output file path using the path, command, anf unique index  
    size_t outputFilePathLen = strlen(command) + strlen(outputPath) + 100;
    char* outputFilePath = calloc(outputFilePathLen + 1, sizeof(char));
    snprintf(outputFilePath, outputFilePathLen, "%s%s_%d-%02d-%02d-%02d-%02d-%02d-%zd.txt", outputPath, command, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, childNum);
    printf("%s\n", outputFilePath);

    int fd = open(outputFilePath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    dup2(fd, 1);   // make stdout go to file

    close(fd);     // fd no longer needed - the dup'ed handles are sufficient

    execlp(command, command, NULL);

    free(command);

    free(outputFilePath);

    exit(0);
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

    // get each line, create child process' to call output function on each
    char line[100];
    int k = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        int p = fork();
		if (p == 0) {
			outputToFile(line, outputPath, k);
		} 
		else if (p < 0) {
			printf("error when creating child process %d\n", k+1);
		}
        else {
            while (wait(NULL) > 0) {}
        }
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