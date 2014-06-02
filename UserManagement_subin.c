/*
	�ۼ���: 141033 �ڼ���
	���� �ۼ���: 2014.06.02
	����: ����� ���忡�� �ִ��� �����ϰ� ���� �� �ֵ��� ������ �߽��ϴ�.

	 1. ���ڿ� �Է��� �ʿ��� �κ�(ȸ�� ��� ��)�� �����ϰ�� ���� ���͸� ���� �ʿ䰡 ������ �Ͽ�����,
		������ �ѱ�, �޴� �̵��� ����Ű��, ������� ESCŰ, Ȯ���� ����Ű�� ����� �� �ְ� �Ͽ����ϴ�.

	 2. ȸ�� ��� �� ����Ʈ�� ����� ��µ� �� �ִ� �� ���� ������ �Է��� �����Ͽ����ϴ�.
		(��, �ʹ� ��ų� ª�� �Է�, Tap�Է� ���� ������ ����)
		���� �Է� ���� ����ϰ� �ٷ� ������ ���� ��츦 ���� Ż�� ��ɾ ���������ϴ�.
		�׸��� �Է��� �� �� �� ���� �� ��(?) �߰��ϰ� ���� ���� ���� �����Ƿ� �������� ���� �����ϰ� �Ͽ����ϴ�.


		=== ���� ���� (2014.06.02) ===

		* ���� ȭ�� �������̽� ���� ( ���� �Է¿��� ȭ��ǥ �Է����� )
		* ����ó �Է½� ���Ŀ� ��Ȯ�� �¾ƾ� �Է� �ǵ��� �Է� ���� ��� ��ȭ 
		* �˻� ���, ���� ���(���� �̿�) �߰�
		* ��� �ּ� ����

*/
#include "UserManagement.h"

int main(void)
{
	UserInfo *userInfo;
	FILE *readFile;
	FILE *writeFile;
	int input, maxsize, count = -1, menu = 1;

	readFile = fopen("data.txt", "rt");	//readFile �ʱ�ȭ
	if (readFile == NULL){
		puts("\n\n\n\n\n\n\n\n\n\n\n\t\t\t �����Ͱ� �������� �ʽ��ϴ�! \n\n\n\n\n\n\n\n\n\n\n");
		return -1;
	}
	while (!feof(readFile)){	//�ʱ� ȸ���� count�� ����
		if (fgetc(readFile) == '\n') count++;
	}
	maxsize = 2 * count;	//�ʱ� ȸ������ 2�� ��ŭ �޸� �Ҵ�
	userInfo = (UserInfo*)malloc(sizeof(UserInfo)*maxsize);

	fseek(readFile, 0, SEEK_SET);		//���� ������ ó�� ��ġ�� ��ȯ
	setUserInfo(userInfo, readFile);	//����ü �迭�� ���� ������ ���� �� readFile close

	while (1){
		printMain(menu);
		input = getch();
		if (input == 224)	//����Ű�� �Է� �� 224���� ���� �� 72, 80 ���� �ٸ� ���� ����
			input = getch();	//�׷��� 224�� ���� ��� ���۸� �ѹ� ��쵵�� �Ͽ���
		switch (input)
		{
		case 72: //�� ����Ű
			if (menu > 1) menu--;
			break;
		case 80: //�� ����Ű
			if (menu < 6) menu++;
			break;

		case 13: //enterŰ
			switch (menu)
			{
			case 1:	//���
				printList(userInfo, count);
				break;
			case 2:	//���
				count = addUser(userInfo, count);
				if (count > maxsize - 5){	//�޸� �Ҵ緮 �Ѱ�ġ�� ��������� �߰��Ҵ�
					maxsize *= 2;
					userInfo = (UserInfo*)realloc(userInfo, sizeof(UserInfo)*maxsize);
				}
				break;
			case 3:	//����
				deleteUserMain(userInfo, count);
				
				break;
			case 4:	//����
			case 5:	//�˻�
				printf("���� ���� ���� ���� ����Դϴ�.");
				break;
			case 6:	//����
				writeFile = 0;	// writeFile�� �ѱ�� ���� �ʱ�ȭ
				saveInfo(userInfo, writeFile, count);
				break;
			} //switch(menu) out
			break;

		case 27: //escŰ
			printf("���α׷��� �����մϴ�.\t");
			free(userInfo);
			return 0;
		default:
			printf("�߸��� �Է��Դϴ�.");
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
	puts("\n\t\t\t      ȸ�� ���� ���α׷� \n");
	puts("-------------------------------------------------------------------------------");
	if (menu == 1) puts("\n\n\t\t\t      [ ȸ�� ��� ��� ]");
	else puts("\n\n\t\t\t        ȸ�� ��� ��� ");
	if (menu == 2) puts("\n\t\t\t      [ �ű� ȸ�� ��� ]");
	else puts("\n\t\t\t        �ű� ȸ�� ��� ");
	if (menu == 3) puts("\n\t\t\t      [ ���� ȸ�� ���� ]");
	else puts("\n\t\t\t        ���� ȸ�� ���� ");
	if (menu == 4) puts("\n\t\t\t      [ ȸ�� ���� ���� ]");
	else puts("\n\t\t\t        ȸ�� ���� ���� ");
	if (menu == 5) puts("\n\t\t\t      [ ���� ȸ�� �˻� ]");
	else puts("\n\t\t\t        ���� ȸ�� �˻� ");
	if (menu == 6) puts("\n\t\t\t      [ ���� ���� ���� ]\n\n\n");
	else puts("\n\t\t\t        ���� ���� ���� \n\n\n");
	puts("-------------------------------------------------------------------------------");
	puts("\t�޴� �̵� : ���\t�޴� ���� : ENTER      \t   ����: ESC");
	puts("-------------------------------------------------------------------------------");
}
void printList(UserInfo userInfo[], int count)
{
	int input, page, i, k = 1;
	page = 1 + count / 18;
	while (1){
		system("cls");
		printf("List   \t\t\t\t\t\t\t\t     page %d/%d\n", k, page);
		puts("\tȸ��ID\t �̸�\t  ����ó\t  �ּ�");
		puts("-------------------------------------------------------------------------------");
		for (i = 1+(k-1)*18; i <= k*18 && i <= count; i++)
			printf("\t%d\t %s\t  %s\t  %s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].handphone, userInfo[i].userAddress);
		puts("-------------------------------------------------------------------------------");
		puts("\t ������ �̵� :   <-    ->     \t\t ������:  ESC");
		puts("-------------------------------------------------------------------------------");
		input = getch();
		if (input == 224)
			input = getch();
		switch (input)
		{
		case 75:	//���� ����Ű
			if (k != 1) k--;
			break;
		case 77:	//���� ����Ű
			if (k != page) k++;
			break;
		case 27:	//escŰ
			return;
		default:
			printf("�߸��� �Է��Դϴ�.");
			break;
		}
	}
}
void setUserInfo(UserInfo userInfo[], FILE *readFile)
{
	fscanf(readFile, "%[^\n]", userInfo[0].userAddress);	//ù ������ ���� ����
	for (int i = 1; !feof(readFile); i++)
		fscanf(readFile, "%d\t%s\t%[^\t]%s\n", &userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].handphone);
	fclose(readFile);
}
int addUser(UserInfo userInfo[], int count)
{
	int input, warning;
	int id = userInfo[1].userId;
	for (int i = 2; i <= count; i++){	//���� ū id�� ���
		id = id > userInfo[i].userId ? id : userInfo[i].userId;
	}
	userInfo[++count].userId = ++id;	//count�� 1����
	// ������ �Է� �ް� �������� ���� ���� ���� �� �����Ƿ� �Ʒ� ���� �����۵��� ���� �ʱ�ȭ
	userInfo[count].userName[1] = 0;
	userInfo[count].handphone[1] = 0;
	userInfo[count].userAddress[1] = 0;
	
	while (1){
		system("cls");
		puts("Register \t\t\t\t\t\t\t out: 'esc'�Է�\n\n");
		puts("\t\t\t       ȸ�� ���� �Է�  \n");
		puts("-------------------------------------------------------------------------------");
		printf("\n\n\t\t ȸ��ID\t: %d \n\n", userInfo[count].userId);

		//�̸� �Է�
		if (userInfo[count].userName[1] == 0){
			printf("\t\t �̸�\t: "); gets(userInfo[count].userName); //�Է�
			if (strcmp(userInfo[count].userName, "esc") == 0) return --count;	//�Է°��� esc�̸� �������� �ʰ� �ٷ� ����
			else if (strlen(userInfo[count].userName) < 4 || strlen(userInfo[count].userName) > 6){	//�Է��� �̻��ϸ� �ٽ� �Է�
				for (int i = 0; i < NAME_PHONE_BUFFER; i++) userInfo[count].userName[i] = 0;	//�ʱ�ȭ
				puts("\n\n\t\t �̸��� �ʹ� ��ų� ª���ϴ�.");
				puts("\t\t �̸��� 2 ~ 3 ���ڸ� �����մϴ�. \n\n\t\t [ ���� 4 ~ 6 ���� ]");
				while (getchar() != '\n');	//���� ���� �� ���� �޼������� ������ ����
				continue;
			}
			for (int i = 0; userInfo[count].userName[i] != '\0'; i++){
				if (userInfo[count].userName[i] == '\t'){
					for (int i = 0; i < NAME_PHONE_BUFFER; i++) userInfo[count].userName[i] = 0;
					puts("\n\n\t\t ��(Tab)�� �Է��� �� �����ϴ�!");
					while (getchar() != '\n');
					warning = 1;
					break;
				}
				warning = 0;
			}
			if (warning) continue;	//�� �Է� �߽߰� �ٽ� �Է�
		}
		else printf("\t\t �̸�\t: %s \n", userInfo[count].userName);	//�Է� �Ϸ�� �׸��� �н�
		
		//����ó �Է�
		if (userInfo[count].handphone[1] == 0){
			printf("\t\t ����ó\t: "); gets(userInfo[count].handphone);
			if (strcmp(userInfo[count].handphone, "esc") == 0) return --count;
			else if (strlen(userInfo[count].handphone) < 12 || strlen(userInfo[count].handphone) > 13
				|| userInfo[count].handphone[3] != '-' ||	// ����ó ���� �˻� ('-'�� �����ߴ���)
				userInfo[count].handphone[7] != '-' && userInfo[count].handphone[8] != '-' ||
				userInfo[count].handphone[7] == '-' && userInfo[count].handphone[8] == '-'){
				for (int i = 0; i < NAME_PHONE_BUFFER; i++) userInfo[count].handphone[i] = 0;
				puts("\n\t\t ����ó ���Ŀ� ���� �ʽ��ϴ�. ");
				puts("\t\t ���Ŀ� �°� �Է����ּ���. \n\n\t\t [ ��) 010-1234-5678  or  031-123-4567 ]");
				while (getchar() != '\n');
				continue;
			}
			for (int i = 0; userInfo[count].handphone[i] != '\0'; i++){
				if (userInfo[count].handphone[i] == '\t'){
					for (int i = 0; i < NAME_PHONE_BUFFER; i++) userInfo[count].handphone[i] = 0;
					puts("\n\n\t\t ��(Tab)�� �Է��� �� �����ϴ�!");
					while (getchar() != '\n');
					warning = 1;
					break;
				}
				// '-'�̿ܿ��� ���ڸ� �Է��ߴ��� �˻�
				if ((userInfo[count].handphone[i] < '0' || userInfo[count].handphone[i] > '9') &&
					(userInfo[count].handphone[i] != '-' || (i != 3 && i != 7 && i != 8))){
					for (int i = 0; i < NAME_PHONE_BUFFER; i++) userInfo[count].handphone[i] = 0;
					puts("\n\t\t ����ó ���Ŀ� ���� �ʽ��ϴ�.");
					puts("\t\t ���Ŀ� �°� �Է����ּ���. \n\n\t\t [ ��) 010-1234-5678  or  031-123-4567 ]");
					while (getchar() != '\n');
					warning = 1;
					break;
				}
				warning = 0;
			}
			if (warning) continue;
		}
		else printf("\t\t ����ó\t: %s \n", userInfo[count].handphone);

		//�ּ� �Է�
		if (userInfo[count].userAddress[1] == 0){
			printf("\t\t �ּ�\t: "); gets(userInfo[count].userAddress);
			if (strcmp(userInfo[count].userAddress, "esc") == 0) return --count;
			else if (strlen(userInfo[count].userAddress) < 20 || strlen(userInfo[count].userAddress) > 30){
				for (int i = 0; i < ADDRESS_BUFFER; i++) userInfo[count].userAddress[i] = 0;
				puts("\n\t\t �ּҰ� �ʹ� ��ų� ª���ϴ�. ");
				puts("\t\t �ּ� 10���� �̻�, �׸��� 15���� �̳��� �Է����ּ���.");
				puts("\n\t\t [ ���� : 20 ~ 30���� (���� ����) ]");
				while (getchar() != '\n');
				continue;
			}
			for (int i = 0; userInfo[count].userAddress[i] != '\0'; i++){
				if (userInfo[count].userAddress[i] == '\t'){
					for (int i = 0; i < ADDRESS_BUFFER; i++) userInfo[count].userAddress[i] = 0;
					puts("\n\n\t\t ��(Tab)�� �Է��� �� �����ϴ�!");
					while (getchar() != '\n');
					warning = 1;
					break;
				}
				warning = 0;
			}
			if (warning) continue;
		}
		else printf("\t\t �ּ�\t: %s \n", userInfo[count].userAddress);

		puts("\n\n\n\t\t\t   ������ ����Ͻðڽ��ϱ�? \n\n\n\n");
		puts("-------------------------------------------------------------------------------");
		puts("\t\t ��� :  ENTER     \t\t ���:  ESC");
		puts("-------------------------------------------------------------------------------");
		input = getch();
		if (input == 13) return count;			//����ϸ� ������ count ��ȯ
		else if (input == 27) return --count;	//������� ������ count�� �������� �����Ƿ� ��ȿ
		else printf("�߸��� �Է��Դϴ�.");
	}
}
void saveInfo(UserInfo userInfo[], FILE *writeFile, int count)
{
	int input;
	while (1){
		system("cls");
		puts("Save \n\n");
		puts("\t\t\t\t���� ���� ����  \n");
		puts("-------------------------------------------------------------------------------");
		puts("\n\n\n\n\n\t\t\t   ������ �����Ͻðڽ��ϱ�? \n\n\n\n\n");
		puts("-------------------------------------------------------------------------------");
		puts("\t\t ���� :  ENTER     \t\t ���:  ESC");
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
		else printf("�߸��� �Է��Դϴ�.");
	}
}
void deleteUserMain(UserInfo userInfo[], int count)
{
	int input, menu = 1, del;
	while (1){
		system("cls");
		puts("Delete \n\n");
		puts("\t\t\t        ȸ�� ���� ���� \n");
		puts("-------------------------------------------------------------------------------");
		puts("\n\n\t\t\t      ��  �˻�  ���  ��");
		puts("\t\t\t       ----------------");
		if (menu == 1) puts("\n\t\t\t      [ ȸ��ID��  �˻� ]");
		else puts("\n\t\t\t        ȸ��ID��  �˻� ");
		if (menu == 2) puts("\n\t\t\t      [ �̸�����  �˻� ]");
		else puts("\n\t\t\t        �̸�����  �˻� ");
		if (menu == 3) puts("\n\t\t\t      [ ����ó��  �˻� ]\n\n\n");
		else puts("\n\t\t\t        ����ó��  �˻� \n\n\n");
		puts("-------------------------------------------------------------------------------");
		puts("\t�޴� �̵� : ���\t�޴� ���� : ENTER      \t ������: ESC");
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
			printf("�߸��� �Է��Դϴ�.");
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
		puts("\t\t\t        ȸ�� ���� �˻� \n");
		puts("-------------------------------------------------------------------------------");
		switch (menu)
		{
		case 1:
			puts("\n\n\t\t\t    ��  ȸ��ID�� �˻�  ��");
			puts("\t\t\t      ------------------");
			if (action){
				printf("\n\t\t\t  ID : "); scanf("%d", &id);
				while (getchar() != '\n');	//���� ����
				for (i = 1; i <= count; i++){	//�˻�
					if (userInfo[i].userId == id) break;
				}
			}
			else printf("\n\t\t\t  ID : %d \n", id);
			if (i > count) puts("\n\n\n\t\t\t   �������� �ʴ� ID�Դϴ�! \n\n\n");
			else return i;	//ã�� ȸ���� �迭 ��ġ�� ����
			break;
		case 2:
			puts("\n\n\t\t\t    ��  �̸����� �˻�  ��");
			puts("\t\t\t      ------------------");
			if (action){
				printf("\n\t\t\t  �̸� : "); gets(key);
				for (i = 1; i <= count; i++){
					if (strcmp(userInfo[i].userName, key) == 0) break;
				}
			}
			else printf("\n\t\t\t  �̸� : %s \n", key);
			if (i > count) puts("\n\n\n\t\t\t   �������� �ʴ� �̸��Դϴ�! \n\n\n");
			else return i;
			break;
		case 3:
			puts("\n\n\t\t\t    ��  ����ó�� �˻�  ��");
			puts("\t\t\t      ------------------");
			if (action){
				printf("\n\t\t\t  ����ó : "); gets(key);
				for (i = 1; i <= count; i++){
					if (strcmp(userInfo[i].handphone, key) == 0) break;
				}
			}
			else printf("\n\t\t\t  ����ó : %s \n", key);
			if (i > count) puts("\n\n\n\t\t\t   �������� �ʴ� ����ó�Դϴ�! \n\n\n");
			else return i;
			break;
		}
		puts("-------------------------------------------------------------------------------");
		puts("\t\t�ٽ� �Է� :  ENTER   \t\t������:  ESC");
		puts("-------------------------------------------------------------------------------");
		input = getch();
		if (input == 13) action = 1;
		else if (input == 27) return 0;
		else{
			puts("�߸��� �Է��Դϴ�.");
			action = 0;
		}
	}
}