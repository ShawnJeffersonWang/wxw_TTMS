#include <stdlib.h>
#include "../Common/list.h"
#include "Seat.h"
#include "../Persistence/Seat_Persist.h"

int Seat_Srv_Add(const seat_t *data)
{

       return Seat_Perst_Insert(data);
}

int Seat_Srv_AddBatch(seat_list_t list)
{

       return 0;
}

int Seat_Srv_Modify(const seat_t *data)
{
       return Seat_Perst_Update(data);
}

int Seat_Srv_DeleteByID(int ID)
{
       return Seat_Perst_DeleteByID(ID);
}

int Seat_Srv_FetchByID(int ID, seat_t *buf)
{
       return Seat_Perst_SelectByID(ID, buf);
}

inline int Seat_Srv_DeleteAllByRoomID(int roomID)
{
       return Seat_Perst_DeleteAllByRoomID(roomID);
}

int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID)
{
       int SeatCount;
       SeatCount = Seat_Perst_SelectByRoomID(list, roomID);
       Seat_Srv_SortSeatList(list);
       return SeatCount;
}

int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
       int SeatCount;
       SeatCount = Seat_Perst_SelectByRoomID(list, roomID);
       seat_list_t temp = list;
       while (list->next != temp)
       {
              list = list->next;
              if (list->data.status != SEAT_GOOD)
              {
                     SeatCount--;
              }
       }
       Seat_Srv_SortSeatList(list);
       return SeatCount;
}

int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount, int colsCount)
{

       seat_list_t tem;
       for (int i = 1; i <= rowsCount; i++)
       {
              for (int j = 1; j <= colsCount; j++)
              {

                     tem = (seat_list_t)malloc(sizeof(seat_node_t));
                     tem->data.column = j;
                     tem->data.row = i;
                     tem->data.roomID = roomID;
                     tem->data.status = SEAT_GOOD;
                     List_AddTail(list, tem);
              }
       }
       return Seat_Perst_InsertBatch(list);
}

void Seat_Srv_SortSeatList(seat_list_t list)
{
       assert(list != NULL);
       seat_list_t listLeft;
       seat_list_t p;
       if (List_IsEmpty(list))
       {
              return;
       }
       else
       {
              list->prev->next = NULL;
              listLeft = list->next;
              list->next = list->prev = list;

              while (listLeft != NULL)
              {
                     p = listLeft;
                     listLeft = listLeft->next;
                     Seat_Srv_AddToSoftedList(list, p);
              }
       }
       return;
}

void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node)
{

       seat_list_t p;
       assert(list != NULL && node != NULL);
       if (List_IsEmpty(list))
       {
              List_AddTail(list, node);
       }
       else
       {
              p = list->next;
              while (p != list && (p->data.row < node->data.row || (p->data.row == node->data.row && p->data.column < node->data.column)))
              {
                     p = p->next;
              }
              List_InsertBefore(p, node);
       }
}

seat_node_t *Seat_Srv_FindByRowCol(seat_list_t list, int row, int column)
{
       seat_list_t p;
       p = list;
       list = list->next;
       while (!((list->data.row == row) && (list->data.column == column)))
       {
              list = list->next;
              if (list == p)
              {
                     break;
              }
       }
       if (list->data.row == row && list->data.column == column)
       {
              return list;
       }
       else
       {
              return NULL;
       }
}

seat_node_t *Seat_Srv_FindByID(seat_list_t list, int rowID)
{

       assert(NULL != list);
       seat_node_t *p;

       List_ForEach(list, p) if (p->data.id == rowID) return p;

       return NULL;
}
