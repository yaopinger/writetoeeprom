/** \file list.h
 *
 * �������������ͺ궨��
 *
 */
#ifndef _LIST_H
#define _LIST_H
/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

typedef struct list_head {
	struct list_head *next, *prev;
}list_head;

#define list_head_init(name) { &(name), &(name) }

#define list_head_def(name) struct list_head name = list_head_init(name)

#define init_list_head(ptr) do { (ptr)->next = (ptr); (ptr)->prev = (ptr); } while (0)

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 * ��prev��nextָ�������������һ���½��
 */
static void __list_add(struct list_head *newnode,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = newnode;
	newnode->next = next;
	newnode->prev = prev;
	prev->next = newnode;
}

/**
 * list_add - add a new entry
 * @param new: new entry to be added
 * @param head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 * �������ӵ������ͷ������
 */
/*static void list_add(struct list_head *newnode, struct list_head *head)
{
	__list_add(newnode, head, head->next);
}*/

/**
 * list_add_tail - add a new entry
 * @param new: new entry to be added
 * @param head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 * �������ӵ������ĩ��
 */
inline static void list_add_tail(struct list_head *newnode, struct list_head *head)
{
	__list_add(newnode, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 * ɾ��һ����㣬nextָ���Ϊ��ɾ�����ĺ�һ����㣬prevָ���Ϊ��ɾ������ǰһ�����
 */
static void __list_del(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}

/**
 * list_del - deletes entry from list.
 * @param entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is in an undefined state.
 * ɾ��entry��ָ�Ľ�㣬ͬʱ��entry��ָ��Ľ��ָ���������
 */

static void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = (void *) 0;
	entry->prev = (void *) 0;
}

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @param entry: the element to delete from the list.
 * ɾ��entry��ָ��Ľ�㣬ͬʱ��entry��ָ��Ľ���next��prevָ����ָ������
 */
inline static void list_del_init(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	init_list_head(entry);
}

/**
 * list_move - delete from one list and add as another's head
 * @param list: the entry to move
 * @param head: the head that will precede our entry
 * ��list��ָ��Ľ���Ƶ������ͷ������
 */
/*static void list_move(struct list_head *list, struct list_head *head)
{
		__list_del(list->prev, list->next);
		list_add(list, head);
}*/

/**
 * list_move_tail - delete from one list and add as another's tail
 * @param list: the entry to move
 * @param head: the head that will follow our entry
 *��list��ָ��Ľ���Ƶ������ĩ��
 */
/*static void list_move_tail(struct list_head *list,
				  struct list_head *head)
{
		__list_del(list->prev, list->next);
		list_add_tail(list, head);
}*/

/**
 * list_empty - tests whether a list is empty
 * @param head: the list to test.
 * �ж������Ƿ�ֻ��һ����㣨Ϊ�գ�������Ǿͷ���1����ͷ���0
 */
inline static int list_empty(struct list_head *head)
{
	return head->next ==head;
}
/**����list�����head����listΪ�����ϵģ���ͷ����ɾ��
*/
/*static void __list_splice(struct list_head *list,
				 struct list_head *head)
{
	struct list_head *first = list->next;
	struct list_head *last = list->prev;
	struct list_head *at = head->next;

	first->prev = head;
	head->next = first;

	last->next = at;
	at->prev = last;
}*/

/**
 * list_splice - join two lists
 * @param list: the new list to add.
 * @param head: the place to add it in the first list.
 * ���list����Ϊ�գ�������list��head
 */
/*static void list_splice(struct list_head *list, struct list_head *head)
{
	if (!list_empty(list))
		__list_splice(list, head);
}*/

/**
 * list_splice_init - join two lists and reinitialise the emptied list.
 * @param list  the new list to add.
 * @param head  the place to add it in the first list.
 *
 * The list at @param list is reinitialised
 */
/*static void list_splice_init(struct list_head *list,
				    struct list_head *head)
{
	if (!list_empty(list)) {
		__list_splice(list, head);
		init_list_head(list);
	}
}*/

/**\brief list_entry - get the struct for this entry
 *
 * @param ptr 	the &struct list_head pointer.
 * @param type 	the type of the struct this is embedded in.
 * @param member 	the name of the list_struct within the struct.
 *
 * list_entry()�������ڽ�ָ��ĳ�������Ա��ָ�������������Ŀ�ʼ������ָ��
ת��Ϊ������������͡�
* ptr��ָ��list_head���������ָ�룬typeΪһ���ṹ��
  ��memberΪ�ṹtype�е�һ��������Ϊlist_head������귵��ָ��type�ṹ��ָ��
 */
#define list_entry(ptr, type, member)  ((type *)((char *)(ptr)-((char *)(&((type *)ptr)->member)-(char *)(ptr))))

/**
 * list_for_each	-	iterate over a list
 * @param pos:	the &struct list_head to use as a loop counter.
 * @param head:	the head for your list.
 * ������
 */
#define list_for_each(pos, head) for ((pos) = (head)->next; (pos) != (head); (pos) = (pos)->next)
/**
 * list_for_each_prev	-	iterate over a list backwards
 * @param pos:	the &struct list_head to use as a loop counter.
 * @param head:	the head for your list.
 * ��ǰ����
 */
#define list_for_each_prev(pos, head) \
	for ((pos) = (head)->prev; (pos) != (head); (pos) = (pos)->prev)

/**
 * list_for_each_safe	-	iterate over a list safe against removal of list entry
 * @param pos:	the &struct list_head to use as a loop counter.
 * @param n:		another &struct list_head to use as temporary storage
 * @param head:	the head for your list.
 * �߱�����ɾ��
 */

#define list_for_each_safe(pos, n, head) \
	for ((pos) = (head)->next, n = (pos)->next; (pos) != (head); \
		(pos) = n, n = (pos)->next)

#endif

