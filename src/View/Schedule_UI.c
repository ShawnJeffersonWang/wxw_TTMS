#include <stdio.h>
#include "../View/Schedule_UI.h"
#include "../Common/list.h"
#include "../View/Ticket_UI.h"
#include "../Service/Schedule.h"
#include "../Service/Studio.h"
#include "../Service/Account.h"

static const int SCHEDULE_PAGE_SIZE = 5;
extern account_t gl_CurUser;
// 04安排演出
void Schedule_UI_MgtEntry(int play_id)
{
	if (gl_CurUser.type == USR_ADMIN)
	{
		printf("you can't join in there!please input the [Enter]");
		getchar();
		return;
	}

	system("clear");
	int schedule_id;
	int i, id;
	int yan_id;
	char choice;

	schedule_list_t head;
	schedule_node_t *pos;
	Pagination_t paging;

	List_Init(head, schedule_node_t);

	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	paging.totalRecords = Schedule_Srv_FetchByPlay(head, play_id);
	Paging_Locate_FirstPage(head, paging);

	do
	{
		printf("===================================================================================================\n");
		printf("************************************************演出计划列表**************************************\n");

		printf("%s  %10s    %10s    %15s    %15s    %15s", "演出计划ID", "剧目ID", "演出厅ID", "放映日期", "放映时间", "座位数\n");
		printf("---------------------------------------------------------------------------------------------------\n");
		Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i)
		{
			printf("%3d           %3d       %3d           %d.%2d.%2d        %d:%2d:%2d          %3d\n", pos->data.id, pos->data.play_id, pos->data.studio_id, pos->data.date.year, pos->data.date.month, pos->data.date.day, pos->data.time.hour, pos->data.time.minute, pos->data.time.second, pos->data.seat_count);
		}

		printf("---totalRecords: %2d ---------------------------------------------Page %2d/%2d------------------------\n", paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));

		printf("[P]revPage  [N]extPage [A]dd [U]pdate [D]elete [T]icket [R]eturn");

		printf("Your Choice:");
		setbuf(stdin, NULL);
		scanf("%c", &choice);
		getchar();

		switch (choice)
		{
		case 'a':
		case 'A':
			if (Schedule_UI_Add(play_id))
			{
				paging.totalRecords = Schedule_Srv_FetchByPlay(head, play_id);
				Paging_Locate_LastPage(head, paging, schedule_node_t);
			}
			break;
		case 'd':
		case 'D':
			printf("演出计划ID:");
			scanf("%d", &yan_id);
			getchar();
			if (Schedule_UI_Delete(yan_id))
			{
				paging.totalRecords = Schedule_Srv_FetchByPlay(head, play_id);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 'U':
		case 'u':
			printf("演出计划ID: ");
			scanf("%d", &yan_id);
			getchar();
			if (Schedule_UI_Modify(yan_id))
			{
				paging.totalRecords = Schedule_Srv_FetchByPlay(head, play_id);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 't':
		case 'T':
			printf("演出计划ID :");
			scanf("%d", &schedule_id);
			getchar();
			if(Schedule_Srv_FetchByID(head,schedule_id))
			{
			Ticket_UI_MgtEntry(schedule_id);
			}
			else
			{
				printf("Schedule do not exist\n");
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	List_Destroy(head, schedule_node_t);
}

void Schedule_UI_ListAll(void)
{
	system("clear");
	int i;
	char choice;

	char play_name[50];
	schedule_list_t list;
	List_Init(list, schedule_node_t);
	play_t play;
	schedule_t sch;
	studio_t studio;
	schedule_node_t *pos;
	Pagination_t paging;

	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	paging.totalRecords = Schedule_Srv_FetchByAll(list);
	Paging_Locate_FirstPage(list, paging);

	do
	{
		printf("\n==========================================================================================\n");
		printf("*****************************************查询演出*****************************************\n");
		Paging_ViewPage_ForEach(list, paging, schedule_node_t, pos, i)
		{
			// if(i % paging.pageSize != 0)
			{
				printf("%5s %20s %5s %10s %3s %3s %8s %8s %3s\n", "演出计划ID", "演出计划名称", "类型", "日期", "等级", "持续时间", "开始日期", "结束日期", "票价");
				//	Play_Srv_FetchByID(pos->data.play_id,&play);
				//	printf( "%5d %20s %5d %10s %3d %3d %4d %2d %2d %4d %2d %2d %4d\n",play.id,play.name,play.type,play.area,play.rating,play.duration,play.start_date.year,play.start_date.month,play.start_date.day,play.end_date.year,play.end_date.month,play.end_date.day,play.price);
				printf("%d \n", pos->data.id);
				Studio_Srv_FetchByID(pos->data.studio_id, &studio);
				printf("%5s  %18s  %10s  %10s  %10s\n", "演出厅ID", "演出厅名称", "行数", "列数", "座位数");
				printf("%5d  %18s  %10d  %10d  %10d\n", studio.id, studio.name, studio.rowsCount, studio.colsCount, studio.seatsCount);
			}
		}

		printf("--------------Total Records : %2d ----------------------Page %2d / %2d-----\n", paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
		printf("=======================================================================================\n");
		printf("[R]eturn   [N]ext     [P]rev       [Q]ry");
		printf("\n***************************************************************************************\n");

		printf("Your choice:");

		setbuf(stdin, NULL);

		scanf("%c", &choice);
		getchar();

		switch (choice)
		{
		case 'n':
		case 'N':
			setbuf(stdin, NULL);
			if (!Pageing_IsLastPage(paging))
			{
				Paging_Locate_OffsetPage(list, paging, 1, schedule_node_t);
			}
			break;
		case 'P':
		case 'p':
			setbuf(stdin, NULL);
			if (!Pageing_IsFirstPage(paging))
			{
				Paging_Locate_OffsetPage(list, paging, -1, schedule_node_t);
			}
			break;
		case 'Q':
		case 'q':
			setbuf(stdin, NULL);
			printf("请输入您想查询的剧目名称:");
			scanf("%s", play_name);
			Schedule_UI_Qry(play_name);
			break;
		default:
			printf("worry answer");
		}
	} while (choice != 'R' && choice != 'r');

	List_Destroy(list, schedule_node_t);

	return;
}

int Schedule_UI_Qry(char *play_name)
{
	int rtn = 0;
	play_list_t list;
	schedule_list_t list_s;

	List_Init(list, play_node_t);
	List_Init(list_s, schedule_node_t);

	Play_Srv_FetchByName(list, play_name);
	play_list_t temp = list;

	list = list->next;

	while (list != temp)
	{
		Schedule_Srv_FetchByPlay(list_s, list->data.id);
		schedule_list_t temp_s = list_s;

		list_s = list_s->next;

		while (list_s != temp_s)
		{
			rtn++;
			printf("%s %10s %10s %20s %20s %20s", "演出名称 ", "演出时间  ", "演出厅ID ", "放映日期", "放映时间", "座位数\n");
			printf("%6s %3d %3d %3d %3d %3d %3d %3d %3d %3d\n", list->data.name, list->data.duration, list_s->data.studio_id, list_s->data.date.year, list_s->data.date.month, list_s->data.date.day, list_s->data.time.hour, list_s->data.time.minute, list_s->data.time.second, list_s->data.seat_count);
			list_s = list_s->next;
		}
		list = list->next;
	}

	printf("please press Enter !\n");
	getchar();

	return rtn;
}
int Schedule_UI_Add(int play_id)
{
	if (gl_CurUser.type == USR_CLERK || gl_CurUser.type == USR_ANOMY)
	{
		printf("you can't join in there!please input the [Enter]");
		getchar();
		return 0;
	}
	system("clear");
	schedule_t rec;
	int newRecCount = 0;
	char choice;

	do
	{
		studio_t buf;
		printf("\n====================================================================================\n");
		printf("********************************添加演出计划*************************\n");
		printf("------------------------------------------------------------------------------------\n");

		setbuf(stdin, NULL);

		rec.play_id = play_id;
		while (1)
		{
			printf("演出厅ID:");
			scanf("%d", &rec.studio_id);
			if (Studio_Srv_FetchByID(rec.studio_id, &buf))
			{
				break;
			}
			else
			{
				printf("演出厅不存在!\n");
				continue;
			}
		}

		printf("上映时间:");
		scanf("%d%d%d", &rec.date.year, &rec.date.month, &rec.date.day);
		printf("演出时长:");
		scanf("%d%d%d", &rec.time.hour, &rec.time.minute, &rec.time.second);
		printf("座位数量:");
		scanf("%d", &rec.seat_count);

		setbuf(stdin, NULL);

		printf("==================================================================================\n");

		if (Schedule_Srv_Add(&rec))
		{
			newRecCount += 1;
			printf("添加演出计划成功!\n");
		}
		else
		{
			printf("添加演出计划失败!\n");
		}

		printf("-------------------------------------------\n");

		printf("[A]dd more  [R]eturn:");

		setbuf(stdin, NULL);

		scanf("%c", &choice);
		getchar();
	} while ('a' == choice || 'A' == choice);

	return newRecCount;
}

int Schedule_UI_Delete(int play_id)
{
	if (gl_CurUser.type == USR_CLERK || gl_CurUser.type == USR_ANOMY)
	{
		printf("you can't join in there!please input the [Enter]");
		getchar();
		return 0;
	}
	int rtn = 0;

	if (Schedule_Srv_DeleteByID(play_id))
	{
		printf("the show is deleted successfully!\n");
		rtn = 1;
	}
	else
	{
		printf("the show is deleted failed!\n");
	}

	return rtn;
}

int Schedule_UI_Modify(int id)
{
	if (gl_CurUser.type == USR_CLERK || gl_CurUser.type == USR_ANOMY)
	{
		printf("you can't join in there!please input the [Enter]");
		getchar();
		return 0;
	}
	schedule_list_t list;
	schedule_t rec;
	int rtn = 0;

	List_Init(list, schedule_node_t);
	if (!Schedule_Srv_FetchByID(list, id))
	{
		printf("the schedule does not exist!\n[Enter] key to return \n");
		getchar();
		return 0;
	}

	printf("\n ===========================================================\n");
	printf("*****************************更新演出计划 ********************\n");
	printf("-----------------------------------------------------------------\n");

	rec.id = id;
	printf("Enter modify data: \n");
	printf("演出厅ID:");
	scanf("%d", &rec.studio_id);
	printf("放映日期:");
	scanf("%d%d%d", &rec.date.year, &rec.date.month, &rec.date.day);
	printf("放映时间:");
	scanf("%d%d%d", &rec.time.hour, &rec.time.minute, &rec.time.second);
	printf("座位数:");
	scanf("%d", &rec.seat_count);

	printf("------------------------------------------\n");
	if (Schedule_Srv_Modify(&rec))
	{
		rtn = 1;
		printf("the scheudle data updata successfully!\npress[Enter] key to return!\n");
	}
	else
	{
		printf("the scheudele data update failed!\npress [Enter] key to return !\n");
	}

	getchar();
	return rtn;
}
