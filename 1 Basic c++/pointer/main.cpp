#include <iostream>

using namespace std;



void changePointer(int*& ptr) {
    int y = 10;    // Khai báo biến y trong hàm (biến cục bộ)
    ptr = &y;      // Thay đổi con trỏ ptr để trỏ đến y
}

int main() {
    int x = 5;
    int* ptr = &x; // Con trỏ ptr trỏ tới x

    std::cout << "Before: ptr is pointing to " << *ptr << std::endl;  // ptr trỏ đến x

    changePointer(ptr);  // Gọi hàm để thay đổi con trỏ ptr trỏ tới y

    std::cout << "After: ptr is pointing to " << *ptr << std::endl;   // ptr trỏ đến y, nhưng sau hàm y không tồn tại nữa!

    return 0;
}
