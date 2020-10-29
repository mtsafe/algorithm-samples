#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        fprintf(stderr, "error: unable to allocate memory.");
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
        fprintf(stderr, "error: name, address and phone must be less than %i characters.", MAX_FIELD);
        fflush(stderr);
        return NULL;
    }
    dude = makePerson(name, address, phone);
    if (dude == NULL) return NULL;

    if (P->first == NULL)  {
        P->first = dude;
        P->last = dude;
    } else if (strcmp(P->first->name, dude->name) >= 0) {
        dude->next = P->first;
        P->first = dude;
    } else {                     
        a = P->first;
        b = a->next;
        while(b->next != NULL && strcmp(b->name, dude->name) < 0) {
            a = b;
            b = b->next;
        }
        dude->previous = a;
        dude->next = b;
        a->next = dude;
        if (b == NULL)
            P->last = dude;
        else
            b->previous = dude;
    }
    printf("Added: %-20s : %-25s : %-20s\n",
        dude->name, dude->address, dude->phone);
    fflush(stdout);
    return dude;
}

void sortRolodex(people *P) {
    return ;
}

person *makePerson(char *name, char *address, char *phone) {
    person *dude;

    dude = (person *)malloc(sizeof(person));
    if (dude == NULL) {
        fprintf(stderr, "error: unable to allocate memory.");
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
        fprintf(stderr, "error: %s is not in the rolodex.", name);
        fflush(stderr);
        return;
    }

    while(0) {
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
            fprintf(stderr, "error: %s is not in the rolodex.", name);
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