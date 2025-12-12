#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>  //để ẩn mật khẩu
#include <ctime>    //để lấy thời gian
#include <fstream>  //để lưu file
#include <vector>
using namespace std;
#define MAX_NV 100
#define MAX_LOG 500
#define MAX_PHIM 100
#define MAX_SUATCHIEU 100
#define SO_HANG 8     //8 hàng ghế (A-H)
#define SO_COT 10     //10 cột ghế (1-10)
#define GIA_VE 50000  //giá vé 50000VND

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
    int thoiLuong=0;
};

//cấu trúc suất chiếu
struct SuatChieu {
    string maSuat;
    string maPhim;
    string tenPhim;
    string ngayChieu;
    string gioChieu;
    string phongChieu; 
    int soGheTrong=0;
    bool trangThaiGhe[SO_HANG][SO_COT]; //false=trống, true=đã đặt
};

//cấu trúc vé
struct Ve {
    string maVe;
    string maSuat;
    string tenPhim;
    string ngayChieu;
    string gioChieu;
    string phongChieu;
    string danhSachGhe; 
    int soLuongGhe=0;
    int tongTien=0;
    string thoiGianDat;
};

//khai báo hàm chính
void hienThiChuongTrinh();
void quanLyNhanSu();
void quanLyPhim();
void quanLySuatChieu();
void quanLyDatVe();

//khai báo biến toàn cục
extern NhanVien nguoiDangNhap;
extern bool daDangNhap;

//hàm xử lý nhân viên
bool loginNhanVien();
void dangXuat();
string taoMaNVTuDong(int soLuongNV);
string nhapMatKhauAn();
string layThoiGianHienTai();
string chuyenViTriThanhMa(int viTri);
void luuLichSuDangNhap();
void xemLichSuDangNhap();
void luuNhanVien();
void docNhanVien();

void themNhanVien(NhanVien dsNV[], int& soLuongNV);
void xoaNhanVien(NhanVien dsNV[], int& soLuongNV);
void hienThiNhanVien(NhanVien dsNV[], int soLuongNV);


////hàm xử lý phim (chỉ quản lý mới dùng được)
void themPhim(Phim dsPhim[], int& soLuongPhim);
void xoaPhim(Phim dsPhim[], int& soLuongPhim);
void hienThiPhim(Phim dsPhim[], int soLuongPhim);
void timKiemPhim(Phim dsPhim[], int soLuongPhim);
string taoMaPhimTuDong(int soLuongPhim);

//hàm xử lý suất chiếu (chỉ quản lý mới dùng được)
void themSuatChieu(SuatChieu dsSuat[], int& soLuongSuat, Phim dsPhim[], int soLuongPhim);
void xoaSuatChieu(SuatChieu dsSuat[], int& soLuongSuat);
void hienThiSuatChieu(SuatChieu dsSuat[], int soLuongSuat);
void timKiemSuatChieu(SuatChieu dsSuat[], int soLuongSuat);
string taoMaSuatTuDong(int soLuongSuat);

//hàm xử lý đặt vé
void datVe(SuatChieu dsSuat[], int soLuongSuat, Ve dsVe[], int& soLuongVe);
void hienThiSoDoGhe(SuatChieu& suat);
void inHoaDon(Ve ve);
void luuVeRaFile(Ve ve);
string taoMaVeTuDong(int soLuongVe);

//hàm kiểm tra quyền
bool kiemTraQuyen(int quyenYeuCau);