#pragma once
#include <iostream>
#include <string>
using namespace std;


//cấu trúc ca làm việc
struct CaLam {
    string maCa;
    string maNV;
    string tenNV;
    string ngayLam;
    string gioBatDau;
    string gioKetThuc;
};

//cấu trúc nhân viên
struct NhanVien {
    string maNV;
    string hoTen;
    string soDT;
    string viTri;
    string matKhau;
};

//cấu trúc phim
struct Phim {
    string maPhim;
    string tenPhim;
    string theLoai;
    int thoiLuong;
};


//khai báo hàm chính
void hienThiChuongTrinh();
void quanLyNhanSu();
void quanLyPhim();
void quanLySuatChieu();
void quanLyDatVe();