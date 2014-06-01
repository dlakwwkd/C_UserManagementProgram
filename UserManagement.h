#ifndef __USERMANAGEMENT_H__
#define __USERMANAGEMENT_H__

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct{
	int userId;
	char userName[20];
	char userAddress[32];
	char handphone[20];
}UserInfo;

void printMain(void);
void printList(UserInfo userInfo[], int count);
void setUserInfo(UserInfo userInfo[], FILE *readFile);
int addUser(UserInfo userInfo[], int count);
void saveInfo(UserInfo userInfo[], FILE *writeFile, int count);

#endif