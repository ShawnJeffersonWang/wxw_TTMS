#include <stdio.h>
#include "../View/Ticket_UI.h"
#include "../Common/list.h"
#include "../Service/Ticket.h"
#include "../Service/Schedule.h"
#include "../Service/Account.h"
#include "../Service/Play.h"

static const int TICKET_PAGE_SIZE = 5;
extern account_t gl_CurUser;

// 05生成演出票
void Ticket_UI_MgtEntry(int schedule_id)
{
	if (gl_CurUser.type == USR_ANOMY || gl_CurUser.type == USR_ADMIN)
	{
		printf("you can't join in there!please input the [Enter]");
		getchar();
		return;
	}

	int i, id;
	int yan_id;
	char choice;
	schedule_t buf;
	play_t data;

	Schedule_Srv_FetchByID_ticket(schedule_id, &buf);
	Play_Srv_FetchByID(buf.play_id, &data);

	printf("=======================================================================\n");

	printf("名称          演出厅ID                日期                  时间       \n");
	printf("%s                 %d             %d.%d.%d               %d:%d:%d\n", data.name, buf.studio_id, buf.date.year, buf.date.month, buf.date.day, buf.time.hour, buf.time.minute, buf.time.second);

	printf("[G]enerating tickets    [R]eproduction of tickets \n");
	setbuf(stdin, NULL);
	printf("Your choice:");
	scanf("%c", &choice);
	getchar();

	switch (choice)
	{
	case 'G':
	case 'g':
		system("clear");
		Ticket_Srv_GenBatch(schedule_id);
		printf("Successlly!\n");
		break;
	case 'r':
	case 'R':
		Ticket_Srv_deleteBatch(schedule_id);
		Ticket_Srv_GenBatch(schedule_id);
		printf("Successlly!\n");
		break;
	case 'q':
	case 'Q':
		Ticket_UI_Query();
		break;
	}
}

void Ticket_UI_Query(void)
{
	/*	ticket_list_t list;

		List_Init(list,ticket_node_t);

		Ticket_Srv_FetchAll(list);
	*/
	printf("==================================================\n");
	printf("******************查询演出票*********************\n");
	printf("请输入演出票ID:");

	int id;
	scanf("%d", &id);
	getchar();

	Ticket_UI_ShowTicket(id);
}

int Ticket_UI_ShowTicket(int ticket_id)
{
	ticket_t buf;
	int temp = Ticket_Srv_FetchByID(ticket_id, &buf);
	if (temp == 0)
	{
		printf("the ticket is not exist!\n");
	}
	else
	{
		printf("票ID      演出计划ID      座位ID      票价      票状态    \n");
		printf("%6d  %6d     %6d    %6d   %6d    \n", buf.id, buf.schedule_id, buf.seat_id, buf.price, buf.status);
	}
}

void Ticket_UI_Print(const ticket_t data)
{
	printf("your ticket data : \n");
	printf("票ID      演出计划ID    座位ID  票价\n");
	printf("%d                  %d           %d      %d    \n", data.id, data.schedule_id, data.seat_id, data.price);
	printf("---------------------------------------\n");
	getchar();
}
