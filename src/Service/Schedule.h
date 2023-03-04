#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include "Play.h"

typedef struct
{
	int hour;
	int minute;
	int second;
} ttms_time_t;

typedef struct
{
	int id;			  // 演出计划id
	int play_id;	  // 上映剧目id
	int studio_id;	  // 演出厅id
	ttms_date_t date; // 放映日期
	ttms_time_t time; // 放映时间
	int seat_count;	  // 座位数
} schedule_t;

typedef struct schedule_node
{
	schedule_t data;
	struct schedule_node *next;
	struct schedule_node *prev;
} schedule_node_t, *schedule_list_t;

int Schedule_Srv_FetchByPlay(schedule_list_t, int play_id); // 跟据剧目id获取演出计划

int Schedule_Srv_Add(schedule_t *data);

int Schedule_Srv_Modify(const schedule_t *data);

int Schedule_Srv_DeleteByID(int id);

int Schedule_Srv_FetchByAll(schedule_list_t list);

int Schedule_Srv_FetchByID(schedule_list_t head, int id);

int Schedule_Srv_FetchByID_ticket(int id, schedule_t *buf);

int Schedule_Srv_DeleteByplayID(int play_id);

#endif
