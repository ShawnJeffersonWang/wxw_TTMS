#ifndef TICKET_UI_H_
#define TICKET_UI_H_
#include "../Service/Ticket.h"
//   schedule_id表示与票相关的演出计划
void Ticket_UI_MgtEntry(int schedule_id);

void Ticket_UI_Query(void);

int Ticket_UI_ShowTicket(int ticket_id);

int Ticket_Srv_FetchBySchID(int ID, ticket_list_t list);

ticket_node_t *Ticket_Srv_FetchBySeatID(ticket_list_t list, int seat_id);

int Ticket_Srv_Modify(const ticket_t *data);

void Ticket_UI_Print(const ticket_t data);
#endif
