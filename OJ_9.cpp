#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_NUM_MAX 32
#define CMD_STR_LEN_MAX 32
#define CMD_PARAM_LEN_MAX 32

typedef unsigned int(*FUNC)(char *pPara);
typedef struct {
	unsigned int index;		//记录命令行的索引值
	char		 cmd[CMD_NUM_MAX];		//命令行
	unsigned int nof_param;	//命令行参数化个数
	FUNC		 proc;		//命令行回调函数
}CMD_T;

CMD_T cmd_list[CMD_NUM_MAX]; //存储命令行集合
unsigned int cmd_count = 0;	//记录已注册命令行的个数

bool isCmdExit(const char *in_cmd)
{
	for (unsigned int i = 0; i < cmd_count; i++)
	{
		if (0 == strcmp(in_cmd, cmd_list[i].cmd))
		{
			return true;
		}
	}
	return false;
}

bool RegisterCmd(const char *pCmd, const unsigned char ucParaNumber, FUNC pfunction)
{
	/*参数合法性检查*/
	if ((pCmd == NULL) || (pfunction == NULL))
	{
		printf("invalid param.\n");
		return false;
	}
	if (cmd_count > CMD_NUM_MAX)
	{
		printf("sorry, cmds overflow!\n");
		return false;
	}
	if ((strlen(pCmd) == 0) || (strlen(pCmd) > CMD_STR_LEN_MAX))
	{
		printf("invalid cmd length! %d\n",strlen(pCmd));
		return false;
	}
	if (isCmdExit(pCmd))
	{
		printf("Oop! %s exit!",pCmd);
		return false;
	}

	//将新命令加入命令集
	memcpy(cmd_list[cmd_count].cmd, pCmd, strlen(pCmd)*sizeof(char));	//危险函数，注意使用！
	cmd_list[cmd_count].index = cmd_count;
	cmd_list[cmd_count].nof_param = ucParaNumber;
	cmd_list[cmd_count].proc = pfunction;

	printf("%s register success! index:%d, nof_param:%d\n", cmd_list[cmd_count].cmd, 
							cmd_list[cmd_count].index, cmd_list[cmd_count].nof_param);
	cmd_count++;
	return true;
}

/*参数说明：
FullCmd: 输入的命令行，包括命令子和参数
cmd: 输出的命令字，内存有外部函数申请和释放,并并保证不越界
nof_param: 输出的参数个数，内存由外部函数申请和释放，并保证不越界
*/
bool CmdParse(const char *FullCmd, char *cmd, char *param)
{
	/*参数合法性检查*/
	if ((FullCmd == NULL) || (cmd == NULL) || (param == NULL))
	{
		printf("invalid param.!\n");
		return false;
	}
	char cmd_buf[CMD_STR_LEN_MAX] = { 0 };
	char param_buf[CMD_PARAM_LEN_MAX] = { 0 };
	const char *fcmd = FullCmd;
	int cmd_len = 0;
	unsigned int i = 0;

	/*查找命令的位置及其长度*/
	while (*fcmd)
	{
		if (*fcmd != ':')
		{
			cmd_len++;
			fcmd++;
		}
		else
		{
			break;
		}
	}
	if (cmd_len == 0)
	{
		printf("error, length of cmd can not be 0!\n");
		return false;
	}
	if (cmd_len > CMD_STR_LEN_MAX)
	{
		printf("error, cmd len overflow!\n");
		return false;
	}

	/*命令行解析*/
	memcpy(cmd, FullCmd, cmd_len * sizeof(char));	//危险函数，注意使用！

	if ((strlen(FullCmd) - cmd_len) == 1)	//输入为：“cmd:”的情况
	{
		printf("invalid cmd format!\n");
		return false;
	}

	if ((strlen(FullCmd) - cmd_len) == 0)
	{
		printf("cmd parse complete! cmd:%s, no param.\n",cmd);
		return true;
	}

	if ((strlen(FullCmd) - cmd_len) > 1)
	{
		memcpy(param, FullCmd + cmd_len + 1, (strlen(FullCmd) - cmd_len - 1) * sizeof(char));	//要去掉":"一个字节
		if (strlen(param) > CMD_PARAM_LEN_MAX)
		{
			printf("error, param len overflow!\n");
			return false;
		}
		else
		{
			//TODO: 参数合法性验证：多个逗号在一起
			printf("cmd parse complete! cmd:%s, param:%s \n", cmd, param);
			return true;
		}
	}
}

int GetParamCount(char *param)
{
	int count = 1;		//最后一个参数后面没有逗号，所以count应该从1开始数

	if (param == NULL)
	{
		printf("error, invalid param!\n");
		return -1;
	}

	while (*param)
	{
		if (*param == ',')
		{
			count++;
		}
		param++;
	}
	printf("param count=%d\n",count);

	return count;
}

FUNC CmdMatch(char *in_cmd, int param_count, int *res)
{
	for (unsigned int i = 0; i < cmd_count; i++)
	{
		if (0 == strcmp(in_cmd, cmd_list[i].cmd))
		{
			printf("cmd match! ready to return the func: 0x%x.\n", cmd_list[i].proc);
			if (param_count != cmd_list[i].nof_param)
			{
				printf("param count not match!\n");
				*res = -2;
				return NULL;
			}

			return cmd_list[i].proc;
			return 0;
		}
	}
	printf("cmd not match!\n");
	*res = -1;
	return NULL;
}


int CmdHandle(const char *pFullCmd)
{
	char cmd_buf[CMD_NUM_MAX] = {0};
	char param_buf[CMD_PARAM_LEN_MAX] = {0};
	FUNC pfunc = NULL;
	int res = 0;
	int param_count;

	/*参数合法性检查*/
	if (pFullCmd == NULL)
	{
		printf("invalid param!\n");
		return -2;
	}

	if (true != CmdParse(pFullCmd, cmd_buf, param_buf))
	{
		printf("invalid param!\n");
		return -2;
	}

	/*计算参数个数，*/
	param_count = GetParamCount(param_buf);
	//return 1;
	//从命令集中查找命令，同时检查参数个数是否匹配,获取回调函数
	pfunc = CmdMatch(cmd_buf, param_count, &res);
	if(pfunc == NULL)
	{
		return res; //没找到命令
	}

	//调用回调函数
	if (pfunc != NULL && *pfunc != NULL)
	{
		return (*pfunc)(param_buf);
	}

	//函数不会执行到此处
}

unsigned int Cmd1Callback(char *para)
{
	printf("This is Cmd1Callback! para: %s\n",para);
	return 0;
}

bool ClrCmd(void)
{
	memset(&cmd_list[0],0,sizeof(CMD_T)*CMD_NUM_MAX);
	cmd_count = 0;
	return true;
}

int main()
{
    //清空命令行
	if (true != ClrCmd())
	{
		printf("ClrCmd failed!\n");
		return false;
	}

	//注册命令行
	if (true != RegisterCmd("cmd1", 3, Cmd1Callback))
	{
		printf("Cmd1 register failed!\n");
		return false;
	}

	//相应命令行
	int res = CmdHandle("cmd1:p1,p2,p3");
	if ( res < 0)
	{
		printf("Cmd1 handle error! ret=%d\n",res);
		return false;
	}

	RegisterCmd("cmd2", 3, Cmd1Callback);
	RegisterCmd("cmd3", 3, Cmd1Callback);
	RegisterCmd("cmd4", 0, Cmd1Callback);
	CmdHandle("cmd2:p4,p5,p6");
	CmdHandle("cmd3:p4,p5,p6");
	CmdHandle("cmd3:p4,p6");
	CmdHandle("cmd4");
	CmdHandle("cmd5:p4,p5,p6");


	return 0;
}

