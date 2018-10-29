/*���е�api���ڴ��ļ���ʵ��*/
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




//------------------�����������---------------//
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


//-----------------�ַ�������------------------//



//-----------------����&����------------------//