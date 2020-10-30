#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define MAX_FIELD 25

struct record {
    struct record* next;
    struct record* previous;
    char name[MAX_FIELD];
    char address[MAX_FIELD];
    char phone[MAX_FIELD];
};
typedef struct record person;

typedef struct {
    person* first;
    person* last;
} people;

people *makeRolodex();
person *addPerson(people*, char *, char *, char *);
void sortRolodex(people *);
void swapFirstLast(people *, person *, person *);
void swapFirst(people *, person *, person *);
void swapLast(people *, person *, person *);
void swapRolodexPosition(people *, person *, person *);
void validateRolodex(people *);
person *makePerson(char *, char *, char *);
void destroyPerson(person *);
void printRolodex(people *);
int isEmpty(people *);
void removePerson(people *, char *);
int size(people *P);
int main(int, char *[]);

people *makeRolodex() {
    people *P = (people *)malloc(sizeof(people));
    if (P == NULL) {
        fprintf(stderr, "error: unable to allocate memory.\n");
        fflush(stderr);
        return NULL;
    }
    P->first = NULL;
    P->last = NULL;
    return P;
}

person *addPerson(people *P, char *name, char *address, char *phone) {
    person *dude;
    person *a, *b;
    int len1, len2, len3;

    len1 = strlen(name);
    len2 = strlen(address);
    len3 = strlen(phone);
    if (len1>=MAX_FIELD || len2>=MAX_FIELD || len3>=MAX_FIELD) {
        fprintf(stderr, "error: name, address and phone must be less than %i characters.\n", MAX_FIELD);
        fflush(stderr);
        return NULL;
    }
    dude = makePerson(name, address, phone);
    if (dude == NULL) return NULL;

    if (P->first == NULL)  {
        P->first = dude;
        P->last = dude;
    } else {
        P->first->previous = dude;
        dude->next = P->first;
        P->first = dude;
    }
    printf("Added: %-20s : %-25s : %-20s\n",
        dude->name, dude->address, dude->phone);
    fflush(stdout);
    sortRolodex(P);
    return dude;
}

void sortRolodex(people *P) {
    person *a, *b;
    int sorted = TRUE;

    printf("BREAK 1\n"); fflush(stdout); printRolodex(P);
    a = P->first;
    if (a == NULL) return ;
    b = a->next;
    if (b == NULL) return ;

    printf("BREAK 2\n"); fflush(stdout); printRolodex(P);
    do {
    printf("BREAK 3\n"); fflush(stdout);
        validateRolodex(P);
    printf("BREAK 4\n"); fflush(stdout);
        if (strcmp(a->name, b->name) < 0) {
            a = b;
            b = a->next;
    printf("BREAK 5\n"); fflush(stdout);
        } else {
printf("b == NULL is %i; b->next == NULL is %i; !sorted is %i;\n", b == NULL, b == NULL ? -1 : b->next == NULL, !sorted);
printf("%d people in rolodex.1\n\n", size(P));  fflush(stdout);
     printRolodex(P);
printf("%d people in rolodex.2\n\n", size(P));  fflush(stdout);
            swapRolodexPosition(P, a, b);
printf("%d people in rolodex.3\n\n", size(P));  fflush(stdout);
        validateRolodex(P);
printf("%d people in rolodex.4\n\n", size(P));  fflush(stdout);
     printRolodex(P);
printf("%d people in rolodex.5\n\n", size(P));  fflush(stdout);
printf("b == NULL is %i; b->next == NULL is %i; !sorted is %i;\n", b == NULL, b == NULL ? -1 : b->next == NULL, !sorted);
printf("%d people in rolodex.6\n\n", size(P));  fflush(stdout);
            b = a->next;
            sorted = FALSE;
printf("b == NULL is %i; b->next == NULL is %i; !sorted is %i;\n", b == NULL, b == NULL ? -1 : b->next == NULL, !sorted);
    printf("BREAK 6\n"); fflush(stdout);
        }

printf("b == NULL is %i; b->next == NULL is %i; !sorted is %i;\n", b == NULL, b == NULL ? -1 : b->next == NULL, !sorted);
        if ((b == NULL || b->next == NULL) && !sorted) {
            a = P->first;
            b = a->next;
            sorted = TRUE;
    printf("BREAK 7\n"); fflush(stdout);
        }
    printf("BREAK 8\n"); fflush(stdout);
printf("b == NULL is %i; b->next == NULL is %i; !sorted is %i;\n", b == NULL, b == NULL ? -1 : b->next == NULL, !sorted);
printf("The OR is %i; The AND is %i;\n", (b == NULL || b->next == NULL), ((b == NULL || b->next == NULL) && !sorted));
    } while ((b != NULL && b->next != NULL) || !sorted);
    printf("Sorted rolodex: %i.\n", sorted);
    fflush(stdout);
        validateRolodex(P);
     printRolodex(P);
    return ;
}

void swapFirstLast(people *P, person *a, person *b) {
    P->first = b;                   // set the first link
    P->last = a;                    // set the last link
    b->previous->next = a;          // set 1 next link
    a->previous = b->previous;      // set 3 previous links
    b->previous = NULL;
    a->next->previous = b;
    b->next = a->next;              // set 2 next links
    a->next = NULL;
    return ;
}

void swapFirst(people *P, person *a, person *b) {
    person *tmp;
    P->first = b;                   // set the first link
    b->previous->next = a;          // set 1 next link
    a->previous = b->previous;      // set 3 previous links
    b->previous = NULL;
    a->next->previous = b;
    tmp = a->next;                  // set 3 next links
    a->next = b->next;
    b->next = tmp;
    a->next->previous = a;
    return ;
}

void swapLast(people *P, person *a, person *b) {
    person *tmp;
    P->last = a;                    // set the last link
    a->next->previous = b;          // set 1 previous link
    b->next = a->next;              // set 3 next links
    a->next = NULL;
    b->next->previous = a;
    tmp = a->previous;              // set 3 previous links
    a->previous = b->previous;
    b->previous = tmp;
    b->previous->next = b;
    return ;
}

void swapRolodexPosition(people *P, person *a, person *b) {
    person tmp;

    printf("swapRolodexPosition STARTED.\n"); fflush(stdout);

    if (P==NULL || a==NULL || b==NULL) {
        fprintf(stderr, "error: unable to swap positions in rolodex.\n");
        fflush(stderr);
        return ;
    }
    
    if (P->first == a)
        if (P->last == b) swapFirstLast(P, a, b);
        else swapFirst(P, a, b);
    else if (P->first == b)
        if (P->last == a) swapFirstLast(P, b, a);
        else swapFirst(P, b, a);
    else if (P->last == a)
        swapLast(P, b, a);
    else if (P->last == b)
        swapLast(P, a, b);
    else {
        tmp.next = a->next;            // tmp replaces a
        tmp.previous = a->previous;
        b->previous->next = a;          // a replaces b
        b->next->previous = a;
        a->previous = b->previous;
        a->next = b->next;
        tmp.previous->next = b;          // b replaces tmp
        tmp.next->previous = b;
        b->previous = tmp.previous;
        b->next = tmp.next;
    }
    printf("swapRolodexPosition XXXXXXXXX.\n"); fflush(stdout);
    validateRolodex(P);
    printf("swapRolodexPosition COMPLETED.\n"); fflush(stdout);
}

void validateRolodex(people *P) {
    printf("validateRolodex STARTED.\n"); fflush(stdout);
    person *a, *b;
    if ((P->first == NULL && (P->last != NULL || P->first->previous != NULL)) ||
        (P->last == NULL && (P->first != NULL || P->last->next != NULL))) {
        fprintf(stderr, "error: fake empty.\n");
        fflush(stderr);
        return ;
    }
    a = P->first;
    b = a->next;
    while (b!=NULL) {
        printf("Validation Loop ...\n"); fflush(stdout);
        if (a->previous==a || a->next==a) {
            fprintf(stderr, "error: %s is self-referential.\n", a->name);
            fflush(stderr);
            return ;            
        }
        if (b->previous==b || b->next==b) {
            fprintf(stderr, "error: %s is self-referential.\n", b->name);
            fflush(stderr);
            return ;            
        }
        if (a->next!=b || b->previous!=a) {
            fprintf(stderr, "error: unmatched links %s and %s.\n", a->name, b->name);
            fflush(stderr);
            return ;
        }
        a = b;
        b = a->next;
    }
    printf("Validated rolodex.\n"); fflush(stdout);
    printf("validateRolodex COMPLETED.\n"); fflush(stdout);
    return ;
}

person *makePerson(char *name, char *address, char *phone) {
    person *dude;

    dude = (person *)malloc(sizeof(person));
    if (dude == NULL) {
        fprintf(stderr, "error: unable to allocate memory.\n");
        fflush(stderr);
        return NULL;
    }

    dude->next = NULL;
    dude->previous = NULL;
    strcpy(dude->name, name);
    strcpy(dude->address, address);
    strcpy(dude->phone, phone);
    printf("Made: %-20s : %-25s : %-20s\n",
        dude->name, dude->address, dude->phone);
    fflush(stdout);
    return dude;
}

void destroyPerson(person *dude) {
    free(dude);
}

void printRolodex(people *P) {
    person* a = P->first;

    validateRolodex(P);
    while(a != NULL) {
        printf("%-20s : %-25s : %-20s\n", a->name, a->address, a->phone);
        a = a->next;
        fflush(stdout);
    }
}

int isEmpty(people *P){
    return (P->first == NULL);
}

void removePerson(people *P, char *name) {
    person *a;

    a = P->first;
    if (a == NULL) {
        fprintf(stderr, "error: %s is not in the rolodex.\n", name);
        fflush(stderr);
        return;
    }

    while(TRUE) {
        if (strcmp(a->name, name) == 0) {
            if (P->first == a) P->first = P->first->next;
            if (P->last == a) P->last = P->last->previous;
            if (a->next != NULL) a->next->previous = a->previous;
            if (a->previous != NULL) a->previous->next = a->next;
            destroyPerson(a);
            printf("%s is removed from the rolodex.", name);
            fflush(stdout);
            return;
        }        
        if (a->next == NULL) {
            fprintf(stderr, "error: %s is not in the rolodex.\n", name);
            fflush(stderr);
            return;
        }
        a = a->next;
    }
}

int size(people *P) {
    person* a = P->first;
    int cnt = 0;
    
    while(a != NULL) {
        a = a->next;
        cnt++;
    }
    return cnt;
}

int main(int argc, char *argv[]) {
    people *rolodex = makeRolodex();
    person *dude;

    if(isEmpty(rolodex)) printf("PASSED: Empty rolodex at start.\n");
    printf("%d people in rolodex.\n\n", size(rolodex)); 
    fflush(stdout);

    dude=addPerson(rolodex, "Chris Kringle", "1000 North Pole", "1-800-4SANTAC");
    if (dude==NULL) return-1;
    dude=addPerson(rolodex, "Herman Munster", "1313 Mockingbird Lane", "206-555-5555");
    if (dude==NULL) return -1;
    dude=addPerson(rolodex, "George Washington", "1600 Pennsylvania Ave NW", "(202) 456-1111");
    if (dude==NULL) return -1;
    dude=addPerson(rolodex, "Buffalo Bill", "Dodge City, KS", "(620) 555-5555");
    if (dude==NULL) return -1;
    dude=addPerson(rolodex, "Superman", "Metropolis, Illinois", "618-555-5555"); 
    if (dude==NULL) return -1;
    printRolodex(rolodex);
    printf("%d people in rolodex.\n\n", size(rolodex)); 
    fflush(stdout);

    removePerson(rolodex, "Superman");
    removePerson(rolodex, "Buffalo Bill");
    removePerson(rolodex, "Herman Munster");
    printRolodex(rolodex);
    printf("%d people in rolodex.\n\n", size(rolodex)); 
    fflush(stdout);

    return 0;
}