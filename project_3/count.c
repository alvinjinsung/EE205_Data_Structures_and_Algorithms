#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE 4096
#define MAX_WORD 1024
#define BUCKET_SIZE 100003

enum {OUTSIDE, INSIDE};

// strucutre to record the word information(word, number of times it appeared) key: word, value: count
struct word_info {
    char* word;
    int count;
    struct word_info* next;
};

// structure for bucket for hash table
struct bucket {
    struct word_info* head;
    int num_node;
};

// creating new wordinfo given new word
// input: char* word, int count, output: struct word_info* new_word
struct word_info* create_wordinfo(char* word, int count) {
    struct word_info* new_word;

    new_word = (struct word_info*) malloc(sizeof(struct word_info));

    new_word->word = malloc(sizeof(char)*(strlen(word)+1));
    strcpy(new_word->word, word);
    new_word->count = count;
    new_word->next = NULL;

    return new_word;
}

// function needed for polynomial rolling hash function
long long int p_pow(int base, int exp, int m) {
    long long int result=0;

    if(exp==0)
        return 1;
    else
    {
        result = (p_pow(base, exp-1, m) * base) % m;
        return result;
    }
}

// function to compute hash value using polynomial rolling hash function
int hash_function (char* word) {
    int p=53;
    long long int hash_index=0;

    for(int i=0; i<(int)strlen(word); i++) {
        hash_index = hash_index + word[i] * p_pow(p, i, BUCKET_SIZE);
        hash_index = hash_index % BUCKET_SIZE;
    }

    return hash_index;
}

// search if the same key(same word) already exists in hash table
// input: struct bucket* hash_T, char* word, output: struct word_info* word_info if it exists, NULL if it doesn't exist
struct word_info* word_search(struct bucket* hash_T, char* word) {
    int hash_index = hash_function(word);

    struct word_info* word_info;

    word_info = hash_T[hash_index].head;


    while (word_info != NULL) {
        if (strcmp(word_info->word, word) == 0) {
            return word_info;
        }

        word_info = word_info->next;
    }

    return NULL;
}

// insert wordinfo into hash table
// input: struct bucket* hash_T, char* word, int count
void insert_wordinfo(struct bucket* hash_T, char* word, int count) {

    int hash_index = hash_function(word);

    struct word_info* new_word;
    new_word = create_wordinfo(word, count);

    if (hash_T[hash_index].num_node == 0) {
        hash_T[hash_index].num_node++;
        hash_T[hash_index].head = new_word;
    }

    else {
        new_word->next = hash_T[hash_index].head;
        hash_T[hash_index].head = new_word;
        hash_T[hash_index].num_node++;
    }

}

// function to create array of wordinfo after all the word was computed in hash table
// input: struct bucket* hash_T, output: struct word_info* word_array
struct word_info* create_wordarray(struct bucket* hash_T, struct word_info* word_array){
    struct word_info* iterator;
    int j = 0;

    for (int i = 0; i<BUCKET_SIZE; i++){
        iterator = hash_T[i].head;

        while (iterator != NULL) {
            word_array[j].word = malloc(sizeof(char)*(strlen(iterator->word)+1));
            strcpy(word_array[j].word, iterator->word);
            word_array[j].count = iterator->count;
            word_array[j].next = NULL;
            iterator = iterator->next;
            j++;
        }

    }

    return word_array;
}

// compare function for qsort()
int compare(const void *a, const void *b) {
    const struct word_info* pa = (const struct word_info*) a;
    const struct word_info* pb = (const struct word_info*) b;

    if (pa->count >= pb->count) {
        return -1;
    }

    else if (pa->count < pb->count) {
        return 1;
    }

    else {
        return 0;
    }
}


int main(int argc, char *argv[])
{

	char buf[MAX_LINE], *temp;
	int  i, in_word = OUTSIDE;
	char str[MAX_WORD];

    // hash table
    struct bucket* hash_T = (struct bucket*) malloc(BUCKET_SIZE * sizeof(struct bucket));

    // hash table initialization
    for (int m=0; m<BUCKET_SIZE; m++) {
        hash_T[m].head = NULL;
        hash_T[m].num_node = 0;
    }

    // total distinct word count variable
    int total_word = 0;


	/* read a line from stdin, break it into words,
	   check if it exists in hash table
	   if it exists, increase the count of that word
	   if it does not exist, insert into hash table */
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		for (temp = buf; *temp; temp++) {
			if (isalpha(*temp)) {
				if (in_word == OUTSIDE) {
					in_word = INSIDE;
					i = 0;
				}
				str[i++] = *temp;
			}

            else {
				if (in_word == INSIDE) {
					str[i] = 0;
                    struct word_info* word_check = word_search(hash_T, str);

                    if (word_check != NULL) {
                        word_check->count++;
                    }

                    else {
                        insert_wordinfo(hash_T, str, 1);
                        total_word++;
                    }

				}
				in_word = OUTSIDE;
			}
		}
	}
	if (in_word == INSIDE) {
		str[i] = 0;
        struct word_info* word_check = word_search(hash_T, str);

        if (word_check != NULL) {
            word_check->count++;
        }

        else {
            insert_wordinfo(hash_T, str, 1);
            total_word++;
        }
	}

    // array to store all wordinfo
    struct word_info* word_array = (struct word_info*) malloc(total_word * sizeof(struct word_info));

    // move all the wordinfo in hash table to wordarray
    word_array = create_wordarray(hash_T, word_array);

    // sort based on each word count
    qsort(word_array, total_word, sizeof(struct word_info), compare);

    // variable indicating how many word to print based on the stdin
    int num_print;

    if (argc == 1) {
        num_print = total_word;
    }

    else {
        num_print = atoi(argv[1]);
    }

    // print
    for (int j=0; j<num_print; j++) {
        if (word_array[j].count != 0) {
            printf("%d %s\n", word_array[j].count, word_array[j].word);
        }
    }


	return 0;
}
