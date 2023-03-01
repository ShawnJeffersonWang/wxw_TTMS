#include "Seat_Persist.h"
#include "../Service/Seat.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

static const char SEAT_DATA_FILE[] = "Seat.dat";
static const char SEAT_DATA_TEMP_FILE[] = "SeatTmp.dat";
static const char SEAT_KEY_NAME[] = "Seat";

int Seat_Perst_Insert(seat_t *data)
{
	assert(NULL != data);
	return 0;
}

int Seat_Perst_InsertBatch(seat_list_t list)
{
	seat_node_t *p;
	assert(NULL != list);

	return 0;
}

int Seat_Perst_Update(const seat_t *seatdata)
{
	assert(NULL != seatdata);
	return 0;
}

int Seat_Perst_DeleteByID(int ID)
{

	return 0;
}

int Seat_Perst_DeleteAllByRoomID(int roomID)
{

	return 0;
}

int Seat_Perst_SelectByID(int ID, seat_t *buf)
{

	return 0;
}

int Seat_Perst_SelectAll(seat_list_t list)
{

	return 0;
}

int Seat_Perst_SelectByRoomID(seat_list_t list, int roomID)
{

	return 0;
}
