#include "Seat_UI.h"
#include "../Service/Seat.h"
#include "../Service/Account.h"
#include "../Service/Studio.h"
#include "../Common/list.h"
#include <stdio.h>
#include <string.h>

extern account_t gl_CurUser;
//02设置座位
inline char Seat_UI_Status2Char(seat_status_t status)
{
    if (status == 0)
        return ' ';
    else if (status == 1)
        return '#';
    else if (status == 9)
        return '~';
}

inline seat_status_t Seat_UI_Char2Status(char statusChar)
{
    if (statusChar == ' ')
        return SEAT_NONE;
    else if (statusChar == '#')
        return SEAT_GOOD;
    else if (statusChar == '~')
        return SEAT_BROKEN;
}

void Seat_UI_MgtEntry(int roomID)
{
    if (gl_CurUser.type != USR_MANG)
    {
        printf("you can't join in there!please input the [Enter]");
        getchar();
        return 0;
    }

    studio_t rec;
    char choice;

    if (!Studio_Srv_FetchByID(roomID, &rec))
    {
        printf("The room does not exist!\nPress [Enter] key to return!\n");
        getchar();
        return;
    }
    seat_list_t head;
    List_Init(head, seat_node_t);
    if (Seat_Srv_FetchByRoomID(head, roomID) == 0)
    {
        rec.seatsCount = Seat_Srv_RoomInit(head, roomID, rec.rowsCount, rec.colsCount);
        Studio_Srv_Modify(&rec);
    }

    do
    {

        printf("行数:%d                   列数:%d                  座位总数:%d\n", rec.rowsCount, rec.colsCount, rec.seatsCount);

        printf("-------------------------------------------------------------------\n");
        setbuf(stdin, NULL);
        int x = 0, y = 1;
        for (int i = 0; i <= rec.rowsCount; i++)
        {
            for (int j = 0; j <= rec.colsCount; j++)
            {

                if (i == 0)
                {
                    printf("%3d", x++);
                }
                else if (j == 0)
                {
                    printf("%3d", y++);
                }
                else
                {
                    int flag = 0;
                    seat_list_t temp;
                    List_ForEach(head, temp)
                    {
                        if (temp->data.row == i && temp->data.column == j)
                        {
                            flag = 1;
                            printf("%3c", Seat_UI_Status2Char(temp->data.status));
                            break;
                        }
                    }
                    if (!flag)
                        printf("   "); // 此处没有座位
                }
            }
            putchar('\n');
        }
        // 用于显示座位情况列表
        setbuf(stdin, NULL);

        int row1, column1;
        printf(
            "******************************************************************\n");
        printf(
            "[A]dd  |  [M]od  |  [D]el  |  [R]eturn");
        printf(
            "\n==================================================================\n");

        printf("Your Choice:");
        setbuf(stdin, NULL);
        scanf("%c", &choice);
        getchar();
        switch (choice)
        {
        case 'A':
        case 'a':
            printf("请输入行号 :");
            scanf("%d", &row1);
            printf("请输入列号 :");
            scanf("%d", &column1);
            getchar();
            if (!Seat_UI_Add(head, roomID, row1, column1))
            {
                printf("添加失败!\n");
            }
            else
            {
                rec.seatsCount = rec.seatsCount + 1;
                Studio_Srv_Modify(&rec);
                Seat_Srv_FetchByRoomID(head, roomID);
                printf("添加成功!\n");
            }
            break;
        case 'M':
        case 'm':
            printf("请输入行号 :");
            scanf("%d", &row1);
            printf("请输入列号 :");
            scanf("%d", &column1);
            getchar();
            if (!Seat_UI_Modify(head, row1, column1))
            {
                printf("修改失败!\n");
            }
            else
            {
                Seat_Srv_FetchByRoomID(head, roomID);
                printf("修改成功!\n");
            }
            break;
        case 'D':
        case 'd':
            printf("请输入行号 :");
            scanf("%d", &row1);
            printf("请输入列号 :");
            scanf("%d", &column1);
            getchar();
            if (!Seat_UI_Delete(head, row1, column1))
            {
                printf("删除失败!\n");
            }
            else
            {
                rec.seatsCount = rec.seatsCount - 1;
                Studio_Srv_Modify(&rec);
                Seat_Srv_FetchByRoomID(head, roomID);
                printf("删除成功!\n");
            }
            break;
        }
    } while (choice != 'r' && choice != 'R');
    List_Destroy(head, seat_node_t);
}

int Seat_UI_Add(seat_list_t list, int roomID, int row, int column)
{

    seat_list_t tmp = Seat_Srv_FindByRowCol(list, row, column);
    if (tmp == NULL)
    {
        seat_t temp;

        temp.column = column;
        temp.row = row;
        temp.status = SEAT_GOOD;
        temp.roomID = roomID;

        if (Seat_Srv_Add(&temp))
        {
            return 1;
        }
    }
    return 0;
}

int Seat_UI_Modify(seat_list_t list, int row, int column)
{

    seat_list_t tmp = Seat_Srv_FindByRowCol(list, row, column);

    if (tmp != NULL)
    {
        seat_t temp;
        Seat_Perst_SelectByID(tmp->data.id, &temp);
        char choice;
        printf(
            "*******************************************************************\n");
        printf(
            "[#]GOOD | [~]BROKEN | [ ]NONE | 座位状态是: %c", Seat_UI_Status2Char(temp.status));
        printf(
            "\n==================================================================\n");
        printf("您的选择:");
        scanf("%c", &choice);
        getchar();
        tmp->data.status = Seat_UI_Char2Status(choice);

        if (Seat_Srv_Modify(&tmp->data))
        {

            return 1;
        }
    }
    return 0;
}

int Seat_UI_Delete(seat_list_t list, int row, int column)
{

    seat_list_t tmp = Seat_Srv_FindByRowCol(list, row, column);

    if (tmp != NULL)
    {
        if (Seat_Srv_DeleteByID(tmp->data.id))
        {
            return 1;
        }
    }
    return 0;
}
