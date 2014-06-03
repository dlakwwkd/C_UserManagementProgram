/*
	작성자: 141033 박수빈
	최종 작성일: 2014.06.03
	설명: 사용자 입장에서 최대한 간편하게 느낄 수 있도록 디자인 했습니다.

	1. 조작키를 방향키, ENTER키, ESC키로 통일 했습니다.

	2. 회원 등록 시 리스트에 제대로 출력될 수 있는 값 범위 안으로 입력을 제한하였습니다.
		(즉, 너무 길거나 짧은 입력, Tap입력 등은 사전에 방지)


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

	while(!feof(readFile)) {	//초기 회원수 count에 저장
		if (fgetc(readFile) == '\n') count++;
	}

	maxsize = 2 * count;	//초기 회원수의 2배 만큼 메모리 할당
	userInfo = (UserInfo*)malloc(sizeof(UserInfo)*maxsize);

	fseek(readFile, 0, SEEK_SET);		//파일 포인터 처음 위치로 귀환
	setUserInfo(userInfo, readFile);	//구조체 배열에 파일 데이터 저장 및 readFile close

	while(1) {
		printMain(menu);	//메인 화면 출력
	
		input = getch();

		if (input == ARROW_BUFFER)	//방향키는 입력 시 아스키확장 값이 먼저 들어온 후 값이 들어옴
			input = getch();	//그래서 이 경우 버퍼를 한번 비우도록 하였음
		
		switch (input)
		{
		case UP_ARROW_KEY: //상 방향키
			if (menu > 1) menu--;
			break;
		case DOWN_ARROW_KEY: //하 방향키
			if (menu < 6) menu++;
			break;
		case ENTER_KEY: //enter키
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
				count = deleteUser(userInfo, count);
				if (count < maxsize / 3){	//빈 메모리 공간이 많아지면 메모리 할당량 축소
					maxsize /= 2;
					userInfo = (UserInfo*)realloc(userInfo, sizeof(UserInfo)*maxsize);
				}
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
		case ESC_KEY: //esc키
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
	puts("\t메뉴 이동 : ↑↓\t메뉴 선택 : ENTER      \t   종료 : ESC");
	puts("-------------------------------------------------------------------------------");
}

void printList(UserInfo userInfo[], int count)
{
	int input, page, i, k = 1;

	page = 1 + (count - 1) / 17;		//전체 페이지 계산

	while(1) {
		system("cls");

		printf("List   \t\t\t\t\t\t\t\t     page %d/%d\n", k, page);
		puts("\n\t회원ID \t 이름   \t연락처  \t주소");
		puts("-------------------------------------------------------------------------------");
		
		for (i = 1+(k-1)*17; i <= k*17 && i <= count; i++)	//리스트 출력
			printf("\t%d \t %s   \t%s  \t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].handphone, userInfo[i].userAddress);
		
		if (page == k){		//공백 채우기
			for (i = count - (1+(k-1)*17); 16 - i > 0; i++)
				puts(" ");
		}

		puts("-------------------------------------------------------------------------------");
		puts("\t 페이지 이동 :   ←    →     \t\t 나가기 :  ESC");
		puts("-------------------------------------------------------------------------------");
		
		input = getch();

		if (input == ARROW_BUFFER)
			input = getch();
		
		switch (input)
		{
		case LEFT_ARROW_KEY:	//좌측 방향키
			if (k != 1) k--;
			break;
		case RIGHT_ARROW_KEY:	//우측 방향키
			if (k != page) k++;
			break;
		case ESC_KEY:	//esc키
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
	int input, warning, input2;
	int id = userInfo[1].userId;	//초기값 설정

	for (int i = 2; i <= count; i++)	//가장 큰 id값 계산
		id = id > userInfo[i].userId ? id : userInfo[i].userId;

	userInfo[++count].userId = ++id;	//count값 1증가 시키고 새로운 id 부여

	/* 이전에 입력 받고 저장하지 않은 값이 있을 수 있으므로 아래 식의 정상작동을 위해 초기화 */
	userInfo[count].userName[1] = 0;
	userInfo[count].handphone[1] = 0;
	userInfo[count].userAddress[1] = 0;
	
	while(1) {
		system("cls");

		puts("Register \n\n");
		puts("\t\t\t       회원 정보 입력  \n");
		puts("-------------------------------------------------------------------------------");
		
		//ID는 자동으로 부여된 값 출력
		printf("\n\n\t\t 회원ID\t: %d \n\n", userInfo[count].userId);

		//이름 입력
		if (userInfo[count].userName[1] == 0){
			/* 버퍼 오버플로우 방지를 위해 fgets로 받음 */
			printf("\t\t 이름\t: "); fgets(userInfo[count].userName, NAME_PHONE_BUFFER, stdin);
			
			/* '\n'이 입력값 안에 있다면 제거하고, 없다면 초과버퍼가 남았다는 뜻이므로 버퍼 제거 */
			if (*(userInfo[count].userName + strlen(userInfo[count].userName) - 1) == '\n')
				*(userInfo[count].userName + strlen(userInfo[count].userName) - 1) = '\0';
			else while (getchar() != '\n'); 
			
			/* 입력이 이상하면 다시 입력 */
			if (strlen(userInfo[count].userName) < 4 || strlen(userInfo[count].userName) > 8){
				
				//입력된 값 초기화
				for (int i = 0; i < NAME_PHONE_BUFFER; i++)
					userInfo[count].userName[i] = 0;
				
				puts("\n\n\t\t 이름이 너무 길거나 짧습니다.");
				puts("\t\t 이름은 2 ~ 4 글자만 가능합니다. \n\n\t\t [ 영문 4 ~ 8 글자 ]\n\n\n");
				bottomMessage();
				
				input2 = getch();	//

				if (input2 == ESC_KEY) return --count;
				else if (input2 == ARROW_BUFFER)	input2 = getch();
				
				continue;
			}

			/* 탭 입력 발견시 다시 입력 */
			for (int i = 0; userInfo[count].userName[i] != '\0'; i++){
				if (userInfo[count].userName[i] == '\t'){
					
					for (int i = 0; i < NAME_PHONE_BUFFER; i++) 
						userInfo[count].userName[i] = 0;
					
					puts("\n\n\t\t 탭(Tab)은 입력할 수 없습니다!\n\n\n\n\n");
					bottomMessage();
					
					input2 = getch();

					if (input2 == ESC_KEY) return --count;
					else if (input2 == ARROW_BUFFER) input2 = getch();
					
					warning = 1;
					break;
				}
				warning = 0;
			}
			if (warning) continue;	
		}
		/* 입력 완료된 항목은 패스 */
		else printf("\t\t 이름\t: %s \n", userInfo[count].userName);	
		
		//연락처 입력
		if (userInfo[count].handphone[1] == 0){
			printf("\t\t 연락처\t: "); fgets(userInfo[count].handphone, NAME_PHONE_BUFFER, stdin);
			
			if (*(userInfo[count].handphone + strlen(userInfo[count].handphone) - 1) == '\n')
				*(userInfo[count].handphone + strlen(userInfo[count].handphone) - 1) = '\0';
			else while (getchar() != '\n');
			
			if (strlen(userInfo[count].handphone) < 12 || strlen(userInfo[count].handphone) > 13
				|| userInfo[count].handphone[3] != '-' || // 연락처 형식 검사 ('-'을 포함했는지)
				userInfo[count].handphone[7] != '-' && userInfo[count].handphone[8] != '-' ||
				userInfo[count].handphone[7] == '-' && userInfo[count].handphone[8] == '-') {
				
				for (int i = 0; i < NAME_PHONE_BUFFER; i++)
					userInfo[count].handphone[i] = 0;
				
				puts("\n\t\t 연락처 형식에 맞지 않습니다. ");
				puts("\t\t 형식에 맞게 입력해주세요. \n\n\t\t [ 예) 010-1234-5678  or  031-123-4567 ]\n\n\n");
				bottomMessage();
				
				input2 = getch();

				if (input2 == ESC_KEY) return --count;
				else if (input2 == ARROW_BUFFER) input2 = getch();
					
				continue;
			}

			for (int i = 0; userInfo[count].handphone[i] != '\0'; i++){
				if (userInfo[count].handphone[i] == '\t'){
					
					for (int i = 0; i < NAME_PHONE_BUFFER; i++)
						userInfo[count].handphone[i] = 0;
					
					puts("\n\n\t\t 탭(Tab)은 입력할 수 없습니다!\n\n\n\n");
					bottomMessage();
					
					input2 = getch();

					if (input2 == ESC_KEY) return --count;
					else if (input2 == ARROW_BUFFER) input2 = getch();
					
					warning = 1;
					break;
				}

				// '-'이외에는 숫자를 입력했는지 검사
				if ((userInfo[count].handphone[i] < '0' || userInfo[count].handphone[i] > '9') &&
					(userInfo[count].handphone[i] != '-' || (i != 3 && i != 7 && i != 8))){

					for (int i = 0; i < NAME_PHONE_BUFFER; i++)
						userInfo[count].handphone[i] = 0;

					puts("\n\t\t 연락처 형식에 맞지 않습니다.");
					puts("\t\t 형식에 맞게 입력해주세요. \n\n\t\t [ 예) 010-1234-5678  or  031-123-4567 ]\n\n\n");
					bottomMessage();
					
					input2 = getch();

					if (input2 == ESC_KEY) return --count;
					else if (input2 == ARROW_BUFFER) input2 = getch();

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
			printf("\t\t 주소\t: "); fgets(userInfo[count].userAddress, ADDRESS_BUFFER, stdin);
			
			if (*(userInfo[count].userAddress + strlen(userInfo[count].userAddress) - 1) == '\n')
				*(userInfo[count].userAddress + strlen(userInfo[count].userAddress) - 1) = '\0';
			else while (getchar() != '\n');
			
			if (strlen(userInfo[count].userAddress) < 10 || strlen(userInfo[count].userAddress) > 30){
				
				for (int i = 0; i < ADDRESS_BUFFER; i++) 
					userInfo[count].userAddress[i] = 0;
				
				puts("\n\t\t 주소가 너무 길거나 짧습니다. ");
				puts("\t\t 최소 5글자 이상, 그리고 15글자 이내로 입력해주세요.");
				puts("\n\t\t [ 영문 : 10 ~ 30글자 (공백 포함) ]\n\n");
				bottomMessage();
				
				input2 = getch();

				if (input2 == ESC_KEY) return --count;
				else if (input2 == ARROW_BUFFER) input2 = getch();
				
				continue;
			}
			
			for (int i = 0; userInfo[count].userAddress[i] != '\0'; i++){
				if (userInfo[count].userAddress[i] == '\t'){
					
					for (int i = 0; i < ADDRESS_BUFFER; i++)
						userInfo[count].userAddress[i] = 0;
					
					puts("\n\n\t\t 탭(Tab)은 입력할 수 없습니다!\n\n\n");
					bottomMessage();
					
					input2 = getch();

					if (input2 == ESC_KEY) return --count;
					else if (input2 == ARROW_BUFFER) input2 = getch();
					
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
		puts("\t\t 등록 :  ENTER     \t\t 취소 :  ESC");
		puts("-------------------------------------------------------------------------------");
		
		input = getch();

		if (input == ENTER_KEY) return count;		//등록하면 증가한 count 반환
		else if (input == ESC_KEY) return --count;	//등록하지 않으면 count가 증가하지 않으므로 무효
		else printf("잘못된 입력입니다.");
	}
}

void saveInfo(UserInfo userInfo[], FILE *writeFile, int count)
{
	int input;

	while(1) {
		system("cls");

		puts("Save \n\n");
		puts("\t\t\t\t변경 내용 저장  \n");
		puts("-------------------------------------------------------------------------------");
		puts("\n\n\n\n\n\t\t\t   정말로 저장하시겠습니까? \n\n\n\n\n");
		puts("-------------------------------------------------------------------------------");
		puts("\t\t 저장 :  ENTER     \t\t 취소 :  ESC");
		puts("-------------------------------------------------------------------------------");
		
		input = getch();

		if (input == ENTER_KEY){
			writeFile = fopen("data.txt", "wt");	//writeFile open
			
			fprintf(writeFile, "%s\n", userInfo[0].userAddress);
			
			for (int i = 1; i <= count; i++)
				fprintf(writeFile, "%d\t%s\t%s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].handphone);
			
			fclose(writeFile);		//writeFile close
			return;
		}

		else if (input == ESC_KEY) return;
		else printf("잘못된 입력입니다.");
	}
}

int deleteUser(UserInfo userInfo[], int count)
{
	int input, menu = 1, del;

	while(1) {
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
		puts("\t메뉴 이동 : ↑↓\t메뉴 선택 : ENTER      \t 나가기 : ESC");
		puts("-------------------------------------------------------------------------------");

		input = getch();

		if (input == ARROW_BUFFER)
			input = getch();

		switch (input)
		{
		case UP_ARROW_KEY:
			if (menu > 1) menu--;
			break;
		case DOWN_ARROW_KEY:
			if (menu < 3) menu++;
			break;
		case ENTER_KEY:
			del = searchUser(userInfo, count, menu);

			while (del){
				system("cls");

				puts("Delete \n\n");
				puts("\t\t\t        회원 정보 삭제 \n");
				puts("-------------------------------------------------------------------------------");
				
				printf("\n\n\n\t\t\t회원ID\t: %d \n\n", userInfo[del].userId);
				printf("\t\t\t이름\t: %s \n", userInfo[del].userName);
				printf("\t\t\t연락처\t: %s \n", userInfo[del].handphone);
				printf("\t\t\t주소\t: %s \n", userInfo[del].userAddress);
				
				puts("\n\n\n\t\t\t   정말로 삭제하시겠습니까? \n\n\n");
				puts("-------------------------------------------------------------------------------");
				puts("\t\t 삭제 :  ENTER     \t\t 취소 :  ESC");
				puts("-------------------------------------------------------------------------------");
				
				input = getch();

				if (input == ENTER_KEY){
					/* 삭제 대상이 맨 마지막에 있다면, count를 하나 줄이는 것으로 끝 */
					if (del == count){
						deleteMessage();
						count--;
						break;
					}
					/* 나머지 경우는 한 칸씩 앞으로 덮어씌움 */
					else{	
						for (int i = del + 1; i <= count; i++){
							userInfo[i - 1].userId = userInfo[i].userId;
							strcpy(userInfo[i - 1].userName, userInfo[i].userName);
							strcpy(userInfo[i - 1].userAddress, userInfo[i].userAddress);
							strcpy(userInfo[i - 1].handphone, userInfo[i].handphone);
						}
						deleteMessage();
						count--;
						break;
					}
				}
				else if (input == ESC_KEY) break;
				else printf("잘못된 입력입니다.");
			}
			break;
		case ESC_KEY:
			return count;
		default:
			printf("잘못된 입력입니다.");
			break;
		}
	}
}
int searchUser(UserInfo userInfo[], int count, int menu)
{
	int id, i, input, action = 1, num;
	char key[NAME_PHONE_BUFFER];
	int overlap[OVERLAP_BUFFER];

	while(1) {
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
				printf("\n\t\t\t  ID : "); fgets(key, NAME_PHONE_BUFFER, stdin);
				
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
			else printf("\n\t\t\t  ID : %d \n", id);
			
			/* 검색 결과가 1명일 때 */
			if (num == 1) return overlap[num];

			/* 검색 결과가 2명 이상일 때 */
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);

			/* 검색 결과가 없을 때 */
			else puts("\n\n\n\t\t\t   존재하지 않는 ID입니다! \n\n\n");
			
			break;
		case 2:
			puts("\n\n\t\t\t    ◎  이름으로 검색  ◎");
			puts("\t\t\t      ------------------");
			
			if (action){
				printf("\n\t\t\t  이름 : "); fgets(key, NAME_PHONE_BUFFER, stdin);
				
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
			else printf("\n\t\t\t  이름 : %s \n", key);
			
			if (num == 1) return overlap[num];
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);
			else puts("\n\n\n\t\t\t   존재하지 않는 이름입니다! \n\n\n");
			
			break;
		case 3:
			puts("\n\n\t\t\t    ◎  연락처로 검색  ◎");
			puts("\t\t\t      ------------------");
			
			if (action){
				printf("\n\t\t\t  연락처 : "); fgets(key, ADDRESS_BUFFER, stdin);
				
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
			else printf("\n\t\t\t  연락처 : %s \n", key);
			
			if (num == 1) return overlap[num];
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);
			else puts("\n\n\n\t\t\t   존재하지 않는 연락처입니다! \n\n\n");
			
			break;
		}

		bottomMessage();
		
		input = getch();
		
		if (input == ENTER_KEY) action = 1;
		else if (input == ESC_KEY) return 0;
		else{
			puts("잘못된 입력입니다.");
			action = 0;
		}
	}
}

void bottomMessage(void)
{
	puts("-------------------------------------------------------------------------------");
	puts("\t\t다시 입력 :  ENTER   \t\t나가기 :  ESC");
	puts("-------------------------------------------------------------------------------");
}

void deleteMessage(void)
{
	system("cls");

	puts("Delete \n\n");
	puts("\t\t\t        회원 정보 삭제 \n");
	puts("-------------------------------------------------------------------------------");
	puts("\n\n\n\n\n\t\t\t       ================");
	puts("\t\t\t      ◎  삭제  완료  ◎");
	puts("\t\t\t       ================ \n\n\n\n\n");
	puts("-------------------------------------------------------------------------------");
	puts("\t\t\t 계속하려면 아무 키나 누르세요 ");
	puts("-------------------------------------------------------------------------------");

	getch();	//메시지 출력을 위해 정지
}

int searchManyPrint(UserInfo userInfo[], int overlap[], int num)
{
	int input;
	
	while (1) {
		system("cls");

		puts("Search \n");
		puts("\t\t\t        회원 정보 검색 \n");
		puts("-------------------------------------------------------------------------------\n");
		puts("\t\t\t      ◎  검색 결과  ◎ \n");

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

		puts("-------------------------------------------------------------------------------");
		puts("\t 선택 :  해당 번호 입력 \t\t     나가기 :  ESC");
		puts("-------------------------------------------------------------------------------");
		
		input = getch();
		input -= '0';	//아스키 값을 받기 때문에

		if (input + '0' == ESC_KEY) return 0;
		else if (input > 0 && input <= num) return overlap[input];
		else printf("잘못된 입력입니다.");
	}
}

//void modifyUser