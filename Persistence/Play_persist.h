#ifndef PLAYPERSIST_H_
#define PLAYPERSIST_H_

#include "../Service/Play.h"

int Play_Perst_SelectAll(play_list_t list); // 从文件中载入所有剧目信息,加载到list上

int Play_Perst_Insert(play_t *data); // 向剧目数据文件的末尾添加一条新的剧目信息

int Play_Perst_Update(const play_t *data); // 更新文件中的一条剧目信息//参数为:带修改的剧目信息

int Play_Perst_RemByID(int id); // 取出文件中的指定的ID信息

int Play_Perst_SelectByID(int id, play_t *buf); // 在文件中载入指定ID的剧目信息到buf中

int Play_Perst_screen(play_list_t list);
#endif
