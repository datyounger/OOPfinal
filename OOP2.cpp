#include <iostream>
#include <string>
using namespace std;

class Nhanvien
{
private:
    string sdt;
    string name;
public:
    Nhanvien(string sdt, string ten) : sdt(sdt), name(ten){}
    ~Nhanvien(){}
    void showinfo(){
        cout << "name" << name << endl;
        cout << "sdt" << sdt <<endl;
    };

};
int main (){
    Nhanvien nv( "Nguyen Van A", "0123456789");
    nv.showinfo();
}
