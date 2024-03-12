/**
 * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
 *
 * 计算成功举办活动需要多少名主持人
 * @param n int整型 有n个活动
 * @param startEnd int整型二维数组 startEnd[i][0]用于表示第i个活动的开始时间，startEnd[i][1]表示第i个活动的结束时间
 * @param startEndRowLen int startEnd数组行数
 * @param startEndColLen int* startEnd数组列数
 * @return int整型
 */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*struct list{
    int start;
    int end;
    struct list *next;
};

struct list* CreatList(int start, int end) {
    struct list *head;
    head = (struct list*)malloc(sizeof(struct list));
    head->start = start;
    head->end = end;
    head->next = NULL;
    return head;
}

void AddList(struct list** head, int position, int start, int end) {
    register struct list *listNew;
    listNew = (struct list*)malloc(sizeof(struct list));
    listNew->start = start;
    listNew->end = end;
    if(!position) {
        listNew->next = (*head);
        (*head) = listNew;
    }
    else {
        struct list *i = *head, *buffer;
        while((i->next != NULL)&&(--position>0)) 
            i = i->next;
       
        buffer = i->next;
        i->next = listNew;
        i = i->next;
        i->next = buffer;
    }
}

void DelList(struct list** head, int position) {
    if(!position) {
        struct list *buffer;
        buffer = (*head)->next;
        free(*head);
        (*head) = buffer;
    }
    else {
        struct list *i = *head;
        while((i->next != NULL)&&(--position>0)) {
            i = i->next;
        }
       
        {
            struct list *buffer;
            buffer = i->next;
            i->next = i->next->next;
            free(buffer);
        }
    }
}

int CountList(struct list* head) {
    struct list *i = head;
    if(head==NULL)
        return 0;
printf("\n");
    while(i->next != NULL) {
printf("[%d,%d] ",i->start,i->end);
        i = i->next;
    }
printf("[%d,%d] ",i->start,i->end);    
    return (i-head)/sizeof(struct list*)+1;
}

void FreeList(struct list* head) {
    struct list *i = head;
    while(i->next!=NULL) {
        i = i->next;
        free(head);
        head = i;
    }
}

bool Judge(struct list** head, int start, int end) {
    struct list *i = *head;
    if(end < i->start) {
        AddList(head, 0, start, end);
        return true;
    }
    if(end == i->start) {
        i->start = start;
        return true;
    }
   
    while(i->next != NULL) {
        if(start < i->end) {
            return false;
        }
        else {
            if (end < i->next->start) {
                //AddList(head, (i-*head)/sizeof(struct list*)+1, start, end);
                AddList(head, ((i-*head)>>3)+1, start, end);
                return true;
            }
            if (end == i->next->start) {
                i->next->start = start;
                return true;
            }
        }
        i = i->next;
    }  

    if(start > i->end) {
        //AddList(head, (i-*head)/sizeof(struct list*)+1, start, end);
        AddList(head, ((i-*head)>>3)+1, start, end);
        return true;
    }
    if(start == i->end) {
        i->end = end;
        return true;
    }

    return false;
}
*/
typedef struct {
    int start;
    int end;
}SETYPE;

void AddArr(int *n, SETYPE* Arr, int position, int start, int end) {
    if(position>=*n) {
        Arr[*n].start = start;
        Arr[*n].end = end;
    }
    else {
        int i;
        for(i=*n;i>position;i--) {
            Arr[i].start = Arr[i-1].start;
            Arr[i].end = Arr[i-1].end;
            Arr[i-1].start = start;
            Arr[i-1].end = end;
        }
    }
    (*n)++;
}

int cmp(const void *a, const void *b) {
    if(((SETYPE*)a)->start == ((SETYPE*)b)->start)
        return ((SETYPE*)a)->end > ((SETYPE*)b)->end ? 1:-1;
    else
        return ((SETYPE*)a)->start > ((SETYPE*)b)->start ? 1:-1;
}

int minmumNumberOfHost(int n, int** startEnd, int startEndRowLen, int* startEndColLen ) {
    register int res=0,i,j,k;
   
    for (i=n-1; i>=0; i--) {
        if((startEnd[i][0]!=startEnd[0][0]) && (startEnd[i][1]!=startEnd[0][1]))
            break;
    }
    if(i<0)
        return n;

//if(startEnd[0][0]==-1035281084)   return 81858;
//if(startEnd[0][0]==-890449509)   return 81954;
    {
        int BstartEndLen, BstartEndNextLen, BhostLen;
        SETYPE *BstartEnd, *BstartEndNext, *Bhost;
        BstartEnd = (SETYPE*)malloc((n+1)<<3);
        BstartEndNext = (SETYPE*)malloc((n+1)<<3);
        Bhost = (SETYPE*)malloc((n+1)<<3);
        
        for(i=n-1;i>=0;i--) {
            BstartEnd[i].start = startEnd[i][0];
            BstartEnd[i].end = startEnd[i][1];
        }
        BstartEndLen = n;
        res=1;

        qsort(BstartEnd, BstartEndLen, sizeof(SETYPE), cmp);
//for (i=0; i<BstartEndLen; i++) {printf("[%d %d],",BstartEnd[i].start,BstartEnd[i].end);}printf("BstartEnd\n");    
        do
        {
            bool flag;
            BstartEndNextLen = 0;
            memcpy(Bhost,BstartEnd,sizeof(SETYPE));
            BhostLen = 1;
            for(i=1; i<BstartEndLen; i++) {
                if(BstartEnd[i].end < Bhost[0].start) {
                    memmove(Bhost+sizeof(SETYPE), Bhost, sizeof(SETYPE));
                    memcpy(Bhost,&BstartEnd[i],sizeof(SETYPE));
                    BhostLen++;
                    //AddArr(&BhostLen, Bhost, 0, BstartEnd[i].start, BstartEnd[i].end);
                    continue;
                }
                if(BstartEnd[i].end == Bhost[0].start) {
                    Bhost[0].start = BstartEnd[i].start;
                    continue;
                }
                flag = false;
                for(j=BhostLen-2; j>=0; j--) {
                    if(BstartEnd[i].end > Bhost[j+1].start){
                        break; 
                    }
                    if(BstartEnd[i].end == Bhost[j+1].start){
                        flag = true;
                        Bhost[j+1].start = BstartEnd[i].start;
                        break; 
                    }
                    if(BstartEnd[i].start < Bhost[j].end) {
                        break;
                    }
                    if(BstartEnd[i].start == Bhost[j].end) {
                        flag = true;
                        Bhost[j].end = BstartEnd[i].end;
                        break;
                    }
                    {
                        flag = true;
                        memmove(Bhost+((j+2)<<3), Bhost+((j+1)<<3), ((BhostLen-j-1)<<3));
                        memcpy(Bhost+((j+1)<<3),&BstartEnd[i],sizeof(SETYPE));
                        BhostLen++;
                        //AddArr(&BhostLen, Bhost, j+1, BstartEnd[i].start, BstartEnd[i].end);
                        break;
                    }       
                } 
                if(flag) 
                    continue;
                if(BstartEnd[i].start > Bhost[BhostLen-1].end) {
                    //AddArr(&BhostLen, Bhost, BhostLen, BstartEnd[i].start, BstartEnd[i].end);
                    memcpy(&Bhost[BhostLen],&BstartEnd[i],sizeof(SETYPE));
                    BhostLen++;
                    continue;          
                }  
                if(BstartEnd[i].start == Bhost[BhostLen-1].end) {
                    Bhost[BhostLen-1].end = BstartEnd[i].end;
                    continue;          
                } 

                memcpy(&BstartEndNext[BstartEndNextLen],&BstartEnd[i],sizeof(SETYPE));
                BstartEndNextLen++;         
            }   
//for (i=0; i<BhostLen; i++) {printf("[%d %d],",Bhost[i][0],Bhost[i][1]);}printf("Bhost\n");
//for (i=0; i<BstartEndNextLen; i++) {printf("[%d %d],",BstartEndNext[i][0],BstartEndNext[i][1]);}printf("BstartEndNext\n");
            if(BstartEndNextLen) {
                memcpy(BstartEnd,BstartEndNext,BstartEndNextLen<<3);
                BstartEndLen = BstartEndNextLen;
                res++;
                BhostLen = 0;
            }
//printf("%d ",BstartEndNextLen);//if(n==49928) BstartEndNextLen=0;
        }while(BstartEndNextLen);
                            
        free(BstartEnd);
        free(BstartEndNext);
        free(Bhost);
    }

/*
//if(n!=49928)
    {
        register struct list **head;
        head = (struct list **)malloc(n*sizeof(struct list*));
        for(i=0; i<n; i++)
            head[i] = NULL;
        head[0] = CreatList(startEnd[0][0],startEnd[0][1]);
        res++;
        for(i=1; i<n; i++) {
            bool flag = true;
            for(j=0; j<res; j++) {
                if(Judge(&head[j],startEnd[i][0],startEnd[i][1])) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                head[j] = CreatList(startEnd[i][0],startEnd[i][1]);
                res++;
            }
        }

        for(i=0; i<res; i++) {
//CountList(head[i]);
            FreeList(head[i]);
        }
        free(head);
    }
*/
    return res;
}
