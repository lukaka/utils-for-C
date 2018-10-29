/*trace.c*/
#include "pch.h"
#include <stdio.h>
#include <stdarg.h>
#include "trace.h"

void TraceERR(int numArgs, const char *fmt, ...)
{
	if ((fmt == NULL) || (numArgs < 0) || (numArgs > 10))
	{
		printf("[ERROR] invalid input! --func:%s,line:%d\n",__FUNCTION__,__LINE__);
		return;
	}

	if (TRACE_ON)
	{
		if (numArgs >= 1)
		{
			int num_tmp = 0;
			int num = numArgs;
			va_list pArgs = NULL;
			va_start(pArgs, fmt);

			printf("[ERROR] ");
			while (num)
			{
				int dwVarArg = va_arg(pArgs, int);
				printf(fmt, dwVarArg);
				num--;
				num_tmp++;
				if (num_tmp > numArgs)
				{
					printf("[WARNING] parameters overflow, loop break!\n");
					break;
				}
			}
			va_end(pArgs);
		}
		else
		{
			printf("[ERROR] ");
			printf(fmt);
			printf("--func:%s,line:%d\n",__FUNCTION__,__LINE__);
		}
	}
	return;
}

void TraceWARN(int numArgs, const char *fmt, ...)
{
	if ((fmt == NULL) || (numArgs < 0) || (numArgs > 10))
	{
		printf("[ERROR] invalid input! func:%s,line:%d\n", __FUNCTION__, __LINE__);
		return;
	}

	if (TRACE_ON)
	{
		if (numArgs >= 1)
		{
			int num_tmp = 0;
			int num = numArgs;
			va_list pArgs = NULL;
			va_start(pArgs, fmt);

			printf("[WARNING] ");
			while (num)
			{
				int dwVarArg = va_arg(pArgs, int);
				printf(fmt, dwVarArg);
				num--;
				num_tmp++;
				if (num_tmp > numArgs)
				{
					printf("[WARNING] parameters overflow, loop break!\n");
					break;
				}
			}
			va_end(pArgs);
		}
		else
		{
			printf("[WARNING] ");
			printf(fmt);
			printf("func:%s,line:%d\n", __FUNCTION__, __LINE__);
		}
	}
	return;
}

void TraceDBG(int numArgs,const char *fmt, ... )
{
	if ((fmt == NULL) || (numArgs < 0) || (numArgs > 10))
	{
		printf("[ERROR] invalid input! func:%s,line:%d", __FUNCTION__, __LINE__);
		return;
	}

	if (TRACE_ON)
	{
		if (numArgs >= 1)
		{
			int num_tmp = 0;
			int num = numArgs;
			va_list pArgs = NULL;
			va_start(pArgs, fmt);

			printf("[TRACE] ");
			while (num)
			{
				int dwVarArg = va_arg(pArgs, int);
				printf(fmt, dwVarArg);
				num --;
				num_tmp ++;
				if (num_tmp > numArgs)
				{
					printf("[WARNING] parameters overflow, loop break!\n");
					break;
				}
			}
			va_end(pArgs);
		}
		else
		{
			printf("[TRACE] ");
			printf(fmt);
		}
	}
	return;
}
