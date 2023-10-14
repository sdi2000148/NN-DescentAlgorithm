typedef struct PQ* PriorityQueue ;

void Initialize(PriorityQueue *, int) ;
int Empty(PriorityQueue) ;
int Full(PriorityQueue) ;
void Insert(PriorityQueue,int, double) ;
int Update(PriorityQueue, int, double) ; 
void Print_PQ(PriorityQueue) ;
void Free(PriorityQueue) ;
