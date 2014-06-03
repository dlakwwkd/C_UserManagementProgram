#ifndef __USERMANAGEMENT_H__
#define __USERMANAGEMENT_H__

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


#define NAME_PHONE_BUFFER 20
#define ADDRESS_BUFFER 32

#define UP_ARROW_KEY 72
#define DOWN_ARROW_KEY 80
#define LEFT_ARROW_KEY 75
#define RIGHT_ARROW_KEY 77
#define ENTER_KEY 13
#define ESC_KEY 27
#define ARROW_BUFFER 224


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
void saveInfo(UserInfo userInfo[], FILE *writeFile, int count);
int deleteUser(UserInfo userInfo[], int count);
int searchUser(UserInfo userInfo[], int count, int menu);
void bottomMessage(void);
void deleteMessage(void);


#endif