#ifndef __USERMANAGEMENT_H__
#define __USERMANAGEMENT_H__

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>


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

#define MENU_NUM 6

#define NAME 1
#define ADDRESS 2
#define PHONE 3
#define TAB 4

#define INSERT 1
#define _DELETE 1
#define MODIFY 2
#define SEARCH 3

#define SAVE 1
#define EXIT 2

#define ON 1
#define OFF 0

#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define DEF_COLOR SetConsoleTextAttribute(col, 63)
#define TOP_COLOR SetConsoleTextAttribute(col, 31)
#define BOT_COLOR SetConsoleTextAttribute(col, 241)
#define WAR_COLOR SetConsoleTextAttribute(col, 207)
#define BOX_COLOR SetConsoleTextAttribute(col, 113)
#define BEAUTI1_COLOR SetConsoleTextAttribute(col, 57)
#define BEAUTI2_COLOR SetConsoleTextAttribute(col, 62)
#define BEAUTI3_COLOR SetConsoleTextAttribute(col, 62)
#define BEAUTI4_COLOR SetConsoleTextAttribute(col, 63)

#define DO	524
#define RE	588
#define MI	660
#define PA	698
#define SOL	784
#define RA	884
#define SI	958
#define _DO	1048

#define DURATION 70


typedef struct{
	int userId;
	char userName[NAME_PHONE_BUFFER];
	char userAddress[ADDRESS_BUFFER];
	char handphone[NAME_PHONE_BUFFER];
}UserInfo;


UserInfo* setUserInfo(UserInfo userInfo[], FILE *readFile);

void printMain(int menu, char *menu_num[MENU_NUM]);
void printMainSub(int menu, char *menu_num[MENU_NUM]);
void printList(UserInfo userInfo[]);
void printListSub(UserInfo userInfo[], int page, int *ptr, int swit);

void menuSelectA(int menu, int max, char *menu_num[MENU_NUM]);
void menuSelectB(int menu, int max, char *menu_num[MENU_NUM]);
void menuSelectC(int menu, int max, char *menu_num[MENU_NUM]);
void topMessage(char mess[], char top[]);
void bottomMessageA(void);
void bottomMessageB(char mess[]);
void bottomMessageC(void);
void centerMessage(char mess[], char top[]);
void messageBoxA(char mess[]);
void messageBoxB(char str[], char mess[]);
void warningMessage(int input, int max, int *ptr);

void addUser(UserInfo userInfo[]);
void deleteUser(UserInfo userInfo[], int del);
void modifyUser(UserInfo userInfo[], int fix);

void dataInputA(UserInfo userInfo[]);
int dataInputB(UserInfo userInfo[], int switB, char *temp, int fix, char str[], int min, int max);
int dataInputAction(int warning, int switB, int *ptrC, char *temp, int min, int max);
void dataInputWarning(char *temp, int switA, int switB, int switC);

void searchMain(UserInfo userInfo[], int todo, char mess[], char top[]);
int searchUser(UserInfo userInfo[], int menu);
int searchManyPrint(UserInfo userInfo[], int overlap[], int num);
void searchResult(UserInfo userInfo[], int num);

int saveInfo(UserInfo userInfo[], FILE *writeFile);
int closeProgram(void);
void closeGift(void);

void inSound(void);
void outSound(void);
void actionSound(void);
void resultSound(void);
void warningSound(void);
void moveSound(void);


#endif