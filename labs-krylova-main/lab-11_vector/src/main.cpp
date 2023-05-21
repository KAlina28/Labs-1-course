#include "my_vector.hpp"
#include <iostream>


namespace product {

    class Product {
    public:
        ~Product() {
            delete[] name_;
        }

        Product() {
            name_ = nullptr;
            price_ = 0;
            quantity_ = 0;
        }

        Product(const char *name, int quantity, double price) {
            name_ = new char[strlen(name) + 1];
            strcpy(name_, name);
            quantity_ = quantity;
            price_ = price;
        }

        Product(const Product &p) {
            name_ = p.name_;
            quantity_ = p.quantity_;
            price_ = p.price_;
        }

        bool operator==(const Product &p) const {
            return (strcmp(name_, p.name_) != 0 && quantity_ == p.quantity_ && price_ == p.price_);
        }

        friend std::ostream &operator<<(std::ostream &out, const Product &p) {
            out << p.name_ << " " << p.quantity_ << " " << p.price_;
            return out;
        }


    private:
        char *name_;
        int quantity_;
        double price_;
    };

}  // namespace product


namespace tests {
    template<typename T>
    void test_my_vector(T a, T b) {
        containers::my_vector<T> c;

        c.push_back(a);
        assert(c.size() == 1);
        assert(c.capacity() == 1);

        c.push_back(b);
        c.pop_back();
        assert(c.size() == 1);
        assert(c.capacity() == 2);


        assert(!c.empty());
        c.clear();
        assert(c.empty());

        c.reserve(2);
        c.push_back(a);
        c.push_back(b);
        assert(c.size() == 2);

        c.resize(10);
        assert(c.size() == 10);
        assert(c.capacity() == 16);
    }

    template<typename T>
    void test_my_vector_default_constructible(T a, T b) {
        test_my_vector<T>(a, b);
        containers::my_vector<T> c(3);
        assert(c.size() == 3);
        assert(c.capacity() == 4);
        c[0] = a;
        assert(c[0] == a);
        c.resize(5);
        assert(c.size() == 5);
        assert(c.resize() == 8);
    }
}


int main() {
    containers::my_vector<int> v;
    v.push_back(2);
    const int n{3};
    v.push_back(n);
    std::cout << v << std::endl;

    tests::test_my_vector<int>(5, 10);
    tests::test_my_vector<product::Product>(product::Product("asdf", 4, 12.0),product::Product("qwe", -1, 7.5));

    return 0;
}
