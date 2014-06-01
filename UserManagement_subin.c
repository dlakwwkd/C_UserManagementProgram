/*
	�ۼ���: 141033 �ڼ���
	�ۼ���: 2014.06.01
	����: �ִ��� �����ϰ� ����ϱ� ���ϰ� ������ �Ϸ� ����߽��ϴ�.

	 1. �������� �Է��� �ʿ��� �κ��� �����ϰ�� ����Ű�� ���� �ʿ䰡 ������ �Ͽ�����,
		������ �ѱ��� ����Ű��, ������� ESCŰ, Ȯ���� ����Ű�� ����� �� �ְ� �Ͽ����ϴ�.

	 2. ȸ�� ��� �� ����Ʈ�� ����� ��µ� �� �ִ� �� ���� ������ �Է��� �����Ͽ����ϴ�.
		(��, �ʹ� ��ų� ª�� �Է�, Tap�Է� ���� ������ ����)
		���� �Է� ���� ����ϰ� �ٷ� ������ ���� ��츦 ���� Ż�� ��ɾ ���������ϴ�.
		�׸��� �Է��� �� �� �� ���� �� ��(?) �߰��ϰ� ���� ���� ���� �����Ƿ� �������� ���� �����ϰ� �Ͽ����ϴ�.
*/
#include "UserManagement.h"

int main(void)
{
	UserInfo *userInfo;
	FILE *readFile;
	FILE *writeFile;
	int input, maxsize, count = -1;		//ù ������ �����ؾ� �ϱ� ������ -1��

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
		printMain();
		input = getch();
		input -= '0';	//������ �ƽ�Ű���� ������ �ޱ� ����
		switch (input)
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
		case 4:	//����
		case 5:	//�˻�
			puts("\n���� ���� ���� ���� ����Դϴ�.");
			break;
		case 6:	//����
			writeFile = 0;	//���� �ѱ�� ���� �ʱ�ȭ
			saveInfo(userInfo, writeFile, count);
			break;
		case 7:		//����
		case -21:	//ESCŰ�� ����
			puts("\n���α׷��� �����մϴ�.");	//���� �����ϰ� �����ϴ� ����� �������� �ʾ���
			free(userInfo);
			return 0;
		default:
			puts("\n�߸��� �Է��Դϴ�.");	//���� �޽����� �������� �ʰ� ������� ���� �ǵ��� ������
			break;
		}
	}
	free(userInfo);
	return 0;
}


void printMain(void)
{
	system("cls");
	puts("Main \n\n");
	puts("\n\t\t\t    [ ȸ������ ���α׷� ] \n");
	puts("\n\t\t\t     1. ȸ�� ��� ���� ");
	puts("\n\t\t\t     2. ȸ�� ����ϱ� ");
	puts("\n\t\t\t     3. ȸ�� �����ϱ� ");
	puts("\n\t\t\t     4. ȸ�� ���� �����ϱ� ");
	puts("\n\t\t\t     5. ȸ�� �˻��ϱ� ");
	puts("\n\t\t\t     6. �����ϱ� ");
	puts("\n\t\t\t     7. �����ϱ� ");
	printf("\n\n|�Է�> ");
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
		puts("\t ������ �̵� :   <-    ->     \t\t ������:  ESCŰ");
		puts("-------------------------------------------------------------------------------");
		input = getch();
		if (input == 224)	//����Ű�� �Է� �� 224���� ���� �� 75,77 ���� �ٸ� ���� ����
			input = getch();	//�׷��� 224�� ���� ��� �ٽ� �ѹ� ���� �޵��� �Ͽ���
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
				for (int i = 0; i < 20; i++) userInfo[count].userName[i] = 0;	//�ʱ�ȭ
				puts("\n\n\t\t �̸��� �ʹ� ��ų� ª���ϴ�.");
				puts("\t\t �̸��� 2 ~ 3 ���ڸ� �����մϴ�. (���� 4 ~ 6 ����)");
				while (getchar() != '\n');	//���� ���� �� ���� �޼������� ����
				continue;
			}
			for (int i = 0; userInfo[count].userName[i] != '\0'; i++){
				if (userInfo[count].userName[i] == '\t'){
					for (int i = 0; i < 20; i++) userInfo[count].userName[i] = 0;
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
			else if (strlen(userInfo[count].handphone) < 12 || strlen(userInfo[count].handphone) > 13){
				for (int i = 0; i < 20; i++) userInfo[count].handphone[i] = 0;
				puts("\n\n\t\t ����ó�� �ʹ� ��ų� ª���ϴ�. ");
				puts("\t\t ���Ŀ� �°� �Է����ּ���. (��: 010-1234-5678)");
				while (getchar() != '\n');
				continue;
			}
			for (int i = 0; userInfo[count].handphone[i] != '\0'; i++){
				if (userInfo[count].handphone[i] == '\t'){
					for (int i = 0; i < 20; i++) userInfo[count].handphone[i] = 0;
					puts("\n\n\t\t ��(Tab)�� �Է��� �� �����ϴ�!");
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
				for (int i = 0; i < 32; i++) userInfo[count].userAddress[i] = 0;
				puts("\n\n\t\t �ּҰ� �ʹ� ��ų� ª���ϴ�. ");
				puts("\t\t �ּ� 10���� �̻�, �׸��� 15���� �̳��� �Է����ּ���.");
				while (getchar() != '\n');
				continue;
			}
			for (int i = 0; userInfo[count].userAddress[i] != '\0'; i++){
				if (userInfo[count].userAddress[i] == '\t'){
					for (int i = 0; i < 32; i++) userInfo[count].userAddress[i] = 0;
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
		printf("\n\n\n\n\n\t\t\t   ������ �����Ͻðڽ��ϱ�? \n\n\n\n\n\n");
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