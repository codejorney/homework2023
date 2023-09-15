#include<stdio.h>
struct ShoppingItem {
 char name[50]; // 商品名称
 int quantity; // 商品数量
 struct ShoppingItem* next; // 指向下一个节点的指针
};
	struct ShoppingItem* shoppingList = NULL;
int main()
{
	while(1){
	printf("按 1 添加商品和数量\n");
	printf("按 2 移除商品\n");
	printf("按 3 查看购物清单\n");
	printf("按 4 修改清单中商品数量\n");
	printf("按 5 清空购物清单\n");
	printf("按 6 计算清单中商品的总数量\n");
	printf("按 7 查找清单中的商品\n");
	printf("按 8 清单中物品排序\n");
	printf("按 9 合并购物清单\n");
	printf("-----------------------------------\n");
	int select;
	int check;
	scanf("%d",&select);
		char itemName[20];
		int itemQuantity;
	if(select==1)
	{
		printf("输入商品名\n");
		scanf("%s",itemName);
		printf("输入数量\n");
		scanf("%d",&itemQuantity);
		addItem(itemName, itemQuantity);
	}
	if(select==2)
	{
		printf("输入要删除的商品名\n");
		scanf("%s",itemName);
		findItem( itemName);
		printf("请问要删除多少项\n");
		int deleteAll;
		scanf("%d",&deleteAll);
		deleteItem(itemName, deleteAll);
		printf("删除成功\n"); 
	}
	if(select==3)
	{
		printf("\n\n");
		displayList();
		printf("\n\n"); 
	}
	if(select==4)
	{
		printf("输入要修改的商品名\n"); 
		scanf("%s",itemName);
		printf("输入修改后的数量\n"); 
		scanf("%d",&itemQuantity) ;
		updateQuantity(itemName,itemQuantity);
	}
	if(select==5)
	{
		printf("确认要清空购物清单吗\n“是”请按 1 \n“否”请按 0 \n");
		scanf("%d",&check);
		if(check==1)
		clearList();
		check=0;		
	}
	if(select==6)
	totalQuantity();
	if(select==7)
	{
		printf("输入商品名\n");
		scanf("%s",itemName);
		findItem( itemName);
	}
	if(select==8)
	{
		sortList();
		printf("整理成功\n"); 
	}
	if(select==9)
	{
		printf("功能未开放\n"); 
		//printf("输入要合并的两个清单，中间用回车分隔")
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
    printf("购物清单:\n");
    while (current != NULL) {
        printf("%s - 数量：%d\n", current->name, current->quantity);
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
    printf("查找商品 \"%s\" ：\n", itemName);
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            printf("%s - 数量：%d\n", current->name, current->quantity);
            return;
        }
        current = current->next;
    }
    printf("未找到商品 \"%s\"。\n", itemName);
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
                // 交换商品信息
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
                // 如果要删除的是第一个节点
                struct ShoppingItem* temp = shoppingList;
                shoppingList = shoppingList->next;
                free(temp);
                current = shoppingList;
                if (!deleteAll) break;
            } else {
                // 如果要删除的不是第一个节点
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

