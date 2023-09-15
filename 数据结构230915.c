#include<stdio.h>
struct ShoppingItem {
 char name[50]; // ��Ʒ����
 int quantity; // ��Ʒ����
 struct ShoppingItem* next; // ָ����һ���ڵ��ָ��
};
	struct ShoppingItem* shoppingList = NULL;
int main()
{
	while(1){
	printf("�� 1 �����Ʒ������\n");
	printf("�� 2 �Ƴ���Ʒ\n");
	printf("�� 3 �鿴�����嵥\n");
	printf("�� 4 �޸��嵥����Ʒ����\n");
	printf("�� 5 ��չ����嵥\n");
	printf("�� 6 �����嵥����Ʒ��������\n");
	printf("�� 7 �����嵥�е���Ʒ\n");
	printf("�� 8 �嵥����Ʒ����\n");
	printf("�� 9 �ϲ������嵥\n");
	printf("-----------------------------------\n");
	int select;
	int check;
	scanf("%d",&select);
		char itemName[20];
		int itemQuantity;
	if(select==1)
	{
		printf("������Ʒ��\n");
		scanf("%s",itemName);
		printf("��������\n");
		scanf("%d",&itemQuantity);
		addItem(itemName, itemQuantity);
	}
	if(select==2)
	{
		printf("����Ҫɾ������Ʒ��\n");
		scanf("%s",itemName);
		findItem( itemName);
		printf("����Ҫɾ��������\n");
		int deleteAll;
		scanf("%d",&deleteAll);
		deleteItem(itemName, deleteAll);
		printf("ɾ���ɹ�\n"); 
	}
	if(select==3)
	{
		printf("\n\n");
		displayList();
		printf("\n\n"); 
	}
	if(select==4)
	{
		printf("����Ҫ�޸ĵ���Ʒ��\n"); 
		scanf("%s",itemName);
		printf("�����޸ĺ������\n"); 
		scanf("%d",&itemQuantity) ;
		updateQuantity(itemName,itemQuantity);
	}
	if(select==5)
	{
		printf("ȷ��Ҫ��չ����嵥��\n���ǡ��밴 1 \n�����밴 0 \n");
		scanf("%d",&check);
		if(check==1)
		clearList();
		check=0;		
	}
	if(select==6)
	totalQuantity();
	if(select==7)
	{
		printf("������Ʒ��\n");
		scanf("%s",itemName);
		findItem( itemName);
	}
	if(select==8)
	{
		sortList();
		printf("����ɹ�\n"); 
	}
	if(select==9)
	{
		printf("����δ����\n"); 
		//printf("����Ҫ�ϲ��������嵥���м��ûس��ָ�")
		//mergeLists(* list1,* list2);
	}

}
	return 0;
}
void addItem(char itemName[], int itemQuantity) {
    struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
    strcpy(newItem->name, itemName);
    newItem->quantity = itemQuantity;
    newItem->next = shoppingList;
    shoppingList = newItem;
}

void removeItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                shoppingList = current->next;
            }
            struct ShoppingItem* temp = current;
            current = current->next;
            free(temp);
        } else {
            previous = current;
            current = current->next;
        }
    }
}

void displayList() {
    struct ShoppingItem* current = shoppingList;
    printf("�����嵥:\n");
    while (current != NULL) {
        printf("%s - ������%d\n", current->name, current->quantity);
        current = current->next;
    }
}

void updateQuantity(char itemName[], int newItemQuantity) {
    struct ShoppingItem* current = shoppingList;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            current->quantity = newItemQuantity;
            break;
        }
        current = current->next;
    }
}

void clearList() {
    while (shoppingList != NULL) {
        struct ShoppingItem* temp = shoppingList;
        shoppingList = shoppingList->next;
        free(temp);
    }
}

int totalQuantity() {
    struct ShoppingItem* current = shoppingList;
    int total = 0;
    while (current != NULL) {
        total += current->quantity;
        current = current->next;
    }
    return total;
}

void findItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    printf("������Ʒ \"%s\" ��\n", itemName);
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            printf("%s - ������%d\n", current->name, current->quantity);
            return;
        }
        current = current->next;
    }
    printf("δ�ҵ���Ʒ \"%s\"��\n", itemName);
}

void sortList() {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* nextItem = NULL;
    char tempName[50];
    int tempQuantity;
    while (current != NULL) {
        nextItem = current->next;
        while (nextItem != NULL) {
            if (strcmp(current->name, nextItem->name) > 0) {
                // ������Ʒ��Ϣ
                strcpy(tempName, current->name);
                tempQuantity = current->quantity;
                strcpy(current->name, nextItem->name);
                current->quantity = nextItem->quantity;
                strcpy(nextItem->name, tempName);
                nextItem->quantity = tempQuantity;
            }
            nextItem = nextItem->next;
        }
        current = current->next;
    }
}

void mergeLists(struct ShoppingItem** list1, struct ShoppingItem** list2) {
    struct ShoppingItem* current = *list1;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = *list2;
    *list2 = NULL;
}

void deleteItem(char itemName[], int deleteAll) {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            if (prev == NULL) {
                // ���Ҫɾ�����ǵ�һ���ڵ�
                struct ShoppingItem* temp = shoppingList;
                shoppingList = shoppingList->next;
                free(temp);
                current = shoppingList;
                if (!deleteAll) break;
            } else {
                // ���Ҫɾ���Ĳ��ǵ�һ���ڵ�
                prev->next = current->next;
                struct ShoppingItem* temp = current;
                current = current->next;
                free(temp);
                if (!deleteAll) break;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

