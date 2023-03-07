#include "../Common/list.h"
#include "../Common/time.h"
#include "../Service/Play.h"
#include "../Service/Account.h"
#include "../Service/Schedule.h"
#include <stdio.h>

char ch;
static const int PLAY_PAGE_SIZE = 5;
extern account_t gl_CurUser;
// 03管理剧目
void Play_UI_MgtEntry(void)
{
	if (gl_CurUser.type == USR_ADMIN)
	{
		printf("you can't join in there!please input the [Enter]");
		getchar();
		return;
	}

	int i, id;
	char choice;
	// Play_UI_screen();
	play_list_t head;
	play_node_t *pos;
	Pagination_t paging;

	List_Init(head, play_node_t);
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;

	paging.totalRecords = Play_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	do
	{
		system("clear");
		printf(
			"\n=======================================================================================================\n");
		printf(
			"******************************************** 剧目列表 *************************************************\n");
		printf("%-5s %-20s      %5s %10s %3s %3s %10s %10s     %3s\n", "ID", "NAME", "TYPE", "AREA", "RATING", "DURATION", "STARTDATA", "ENDDATA", "PRICE");

		printf("-------------------------------------------------------------------------------------------------------\n");

		Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i)
		{
			printf("%-5d %-25s %5d %10s %6d %6d %7d%3d%3d %4d%3d%3d     %4d\n", pos->data.id, pos->data.name, pos->data.type, pos->data.area, pos->data.rating, pos->data.duration, pos->data.start_date.year, pos->data.start_date.month, pos->data.start_date.day, pos->data.end_date.year, pos->data.end_date.month, pos->data.end_date.day, pos->data.price);
		}

		printf("-----------------Total Recoeds: %2d---------------------------------------------Page %2d/%2d   -----------\n", paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));

		printf("*******************************************************************************************************\n");

		printf("[P]revPage|[N]extPage | [A]dd|[D]elete|[U]pdate | [S]earch | [F]ind | [R]eturn");
		printf("\n=======================================================================================================\n");
		printf("your choice: ");
		scanf("%c", &choice);

		while ((ch = getchar()) != '\n')
			;

		switch (choice)
		{
		case 'a':
		case 'A':
			setbuf(stdin, NULL);
			if (Play_UI_Add())
			{
				paging.totalRecords = Play_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, play_node_t);
			}
			break;
		case 'd':
		case 'D':
			printf("演出ID:");
			scanf("%d", &id);
			while ((ch = getchar()) != '\n')
				;
			if (Play_UI_Delete(id))
			{
				paging.totalRecords = Play_Srv_FetchAll(head);
				List_Paging(head, paging, play_node_t);
			}
			break;
		case 'u':
		case 'U':
			printf("演出ID:");
			scanf("%d", &id);
			while ((ch = getchar()) != '\n')
				;
			if (Play_UI_Modify(id))
			{
				paging.totalRecords = Play_Srv_FetchAll(head);
				List_Paging(head, paging, play_node_t);
			}
			break;
		case 's':
		case 'S':
			printf("演出ID:");
			scanf("%d", &id);
			while ((ch = getchar()) != '\n')
				;
			if (Play_UI_Query(id))
			{
				paging.totalRecords = Play_Srv_FetchAll(head);
				List_Paging(head, paging, play_node_t);
			}
			break;
		case 'f':
		case 'F':
			printf("请输入演出ID:");
			scanf("%d", &id);
			getchar();
			Schedule_UI_MgtEntry(id);
			break;
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');

	List_Destroy(head, play_node_t);
}

int Play_UI_Add(void)
{

	play_t rec;
	int newRecCount = 0;
	char choice;
	system("clear");
	do
	{
		if (gl_CurUser.type != USR_MANG)
		{
			printf("you can't join in there!please input the [Enter]");
			getchar();
			return 0;
		}
		printf("\n=======================================================================================\n");
		printf("************************************添加新演出***************************************\n");
		printf("---------------------------------------------------------------------------------------\n");
		printf("请在下方输入添加的演出信息.\n");
		printf("演出名称 : ");
		scanf("%s", rec.name);
		printf("演出类型  (1 电影 || 2 戏剧 || 3  演唱会) : ");
		scanf("%d", &(rec.type));
		getchar();
		printf("上映地区 : ");
		scanf("%s", rec.area);
		printf("演出等级  (1 or 2 or 3) : ");
		scanf("%d", &rec.rating);
		getchar();
		printf("演出持续时间 :");
		scanf("%d", &rec.duration);
		getchar();

		while (1)
		{
			while (1)
			{
				printf("演出开始于? : ");
				scanf("%d%d%d", &rec.start_date.year, &rec.start_date.month, &rec.start_date.day);
				getchar();
				if (time_judge(rec.start_date.year, rec.start_date.month, rec.start_date.day))
				{
					break;
				}
			}
			while (1)
			{
				printf("演出结束于? : ");
				scanf("%d%d%d", &rec.end_date.year, &rec.end_date.month, &rec.end_date.day);
				getchar();
				if (time_judge(rec.end_date.year, rec.end_date.month, rec.end_date.day))
				{
					break;
				}
			}

			if ((rec.end_date.year >= rec.start_date.year && rec.end_date.month >= rec.start_date.month && rec.end_date.day >= rec.start_date.day) ||
				(rec.end_date.year > rec.start_date.year) ||
				(rec.end_date.year >= rec.start_date.year && rec.end_date.month > rec.start_date.month))
			{
				break;
			}
			else
			{
				printf("输入时间错误!\n请重试\n");
			}
		}

		printf("演出票价 :");
		scanf("%d", &rec.price);
		printf("=======================================================================================\n");
		if (Play_Srv_Add(&rec))
		{
			newRecCount += 1;
			printf("添加成功!\n");
		}
		else
			printf("添加失败! \n");

		printf("---------------------------------------------------------------------------------------\n");

		printf("[A]dd more,[R]eturn :");
		scanf("%c", &choice);
		getchar();
	} while ('a' == choice || 'A' == choice);

	return newRecCount;
}

int Play_UI_Delete(int id)
{
	if (gl_CurUser.type != USR_MANG)
	{
		printf("you can't join in there!please input the [Enter]");
		getchar();
		return 0;
	}

	int rtn = 0;

	if (Play_Srv_DeleteByID(id))
	{
		printf(" the play deleted successfully!\n");
	}
	else
	{
		printf("the play deleted faile!\n");
	}
	return 0;
}

int Play_UI_Modify(int id)
{
	if (gl_CurUser.type != USR_MANG)
	{
		printf("you can't join in there!please input the [Enter]");
		getchar();
		return 0;
	}
	play_t rec;
	play_t data;
	int rtn = 0;

	if (!Play_Srv_FetchByID(id, &rec))
	{
		printf("the play does not exist!\npPress [Enter] key to return !\n");
		getchar();
		return 0;
	}

	system("clear");
	printf("=======================================================================================\n");
	printf("*******************************更新演出信息 ****************************\n");
	printf("---------------------------------------------------------------------------------------\n");
	printf("play  id :  %d\n", rec.id);
	printf("请在下方输入添加的演出信息.\n");
	printf("演出名称: ");
	scanf("%s", rec.name);
	printf("演出类型  (1 电影 || 2 戏剧 || 3 演唱会)");
	scanf("%d", &(rec.type));
	getchar();
	printf("上映地区?");
	scanf("%s", rec.area);
	printf("演出等级  (1 or 2 or 3)  ");
	scanf("%d", &rec.rating);
	getchar();
	printf("演出持续时间?");
	scanf("%d", &rec.duration);
	getchar();
	printf("演出开始于?");
	scanf("%d%d%d", &rec.start_date.year, &rec.start_date.month, &rec.start_date.day);
	getchar();
	printf("演出结束于?");
	scanf("%d%d%d", &rec.end_date.year, &rec.end_date.month, &rec.end_date.day);
	getchar();
	printf("票价多少?");
	scanf("%d", &rec.price);
	printf("==============================\n");
	printf("%s\n", rec.name);

	Play_Srv_Modify(&rec);

	return 1;
}

int Play_UI_Query(int id)
{
	play_t buf;
	int rtn = 0;
	if (Play_Srv_FetchByID(id, &buf))
	{

		printf("查找成功!\n");
		printf("演出存在\n");
		rtn = 1;
	}
	else
	{
		printf("查找失败\n");
		printf("演出不存在\n");
	}

	printf("请输入[Enter]\n");
	getchar();
	return rtn;
}
// int Play_UI_screen()
// {
// 	play_list_t head;
// 	List_Init(head, play_node_t);

// 	Play_Srv_screen(head); // 将删除的 剧目 提 到链表里

// 	play_node_t *temp;
// 	temp = head;
// 	head = head->next;

// 	while (temp != head) // 删除对应的剧目 的 演出计划
// 	{
// 		Schedule_Srv_DeleteByplayID(head->data.id);
// 		head = head->next;
// 	}

// 	return 0;
// }
