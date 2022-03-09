#pragma once
#include<stdio.h>
#include<iostream>
#include <string>

FILE* fp;
std::string savefile;
int stage;

void opensave() {
	fp = fopen("savefile.txt", "a+");
	if (fscanf(fp, "%s %d", savefile, &stage) != EOF)
		printf("%d", stage);
	fclose(fp);
}
