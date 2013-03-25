/**
C++11ÐÂ¹Ø¼ü×ÖÊÔÓÃ
*/

#include <iostream>

using namespace std;

namespace localname {
    struct nullptr_t{
        void *_;
        struct __nat {int __for_bool__;};
        nullptr_t(int __nat::*) {cout<<"nullptr_t construct is called"<<endl;}
        operator int __nat::*()const {cout<<"operator __nat::* is called"<<endl;return 0;}
        template <typename _Tp>
        operator _Tp*() const {return 0;}
        template <typename _Tp, typename _Up>
        operator _Tp _Up::* () const {return 0;}
        friend bool operator==(nullptr_t, nullptr_t) {return true;}
        friend bool operator!=(nullptr_t, nullptr_t) {return false;}
        friend bool operator<(nullptr_t, nullptr_t) {return false;}
        friend bool operator<=(nullptr_t, nullptr_t) {return true;}
        friend bool operator>(nullptr_t, nullptr_t) {return false;}
        friend bool operator>=(nullptr_t, nullptr_t) {return true;}
    };
    struct Test{};
};

using namespace localname;

inline nullptr_t __get_nullptr_t() {return nullptr_t(0);}
#define nullptr __get_nullptr_t()
int main() {
    char *pch = nullptr;//template 1
    int *pint = nullptr;//template 1
    bool b = nullptr;//operateor
    int Test::*p = nullptr;//template 2
    void (Test::*pfn)(int, char) = nullptr;//template2
    return 0;
}
