#include <stdlib.h>
#include "../Common/List.h"
#include "Seat.h"

int Seat_Srv_Add(const seat_t *data)
{
       return 0;
}

int Seat_Srv_AddBatch(seat_list_t list)
{
       return 0;
}

int Seat_Srv_Modify(const seat_t *data)
{
       return 0;
}

int Seat_Srv_DeleteByID(int ID)
{
       return 1;
}

int Seat_Srv_FetchByID(int ID, seat_t *buf)
{
       return 0;
}

inline int Seat_Srv_DeleteAllByRoomID(int roomID)
{
       return 0;
}

int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID)
{
       return 0;
}

int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
       return 0;
}

int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,
                      int colsCount)
{
       return 0;
}

void Seat_Srv_SortSeatList(seat_list_t list)
{
}

void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node)
{
}

seat_node_t *Seat_Srv_FindByRowCol(seat_list_t list, int row, int column)
{
       return NULL;
}

seat_node_t *Seat_Srv_FindByID(seat_list_t list, int rowID)
{
       return NULL;
}