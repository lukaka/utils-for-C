
#include "pch.h"
#include <iostream>
#include "string_int.h"
#include "trace.h"
#include "list.h"



int main()
{
	int num[10] = {1,2,2,3,4,4,6,6,7,8};
//	PRINT("hello world:%d", 318);

	//Int_Deduplicated(num,10);
	//TraceDBG(0,"this is my debug info:\n");
	//TraceDBG(2,"hello world:%d,%d\n",num[3],num[4]);
	//TraceDBG(1,"parameters longer than %d\n",num[1],num[2]);
	//TraceERR(0,"debug error!");
	//TraceWARN(0, "debug warning!");
	
	List_test();
	return 0;
}
