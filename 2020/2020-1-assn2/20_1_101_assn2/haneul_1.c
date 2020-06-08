#include <stdio.h>
#pragma warning (disable:4996)
#define MAX 30
#define max 20
#define FFLUSH while(getchar()!='\n');
void make_password(char vpw[], char email[]);//패스워드 만듦
char validate_email(char email[]);//이메일 타당성 여부 판단
void input(char email[], char pw[]);//이메일 , pw입력받음
int seq_search(char arr[], char n);//배열 내에서 n의 인덱스 찾아줌
char try_again();//다시시작 여부 판단
int subsq(char arr[], char n);//연속된 . 판단

int main() {
	char email[MAX] = "", pw[11] = "", vpw[11] = "";//입력한 이메일, 입력한 password, 실제 password
	char valid, yorn = '\0';//이메일의 타당성을 담는 변수, 다시시도의 값을 담는 변수
	int i, cor = 0;//반복 관련, correct
	while (1) {
		input(email, pw);//이메일과 패스워드 입력받음
		valid = validate_email(email);//이메일의 타당성 test
		if (valid == 'n')//이메일이 틀리고 다시시작하지 않는 것을 선택, 다시시작 선택의 경우 뒤에 해당하는 문장이 없으므로 자연스럽게 while 반복
			break;
		else if (valid == 't') {//이메일 맞을 때
			make_password(vpw, email);//패스워드 만들고 vpw에 저장
			for (i = 0; i < 10; i++)
				if (pw[i] != vpw[i]) {//입력한 pw와 실제 pw가 다를 때
					printf("ERROR! invalid password!\n\n");
					yorn = try_again();//다시?
					break;
				}
				else cor = 1;//같은 값이 있어서 cor에 1이 들어가도 continue 문 때문에 if cor==1에 걸리지 않음
		}
		if (yorn == 'n')//다시 시작 안함 선택 시
			break;//while 빠져나감
		else if (yorn == 'y')//다시 시작함 선택 시 while 반복
			continue;//뒤에 것은 실행하지 않음
		if (cor == 1) {//이메일이 맞고 패스워드가 맞았을 때
			printf("SUCCESS! now you can access HEA system!\n\n");
			return 0;//종료
		}
	}
	return 0;//종료
}
void input(char email[], char pw[]) {
	printf("---LOGIN TO ACCESS HEA SYSTEM---\n\n");
	printf("email : ");
	scanf("%s", email); FFLUSH;//이메일 입력
	printf("password : ");
	scanf("%s", pw); FFLUSH;//패스워드 입력
}
int seq_search(char arr[], char word) {
	int i, k = 0;
	if (word == '.') {//도메인 내부 판단 필요(이메일에는 . 사용 가능)
		k = seq_search(arr, '@');//@의 index
	}
	for (i = k; i < MAX; i++) {//.일 땐 @부터, @일 땐 처음부터
		if (arr[i] == word)//word와 같은 문자일 때
			return i;//그 값을 리턴(index)
	}
	return 100;//해당 문자가 없음.
}
char validate_email(char email[]) {
	FILE* alwdom;//allowed_domain 파일
	char domain[max] = "";//파일 내 도메인을 받을 string
	int n, i, s, err = 0, j = seq_search(email, '@');//j는 입력한 이메일 내 index
	printf("------------CHECKING------------\n");
	alwdom = fopen("allowed_domain.txt", "r");
	fscanf(alwdom, "%d", &n);//도메인의 개수
	if (j == 100 || j == 0) {//@가 없을 때||아이디가 없을 때
		printf("ERROR! invalid email format!\n\n");
		return try_again();
	}
	if (subsq(email, '.') >= 50 || //도메인에 연속한 .이 있을 때
		email[seq_search(email, '\0') - 1] == '.' ||//도메인이 .으로 끝날 때
		seq_search(email, '.') == 100 ||//domain에 .이 없을 때
		seq_search(email, '.') == seq_search(email, '@') + 1) {//도메인이 .으로 시작할 때
		printf("ERROR! invalid domain format!\n\n");
		return try_again();
	}
	while (fscanf(alwdom, "%s", domain) != EOF) {//파일 끝까지
		for (s = j + 1; s < max; s++) {//max길이 까지 존재
			if (email[s] == '\0')//이메일 끝나면 빠져나감.(이후 비교 불가)
				break;
			if (email[s] != domain[s - (j + 1)]) {//입력한 @이후 첫글자!=허용된 도메인의 첫글자, 0부터 시작해서 1씩 증가해야하므로 s-(j+1)사용
				err += 1;
				break;
			}
		}
	}
	if (err != n - 1) {//err가 한 번도 일치하지 않았을 때//한 번 일치하면 err==n-1
		printf("ERROR! This domain is not allowed!\n\n");
		return try_again();
	}
	return 't';
	fclose(alwdom);
}
char try_again() {//다시 시작 여부 판단
	char yorn = '\0';//yes or no?
	printf("Do you want try again? (y/n) ");
	scanf("%c", &yorn); FFLUSH;//입력받음
	printf("\n");
	return yorn;
}
int subsq(char arr[], char n) {
	int i, re = 0;
	for (i = seq_search(arr, '@') + 1; i < MAX - 1; i++)//@이후 도메인부터 시작 //arr[i]와 arr[i+1]을 비교해야하기 때문에 MAX-1사용
		if (arr[i] == n)//arr[i]가 입력된 워드일 때
			re += (arr[i] == arr[i + 1]) ? 50 : 0;//@ 이후 연속된 워드있으면 re에 50 추가
	return re;
}
void make_password(char vpw[], char email[]) {
	int i, s, j = seq_search(email, '@') + 1/*도메인의 시작점의 인덱스*/, front = j - 1/*도메인 시작점으로부터 2만큼 적은 index가짐, index+1==개수*/,
		tail = seq_search(email, '\0') - j;//도메인 끝의 index==seq_search-1, @의 index==j-1, 따라서 둘을 빼면 도메인의 길이
	if (front <= tail) {//도메인이 아이디보다 길거나 같을 때
		for (i = 0; i < ((front <= 5) ? front : 5); i++)//아이디가 5이하면 아이디의 길이만큼 반복, 5 초과면 5만큼만 반복, (비밀번호가 10자리이기 때문)
			vpw[2 * i] = email[i];//아이디는 패스워드의 첫번째, 3번째 등 홀수 위치 차지-> index는 짝수
		for (i = 0; i < ((front <= 5) ? front : 5); i++)//같은 방식
			vpw[2 * i + 1] = email[j + i];//홀수 index엔 도메인
		for (s = 0; s < 10 - (2 * front); s++) {//아이디가 5개가 되지 않으면 패스워드의 나머지 부분은 도메인에서 채움
			if (email[j + i + s] == '\0')//도메인 끝나면 
				break;//끝냄, 0으로 초기화되어있으므로 남은 pw는 0
			vpw[2 * front + s] = email[j + i + s];//front가 짧으므로 front의 2배까지 채워져있음, 나머지는 도메인의 안 쓰인 부분에서 채움
		}
	}
	if (tail < front) {//위와 같은 방식 사용
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