#include <vector>
#include <string>
#include <cmath>
#include <random>
#include <chrono>

class bitwrap {
private:
    std::string astr = "0123456789abcdefghijklmnopqrstuvwxyz";

    //reverse a string
    std::string reverse(std::string str) {
        std::string tmp = "";
        int len = str.length();
        for (int i = 1; i <= len; i++) {
            tmp += str[len - i];
        }
        return tmp;
    }

    //get index of a string
    int indexOf(std::string str, char chr) {
        int res = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == chr) res = i;
        }
        return res;
    }


    //toStrings with a radix
    std::string toBase(int num, int base) {
        std::string str = astr,
            rstr = "";
        int i = 0,
            n = 0,
            strlen = str.length();

        while (n <= num) n = pow(base, i++);
        i -= 2;
        n = pow(base, i);

        for (int c = i; c > -1; c--) {
            int d = pow(base, c);
            rstr += str[(num / d | 0) % base % strlen];
            num = num % d;
        }

        return rstr;
    }

    //parseInt
    int parseInt(std::string str, int radix) {
        int base = 1,
            res = 0;
        std::string bstr = astr;

        str = reverse(str);

        for (char el : str) {
            int n = indexOf(bstr, el);
            res += n * base;
            base *= radix;
        }

        return res;
    }

    std::string gbits(int side = 4) {
        std::string tmp = "";
        for (int i = 0; i < side; i++) {
            tmp += astr[generator() % 2];
        }
        return tmp;
    }

    //slices a string
    std::string slice(std::string str, int min = 0, int max = -1) {
        if (max < 0) max = str.length();
        std::string tmp = "";
        for (int i = min; i < max; i++) tmp += str[i];
        return tmp;
    }

public:
    std::mt19937 generator;
    bitwrap() {
        //cancer c++ sorry :(
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed);
        generator = gen;
    }
    ~bitwrap() {  }

    std::vector<int> wrap(std::vector<int> arr) {
        std::vector<int> tmp = {};
        for (int el : arr) {
            tmp.push_back(parseInt("1" + gbits(3) + toBase(el, 2) + gbits(), 2));
        }
        return tmp;
    }

    std::vector<int> unwrap(std::vector<int> arr) {
        std::vector<int> tmp = {};
        for (int el : arr) {
            std::string bits = toBase(el, 2);
            int blen = bits.length() - 8; //sum of both bits (4 + 4)
            tmp.push_back( parseInt( slice(bits, 4, blen + 4), 2) );
        }
        return tmp;
    }
};
