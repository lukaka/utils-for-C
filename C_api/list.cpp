/*����ṹ����ز���*/
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include "trace.h"
#include "list.h"


/*����һ������
��������
����ֵ�� ����  ͷ�ڵ�
		 ����	NULL
*/
pNODE_t List_create(void)
{
	pNODE_t Head = NULL;
	
	Head = (pNODE_t)malloc(sizeof(Node));
	if(Head == NULL)
	{
#if TRACE_ON
		printf("[ERROR] malloc failed. func:%s,line:%d", __FUNCTION__, __LINE__);
#endif
		return NULL;
	}
	
	Head->next = NULL;

#if TRACE_ON
	printf("[DEBUG] head create List success!\n");
#endif
	return Head;
}

/*ͷ�巨����һ���ڵ�
������
����ֵ��
	0	����
	-1	�쳣
*/
int List_insert_by_head(pNODE_t Head, ElemType data)
{
	if (Head == NULL)
	{
		printf("[ERROR] invalid para.\n");
		return -1;
	}

	pNODE_t p = NULL;
	p = (pNODE_t)malloc(sizeof(Node));
	if (p == NULL)
	{
		printf("[ERROR] malloc failed. func=%s,line:%d\n",__FUNCTION__,__LINE__);
		return -1;
	}
	p->data = data;
	p->next = Head->next;
	Head->next = p;

#if TRACE_ON
	printf("[DEBUG] head insert List success!\n");
#endif
	return 0;
}

/*β�巨����һ���ڵ�
������
����ֵ��
	0	����
	-1	�쳣
*/
int List_insert_by_tail(pNODE_t Head, ElemType data)
{
	if (Head == NULL)
	{
		printf("[ERROR] invalid para.\n");
		return -1;
	}
	pNODE_t p = Head;

	while (p->next)
	{
		p = p->next;
	}
	pNODE_t node = NULL;
	node = (pNODE_t)malloc(sizeof(Node));
	if (node == NULL)
	{
		printf("[ERROR] malloc failed. func=%s,line:%d\n", __FUNCTION__, __LINE__);
		return -1;
	}
	node->data = data;
	node->next = NULL;
	p->next = node;

#if TRACE_ON
	printf("[DEBUG] head insert List success!\n");
#endif
	return 0;
}

/*����index����һ���ڵ�*/
int List_insert_by_index(pNODE_t Head, ElemType data, int index)
{
	if ((Head == NULL)||(index <= 0))
	{
		printf("[ERROR] invalid para.\n");
		return -1;
	}
	if (Head->next == NULL)
	{
		printf("empty List, return NULL\n");
		return NULL;
	}

	int i = 0;
	pNODE_t p = Head;
	while (p)
	{
		if (i == index)
		{
			break;
		}
		i++;
		p = p->next;
	}

	if (i < index)
	{
		printf("[ERROR] index overflow!\n");
		return -1;
	}
	else
	{
		printf("index found!\n");
		
		pNODE_t node = (pNODE_t)malloc(sizeof(node));
		if (node == NULL)
		{
			printf("[ERROR] malloc failed. func=%s,line:%d\n", __FUNCTION__, __LINE__);
			return -1;
		}
		node->data = data;
		node->next = p->next;
		p->next = node;
	}

	return 0;
}

/*��ȡ����β���Ľڵ�
����:
����ֵ��
*/
ElemType List_get_elem_by_tail(pNODE_t Head)
{
	if (Head == NULL)
	{
		printf("[ERROR] invalid para.\n");
		return -1;
	}
	pNODE_t p = Head;
	if (p->next == NULL)
	{
		printf("empty List, return NULL\n");
		return NULL;
	}

	while (p->next)
	{
		p = p->next;
	}

#if TRACE_ON
	printf("[DEBUG]get tail element success:%d\n",p->data);
#endif
	return p->data;
}

/*��ȡ����ͷ���ĵ�һ���ڵ�
������
����ֵ��
*/
ElemType List_get_elem_by_head(pNODE_t Head)
{
	if (Head == NULL)
	{
		printf("[ERROR] invalid para.\n");
		return -1;
	}
	
	if (Head->next == NULL)
	{
		printf("empty List, return NULL\n");
		return NULL;
	}

#if TRACE_ON
	printf("[DEBUG]get tail element success:%d\n", (Head->next)->data);
#endif
	return (Head->next)->data;
}

/*��ȡ����ָ���ڵ��ֵ*/
ElemType List_get_elem_by_index(pNODE_t Head, int index)
{
	if ((Head == NULL)||(index <= 0))
	{
		printf("[ERROR] invalid para.\n");
		return -1;
	}

	if (Head->next == NULL)
	{
		printf("empty List, return NULL\n");
		return NULL;
	}

	int i = 0;
	pNODE_t p = Head;
	while (p)
	{
		if (i == index)
		{
			break;
		}
		i++;
		p = p->next;
	}

	if (i < index)
	{
		printf("[ERROR] index overflow!\n");
		return NULL;
	}
	else
	{
		printf("get element by index:%d success,data:%d\n",index,p->data);
		return p->data;
	}
}

/*��ӡ����
������
����ֵ��
ע�������ӡҪע��ElemType������
*/
int List_print(pNODE_t Head)
{
	if(Head == NULL)
	{
		printf("[ERROR] invalid para.\n");
		return -1;
	}

	if (Head->next == NULL)
	{
		printf("empty List, return NULL\n");
		return NULL;
	}

	pNODE_t p = Head->next;

	printf("List print:\n");
	while (p)
	{
		printf("%d, ",p->data);
		p = p->next;
	}
	printf("end.\n");

	return 0;
}


/*ɾ��ͷ�ڵ�֮��ĵ�һ���ڵ�
������
����ֵ��
	0	����
	-1	�쳣
*/
int List_delete_elem_by_head(pNODE_t Head)
{
	if (Head == NULL)
	{
		printf("[ERROR] invalid para.\n");
		return -1;
	}
	if (Head->next == NULL)
	{
		printf("empty List, return NULL\n");
		return -1;
	}

	pNODE_t p = Head->next;

	Head->next = p->next;
	p->next = NULL;
	free(p);

#if TRACE_ON
	printf("[DEBUG] head delete List success!\n");
#endif
	return 0;
}

/*β�巨ɾ��һ���ڵ�
������
����ֵ��
	0	����
	-1	�쳣
*/
int List_delete_elem_by_tail(pNODE_t Head)
{
	if (Head == NULL)
	{
		printf("[ERROR] invalid para.\n");
		return -1;
	}

	if (Head->next == NULL)
	{
		printf("empty List, return NULL\n");
		return -1;
	}

	pNODE_t p = Head;
	pNODE_t node = Head;

	while (p->next)
	{
		node = p;
		p = p->next;
	}
	
	node->next = NULL;
	free(p);

#if TRACE_ON
	printf("[DEBUG] tail delete List success!\n");
#endif
	return 0;
}

/*����index����һ���ڵ�*/
int List_delete_elem_by_index(pNODE_t Head, int index)
{
	if ((Head == NULL) || (index <= 0))
	{
		printf("[ERROR] invalid para.\n");
		return -1;
	}

	if (Head->next == NULL)
	{
		printf("empty List, return NULL\n");
		return NULL;
	}

	int i = 0;
	pNODE_t p = Head;
	pNODE_t node = Head;

	while (p)
	{
		if (i == index)
		{
			break;
		}
		i++;
		node = p;
		p = p->next;
	}

	if (i < index)
	{
		printf("[ERROR] index overflow!\n");
		return -1;
	}
	else
	{
		printf("index found!\n");
		node->next = p->next;
		p->next = NULL;
		free(p);
		printf("delete success!\n");
	}

	return 0;
}

/*ɾ����������*/
int List_delete(pNODE_t Head)
{
	if (Head == NULL)
	{
		printf("[ERROR] invalid para.\n");
		return -1;
	}

	pNODE_t p = Head;
	pNODE_t node;
	while (p)
	{
		node = p;
		p = p->next;
		node->next = NULL;
		free(node);
	}

	printf("List delete success!\n");
	return 0;
}

/*����API����*/
void List_test(void)
{
	pNODE_t list = NULL;

	list = List_create();
	List_insert_by_head(list, 6);
	List_insert_by_head(list, 7);
	List_insert_by_head(list, 8);
	List_insert_by_tail(list, 4);
	List_insert_by_tail(list, 3);
	List_insert_by_tail(list, 2);

	printf("get list head:%d\n", List_get_elem_by_head(list));
	printf("get list tail:%d\n", List_get_elem_by_tail(list));
	printf("get list by index 4:%d\n", List_get_elem_by_index(list, 4));
	List_print(list);
	List_insert_by_index(list, 5, 4);
	List_print(list);
	List_delete_elem_by_index(list, 2);
	List_print(list);
	List_delete_elem_by_head(list);
	List_print(list);
	List_delete_elem_by_tail(list);
	List_print(list);
//	List_delete(list);
}