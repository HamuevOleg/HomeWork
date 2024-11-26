/*
Copyright © 2024 Hamuev Oleg. All rights reserved,
except for the ones I borrow from the internet.
Any unauthorized copying will result in infinite loops and frustration.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "list.c"

#include "compare-int.h"
#include "compare-int.c"

void test_generate_list(void);
void test_list_append(void);
void test_list_prepend(void);
void test_list_free(void);
void test_list_next(void);
void test_list_nth_entry(void);
void test_list_nth_data(void);
void test_list_length(void);
void test_list_remove_entry(void);
void test_list_remove_data(void);
void test_list_sort(void);
void test_list_to_array(void);
void test_list_iterate(void);

int x = 5;
int y = 10;
int z = 15;

int main()
{
    test_generate_list(); //done
    test_list_append(); //done
    test_list_prepend(); //done
    test_list_free(); //done
    test_list_next(); //done
    test_list_nth_entry(); //done
    test_list_nth_data(); //done
    test_list_length(); //done
    test_list_remove_entry(); //done
    test_list_remove_data(); //done
    test_list_sort(); //done
    test_list_to_array(); //done
    test_list_iterate(); // probably done - 90%working.There aren't as many asserts as needed.
    return 0;
};

void test_generate_list()
{
    ListEntry* a = NULL;
    assert(list_length(a) == 0);

    assert (list_append (&a, &x) != NULL);
    assert (list_append (&a, &y) != NULL);
    assert (list_append (&a, &z) != NULL);

    assert(list_length(a) == 3);

    list_free (a);
    printf("test_generate_list is passed successfully \n");
}

void test_list_append()
{
    ListEntry* a = NULL;

    (list_append (&a, &x));
    (list_append (&a, &y));
    (list_append (&a, &z));

    assert(list_length(a) == 3);
    ListEntry *node;
    node = a;
    assert(list_data(node) == &x);
    node = a->next;
    assert(list_data(node) == &y);
    node = a->next->next;
    assert(list_data(node) == &z);

    list_free (a);
    printf("test_list_append is passed successfully\n");
}

void test_list_prepend()
{
    ListEntry* a = NULL;

    (list_prepend(&a, &x));
    (list_prepend(&a, &y));
    (list_prepend(&a, &z));

    assert(list_length(a) == 3);
    ListEntry *node = a;
    assert(list_data(node) == &z);
    node = a->next;
    assert(list_data(node) == &y);
    node = a->next->next;
    assert(list_data(node) == &x);

    list_free (a);
    printf("test_list_prepend is passed successfully\n");
}

void test_list_free()
{
    ListEntry *a = NULL;

    (list_append (&a, &x));
    (list_append (&a, &y));
    (list_append (&a, &z));

    list_free (a);

    a = NULL;
    assert(list_data(a)== 0);

    list_free (a);
    printf("test_list_free is passed\n");
}

void test_list_next() {
    ListEntry* a = NULL;
    ListEntry* rover;

    (list_append (&a, &x));
    (list_append (&a, &y));
    (list_append (&a, &z));

    rover = a;
    assert(list_data(rover) == &x);

    rover = list_next(rover);
    assert(list_data(rover) == &y);

    rover = list_next(rover);
    assert(list_data(rover) == &z);

    rover = list_next(rover);
    assert(rover == NULL);


    list_free(a);
    printf("test_list_free is passed successfully\n");
}

void test_list_nth_entry()
{
    ListEntry* a = NULL;
    ListEntry* node;

    (list_append (&a, &x));
    (list_append (&a, &y));
    (list_append (&a, &z));

    node = list_nth_entry (a, 0);
    assert (list_data (node) == &x);

    node = list_nth_entry (a, 1);
    assert (list_data (node) == &y);

    node = list_nth_entry (a, 2);
    assert (list_data (node) == &z);

    node = list_nth_entry (a, 3);
    assert (node == NULL);
    node = list_nth_entry (a, 5);
    assert (node == NULL);

    list_free (a);
    printf("test_list_nth_entry is passed successfully \n");
}

void test_list_nth_data(){
    ListEntry *a = NULL;

    (list_append (&a, &x));
    (list_append (&a, &y));
    (list_append (&a, &z));

    assert (list_nth_data (a, 0) == &x);
    assert (list_nth_data (a, 1) == &y);
    assert (list_nth_data (a, 2) == &z);

    assert (list_nth_data (a, 4) == NULL);
    assert (list_nth_data (a, 5) == NULL);

    list_free (a);
    printf("test_list_nth_data is passed successfully\n");
}

void test_list_length(){
    ListEntry *a = NULL;

    (list_append (&a, &x));
    (list_append (&a, &y));
    (list_append (&a, &z));

    assert(list_length(a) == 3);

    list_free(a);
    printf("test_list_length is passed successfully\n");
}

void test_list_remove_entry()
{
    ListEntry *a = NULL;
    assert (list_remove_entry (&a, NULL) == 0);

    a = NULL;
    assert (list_append (&a, &x) != NULL);
    assert (a != NULL);
    assert (list_remove_entry (&a, a) != 0);
    assert (a == NULL);

    printf("test_list_remove_entry is passed successfully\n");
}

void test_list_remove_data(void) {
    int entries[] = { 89, 4, 23, 4, 8 };
    unsigned int num_entries = 5;
    int value;
    ListEntry* a = NULL;

    for (unsigned int i = 0; i < num_entries; ++i) {
        assert(list_prepend(&a, &entries[i]) != NULL);
    }

    value = 0;
    assert(list_remove_data(&a, int_equal, &value) == 0);
    assert(list_length(a) == num_entries);

    value = 56;
    assert(list_remove_data(&a, int_equal, &value) == 0);
    assert(list_length(a) == num_entries);

    value = 8;
    assert(list_remove_data(&a, int_equal, &value) == 1);
    assert(list_length(a) == num_entries - 1);

    value = 4;
    assert(list_remove_data(&a, int_equal, &value) == 2);
    assert(list_length(a) == num_entries - 3);

    value = 89;
    assert(list_remove_data(&a, int_equal, &value) == 1);
    assert(list_length(a) == num_entries - 4);

    list_free(a);
    printf("test_list_remove_data passed successfully\n");
}

    void test_list_sort(void) {
        int entries[] = { 89, 4, 23, 4, 8 };
        int sorted[]  = { 4, 4, 8, 23, 89 };
        unsigned int num_entries = 5;
        unsigned int i;
        ListEntry* a = NULL;

        for (i = 0; i < num_entries; ++i) {
            assert(list_prepend(&a, &entries[i]) != NULL);
        }

        list_sort(&a, int_compare);

        assert(list_length(a) == num_entries);

        for (i = 0; i < num_entries; ++i) {
            int* value = (int*)list_nth_data(a, i);
            assert(*value == sorted[i]);
        }

        list_free(a);

        a = NULL;
        list_sort(&a, int_compare);
        assert(a == NULL);

        printf("test_list_sort passed successfully\n");
    }

void test_list_to_array() {
    ListEntry* a = NULL;
    void** array;

    list_append(&a, &x);
    list_append(&a, &y);
    list_append(&a, &z);

    array = list_to_array(a);
    assert(array != NULL);

    assert(array[0] == &x);
    assert(array[1] == &y);
    assert(array[2] == &z);

    free(array);

    list_free(a);

    printf("test_list_to_array is passed successfully\n");
}

void test_list_iterate() {
    ListEntry* a = NULL;
    ListIterator iter;
    int i;
    int counter = 0;

    for (i = 0; i < 12; ++i) {
        assert(list_prepend(&a, &i) != NULL);
    }

    list_iterate(&a, &iter);

    while (list_iter_has_more(&iter)) {
        ++counter;

        if ((counter % 2) == 0) {
            list_iter_remove(&iter);
        } else {
            list_iter_next(&iter);
        }
    }

    list_free(a);

    a = NULL;
    counter = 0;

    list_iterate(&a, &iter);

    while (list_iter_has_more(&iter)) {
        list_iter_next(&iter);
        ++counter;
    }

    assert(counter == 0);
    printf("test_list_iterate is passed successfully\n");
}









