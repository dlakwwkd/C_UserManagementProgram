/*
	�ۼ���: 141033 �ڼ���
	���� �ۼ���: 2014.06.07
	����: ����� ���忡�� �ִ��� �����ϰ� ���� �� �ֵ��� ������ �߽��ϴ�.
	      �׸��� � ��Ȳ������ ������ ������ �ʴ� �������� �߱��߽��ϴ�.

	1. ����Ű�� ����Ű, ENTERŰ, ESCŰ�� ���� �߽��ϴ�.

	2. ȸ�� ��Ͻ� ����Ʈ�� ����� ��µ� �� �ִ� �� ���� ������ �Է��� �����Ͽ����ϴ�.
		(��, �ʹ� ��ų� ª�� �Է�, Tap�Է� ���� ������ ����)

	3. �ߺ��Ǵ� �ڵ带 �ִ��� ������ �ʾҰ�, ��� ���� ���ȭ �Ͽ����ϴ�.

	4. ������ ��� ���ܻ�Ȳ�� �׽�Ʈ �غ��� �ֽ��ϴ�.

	=== ���� ���� (2014.06.07) ===

	* dataInput �Լ� 3���� �Լ��� �и�(dataInputA, dataInputB, dataInputWarning)
	* �ߺ��Ǵ� UI �и� (topMessage, bottomMessageA, bottomMessageB)
	* �ּ� �߰�
	* ���� �߰�

	=== ���� ���� (2014.06.06) ===

	* ȸ�� ��� �� �ּ� �Է� �� �߻��� �� �ִ� ���� ����
	* ȸ�� ���� �� �� �Է� �� �߻��� �� �ִ� ���� ����
	* ������ ���� �ε� �� ���� �ִ� ��� �߻��ϴ� ���� ����
	* maxsize, count ���������� �����ϰ�, �������� �Լ� ����ȭ
	* �Լ� ��ġ ��ɺ� ������ �°� ���ġ
	* ������� UI ���� (�÷� ����)
	* ���Ͽ� ������ ���� ��� ����� ���� ����
	* �߰����� UI ����
	
	=== ���� ���� (2014.06.05) ===

	* ȸ�� ��Ͻ� �Ź� maxid�� ����ϴ� ���� ó�� �ѹ��� �ϵ��� ����
	* ���, ����, ���� �ÿ� ��ø�Ǵ� �Է� �ڵ带 �Լ��� �и��ؼ� ����ȭ
	* ���������� �ߺ��Ǵ� �˻� �ڵ带 �Լ��� �и�
	* ���� ������ define ����
	* �˻�, ���� ��� �ϼ�
	* ���������� ����� �Ͽ� �߰ߵ� ���� ��� ����

	=== ���� ���� (2014.06.03) ===

	* �Է�Ű �� define���� ���� (ENTER, ESC ��)
	* �ڵ� ���� (�� ����, �鿩���� ��)
	* ȸ�� ��� �ߵ� ��� ��� ���� ('esc' Ÿ���� -> ESCŰ ������ ������)
	* �ߺ��Ǵ� �޽��� ��� �ڵ� �Լ��� ����� ����
	* �˻� �� �ߺ��Ǵ� �� ���͸� ��� �߰�
	* ȸ�� ��� ��� UI ����

	=== ���� ���� (2014.06.03)(����) ===

	* ȸ�� ��� ��� UI ����
	* ȸ�� ��Ͻ� �̸� 3���� ���ѿ��� 4���� �������� Ȯ��
	* ȸ�� ��Ͻ� �ּ� 10 ~ 15���� ���� 5 ~ 15���ڷ� ���� Ȯ��
	* ���� ��� �ϼ�
	* ���� �����÷ο� ������ ���� �Լ� ��ü (gets -> fgets)
	* fgets�� '\n'�� �����ع����Ƿ� �̸� �����ϴ� ���� �߰�

	=== ���� ���� (2014.06.02) ===

	* ���� ȭ�� �������̽� ���� ( ���� �Է¿��� ȭ��ǥ �Է����� )
	* ����ó �Է½� ���Ŀ� ��Ȯ�� �¾ƾ� �Է� �ǵ��� �Է� ���� ��� ��ȭ 
	* �˻� ���, ���� ���(���� �̿�) �߰�
	* ��� �ּ� ����

*/
#include "UserManagement.h"

static int maxid;		//���� ū ID ��
static int maxsize;		//�޸� �Ҵ� ������
static int count = -1;	//��ü ȸ�� ��

int main(void)
{
	system("mode con lines=25 cols=80");	//�ܼ� â ũ�� �ʱ�ȭ
	UserInfo *userInfo = NULL;
	FILE *readFile = NULL;
	FILE *writeFile = NULL;
	int input = 1, menu = 1, choice, clear = 1;

	userInfo = setUserInfo(userInfo, readFile);	//����ü �迭�� ���� ������ ����
	if (userInfo == (UserInfo*)-1) return 0;		//���� ���� ��� �ٷ� ����

	while(1) {
		printMain(menu);	//���� ȭ�� ���
		
		
		if (clear) clear--;	//�ʱ� ȭ�� ����
		else input = getch();
		
		if (input == ARROW_BUFFER)	//����Ű�� �Է� �� �ƽ�ŰȮ�� ���� ���� ���� �� ���� ����
			input = getch();		//�׷��� �� ��� ���۸� �ѹ� ��쵵�� �Ͽ���
		
		switch (input)
		{
		case UP_ARROW_KEY:		//�� ����Ű
			if (menu > 1) menu--;
			Beep(MI, DURATION);
			break;
		case DOWN_ARROW_KEY:	//�� ����Ű
			if (menu < 6) menu++;
			Beep(MI, DURATION);
			break;
		case ENTER_KEY:			//enterŰ
			Beep(DO, DURATION);
			Beep(RA, DURATION);
			switch (menu)
			{
			case 1:	//���
				printList(userInfo);
				break;
			case 2:	//���
				addUser(userInfo);
				break;
			case 3:	//����
				searchMain(userInfo, _DELETE, "����", "Delete");
				break;
			case 4:	//����
				searchMain(userInfo, MODIFY, "����", "Modify");
				break;
			case 5:	//�˻�
				searchMain(userInfo, SEARCH, "�˻�", "Search");
				break;
			case 6:	//����
				saveInfo(userInfo, writeFile);
				break;
			} //switch(menu) out
			break;
		case ESC_KEY:			//escŰ
			Beep(DO, DURATION);
			Beep(RA, DURATION);
			choice = closeProgram();

			if (choice == SAVE)
				choice = saveInfo(userInfo, writeFile);

			if (choice == SAVE || choice == EXIT){
				printf("���α׷��� �����մϴ�.\t");
				free(userInfo);
				closeGift();
				return 0;
			}
			else break;
		default:
			WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
			Beep(_DO, DURATION);
			break;
		} //switch(input) out
	}

	free(userInfo);
	return 0;
}


UserInfo* setUserInfo(UserInfo userInfo[], FILE *readFile)
{
	readFile = fopen("data.txt", "rt");
	if (readFile == NULL){
		puts("\n\n\n\n\n\n\n\n\n\n\n\t\t\t �����Ͱ� �������� �ʽ��ϴ�! \n\n\n\n\n\n\n\n\n\n\n");
		return (UserInfo*)-1;
	}

	while (!feof(readFile)) {	//�ʱ� ȸ���� count�� ����
		if (fgetc(readFile) == '\n') count++;
	}

	if (count < 1){
		puts("\n\n\n\n\n\n\n\n\n\n\n\t\t\t �����Ͱ� �������� �ʽ��ϴ�! \n\n\n\n\n\n\n\n\n\n\n");
		return (UserInfo*)-1;
	}

	maxsize = 2 * count;	//�ʱ� ȸ������ 2�� ��ŭ �޸� �Ҵ�
	userInfo = (UserInfo*)malloc(sizeof(UserInfo)*maxsize);

	fseek(readFile, 0, SEEK_SET);		//���� ������ ó�� ��ġ�� ��ȯ
	fscanf(readFile, "%[^\n]", userInfo[0].userAddress);	//ù ������ ���� ����

	for (int i = 1; !feof(readFile); i++)
		fscanf(readFile, "%d\t%[^\t]\t%[^\t]\t%[^\n]\n", &userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].handphone);

	fclose(readFile);

	maxid = userInfo[1].userId;			//�ʱⰪ ����
	for (int i = 2; i <= count; i++)	//���� ū id�� ���
		maxid = maxid > userInfo[i].userId ? maxid : userInfo[i].userId;

	return userInfo;
}


void printMain(int menu)
{
	system("cls");

	TOP_COLOR;
	printf("Main \t\t\t\t\t\t\t\t\t        "); printf("\t\t\t\t\t\t\t\t\t        ");
	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("\t\t\t      ȸ�� ���� ���α׷�\t\t\t        ");
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;

	if (menu == 1) puts("\n\n\n\t\t\t      [ ȸ�� ��� ��� ]");
	else puts("\n\n\n\t\t\t        ȸ�� ��� ��� ");
	if (menu == 2) puts("\n\t\t\t      [ �ű� ȸ�� ��� ]");
	else puts("\n\t\t\t        �ű� ȸ�� ��� ");
	if (menu == 3) puts("\n\t\t\t      [ ���� ȸ�� ���� ]");
	else puts("\n\t\t\t        ���� ȸ�� ���� ");
	if (menu == 4) puts("\n\t\t\t      [ ȸ�� ���� ���� ]");
	else puts("\n\t\t\t        ȸ�� ���� ���� ");
	if (menu == 5) puts("\n\t\t\t      [ ���� ȸ�� �˻� ]");
	else puts("\n\t\t\t        ���� ȸ�� �˻� ");
	if (menu == 6) puts("\n\t\t\t      [ ���� ���� ���� ]\n\n");
	else puts("\n\t\t\t        ���� ���� ���� \n\n");

	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("\t�޴� �̵� : ���\t�޴� ���� : ENTER      \t   ���� : ESC \t        ");
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;
}

void printList(UserInfo userInfo[])
{
	int input, page, i, k = 1;

	page = 1 + (count - 1) / 18;		//��ü ������ ���

	while(1) {
		system("cls");

		TOP_COLOR;
		printf("List   \t\t\t\t\t\t\t\t     page %d/%d   ", k, page); printf("\t\t\t\t\t\t\t\t\t        ");
		BOT_COLOR;
		printf("\tȸ��ID \t �̸�   \t����ó  \t�ּ� \t\t\t\t");
		DEF_COLOR;
		printf("\t\t\t\t\t\t\t\t\t        ");
		
		for (i = 1+(k-1)*18; i <= k*18 && i <= count; i++)	//����Ʈ ���
			printf("\t%d \t %s   \t%s  \t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].handphone, userInfo[i].userAddress);
		
		if (page == k){		//���� ä���
			for (i = count - (1+(k-1)*18); 17 - i > 0; i++)
				puts(" ");
		}

		BOT_COLOR;
		printf("\n\t ������ �̵� :   ��    ��  \t\t\t ������ :  ESC \t\t");
		DEF_COLOR;

		input = getch();

		if (input == ARROW_BUFFER)
			input = getch();
		
		switch (input)
		{
		case LEFT_ARROW_KEY:	//���� ����Ű
			Beep(MI, DURATION);
			if (k != 1) k--;
			break;
		case RIGHT_ARROW_KEY:	//���� ����Ű
			Beep(MI, DURATION);
			if (k != page) k++;
			break;
		case ESC_KEY:	//escŰ
			Beep(RA, DURATION);
			Beep(DO, DURATION);
			return;
		default:
			WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
			Beep(_DO, DURATION);
			break;
		}
	}
}


void topMessage(char mess[], char top[])
{
	system("cls");

	TOP_COLOR;
	printf("%s \t\t\t\t\t\t\t\t\t\t ", top); printf("\t\t\t\t\t\t\t\t\t        ");
	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("\t\t\t        ȸ�� ���� %s\t\t\t\t\t ", mess);
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;
}

void bottomMessageA(void)
{
	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("\t\t�ٽ� �Է� :  ENTER   \t\t������ :  ESC  \t\t\t  ");
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;
}

void bottomMessageB(char mess[])
{
	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("\t\t %s :  ENTER     \t\t ��� :  ESC \t\t\t   ", mess);
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;
}

void deleteMessage(char mess[], char top[])
{
	topMessage(mess, top);

	printf("\n\n\n\n\n\n\t\t\t    "); BOX_COLOR;
	printf(" ==================== "); DEF_COLOR;
	printf("\n\t\t\t    "); BOX_COLOR;
	printf(" \t\t\t  "); DEF_COLOR;
	printf("\n\t\t\t    "); BOX_COLOR;
	printf("      %s  �Ϸ�      \n", mess); DEF_COLOR;
	printf("\t\t\t    "); BOX_COLOR;
	printf(" \t\t\t  "); DEF_COLOR;
	printf("\n\t\t\t    "); BOX_COLOR;
	printf(" ==================== \n\n\n\n\n\n"); DEF_COLOR;
	Beep(_DO, DURATION);
	Beep(SOL, DURATION);
	Beep(RA, DURATION);

	BOT_COLOR;
	printf("\t\t\t\t\t\t\t\t\t        ");
	printf("\t\t\t ����Ϸ��� �ƹ� Ű�� �������� \t\t\t\t ");
	printf("\t\t\t\t\t\t\t\t\t        ");
	DEF_COLOR;

	getch();	//�޽��� ����� ���� ����
}


void addUser(UserInfo userInfo[])
{
	userInfo[++count].userId = ++maxid;	//count�� 1���� ��Ű�� ���ο� id �ο�
	
	if (count > maxsize - 5){	//�޸� �Ҵ緮 �Ѱ�ġ�� ��������� �߰��Ҵ�
		maxsize *= 2;
		userInfo = (UserInfo*)realloc(userInfo, sizeof(UserInfo)*maxsize);
	}

	dataInputA(userInfo);
}

void deleteUser(UserInfo userInfo[], int del)
{
	int input, menu = 1;

	while (del){
		topMessage("����", "Delete");

		printf("\n\n\n\n\t\t\tȸ��ID\t: %d \n\n", userInfo[del].userId);
		printf("\t\t\t�̸�\t: %s \n", userInfo[del].userName);
		printf("\t\t\t����ó\t: %s \n", userInfo[del].handphone);
		printf("\t\t\t�ּ�\t: %s \n", userInfo[del].userAddress);

		puts("\n\n\n\t\t\t   ������ �����Ͻðڽ��ϱ�? \n\n\n");
		BOT_COLOR;
		printf("\t\t\t\t\t\t\t\t\t        ");
		printf("\t\t ���� :  ENTER     \t\t ��� :  ESC  \t\t\t  ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;

		input = getch();

		if (input == ENTER_KEY){
			Beep(DO, DURATION);
			Beep(RA, DURATION);
			/* �� �޸� ������ �������� �޸� �Ҵ緮 ��� */
			if (count < maxsize / 3){
				maxsize /= 2;
				userInfo = (UserInfo*)realloc(userInfo, sizeof(UserInfo)*maxsize);
			}
			/* ���� ����� �� �������� �ִٸ�, count�� �ϳ� ���̴� ������ �� */
			if (del == count){
				deleteMessage("����", "Delete");
				count--;
				return;
			}
			/* ������ ���� �� ĭ�� ������ ����� */
			else{
				for (int i = del + 1; i <= count; i++){
					userInfo[i - 1].userId = userInfo[i].userId;
					strcpy(userInfo[i - 1].userName, userInfo[i].userName);
					strcpy(userInfo[i - 1].userAddress, userInfo[i].userAddress);
					strcpy(userInfo[i - 1].handphone, userInfo[i].handphone);
				}
				deleteMessage("����", "Delete");
				count--;
				return;
			}
		}
		else if (input == ESC_KEY){
			Beep(RA, DURATION);
			Beep(DO, DURATION);
			return;
		}
		else{
			WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
			Beep(_DO, DURATION);
		}
	}
	return;
}

void modifyUser(UserInfo userInfo[], int fix)
{
	int input, menu = 1, action, action2;
	char temp[ADDRESS_BUFFER];
	char *ptr;
	ptr = temp;
	action = 1;


	while (action){
		topMessage("����", "Modify");

		puts("\n\n\n\t\t\t      ��  ������ ����  ��");
		puts("\t\t\t       ================\n");

		if (menu == NAME) puts("\n\t\t\t\t   [ �̸� ]");
		else puts("\n\t\t\t\t     �̸� ");
		if (menu == ADDRESS) puts("\n\t\t\t\t   [ �ּ� ]");
		else puts("\n\t\t\t\t     �ּ� ");
		if (menu == PHONE) puts("\n\t\t\t\t  [ ����ó ]\n\n\n\n");
		else puts("\n\t\t\t\t    ����ó \n\n\n\n");

		BOT_COLOR;
		printf("\t\t\t\t\t\t\t\t\t        ");
		printf("\t�޴� �̵� : ���\t�޴� ���� : ENTER      \t ������ : ESC \t        ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;

		input = getch();

		if (input == ARROW_BUFFER)
			input = getch();

		switch (input)
		{
		case UP_ARROW_KEY:
			Beep(MI, DURATION);
			if (menu > 1) menu--;
			break;
		case DOWN_ARROW_KEY:
			Beep(MI, DURATION);
			if (menu < 3) menu++;
			break;
		case ENTER_KEY:
			Beep(DO, DURATION);
			Beep(RA, DURATION);
			switch (menu){
			case NAME:
				action2 = dataInputB(userInfo, NAME, ptr, fix, "�̸�", 4, 8);

				if (action2){
					strcpy(userInfo[fix].userName, temp);
					deleteMessage("����", "Modify");
				}
				break;
			case ADDRESS:
				action2 = dataInputB(userInfo, ADDRESS, ptr, fix, "�ּ�", 10, 30);

				if (action2){
					strcpy(userInfo[fix].userAddress, temp);
					deleteMessage("����", "Modify");
				}
				break;
			case PHONE:
				action2 = dataInputB(userInfo, PHONE, ptr, fix, "����ó", 12, 13);

				if (action2){
					strcpy(userInfo[fix].handphone, temp);
					deleteMessage("����", "Modify");
				}
				break;
			}
			break;
		case ESC_KEY:
			action = 0;
			Beep(RA, DURATION);
			Beep(DO, DURATION);
			break;
		default:
			WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
			Beep(_DO, DURATION);
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
		topMessage("�Է�", "Regist");

		printf("\n\n\n\n\t\t\t ȸ��ID\t: %d \n\n", userInfo[count].userId);

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
			printf("\t\t\t �̸�\t: ");
			switC = NAME;
			warning = dataInputAction(warning, NAME, ptrC, userInfo[count].userName, 4, 8);
			if (!warning) switD = 2;
		}
		else if (switD >= 1) printf("\t\t\t �̸�\t: %s \n", userInfo[count].userName);

		if (switD == 2 && action){
			printf("\t\t\t ����ó\t: ");
			switC = PHONE;
			warning = dataInputAction(warning, PHONE, ptrC, userInfo[count].handphone, 12, 13);
			if (!warning) switD = 3;
		}
		else if (switD >= 2) printf("\t\t\t ����ó\t: %s \n", userInfo[count].handphone);

		if (switD == 3 && action){
			printf("\t\t\t �ּ�\t: ");
			switC = ADDRESS;
			warning = dataInputAction(warning, ADDRESS, ptrC, userInfo[count].userAddress, 10, 30);
			if (!warning) switD = 4;
		}
		else if (switD >= 3) printf("\t\t\t �ּ�\t: %s \n", userInfo[count].userAddress);


		if (warning){
			dataInputWarning((char*)0, INSERT, 0, switC);

			input = getch();

			if (input == ESC_KEY){
				maxid--;	 count--;	//������� ������ count ������� �ǵ��� ���� ����
				Beep(RA, DURATION);
				Beep(DO, DURATION);
				return;
			}
			else if (input == ENTER_KEY){
				action = 1;
				Beep(RA, DURATION);
				Beep(DO, DURATION);
			}
			else{
				action = 0;
				WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
				Beep(_DO, DURATION);
			}
		}
		else{
			puts("\n\n\n\t\t\t   ������ ����Ͻðڽ��ϱ�? \n\n\n");

			bottomMessageB("���");

			input = getch();

			if (input == ESC_KEY){
				maxid--; count--;
				Beep(RA, DURATION);
				Beep(DO, DURATION);
				return;
			}
			else if (input == ENTER_KEY){
				Beep(DO, DURATION);
				Beep(RA, DURATION);
				return;	//����ϸ� count ������ ä�� ����
			}
				
			else{
				action = 0;
				WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
				Beep(_DO, DURATION);
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
		topMessage("����", "Modify");

		printf("\n\n\n\t\t\t      ��  %s  ����  ��\n", str);
		puts("\t\t\t       ================");
		switch (switB){
		case NAME:
			printf("\n\t\t   ���� %s : %s \n", str, userInfo[fix].userName);
			break;
		case ADDRESS:
			printf("\n\t\t   ���� %s : %s \n", str, userInfo[fix].userAddress);
			break;
		case PHONE:
			printf("\n\t\t   ���� %s : %s \n", str, userInfo[fix].handphone);
			break;
		}

		printf("\t\t ���ο� %s : ", str);
		if (action){
			switC = switB;
			warning = dataInputAction(warning, switB, ptrC, temp, min, max);
		}
		else printf("%s \n", temp);
		
		if(warning){
			dataInputWarning(temp, UPDATE, switB, switC);

			input = getch();

			if (input == ESC_KEY){
				Beep(RA, DURATION);
				Beep(DO, DURATION);
				return 0;	//��ҽ� 0�� ���� 
			}
			else if (input == ENTER_KEY){
				Beep(DO, DURATION);
				Beep(RA, DURATION);
				action = 1;
			}
			else{
				action = 0;
				WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
				Beep(_DO, DURATION);
			}
		}
		else{
			puts("\n\n\n\t\t\t   ������ �����Ͻðڽ��ϱ�? \n\n\n\n");

			bottomMessageB("����");

			input = getch();

			if (input == ENTER_KEY){
				Beep(DO, DURATION);
				Beep(RA, DURATION);
				return 1;	//�����ϸ� 1��ȯ
			}
			else if (input == ESC_KEY){
				Beep(RA, DURATION);
				Beep(DO, DURATION);
				return 0;
			}
			else{
				action = 0;
				WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
				Beep(_DO, DURATION);
			}
		}
	}
}

int dataInputAction(int warning, int switB, int *ptrC, char *temp, int min, int max)
{
	int sizeTemp;
	
	if (switB == ADDRESS) fgets(temp, ADDRESS_BUFFER, stdin);
	else fgets(temp, NAME_PHONE_BUFFER, stdin);

	if (*(temp + strlen(temp) - 1) == '\n')
		*(temp + strlen(temp) - 1) = '\0';
	else while (getchar() != '\n');

	sizeTemp = strlen(temp);	//strlen�� unsigned int ������ ��ȯ�ϱ� ����

	if (sizeTemp < min || sizeTemp > max)
		warning = 1;
	else
		warning = 0;

	if (!warning){	// !warning�� �ǹ̴� ���� �˻縦 ����ߴٴ� �ǹ�
		for (int i = 0; temp[i] != '\0'; i++){
			/* �� �Է� �߽߰� �ٽ� �Է� */
			if (temp[i] == '\t'){
				*ptrC = TAB;
				warning = 1;
				break;
			}
			/* '-'�̿ܿ��� ���ڸ� �Է��ߴ��� �˻� */
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
		/* '-'�� ��ġ�� �������� �˻� */
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
		if (switA == UPDATE){
			for (int i = 0; i < NAME_PHONE_BUFFER; i++)
				temp[i] = 0;
		}
		else puts(" ");
		puts("\n\n\n\t\t\t �̸��� �ʹ� ��ų� ª���ϴ�.");
		puts("\t\t\t �̸��� 2 ~ 4 ���ڸ� �����մϴ�. \n\t\t\t [ ���� 4 ~ 8 ���� ]\n\n");
		break;
	case ADDRESS:
		if (switA == UPDATE){
			for (int i = 0; i < ADDRESS_BUFFER; i++)
				temp[i] = 0;
			puts(" ");
		}
		puts("\n\t\t  �ּҰ� �ʹ� ��ų� ª���ϴ�. ");
		puts("\t\t  �ּ� 5���� �̻�, �׸��� 15���� �̳��� �Է����ּ���.");
		puts("\n\t\t  [ ���� : 10 ~ 30���� (���� ����) ]\n\n");
		break;
	case PHONE:
		if (switA == UPDATE){
			for (int i = 0; i < NAME_PHONE_BUFFER; i++)
				temp[i] = 0;
		}
		puts("\n\n\t\t\t ����ó ���Ŀ� ���� �ʽ��ϴ�. ");
		puts("\t\t\t ���Ŀ� �°� �Է����ּ���. \n\n\t\t     [ ��) 010-1234-5678  or  031-123-4567 ]\n\n");
		break;
	case TAB:
		if (switA == UPDATE){
			if (switB == ADDRESS){
				for (int i = 0; i < ADDRESS_BUFFER; i++)
					temp[i] = 0;
			}
			else{
				for (int i = 0; i < NAME_PHONE_BUFFER; i++)
					temp[i] = 0;
			}
		}
		puts("\n\n\n\t\t\t ��(Tab)�� �Է��� �� �����ϴ�!\n\n\n");
		break;
	}
	bottomMessageA();
}


void searchMain(UserInfo userInfo[], int todo, char mess[], char top[])
{
	int input, menu = 1, num;

	while (1) {
		topMessage(mess, top);

		puts("\n\n\n\t\t\t      ��  �˻�  ���  ��");
		puts("\t\t\t       ================\n");

		if (menu == 1) puts("\n\t\t\t      [ ȸ��ID��  �˻� ]");
		else puts("\n\t\t\t        ȸ��ID��  �˻� ");
		if (menu == 2) puts("\n\t\t\t      [ �̸�����  �˻� ]");
		else puts("\n\t\t\t        �̸�����  �˻� ");
		if (menu == 3) puts("\n\t\t\t      [ ����ó��  �˻� ]\n\n\n\n");
		else puts("\n\t\t\t        ����ó��  �˻� \n\n\n\n");

		BOT_COLOR;
		printf("\t\t\t\t\t\t\t\t\t        ");
		printf("\t�޴� �̵� : ���\t�޴� ���� : ENTER      \t ������ : ESC \t        ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;


		input = getch();

		if (input == ARROW_BUFFER)
			input = getch();

		switch (input)
		{
		case UP_ARROW_KEY:
			Beep(MI, DURATION);
			if (menu > 1) menu--;
			break;
		case DOWN_ARROW_KEY:
			Beep(MI, DURATION);
			if (menu < 3) menu++;
			break;
		case ENTER_KEY:
			Beep(DO, DURATION);
			Beep(RA, DURATION);
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
			Beep(RA, DURATION);
			Beep(DO, DURATION);
			return;
		default:
			WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
			Beep(_DO, DURATION);
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
		topMessage("�˻�", "Search");

		switch (menu)
		{
		case 1:
			puts("\n\n\n\t\t\t     ��  ȸ��ID�� �˻�  ��");
			puts("\t\t\t       =================\n");

			if (action){
				printf("\n\t\t\t\t ID : "); fgets(key, NAME_PHONE_BUFFER, stdin);

				if (*(key + strlen(key) - 1) == '\n')
					*(key + strlen(key) - 1) = '\0';
				else while (getchar() != '\n');

				id = atoi(key);	//scanf�� ���Ͱ��� �����ϱ� ������ fgets�� �ް� ������ ��ȯ�Ͽ���

				num = 0;
				for (i = 1; i <= count; i++){	//�˻�
					if (num + 1 >= OVERLAP_BUFFER)
						break;	//�˻� ����� �ʹ� ������ ���� �Ѱ�ġ���� ����
					if (userInfo[i].userId == id)
						overlap[++num] = i;
				}
			}
			else printf("\n\t\t\t\t ID : %d \n", id);

			/* �˻� ����� 1���� �� */
			if (num == 1) return overlap[num];

			/* �˻� ����� 2�� �̻��� �� */
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);

			/* �˻� ����� ���� �� */
			else puts("\n\n\n\t\t\t    �������� �ʴ� ID�Դϴ� ! \n\n\n\n");
			break;
		case 2:
			puts("\n\n\n\t\t\t     ��  �̸����� �˻�  ��");
			puts("\t\t\t       =================\n");

			if (action){
				printf("\n\t\t\t     �̸� : "); fgets(key, NAME_PHONE_BUFFER, stdin);

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
			else printf("\n\t\t\t     �̸� : %s \n", key);

			if (num == 1) return overlap[num];
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);
			else puts("\n\n\n\t\t\t   �������� �ʴ� �̸��Դϴ� ! \n\n\n\n");
			break;
		case 3:
			puts("\n\n\n\t\t\t     ��  ����ó�� �˻�  ��");
			puts("\t\t\t       =================\n");

			if (action){
				printf("\n\t\t\t����ó : "); fgets(key, ADDRESS_BUFFER, stdin);

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
			else printf("\n\t\t\t����ó : %s \n", key);

			if (num == 1) return overlap[num];
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);
			else puts("\n\n\n\t\t\t  �������� �ʴ� ����ó�Դϴ� ! \n\n\n\n");
			break;
		}

		bottomMessageA();

		input = getch();

		if (input == ENTER_KEY){
			Beep(DO, DURATION);
			Beep(RA, DURATION);
			action = 1;
		}
		else if (input == ESC_KEY){
			Beep(RA, DURATION);
			Beep(DO, DURATION);
			return 0;
		}
		else{
			WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
			Beep(_DO, DURATION);
			action = 0;
		}
	}
}

int searchManyPrint(UserInfo userInfo[], int overlap[], int num)
{
	int input;

	Beep(DO, DURATION);
	Beep(MI, DURATION);
	Beep(SOL, DURATION);
	Beep(_DO, DURATION);
	while (1) {
		topMessage("�˻�", "Search");

		puts("\n\t\t\t      ��  �˻�  ���  ��");
		puts("\t\t\t       ================");

		for (int i = 1; i <= num; i++){
			printf("   %2d.  %d \t %s   \t%s  \t%s\n", i,
				userInfo[overlap[i]].userId, userInfo[overlap[i]].userName,
				userInfo[overlap[i]].handphone, userInfo[overlap[i]].userAddress);
		}

		for (int i = 1; i < OVERLAP_BUFFER - num; i++)
			puts(" ");	//���� ä���

		if (num + 1 == OVERLAP_BUFFER){
			puts("\n\t\t  �˻� ����� �� ������ ��������� ��µ˴ϴ�. ");
			puts("\t\t���Ͻô� ����� ������ �ٸ� ������� �˻����ּ���.\n");
		}
		else puts("\n\n\n");

		BOT_COLOR;
		printf("\t\t\t\t\t\t\t\t\t        ");
		printf("\t ���� :  �ش� ��ȣ �Է� \t\t     ������ :  ESC \t\t    ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;

		input = getch();
		input -= '0';	//�ƽ�Ű ���� �ޱ� ������

		if (input + '0' == ESC_KEY){
			Beep(RA, DURATION);
			Beep(DO, DURATION);
			return 0;
		}
		else if (input > 0 && input <= num){
			Beep(RA, DURATION);
			return overlap[input];
		}
		else {
			WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
			Beep(_DO, DURATION);
		}
	}
}

void searchResult(UserInfo userInfo[], int num)
{
	int input;

	while (1){
		topMessage("�˻�", "Search");

		puts("\n\n\n\t\t\t      ��  �˻�  ���  ��");
		puts("\t\t\t       ================\n");

		printf("\n\t\t\tȸ��ID\t: %d \n\n", userInfo[num].userId);
		printf("\t\t\t�̸�\t: %s \n", userInfo[num].userName);
		printf("\t\t\t����ó\t: %s \n", userInfo[num].handphone);
		printf("\t\t\t�ּ�\t: %s \n", userInfo[num].userAddress);

		puts("\n\n\n");
		BOT_COLOR;
		printf("\t\t\t\t\t\t\t\t\t        ");
		printf("\t\t\t\t ������ :  ESC \t\t\t\t\t   ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;

		input = getch();

		if (input == ESC_KEY){
			Beep(RA, DURATION);
			Beep(DO, DURATION);
			return;
		}
		else {
			WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
			Beep(_DO, DURATION);
		}
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
		printf("\t\t\t        ���� ���� ����\t\t\t\t\t ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;

		puts("\n\n\n\n\n\n\n\n\t\t\t   ������ �����Ͻðڽ��ϱ�? \n\n\n\n\n\n\n");

		bottomMessageB("����");

		input = getch();

		if (input == ENTER_KEY){
			Beep(_DO, DURATION);
			Beep(SOL, DURATION);
			Beep(RA, DURATION);
			writeFile = fopen("data.txt", "wt");	//writeFile open

			fprintf(writeFile, "%s\n", userInfo[0].userAddress);

			for (int i = 1; i <= count; i++)
				fprintf(writeFile, "%d\t%s\t%s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].handphone);

			fclose(writeFile);		//writeFile close
			return SAVE;
		}

		else if (input == ESC_KEY){
			Beep(RA, DURATION);
			Beep(DO, DURATION);
			return 0;
		}
		else {
			WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
			Beep(_DO, DURATION);
		}
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
		printf("\t\t\t         ���α׷� ���� \t\t\t\t\t ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;

		puts("\n\n\n\n\t\t\t   ��  �����Ͻðڽ��ϱ�?  ��");
		puts("\t\t\t     =====================");

		if (menu == 1) puts("\n\n\t\t\t       [ �����ϰ� ���� ]");
		else puts("\n\n\t\t\t         �����ϰ� ���� ");
		if (menu == 2) puts("\n\t\t\t    [ �������� �ʰ�  ���� ] \n\n\n\n\n");
		else puts("\n\t\t\t      �������� �ʰ�  ���� \n\n\n\n\n");

		BOT_COLOR;
		printf("\t\t\t\t\t\t\t\t\t        ");
		printf("\t�޴� �̵� : ���\t�޴� ���� : ENTER      \t   ��� : ESC \t        ");
		printf("\t\t\t\t\t\t\t\t\t        ");
		DEF_COLOR;

		input = getch();

		if (input == ARROW_BUFFER)
			input = getch();

		switch (input)
		{
		case UP_ARROW_KEY:
			Beep(MI, DURATION);
			if (menu > 1) menu--;
			break;
		case DOWN_ARROW_KEY:
			Beep(MI, DURATION);
			if (menu < 2) menu++;
			break;
		case ENTER_KEY:
			Beep(DO, DURATION);
			Beep(RA, DURATION);
			return menu;
		case ESC_KEY:
			Beep(RA, DURATION);
			Beep(DO, DURATION);
			return 0;
		default:
			WAR_COLOR; printf("�߸��� �Է��Դϴ�.\t\t\t\t\t\t\t       "); DEF_COLOR;
			Beep(_DO, DURATION);
			break;
		}
	}
}

void closeGift(void)
{
	Beep(SOL, 200);
	Beep(SOL, 200);
	Beep(RA, 200);
	Beep(RA, 200);
	Beep(SOL, 200);
	Beep(SOL, 200);
	Beep(MI, 500);
	Sleep(200);
	Beep(SOL, 200);
	Beep(SOL, 200);
	Beep(MI, 200);
	Beep(MI, 200);
	Beep(RE, 500);
	Sleep(500);
	Beep(SOL, 200);
	Beep(SOL, 200);
	Beep(RA, 200);
	Beep(RA, 200);
	Beep(SOL, 200);
	Beep(SOL, 200);
	Beep(MI, 500);
	Sleep(200);
	Beep(SOL, 200);
	Beep(MI, 200);
	Beep(RE, 200);
	Beep(MI, 200);
	Beep(DO, 500);
	Sleep(700);

	Beep(DO, 100);
	Beep(MI, 100);
	Beep(SOL, 100);
	Beep(_DO, 100);
	Sleep(500);
}