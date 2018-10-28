#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define OK      1
#define ERROR   0

typedef char ElemType;
typedef int Status;

//树节点
typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//栈
typedef struct{
    BiTree *base;
    BiTree *top;
    int stacksize;
}sqStack;

//队列结构
typedef struct QNode{
    BiTree data;
    struct QNode * next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front;         //队头指针
    QueuePtr rear;          //队尾指针
}LinkQueue;

void visitTree(ElemType c, int level);              //也是显示树的节点的值
Status CreateBiTree(BiTree *T);                     //递归创建二叉树
Status PreOrderTraverse(BiTree T, int level);       //递归先序遍历二叉树
void print(ElemType e);                             //显示树节点的值
Status FirstInOrderTraverse(BiTree T);              //非递中序归遍历二叉树
Status SecondInOrderTraverse(BiTree T);             //非递中序归遍历二叉树
Status PostOrderTraverse(BiTree T);                 //递归后序遍历二叉树
Status InOrderTraverse(BiTree T);                   //递归中序遍历二叉树
int TreeDeep(BiTree T);                             //非递归求二叉树的深度
int RETreeDeep(BiTree T);                           //递归求二叉树的深度
int LeafCount(BiTree T);                            //二叉树的叶子节点个数

Status InitStack(sqStack *S);                       //初始化栈
Status Push(sqStack *S, BiTree e);                  //压栈
Status Pop(sqStack *S, BiTree *e);                  //弹栈
Status DestroyStack(sqStack *S);                    //销毁栈
Status StackEmpty(sqStack S);                       //判断栈是否为空
Status GetTop(sqStack *S, BiTree *e);               //获取栈顶元素
int StackLength(sqStack s);                         //获取栈长度

Status InitQueue(LinkQueue *Q);                     //初始化队列
Status EnQueue(LinkQueue *Q, BiTree e);             //进队列
Status DeQueue(LinkQueue *Q, BiTree *e);            //出队列
Status QueueEmpty(LinkQueue *Q);                    //判断队列是否为空


Status InitQueue(LinkQueue *Q){

    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q->front)
        return ERROR;
    Q->front->next = NULL;
    //printf("队列初始化成功！\n");
    return OK;
}
//进队
Status EnQueue(LinkQueue *Q, BiTree e){
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if(!p)
        return ERROR;
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}
//删除队头
Status DeQueue(LinkQueue *Q, BiTree *e){

    QueuePtr p;

    if(Q->front == Q->rear)
        return ERROR;
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if(Q->rear == p)
        Q->rear = Q->front;
    free(p);
    //printf("删除队头成功！\n");
    return OK;
}

 Status QueueEmpty(LinkQueue *Q){
    if(Q->front == Q->rear){
        //printf("队列为空\n");
        return ERROR;
    }
    //printf("队列不为空\n");
    return OK;
}

Status InitStack(sqStack *S){
    S->base = (BiTree * )malloc(STACK_INIT_SIZE * sizeof(BiTree));
    if(!S->base){
        exit(0);
    }
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;

}


Status Push(sqStack *S, BiTree e)
{
    if(S->top - S->base >= S->stacksize)           //栈满， 追加空间
    {
        S->base = (BiTree *)realloc(S->base, (S->stacksize + STACKINCREMENT)* sizeof(BiTree));
        if(!S->base){
            exit(0);                 //分配失败
        }
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }

    *(S->top) = e;
    S->top++;
    return OK;
}

Status Pop(sqStack *S, BiTree *e){
    if(S->top == S->base){
        return ERROR;                  //判空
    }
    *e = * --(S->top);
    return OK;
}

Status StackEmpty(sqStack S){
    if(S.top - S.base == 0){
        //printf("StackEmpty()当前栈为空！\n");
        return ERROR;
    }
    return OK;
}

Status GetTop(sqStack *S, BiTree *e){
    if(S->top == S->base){
        return ERROR;
    }
    *e = *(S->top-1);
    return OK;

}

int StackLength(sqStack s){
    return (s.top - s.base);
}

Status DestroyStack(sqStack *S){
    free(S);
    return OK;
}

//先序创建树
Status CreateBiTree(BiTree *T){
    ElemType c;

    scanf("%c", &c);
    if(' ' == c ){
        *T = NULL;
    }
    else{
        if(!((*T) = (BiTNode *)malloc(sizeof(BiTNode)))) return ERROR;
        (*T)->data = c;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);

    }
    return OK;
}

void visitTree(ElemType c, int level){
    printf("结点%c在第%d层\n", c, level);
}

void print(ElemType e){
    printf("%c  ", e);
}
//递归先序遍历二叉树
Status PreOrderTraverse(BiTree T, int level){
    if(T){
        visitTree(T->data, level);
        PreOrderTraverse(T->lchild, level+1);
        PreOrderTraverse(T->rchild, level+1);
    }
    return OK;
}
//递归中序遍历二叉树
Status InOrderTraverse(BiTree T){

    if(T == NULL){
        return ERROR;
    }
    else{
        InOrderTraverse(T->lchild);
        print(T->data);
        InOrderTraverse(T->rchild);
    }
    return OK;
}
//非递归中序遍历二叉树
Status FirstInOrderTraverse(BiTree T){

    BiTree p;
    sqStack S;
    InitStack(&S);
    Push(&S, T);
    while(StackEmpty(S) == 1){
        while(GetTop(&S, &p) && p) {
            Push(&S, p->lchild);
        }
        Pop(&S, &p);
        if(StackEmpty(S) == 1){
            Pop(&S, &p);
            print(p->data);
            Push(&S, p->rchild);
        }
    }
    return OK;
}
//非递归中序遍历二叉树
Status SecondInOrderTraverse(BiTree T){

    BiTree p;
    p = T;
    sqStack S;
    InitStack(&S);
    while(p || StackEmpty(S) == 1){
        if(p){
            Push(&S, p);
            p = p->lchild;
        }
        else{
            Pop(&S, &p);
            print(p->data);
            p = p->rchild;
        }
    }
    return OK;
}
//递归后序遍历二叉树
Status PostOrderTraverse(BiTree T){

    if(T == NULL){
        return 0;
    }
    else{
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        print(T->data);
    }
    return OK;
}

//层次遍历二叉树
Status LevelOrderTraverse(BiTree T){

    LinkQueue Q;
    InitQueue(&Q);
    BiTree p;
    p = T;
    EnQueue(&Q, p);
    while(QueueEmpty(&Q) == 1){
        DeQueue(&Q, &p);
        if(p->lchild != NULL){
            EnQueue(&Q,p->lchild);
        }
        if(p->rchild != NULL){
            EnQueue(&Q, p->rchild);
        }
        print(p->data);
    }
    return OK;
}
//非递归求二叉树的深度
int TreeDeep(BiTree T){
    int Deep = 0;

    sqStack S, Tag;
    InitStack(&S);
    InitStack(&Tag);
    BiTree q, p;
    p = T;
    while(p != NULL || StackEmpty(S) == 1){
        while(p != NULL){
            Push(&S, p);
            Push(&Tag, NULL);
            p = p->lchild;
        }
        GetTop(&Tag, &q);
        if(q != NULL){
            Deep = Deep>StackLength(S)?Deep:StackLength(S);
            Pop(&S, &p);
            Pop(&Tag, &p);
            p = NULL;
        }
        else{
            GetTop(&S,&p);
            p = p->rchild;
            Pop(&Tag, &q);
            Push(&Tag, T);
        }
    }

    return Deep;
}

//递归求二叉树的深度
int RETreeDeep(BiTree T){

    int Deep = 0 ;
    if(T){
        int lchilddeep=RETreeDeep(T->lchild);
        int rchilddeep=RETreeDeep(T->rchild);
        Deep=lchilddeep>=rchilddeep?lchilddeep+1:rchilddeep+1;
    }
    return Deep;
}

int LeafCount(BiTree T){

    int Count = 0;
    BiTree p;
    sqStack S;
    InitStack(&S);
    Push(&S,T);
    while(StackEmpty(S) == 1){

        while(GetTop(&S, &p) && p){
            Push(&S, p->lchild);
        }
        Pop(&S, &p);
        if(StackEmpty(S) == 1){
            Pop(&S, &p);
            if(p->lchild == NULL && p->rchild == NULL){
                Count++;
            }
            Push(&S, p->rchild);
        }
    }
    return Count;
}


int main()
{

    int level = 1;
    BiTree T = NULL;
    CreateBiTree(&T);
    printf("递归的先序遍历结果为：\n");
    PreOrderTraverse(T, level);
    printf("\n");
    printf("递归中序遍历二叉树结果：\n");
    InOrderTraverse(T);
    printf("\n");
    printf("第一种非递归的中序遍历结果为：\n");
    FirstInOrderTraverse(T);
    printf("\n");
    printf("第二种非递归的中序遍历结果为：\n");
    SecondInOrderTraverse(T);
    printf("\n");
    printf("递归后续遍历二叉树的结果：\n");
    PostOrderTraverse(T);
    printf("\n");
    printf("非递归层次遍历二叉数的结果：\n");
    LevelOrderTraverse(T);
    printf("\n");
    printf("非递归求二叉树的深度是：%d\n", TreeDeep(T));
    printf("递归求二叉树的深度是：%d\n", RETreeDeep(T));
    printf("二叉树的叶子节点个数是：%d\n", LeafCount(T));
    system("pause");
    return 0;
}
