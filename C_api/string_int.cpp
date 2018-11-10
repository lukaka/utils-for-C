/*���е�api���ڴ��ļ���ʵ��*/
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_int.h"



//------------------�����������---------------//
/*�ж��Ƿ���'0'-'9'
����ֵ�� 1   ������
		 0	 ��������
*/
unsigned int isDigital(char num)
{
	if (num >= '0' && num <= '9')
		return 1;
	else
		return 0;
}

/*�ж��ǲ�����ĸ*/
/*����ֵ�� 1   ������
		   0   ��������
*/
unsigned int isAlpha(char a)
{
	return 0;
}

/*�ַ���������ת������������*/
// "123" --> 123
int str2int(char *str)
{
	int num = 0;
	char *ptr = str;

	if (str == NULL)
	{
		printf("ERROR, invalid para. line:%d, func:%s\n",__LINE__,__FUNCTION__);
		return -1;
	}

	while (*ptr)
	{
		if (isDigital(*ptr))
		{
			num *= 10;
			num += (*ptr - '0');
		}
		ptr++;
	}
	//printf("str2int, str: %s, int: %d\n",ptr,num);
	
	return num;
}

/*��������ת�����ַ���
ע��������������Ҫ��֤strִָ��ĺϷ���
*/
int int2str(int num, char *str)
{
	char num_str[1024] = {0};//TODO:�滻��malloc������ڴ�
	int num_tmp = num;
	int i = 0;
	if (str == NULL)
	{
		printf("ERROR: invalid para.line:%d, func=%s\n",__LINE__,__FUNCTION__);
		return -1;
	}
	while (num_tmp)
	{
		str[i] = (num_tmp % 10) + '0';
		num_tmp /= 10;
		i++;
	}
	str[i] = '\0';

	str_reverse(str);
	//printf("int: %d, output str:%s\n",num, str);

	return 0;
}

/*�ַ�����ת*/
int str_reverse(char *str)
{
	int len = 0;
	char *ptr = str;
	char tmp;

	if (str == NULL)
	{
		printf("ERROR: invalid para.line:%d, func=%s\n", __LINE__, __FUNCTION__);
		return -1;
	}
	len = strlen(str);
	ptr = str;
	for (int i = 0; i < len / 2; i++)
	{
		tmp = ptr[i];
		ptr[i] = ptr[len - i - 1];
		ptr[len - i - 1] = tmp;
	}

	return 0;
}

/*��������ȥ��*/
//�������鳤��
//ʱ�临�Ӷȣ�O(n^2)
int Int_Deduplicated(int InNum[], int len)
{
	int i, j;
	int *num_tmp = NULL;
	int len_tmp = 0;
	int duplicated_flag = 0;

	if (InNum == NULL || len < 1)
	{
		printf("ERROR: invalid input, line:%d!\n",__LINE__);
		return -1;
	}

	num_tmp = (int *)malloc(len * sizeof(int));
	if (num_tmp == NULL)
	{
		printf("ERROR: malloc failed, line:%d\n",__LINE__);
		return -1;
	}
	memset(num_tmp, 0, sizeof(num_tmp));

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < len_tmp; j++)
		{
			if (InNum[i] == num_tmp[j])
				duplicated_flag = 1;
		}
		if (duplicated_flag == 0)
		{
			num_tmp[len_tmp++] = InNum[i];
		}
		else
		{
			duplicated_flag = 0;
		}
	}

	memset(InNum, 0, len * sizeof(int));
	memcpy(InNum, num_tmp, len_tmp * sizeof(int));
	free(num_tmp);
	num_tmp = NULL;

	printf("\nOutNum:");
	for (i = 0; i < len_tmp; i++)
		printf("%d,",InNum[i]);

	return len_tmp;
}

//��һ��ʵ��
//ʱ�临�Ӷȣ�O(n)
//TODO:

/*��������ֻ��������N������*/
int Int_docker_top2(int num, int output[])
{
	int num_list[2] = {0};
	static int flag = 0;
	int tmp;

	if (output == NULL)
	{
		printf("ERROR, invalid para. line:%d, func:%s\n", __LINE__, __FUNCTION__);
		return -1;
	}

	if (flag == 0)
	{
		output[0] = num;
		flag++;
	}
	else if (flag == 1)
	{
		if (num > output[0])
		{
			output[1] = output[0];
			output[0] = num;
			flag++;
		}
		else
		{
			output[1] = num;
		}
	}
	else
	{
		if (num > output[0])
		{
			tmp = output[0];
			output[0] = num;
			output[1] = tmp;
		}
		else if (num <= output[0] && num >= output[1])
		{
			output[1] = num;
		}
	}

	return 0;
}

#define N 10
int Int_docker_top2_test()
{
	printf("--------------Int_docker_top2 ����--------------");
	int num_list[N] = { 1,2,3,3,9,9,8,7,65,65};
	int num_top2[2] = { 0 };
	int i;

	for (i = 0; i < N; i++)
	{
		Int_docker_top2(num_list[i], num_top2);
	}

	printf("\nnum_list: ");
	for (i = 0; i < N; i++)
	{
		printf("%d,", num_list[i]);
	}
	printf("\ntop2: ");
	for (i = 0; i < 2; i++)
	{
		printf("%d, ", num_top2[i]);
	}

	return 0;
}
//-----------------�ַ�������------------------//



//-----------------����&����------------------//


/*���Ժ���*/
int string_int_test()
{
	char num_str[10] = "12345";
	char str[10] = {0};

	Int_docker_top2_test();
	printf("\n-----str2int-----\n  str:%s, int:%d\n",num_str,str2int(num_str));

	int2str(str2int(num_str), str);
	printf("\n-----int2str-----\n  int:%d, str:%s\n", str2int(num_str), str);

	str_reverse(num_str);
	printf("\n-----reverse-----\n  output:%s\n", num_str);

	return 0;
}