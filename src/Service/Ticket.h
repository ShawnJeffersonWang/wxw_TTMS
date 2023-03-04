#ifndef TICKET_H_
#define TICKET_H_
#include "Schedule.h"

typedef enum
{
	TICKET_AVL = 0,	 // 待售
	TICKET_SOLD = 1, // 以售
	TICKET_RESV = 9	 // 预留
} ticket_status_t;

typedef struct
{
	int id;					// 票ID
	int schedule_id;		// 演出计划ID
	int seat_id;			// 座位 ID
	int price;				// 票价
	ticket_status_t status; // 票状态
} ticket_t;

typedef struct ticket_node
{
	ticket_t data;
	struct ticket_node *next, *prev;
} ticket_node_t, *ticket_list_t;

int Schedule_Srv_FetchByID_ticket(int id, schedule_t *buf); // 跟据ID获取演出计划

int Ticket_Srv_GenBatch(int schedule_id); // 批量增加文件ticket中的票的个数

void Ticket_Srv_deleteBatch(int schedule_id); // 删除演出票函数

int Ticket_Srv_FetchAll(ticket_list_t list);

int Ticket_Srv_FetchByticketID(int ticket_id, ticket_t *buf);

int Ticket_Srv_FetchBySchID_ticket(ticket_list_t list, int id);

// 标识符:TTMS_SCU_Ticket_Srv_FetchBySchID
// 功能:根据演出计划的ID获取演出票的数据
// int Ticket_Srv_FetchBySchID(int ID,ticket_list_t list);

#endif
