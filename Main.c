#include <assert.h>
#include "HashMap.h"

typedef struct String {
    char *chars;
    int length;
} String;

int stringHashCode(void *value) {
    String string = *((String *) value);
    return string.length;
}

bool stringEquals(void *value1, void *value2) {
    if (value1 == 0 || value2 == 0) {
        return false;
    }
    String string1 = *((String *)value1);
    String string2 = *((String *)value2);
    if (string1.length != string2.length) {
        return false;
    }
    for (int i = 0; i < string1.length; i++) {
        if (string1.chars[i] != string2.chars[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    HashMap map = *createHashMap(stringHashCode, stringEquals);
    String key1 = {"a", 1}; String value1 = {"1", 1};
    put(&map, &key1, &value1);
    String key2 = {"22", 2};String value2 = {"2", 1};
    put(&map, &key2, &value2);
    String key3 = {"333", 3};String value3 = {"3", 1};
    put(&map, &key3, &value3);
    String key4 = {"b", 1};String value4 = {"1", 1};
    put(&map, &key4, &value4);
    String key5 = {"c", 1};String value5 = {"1", 1};
    put(&map, &key5, &value5);
    String key6 = {"d", 1};String value6 = {"1", 1};
    put(&map, &key6, &value6);
    String key7 = {"4444", 4};String value7 = {"4", 1};
    put(&map, &key7, &value7);
    String key8 = {"55555", 5};String value8 = {"5", 1};
    put(&map, &key8, &value8);
    String key9 = {"666666", 6};String value9 = {"6", 1};
    put(&map, &key9, &value9);
    assert(stringEquals(get(&map, &key7), &value7));
    remove(&map, &key7);
    assert(get(&map, &key7) == 0);
    freeHashMap(&map);
    return 0;
}