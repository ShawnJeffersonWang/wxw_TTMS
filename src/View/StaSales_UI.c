#include "StaSales_UI.h"
#include <time.h>
#include <stdio.h>
#include "../Common/list.h"
#include "../Service/Sale.h"
#include "../Service/Account.h"
#include "../Service/SalesAnalysis.h"

extern account_t gl_CurUser;
// 10统计销售额
void StaSales_UI_MgtEntry()
{

    if (gl_CurUser.type == 1)
    {
        StaSales_UI_Self();
        printf("please input the [Enter]");
        getchar();
    }
    else if (gl_CurUser.type == 2)
    {
        StaSales_UI_Clerk();
        printf("please input the [Enter]");
        getchar();
    }
    else
    {
        printf("you can't join in there!please input the [Enter]");
        getchar();
    }
}

// 统计个人销售额界面
void StaSales_UI_Self()
{
    int id = gl_CurUser.id;
    char choice;

    ttms_date_t curdate, startdate, enddate;
    struct tm *p;
    time_t timep;
    time(&timep);
    p = localtime(&timep);
    printf("[D]ay is One-day sales            |            [M]onth Monthly sales");
    printf("\nyou choice:");
    scanf("%c", &choice);
    getchar();
    setbuf(stdin, NULL);
    curdate.year = p->tm_year + 1900;
    curdate.month = p->tm_mon + 1;
    curdate.day = p->tm_mday;
    startdate.year = p->tm_year + 1900;
    startdate.month = p->tm_mon + 1;
    startdate.day = 1;
    enddate.year = p->tm_year + 1900;
    enddate.month = p->tm_mon + 1;
    enddate.day = 31;
    switch (choice)
    {
    case 'd':
    case 'D': // 当日
        printf("Your sales this day are %d\n", SalesAnalysis_Srv_CompSaleVal(id, curdate, curdate));
        break;
    case 'm':
    case 'M': // 当月
        printf("Your sales this month are %d\n", SalesAnalysis_Srv_CompSaleVal(id, startdate, enddate));
        break;
    }
}

// 统计售票员销售额界面
void StaSales_UI_Clerk()//wxw 20021201
{
    account_t tem;
    int id;

    ttms_date_t startdate, enddate;

    char Usrname[20];
    printf("请输入售票员用户名:");
    scanf("%s", Usrname);
    if (Account_Srv_FetchByName(Usrname, &tem))
    {
        if (tem.type != USR_CLERK)
        {
            printf("此人不是售票员!!");
            getchar();
            return;
        }
        id = tem.id;
        printf("请输入开始日期(年 月 日):");
        scanf("%d%d%d", &startdate.year, &startdate.month, &startdate.day);
        printf("请输入结束日期(年 月 日):");
        scanf("%d%d%d", &enddate.year, &enddate.month, &enddate.day);
        getchar();
        printf("售票员的销售额为 %d\n", SalesAnalysis_Srv_CompSaleVal(id, startdate, enddate));
    }
    else
    {
        printf("the user is not in this company!!");
        getchar();
        return 0;
    }
}
