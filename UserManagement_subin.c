/*
	작성자: 141033 박수빈
	최종 작성일: 2014.06.12
	설명: 사용자 입장에서 최대한 간편하게 느낄 수 있도록 디자인 했습니다.
	      그리고 어떤 상황에서도 문제가 생기지 않는 안전성을 추구했습니다.

	1. 조작키를 방향키, ENTER키, ESC키로 통일 했습니다.
	2. 회원 등록시 리스트에 제대로 출력될 수 있는 값 범위 안으로 입력을 제한하였습니다.
		(즉, 너무 길거나 짧은 입력, Tap입력 등은 사전에 방지)
	3. 가능한 모든 예외상황을 테스트 해보고 있습니다.
	
	=== 변경 사항 (2014.06.12) ===

	* 메인 화면 구성 방법 변경
	* 강조색 사용
	* 메뉴 선택 숫자키로도 가능하도록 수정
	* 페이지 검색 기능 추가
	* 경고 메시지 함수로 분리
	* define 이름 몇몇 가지 통합사용

	=== 변경 사항 (2014.06.10) ===

	* bottomMessageC 추가
	* deleteMessage -> centerMessage로 함수 이름 변경

	=== 변경 사항 (2014.06.08) ===

	* 초기 화면 구성 방법 수정

	=== 변경 사항 (2014.06.07) ===

	* dataInput 함수 3가지 함수로 분리(dataInputA, dataInputB, dataInputWarning)
	* 중복되는 UI 분리 (topMessage, bottomMessageA, bottomMessageB)
	* 주석 추가
	* 사운드 추가
	* UI 색상 조금 변경
	* 사운드 조정
	* UI 개선 (메세지 박스 생성)
	* 종료 노래 조정

	=== 변경 사항 (2014.06.06) ===

	* 회원 등록 중 주소 입력 시 발생할 수 있는 오류 수정
	* 회원 수정 중 탭 입력 시 발생할 수 있는 오류 수정
	* 데이터 파일 로드 중 띄어쓰기 있는 경우 발생하는 오류 수정
	* maxsize, count 전역변수로 변경하고, 전반적인 함수 간소화
	* 함수 위치 기능별 순서에 맞게 재배치
	* 대대적인 UI 개선 (컬러 도입)
	* 파일에 내용이 없을 경우 생기는 오류 수정
	* 추가적인 UI 개선
	
	=== 변경 사항 (2014.06.05) ===

	* 회원 등록시 매번 maxid를 계산하는 것을 처음 한번만 하도록 수정
	* 등록, 삭제, 수정 시에 중첩되는 입력 코드를 함수로 분리해서 단일화
	* 마찬가지로 중복되는 검색 코드를 함수로 분리
	* 여러 정수값 define 설정
	* 검색, 종료 기능 완성
	* 전반적으로 디버깅 하여 발견된 버그 모두 수정

	=== 변경 사항 (2014.06.03) ===

	* 입력키 값 define으로 정의 (ENTER, ESC 등)
	* 코드 정돈 (줄 간격, 들여쓰기 등)
	* 회원 등록 중도 취소 기능 변경 ('esc' 타이핑 -> ESC키 누르는 것으로)
	* 중복되는 메시지 출력 코드 함수로 만들어 압축
	* 검색 시 중복되는 값 필터링 기능 추가
	* 회원 명단 출력 UI 개선

	=== 변경 사항 (2014.06.03)(새벽) ===

	* 회원 명단 출력 UI 개선
	* 회원 등록시 이름 3글자 제한에서 4글자 제한으로 확대
	* 회원 등록시 주소 10 ~ 15글자 에서 5 ~ 15글자로 범위 확대
	* 삭제 기능 완성
	* 버퍼 오버플로우 방지를 위해 함수 교체 (gets -> fgets)
	* fgets는 '\n'을 저장해버리므로 이를 제거하는 과정 추가

	=== 변경 사항 (2014.06.02) ===

	* 메인 화면 인터페이스 변경 ( 숫자 입력에서 화살표 입력으로 )
	* 연락처 입력시 형식에 정확히 맞아야 입력 되도록 입력 제한 기능 강화 
	* 검색 기능, 삭제 기능(아직 미완) 추가
	* 몇몇 주석 수정

*/
#include "UserManagement.h"

static int maxid;	//가장 큰 ID 값
static int maxsize;	//메모리 할당 사이즈
static int count = -1;	//전체 회원 수

int main(void)
{
	system("mode con lines=25 cols=80");	//콘솔 창 크기 초기화

	UserInfo *userInfo = NULL;
	FILE *readFile = NULL;
	FILE *writeFile = NULL;
	int input = 1, menu = 1, choice;
	int *ptr = &menu;
	char *menu_num[MENU_NUM];

	puts("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t        =  시작하는 중  = \n\n\n\n\n\n\n\n\n\n\n");

	userInfo = setUserInfo(userInfo, readFile);	//구조체 배열에 파일 데이터 저장
	if (userInfo == (UserInfo*)-1) return 0;	//오류 났을 경우 바로 종료

	printMainSub(menu, menu_num);	//메인 메뉴 구성

	actionSound();	//로딩 완료 효과음

	while(1) {
		printMain(menu, menu_num);	//메인 화면 출력
		
		input = getch();	//입력
		
		if (input == ARROW_BUFFER)	//방향키는 입력 시 아스키확장 값이 먼저 들어온 후 값이 들어옴
			input = getch();	//그래서 이 경우 버퍼를 한번 비우도록 하였음

		switch (input)
		{
		case UP_ARROW_KEY:	//상 방향키
			if (menu > 1) menu--;
			moveSound();
			break;
		case DOWN_ARROW_KEY:	//하 방향키
			if (menu < 6) menu++;
			moveSound();
			break;
		case ENTER_KEY:		//enter키
			inSound();
			switch (menu)
			{
			case 1:	//출력
				printList(userInfo);
				break;
			case 2:	//등록
				addUser(userInfo);
				break;
			case 3:	//삭제
				searchMain(userInfo, _DELETE, "삭제", "Delete");
				break;
			case 4:	//수정
				searchMain(userInfo, MODIFY, "수정", "Modify");
				break;
			case 5:	//검색
				searchMain(userInfo, SEARCH, "검색", "Search");
				break;
			case 6:	//저장
				saveInfo(userInfo, writeFile);
				break;

			} //switch(menu) out
			break;
		case ESC_KEY:		//esc키
			inSound();
			choice = closeProgram();

			if (choice == SAVE)
				choice = saveInfo(userInfo, writeFile);

			if (choice == SAVE || choice == EXIT){
				printf("프로그램을 종료합니다.\t");
				free(userInfo);
				closeGift();
				return 0;
			}
			else break;
		default:
			warningMessage(input - '0', 6, ptr);
			break;
		} //switch(input) out
	}

	free(userInfo);
	return 0;
}


UserInfo* setUserInfo(UserInfo userInfo[], FILE *readFile)
{
	readFile = fopen("data.txt", "rt");	//readFile open
	if (readFile == NULL){
		puts("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t 데이터가 존재하지 않습니다! \n\n\n\n\n\n\n\n\n\n\n");
		return (UserInfo*)-1;
	}

	while (!feof(readFile)) {	//초기 회원수 count에 저장
		if (fgetc(readFile) == '\n') count++;
	}

	if (count < 1){
		puts("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t 데이터가 존재하지 않습니다! \n\n\n\n\n\n\n\n\n\n\n");
		return (UserInfo*)-1;
	}

	maxsize = 2 * count;	//초기 회원수의 2배 만큼 메모리 할당
	userInfo = (UserInfo*)malloc(sizeof(UserInfo)*maxsize);

	fseek(readFile, 0, SEEK_SET);	//파일 포인터 처음 위치로 귀환
	fscanf(readFile, "%[^\n]", userInfo[0].userAddress);	//첫 문장은 따로 저장

	for (int i = 1; !feof(readFile); i++)
		fscanf(readFile, "%d\t%[^\t]\t%[^\t]\t%[^\n]\n", &userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].handphone);

	fclose(readFile);	//readFile close

	maxid = userInfo[1].userId;		//초기값 설정
	for (int i = 2; i <= count; i++)	//가장 큰 id값 계산
		maxid = maxid > userInfo[i].userId ? maxid : userInfo[i].userId;

	return userInfo;
}


void printMain(int menu, char *menu_num[MENU_NUM])
{
	system("cls");

	TOP_COLOR;
	printf("Main \t\t\t\t\t\t\t\t\t        "); printf("\t\t\t\t\t\t\t\t\t        ");
	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("\t\t\t      회원 관리 프로그램\t\t\t        ");
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;

	menuSelectA(menu, 6, menu_num);

	bottomMessageC();
}

void printMainSub(int menu, char *menu_num[MENU_NUM])
{
	menu_num[0] = "1. 전체 명단 보기";
	menu_num[1] = "2. 신규 회원 등록";
	menu_num[2] = "3. 기존 회원 삭제";
	menu_num[3] = "4. 회원 정보 수정";
	menu_num[4] = "5. 회원 정보 검색";
	menu_num[5] = "6. 변경 사항 저장";

	printMain(menu, menu_num);	//초기 화면 기반
	printMain(menu, menu_num);	//초기 화면 정돈
}

void printList(UserInfo userInfo[])
{
	int input, page, k = 1, temp;
	int *ptr = &k;
	char search[OVERLAP_BUFFER];

	page = 1 + (count - 1) / 18;	//전체 페이지 계산

	while(1) {
		printListSub(userInfo, page, ptr, ON);

		input = getch();

		if (input == ARROW_BUFFER)
			input = getch();
		
		switch (input)
		{
		case LEFT_ARROW_KEY:	//좌측 방향키
			moveSound();
			if (k != 1) k--;
			break;
		case RIGHT_ARROW_KEY:	//우측 방향키
			moveSound();
			if (k != page) k++;
			break;
		case ENTER_KEY:		//enter키
			inSound();
			printListSub(userInfo, page, ptr, OFF);

			printf("페이지 검색: "); fgets(search, OVERLAP_BUFFER, stdin);
			temp = atoi(search);

			if (temp > 0 && temp <= page) k = temp;
			else warningMessage(0, 0, 0);

			break;
		case ESC_KEY:		//esc키
			outSound();
			return;
		default:
			warningMessage(input - '0', page, ptr);
			break;
		}
	}
}

void printListSub(UserInfo userInfo[], int page, int *ptr, int swit)
{
	int i;
	system("cls");

	TOP_COLOR;
	printf("List   \t\t\t\t\t\t\t\t     page %d/%d   ", *ptr, page); printf("\t\t\t\t\t\t\t\t\t        ");
	BOT_COLOR;
	printf("\t회원ID \t 이름   \t연락처  \t주소 \t\t\t\t");
	DEF_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");

	for (i = 1 + (*ptr - 1) * 18; i <= *ptr * 18 && i <= count; i++){	//리스트 출력
		if (i % 6 == 1) BEAUTI2_COLOR;
		else DEF_COLOR;
		printf("\t%d \t %s   \t%s  \t%s\n",
			userInfo[i].userId, userInfo[i].userName, userInfo[i].handphone, userInfo[i].userAddress);
	}

	if (page == *ptr){	//공백 채우기
		for (i = count - (1 + (*ptr - 1) * 18); 17 - i > 0; i++)
			puts(" ");
	}

	if (swit) puts(" ");

	BOT_COLOR;
	printf("\t 페이지 이동 :  ← → or 숫자키\t\t  나가기 :  ESC \t\t");
	DEF_COLOR;
}


void menuSelectA(int menu, int max, char *menu_num[MENU_NUM])
{
	puts("\n");
	for (int i = 0; i < max; i++){
		if (menu == i + 1){
			printf("\n\t\t\t    "); BEAUTI1_COLOR;
			printf("[ "); BEAUTI2_COLOR;
			printf("%s", menu_num[i]); BEAUTI1_COLOR;
			printf(" ] \n"); DEF_COLOR;
		}
		else printf("\n\t\t\t      %s \n", menu_num[i]);
	}
	puts("\n");
}

void menuSelectB(int menu, int max, char *menu_num[MENU_NUM])
{
	puts(" ");
	for (int i = 0; i < max; i++){
		if (menu == i + 1){
			printf("\n\t\t\t     "); BEAUTI1_COLOR;
			printf("[ "); BEAUTI2_COLOR;
			printf("%s", menu_num[i]); BEAUTI1_COLOR;
			printf(" ] \n"); DEF_COLOR;
		}
		else printf("\n\t\t\t       %s \n", menu_num[i]);
	}
	puts("\n\n");
}

void menuSelectC(int menu, int max, char *menu_num[MENU_NUM])
{
	puts(" ");
	for (int i = 0; i < max; i++){
		if (menu == i + 1){
			printf("\n\t\t\t        "); BEAUTI1_COLOR;
			printf("[ "); BEAUTI2_COLOR;
			printf("%s", menu_num[i]); BEAUTI1_COLOR;
			printf(" ] \n"); DEF_COLOR;
		}
		else printf("\n\t\t\t          %s \n", menu_num[i]);
	}
	puts("\n\n");
}

void topMessage(char mess[], char top[])
{
	system("cls");

	TOP_COLOR;
	printf("%s \t\t\t\t\t\t\t\t\t\t ", top); printf("\t\t\t\t\t\t\t\t\t        ");
	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("\t\t\t        회원 정보 %s\t\t\t\t\t ", mess);
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;
}

void bottomMessageA(void)
{
	warningSound();
	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("\t\t다시 입력 :  ENTER   \t\t나가기 :  ESC  \t\t\t  ");
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;
}

void bottomMessageB(char mess[])
{
	warningSound();
	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("\t\t %s :  ENTER     \t\t 취소 :  ESC \t\t\t   ", mess);
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;
}

void bottomMessageC(void)
{
	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("     메뉴 선택 : ENTER     메뉴 이동 : ↑↓ or 숫자키      나가기 : ESC \t       ");
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;
}

void centerMessage(char mess[], char top[])
{
	topMessage(mess, top);

	printf("\n\n\n\n\n\n\t\t\t   "); BOX_COLOR;
	printf("┌──────────┐"); DEF_COLOR;
	printf("\n\t\t\t   "); BOX_COLOR;
	printf("│\t\t\t │"); DEF_COLOR;
	printf("\n\t\t\t   "); BOX_COLOR;
	printf("│     %s  완료     │", mess); DEF_COLOR;
	printf("\n\t\t\t   "); BOX_COLOR;
	printf("│\t\t\t │"); DEF_COLOR;
	printf("\n\t\t\t   "); BOX_COLOR;
	printf("└──────────┘\n\n\n\n\n\n"); DEF_COLOR;

	resultSound();

	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("\t\t\t 계속하려면 아무 키나 누르세요 \t\t\t\t ");
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;

	getch();	//메시지 출력을 위해 정지
}

void messageBoxA(char mess[])
{
	printf("\n\n\n\t\t\t     "); BOX_COLOR;
	printf("┌────────┐"); DEF_COLOR;
	printf("\n\t\t\t     "); BOX_COLOR;
	printf("│ %s │\n", mess); DEF_COLOR;
	printf("\t\t\t     "); BOX_COLOR;
	printf("└────────┘\n"); DEF_COLOR;
}

void messageBoxB(char str[], char mess[])
{
	printf("\n\n\n\t\t\t      "); BOX_COLOR;
	printf("┌───────┐"); DEF_COLOR;
	printf("\n\t\t\t      "); BOX_COLOR;
	printf("│  %s%s  │\n", str, mess); DEF_COLOR;
	printf("\t\t\t      "); BOX_COLOR;
	printf("└───────┘\n"); DEF_COLOR;
}

void warningMessage(int input, int max, int *ptr)
{
	if (input > 0 && input <= max) *ptr = input;
	else{
		WAR_COLOR; printf("잘못된 입력입니다.\t\t\t\t\t\t\t       "); DEF_COLOR;
		warningSound();
	}
}


void addUser(UserInfo userInfo[])
{
	userInfo[++count].userId = ++maxid;	//count값 1증가 시키고 새로운 id 부여
	
	if (count > maxsize - 5){	//메모리 할당량 한계치에 가까워지면 추가할당
		maxsize *= 2;
		userInfo = (UserInfo*)realloc(userInfo, sizeof(UserInfo)*maxsize);
	}

	dataInputA(userInfo);
}

void deleteUser(UserInfo userInfo[], int del)
{
	int input, menu = 1;

	while (del){
		topMessage("삭제", "Delete");

		printf("\n\n\n\n\t\t\t회원ID\t: %d \n\n", userInfo[del].userId);
		printf("\t\t\t이름\t: %s \n", userInfo[del].userName);
		printf("\t\t\t연락처\t: %s \n", userInfo[del].handphone);
		printf("\t\t\t주소\t: %s \n", userInfo[del].userAddress);

		puts("\n\n\n\t\t\t   정말로 삭제하시겠습니까? \n\n\n");
		bottomMessageB("삭제");

		input = getch();

		if (input == ENTER_KEY){
			inSound();
			/* 빈 메모리 공간이 많아지면 메모리 할당량 축소 */
			if (count < maxsize / 3){
				maxsize /= 2;
				userInfo = (UserInfo*)realloc(userInfo, sizeof(UserInfo)*maxsize);
			}
			/* 삭제 대상이 맨 마지막에 있다면, count를 하나 줄이는 것으로 끝 */
			if (del == count){
				centerMessage("삭제", "Delete");
				count--;
				return;
			}
			/* 나머지 경우는 한 칸씩 앞으로 덮어씌움 */
			else{
				for (int i = del + 1; i <= count; i++){
					userInfo[i - 1].userId = userInfo[i].userId;
					strcpy(userInfo[i - 1].userName, userInfo[i].userName);
					strcpy(userInfo[i - 1].userAddress, userInfo[i].userAddress);
					strcpy(userInfo[i - 1].handphone, userInfo[i].handphone);
				}
				centerMessage("삭제", "Delete");
				count--;
				return;
			}
		}
		else if (input == ESC_KEY){
			outSound();
			return;
		}
		else warningMessage(input - '0', 0, 0);
	}
	return;
}

void modifyUser(UserInfo userInfo[], int fix)
{
	int input, menu = 1, action, action2;
	char temp[ADDRESS_BUFFER];
	char *ptr;
	int *ptr2;
	ptr = temp;
	ptr2 = &menu;
	action = 1;
	char *menu_num3[MENU_NUM] = {
		{ "1. 이름" },
		{ "2. 주소" },
		{ "3. 연락처" },
	};
	
	inSound();

	while (action){
		topMessage("수정", "Modify");
		messageBoxA(" 수정할  정보 ");
		menuSelectC(menu, 3, menu_num3);
		bottomMessageC();

		input = getch();

		if (input == ARROW_BUFFER)
			input = getch();

		switch (input)
		{
		case UP_ARROW_KEY:
			moveSound();
			if (menu > 1) menu--;
			break;
		case DOWN_ARROW_KEY:
			moveSound();
			if (menu < 3) menu++;
			break;
		case ENTER_KEY:
			inSound();
			switch (menu){
			case NAME:
				action2 = dataInputB(userInfo, NAME, ptr, fix, "이름  ", 4, 8);

				if (action2){
					strcpy(userInfo[fix].userName, temp);
					centerMessage("수정", "Modify");
				}
				break;
			case ADDRESS:
				action2 = dataInputB(userInfo, ADDRESS, ptr, fix, "주소  ", 10, 30);

				if (action2){
					strcpy(userInfo[fix].userAddress, temp);
					centerMessage("수정", "Modify");
				}
				break;
			case PHONE:
				action2 = dataInputB(userInfo, PHONE, ptr, fix, "연락처", 12, 13);

				if (action2){
					strcpy(userInfo[fix].handphone, temp);
					centerMessage("수정", "Modify");
				}
				break;
			}
			break;
		case ESC_KEY:
			action = 0;
			outSound();
			break;
		default:
			warningMessage(input - '0', 3, ptr2);
			break;
		}
	}
}


void dataInputA(UserInfo userInfo[])
{
	int input, warning = 0, action = 1, switC = 1, switD = 1;
	int *ptrC;
	ptrC = &switC;

	while (1) {
		topMessage("입력", "Regist");

		printf("\n\n\n\n\t\t\t 회원ID\t: %d \n\n", userInfo[count].userId);

		if (switD == 1){
			for (int i = 0; i < NAME_PHONE_BUFFER; i++)
				userInfo[count].userName[i] = 0;
		}
		else if (switD == 2){
			for (int i = 0; i < NAME_PHONE_BUFFER; i++)
				userInfo[count].handphone[i] = 0;
		}
		else if (switD == 3){
			for (int i = 0; i < ADDRESS_BUFFER; i++)
				userInfo[count].userAddress[i] = 0;
		}

		if (switD == 1 && action){
			printf("\t\t\t 이름\t: ");
			switC = NAME;
			warning = dataInputAction(warning, NAME, ptrC, userInfo[count].userName, 4, 8);
			if (!warning) switD = 2;
		}
		else if (switD >= 1) printf("\t\t\t 이름\t: %s \n", userInfo[count].userName);

		if (switD == 2 && action){
			printf("\t\t\t 연락처\t: ");
			switC = PHONE;
			warning = dataInputAction(warning, PHONE, ptrC, userInfo[count].handphone, 12, 13);
			if (!warning) switD = 3;
		}
		else if (switD >= 2) printf("\t\t\t 연락처\t: %s \n", userInfo[count].handphone);

		if (switD == 3 && action){
			printf("\t\t\t 주소\t: ");
			switC = ADDRESS;
			warning = dataInputAction(warning, ADDRESS, ptrC, userInfo[count].userAddress, 10, 30);
			if (!warning) switD = 4;
		}
		else if (switD >= 3) printf("\t\t\t 주소\t: %s \n", userInfo[count].userAddress);


		if (warning){
			dataInputWarning((char*)0, INSERT, 0, switC);

			input = getch();

			if (input == ESC_KEY){
				maxid--;	 count--;	//등록하지 않으면 count 원래대로 되돌려 놓고 종료
				outSound();
				return;
			}
			else if (input == ENTER_KEY){
				action = 1;
				inSound();
			}
			else{
				action = 0;
				warningMessage(input - '0', 0, 0);
			}
		}
		else{
			puts("\n\n\n\t\t\t   정말로 등록하시겠습니까? \n\n\n");

			bottomMessageB("등록");

			input = getch();

			if (input == ESC_KEY){
				maxid--; count--;
				outSound();
				return;
			}
			else if (input == ENTER_KEY){
				actionSound();
				Beep(_DO, DURATION);
				return;	//등록하면 count 증가한 채로 종료
			}
				
			else{
				action = 0;
				warningMessage(input - '0', 0, 0);
			}
		}
	}
}

int dataInputB(UserInfo userInfo[], int switB, char *temp, int fix, char str[], int min, int max)
{
	int input, warning = 0, action = 1, switC = 1, switD = 1;
	int *ptrC;
	ptrC = &switC;

	while (1) {
		topMessage("수정", "Modify");
		messageBoxB(str, "수정");

		switch (switB){
		case NAME:
			printf("\n\t\t   기존 %s : %s \n", str, userInfo[fix].userName);
			break;
		case ADDRESS:
			printf("\n\t\t   기존 %s : %s \n", str, userInfo[fix].userAddress);
			break;
		case PHONE:
			printf("\n\t\t   기존 %s : %s \n", str, userInfo[fix].handphone);
			break;
		}

		printf("\t\t 새로운 %s : ", str);
		if (action){
			switC = switB;
			warning = dataInputAction(warning, switB, ptrC, temp, min, max);
		}
		else printf("%s \n", temp);
		
		if(warning){
			dataInputWarning(temp, MODIFY, switB, switC);

			input = getch();

			if (input == ESC_KEY){
				outSound();
				return 0;	//취소시 0을 리턴 
			}
			else if (input == ENTER_KEY){
				inSound();
				action = 1;
			}
			else{
				action = 0;
				warningMessage(input - '0', 0, 0);
			}
		}
		else{
			puts("\n\n\n\t\t\t   정말로 수정하시겠습니까? \n\n\n");
			bottomMessageB("수정");

			input = getch();

			if (input == ENTER_KEY){
				inSound();
				return 1;	//수정하면 1반환
			}
			else if (input == ESC_KEY){
				outSound();
				return 0;
			}
			else{
				action = 0;
				warningMessage(input - '0', 0, 0);
			}
		}
	}
}

int dataInputAction(int warning, int switB, int *ptrC, char *temp, int min, int max)
{
	int sizeTemp;
	
	if (switB == ADDRESS) fgets(temp, ADDRESS_BUFFER, stdin);
	else fgets(temp, NAME_PHONE_BUFFER, stdin);

	if (*(temp + strlen(temp) - 1) == '\n')	//fgets는 '\n'도 변수에 저장하기 때문에 이를 제거
		*(temp + strlen(temp) - 1) = '\0';
	else while (getchar() != '\n');

	sizeTemp = strlen(temp);	//strlen은 unsigned int 형으로 반환하기 때문

	if (sizeTemp < min || sizeTemp > max)
		warning = 1;
	else
		warning = 0;

	if (!warning){	// !warning의 의미는 이전 검사를 통과했다는 의미
		for (int i = 0; temp[i] != '\0'; i++){
			/* 탭 입력 발견시 다시 입력 */
			if (temp[i] == '\t'){
				*ptrC = TAB;
				warning = 1;
				break;
			}
			/* '-'이외에는 숫자를 입력했는지 검사 */
			if (switB == PHONE){
				if ((temp[i] < '0' || temp[i] > '9') &&
					(temp[i] != '-' || (i != 3 && i != 7 && i != 8))){
					warning = 1;
					break;
				}
			}
			warning = 0;
		}
	}

	if (!warning){
		/* '-'의 위치가 적절한지 검사 */
		if (switB == PHONE && (temp[3] != '-' || temp[7] != '-' &&
			temp[8] != '-' || temp[7] == '-' && temp[8] == '-'))
			warning = 1;
		else
			warning = 0;
	}
	return warning;
}

void dataInputWarning(char *temp, int switA, int switB, int switC)
{
	switch (switC){
	case NAME:
		if (switA == MODIFY){
			for (int i = 0; i < NAME_PHONE_BUFFER; i++)
				temp[i] = 0;
		}
		else puts("\n");
		puts("\n\n\t\t\t 이름이 너무 길거나 짧습니다.");
		puts("\t\t\t 이름은 2 ~ 4 글자만 가능합니다. \n\t\t\t [ 영문 4 ~ 8 글자 ]\n\n");
		break;
	case ADDRESS:
		if (switA == MODIFY){
			for (int i = 0; i < ADDRESS_BUFFER; i++)
				temp[i] = 0;
		}
		puts("\n\t\t  주소가 너무 길거나 짧습니다. ");
		puts("\t\t  최소 5글자 이상, 그리고 15글자 이내로 입력해주세요.");
		puts("\n\t\t  [ 영문 : 10 ~ 30글자 (공백 포함) ]\n\n");
		break;
	case PHONE:
		if (switA == MODIFY){
			for (int i = 0; i < NAME_PHONE_BUFFER; i++)
				temp[i] = 0;
		}
		else puts(" ");
		puts("\n\t\t\t 연락처 형식에 맞지 않습니다. ");
		puts("\t\t\t 형식에 맞게 입력해주세요. \n\n\t\t     [ 예) 010-1234-5678  or  031-123-4567 ]\n\n");
		break;
	case TAB:
		if (switA == MODIFY){
			if (switB == ADDRESS){
				for (int i = 0; i < ADDRESS_BUFFER; i++)
					temp[i] = 0;
			}
			else{
				for (int i = 0; i < NAME_PHONE_BUFFER; i++)
					temp[i] = 0;
			}
		}
		puts("\n\n\n\t\t\t 탭(Tab)은 입력할 수 없습니다!\n\n\n");
		break;
	}
	bottomMessageA();
}


void searchMain(UserInfo userInfo[], int todo, char mess[], char top[])
{
	int input, menu = 1, num;
	int *ptr = &menu;
	char *menu_num2[MENU_NUM] = {
		{ "1. 회원ID로 검색" },
		{ "2. 이름으로 검색" },
		{ "3. 연락처로 검색" }
	};

	while (1) {
		topMessage(mess, top);
		messageBoxB("검색  ", "방법");
		menuSelectB(menu, 3, menu_num2);
		bottomMessageC();

		input = getch();

		if (input == ARROW_BUFFER)
			input = getch();

		switch (input)
		{
		case UP_ARROW_KEY:
			moveSound();
			if (menu > 1) menu--;
			break;
		case DOWN_ARROW_KEY:
			moveSound();
			if (menu < 3) menu++;
			break;
		case ENTER_KEY:
			inSound();
			num = searchUser(userInfo, menu);

			if (num){
				if (todo == _DELETE)
					deleteUser(userInfo, num);
				else if (todo == MODIFY)
					modifyUser(userInfo, num);
				else
					searchResult(userInfo, num);
			}
			break;
		case ESC_KEY:
			outSound();
			return;
		default:
			warningMessage(input - '0', 3, ptr);
			break;
		}
	}
}

int searchUser(UserInfo userInfo[], int menu)
{
	int id, i, input, action = 1, num;
	char key[NAME_PHONE_BUFFER];
	int overlap[OVERLAP_BUFFER];

	while (1) {
		topMessage("검색", "Search");

		switch (menu)
		{
		case 1:
			messageBoxA("회원 ID로 검색");

			if (action){
				printf("\n\n\t\t\t\t ID : "); fgets(key, NAME_PHONE_BUFFER, stdin);

				if (*(key + strlen(key) - 1) == '\n')
					*(key + strlen(key) - 1) = '\0';
				else while (getchar() != '\n');

				id = atoi(key);	//scanf는 엔터값을 무시하기 때문에 fgets로 받고 정수로 변환하였음

				num = 0;
				for (i = 1; i <= count; i++){	//검색
					if (num + 1 >= OVERLAP_BUFFER)
						break;	//검색 결과가 너무 많으면 버퍼 한계치에서 끊음
					if (userInfo[i].userId == id)
						overlap[++num] = i;
				}
			}
			else printf("\n\n\t\t\t\t ID : %d \n", id);

			/* 검색 결과가 1명일 때 */
			if (num == 1) return overlap[num];

			/* 검색 결과가 2명 이상일 때 */
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);

			/* 검색 결과가 없을 때 */
			else puts("\n\n\n\t\t\t    존재하지 않는 ID입니다 ! \n\n\n");
			break;
		case 2:
			messageBoxA("이름으로  검색");

			if (action){
				printf("\n\n\t\t\t     이름 : "); fgets(key, NAME_PHONE_BUFFER, stdin);

				if (*(key + strlen(key) - 1) == '\n')
					*(key + strlen(key) - 1) = '\0';
				else while (getchar() != '\n');

				num = 0;
				for (i = 1; i <= count; i++){
					if (num + 1 >= OVERLAP_BUFFER)
						break;
					if (strcmp(userInfo[i].userName, key) == 0)
						overlap[++num] = i;
				}
			}
			else printf("\n\n\t\t\t     이름 : %s \n", key);

			if (num == 1) return overlap[num];
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);
			else puts("\n\n\n\t\t\t   존재하지 않는 이름입니다 ! \n\n\n");
			break;
		case 3:
			messageBoxA("연락처로  검색");

			if (action){
				printf("\n\n\t\t\t연락처 : "); fgets(key, ADDRESS_BUFFER, stdin);

				if (*(key + strlen(key) - 1) == '\n')
					*(key + strlen(key) - 1) = '\0';
				else while (getchar() != '\n');

				num = 0;
				for (i = 1; i <= count; i++){
					if (num + 1 >= OVERLAP_BUFFER)
						break;
					if (strcmp(userInfo[i].handphone, key) == 0)
						overlap[++num] = i;
				}
			}
			else printf("\n\n\t\t\t연락처 : %s \n", key);

			if (num == 1) return overlap[num];
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);
			else puts("\n\n\n\t\t\t  존재하지 않는 연락처입니다 ! \n\n\n");
			break;
		}

		bottomMessageA();

		input = getch();

		if (input == ENTER_KEY){
			inSound();
			action = 1;
		}
		else if (input == ESC_KEY){
			outSound();
			return 0;
		}
		else{
			warningMessage(input - '0', 0, 0);
			action = 0;
		}
	}
}

int searchManyPrint(UserInfo userInfo[], int overlap[], int num)
{
	int input;

	resultSound();

	while (1) {
		topMessage("검색", "Search");

		puts("\n\t\t\t      ◎  검색  결과  ◎");
		puts("\t\t\t       ================");

		for (int i = 1; i <= num; i++){
			printf("   %2d.  %d \t %s   \t%s  \t%s\n", i,
				userInfo[overlap[i]].userId, userInfo[overlap[i]].userName,
				userInfo[overlap[i]].handphone, userInfo[overlap[i]].userAddress);
		}

		for (int i = 1; i < OVERLAP_BUFFER - num; i++)
			puts(" ");	//공백 채우기

		if (num + 1 == OVERLAP_BUFFER){
			puts("\n\t\t  검색 결과가 더 있으나 여기까지만 출력됩니다. ");
			puts("\t\t원하시는 결과가 없으면 다른 방법으로 검색해주세요.\n");
		}
		else puts("\n\n\n");

		BOT_COLOR;
		printf("\t\t\t\t\t\t\t\t\t        ");
		printf("\t 선택 :  해당 번호 입력 \t\t     나가기 :  ESC \t\t    ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;

		input = getch();
		input -= '0';	//아스키 값을 받기 때문에

		if (input + '0' == ESC_KEY){
			outSound();
			return 0;
		}
		else if (input > 0 && input <= num){
			inSound();
			return overlap[input];
		}
		else warningMessage(input - '0', 0, 0);
	}
}

void searchResult(UserInfo userInfo[], int num)
{
	int input;

	resultSound();

	while (1){
		topMessage("검색", "Search");
		messageBoxB("검색  ", "결과");

		printf("\n\n\t\t\t회원ID\t: %d \n\n", userInfo[num].userId);
		printf("\t\t\t이름\t: %s \n", userInfo[num].userName);
		printf("\t\t\t연락처\t: %s \n", userInfo[num].handphone);
		printf("\t\t\t주소\t: %s \n", userInfo[num].userAddress);

		puts("\n\n");
		BOT_COLOR;
		printf("\t\t\t\t\t\t\t\t\t        ");
		printf("\t\t\t\t 나가기 :  ESC \t\t\t\t\t   ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;

		input = getch();

		if (input == ESC_KEY){
			outSound();
			return;
		}
		else warningMessage(input - '0', 0, 0);
	}
}


int saveInfo(UserInfo userInfo[], FILE *writeFile)
{
	int input;

	while (1) {
		system("cls");

		TOP_COLOR;
		printf("Save  \t\t\t\t\t\t\t\t\t\t"); printf("\t\t\t\t\t\t\t\t\t        ");
		BOT_COLOR;
		printf("\t\t\t\t\t\t\t\t\t        ");
		printf("\t\t\t        변경 내용 저장\t\t\t\t\t ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;

		puts("\n\n\n\n\n\n\n\n\t\t\t    정말로 저장하시겠습니까? \n\n\n\n\n\n\n");
		bottomMessageB("저장");

		input = getch();

		if (input == ENTER_KEY){
			actionSound();
			writeFile = fopen("data.txt", "wt");	//writeFile open

			fprintf(writeFile, "%s\n", userInfo[0].userAddress);

			for (int i = 1; i <= count; i++)
				fprintf(writeFile, "%d\t%s\t%s\t%s\n",
				userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].handphone);

			fclose(writeFile);		//writeFile close
			return SAVE;
		}

		else if (input == ESC_KEY){
			outSound();
			return 0;
		}
		else warningMessage(input - '0', 0, 0);
	}
}

int closeProgram(void)
{
	int input, menu = 1;

	while (1) {
		system("cls");

		TOP_COLOR;
		printf("Close \t\t\t\t\t\t\t\t\t\t"); printf("\t\t\t\t\t\t\t\t\t        ");
		BOT_COLOR;
		printf("\t\t\t\t\t\t\t\t\t        ");
		printf("\t\t\t         프로그램 종료 \t\t\t\t\t ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;

		printf("\n\n\n\n\t\t\t    "); BOX_COLOR;
		printf("┌──────────┐"); DEF_COLOR;
		printf("\n\t\t\t    "); BOX_COLOR;
		printf("│ 저장하시겠습니까 ? │\n"); DEF_COLOR;
		printf("\t\t\t    "); BOX_COLOR;
		printf("└──────────┘\n"); DEF_COLOR;

		if (menu == 1) puts("\n\n\t\t\t        [ 저장 후 종료 ]");
		else puts("\n\n\t\t\t          저장 후 종료 ");
		if (menu == 2) puts("\n\t\t\t     [ 저장하지 않고 종료 ] \n\n\n\n");
		else puts("\n\t\t\t       저장하지 않고 종료 \n\n\n\n");

		bottomMessageC();

		input = getch();

		if (input == ARROW_BUFFER)
			input = getch();

		switch (input)
		{
		case UP_ARROW_KEY:
			moveSound();
			if (menu > 1) menu--;
			break;
		case DOWN_ARROW_KEY:
			moveSound();
			if (menu < 2) menu++;
			break;
		case ENTER_KEY:
			inSound();
			return menu;
		case ESC_KEY:
			outSound();
			return 0;
		default:
			warningMessage(input - '0', 0, 0);
			break;
		}
	}
}

void closeGift(void)
{
	Beep(SOL, 400);
	Beep(SOL, 100);
	Beep(RA, 400);
	Beep(RA, 100);
	Beep(SOL, 400);
	Beep(SOL, 100);
	Beep(MI, 600);
	Beep(SOL, 360);
	Beep(SOL, 80);
	Beep(MI, 360);
	Beep(MI, 100);
	Beep(RE, 900);

	Beep(SOL, 100);
	Beep(SOL, 100);
	Beep(SOL, 100);
	Beep(RA, 400);
	Beep(RA, 100);
	Beep(SOL, 100);
	Beep(SOL, 100);
	Beep(SOL, 100);
	Beep(MI, 700);
	Sleep(100);

	Beep(SOL, 300);
	Beep(MI, 300);
	Beep(RE, 300);
	Beep(MI, 500);
	Beep(DO, 700);
	Sleep(300);

	Beep(DO, 90);
	Beep(MI, 90);
	Beep(SOL, 90);
	Beep(_DO, 120);
	Sleep(300);
}

void inSound(void)
{
	Beep(MI, DURATION);
	Beep(RA, DURATION);
}
void outSound(void)
{
	Beep(RA, DURATION);
	Beep(MI, DURATION);
}
void actionSound(void)
{
	Beep(DO, DURATION);
	Beep(MI, DURATION);
	Beep(SOL, DURATION);
}
void resultSound(void)
{
	Beep(_DO, DURATION);
	Beep(SOL, DURATION);
	Beep(RA, DURATION);
}
void warningSound(void)
{
	Beep(_DO, DURATION);
}
void moveSound(void)
{
	Beep(MI, DURATION);
}