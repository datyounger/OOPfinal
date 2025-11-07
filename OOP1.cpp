#include <iostream>
#include <string>
using namespace std;
class person
{
private:
    string name;
    int age;
    string cccd;
    string gioitinh;
    int sdt;

public:
    person(string n, int a, string c, string gt, int sdt) : name(n), age(a), cccd(c), gioitinh(gt), sdt(sdt) {}
    ~person() {}
    void showInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "CCCD: " << cccd << endl;
        cout << "gioitinh: " << gioitinh << endl;
        cout << "SDT: " << sdt << endl;
    }
};
class Nhanvien : public person
{
private:
    string manv;
    string phongban;
    int luong;

public:
    Nhanvien(string n, int a, string c, string gt, int sdt, string mnv, string pb, int l)
        : person(n, a, c, gt, sdt), manv(mnv), phongban(pb), luong(l) {}
    ~Nhanvien() {}
    void showInfo()
    {
        person::showInfo();
        cout << "Ma NV: " << manv << endl;
        cout << "Phong Ban: " << phongban << endl;
        cout << "Luong: " << luong << endl;
    }
};
class Sinhvien : public person
{
private:
    string msv;
    string khoa;
    float diemTB;
    int x;

public:
    Sinhvien(string n, int a, string c, string gt, int sdt, string msv, string k, float dtb)
        : person(n, a, c, gt, sdt), msv(msv), khoa(k), diemTB(dtb) {}
    ~Sinhvien() {}
    void showInfo()
    {
        person::showInfo();
        cout << "Ma SV: " << msv << endl;
        cout << "Khoa: " << khoa << endl;
        cout << "Diem TB: " << diemTB << endl;
    }
    
};
int main()
{
    Nhanvien nv("Nguyen Van A", 30, "123456789", "Male", 987654321, "NV001", "IT", 15000000);
    Sinhvien sv("Tran Thi B", 20, "987654321", "Female", 123456789, "SV001", "CNTT", 8.5);

    cout << "Nhan Vien Info:" << endl;
    nv.showInfo();
    cout << endl;

    cout << "Sinh Vien Info:" << endl;
    sv.showInfo();
    cout << endl;

    return 0;
}