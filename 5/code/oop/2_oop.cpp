#include <iostream>
#include <cstring>

// std::cout << "Ctr" << std::endl;

class StringS {
public:
    StringS(size_t len = 8)
            : len(len) {
        std::cout << "Ctr" << std::endl;
        alloc_data(len);
    }

    StringS(const char *str) : StringS(strlen(str)) {
        copy_data(str);
    }

    StringS(const StringS &rhs) : StringS(rhs.data) {}

    ~StringS() {
        std::cout << "Dtr" << std::endl;
        free(data);
    }

    StringS& operator=(const StringS &rhs) {
        if (this == &rhs) {
            return *this;
        }

        free(data);
        alloc_data(rhs.len);
        copy_data(rhs.data);

        return *this;
    }

    bool operator==(const StringS& rhs){
        return strcmp(this->data, rhs.data) == 0;
    }

    StringS operator+(const StringS& rhs) const {
        return concat(rhs);
    }

    const char *get_data() const {
        return data;
    }

    StringS concat(const StringS& rhs) const {
        //this.data + rhs.data -> res
        StringS res(this->len + rhs.len);

        strncpy(res.data, this->data, this->len);
        strncpy(res.data + this->len, rhs.data, rhs.len);

        res.data[res.len] = '\0';

        return res;
    }

private:
    void alloc_data(size_t len) {
        this->len = len;
        data = static_cast<char *>(calloc(len + 1, 1));
        if (!data) {
            throw std::bad_alloc();
        }
    }

    void copy_data(const char *str) {
        strncpy(data, str, len);
        data[len] = '\0';
    }

    char *data;
    size_t len;
};

int main() {
    const StringS s1("Hello");
    StringS s2(" ");
    StringS s3("world!");

    s3=s3;
    if (s2 == s3){
        std::cout << "condition works" << std::endl;
    }

    const StringS res = s1 + s2 + s3;
    std::cout << res.get_data() << std::endl;

    return 0;
}