#ifndef TICKET_PERSIST_H_
#define TICKET_PERSIST_H_

#include "../Service/Ticket.h"
#include "../Service/Schedule.h"
#include "../Service/Seat.h"
// int Schedule_Perst_SelectByID(int id,schedule_t *buf);   //从文件中载入指定ID的演出计划

int Ticket_Perst_Insert(seat_list_t list, int schedule_id); // 在票信息文件ticket.dat 中批量加入list链表上的所有信息

int Ticket_Perst_Update(const ticket_t *data);

int Ticket_Perst_SelBySchID(int ID, ticket_list_t list);

int Ticket_Perst_Rem(int schedule_id); // 批量删除演出计划的ID

int Ticket_Perst_SelByticketID(id, buf);

#endif
