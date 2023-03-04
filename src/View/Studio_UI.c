#include <stdio.h>
#include "../Service/Account.h"
#include "../View/Studio_UI.h"
#include "../Common/list.h"
#include "../Service/Studio.h"
#include "../Service/Seat.h"


//01管理演出厅
extern account_t gl_CurUser;
void Seat_UI_MgtEntry(int id);

static const int STUDIO_PAGE_SIZE = 5;

void Studio_UI_MgtEntry(void)
{

	if (gl_CurUser.type != USR_MANG)
	{
		printf("you can't join in there!please input the [Enter]");
		getchar();
		return;
	}

	int i, id;
	char choice;

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;

	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;

	paging.totalRecords = Studio_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	do
	{
		system("clear");
		printf(
			"\n==================================================================\n");
		printf(
			"********************** Projection Room List **********************\n");
		printf("%5s  %18s  %10s  %10s  %10s\n", "ID", "Name", "Rows Count",
			   "Columns Count", "Seats Count");
		printf(
			"------------------------------------------------------------------\n");
		Paging_ViewPage_ForEach(head, paging, studio_node_t, pos, i)
		{
			printf("%5d  %18s  %10d  %10d  %10d\n", pos->data.id,
				   pos->data.name, pos->data.rowsCount, pos->data.colsCount,
				   pos->data.seatsCount);
		}

		printf(
			"------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
			paging.totalRecords, Pageing_CurPage(paging),
			Pageing_TotalPages(paging));
		printf(
			"******************************************************************\n");
		printf(
			"[P]revPage|[N]extPage | [A]dd|[D]elete|[U]pdate | [S]eat | [R]eturn");
		printf(
			"\n==================================================================\n");
		printf("Your Choice:");
		scanf("%c", &choice);
		getchar();

		switch (choice)
		{
		case 'a':
		case 'A':
			if (Studio_UI_Add())
			{
				paging.totalRecords = Studio_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, studio_node_t);
			}
			break;
		case 'd':
		case 'D':
			printf("Input the ID:");
			scanf("%d", &id);
			getchar();
			if (Studio_UI_Delete(id))
			{
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			break;
		case 'u':
		case 'U':
			printf("Input the ID:");
			scanf("%d", &id);
			getchar();
			if (Studio_UI_Modify(id))
			{
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
			}
			break;
		case 's':
		case 'S':
			printf("Input the ID:");
			scanf("%d", &id);
			getchar();
			Seat_UI_MgtEntry(id);
			paging.totalRecords = Studio_Srv_FetchAll(head);
			List_Paging(head, paging, studio_node_t);
			break;
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');

	setbuf(stdin, NULL);
	List_Destroy(head, studio_node_t);
}

int Studio_UI_Add(void)
{
	studio_t rec;
	int newRecCount = 0;
	char choice;

	do
	{
		printf("\n=======================================================\n");
		printf("****************  Add New Projection Room  ****************\n");
		printf("-------------------------------------------------------\n");
		printf("Room Name:");
		scanf("%s", rec.name);
		printf("Row Count of Seats:");
		scanf("%d", &(rec.rowsCount));
		printf("Column Count of Seats:");
		scanf("%d", &(rec.colsCount));
		getchar();
		rec.seatsCount = 0;
		printf("=======================================================\n");

		if (Studio_Srv_Add(&rec))
		{
			newRecCount += 1;
			printf("The new room added successfully!\n");
		}
		else
			printf("The new room added failed!\n");
		printf("-------------------------------------------------------\n");
		printf("[A]dd more, [R]eturn:");
		scanf("%c", &choice);
		getchar();
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

int Studio_UI_Modify(int id)
{
	studio_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	seat_list_t list;
	int seatcount;

	/*Load record*/
	if (!Studio_Srv_FetchByID(id, &rec))
	{
		printf("The room does not exist!\nPress [Enter] key to return!\n");
		getchar();
		return 0;
	}

	printf("\n=======================================================\n");
	printf("****************  Update Projection Room  ****************\n");
	printf("-------------------------------------------------------\n");
	printf("Room ID:%d\n", rec.id);
	printf("Room Name[%s]:", rec.name);
	scanf("%s", rec.name);

	List_Init(list, seat_node_t);
	seatcount = Seat_Srv_FetchByRoomID(list, rec.id);
	if (seatcount)
	{
		do
		{
			printf("Row Count of Seats should >= [%d]:", rec.rowsCount);
			scanf("%d", &(newrow));
			printf("Column Count of Seats should >= [%d]:", rec.colsCount);
			scanf("%d", &(newcolumn));
		} while (newrow < rec.rowsCount || newcolumn < rec.colsCount);

		rec.rowsCount = newrow;
		rec.colsCount = newcolumn;
		rec.seatsCount = seatcount;
	}
	else
	{
		printf("Row Count of Seats:");
		scanf("%d", &rec.rowsCount);
		printf("Column Count of Seats:");
		scanf("%d", &rec.colsCount);
		getchar();
		rec.seatsCount = 0;
	}

	printf("-------------------------------------------------------\n");

	if (Studio_Srv_Modify(&rec))
	{
		rtn = 1;
		printf(
			"The room data updated successfully!\nPress [Enter] key to return!\n");
	}
	else
		printf("The room data updated failed!\nPress [Enter] key to return!\n");
	getchar();
	return rtn;
}

int Studio_UI_Delete(int id)
{

	int rtn = 0;

	if (Studio_Srv_DeleteByID(id))
	{
		if (Seat_Srv_DeleteAllByRoomID(id))
			printf("The seats of the room deleted successfully!\n");
		printf(
			"The room deleted successfully!\nPress [Enter] key to return!\n");
		rtn = 1;
	}
	else
	{
		printf("The room does not exist!\nPress [Enter] key to return!\n");
	}
	getchar();
	return rtn;
}
