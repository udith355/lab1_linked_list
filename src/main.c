#include <stdio.h>
#include <stdlib.h>
#include "../include/common.h"
#include <time.h>
#include <pthread.h>

FILE *file;

pthread_mutex_t mutex;
pthread_rwlock_t rwlock;
clock_t start_time;
clock_t end_time;

int n = 1000;
int m = 10000;
int total_cases = 3;

int num_of_tests = 3;

int *operation_list;

struct node *linked_list;

double m_member_values[] = {-1, 0.99, 0.90, 0.50};
double m_insert_values[] = {-1, 0.005, 0.05, 0.25};
double m_delete_values[] = {-1, 0.005, 0.05, 0.25};
int numbers_of_threads[] = {1, 2, 4, 8};
int size_threads = 4;
int num_of_methods = 3;

double results[3][4][3]; //results[total_cases][size_of_threads][num_of_tests]



void printl(int *arr) {
    int length = 10000;
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n================\n");
}

long getRandomValue() {
    return rand() % 65536;
}

void shuffle_array(int arr[], int size) {
    srand(time(NULL));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void create_operation_list(double m_member, double m_insert, double m_delete) {
    free(operation_list);
    operation_list = (int *) malloc(m * sizeof(int));
    for (int r = 0; r < (int) (m * m_member); r++) {
        operation_list[r] = 0;
    }
    for (int s = 0; s < (int) (m * m_insert); s++) {
        operation_list[s + (int) (m * m_member)] = 1;
    }
    for (int t = 0; t < (int) (m * m_delete); t++) {
        operation_list[t + (int) (m * m_member) + (int) (m * m_insert)] = 2;
    }
}

void *thread_function(void *arguments) {
    int *arguments_casted = (int *) arguments;
    int id = arguments_casted[0];
    int thread_count = arguments_casted[1];
    int method = arguments_casted[2];

    for (int r = (int) (m / thread_count) * id; r < (int) (m / thread_count) * (id + 1); r++) {
        long randomNumber = getRandomValue();
        switch (operation_list[r]) {
            case 0: // run Member function
                if (method == 1) {
                    pthread_mutex_lock(&mutex);
                    Member(randomNumber, linked_list);
                    pthread_mutex_unlock(&mutex);
                } else if (method == 2) {
                    pthread_rwlock_wrlock(&rwlock);
                    Member(randomNumber, linked_list);
                    pthread_rwlock_unlock(&rwlock);
                } else {
                    Member(randomNumber, linked_list);
                }
                break;
            case 1: // run Insert function
                if (method == 1) {
                    pthread_mutex_lock(&mutex);
                    Insert(randomNumber, &linked_list);
                    pthread_mutex_unlock(&mutex);
                } else if (method == 2) {
                    pthread_rwlock_wrlock(&rwlock);
                    Insert(randomNumber, &linked_list);
                    pthread_rwlock_unlock(&rwlock);
                } else {
                    Insert(randomNumber, &linked_list);
                }
                break;
            case 2: // run Delete function
                if (method == 1) {
                    pthread_mutex_lock(&mutex);
                    Delete(randomNumber, &linked_list);
                    pthread_mutex_unlock(&mutex);
                } else if (method == 2) {
                    pthread_rwlock_wrlock(&rwlock);
                    Delete(randomNumber, &linked_list);
                    pthread_rwlock_unlock(&rwlock);
                } else {
                    Delete(randomNumber, &linked_list);
                }
                break;
            default:
                for (int i = 0; i < 3; ++i) {
                    printf("===>> %d\n", arguments_casted[i]);
                }
        }
    }
    return 0;
}

double exec_time(clock_t end_time, clock_t start_time) {
    return (double) (end_time - start_time) / CLOCKS_PER_SEC;
}

double calculateAverage(int *array, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return (double) sum / size;
}

void run_tests(int test_num) {

    // Iterate through 3 cases
    for (int i = 1; i <= total_cases; i++) {
        int case_number = i;
        printf("case : %d\n", case_number);

        double m_member = m_member_values[case_number];
        double m_insert = m_insert_values[case_number];
        double m_delete = m_delete_values[case_number];

        create_operation_list(m_member, m_insert, m_delete);

        shuffle_array(operation_list, m);


        // Iterate through number of threads
        for (int thread_count_id = 0; thread_count_id < size_threads; thread_count_id++) {
            int thread_count = numbers_of_threads[thread_count_id];
            printf("--number of threads : %d\n", thread_count);
            pthread_t threads[thread_count];

            // Run serial for single thread
            if (thread_count == 1) {
                linked_list = initialize_linked_list(linked_list, n);
                clock_t start_time_ser = clock();
                int arguments_ser[] = {0, 1, 0};
                thread_function(arguments_ser);
                clock_t end_time_ser = clock();
                printf("----method : 0, exec time %.10fs\n", exec_time(end_time_ser, start_time_ser));
                results[case_number][0][0] = exec_time(end_time_ser, start_time_ser);
            }

            // method indexes - 0: sequential , 1: mutex, 2: rw_lock
            for (int method = 1; method < num_of_methods; method++) {
                linked_list = initialize_linked_list(linked_list, n);
                start_time = clock();

                for (int k = 0; k < thread_count; k++) {
                    int arguments[] = {k, thread_count, method};
                    pthread_create(&threads[k], NULL, (void *(*)(void *)) thread_function, (void *) arguments);

                }

                for (int l = 0; l < thread_count; l++) {
                    pthread_join(threads[l], NULL);
                }

                end_time = clock();

                printf("----method : %d, exec time %.10fs\n", method, exec_time(end_time, start_time));
                results[case_number][thread_count_id][method] = exec_time(end_time, start_time);
            }

        }
        printf("case %d done!\n\n", case_number);
    }
}

void generate_results() {
    file = fopen("../test_results/results.csv", "a");

    for (int i = 0; i < total_cases; i++) {
        for (int j = 0; j < size_threads; j++) {
            for (int k = 0; k < num_of_tests; k++) {
                fprintf(file, "%f, ", results[i][j][k]);
            }
            fprintf(file, "\n");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}


int main() {

    for (int test = 0; test < num_of_tests; test++) {
        run_tests(test);
    }

    generate_results();

    return 0;
}
