#ifndef PLAY_H_
#define PLAY_H_

#include "../Common/common.h"

typedef enum
{
	PLAY_TYPE_FILE = 1,
	PLAY_TYPE_OPEAR = 2,
	PLAY_TYPE_CONCERT = 3
} play_type_t;

typedef enum
{
	PLAY_RATE_CHILD = 1,
	PLAY_RATE_TEENAGE = 2,
	PLAY_RATE_ADULT = 3
} play_rating_t;

typedef struct
{
	int year;
	int month;
	int day;
} ttms_date_t;

typedef struct
{
	int id;
	char name[30];
	play_type_t type;
	char area[10];
	play_rating_t rating;
	int duration;
	ttms_date_t start_date;
	ttms_date_t end_date;
	int price;
} play_t;

typedef struct play_node
{
	play_t data;
	struct play_node *next;
	struct play_node *prev;
} play_node_t, *play_list_t;

int Play_Srv_FetchAll(play_list_t list);

int Play_Srv_Add(play_t *data);

int Play_Srv_Modify(const play_t *data);

int Play_Srv_DeleteByID(int id);

int Play_Srv_FetchByID(int id, play_t *buf);

int Play_Srv_FetchByName(play_list_t list, char condt[]);

int Play_Srv_screen(play_list_t list);
#endif
