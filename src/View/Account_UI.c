#include "../View/Account_UI.h"
#include <stdio.h>
#include <string.h>
#include "../Common/list.h"
#include "../Service/Account.h"
#include <termios.h> //getch()
#include <unistd.h>
#include <assert.h>
#include "../Common/md5.h"
#include "MaiAccount_UI.h"

static const int Account_PAGE_SIZE = 5;
char ch1;
const int len1 = 20;
extern account_t gl_CurUser;
// 99管理系统用户
//  系统登录

int getch(void)
{
    int ch;
    struct termios tm, tm_old;
    tcgetattr(STDIN_FILENO, &tm);
    tm_old = tm;
    tm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tm);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &tm_old);
    return ch;
}

int SysLogin()
{
	system("clear");
	printf("********************.....=@^........**.*O@/............=@\\`.****..***=*=@@^****OO*.******************OO@^**********,OO@.........\\@^*.*.*=@^\n"
		   "********************.....=@^........**O@@`..............\\@^.*********=O,O@O^***=O^******************OOOO***********/@@`..........\\@^**.*=@^***********\n"
		   "********************.....=@\\**...***/@@/.................\\@O]********,O*\\@OO****OO**************=**/O`OO^***`*****=@@`............\\@^*.*O@^*********\n"
		   "***********************..=@O**...*/@@/......................\\@OO`*****O^=@OOO***=OO**]*/********^/oO^,OOoo/o/o`//O@/...............O@`**O@^************\n"
		   "*************************=@O*..*O@@/...........................\\O@@O]`oO^OO,@\\^,]O@O]o=\\oooo/o\\o=oOO.=@OO/OOOOOOO*..,]].............OO**@@**********\n"
		   "************************.=@@^=O@@^..................................[\\@@@@@^,@O,=o@@Ooo\\oooOOOOO@@O....`.....]/@@@@@@@@@@@@@@]`...]]]@O=@O************\n"
		   "*************************=@@@@@`..............................................[[[[[[[[[[[[...............,O@@@@@@@@@@@@@@@@@@@@@@@@@^\\@O@O*************\n"
		   "**************************@@@`.........................................................................../@@@@@@@@@@@@@@@@@@@@@@@@@@`.O@@O**************\n"
		   "**************************O@^..........................................................................,@@@@@@@@/[....=@@@@@@@@@@@@@@`=@@o**************\n"
		   "**************************=@O........................................................................,@@@@@@@@^..,]]/@@@@@@@@@O@@@@@@@O@@o**************\n"
		   "**************************=@@`.........................................................................=@@@@@@@@@@@@@@@@@@@@@@@oO@@@@@@@O/**************\n"
		   "***************************O@^....................................**...................................O@@@@@@@OOOOOOOOOOO@@@@O\\oo@@@@@@O^=************\n"
		   "^**`***********************=@@...........]/@@@@@@@@@@@@@@@@@\\`......,^.................................O@@O@@OOOOOOOOOOOOO@OO@^...\\@@@@@o*************\n"
		   "\\***************************O@^......,/@@@@@@@@@@@@@@@@@@@@@@@@@@].....................................=@OO@@OOOOOOOOOOOO@@OO@.....=@@@O`**************\n"
		   "O/*^*********,**,`**********\\@O...,/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\`.................................*@OOO@OOOOOooOOOOO@OO@^......@@@/**************\n"
		   "@^*`********`*`/@@@@@\\`******O@@@@@@@@@@@@@[[`..............,[\\@@@@/[...................................@@OOoo\\*******/OOOO@O......,@@O[*************\n"
		   "@O`*********=*\\@^....,@@`*,**=@@@@@@@@/`................................................................=@^**,oOOoooOOo^,,@/.......O@@o=***********]`\\\n"
		   "@@\\***********=@`......\\@**^,*=@OOOO`....................................................................,@\\***********,O@`.......,O@Oo`***********=/\n"
		   "@@@\\********`,=@........@@,*=*^O@^.........................................................................\\@@]]]]]]/@@@\\..........@@o*`]]*,*`,//O@@@\n"
		   "@@@@@Oo******=@@........=@,=***,@@`...........................................................................*,[[`****.*.........=@O\\*^\\oOO@@@@@@OO//\n"
		   "OOOO@@@@@@O]`,@^........,@^^***//@@]`...............................................................................****..........=@@@@@@@@OOOOOOOO`....\n"
		   "**\\OOOOO@@@@@@@^.........@@@@@[[[[[[[\\@@^*.*.......................................................................................*@@@@OOOOOOOOO`**..\n"
		   "*****\\OOOOOOO@@........\\[[.............,@^.....................................................\\`..................................,@@@@OOOOOOO`*****\n"
		   "*******[OOOOO@@.........................@^.........................................................................................=@@@@OOOOO`**********\n"
		   "*.**....**,OO@/..................]]]]]]]@^.*......................................................................................./@@@@OOO`************\n"
		   "`*.*....****=@@`............./@@[`......[@^..............................]]]]OOO@@@@@OOO]]]]......................................=@@@@@O`**************\n"
		   "O*.*******.*@@=@`........................@/............................O@@@OOOOO@OOOOOO@@@@@@@@^.................................=@@@@@^****************\n"
		   "@^******.**=@^.,@@].....................//.............................O@OoOOOOOOOOOOOoOOO@@@@@^................................/@@O\\OO****************\n"
		   "@O******.*,/@.....[@@`..........]@@@@/[[@\\.............................O@OOOOOOOOOOOOOOOOOOO@@/.............................../@@O^**OO********.*******\n"
		   "@@^*******,@^.......@^........,[........=@.............................,@OOOOOOOOOOOOOOOOOOO@@.............................]O@@O[**.=@^.****************\n"
		   "=@O*******@@........@^.................=@@@@\\`..........................=@OOOOOOOOOOOOOOOOOOO..........................,/@@O[O@^****/O*****************\n"
		   "*O@\\******@^........\\@`.............../@@@@@@@@@O].......................,OOOOOOOOOOOOOOOOO[........................]@@@[*...O@^****OO***************,\n"
		   "欢迎使用TTMS影院管理系统\n");
	Account_Srv_InitSys(); // 创建Admin系统用户
	int x = 3;
	while (x > 0)
	{
		printf("您还有 %d 次登录机会!\n", x);
		char usrName[35], pwd[35];
		printf("请输入用户名 :");
		setbuf(stdin, NULL);
		scanf("%s", usrName);

		printf("请输入密码 :");
		setbuf(stdin, NULL);

		for (int i = 0; i < len1; i++)
		{
			pwd[i] = getch();
			if (pwd[i] == '\n')
			{
				pwd[i] = '\0';
				break;
			}

			if ((int)pwd[i] == 127)
			{
				printf("\b \b");
				i = i - 2;
			}
			else
			{
				printf("*");
			}
			if (i < 0)
				pwd[0] = '\0';
		}

		// printf("%s\n", pwd);
		unsigned char decrypt[16];
		MD5_CTX md5;
		MD5Init(&md5);
		MD5Update(&md5, pwd, strlen((char *)pwd));
		MD5Final(&md5, decrypt);

		if (Account_Srv_Verify(usrName, decrypt)) // 验证系统用户是否存在
		{
			printf("\nLogin successfully! welcome shawn_wang! []~（￣▽￣）~*");
			getchar();
			return 1;
		}
		else
		{
			printf("登录失败! ╮（￣▽￣）╭\n");
			x--;
		}
	}
	printf("%d\n", x);
	if (x == 0)
	{
		char cho;
		printf("忘记密码?  想要重置? （￣▽￣）~*\n[Y]es   or   [N]o:");
		scanf("%c", &cho);
		getchar();
		if (cho == 'Y' || cho == 'y')
		{
			MaiAccount_UI_Mgt();
		}
	}
	return 0;
}

char Account_UI_Status2Char(account_type_t status)
{
	if (status == 0)
		return 'N';
	else if (status == 1)
		return 'X';
	else if (status == 9)
		return 'A';
	else if (status == 2)
		return 'M';
}

void Account_UI_MgtEntry(void)
{
	if (gl_CurUser.type != USR_ADMIN)
	{
		printf("you can't join in there!please input the [Enter]");
		getchar();
		return;
	}

	int ii, id;
	char choice, usrName[20];

	account_list_t head;
	account_node_t *pos;
	Pagination_t paging;

	List_Init(head, account_node_t);
	paging.offset = 0;
	paging.pageSize = Account_PAGE_SIZE;

	paging.totalRecords = Account_Srv_FetchAll(head); // 构建head链表
	Paging_Locate_FirstPage(head, paging);
	do
	{
		printf("[N]匿名用户    |    [X]售票员     |     [M]经理     |     [A]系统管理员");
		printf(
			"\n==================================================================\n");
		printf(
			"******************* Account Management Interface *******************\n");
		printf("%3s  %18s  %23s  %16s\n", "ID", "username", "password",
			   "type");
		printf(
			"------------------------------------------------------------------\n");

		Paging_ViewPage_ForEach(head, paging, account_node_t, pos, ii)
		{
			printf("%3d  %18s  ", pos->data.id, pos->data.username);
			printf("%16s ", pos->data.password);
			printf("  %6c\n", Account_UI_Status2Char(pos->data.type));
		}

		printf(
			"------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
			paging.totalRecords, Pageing_CurPage(paging),
			Pageing_TotalPages(paging));
		printf(
			"******************************************************************\n");
		printf(
			"[P]revPage|[N]extPage | [A]dd | [D]elete | [Q]uery | [M]od | [R]eturn");
		printf(
			"\n==================================================================\n");

		printf("Your Choice:");
		setbuf(stdin, NULL);
		scanf("%c", &choice);
		getchar();
		switch (choice)
		{
		case 'a':
		case 'A':
			system("clear");

			if (Account_UI_Add(head))
			{
				paging.totalRecords = Account_Srv_FetchAll(head);
				// Paging_Locate_LastPage(head, paging, account_node_t);
			}
			else
			{
				printf("this user is already have\n");
			}
			break;
		case 'd':
		case 'D':
			system("clear");

			printf("Input the username:");
			setbuf(stdin, NULL);
			scanf("%s", usrName);
			getchar();
			if (Account_UI_Delete(head, usrName))
			{
				printf("delete accept\n");
				paging.totalRecords = Account_Srv_FetchAll(head);
				List_Paging(head, paging, account_node_t);
			}
			else
			{
				printf("delete error\n");
			}
			break;
		case 'q':
		case 'Q':
			system("clear");

			printf("Input the username:");
			setbuf(stdin, NULL);
			scanf("%s", usrName);
			getchar();
			if (Account_UI_Query(head, usrName))
			{
				paging.totalRecords = Account_Srv_FetchAll(head);
				List_Paging(head, paging, account_node_t);
			}
			else
			{
				printf("query error\n");
			}
			break;
		case 'm':
		case 'M':
			system("clear");

			printf("Input the username:");
			setbuf(stdin, NULL);
			scanf("%s", usrName);
			getchar();
			if (Account_UI_Modify(head, usrName))
			{
				printf("mod accept\n");
				paging.totalRecords = Account_Srv_FetchAll(head);
				List_Paging(head, paging, account_node_t);
			}
			break;
		case 'p':
		case 'P':
			system("clear");

			if (!Pageing_IsFirstPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, -1, account_node_t);
			}
			break;
		case 'n':
		case 'N':
			system("clear");

			if (!Pageing_IsLastPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, 1, account_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	List_Destroy(head, account_node_t);
}
int Account_UI_Add(account_list_t list)
{
	account_t data;
	int newRecCount = 0;
	char choice;

	do
	{
		printf("\n==================================================================\n");
		printf("**************************  Add New User **************************\n");
		printf("-------------------------------------------------------------------\n");
		printf("please input you want add newname :");
		setbuf(stdin, NULL);
		scanf("%s", data.username);

		getchar();
		printf("===================================================================\n");
		account_list_t temp = Account_Srv_FindByUsrName(list, data.username);
		if (temp != NULL)
		{
			printf("this user is already have\n");
			printf("[A]dd other, [R]eturn:");
			setbuf(stdin, NULL);
			scanf("%c", &choice);
			getchar();
		}
		else
		{
			printf("please input you want passsword :");
			setbuf(stdin, NULL);
			char password[35];
			//	scanf("%s", password);

			for (int i = 0; i < len1; i++)
			{
				password[i] = getchar();
				if (password[i] == '\n')
				{
					password[i] = '\0';
					break;
				}
				if ((int)password[i] == 127)
				{
					printf("\b \b");
					i = i - 2;
				}
				else
				{
					printf("*");
				}
				if (i < 0)
					password[0] = '\0';
			}

			unsigned char decrypt[16];
			MD5_CTX md5;
			MD5Init(&md5);
			MD5Update(&md5, password, strlen((char *)password));
			MD5Final(&md5, data.password);

			//	getchar();
			printf("please input you want type :\n");
			printf("===================================================================\n");
			printf("[0]匿名用户  |  [1]售票员  |  [2]经理  |  [9]系统管理员:");

			setbuf(stdin, NULL);
			scanf("%d", &data.type);
			getchar();
			printf("Please enter your security questions.\n");
			scanf("%s", data.mipao);
			getchar();

			if (Account_Srv_Add(&data))
			{
				newRecCount += 1;
				Account_Srv_FetchAll(list);
				printf("The new user added successfully!\n");
			}
			else
				printf("The new user added failed!\n");
			// getchar();
			printf("-------------------------------------------------------------------\n");
			printf("[A]dd more, [R]eturn:");
			setbuf(stdin, NULL);
			scanf("%c", &choice);
			char ch1;
			while ((ch1 = getchar()) != '\n' && ch1 != EOF)
				;
		}
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

// 修改系统用户界面
int Account_UI_Modify(account_list_t list, char usrName[])
{
	account_list_t temp = Account_Srv_FindByUsrName(list, usrName);
	if (temp != NULL)
	{
		int choice = 10;
		do
		{
			char password[20];
			printf("prease input the new password:");
			setbuf(stdin, NULL);
			int x;

			//	scanf("%s", password);

			for (int i = 0; i < len1; i++)
			{
				password[i] = getchar();
				if (password[i] == '\n')
				{
					password[i] = '\0';
					break;
				}
				if ((int)password[i] == 127)
				{
					printf("\b \b");
					i = i - 2;
				}
				else
				{
					printf("*");
				}
				if (i < 0)
					password[0] = '\0';
			}

			unsigned char decrypt[16];
			MD5_CTX md5;
			MD5Init(&md5);
			MD5Update(&md5, password, strlen((char *)password));
			MD5Final(&md5, decrypt);
			for (int i = 0; i < 16; i++)
			{
				if (decrypt[i] != temp->data.password[i])
					x = 0;
			}
			if (x)
			{
				printf("mod error,password the same,please choice next\n");
				printf("[0]exit  |   [1]input again\n");
				scanf("%d", &choice);
				setbuf(stdin, NULL);
			}
			else
			{
				for (int i = 0; i < 16; i++)
				{
					// printf("%02x", decrypt[i]);
					temp->data.password[i] = decrypt[i];
				}
				int aaa = Account_Srv_Modify(temp);
				if (aaa == 0)
				{
					return 0;
				}
				Account_Srv_FetchAll(list);

				return 1;
			}
		} while (choice != 0);
	}
	else
	{
		printf("The user does not exist!\n");
		return 0;
	}
}

// 删除系统用户界面
int Account_UI_Delete(account_list_t list, char usrName[])
{
	account_list_t temp = Account_Srv_FindByUsrName(list, usrName);
	if (temp != NULL)
	{
		Account_Srv_DeleteByID(temp->data.id);
		Account_Srv_FetchAll(list);
		return 1;
	}
	return 0;
}

// 查询用户界面
int Account_UI_Query(account_list_t list, char usrName[])
{
	account_list_t temp = Account_Srv_FindByUsrName(list, usrName);
	if (temp != NULL)
	{
		printf("user ID:%d\n", temp->data.id);
		printf("user password:\n");
		printf("%s ", temp->data.password);
		putchar('\n');
		printf("user username:%s\n", temp->data.username);
		printf("user type:%c\n", Account_UI_Status2Char(temp->data.type));

		return 1;
	}
	return 0;
}
