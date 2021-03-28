#include <sys/dir.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INCREASE 2
#define ADD_PATH "/add"
#define MUL_PATH "/mul"
#define ADD "add"
#define MUL "mul"
#define ERROR "Error!"


int arrayNamesFoldersFiles(char ***arrNames, DIR **dir) {
	int size = 0;
	int capacity = 5;
	*arrNames = (char **) malloc(capacity * sizeof(char *));
	if (*dir) {
		struct dirent *de = readdir(*dir);
		while (de) {
			if (capacity == size + 1) {
				char **tempList = (char **) realloc(*arrNames, (capacity * INCREASE) * sizeof(char *));
				if (!tempList) {
					puts(ERROR);
					return 0;
				}
				capacity *= INCREASE;
				*arrNames = tempList;
			}
			int lengthName = strlen(de->d_name) + 1;
			(*arrNames)[size] = (char *) malloc(lengthName * sizeof(char));
			strcpy((*arrNames)[size], de->d_name);
			size++;
			de = readdir(*dir);
		}
	}
	return size;
}


long long calcNumsFile(char *path, char action) {
	FILE *file = fopen(path, "r");
	if (!file) {
		puts(ERROR);
		return 0;
	}
	long long result = (action == 'a' ? 0 : 1);
	long long tempNum;
	while (fscanf(file, "%lld", &tempNum) != EOF) {
		result = (action == 'a' ? result + tempNum : result * tempNum);
	}
	fclose(file);
	return result;
}

long long calcInDir(char **dirPath, char action, int indexDirPath, int *sizeDirPath) {
	long long result = (action == 'a' ? 0 : 1);
	DIR *dir = opendir(*dirPath);
	char **arr;
	int size = arrayNamesFoldersFiles(&arr, &dir);
	for (int i = 0; i < size; ++i) {
		long long num;
		if (!strcmp(arr[i], ADD)) {
			if (indexDirPath + 4 > *sizeDirPath) {
				char *tempStr = (char *) realloc(*dirPath, (*sizeDirPath + 4 + 1) * sizeof(char));
				if (!tempStr) {
					puts(ERROR);
					return 0;
				}
				*sizeDirPath += 4;
				*dirPath = tempStr;
			}
			strcpy((*dirPath) + indexDirPath, ADD_PATH);
			num = calcInDir(dirPath, 'a', indexDirPath + 4, sizeDirPath);
			(*dirPath)[indexDirPath] = '\0';
		}
		else if (!strcmp(arr[i], MUL)) {
			if (indexDirPath + 4 > *sizeDirPath) {
				char *tempStr = (char *) realloc(*dirPath, (*sizeDirPath + 4 + 1) * sizeof(char));
				if (!tempStr) {
					puts(ERROR);
					return 0;
				}
				*sizeDirPath += 4;
				*dirPath = tempStr;
			}
			strcpy(*dirPath + indexDirPath, MUL_PATH);
			num = calcInDir(dirPath, 'm', indexDirPath + 4, sizeDirPath);
			(*dirPath)[indexDirPath] = '\0';
		}
		else if (strcmp(arr[i], ".") && strcmp(arr[i], "..")) {
			int length = strlen(arr[i]);
			if (indexDirPath + length + 1 > *sizeDirPath) {
				char *tempStr = (char *) realloc(*dirPath, (*sizeDirPath + length + 1 + 1) * sizeof(char));
				if (!tempStr) {
					puts(ERROR);
					return 0;
				}
				*sizeDirPath += length + 1;
				*dirPath = tempStr;
			}
			(*dirPath)[indexDirPath] = '/';
			strcpy(*dirPath + indexDirPath + 1, arr[i]);
			num = calcNumsFile(*dirPath, action);
			(*dirPath)[indexDirPath] = '\0';
		}
		else
			continue;

		result = (action == 'a' ? result + num : result * num);
	}
	closedir(dir);
	for (int i = 0; i < size; ++i)
		free(arr[i]);
	free(arr);
	return result;
}


int main() {
	int capacity = 10;
	char *dir = (char *) malloc(capacity * sizeof(char));
	strcpy(dir, "./tmp");
	long long result = calcInDir(&dir, 'a', 5, &capacity);
	FILE *output = fopen("result.txt", "w");
	fprintf(output, "%lld", result);
	//printf("%lld", result);
	fclose(output);
	free(dir);
	return 0;

}


