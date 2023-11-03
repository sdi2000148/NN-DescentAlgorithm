#include <stdio.h>
#include <stdlib.h>
#include "services.h"
#include "list.h"

int seq_search(int value , int size , int *array)
{
    int i ;
    for (i=0 ; i<size ; i++){
        if (value==array[i]){
            return 1 ;
        }
    }
    return 0 ;
}


List *reverse(Heap *heap, int numberOfObjects) {
    List *R = malloc(numberOfObjects * sizeof(List));

    for (int i=0 ; i < numberOfObjects ; i++){
        list_initialize(&R[i]);
    }

    for(int i=0; i < numberOfObjects; i++) {
        for(int j=i+1; j < numberOfObjects; j++) {   // start from i+1
            if (heap_search(heap[j], i) == 1){
                if (heap_search(heap[i], j) == 0){
                    list_insert(R[i], j);
                }
            }
            if (heap_search(heap[i], j) == 1){
                if (heap_search(heap[j], i) == 0){
                    list_insert(R[j], i);
                }
            }
        }
    }
    return R;
}

//ενημερωση της λύσης (γραφου) και ενημερωση των reverse
int nn_update(Heap *B, int v, int u, double l, Avl *R)
{
	int r; 
	if (heap_update(B[v], u, l, &r) == 0){
		return 0;
	}
	else{
        //περιπτωση που αρχικοποιειτε ακομα ο γραφος 
		if (r == -1){
            //αρα για να αποφυγουμε τα διπλοτυπα πρεπει να βγαλουμε αυτον που μπηκε
            //στους Κ κοντινους του v (δηλαδη ο u) απο τους reverse του v αν υπαρχει (Περιπτωση (v <--> u))

            //και να προσθεσουμε στους reverse του u τον v αμα δεν ειναι ηδη στους γειτονες
            //του u ως ενας απο τους Κ κοντινοτερους (Περιπτωση (v --> u))
			if (avl_remove(R[v], u) == 0){
        		avl_insert(R[u], v);
            }
		}
        //περιπτωση που ενημερωνετε ο γραφος 
		else{

            //αρα για να αποφυγουμε τα διπλοτυπα πρεπει να βγαλουμε αυτον που μπηκε
            //στους Κ κοντινους του v (δηλαδη ο u) απο τους reverse του v αν υπαρχει (Περιπτωση (v <--> u))

            //και να προσθεσουμε στους reverse του u τον v αμα δεν ειναι ηδη στους γειτονες
            //του u ως ενας απο τους Κ κοντινοτερους (Περιπτωση (v --> u))
			if (avl_remove(R[v], u) == 0){
        		avl_insert(R[u], v);
            }
            //επισης πρεπει να βγαλουμε αν υπαρχει τον v απο τους reverse του r (που βγηκε απο τους Κ κοντινους του v) (Περιπτωση (r καμια ακμη v))

            //και να προσθεσουμε στους reverse του v τον r αμα ειναι στους γειτονες
            //του r ως ενας απο τους Κ κοντινοτερους (Περιπτωση (r --> v))
            if (avl_remove(R[r], v) == 0){
        		avl_insert(R[v], r);
			}
		}
		return 1;
	}
}

void heap_free_all(Heap *heaps, int n)
{
	for (int i=0 ; i<n ; i++){
		heap_free(heaps[i]) ;
	}
	free(heaps);
}


void actual_solution(Heap *heaps, char *path, int N, int k) {
    FILE *fp = fopen(path, "w");

    // #object : #n1 #n2 #n3 

    for (int i=0 ; i<N ; i++){
        fprintf(fp, "%d:", i);
        for (int j=0 ; j<k-1; j++){
            fprintf(fp, "%d,", heap_getIndex(heaps[i], j));
        }
        fprintf(fp, "%d\n", heap_getIndex(heaps[i], k-1));
    }

    fclose(fp);
}