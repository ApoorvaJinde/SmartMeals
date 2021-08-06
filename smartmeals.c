#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define MAX 10
#include<conio.h>
#define INFINITY 9999

int pos[MAX];
int available[MAX];
int we=0;

struct item
{
    int sr;
    char name[40];
    float price;
};

struct Area
{
    int n;
    char nam[20];
};

struct vertex
{
int v;
int wt;
};

struct node
{
struct vertex data;
struct node *next;
};

struct Heap
{
struct vertex a[MAX];
int size;
};

struct Graph
{
struct node *head;
struct node *last;
};

int dijikstra(int G[MAX][MAX], int n, int startnode,int ch)
{
int cost[MAX][MAX], distance[MAX], pred[MAX],f;
int visited[MAX], count, mindistance, nextnode, i,j;
for(i=0;i < n;i++)
for(j=0;j < n;j++)
if(G[i][j]==0)
cost[i][j]=INFINITY;
else
cost[i][j]=G[i][j];

for(i=0;i< n;i++)
{
distance[i]=cost[startnode][i];
pred[i]=startnode;
visited[i]=0;
}
distance[startnode]=0;
visited[startnode]=1;
count=1;
while(count < n-1){
mindistance=INFINITY;
for(i=0;i < n;i++)
if(distance[i] < mindistance&&!visited[i])
{
mindistance=distance[i];
nextnode=i;
}
visited[nextnode]=1;
for(i=0;i < n;i++)
if(!visited[i])
if(mindistance+cost[nextnode][i] < distance[i])
{
distance[i]=mindistance+cost[nextnode][i];
pred[i]=nextnode;
}
count++;
}
          f=0;
   for(i=0;i < n;i++)
{
   if(i!=startnode && i==ch)
{
printf("WE HAVE TO TRAVEL %d KILOMETERS TO REACH YOU\n", distance[i]);
printf("YOUR PARCEL WILL BE DELIVERED BY THIS ROUTE\n%d",i);
//printf("\nPath = %d", i);
j=i;
do
{
j=pred[j];
printf(" <-%d", j);
}
while(j!=startnode);
f=1;
}
printf("\n");
if(f==1)
            return distance[i];
}
}



void displayGraph(int graph[10][10])
{
    for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
               {
                   printf("%d\t",graph[i][j]);
               }
            printf("\n");
        }
}


void initHeap(struct Heap *h)
{
h->size=0;
}


void initGraph(struct Graph G[])
{
int i;
for(i=0;i<MAX;i++)
{
G[i].head= NULL;
G[i].last= NULL;
}
}


void swap(struct vertex *a, struct vertex *b)
{
struct vertex temp;
temp = *a;
*a = *b;
*b = temp;
}


void swapint(int *a, int *b)
{
int temp;
temp = *a;
*a = *b;
*b = temp;
}


void insertKey(struct Heap *h, struct vertex key)
{
h->a[h->size]=key;
h->size++;

    int i = h->size - 1;

while(i!=0 && h->a[i].wt < h->a[(i-1)/2].wt)
{
swap(&h->a[i],&h->a[(i-1)/2]);
swapint(&pos[i],&pos[(i-1)/2]);
i = (i-1)/2;
}
}


int isEmpty(struct Heap *h)
{
return (h->size==0);
}


void Heapify(struct Heap *h,int i)
{
int left = 2*i+1;
int right = 2*i+2;
int min = i;

if(  left<h->size &&   h->a[min].wt > h->a[left].wt)
        left = min;

if(  right<h->size && h->a[min].wt > h->a[right].wt)
        right = min;

if(min!=i)
{
swap(&h->a[i],&h->a[min]);
swapint(&pos[h->a[i].v],&pos[h->a[min].v]); //change vertex-pos of parent
Heapify(h, min);
}
}


struct vertex extractMin(struct Heap *h,int k[])
{
struct vertex m = h->a[0];

h->a[0] = h->a[h->size-1];

available[m.v]=0;

k[we]=m.v;
we++;

int x = (h->a[0]).v;
pos[x]=0;
h->size--;

Heapify(h,0);

return m;
}


void decreseKey(struct Heap *h, int i,int k)
{
if(i>=h->size)
return;

if(k>h->a[i].wt)
return;

h->a[i].wt = k;

while(i!=0 && h->a[i].wt < h->a[(i-1)/2].wt)
{
swap(&h->a[i],&h->a[(i-1)/2]);
swapint(&pos[h->a[i].v],&pos[h->a[(i-1)/2].v]); //change vertex-pos of parent
i = (i-1)/2;
}
}


void addEdge(struct Graph G[],int src,int dest,int wt)
{
struct node *p=(struct node *)malloc(sizeof(struct node));
p->data.v = dest;
p->data.wt = wt;
p->next = NULL;

if(G[src].head==NULL)
G[src].head = p;
else
G[src].last->next = p;

G[src].last = p;
}

void deleteGraph(struct Graph G[],int vertex)
{
int i;
for(i=0;i<vertex;i++)
{
struct node *p = G[i].head;
while(p!=NULL)
{
G[i].head=p->next;
free(p);
p = G[i].head;
}
}
}

void print(int distance[],int vertex,int src)
{
int i;
for(i=0;i<vertex;i++)
{
printf("Distance from %d to %d is %d \n",src,i,distance[i]);
}
}

/*int dijkstra(struct Graph G[], int src, int destination,int k[10])
{
int i;
int n=10, d, wt,v;
int dest, destWt, index;
int distance[MAX];
struct vertex u;
struct Heap h;
initHeap(&h);
for(i=0;i<n;i++)
{
u.v = i;
u.wt = INT_MAX;
insertKey(&h,u);
available[i]=1;
pos[i]=i;
}

decreseKey(&h,pos[src],0);
    available[0]=0;
while(!isEmpty(&h))
{
u = extractMin(&h,k);
d = u.wt; //Distance from source to vertex
v = u.v; //The min distance vertex is taken from the heap

distance[v]=d; //Store the distance in distance array
         //if(v==destination)
            //return distance[destination];

struct node * p = G[v].head;

 //Iterate through all the edges of the vertex extracted from Heap(Extract Min Weight)

while(p!=NULL)
{
dest = p->data.v; //Get the dest vertex
destWt = p->data.wt; //Get the weight to the dest
index = pos[dest]; //Get where the dest is available on Heap

//check if available and current distance is greater than distance
//computed (relax the edge)

if(available[dest] && d+destWt < h.a[index].wt)
{
//decreseKey
decreseKey(&h,index, d+destWt);
}
p=p->next;
}
}

deleteGraph(G,n); //Delete Graph at end.

}*/

void displaylink(struct Graph G[],int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        struct node *p=G[i].head;
        while(p)
        {
            printf("%d\t%d\t%d\n",i,p->data.v,p->data.wt);
            p=p->next;
        }
    }
}



int main()
{
    int i=0,j,choice,a,e,sum=0,b[20],k[10],z;

    FILE *fp;
    FILE *kl;
    struct Graph G[10];
    initGraph(G);
    struct item s[20];
    struct Area d[20];
    struct item n[20];


    //MATRIX REPRESENTATION OF GRAPH
    int graph[10][10]={{0,0,2,0,0,0,6,7,0},
                       {0,0,8,0,0,0,0,11,4},
                       {2,8,0,7,0,0,0,0,0},
                       {0,0,7,0,9,14,0,0,0},
                       {0,0,0,9,0,10,0,0,0},
                       {0,0,4,14,10,0,2,0,0},
                       {6,0,0,0,0,2,0,1,0},
                       {7,11,0,0,0,0,1,0,8},
                       {0,4,0,0,0,0,0,8,0}};

    //printing graph
     /*for(i=0;i<9;i++)
{

for(j=0;j<9;j++)
{
printf("%d\t",graph[i][j]);
}
printf("\n");
}
     printf("\n\n");*/


    //LINKED LIST REPRESENTATIOM OF GRAPH
     for(i=0;i<9;i++)
{

for(j=0;j<9;j++)
{
if(graph[i][j]>0)
addEdge(G,i,j,graph[i][j]);
}
}

     //displaylink(G,9);


    printf("\n\n\t\t\t\t\t\t\tWELCOME TO ZOMATO\n\n");
   while(1){
    printf("SERVICE AVAILABLE TO AREAS:\n\n");

    fp=fopen("s.txt","r");

        i=0;
        while(!feof(fp))
        {
             if(feof(fp))
                break;
            fscanf(fp,"%d",&d[i].n);
            fscanf(fp,"%s",&d[i].nam);
            printf("%d.%s\n",d[i].n,d[i].nam);
            i++;

        }
    fclose(fp);

    printf("ENTER YOUR BRANCH : ");
    scanf("%d",&choice) ;

    printf("ENTER OPTION\n1 FOR VEG\n2 FOR NON VEG : ") ;
    scanf("%d",&a);



    //VEG MENU
if(a==1)
{

        fp=fopen("vegText.txt","r");

        i=0;
        while(!feof(fp))
        {
            if(feof(fp))
                break;
             //printf("%d\t",i);
            fscanf(fp,"%d",&s[i].sr);
            fscanf(fp,"%s",&s[i].name);
            fscanf(fp,"%f",&s[i].price);
            printf("%d\t%s\t%f\n",s[i].sr,s[i].name,s[i].price);
            i++;

        }
        fclose(fp);printf("\n");
        /*for(j=0;j<i;j++)
       {

     printf("%d\t%s\t%f\n",s[j].sr,s[j].name,s[j].price);
       }
        // printf("\n%d\n",i);*/

      printf("Enter the number of items to be ordered :");
      scanf("%d",&e);


      //MAKING BILL
      printf("ENTER THE SERIAL NUMBER OF THE ITEMS WHICH YOU SELECTED:");
      for(j=0;j<e;j++)
      {
       scanf("%d",&b[j]);
       sum=sum+s[b[j]-1].price;
      }

      //DISPLAYING BILL
      printf("YOU HAVE SELECTED %d ITEMS\n\n",e);
      printf("ITEMS ARE:\n");
      for(i=0;i<e;i++)
          {
               int z=b[i]-1;
               printf("%d\t%s\t%f\n",s[z].sr,s[z].name,s[z].price);
          }
}


//NON-VEG MENU
if(a==2)
{
       fp=fopen("non_vegText.txt","r");


        i=0;
        while(!feof(fp))
        {
            if(feof(fp))
                break;

            fscanf(fp,"%d",&n[i].sr);
            fscanf(fp,"%s",&n[i].name);
            fscanf(fp,"%f",&n[i].price);
            printf("%d\t%s\t%f\n",n[i].sr,n[i].name,n[i].price);
            i++;

        }
        fclose(fp);

      printf("Enter the number of items to be ordered: ");
      scanf("%d",&e);

      //MAKING BILL
      printf("ENTER THE SERIAL NUMBER OF THE ITEMS WHICH YOU SELECTED:");
      for(j=0;j<e;j++)
      {
       scanf("%d",&b[j]);
       int z=b[j]-1;
       sum=sum+n[z].price;
      }

      //DISPLAYING BILL
      printf("YOU HAVE SELECTED %d ITEMS\n\n",e);
      printf("ITEMS ARE:\n");
      for(i=0;i<e;i++)
            {
                int z=b[i]-1;
                printf("%d\t%s\t%f\n",n[z].sr,n[z].name,n[z].price);
            }

}

   if(a==1 || a==2)
    {
    printf("\nAND TOTAL AMOUNT TO BE PAID IS %d/-\n",sum);


     int x=dijikstra(graph,9,0,choice);

    float m=2.0/x;

      printf("YOUR PARCEL WILL BE DELIVERED IN %0.2f MINUTES\n\n\n\n",m+20);


      }

      else
        return 0;


   }

}
