#ifndef __USERMANAGEMENT_H__
#define __USERMANAGEMENT_H__

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


#define NAME_PHONE_BUFFER 20
#define ADDRESS_BUFFER 32
#define OVERLAP_BUFFER 10

#define UP_ARROW_KEY 72
#define DOWN_ARROW_KEY 80
#define LEFT_ARROW_KEY 75
#define RIGHT_ARROW_KEY 77
#define ENTER_KEY 13
#define ESC_KEY 27
#define ARROW_BUFFER 224

#define INSERT 1
#define UPDATE 2

#define NAME 1
#define ADDRESS 2
#define PHONE 3
#define TAB 4

#define DELETE 1
#define MODIFY 2
#define SEARCH 3

#define SAVE 1
#define EXIT 2

typedef struct{
	int userId;
	char userName[NAME_PHONE_BUFFER];
	char userAddress[ADDRESS_BUFFER];
	char handphone[NAME_PHONE_BUFFER];
}UserInfo;


void printMain(int menu);
void printList(UserInfo userInfo[], int count);

void setUserInfo(UserInfo userInfo[], FILE *readFile);
int addUser(UserInfo userInfo[], int count);
int saveInfo(UserInfo userInfo[], FILE *writeFile, int count);

int deleteUser(UserInfo userInfo[], int count, int del);
int searchUser(UserInfo userInfo[], int count, int menu);

void bottomMessage(void);
void deleteMessage(char mess[]);

int searchManyPrint(UserInfo userInfo[], int overlap[], int num);
void modifyUser(UserInfo userInfo[], int count, int fix);

int dataInput(UserInfo userInfo[], int count, int switA, int switB, char *temp, int fix, char str[], int min, int max);
int dataInputAction(int warning, int switB, int *ptrC, char *temp, int min, int max);

int searchMain(UserInfo userInfo[], int count, int todo, char top[], char bar[]);
void searchResult(UserInfo userInfo[], int num);

int closeProgram(void);

#endif