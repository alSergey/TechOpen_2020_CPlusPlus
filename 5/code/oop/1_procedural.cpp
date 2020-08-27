#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>


struct StringS {
    char *data;
    size_t len;
};

StringS *initString(size_t len) {
    auto res = static_cast<StringS *>(calloc(1, sizeof(StringS)));
    if (!res) {
        return nullptr;
    }

    res->len = len;

    res->data = static_cast<char *>(calloc(res->len + 1, 1));
    if (!res->data) {
        free(res);
        return nullptr;
    }

    return res;
}

StringS *initString(const char *str) {
    assert(str);
    auto res = initString(strlen(str));
    if (!res) {
        return nullptr;
    }

    strncpy(res->data, str, res->len);
    res->data[res->len] = '\0';

    return res;
}

void freeString(StringS *str) {
    assert(str);
    free(str->data);
    free(str);
}

StringS *concat(const StringS *a, const StringS *b) {
    assert(a && b);
    auto res = initString(a->len + b->len);
    if (!res) {
        return nullptr;
    }

    strncpy(res->data, a->data, a->len);
    strncpy(res->data + a->len, b->data, b->len);
    res->data[res->len] = '\0';

    return res;
}

int main() {
    int a = 5;
    int b = 11;
    int c = a + b;

    StringS tmp_s;
    tmp_s.len = 123;

    StringS *s1 = initString("Hello,");
    if (!s1) {
        return -1;
    }
    StringS *s2 = initString(" ");
    if (!s2) {
        freeString(s1);
        return -1;
    }
    StringS *s3 = initString("world!");
    if (!s3) {
        freeString(s2);
        freeString(s1);
        return -1;
    }

    StringS *s2_s3 = concat(s2, s3);
    if (!s2_s3) {
        freeString(s3);
        freeString(s2);
        freeString(s1);
        return -1;
    }

    auto res = concat(s1, s2_s3);
    if (!res) {
        freeString(s2_s3);
        freeString(s3);
        freeString(s2);
        freeString(s1);
        return -1;
    }


    std::cout << res->data << std::endl;

    freeString(s2_s3);
    freeString(res);
    freeString(s3);
    freeString(s2);
    freeString(s1);

    return 0;
}