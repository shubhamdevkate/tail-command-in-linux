#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "stack.c"

int flag = 0;
char ip[1024];

/* functions for tail command */

void copy(int x) {
	flag = x;
}

void resetflag(){
	flag = 0;
}

//prints last 'n' bytes from file
int t_nbyte(char *file, int n){
	FILE *fp;
	long int len;
	char ch;

	fp = fopen(file, "r");

	if(fp == NULL){
		printf("\nCan't open %s file !!!\n", file);
		return -1;
	}

	if(n != -1){
		fseek(fp, 0, SEEK_END);
		len = ftell(fp);
		fseek(fp, (len - n), SEEK_SET);
	}

	do{
		ch = fgetc(fp);
		if(ch != EOF)
			putchar(ch);

	}while(ch != EOF);

	fclose(fp);
}

//prints last 'n' lines from file
int t_nlines(char *file, int n){
	FILE *fp;
	int cnt = 0, sum = 0, i = 0, d, c, tot;

	fp = fopen(file, "r");

	if(fp == NULL){
		printf("\nCan't open %s file !!!\n", file);
		return -1;
	}

	init();

	do{	
		c = fgetc(fp);

		if(feof(fp))
			break;

		cnt++;
		if(c == '\n'){

			push(cnt);
			cnt = 0;
		}

	}while(1);

	while(i < n){
		d = pop();
		sum = sum + d;
		i++;		
	}

	tot = ftell(fp);
	fseek(fp, (tot - sum), SEEK_SET);

	do{	
		c = fgetc(fp);
		if(feof(fp))
			break;
		printf("%c", c);
	}while(1);
	fclose(fp);
}

//copy last 'n' number of lines from src and paste or append to  target file
int t_copyline(char *src, int n, char *target){
	FILE *fp1, *fp2;
	int cnt = 0, sum = 0, i = 0, d, c, tot;


	fp1 = fopen(src, "r");

	if(fp1 == NULL){
		printf("\nCan't open %s file !!!\n", src);
		return -1;
	}

	if(flag == 1)
		fp2 = fopen(target, "a");
	else
		fp2 = fopen(target, "w");

	if(fp2 == NULL){
		printf("\nCan't open %s file !!!\n", target);
		return -1;
	}

	init();

	do{
		c = fgetc(fp1);

		if(feof(fp1))
			break;

		cnt++;
		if(c == '\n'){

			push(cnt);
			cnt = 0;
		}

	}while(1);

	while(i < n){
		d = pop();
		sum = sum + d;
		i++;
	}

	tot = ftell(fp1);
	fseek(fp1, (tot - sum), SEEK_SET);

	do{
		c = fgetc(fp1);
		if(feof(fp1))
			break;
		fwrite(&c, 1, 1, fp2);
	}while(1);

	resetflag();
	fclose(fp1);
	fclose(fp2);
}

//copy last 'n' number of bytes from src and paste or append to target file
int t_copybyte(char *src, int n, char *target){
	FILE *fp1, *fp2;
	long int len;
	char ch;

	fp1 = fopen(src, "r");

	if(fp1 == NULL){
		printf("\nCan't open %s file !!!\n", src);
		return -1;
	}

	if(flag == 1)
		fp2 = fopen(target, "a");
	else
		fp2 = fopen(target, "w");

	if(fp2 == NULL){
		printf("\nCan't open %s file !!!\n", target);
		return -1;
	}



	fseek(fp1, 0, SEEK_END);
	len = ftell(fp1);
	fseek(fp1, (len - n), SEEK_SET);


	do{
		ch = fgetc(fp1);
		fwrite(&ch, 1, 1, fp2);

	}while(ch != EOF);

	resetflag();
	fclose(fp1);
	fclose(fp2);

}

//if user do not mention filename, this function invokes
void input(){

	while(1){
		scanf("%s", ip);
		if(flag != 1){
			printf("%s", ip);
			printf("\n");
		}
	}

	resetflag();
}

//implement -z option, print all file
int printfile(char *file){
	FILE *fp;
	char ch;

	fp = fopen(file, "r");

	if(fp == NULL){
		printf("\nCan't open %s file !!!\n", file);
		return -1;
	}

	do{
		ch = fgetc(fp);
		if(ch != EOF)
			putchar(ch);
	}while(ch != EOF);

}

