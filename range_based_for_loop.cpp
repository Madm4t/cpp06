
#include <string>
#include <iostream>


Range-based for works on any “range”:
The thing after the colon in
for ( ElementType& name : some_range ) {
    …
}
It’s a C-style array (e.g. int arr[10]), or
It has free or member overloads of begin() and end()
In practice that means you can loop over:
Standard containers (std::vector, std::string, std::map, …)
C-arrays (int a[] = {1,2,3};)
std::initializer_lists (for (auto x : {1,2,3}) …)
Even your own types, so long as you provide begin()/end()
You can write char c if you want a copy, char& c to mutate the element in place, or const char& c to read without copying.
You can also use auto, auto&, or const auto& to let the compiler deduce the exact type.


std::string s = "Hello";
for (char& c : s) {
    c = std::toupper(c);  // modifies each character in s
}

int arr[] = {1,2,3,4};
for (auto x : arr) {
    std::cout << x << ' ';  // prints 1 2 3 4
}

std::vector<double> v{3.14, 2.71, 1.62};
for (const auto& d : v) {
    std::cout << d << '\n'; // safe read-only access
}

In each case, the thing after : is a “range,” not strictly an std::container.

The compiler looks for begin(range) and end(range) (via ADL or members) to drive the loop.
What does const auto& d mean here?
auto& d would be a reference to each double in the vector—you could write d = 99.9; and mutate v.

const auto& d is a reference-to-const, so d is read-only: any attempt to assign through it is a compile-time error.

Why does re-binding still work?
A reference in C++ must be initialized when it’s declared and can’t be re-“reseated” afterwards.

But in a range-based for, each iteration is conceptually equivalent to:

for (/* init hidden */) {
    const double& d = /* next element of v */;
    // …
}
So every pass creates a fresh const double& d bound to that iteration’s element. There’s never a single reference being “moved around”; instead, the loop constructs a new one each time.