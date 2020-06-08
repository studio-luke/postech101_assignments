#include <stdio.h>
#pragma warning (disable:4996)
#define MAX 30
#define max 20
#define FFLUSH while(getchar()!='\n');
void make_password(char vpw[], char email[]);//�н����� ����
char validate_email(char email[]);//�̸��� Ÿ�缺 ���� �Ǵ�
void input(char email[], char pw[]);//�̸��� , pw�Է¹���
int seq_search(char arr[], char n);//�迭 ������ n�� �ε��� ã����
char try_again();//�ٽý��� ���� �Ǵ�
int subsq(char arr[], char n);//���ӵ� . �Ǵ�

int main() {
	char email[MAX] = "", pw[11] = "", vpw[11] = "";//�Է��� �̸���, �Է��� password, ���� password
	char valid, yorn = '\0';//�̸����� Ÿ�缺�� ��� ����, �ٽýõ��� ���� ��� ����
	int i, cor = 0;//�ݺ� ����, correct
	while (1) {
		input(email, pw);//�̸��ϰ� �н����� �Է¹���
		valid = validate_email(email);//�̸����� Ÿ�缺 test
		if (valid == 'n')//�̸����� Ʋ���� �ٽý������� �ʴ� ���� ����, �ٽý��� ������ ��� �ڿ� �ش��ϴ� ������ �����Ƿ� �ڿ������� while �ݺ�
			break;
		else if (valid == 't') {//�̸��� ���� ��
			make_password(vpw, email);//�н����� ����� vpw�� ����
			for (i = 0; i < 10; i++)
				if (pw[i] != vpw[i]) {//�Է��� pw�� ���� pw�� �ٸ� ��
					printf("ERROR! invalid password!\n\n");
					yorn = try_again();//�ٽ�?
					break;
				}
				else cor = 1;//���� ���� �־ cor�� 1�� ���� continue �� ������ if cor==1�� �ɸ��� ����
		}
		if (yorn == 'n')//�ٽ� ���� ���� ���� ��
			break;//while ��������
		else if (yorn == 'y')//�ٽ� ������ ���� �� while �ݺ�
			continue;//�ڿ� ���� �������� ����
		if (cor == 1) {//�̸����� �°� �н����尡 �¾��� ��
			printf("SUCCESS! now you can access HEA system!\n\n");
			return 0;//����
		}
	}
	return 0;//����
}
void input(char email[], char pw[]) {
	printf("---LOGIN TO ACCESS HEA SYSTEM---\n\n");
	printf("email : ");
	scanf("%s", email); FFLUSH;//�̸��� �Է�
	printf("password : ");
	scanf("%s", pw); FFLUSH;//�н����� �Է�
}
int seq_search(char arr[], char word) {
	int i, k = 0;
	if (word == '.') {//������ ���� �Ǵ� �ʿ�(�̸��Ͽ��� . ��� ����)
		k = seq_search(arr, '@');//@�� index
	}
	for (i = k; i < MAX; i++) {//.�� �� @����, @�� �� ó������
		if (arr[i] == word)//word�� ���� ������ ��
			return i;//�� ���� ����(index)
	}
	return 100;//�ش� ���ڰ� ����.
}
char validate_email(char email[]) {
	FILE* alwdom;//allowed_domain ����
	char domain[max] = "";//���� �� �������� ���� string
	int n, i, s, err = 0, j = seq_search(email, '@');//j�� �Է��� �̸��� �� index
	printf("------------CHECKING------------\n");
	alwdom = fopen("allowed_domain.txt", "r");
	fscanf(alwdom, "%d", &n);//�������� ����
	if (j == 100 || j == 0) {//@�� ���� ��||���̵� ���� ��
		printf("ERROR! invalid email format!\n\n");
		return try_again();
	}
	if (subsq(email, '.') >= 50 || //�����ο� ������ .�� ���� ��
		email[seq_search(email, '\0') - 1] == '.' ||//�������� .���� ���� ��
		seq_search(email, '.') == 100 ||//domain�� .�� ���� ��
		seq_search(email, '.') == seq_search(email, '@') + 1) {//�������� .���� ������ ��
		printf("ERROR! invalid domain format!\n\n");
		return try_again();
	}
	while (fscanf(alwdom, "%s", domain) != EOF) {//���� ������
		for (s = j + 1; s < max; s++) {//max���� ���� ����
			if (email[s] == '\0')//�̸��� ������ ��������.(���� �� �Ұ�)
				break;
			if (email[s] != domain[s - (j + 1)]) {//�Է��� @���� ù����!=���� �������� ù����, 0���� �����ؼ� 1�� �����ؾ��ϹǷ� s-(j+1)���
				err += 1;
				break;
			}
		}
	}
	if (err != n - 1) {//err�� �� ���� ��ġ���� �ʾ��� ��//�� �� ��ġ�ϸ� err==n-1
		printf("ERROR! This domain is not allowed!\n\n");
		return try_again();
	}
	return 't';
	fclose(alwdom);
}
char try_again() {//�ٽ� ���� ���� �Ǵ�
	char yorn = '\0';//yes or no?
	printf("Do you want try again? (y/n) ");
	scanf("%c", &yorn); FFLUSH;//�Է¹���
	printf("\n");
	return yorn;
}
int subsq(char arr[], char n) {
	int i, re = 0;
	for (i = seq_search(arr, '@') + 1; i < MAX - 1; i++)//@���� �����κ��� ���� //arr[i]�� arr[i+1]�� ���ؾ��ϱ� ������ MAX-1���
		if (arr[i] == n)//arr[i]�� �Էµ� ������ ��
			re += (arr[i] == arr[i + 1]) ? 50 : 0;//@ ���� ���ӵ� ���������� re�� 50 �߰�
	return re;
}
void make_password(char vpw[], char email[]) {
	int i, s, j = seq_search(email, '@') + 1/*�������� �������� �ε���*/, front = j - 1/*������ ���������κ��� 2��ŭ ���� index����, index+1==����*/,
		tail = seq_search(email, '\0') - j;//������ ���� index==seq_search-1, @�� index==j-1, ���� ���� ���� �������� ����
	if (front <= tail) {//�������� ���̵𺸴� ��ų� ���� ��
		for (i = 0; i < ((front <= 5) ? front : 5); i++)//���̵� 5���ϸ� ���̵��� ���̸�ŭ �ݺ�, 5 �ʰ��� 5��ŭ�� �ݺ�, (��й�ȣ�� 10�ڸ��̱� ����)
			vpw[2 * i] = email[i];//���̵�� �н������� ù��°, 3��° �� Ȧ�� ��ġ ����-> index�� ¦��
		for (i = 0; i < ((front <= 5) ? front : 5); i++)//���� ���
			vpw[2 * i + 1] = email[j + i];//Ȧ�� index�� ������
		for (s = 0; s < 10 - (2 * front); s++) {//���̵� 5���� ���� ������ �н������� ������ �κ��� �����ο��� ä��
			if (email[j + i + s] == '\0')//������ ������ 
				break;//����, 0���� �ʱ�ȭ�Ǿ������Ƿ� ���� pw�� 0
			vpw[2 * front + s] = email[j + i + s];//front�� ª���Ƿ� front�� 2����� ä��������, �������� �������� �� ���� �κп��� ä��
		}
	}
	if (tail < front) {//���� ���� ��� ���
		for (i = 0; i < ((tail <= 5) ? tail : 5); i++)
			vpw[2 * i] = email[i];
		for (i = 0; i < ((tail <= 5) ? tail : 5); i++)
			vpw[2 * i + 1] = email[j + i];
		for (s = 0; s < 10 - (2 * tail); s++) {
			if (email[j + i + s] == '\0')
				break;
			vpw[2 * tail + s] = email[j + i + s];
		}
	}
}