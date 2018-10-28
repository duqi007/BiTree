#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define OK      1
#define ERROR   0

typedef char ElemType;
typedef int Status;

//���ڵ�
typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//ջ
typedef struct{
    BiTree *base;
    BiTree *top;
    int stacksize;
}sqStack;

//���нṹ
typedef struct QNode{
    BiTree data;
    struct QNode * next;
}QNode, *QueuePtr;

typedef struct{
    QueuePtr front;         //��ͷָ��
    QueuePtr rear;          //��βָ��
}LinkQueue;

void visitTree(ElemType c, int level);              //Ҳ����ʾ���Ľڵ��ֵ
Status CreateBiTree(BiTree *T);                     //�ݹ鴴��������
Status PreOrderTraverse(BiTree T, int level);       //�ݹ��������������
void print(ElemType e);                             //��ʾ���ڵ��ֵ
Status FirstInOrderTraverse(BiTree T);              //�ǵ���������������
Status SecondInOrderTraverse(BiTree T);             //�ǵ���������������
Status PostOrderTraverse(BiTree T);                 //�ݹ�������������
Status InOrderTraverse(BiTree T);                   //�ݹ��������������
int TreeDeep(BiTree T);                             //�ǵݹ�������������
int RETreeDeep(BiTree T);                           //�ݹ�������������
int LeafCount(BiTree T);                            //��������Ҷ�ӽڵ����

Status InitStack(sqStack *S);                       //��ʼ��ջ
Status Push(sqStack *S, BiTree e);                  //ѹջ
Status Pop(sqStack *S, BiTree *e);                  //��ջ
Status DestroyStack(sqStack *S);                    //����ջ
Status StackEmpty(sqStack S);                       //�ж�ջ�Ƿ�Ϊ��
Status GetTop(sqStack *S, BiTree *e);               //��ȡջ��Ԫ��
int StackLength(sqStack s);                         //��ȡջ����

Status InitQueue(LinkQueue *Q);                     //��ʼ������
Status EnQueue(LinkQueue *Q, BiTree e);             //������
Status DeQueue(LinkQueue *Q, BiTree *e);            //������
Status QueueEmpty(LinkQueue *Q);                    //�ж϶����Ƿ�Ϊ��


Status InitQueue(LinkQueue *Q){

    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q->front)
        return ERROR;
    Q->front->next = NULL;
    //printf("���г�ʼ���ɹ���\n");
    return OK;
}
//����
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
//ɾ����ͷ
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
    //printf("ɾ����ͷ�ɹ���\n");
    return OK;
}

 Status QueueEmpty(LinkQueue *Q){
    if(Q->front == Q->rear){
        //printf("����Ϊ��\n");
        return ERROR;
    }
    //printf("���в�Ϊ��\n");
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
    if(S->top - S->base >= S->stacksize)           //ջ���� ׷�ӿռ�
    {
        S->base = (BiTree *)realloc(S->base, (S->stacksize + STACKINCREMENT)* sizeof(BiTree));
        if(!S->base){
            exit(0);                 //����ʧ��
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
        return ERROR;                  //�п�
    }
    *e = * --(S->top);
    return OK;
}

Status StackEmpty(sqStack S){
    if(S.top - S.base == 0){
        //printf("StackEmpty()��ǰջΪ�գ�\n");
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

//���򴴽���
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
    printf("���%c�ڵ�%d��\n", c, level);
}

void print(ElemType e){
    printf("%c  ", e);
}
//�ݹ��������������
Status PreOrderTraverse(BiTree T, int level){
    if(T){
        visitTree(T->data, level);
        PreOrderTraverse(T->lchild, level+1);
        PreOrderTraverse(T->rchild, level+1);
    }
    return OK;
}
//�ݹ��������������
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
//�ǵݹ��������������
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
//�ǵݹ��������������
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
//�ݹ�������������
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

//��α���������
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
//�ǵݹ�������������
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

//�ݹ�������������
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
    printf("�ݹ������������Ϊ��\n");
    PreOrderTraverse(T, level);
    printf("\n");
    printf("�ݹ�������������������\n");
    InOrderTraverse(T);
    printf("\n");
    printf("��һ�ַǵݹ������������Ϊ��\n");
    FirstInOrderTraverse(T);
    printf("\n");
    printf("�ڶ��ַǵݹ������������Ϊ��\n");
    SecondInOrderTraverse(T);
    printf("\n");
    printf("�ݹ���������������Ľ����\n");
    PostOrderTraverse(T);
    printf("\n");
    printf("�ǵݹ��α����������Ľ����\n");
    LevelOrderTraverse(T);
    printf("\n");
    printf("�ǵݹ��������������ǣ�%d\n", TreeDeep(T));
    printf("�ݹ��������������ǣ�%d\n", RETreeDeep(T));
    printf("��������Ҷ�ӽڵ�����ǣ�%d\n", LeafCount(T));
    system("pause");
    return 0;
}
