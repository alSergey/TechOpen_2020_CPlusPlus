
#include <iostream>
#include <cstring>

struct Predicate {
    bool prev = true;

    bool operator()(int a, int b) {
        prev = !prev;
        if (prev) {
            return a > b;
        } else {
            return b > a;
        }
    }
};

namespace tp_prep {
    namespace internal {
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

            StringS &operator=(const StringS &rhs) {
                if (this == &rhs) {
                    return *this;
                }

                free(data);
                alloc_data(rhs.len);
                copy_data(rhs.data);

                return *this;
            }

            bool operator==(const StringS &rhs) {
                return strcmp(this->data, rhs.data) == 0;
            }

            std::ostream &operator>>(std::ostream &os) {
                os << data;
                return os;
            }

            StringS operator+(const StringS &rhs) const {
                return concat(rhs);
            }

            const char *get_data() const {
                return data;
            }

            StringS concat(const StringS &rhs) const {
                StringS res(this->len + rhs.len);

                strncpy(res.data, this->data, this->len);
                strncpy(res.data + this->len, rhs.data, rhs.len);

                res.data[res.len] = '\0';

                return res;
            }

            friend
            std::ostream &operator<<(std::ostream &os, const StringS &str);

            friend
            std::istream &operator>>(std::istream &is, StringS &str);

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


        std::ostream &operator<<(std::ostream &os, const StringS &str) {
            os << str.data;
            return os;
        }

        std::istream &operator>>(std::istream &is, StringS &str) {
            char tmp[4096];
            is.getline(tmp, 4096);

            free(str.data);
            str.alloc_data(strlen(tmp));
            str.copy_data(tmp);

            return is;
        }
    }

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

        StringS &operator=(const StringS &rhs) {
            if (this == &rhs) {
                return *this;
            }

            free(data);
            alloc_data(rhs.len);
            copy_data(rhs.data);

            return *this;
        }

        bool operator==(const StringS &rhs) {
            return strcmp(this->data, rhs.data) == 0;
        }

        std::ostream &operator>>(std::ostream &os) {
            os << data;
            return os;
        }

        StringS operator+(const StringS &rhs) const {
            return concat(rhs);
        }

        const char *get_data() const {
            return data;
        }

        StringS concat(const StringS &rhs) const {
            StringS res(this->len + rhs.len);

            strncpy(res.data, this->data, this->len);
            strncpy(res.data + this->len, rhs.data, rhs.len);

            res.data[res.len] = '\0';

            return res;
        }

        friend
        std::ostream &operator<<(std::ostream &os, const StringS &str);

        friend
        std::istream &operator>>(std::istream &is, StringS &str);

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

        size_t len;
        char *data;
    };


    std::ostream &operator<<(std::ostream &os, const StringS &str) {
        os << str.data;
        return os;
    }

    std::istream &operator>>(std::istream &is, StringS &str) {
        char tmp[4096];
        is.getline(tmp, 4096);

        free(str.data);
        str.alloc_data(strlen(tmp));
        str.copy_data(tmp);

        return is;
    }
}

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

    StringS &operator=(const StringS &rhs) {
        if (this == &rhs) {
            return *this;
        }

        free(data);
        alloc_data(rhs.len);
        copy_data(rhs.data);

        return *this;
    }

    bool operator==(const StringS &rhs) {
        return strcmp(this->data, rhs.data) == 0;
    }

    std::ostream &operator>>(std::ostream &os) {
        os << data;
        return os;
    }

    StringS operator+(const StringS &rhs) const {
        return concat(rhs);
    }

    const char *get_data() const {
        return data;
    }

    //str.concat(str1) -> concat(&str, str1)
    StringS concat(const StringS &rhs) const {
        StringS res(this->len + rhs.len);

        strncpy(res.data, this->data, this->len);
        strncpy(res.data + this->len, rhs.data, rhs.len);

        res.data[res.len] = '\0';

        return res;
    }

    friend
    std::ostream &operator<<(std::ostream &os, const StringS &str);

    friend
    std::istream &operator>>(std::istream &is, StringS &str);

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


std::ostream &operator<<(std::ostream &os, const StringS &str) {
    int i;
    os << str.data; // addr(str) + sizeof(size_t) /*len*/ == addr(str.data)
    return os;
}

std::istream &operator>>(std::istream &is, StringS &str) {
    char tmp[4096];
    is.getline(tmp, 4096);

    free(str.data);
    str.alloc_data(strlen(tmp));
    str.copy_data(tmp);

    return is;
}

int main() {
    Predicate p;
    std::cout << p(1,2) << '\n' << p(1,2);

    tp_prep::StringS str = "This is my own string!";
    StringS str1 = "This is my own string!";
    tp_prep::internal::StringS str2 = "This is my own string!";
    int i = 123;

    str == str2;

    std::cout << str << std::endl;
    operator<<(std::cout, str) << std::endl;

    std::cin >> str1;
    std::cout << str1 << std::endl;

    return 0;
}