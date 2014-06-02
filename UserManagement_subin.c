/*
	작성자: 141033 박수빈
	최종 작성일: 2014.06.02
	설명: 사용자 입장에서 최대한 간편하게 느낄 수 있도록 디자인 했습니다.

	 1. 문자열 입력이 필요한 부분(회원 등록 중)을 제외하고는 따로 엔터를 쳐줄 필요가 없도록 하였으며,
		페이지 넘김, 메뉴 이동은 방향키로, 나가기는 ESC키, 확인은 엔터키를 사용할 수 있게 하였습니다.

	 2. 회원 등록 시 리스트에 제대로 출력될 수 있는 값 범위 안으로 입력을 제한하였습니다.
		(즉, 너무 길거나 짧은 입력, Tap입력 등은 사전에 방지)
		또한 입력 도중 취소하고 바로 나가고 싶을 경우를 위해 탈출 명령어도 만들어놨습니다.
		그리고 입력을 다 한 후 맘에 안 들어서(?) 추가하고 싶지 않을 수도 있으므로 마지막에 선택 가능하게 하였습니다.


		=== 변경 사항 (2014.06.02) ===

		* 메인 화면 인터페이스 변경 ( 숫자 입력에서 화살표 입력으로 )
		* 연락처 입력시 형식에 정확히 맞아야 입력 되도록 입력 제한 기능 강화 
		* 검색 기능, 삭제 기능(아직 미완) 추가
		* 몇몇 주석 수정

*/
#include "UserManagement.h"

int main(void)
{
	UserInfo *userInfo;
	FILE *readFile;
	FILE *writeFile;
	int input, maxsize, count = -1, menu = 1;

	readFile = fopen("data.txt", "rt");	//readFile 초기화
	if (readFile == NULL){
		puts("\n\n\n\n\n\n\n\n\n\n\n\t\t\t 데이터가 존재하지 않습니다! \n\n\n\n\n\n\n\n\n\n\n");
		return -1;
	}
	while (!feof(readFile)){	//초기 회원수 count에 저장
		if (fgetc(readFile) == '\n') count++;
	}
	maxsize = 2 * count;	//초기 회원수의 2배 만큼 메모리 할당
	userInfo = (UserInfo*)malloc(sizeof(UserInfo)*maxsize);

	fseek(readFile, 0, SEEK_SET);		//파일 포인터 처음 위치로 귀환
	setUserInfo(userInfo, readFile);	//구조체 배열에 파일 데이터 저장 및 readFile close

	while (1){
		printMain(menu);
		input = getch();
		if (input == 224)	//방향키는 입력 시 224값이 들어온 후 72, 80 등의 다른 값이 들어옴
			input = getch();	//그래서 224가 들어올 경우 버퍼를 한번 비우도록 하였음
		switch (input)
		{
		case 72: //상 방향키
			if (menu > 1) menu--;
			break;
		case 80: //하 방향키
			if (menu < 6) menu++;
			break;

		case 13: //enter키
			switch (menu)
			{
			case 1:	//출력
				printList(userInfo, count);
				break;
			case 2:	//등록
				count = addUser(userInfo, count);
				if (count > maxsize - 5){	//메모리 할당량 한계치에 가까워지면 추가할당
					maxsize *= 2;
					userInfo = (UserInfo*)realloc(userInfo, sizeof(UserInfo)*maxsize);
				}
				break;
			case 3:	//삭제
				deleteUserMain(userInfo, count);
				
				break;
			case 4:	//수정
			case 5:	//검색
				printf("아직 구현 되지 않은 기능입니다.");
				break;
			case 6:	//저장
				writeFile = 0;	// writeFile을 넘기기 위해 초기화
				saveInfo(userInfo, writeFile, count);
				break;
			} //switch(menu) out
			break;

		case 27: //esc키
			printf("프로그램을 종료합니다.\t");
			free(userInfo);
			return 0;
		default:
			printf("잘못된 입력입니다.");
			break;
		} //switch(input) out
	}
	free(userInfo);
	return 0;
}


void printMain(int menu)
{
	system("cls");
	puts("Main ");
	puts("\n\t\t\t      회원 관리 프로그램 \n");
	puts("-------------------------------------------------------------------------------");
	if (menu == 1) puts("\n\n\t\t\t      [ 회원 명단 출력 ]");
	else puts("\n\n\t\t\t        회원 명단 출력 ");
	if (menu == 2) puts("\n\t\t\t      [ 신규 회원 등록 ]");
	else puts("\n\t\t\t        신규 회원 등록 ");
	if (menu == 3) puts("\n\t\t\t      [ 기존 회원 삭제 ]");
	else puts("\n\t\t\t        기존 회원 삭제 ");
	if (menu == 4) puts("\n\t\t\t      [ 회원 정보 수정 ]");
	else puts("\n\t\t\t        회원 정보 수정 ");
	if (menu == 5) puts("\n\t\t\t      [ 현재 회원 검색 ]");
	else puts("\n\t\t\t        현재 회원 검색 ");
	if (menu == 6) puts("\n\t\t\t      [ 변경 사항 저장 ]\n\n\n");
	else puts("\n\t\t\t        변경 사항 저장 \n\n\n");
	puts("-------------------------------------------------------------------------------");
	puts("\t메뉴 이동 : ↑↓\t메뉴 선택 : ENTER      \t   종료: ESC");
	puts("-------------------------------------------------------------------------------");
}
void printList(UserInfo userInfo[], int count)
{
	int input, page, i, k = 1;
	page = 1 + count / 18;
	while (1){
		system("cls");
		printf("List   \t\t\t\t\t\t\t\t     page %d/%d\n", k, page);
		puts("\t회원ID\t 이름\t  연락처\t  주소");
		puts("-------------------------------------------------------------------------------");
		for (i = 1+(k-1)*18; i <= k*18 && i <= count; i++)
			printf("\t%d\t %s\t  %s\t  %s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].handphone, userInfo[i].userAddress);
		puts("-------------------------------------------------------------------------------");
		puts("\t 페이지 이동 :   <-    ->     \t\t 나가기:  ESC");
		puts("-------------------------------------------------------------------------------");
		input = getch();
		if (input == 224)
			input = getch();
		switch (input)
		{
		case 75:	//좌측 방향키
			if (k != 1) k--;
			break;
		case 77:	//우측 방향키
			if (k != page) k++;
			break;
		case 27:	//esc키
			return;
		default:
			printf("잘못된 입력입니다.");
			break;
		}
	}
}
void setUserInfo(UserInfo userInfo[], FILE *readFile)
{
	fscanf(readFile, "%[^\n]", userInfo[0].userAddress);	//첫 문장은 따로 저장
	for (int i = 1; !feof(readFile); i++)
		fscanf(readFile, "%d\t%s\t%[^\t]%s\n", &userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].handphone);
	fclose(readFile);
}
int addUser(UserInfo userInfo[], int count)
{
	int input, warning;
	int id = userInfo[1].userId;
	for (int i = 2; i <= count; i++){	//가장 큰 id값 계산
		id = id > userInfo[i].userId ? id : userInfo[i].userId;
	}
	userInfo[++count].userId = ++id;	//count값 1증가
	// 이전에 입력 받고 저장하지 않은 값이 있을 수 있으므로 아래 식의 정상작동을 위해 초기화
	userInfo[count].userName[1] = 0;
	userInfo[count].handphone[1] = 0;
	userInfo[count].userAddress[1] = 0;
	
	while (1){
		system("cls");
		puts("Register \t\t\t\t\t\t\t out: 'esc'입력\n\n");
		puts("\t\t\t       회원 정보 입력  \n");
		puts("-------------------------------------------------------------------------------");
		printf("\n\n\t\t 회원ID\t: %d \n\n", userInfo[count].userId);

		//이름 입력
		if (userInfo[count].userName[1] == 0){
			printf("\t\t 이름\t: "); gets(userInfo[count].userName); //입력
			if (strcmp(userInfo[count].userName, "esc") == 0) return --count;	//입력값이 esc이면 저장하지 않고 바로 나감
			else if (strlen(userInfo[count].userName) < 4 || strlen(userInfo[count].userName) > 6){	//입력이 이상하면 다시 입력
				for (int i = 0; i < NAME_PHONE_BUFFER; i++) userInfo[count].userName[i] = 0;	//초기화
				puts("\n\n\t\t 이름이 너무 길거나 짧습니다.");
				puts("\t\t 이름은 2 ~ 3 글자만 가능합니다. \n\n\t\t [ 영문 4 ~ 6 글자 ]");
				while (getchar() != '\n');	//버퍼 제거 및 오류 메세지에서 정지를 위해
				continue;
			}
			for (int i = 0; userInfo[count].userName[i] != '\0'; i++){
				if (userInfo[count].userName[i] == '\t'){
					for (int i = 0; i < NAME_PHONE_BUFFER; i++) userInfo[count].userName[i] = 0;
					puts("\n\n\t\t 탭(Tab)은 입력할 수 없습니다!");
					while (getchar() != '\n');
					warning = 1;
					break;
				}
				warning = 0;
			}
			if (warning) continue;	//탭 입력 발견시 다시 입력
		}
		else printf("\t\t 이름\t: %s \n", userInfo[count].userName);	//입력 완료된 항목은 패스
		
		//연락처 입력
		if (userInfo[count].handphone[1] == 0){
			printf("\t\t 연락처\t: "); gets(userInfo[count].handphone);
			if (strcmp(userInfo[count].handphone, "esc") == 0) return --count;
			else if (strlen(userInfo[count].handphone) < 12 || strlen(userInfo[count].handphone) > 13
				|| userInfo[count].handphone[3] != '-' ||	// 연락처 형식 검사 ('-'을 포함했는지)
				userInfo[count].handphone[7] != '-' && userInfo[count].handphone[8] != '-' ||
				userInfo[count].handphone[7] == '-' && userInfo[count].handphone[8] == '-'){
				for (int i = 0; i < NAME_PHONE_BUFFER; i++) userInfo[count].handphone[i] = 0;
				puts("\n\t\t 연락처 형식에 맞지 않습니다. ");
				puts("\t\t 형식에 맞게 입력해주세요. \n\n\t\t [ 예) 010-1234-5678  or  031-123-4567 ]");
				while (getchar() != '\n');
				continue;
			}
			for (int i = 0; userInfo[count].handphone[i] != '\0'; i++){
				if (userInfo[count].handphone[i] == '\t'){
					for (int i = 0; i < NAME_PHONE_BUFFER; i++) userInfo[count].handphone[i] = 0;
					puts("\n\n\t\t 탭(Tab)은 입력할 수 없습니다!");
					while (getchar() != '\n');
					warning = 1;
					break;
				}
				// '-'이외에는 숫자를 입력했는지 검사
				if ((userInfo[count].handphone[i] < '0' || userInfo[count].handphone[i] > '9') &&
					(userInfo[count].handphone[i] != '-' || (i != 3 && i != 7 && i != 8))){
					for (int i = 0; i < NAME_PHONE_BUFFER; i++) userInfo[count].handphone[i] = 0;
					puts("\n\t\t 연락처 형식에 맞지 않습니다.");
					puts("\t\t 형식에 맞게 입력해주세요. \n\n\t\t [ 예) 010-1234-5678  or  031-123-4567 ]");
					while (getchar() != '\n');
					warning = 1;
					break;
				}
				warning = 0;
			}
			if (warning) continue;
		}
		else printf("\t\t 연락처\t: %s \n", userInfo[count].handphone);

		//주소 입력
		if (userInfo[count].userAddress[1] == 0){
			printf("\t\t 주소\t: "); gets(userInfo[count].userAddress);
			if (strcmp(userInfo[count].userAddress, "esc") == 0) return --count;
			else if (strlen(userInfo[count].userAddress) < 20 || strlen(userInfo[count].userAddress) > 30){
				for (int i = 0; i < ADDRESS_BUFFER; i++) userInfo[count].userAddress[i] = 0;
				puts("\n\t\t 주소가 너무 길거나 짧습니다. ");
				puts("\t\t 최소 10글자 이상, 그리고 15글자 이내로 입력해주세요.");
				puts("\n\t\t [ 영문 : 20 ~ 30글자 (공백 포함) ]");
				while (getchar() != '\n');
				continue;
			}
			for (int i = 0; userInfo[count].userAddress[i] != '\0'; i++){
				if (userInfo[count].userAddress[i] == '\t'){
					for (int i = 0; i < ADDRESS_BUFFER; i++) userInfo[count].userAddress[i] = 0;
					puts("\n\n\t\t 탭(Tab)은 입력할 수 없습니다!");
					while (getchar() != '\n');
					warning = 1;
					break;
				}
				warning = 0;
			}
			if (warning) continue;
		}
		else printf("\t\t 주소\t: %s \n", userInfo[count].userAddress);

		puts("\n\n\n\t\t\t   정말로 등록하시겠습니까? \n\n\n\n");
		puts("-------------------------------------------------------------------------------");
		puts("\t\t 등록 :  ENTER     \t\t 취소:  ESC");
		puts("-------------------------------------------------------------------------------");
		input = getch();
		if (input == 13) return count;			//등록하면 증가한 count 반환
		else if (input == 27) return --count;	//등록하지 않으면 count가 증가하지 않으므로 무효
		else printf("잘못된 입력입니다.");
	}
}
void saveInfo(UserInfo userInfo[], FILE *writeFile, int count)
{
	int input;
	while (1){
		system("cls");
		puts("Save \n\n");
		puts("\t\t\t\t변경 내용 저장  \n");
		puts("-------------------------------------------------------------------------------");
		puts("\n\n\n\n\n\t\t\t   정말로 저장하시겠습니까? \n\n\n\n\n");
		puts("-------------------------------------------------------------------------------");
		puts("\t\t 저장 :  ENTER     \t\t 취소:  ESC");
		puts("-------------------------------------------------------------------------------");
		input = getch();
		if (input == 13){
			writeFile = fopen("data.txt", "wt");	//writeFile open
			fprintf(writeFile, "%s\n", userInfo[0].userAddress);
			for (int i = 1; i <= count; i++)
				fprintf(writeFile, "%d\t%s\t%s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].handphone);
			fclose(writeFile);		//writeFile close
			return;
		}
		else if (input == 27) return;
		else printf("잘못된 입력입니다.");
	}
}
void deleteUserMain(UserInfo userInfo[], int count)
{
	int input, menu = 1, del;
	while (1){
		system("cls");
		puts("Delete \n\n");
		puts("\t\t\t        회원 정보 삭제 \n");
		puts("-------------------------------------------------------------------------------");
		puts("\n\n\t\t\t      ◎  검색  방법  ◎");
		puts("\t\t\t       ----------------");
		if (menu == 1) puts("\n\t\t\t      [ 회원ID로  검색 ]");
		else puts("\n\t\t\t        회원ID로  검색 ");
		if (menu == 2) puts("\n\t\t\t      [ 이름으로  검색 ]");
		else puts("\n\t\t\t        이름으로  검색 ");
		if (menu == 3) puts("\n\t\t\t      [ 연락처로  검색 ]\n\n\n");
		else puts("\n\t\t\t        연락처로  검색 \n\n\n");
		puts("-------------------------------------------------------------------------------");
		puts("\t메뉴 이동 : ↑↓\t메뉴 선택 : ENTER      \t 나가기: ESC");
		puts("-------------------------------------------------------------------------------");

		input = getch();
		if (input == 224)
			input = getch();
		switch (input)
		{
		case 72:
			if (menu > 1) menu--;
			break;
		case 80:
			if (menu < 3) menu++;
			break;
		case 13:
			del = searchUser(userInfo, count, menu);


			break;
		case 27:
			return;
		default:
			printf("잘못된 입력입니다.");
			break;
		}
	}
}
int searchUser(UserInfo userInfo[], int count, int menu)
{
	int id, i, input, action = 1;
	char key[NAME_PHONE_BUFFER];
	while (1){
		system("cls");
		puts("Search \n\n");
		puts("\t\t\t        회원 정보 검색 \n");
		puts("-------------------------------------------------------------------------------");
		switch (menu)
		{
		case 1:
			puts("\n\n\t\t\t    ◎  회원ID로 검색  ◎");
			puts("\t\t\t      ------------------");
			if (action){
				printf("\n\t\t\t  ID : "); scanf("%d", &id);
				while (getchar() != '\n');	//버퍼 제거
				for (i = 1; i <= count; i++){	//검색
					if (userInfo[i].userId == id) break;
				}
			}
			else printf("\n\t\t\t  ID : %d \n", id);
			if (i > count) puts("\n\n\n\t\t\t   존재하지 않는 ID입니다! \n\n\n");
			else return i;	//찾은 회원의 배열 위치값 리턴
			break;
		case 2:
			puts("\n\n\t\t\t    ◎  이름으로 검색  ◎");
			puts("\t\t\t      ------------------");
			if (action){
				printf("\n\t\t\t  이름 : "); gets(key);
				for (i = 1; i <= count; i++){
					if (strcmp(userInfo[i].userName, key) == 0) break;
				}
			}
			else printf("\n\t\t\t  이름 : %s \n", key);
			if (i > count) puts("\n\n\n\t\t\t   존재하지 않는 이름입니다! \n\n\n");
			else return i;
			break;
		case 3:
			puts("\n\n\t\t\t    ◎  연락처로 검색  ◎");
			puts("\t\t\t      ------------------");
			if (action){
				printf("\n\t\t\t  연락처 : "); gets(key);
				for (i = 1; i <= count; i++){
					if (strcmp(userInfo[i].handphone, key) == 0) break;
				}
			}
			else printf("\n\t\t\t  연락처 : %s \n", key);
			if (i > count) puts("\n\n\n\t\t\t   존재하지 않는 연락처입니다! \n\n\n");
			else return i;
			break;
		}
		puts("-------------------------------------------------------------------------------");
		puts("\t\t다시 입력 :  ENTER   \t\t나가기:  ESC");
		puts("-------------------------------------------------------------------------------");
		input = getch();
		if (input == 13) action = 1;
		else if (input == 27) return 0;
		else{
			puts("잘못된 입력입니다.");
			action = 0;
		}
	}
}