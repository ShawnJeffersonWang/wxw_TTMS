#ifndef SCHEDULE_UI_H_
#define SCHEDULE_UI_H_

void Schedule_UI_MgtEntry(int play_id); // 显示id号为play_id的剧目的相关的所有演出计划

int Schedule_UI_Add(int play_id);

int Schedule_UI_Modify(int id);

int Schedule_UI_Delete(int id);

int Schedule_UI_Qry(char *play_name);

#endif
