#include"Schedule.h"
#include"../Persistence/Schedule_Persist.h"
#include<stdlib.h>
#include<assert.h>
#include"Ticket.h"
//04安排演出
int Schedule_Srv_FetchByPlay(schedule_list_t head ,int play_id)
{
	return Schedule_Perst_SelectByPlay(head,play_id);
}

int Schedule_Srv_Add(schedule_t *data)
{
	return Schedule_Perst_Insert(data);
}

int Schedule_Srv_DeleteByID(int play_id)
{
	return Schedule_Perst_RemByID(play_id);
}

int Schedule_Srv_Modify(const schedule_t *data)
{
	return Schedule_Perst_Update(data);
}

int Schedule_Srv_FetchByID(schedule_list_t head ,int id)
{
	return Schedule_Perst_SelectByID(head,id);
}

int Schedule_Srv_FetchByID_ticket(int id,schedule_t *buf)
{
	return Schedule_Perst_SelectByID_ticket(id,buf);
}

int Schedule_Srv_FetchByAll(schedule_list_t list)
{
	return Schedule_Perst_SelectAll(list);
}

int Schedule_Srv_DeleteByplayID(int play_id)
{
	return Schedule_Perst_DeleByplayid(play_id);
}
