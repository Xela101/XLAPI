/*
	Copyright (C) 2012  Alex White

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "XL_List_Struct.h"

void new_LinkedList(LinkedList **);
void addItem(LinkedList*,void*);
void deleteItem(LinkedList*,void*);
void showItems(LinkedList*);

void new_LinkedList(LinkedList **list){
	LinkedList *new_list=(struct LinkedList*)malloc(sizeof(struct LinkedList));
	new_list->size=0;
	*list=new_list;
}

void addItem(LinkedList *list,void *item){
	Node *conductor=list->start;
	if(list->size!=0){
		Node *temp=(struct Node*)malloc(sizeof(struct Node));
		temp->data=item;
		temp->id=list->size;
		while(conductor->next!=NULL){
			conductor=conductor->next;
		}
		temp->next=NULL;
		conductor->next=temp;
		list->size++;
	}
	else{
		list->start=(struct Node*)malloc(sizeof(struct Node));
		list->start->data=item;
		list->start->id=list->size;
		list->start->next=NULL;
		list->size++;
	}
}

void deleteItem(LinkedList *list,void *item){
	Node *conductor=list->start;
	if(conductor->data==item){
		if(conductor->next!=NULL){
			Node *nextNode=conductor->next;
			free(list->start);
			list->start=NULL;
			list->start=nextNode;
			list->size--;
		}
		else{
			free(list->start);
			list->start=NULL;
			list->start=(struct Node*)malloc(sizeof(struct Node));
			list->size=0;
		}
	}
	else{
		Node *pNode;
		for(conductor=list->start;conductor!=NULL;pNode=conductor,conductor=conductor->next){
			if(conductor->data==item){
				pNode->next=conductor->next;
				free(conductor);
				conductor=NULL;
				list->size--;
				break;
			}
		}
	}
}

void showItems(LinkedList *list){
	Node *conductor=list->start;
	if(list->size!=0){
		if(conductor->next==NULL){
			printf("Node ID: %d\n",conductor->id);
			conductor=conductor->next;
		}
		else{
			while(conductor->next!=NULL){
				printf("Node ID: %d\n",conductor->id);
				conductor=conductor->next;
				if(conductor->next==NULL) printf("Node ID: %d\n",conductor->id);
			}
		}
	}
	else{
		printf("List empty\n");
	}
}