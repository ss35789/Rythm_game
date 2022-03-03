#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>

#include<memory.h>

#define ALLNOTE 1000

// �Ҹ� ��� PlaySound�Լ�
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
//PlaySound(TEXT("Festival_of_Ghost.wav"), NULL, SND_ASYNC | SND_LOOP);
#include "music1.h"
#include "music2.h"
#include "music3.h"
// ���� ����

#define BLACK 0
#define BLUE1 1
#define GREEN1 2
#define CYAN1 3
#define RED1 4
#define MAGENTA1 5
#define YELLOW1 6
#define GRAY1 7
#define GRAY2 8
#define BLUE2 9
#define GREEN2 10
#define CYAN2 11
#define RED2 12
#define MAGENTA2 13
#define YELLOW2 14
#define WHITE 15
#define ESC 0x1b


#define UP  0x48 // Up key�� 0xe0 + 0x48 �ΰ��� ���� ���´�.
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

#define ENTER 13
#define ESC 0x1b //  ESC ������ ����

int Bmusic;
int score = 0;
int speed = 150;
int Mcombo = 0;
char name[20];




int combo = 0;
int height;
char arr[20];
void record(int Score) {
	char* arr[20];
	// ���� ���� �Է�
	FILE *fp = fopen("record.txt", "w");
	fscanf(fp, "%s  :", arr);
	fprintf(fp, "%d\n", Score);
	fclose(fp);
}


void gotoxy(int x, int y) //���� ���ϴ� ��ġ�� Ŀ�� �̵�

{

	COORD pos; // Windows.h �� ����

	pos.X = x;

	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}




void textcolor(int fg_color, int bg_color)

{

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);

}



void removeCursor(void) { // Ŀ���� �Ⱥ��̰� �Ѵ�

	CONSOLE_CURSOR_INFO curInfo;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	curInfo.bVisible = 0;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

}

void showCursor(void) { // Ŀ���� ���̰� �Ѵ�

	CONSOLE_CURSOR_INFO curInfo;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	curInfo.bVisible = 1;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

}

void cls(int bg_color, int text_color) // ȭ�� �����

{

	char cmd[100];

	system("cls");

	sprintf(cmd, "COLOR %x%x", bg_color, text_color);

	system(cmd);

}
void eraseSelect(int x, int y)
{
	gotoxy(x, y); printf(" ");

}
void drawSelect(int x, int y)
{

	gotoxy(x, y); printf("��");



}



// box �׸��� �Լ�, ch ���ڷ� (x1,y1) ~ (x2,y2) box�� �׸���.

void draw_box(int x1, int y1, int x2, int y2, char ch)

{

	int x, y;

	// �ϼ��� �� ������ �� ��

	y = y1;

	for (x = x1; x <= x2; x++) {

		gotoxy(x, y);

		printf("%c", ch);

	}

	x = x1;

	for (y = y1; y <= y2; y++) {

		gotoxy(x, y);

		printf("%c", ch);

	}

	y = y2;

	for (x = x1; x <= x2; x++) {

		gotoxy(x, y);

		printf("%c", ch);

	}

	x = x2;

	for (y = y1; y <= y2; y++) {

		gotoxy(x, y);

		printf("%c", ch);

	}

}
void gm_mo() {
	cls(BLACK, CYAN2);
	draw_box(10, 2, 50, 22, '-');
	for (int x = 20; x <= 40; x += 10) {
		for (int y = 20; y < 22; y++) {
			gotoxy(x, y);
			printf("|");
		}
	}
	


	for (int i = 11; i < 50; i++) {
		gotoxy(i, 20);
		printf("��");
	}
	gotoxy(15, 21); printf("Q");
	gotoxy(25, 21); printf("W");
	gotoxy(35, 21); printf("E");
	gotoxy(45, 21); printf("R");
	
	gotoxy(57, 5); printf("����:%d", score);
	gotoxy(3, 18); printf("Hit!! ->");
	gotoxy(57, 10); printf("Combo:%d", combo);
	gotoxy(57, 12); printf("Max Combo:%d", Mcombo);
	gotoxy(61, 21);	printf("P  : ���� ����");
	gotoxy(60, 23);	printf("ESC : ����");

}

int music_select( int color) {
	int i, x, y, nowy = 13;
	
	char ch;
	cls(BLACK, color);// ������ �ؽ�Ʈ ���� ����

	textcolor(color, BLACK);
	gotoxy(11, 2);
	printf("       #####    #####    ##    #####    #####    #####"); Sleep(150);
	gotoxy(11, 3);
	printf("      #        #        ##    #        #          #  "); Sleep(150);
	gotoxy(11, 4);
	printf("     #####    #####    ##    #####    #          #  "); Sleep(150);
	gotoxy(11, 5);
	printf("        #    #        ##    #        #          #  "); Sleep(150);
	gotoxy(11, 6);
	printf("   #####    #####    ##    #####    #####      #  "); Sleep(150);

	textcolor(CYAN2, BLACK);
	gotoxy(38, 23);
	printf("Enter: Select music   ��: UP   ��: DOWN");
	gotoxy(18, 10);
	printf(" < SELECT MUSIC NUMBER >"); Sleep(150);
	gotoxy(19, 13);
	printf("1. Believer - Imagine Dragons"); Sleep(150);
	gotoxy(19, 15);
	printf("2. 2002 - Anne Marie"); Sleep(150);
	gotoxy(19, 17);
	printf("3. thank u, next - Ariana Grande"); Sleep(150);


	while (1) {
		if (kbhit() == 1) {
			ch = getch();
			if (ch == UP || ch == DOWN) {
				if (nowy == 13)
				{
					if (ch == UP)//3
					{
						eraseSelect(15, nowy);
						nowy = 17;
						drawSelect(15, nowy); PlaySound(TEXT("thank_u_next.wav"), NULL, SND_ASYNC | SND_LOOP);

					}
					else if (ch == DOWN) {//2
						eraseSelect(15, nowy);
						nowy += 2;
						drawSelect(15, nowy); PlaySound(TEXT("2002.wav"), NULL, SND_ASYNC | SND_LOOP);

					}
				}
				else if (nowy == 15) {
					if (ch == UP)//1
					{
						eraseSelect(15, nowy);
						nowy -= 2;
						drawSelect(15, nowy); PlaySound(TEXT("believer.wav"), NULL, SND_ASYNC | SND_LOOP);

					}
					else if (ch == DOWN) {//3
						eraseSelect(15, nowy);
						nowy += 2;
						drawSelect(15, nowy); PlaySound(TEXT("thank_u_next.wav"), NULL, SND_ASYNC | SND_LOOP);

					}
				}
				else if (nowy == 17) {
					if (ch == UP)//2
					{
						eraseSelect(15, nowy);
						nowy -= 2;
						drawSelect(15, nowy); PlaySound(TEXT("2002.wav"), NULL, SND_ASYNC | SND_LOOP);

					}
					else if (ch == DOWN) {//1
						eraseSelect(15, nowy);
						nowy = 13;
						drawSelect(15, nowy); PlaySound(TEXT("believer.wav"), NULL, SND_ASYNC | SND_LOOP);

					}
				}
			}
			else if (ch == ENTER) {
				if (nowy == 13) {
					
					Bmusic = 1;
					break;
				}
				else if (nowy == 15) {
					
					Bmusic = 2;
					break;
				}
				else if (nowy == 17) {
					
					Bmusic = 3;
					break;
				}
			}
			/*MUSIC_N = getch();
			MUSIC_N = MUSIC_N - '0';*/


		}


	}
	return Bmusic;
}
void move_Node(char *music[100000]) {
	int h = 4, x = 13;
	int jud = 0;
	char ch;
	PlaySound(TEXT("Nosound.wav"), NULL, SND_ASYNC | SND_LOOP);
	gotoxy(58, 15); printf("������");
	gotoxy(58, 16); printf("        ��");
	gotoxy(58, 17); printf("������");
	gotoxy(58, 18); printf("        ��");
	gotoxy(58, 19); printf("������");
	Sleep(650);
	gotoxy(58, 15); printf("          ");
	gotoxy(58, 16); printf("          ");
	gotoxy(58, 17); printf("          ");
	gotoxy(58, 18); printf("          ");
	gotoxy(58, 19); printf("          ");

	gotoxy(58, 15); printf("������");
	gotoxy(58, 16); printf("        ��");
	gotoxy(58, 17); printf("������");
	gotoxy(58, 18); printf("��        ");
	gotoxy(58, 19); printf("������");
	Sleep(650);
	gotoxy(58, 15); printf("          ");
	gotoxy(58, 16); printf("          ");
	gotoxy(58, 17); printf("          ");
	gotoxy(58, 18); printf("          ");
	gotoxy(58, 19); printf("          ");
	gotoxy(57, 15); printf("    ��    ");
	gotoxy(57, 16); printf("  ���    ");
	gotoxy(57, 17); printf("    ��    ");
	gotoxy(57, 18); printf("    ��    ");
	gotoxy(57, 19); printf("  ����  ");
	Sleep(650);
	gotoxy(58, 15); printf("          ");
	gotoxy(58, 16); printf("          ");
	gotoxy(58, 17); printf("          ");
	gotoxy(58, 18); printf("          ");
	gotoxy(58, 19); printf("          ");

	
	if (Bmusic == 1) {
		PlaySound(TEXT("believer.wav"), NULL, SND_ASYNC | SND_LOOP);
	}
	else if (Bmusic == 2) {
		PlaySound(TEXT("2002.wav"), NULL, SND_ASYNC | SND_LOOP);
	}
	else if (Bmusic == 3) {
		PlaySound(TEXT("thank_u_next.wav"), NULL, SND_ASYNC | SND_LOOP);
	}
	
	
		
		
		
		for (int j = 0; j <= 1000000; j++) {
			
			

			
				for (int i = 0; i <= j; i++) {
					
					gotoxy(x, h + i);
					
					if (h + i >=20 ) {
						break;
					}
					


					height = j - i;
					printf("%s", music[j - i]); jud++;
					
					
				}
				for (int k = 0; k < 10; k++) {//��Ʈ�����ð��� �ø����� �ݺ����� ���
					if (kbhit() == 1) {
						ch = getch();
						if (jud>=16&&music[height] == "����                              "&& ch == 'q') {
							score += 100;
							 gotoxy(57, 5); printf("����:%d", score);
							 gotoxy(57, 10); printf("                       ");
							 combo += 1; gotoxy(57, 10); printf("Combo:%d", combo);
							 if (Mcombo <= combo) { Mcombo = combo; gotoxy(57, 12); printf("Max Combo:%d", Mcombo); }
							 gotoxy(57, 8); printf("               ");
							gotoxy(57, 8); printf("��Perfect��"); 

						}
						else if (jud >= 16 && music[height] == "          ����                    "&& ch == 'w') {
							score += 100; gotoxy(57, 5); printf("����:%d", score);
							gotoxy(57, 10); printf("                       ");
							combo += 1; gotoxy(57, 10); printf("Combo:%d", combo);
							if (Mcombo <= combo) { Mcombo = combo; gotoxy(57, 12); printf("Max Combo:%d", Mcombo); }
							gotoxy(57, 8); printf("               ");
							gotoxy(57, 8); printf("��Perfect��"); 
						}
						
						else if (jud >= 16 && music[height] == "                    ����          "&& ch == 'e') {
							score += 100;  gotoxy(57, 5); printf("����:%d", score);
							gotoxy(57, 10); printf("                       ");
							combo += 1; gotoxy(57, 10); printf("Combo:%d", combo);
							if (Mcombo <= combo) { Mcombo = combo; gotoxy(57, 12); printf("Max Combo:%d", Mcombo); }
							gotoxy(57, 8); printf("               ");
							gotoxy(57, 8); printf("��Perfect��"); 
						}
						
						else if (jud >= 16 && music[height] == "                              ����"&& ch == 'r') {
							score += 100;  gotoxy(57, 5); printf("����:%d", score);
							gotoxy(57, 10); printf("                       ");
							combo += 1; gotoxy(57, 10); printf("Combo:%d", combo);
							if (Mcombo <= combo) { Mcombo = combo; gotoxy(57, 12); printf("Max Combo:%d", Mcombo); }
							gotoxy(57, 8); printf("               ");
							gotoxy(57, 8); printf("��Perfect��"); 
						}
						else if (ch == ESC) {
							cls(BLACK, CYAN2);
							while (1) {
								gotoxy(28, 10);
								printf("������ ����Ͻðڽ��ϱ�?");
								gotoxy(30, 15);
								printf("Y/N");
								if (kbhit() == 1) {
									char ans;
									ans = getch();

									if (ans == 'y') {
										cls(BLACK, CYAN2);
										gotoxy(28, 8);
										printf("�̸��� �Է����ּ���\n");

										FILE *fp = fopen("record.txt", "a");


										gotoxy(28, 10);
										scanf("%s", name);


										fprintf(fp, "%s: %d ", name, score);




										fclose(fp);
										cls(BLACK,CYAN2);
										gotoxy(28, 10);
										printf("������ �����մϴ�.");
										getch();
										exit(1);


									}
									else if (ans == 'n') {

										cls(CYAN2, BLACK);
										gotoxy(28, 10);
										printf("������ �����մϴ�.");
										getch();
										exit(1);

									}
								}
							}

							getch();
							exit(1);
						}
						else if (ch == 'p') {
							PlaySound(TEXT("Nosound.wav"), NULL, SND_ASYNC | SND_LOOP);
							Bmusic = 0;
							music_select(CYAN2);
							gm_mo();

							if (Bmusic == 1) {
								move_Node(music1);
							}
							else if (Bmusic == 2) {

								move_Node(music2);


							}
							else if (Bmusic == 3) {

								move_Node(music3);


							}


							getch();
						}
						

						
						else {
							gotoxy(57, 8); printf("               ");
							gotoxy(57, 8); printf("SO UGLY");
							combo = 0;
							gotoxy(57, 10); printf("Combo:%d", combo);
						}
						
						

					}

					


					ch = NULL;
			}
			jud = 0;
			Sleep(100);

				
			for (int u = 0; u <= j; u++) {
				gotoxy(x, h + u);
				if (h + u > 19) {
					break;
				}
				printf("                                    ");
				



			}
			

		
		}
		cls(BLACK, CYAN2);
		

		while (1) {
			gotoxy(28, 10);
			printf("������ ����Ͻðڽ��ϱ�?");
			gotoxy(30, 15);
			printf("Y/N");
			if (kbhit() == 1) {
				char ans;
				ans = getch();
				
				if (ans == 'y') {
					cls(BLACK, CYAN2);
					gotoxy(28, 8);
					printf("�̸��� �Է����ּ���\n");
					
					FILE *fp = fopen("record.txt", "a");
				
					
						gotoxy(28, 10);
						scanf("%s", name);

						
						 fprintf(fp, "\n%s: %d ", name, score);
						
					
					

						 fclose(fp);
						 cls(BLACK, CYAN2);
						 gotoxy(28, 10);
						 printf("������ �����մϴ�.");
						 getch(); 
						 exit(1);
						

				}
				else if (ans == 'n') {

					cls(BLACK, CYAN2);
					gotoxy(28, 10);
					printf("������ �����մϴ�.");
					getch();
					exit(1);

				}
			}
		}

		
	
}
//void music_play(int MUSIC_N) {
// //�뷡���
//}
void game_start() {

	if (Bmusic == 1) {
		move_Node(music1);
	}
	else if (Bmusic == 2) {

		move_Node(music2);


	}
	else if (Bmusic == 3) {

		move_Node(music3);


	}
}


void  game_basic_MUSICNUMBER() {
	int i, x, y, color = 1,nowy=13;
	int MUSIC_N;
	char ch;
	cls(BLACK, CYAN2);// ������ �ؽ�Ʈ ���� ����
	removeCursor();
	PlaySound(TEXT("opening.wav"), NULL, SND_ASYNC | SND_LOOP);

	gotoxy(2, 0);
	printf("  ����������������������������������������������������������������������������������������������������������������������������������������������"); Sleep(100);
	gotoxy(2, 2);
	printf("       ####    ####   #         #      #######     #######        #####      "); Sleep(150);
	gotoxy(2, 3);
	printf("      ## ##   # ##   #         #    ##              ##       ####      ##    "); Sleep(150);
	gotoxy(2, 4);
	printf("     ## ##  #  ##   #         #       ####         ##     ####               "); Sleep(150);
	gotoxy(2, 5);
	printf("    ## ##  #  ##    #        #           ##      ##        ####     ##       "); Sleep(150);
	gotoxy(2, 6);
	printf("   ##   ###  ##      #######     #######     #######          #####          "); Sleep(150);
	gotoxy(2, 8);
	printf("  ����������������������������������������������������������������������������������������������������������������������������������������������"); Sleep(100);


	gotoxy(29, 16);

	printf("�� Q,W,E,R : Node�� ");
	gotoxy(29, 18);
	printf("�� P : Select music ");
	gotoxy(29, 20);

	printf("�� ESC : Quit ");

	 
	while (1) {

		textcolor(color, BLACK);


		gotoxy(2, 2);
		printf("       ####    ####   #         #      #######     #######        #####          "); Sleep(150);
		gotoxy(2, 3);
		printf("      ## ##   # ##   #         #    ##              ##       ####      ##        "); Sleep(150);
		gotoxy(2, 4);
		printf("     ## ##  #  ##   #         #       ####         ##     ####                   "); Sleep(150);
		gotoxy(2, 5);
		printf("    ## ##  #  ##    #        #           ##      ##        ####     ##           "); Sleep(150);
		gotoxy(2, 6);
		printf("   ##   ###  ##      #######     #######     #######          #####              "); Sleep(150);



		gotoxy(25, 11);
		textcolor(15 - color, BLACK);
		printf(" < PRESS ANY KEY TO START >");

		if (kbhit() == 1) {
			getch();
			
			break;
		}

		Sleep(200);
		color++;
		if (color > 15)color = 1;
	}


	
	
	

	
}


void main()

{
	game_basic_MUSICNUMBER();
	music_select(CYAN2);
	gm_mo();
	game_start();
	

	getch();
}
// �ؾ��� ��
//    1.Ű���� �Է�
//    2.������ ������ �ϰ� ������ �뷡�� ������ ������ �����ұ�?
//    3.�߰��� ���ߴ� ����� ������ ������ �־��.
//    4.�޺��� �ʿ��ҵ��ϴ�.
