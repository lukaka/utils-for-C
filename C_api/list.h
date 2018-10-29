#pragma once
#ifndef __LIST_H
#define __LIST_H

typedef int ElemType;
typedef struct Node
{
	ElemType data;
	struct Node *next;
}NODE_t,*pNODE_t;


pNODE_t List_create(void);
int List_insert_by_head(pNODE_t Head, ElemType data);
int List_insert_by_tail(pNODE_t Head, ElemType data);
int List_insert_by_index(pNODE_t Head, ElemType data,int index);
ElemType List_get_elem_by_tail(pNODE_t Head);
ElemType List_get_elem_by_head(pNODE_t Head);
ElemType List_get_elem_by_index(pNODE_t Head, int index);
ElemType List_delete_elem_by_tail(pNODE_t Head);
ElemType List_delete_elem_by_head(pNODE_t Head);
ElemType List_delete_elem_by_index(pNODE_t Head, int index);
int List_print(pNODE_t Head);
int List_delete(pNODE_t Head);
void List_test(void);

#endif
