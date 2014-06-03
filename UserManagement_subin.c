/*
	�ۼ���: 141033 �ڼ���
	���� �ۼ���: 2014.06.03
	����: ����� ���忡�� �ִ��� �����ϰ� ���� �� �ֵ��� ������ �߽��ϴ�.

	1. ����Ű�� ����Ű, ENTERŰ, ESCŰ�� ���� �߽��ϴ�.

	2. ȸ�� ��� �� ����Ʈ�� ����� ��µ� �� �ִ� �� ���� ������ �Է��� �����Ͽ����ϴ�.
		(��, �ʹ� ��ų� ª�� �Է�, Tap�Է� ���� ������ ����)


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

	while(!feof(readFile)) {	//�ʱ� ȸ���� count�� ����
		if (fgetc(readFile) == '\n') count++;
	}

	maxsize = 2 * count;	//�ʱ� ȸ������ 2�� ��ŭ �޸� �Ҵ�
	userInfo = (UserInfo*)malloc(sizeof(UserInfo)*maxsize);

	fseek(readFile, 0, SEEK_SET);		//���� ������ ó�� ��ġ�� ��ȯ
	setUserInfo(userInfo, readFile);	//����ü �迭�� ���� ������ ���� �� readFile close

	while(1) {
		printMain(menu);	//���� ȭ�� ���
	
		input = getch();

		if (input == ARROW_BUFFER)	//����Ű�� �Է� �� �ƽ�ŰȮ�� ���� ���� ���� �� ���� ����
			input = getch();	//�׷��� �� ��� ���۸� �ѹ� ��쵵�� �Ͽ���
		
		switch (input)
		{
		case UP_ARROW_KEY: //�� ����Ű
			if (menu > 1) menu--;
			break;
		case DOWN_ARROW_KEY: //�� ����Ű
			if (menu < 6) menu++;
			break;
		case ENTER_KEY: //enterŰ
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
				count = deleteUser(userInfo, count);
				if (count < maxsize / 3){	//�� �޸� ������ �������� �޸� �Ҵ緮 ���
					maxsize /= 2;
					userInfo = (UserInfo*)realloc(userInfo, sizeof(UserInfo)*maxsize);
				}
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
		case ESC_KEY: //escŰ
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
	puts("\t�޴� �̵� : ���\t�޴� ���� : ENTER      \t   ���� : ESC");
	puts("-------------------------------------------------------------------------------");
}

void printList(UserInfo userInfo[], int count)
{
	int input, page, i, k = 1;

	page = 1 + (count - 1) / 17;		//��ü ������ ���

	while(1) {
		system("cls");

		printf("List   \t\t\t\t\t\t\t\t     page %d/%d\n", k, page);
		puts("\n\tȸ��ID \t �̸�   \t����ó  \t�ּ�");
		puts("-------------------------------------------------------------------------------");
		
		for (i = 1+(k-1)*17; i <= k*17 && i <= count; i++)	//����Ʈ ���
			printf("\t%d \t %s   \t%s  \t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].handphone, userInfo[i].userAddress);
		
		if (page == k){		//���� ä���
			for (i = count - (1+(k-1)*17); 16 - i > 0; i++)
				puts(" ");
		}

		puts("-------------------------------------------------------------------------------");
		puts("\t ������ �̵� :   ��    ��     \t\t ������ :  ESC");
		puts("-------------------------------------------------------------------------------");
		
		input = getch();

		if (input == ARROW_BUFFER)
			input = getch();
		
		switch (input)
		{
		case LEFT_ARROW_KEY:	//���� ����Ű
			if (k != 1) k--;
			break;
		case RIGHT_ARROW_KEY:	//���� ����Ű
			if (k != page) k++;
			break;
		case ESC_KEY:	//escŰ
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
	int input, warning, input2;
	int id = userInfo[1].userId;	//�ʱⰪ ����

	for (int i = 2; i <= count; i++)	//���� ū id�� ���
		id = id > userInfo[i].userId ? id : userInfo[i].userId;

	userInfo[++count].userId = ++id;	//count�� 1���� ��Ű�� ���ο� id �ο�

	/* ������ �Է� �ް� �������� ���� ���� ���� �� �����Ƿ� �Ʒ� ���� �����۵��� ���� �ʱ�ȭ */
	userInfo[count].userName[1] = 0;
	userInfo[count].handphone[1] = 0;
	userInfo[count].userAddress[1] = 0;
	
	while(1) {
		system("cls");

		puts("Register \n\n");
		puts("\t\t\t       ȸ�� ���� �Է�  \n");
		puts("-------------------------------------------------------------------------------");
		
		//ID�� �ڵ����� �ο��� �� ���
		printf("\n\n\t\t ȸ��ID\t: %d \n\n", userInfo[count].userId);

		//�̸� �Է�
		if (userInfo[count].userName[1] == 0){
			/* ���� �����÷ο� ������ ���� fgets�� ���� */
			printf("\t\t �̸�\t: "); fgets(userInfo[count].userName, NAME_PHONE_BUFFER, stdin);
			
			/* '\n'�� �Է°� �ȿ� �ִٸ� �����ϰ�, ���ٸ� �ʰ����۰� ���Ҵٴ� ���̹Ƿ� ���� ���� */
			if (*(userInfo[count].userName + strlen(userInfo[count].userName) - 1) == '\n')
				*(userInfo[count].userName + strlen(userInfo[count].userName) - 1) = '\0';
			else while (getchar() != '\n'); 
			
			/* �Է��� �̻��ϸ� �ٽ� �Է� */
			if (strlen(userInfo[count].userName) < 4 || strlen(userInfo[count].userName) > 8){
				
				//�Էµ� �� �ʱ�ȭ
				for (int i = 0; i < NAME_PHONE_BUFFER; i++)
					userInfo[count].userName[i] = 0;
				
				puts("\n\n\t\t �̸��� �ʹ� ��ų� ª���ϴ�.");
				puts("\t\t �̸��� 2 ~ 4 ���ڸ� �����մϴ�. \n\n\t\t [ ���� 4 ~ 8 ���� ]\n\n\n");
				bottomMessage();
				
				input2 = getch();	//

				if (input2 == ESC_KEY) return --count;
				else if (input2 == ARROW_BUFFER)	input2 = getch();
				
				continue;
			}

			/* �� �Է� �߽߰� �ٽ� �Է� */
			for (int i = 0; userInfo[count].userName[i] != '\0'; i++){
				if (userInfo[count].userName[i] == '\t'){
					
					for (int i = 0; i < NAME_PHONE_BUFFER; i++) 
						userInfo[count].userName[i] = 0;
					
					puts("\n\n\t\t ��(Tab)�� �Է��� �� �����ϴ�!\n\n\n\n\n");
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
		/* �Է� �Ϸ�� �׸��� �н� */
		else printf("\t\t �̸�\t: %s \n", userInfo[count].userName);	
		
		//����ó �Է�
		if (userInfo[count].handphone[1] == 0){
			printf("\t\t ����ó\t: "); fgets(userInfo[count].handphone, NAME_PHONE_BUFFER, stdin);
			
			if (*(userInfo[count].handphone + strlen(userInfo[count].handphone) - 1) == '\n')
				*(userInfo[count].handphone + strlen(userInfo[count].handphone) - 1) = '\0';
			else while (getchar() != '\n');
			
			if (strlen(userInfo[count].handphone) < 12 || strlen(userInfo[count].handphone) > 13
				|| userInfo[count].handphone[3] != '-' || // ����ó ���� �˻� ('-'�� �����ߴ���)
				userInfo[count].handphone[7] != '-' && userInfo[count].handphone[8] != '-' ||
				userInfo[count].handphone[7] == '-' && userInfo[count].handphone[8] == '-') {
				
				for (int i = 0; i < NAME_PHONE_BUFFER; i++)
					userInfo[count].handphone[i] = 0;
				
				puts("\n\t\t ����ó ���Ŀ� ���� �ʽ��ϴ�. ");
				puts("\t\t ���Ŀ� �°� �Է����ּ���. \n\n\t\t [ ��) 010-1234-5678  or  031-123-4567 ]\n\n\n");
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
					
					puts("\n\n\t\t ��(Tab)�� �Է��� �� �����ϴ�!\n\n\n\n");
					bottomMessage();
					
					input2 = getch();

					if (input2 == ESC_KEY) return --count;
					else if (input2 == ARROW_BUFFER) input2 = getch();
					
					warning = 1;
					break;
				}

				// '-'�̿ܿ��� ���ڸ� �Է��ߴ��� �˻�
				if ((userInfo[count].handphone[i] < '0' || userInfo[count].handphone[i] > '9') &&
					(userInfo[count].handphone[i] != '-' || (i != 3 && i != 7 && i != 8))){

					for (int i = 0; i < NAME_PHONE_BUFFER; i++)
						userInfo[count].handphone[i] = 0;

					puts("\n\t\t ����ó ���Ŀ� ���� �ʽ��ϴ�.");
					puts("\t\t ���Ŀ� �°� �Է����ּ���. \n\n\t\t [ ��) 010-1234-5678  or  031-123-4567 ]\n\n\n");
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

		else printf("\t\t ����ó\t: %s \n", userInfo[count].handphone);

		//�ּ� �Է�
		if (userInfo[count].userAddress[1] == 0){
			printf("\t\t �ּ�\t: "); fgets(userInfo[count].userAddress, ADDRESS_BUFFER, stdin);
			
			if (*(userInfo[count].userAddress + strlen(userInfo[count].userAddress) - 1) == '\n')
				*(userInfo[count].userAddress + strlen(userInfo[count].userAddress) - 1) = '\0';
			else while (getchar() != '\n');
			
			if (strlen(userInfo[count].userAddress) < 10 || strlen(userInfo[count].userAddress) > 30){
				
				for (int i = 0; i < ADDRESS_BUFFER; i++) 
					userInfo[count].userAddress[i] = 0;
				
				puts("\n\t\t �ּҰ� �ʹ� ��ų� ª���ϴ�. ");
				puts("\t\t �ּ� 5���� �̻�, �׸��� 15���� �̳��� �Է����ּ���.");
				puts("\n\t\t [ ���� : 10 ~ 30���� (���� ����) ]\n\n");
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
					
					puts("\n\n\t\t ��(Tab)�� �Է��� �� �����ϴ�!\n\n\n");
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

		else printf("\t\t �ּ�\t: %s \n", userInfo[count].userAddress);

		puts("\n\n\n\t\t\t   ������ ����Ͻðڽ��ϱ�? \n\n\n\n");
		puts("-------------------------------------------------------------------------------");
		puts("\t\t ��� :  ENTER     \t\t ��� :  ESC");
		puts("-------------------------------------------------------------------------------");
		
		input = getch();

		if (input == ENTER_KEY) return count;		//����ϸ� ������ count ��ȯ
		else if (input == ESC_KEY) return --count;	//������� ������ count�� �������� �����Ƿ� ��ȿ
		else printf("�߸��� �Է��Դϴ�.");
	}
}

void saveInfo(UserInfo userInfo[], FILE *writeFile, int count)
{
	int input;

	while(1) {
		system("cls");

		puts("Save \n\n");
		puts("\t\t\t\t���� ���� ����  \n");
		puts("-------------------------------------------------------------------------------");
		puts("\n\n\n\n\n\t\t\t   ������ �����Ͻðڽ��ϱ�? \n\n\n\n\n");
		puts("-------------------------------------------------------------------------------");
		puts("\t\t ���� :  ENTER     \t\t ��� :  ESC");
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
		else printf("�߸��� �Է��Դϴ�.");
	}
}

int deleteUser(UserInfo userInfo[], int count)
{
	int input, menu = 1, del;

	while(1) {
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
		puts("\t�޴� �̵� : ���\t�޴� ���� : ENTER      \t ������ : ESC");
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
				puts("\t\t\t        ȸ�� ���� ���� \n");
				puts("-------------------------------------------------------------------------------");
				
				printf("\n\n\n\t\t\tȸ��ID\t: %d \n\n", userInfo[del].userId);
				printf("\t\t\t�̸�\t: %s \n", userInfo[del].userName);
				printf("\t\t\t����ó\t: %s \n", userInfo[del].handphone);
				printf("\t\t\t�ּ�\t: %s \n", userInfo[del].userAddress);
				
				puts("\n\n\n\t\t\t   ������ �����Ͻðڽ��ϱ�? \n\n\n");
				puts("-------------------------------------------------------------------------------");
				puts("\t\t ���� :  ENTER     \t\t ��� :  ESC");
				puts("-------------------------------------------------------------------------------");
				
				input = getch();

				if (input == ENTER_KEY){
					/* ���� ����� �� �������� �ִٸ�, count�� �ϳ� ���̴� ������ �� */
					if (del == count){
						deleteMessage();
						count--;
						break;
					}
					/* ������ ���� �� ĭ�� ������ ����� */
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
				else printf("�߸��� �Է��Դϴ�.");
			}
			break;
		case ESC_KEY:
			return count;
		default:
			printf("�߸��� �Է��Դϴ�.");
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
		puts("\t\t\t        ȸ�� ���� �˻� \n");
		puts("-------------------------------------------------------------------------------");
		
		switch (menu)
		{
		case 1:
			puts("\n\n\t\t\t    ��  ȸ��ID�� �˻�  ��");
			puts("\t\t\t      ------------------");
			
			if (action){
				printf("\n\t\t\t  ID : "); fgets(key, NAME_PHONE_BUFFER, stdin);
				
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
			else printf("\n\t\t\t  ID : %d \n", id);
			
			/* �˻� ����� 1���� �� */
			if (num == 1) return overlap[num];

			/* �˻� ����� 2�� �̻��� �� */
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);

			/* �˻� ����� ���� �� */
			else puts("\n\n\n\t\t\t   �������� �ʴ� ID�Դϴ�! \n\n\n");
			
			break;
		case 2:
			puts("\n\n\t\t\t    ��  �̸����� �˻�  ��");
			puts("\t\t\t      ------------------");
			
			if (action){
				printf("\n\t\t\t  �̸� : "); fgets(key, NAME_PHONE_BUFFER, stdin);
				
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
			else printf("\n\t\t\t  �̸� : %s \n", key);
			
			if (num == 1) return overlap[num];
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);
			else puts("\n\n\n\t\t\t   �������� �ʴ� �̸��Դϴ�! \n\n\n");
			
			break;
		case 3:
			puts("\n\n\t\t\t    ��  ����ó�� �˻�  ��");
			puts("\t\t\t      ------------------");
			
			if (action){
				printf("\n\t\t\t  ����ó : "); fgets(key, ADDRESS_BUFFER, stdin);
				
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
			else printf("\n\t\t\t  ����ó : %s \n", key);
			
			if (num == 1) return overlap[num];
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);
			else puts("\n\n\n\t\t\t   �������� �ʴ� ����ó�Դϴ�! \n\n\n");
			
			break;
		}

		bottomMessage();
		
		input = getch();
		
		if (input == ENTER_KEY) action = 1;
		else if (input == ESC_KEY) return 0;
		else{
			puts("�߸��� �Է��Դϴ�.");
			action = 0;
		}
	}
}

void bottomMessage(void)
{
	puts("-------------------------------------------------------------------------------");
	puts("\t\t�ٽ� �Է� :  ENTER   \t\t������ :  ESC");
	puts("-------------------------------------------------------------------------------");
}

void deleteMessage(void)
{
	system("cls");

	puts("Delete \n\n");
	puts("\t\t\t        ȸ�� ���� ���� \n");
	puts("-------------------------------------------------------------------------------");
	puts("\n\n\n\n\n\t\t\t       ================");
	puts("\t\t\t      ��  ����  �Ϸ�  ��");
	puts("\t\t\t       ================ \n\n\n\n\n");
	puts("-------------------------------------------------------------------------------");
	puts("\t\t\t ����Ϸ��� �ƹ� Ű�� �������� ");
	puts("-------------------------------------------------------------------------------");

	getch();	//�޽��� ����� ���� ����
}

int searchManyPrint(UserInfo userInfo[], int overlap[], int num)
{
	int input;
	
	while (1) {
		system("cls");

		puts("Search \n");
		puts("\t\t\t        ȸ�� ���� �˻� \n");
		puts("-------------------------------------------------------------------------------\n");
		puts("\t\t\t      ��  �˻� ���  �� \n");

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

		puts("-------------------------------------------------------------------------------");
		puts("\t ���� :  �ش� ��ȣ �Է� \t\t     ������ :  ESC");
		puts("-------------------------------------------------------------------------------");
		
		input = getch();
		input -= '0';	//�ƽ�Ű ���� �ޱ� ������

		if (input + '0' == ESC_KEY) return 0;
		else if (input > 0 && input <= num) return overlap[input];
		else printf("�߸��� �Է��Դϴ�.");
	}
}

//void modifyUser