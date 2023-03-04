#ifndef PLAYPERSIST_H_
#define PLAYPERSIST_H_

#include"../Service/Play.h"

int Play_Perst_SelectAll(play_list_t list);

int Play_Perst_Insert(play_t *data);

int Play_Perst_Update(const play_t *data);

int Play_Perst_RemByID(int id);

int Play_Perst_SelectByID(int id,play_t *buf);

int Play_Perst_screen(play_list_t list);
#endif
