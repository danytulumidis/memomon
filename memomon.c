// TODO: [] Collecting

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const uint8_t MEMOMON_COUNT = 30;
const uint8_t MAX_NAME_LENGTH = 20;
const uint8_t MAX_POWER = 100;

typedef enum { FIRE, WATER, AIR, EARTH, DARK, LIGHT } Element;

typedef struct {
    Element element;
    char name[20];
    // Memomons with higher power consumes more memory
    int power;
} Memomon;

void init_memomons(const char *filename, Memomon *memomon_list);
Memomon create_memomons(const Element element, const char *name,
                        const int power);
int fight(Memomon *memomon_list, int memomon_one, int memomon_two);

int main(int argc, char *argv[]) {
    Memomon *memomon_list = malloc(MEMOMON_COUNT * sizeof(Memomon));
    if (memomon_list == NULL) {
        exit(EXIT_FAILURE);
    }

    init_memomons("data.txt", memomon_list);

    srand(time(NULL));
    int rand_one = rand() % (MEMOMON_COUNT - 1);
    int rand_two = rand() % (MEMOMON_COUNT - 1);
    fight(memomon_list, rand_one, rand_two);

    return 0;
}

void init_memomons(const char *filename, Memomon *memomon_list) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Could not open the file");
        exit(EXIT_FAILURE);
    }

    char name[MAX_NAME_LENGTH];
    int element, power;

    while (fscanf(file, "%d %s %d", &element, name, &power) == 3) {
        *memomon_list = create_memomons(element, name, power);
        memomon_list++;
    }

    fclose(file);
}

Memomon create_memomons(const Element element, const char *name,
                        const int power) {
    Memomon *memomon = malloc(sizeof(Memomon) + power * sizeof(int));
    if (memomon == NULL) {
        exit(EXIT_FAILURE);
    }
    memomon->element = element;
    memomon->power = power;
    memcpy(memomon->name, name, MAX_NAME_LENGTH);
    return *memomon;
}

int fight(Memomon *memomon_list, int memomone_one, int memomone_two) {
    if (memomone_one >= MEMOMON_COUNT || memomone_two >= MEMOMON_COUNT) {
        printf("Memomons dont live outside the Array Area!\n");
        return (EXIT_FAILURE);
    }

    // TODO: Take elements into consideration
    Memomon fighter_one = memomon_list[memomone_one];
    Memomon fighter_two = memomon_list[memomone_two];
    printf("%s(%d) and %s(%d) are ready to fight for the memory!\n",
           fighter_one.name, fighter_one.power, fighter_two.name,
           fighter_two.power);

    if (fighter_one.power > fighter_two.power) {
        printf("%s wins! %s is defeated and flees!\n", fighter_one.name,
               fighter_two.name);

    } else if (fighter_one.power < fighter_two.power) {
        printf("%s wins! %s is defeated and flees!\n", fighter_two.name,
               fighter_one.name);
    } else {
        printf("Its a tie!");
    }

    return 0;
}
