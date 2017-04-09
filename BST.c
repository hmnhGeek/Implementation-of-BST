#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *left, *right
}bst;

bst *root = NULL;
bst *parent = NULL;
int found = 0;
int counter = 1;
int last;
int main_count, count, father_count = 0;
int SUM = 0, cnt = 0;
int leftSub, rightSub = 0;

bst *newNode(int item){
    bst *temp = (bst *)malloc(sizeof(bst));
    temp -> data = item;
    temp -> left = temp -> right = NULL;
    return temp;
}





void check(bst *node, int lower, int upper){
    if(node != NULL){
        check(node -> left, lower, upper);
        if(node -> data >= lower && node -> data <= upper){
            count += 1;
        }
        main_count += 1;
        check(node -> right, lower, upper);
    }
}

void run(bst *node, int lower, int upper){
    count = main_count = 0;
    if(node != NULL){
        run(node -> left, lower, upper);
        check(node, lower, upper);
        if(count == main_count){
            father_count += 1;
        }
        run(node -> right, lower, upper);
    }
}










void k_small(bst *node, int k){
    if(node != NULL){
        k_small(node -> left, k);

        if(counter == k){
            last = node -> data;
        }
        counter += 1;
        k_small(node -> right, k);
    }
}

void k_large(bst *node, int k){
    if(node != NULL){
        k_large(node -> right, k);

        if(counter == k){
            last = node -> data;
        }
        counter += 1;
        k_large(node -> left, k);
    }
}

void greater_sum(bst *node){
    if(node != NULL){
        greater_sum(node -> right);
        int data = node -> data;
        node -> data = SUM;
        SUM = SUM + data;
        greater_sum(node -> left);
    }
}

void gvals(bst *node){
    if(node != NULL){
        gvals(node -> right);
        int data = node -> data;
        node -> data = SUM + node -> data;
        SUM = SUM + data;
        gvals(node -> left);
    }
}

void del_out_of_range(bst *node, int lower, int upper){
    if(node != NULL){
        del_out_of_range(node -> left, lower, upper);
        if(node -> data < lower || node -> data > upper){
            delete(node -> data);
        }
        del_out_of_range(node -> right, lower, upper);
    }
}

void final_check(bst *node){
    if(!(node -> right != NULL && node -> left != NULL)){
        cnt += 1;
    }
}

void has_only_one_child(bst *node){
    if(node != NULL){
        has_only_one_child(node -> left);
        final_check(node);
        main_count += 1;
        has_only_one_child(node -> right);
    }
}

void insert(bst *node, int item){
    if(root == NULL){
        root = newNode(item);
    }
    else{
        searchNode(root, item);
    }
}

void searchNode(bst *node, int item){
    if(item > node -> data){
        if(node -> right != NULL)
            searchNode(node -> right, item);
        else
            node -> right = newNode(item);
        return;
    }
    else{
        if(node -> left != NULL){
            searchNode(node -> left, item);
        }
        else{
            node -> left = newNode(item);
        }
        return;
    }
}

void inorder(bst *node){
    if(node != NULL){
        inorder(node -> left);
        printf("%d\n", node -> data);
        inorder(node -> right);
    }
}

void delete(int item){
    if(root == NULL){
        printf("The tree is empty.\n");
    }
    else{
        parent = root;
        search(root, item);
    }
}

void search(bst *node, int item){
    if(item > node -> data){
        parent = node;
        search(node -> right, item);
    }
    else if(item < node -> data){
        parent = node;
        search(node -> left, item);
    }
    else{
        del(node);
    }
}

void del(bst *node){
    //leafnode//
    if(node -> left == NULL && node -> right == NULL){
        if(node == parent){
            root = NULL;
            parent = root;
        }
        else if(parent -> left == node){
            parent -> left = NULL;
        }
        else if(parent -> right == node){
            parent -> right = NULL;
        }
        free(node);
    }

    // only left child //
    else if(node -> right == NULL){
        if(node == parent){
            root = node -> left;
            parent = root;
        }
        else if(parent -> left == node){
            parent -> left = node -> left;
        }
        else if(parent -> right == node){
            parent -> right = node -> left;
        }
        free(node);
    }

    // only right child //
    else if(node -> left == NULL){
        if(node == parent){
            root = node -> right;
            parent = root;
        }
        else if(parent -> left == node){
            parent -> left = node -> right;
        }
        else if(parent -> right == node){
            parent -> right = node -> right;
        }
        free(node);
    }
    else if(node -> left != NULL && node -> right != NULL){
        int small = smallest(node -> right);
        search(root, small);
        node -> data = small;
    }
}

int smallest(bst *node){
    while(node -> left != NULL){
        node = node -> left;
    }
    return node -> data;
}

void find(bst *node, int item){
    if(node != NULL){
        find(node -> left, item);
        if(item == node -> data){
            found = 1;
            printf("True\n");
            return;
        }
        find(node -> right, item);
    }
}

void tree(int arr[], int size){
    int i = 0;
    for(i; i< size; i+=1){
        insert(root, arr[i]);
    }
}

void left_size(bst *node){
    if(node != NULL){
        left_size(node -> left);
        leftSub += 1;
        left_size(node -> right);
    }
}

void right_size(bst *node){
    if(node != NULL){
        right_size(node -> left);
        rightSub += 1;
        right_size(node -> right);
    }
}

void print_in_range(bst *node, int lower, int upper){
    if(node != NULL){
        print_in_range(node -> left, lower, upper);
        if(node -> data >= lower && node -> data <= upper){
            printf("%d\n", node -> data);
        }
        print_in_range(node -> right, lower, upper);
    }
}

void main(){
    int ch = 1;
    while(ch){
        printf("Enter 1 to insert.\n");
        printf("Enter 2 to display.\n");
        printf("Enter 3 to delete.\n");
        printf("Enter 4 to find.\n");
        printf("Enter 5 to find kth small element.\n");
        printf("Enter 6 to count range_nodes.\n");
        printf("Enter 7 to find kth large element.\n");
        printf("Enter 8 to find the greater sum tree.\n");
        printf("Enter 9 to find the add data to nodes.\n");
        printf("Enter 10 to delete all the elements out of range.\n");
        printf("Enter 11 to see if bst is linear.\n");
        printf("Enter 12 to convert a tree to BST.\n");
        printf("Enter 13 to find maximum size subtree.\n");
        printf("Enter 14 to print keys in range.\n");

        int choice;
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1){
            int item;
            printf("Enter item: ");
            scanf("%d", &item);
            insert(root, item);
        }
        else if(choice == 2){
            inorder(root);
        }
        else if(choice == 3){
            int item;
            printf("Enter item: ");
            scanf("%d", &item);
            delete(item);
        }
        else if(choice == 4){
            int item;
            found = 0;
            printf("Enter item: ");
            scanf("%d", &item);
            find(root, item);
            if(found == 0){
                printf("False\n");
            }
        }
        else if(choice == 5){
            int k;
            counter = 1;
            last = 0;
            printf("Enter k: ");
            scanf("%d", &k);
            k_small(root, k);
            printf("%d\n", last);
        }
        else if(choice == 6){
            int lower, upper;
            printf("Enter lower: ");
            scanf("%d", &lower);
            printf("Enter upper: ");
            scanf("%d", &upper);
            father_count = count = main_count = 0;
            run(root, lower, upper);
            printf("%d\n", father_count);
        }
        else if(choice == 7){
            int k;
            counter = 1;
            last = 0;
            printf("Enter k: ");
            scanf("%d", &k);
            k_large(root, k);
            printf("%d\n", last);
        }
        else if(choice == 8){
            SUM = 0;
            greater_sum(root);
            inorder(root);
        }
        else if(choice == 9){
            SUM = 0;
            gvals(root);
            inorder(root);
        }
        else if(choice == 10){
            int lower, upper;
            printf("Enter lower: ");
            scanf("%d", &lower);
            printf("Enter upper: ");
            scanf("%d", &upper);
            del_out_of_range(root, lower, upper);
            inorder(root);
        }
        else if(choice == 11){
            has_only_one_child(root);
            if(cnt == main_count){
                printf("True\n");
            }
            else{
                printf("False\n");
            }
        }
        else if(choice == 12){
            int n;
            printf("Enter size of array: ");
            scanf("%d", &n);

            int arr[n];
            int i = 0;
            for(i; i<n; i+=1){
                printf("Enter element %d: ", i+1);
                scanf("%d", &arr[i]);
            }

            tree(arr, n);
            inorder(root);
        }
        else if(choice == 13){
            leftSub = rightSub = 0;
            left_size(root -> left);
            right_size(root -> right);
            
            if(leftSub - rightSub > 0){
                printf("Left Subtree of size = %d\n", leftSub);
            }
            else{
                printf("Right Subtree of size = %d\n", rightSub);
            }
        }
        else if(choice == 14){
            int lower, upper;
            printf("Enter ll: ");
            scanf("%d", &lower);
            printf("Enter ul: ");
            scanf("%d", &upper);
            
            print_in_range(root, lower, upper);
        }
        else{
            ch = 0;
        }
    }
}
