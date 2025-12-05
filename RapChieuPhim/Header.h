#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>  //để ẩn mật khẩu
#include <ctime>    //để lấy thời gian
#include <fstream>  //để lưu file
using namespace std;
#define MAX_NV 100
#define MAX_LOG 500
#define MAX_PHIM 100

//cấu trúc nhân viên
struct NhanVien {
    string maNV;
    string hoTen;
    string soDT;
    int  viTri=0;
    string matKhau;
};

//cấu trúc lịch sử đăng nhập
struct LichSuDangNhap {
    string maNV;
    string hoTen;
    string thoiGianLogIn;
    string thoiGianLogOut;
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

//hàm xử lý nhân viên
bool loginNhanVien();
void dangXuat();
string taoMaNVTuDong();
string nhapMatKhauAn();
string layThoiGianHienTai();
string chuyenViTriThanhMa(int viTri);
void luuLichSuDangNhap();
void xemLichSuDangNhap();

void themNhanVien(NhanVien dsNV[], int& soLuongNV);
void xoaNhanVien(NhanVien dsNV[], int& soLuongNV);
void hienthiNhanVien(NhanVien dsNV[], int soLuongNV);


//hàm xử lý phim (chỉ quản lý mới dùng được)
void themPhim(Phim dsPhim[], int& soLuongPhim);
void xoaPhim(Phim dsPhim[], int& soLuongPhim);
void hienThiPhim(Phim dsPhim[], int soLuongPhim);
void timKiemPhim(Phim dsPhim[], int soLuongPhim);

//hàm kiểm tra quyền
bool kiemTraQuyen(int quyenYeuCau);