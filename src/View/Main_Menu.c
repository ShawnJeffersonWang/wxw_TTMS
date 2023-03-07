#include "MaiAccount_UI.h"
#include "../View/Main_Menu.h"
#include "SalesAnalysis_UI.h"
#include <stdio.h>
#include "StaSales_UI.h"
#include "../View/Studio_UI.h"
char ch0;
// 维护个人资料
void Main_Menu(void)
{
	if (SysLogin() == 0)
	{
		return;
	}

	char choice;
	do
	{
		system("clear");
		printf("\n==================================================================\n");
		printf("********************** TTMS剧院票务管理系统 **********************\n");
		printf("[S]管理演出厅.\n");
		printf("[P]管理剧目.\n");
		printf("[T]售票.\n");
		printf("[I]查询演出.\n");
		printf("[R]退票.\n");
		printf("[L]统计销售额\n");
		printf("[Q]统计票房.\n");
		printf("[A]系统管理员\n");
		printf("[M]维护个人资料\n");
		printf("[E]退出.\n");
		printf("====================================================================\n");
		printf("请输入你的选择:");
		choice = getchar();
		while ((ch0 = getchar()) != '\n')
			;
		switch (choice)
		{
		case 'S':
		case 's':
			Studio_UI_MgtEntry();
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry();
			break;
		case 'I':
		case 'i':
			Schedule_UI_ListAll();
			break;
		case 'T':
		case 't':
			Sale_UI_MgtEntry();
			break;
		case 'R':
		case 'r':
			Sale_UI_ReturnTicket();
			break;
		case 'L':
		case 'l':
			StaSales_UI_MgtEntry();
			break;
		case 'Q':
		case 'q':
			SalesAanalysis_UI_MgtEntry();
			break;
		case 'A':
		case 'a':
			Account_UI_MgtEntry();
			break;
		case 'M':
		case 'm':
			MaiAccount_UI_MgtEntry();
			break;
		}

	} while ('E' != choice && 'e' != choice);
	
	return;
}
