#include <assert.h>
#include <stdio.h>
#include "compare-int.h"
#include "compare-int.c"

#include "list.h"
#include "list.c"

void test_new(void);
void test_append(void);
void test_clear(void);
void test_free(void);
void test_index_of(void);
void test_insert(void);
void test_prepend(void);
void test_remove(void);
void test_remove_range(void);
void test_sort(void);
void test_remove_at();

int main(void)
{
    test_new();
    test_append();
    test_clear();
    test_free();
    test_index_of();
    test_insert();
    test_prepend();
    test_remove();
    test_remove_range();
    test_remove_at();
    test_sort();

    return 0;
}

    void test_new()
    {
       ListEntry *a = NULL;
        assert(list_length(a) == 0);
    }

void test_append(void){
    ListEntry *a = NULL;
    list_append(&a, (ListValue)(7));
    list_append(&a, (ListValue)(6));
    list_append(&a, (ListValue)(5));
    assert(list_length(a) == 3);
    assert((int)list_data(a) == 5);
//    ListEntry *current = a;
//    while (current->next != NULL) {
//        current = current->next;
//    }
//    assert((int)list_data(current) == 120);
}

void test_clear(){
    ListEntry *a = NULL;
    list_append(&a, (ListValue)(7));
    list_append(&a, (ListValue)(6));
    list_append(&a, (ListValue)(5));
    list_remove_entry(&a,a);
    list_remove_entry(&a,a);
    list_remove_entry(&a,a);
    assert(list_length(a) == 0);
}

void test_free(){
    ListEntry *a = NULL;

    list_append(&a, (ListValue)(7));
    list_append(&a, (ListValue)(6));
    list_append(&a, (ListValue)(5));

    list_free(a);

    // a = NULL;
    assert(a == NULL);
}

void test_index_of()
{
    ListEntry *a = NULL;
    list_append(&a, (ListValue)(7));
    list_append(&a, (ListValue)(6));
    list_append(&a, (ListValue)(5));

    list_to_array(a);

//    for (unsigned int i = 0; i < list_length(a); i++)
//    {
//    }
}

    void test_insert()
{
    ListEntry *a = NULL;
    list_append(&a, (ListValue)(7));
    list_append(&a, (ListValue)(6));
    list_append(&a, (ListValue)(5));

}

void test_prepend()
{
    ListEntry *a = NULL;
    list_prepend(&a, (ListValue)(7));
    list_prepend(&a, (ListValue)(6));
    list_prepend(&a, (ListValue)(5));

    assert(list_length(a) == 3);
    assert((int)list_data(a) == 5);
}

void test_remove()
{
    ListEntry *a = NULL;
    list_append(&a, (ListValue)(7));
    list_append(&a, (ListValue)(6));
    list_append(&a, (ListValue)(5));
}
void test_remove_range()
{

}
void test_sort()
{

}
void test_remove_at()
{

}


