#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// global ticket count
int gtickets = 0;

struct node_t {
    int            tickets;
    struct node_t *next;
};

struct node_t *head = NULL;

void insert(int tickets) {
    struct node_t *tmp = malloc(sizeof(struct node_t));
    assert(tmp != NULL);
    tmp->tickets = tickets;
    tmp->next    = head;
    head         = tmp;
    gtickets    += tickets;
}

void print_list() {
    struct node_t *curr = head;
    printf("List: ");
    while (curr) {
	printf("[%d] ", curr->tickets);
	curr = curr->next;
    }
    printf("\n");
}

int
main(int argc, char *argv[])
{
    if (argc != 3) {
	fprintf(stderr, "usage: lottery <seed> <loops>\n");
	exit(1);
    }
    int seed  = atoi(argv[1]);
    int loops = atoi(argv[2]);
    srandom(seed);

    // populate list with some number of jobs, each
    // with some number of tickets
    insert(50);
    insert(100);
    insert(25);

    print_list();
    
    int i;
    for (i = 0; i < loops; i++) {
	int counter            = 0;
	int winner             = random() % gtickets; // get winner
	struct node_t *current = head;

	// loop until the sum of ticket values is > the winner
	while (current) {
	    counter = counter + current->tickets;
	    if (counter > winner)
		break; // found the winner
	    current = current->next;
	}
	// current is the winner: schedule it...
	print_list();
	printf("winner: %d %d\n\n", winner, current->tickets);

    }
    return 0;
}

