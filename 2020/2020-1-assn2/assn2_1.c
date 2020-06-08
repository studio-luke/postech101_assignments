/* Started  at 01:17 AM, 5/23/2020 
 * Finished at 02:21 AM, 5/23/2020
 * Code by Studio-Luke
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LEN		30
#define MAX_PW_LEN			30
#define MAX_DOMAIN_LEN		20
#define MAX_ALLOWED_DOMAIN	20

#define FFLUSH while(getchar() != '\n')

char* make_password(char* email) {
	char pw[11] = "";
	char* sep = strchr(email, '@');
	char* domain = sep + 1;

	int id_len = sep - email, do_len = strlen(domain);
	int placeholder = 0;

	for (int i = 0; placeholder < 10; i++) {
		if (i < id_len) pw[placeholder++] = email[i];
		if (i < do_len) pw[placeholder++] = domain[i];
		if (i >= id_len && i >= do_len) break;
	}
	if (placeholder < 10)
		for (int i = placeholder; i < 10; i++)
			pw[i] = '0';
	pw[10] = '\0';

	return pw;
}

int validate_email(char* email) {
	FILE* f;
	char* sep, * domain, *dot;
	int is_dot_exist = 0;
	int num_domain;
	char allowed_domain[MAX_DOMAIN_LEN];

	sep = strchr(email, '@');
	if (sep == NULL)  return 0;				// @ doesn't exist
	if (sep == email) return 0;				// id doesn't exist
	domain = sep + 1;

	sep += 1;
	while (1) {
		if (!strcmp(sep, "")) return 0;		// Text not exist after a dot
		
		dot = strchr(sep, '.');
		if (dot != NULL)						is_dot_exist = 1;
		else if (dot == NULL && !is_dot_exist)	return 0;	// Dot never exists
		else									break;	// Dot appeared more than once and finished
		
		if (sep == dot)		return 0;
		sep = dot + 1;
	}

	f = fopen("allowed_domain.txt", "r");
	fscanf(f, "%d", &num_domain);

	for (int i = 0; i < num_domain; i++) {
		fscanf(f, "%s", allowed_domain);
		if (!strcmp(domain, allowed_domain))
			return 1;
	}
	
	return -1;	// Domain not allowed
	
}

int main()
{
	char email[MAX_EMAIL_LEN], pw[MAX_PW_LEN];
	int validation;
	char cont;

	while (1) {
		printf("\n---LOGIN TO ACCESS HEA SYSTEM---\n\n");
		printf("email : ");
		scanf("%s", email); FFLUSH;
		printf("password : ");
		scanf("%s", pw); FFLUSH;

		printf("\n------------CHECKING------------\n\n");
		validation = validate_email(email);
		if (validation == 0)			printf("ERROR! invalid email format!\n");
		else if (validation == -1)		printf("ERROR! This domain is not allowed!\n");
		else {
			if (!strcmp(pw, make_password(email))) {
				printf("SUCCESS! now you can access HEA system!\n");
				break;
			}
			else						printf("ERROR! invalied password!\n");
		}

		printf("\nDo you want try again? (y/n) ");
		scanf("%c", &cont); FFLUSH;
		if		(cont == 'y' || cont == 'Y') continue;
		else if (cont == 'n' || cont == 'N') break;
	}

	printf("\nPress Enter to quit...\n"); FFLUSH;
	return 0;
}