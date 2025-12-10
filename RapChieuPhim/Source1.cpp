#include "Header.h"

void hienThiChuongTrinh() {
    //kiểm tra đã đăng nhập chưa
    if (!daDangNhap) {
        cout << "\n Ban chua dang nhap!\n";
        return;
    }

    int chon;
    do {
        cout << "====QUAN LY RAP CHIEU PHIM====\n";
        cout << " Nguoi dung: " << nguoiDangNhap.hoTen << endl;
        cout << " Quyen han: " << chuyenViTriThanhMa(nguoiDangNhap.viTri) << endl;

        //hiển thị menu theo quyền
        if (nguoiDangNhap.viTri == 1) {  
            cout << "1. Quan ly nhan su\n";
            cout << "2. Quan ly phim\n";
            cout << "3. Quan ly suat chieu\n";
            cout << "4. Dat ve\n";
        }
        else if (nguoiDangNhap.viTri == 2) {  //
            cout << "1. Xem thong tin ca nhan\n";
            cout << "4. Dat ve\n";
        }
        cout << "0. Dang xuat\n";
        cout << "================================\n";
        cout << "Nhap lua chon: ";
        cin >> chon;

        switch (chon) {
        case 1:
            if (nguoiDangNhap.viTri == 1) {
                quanLyNhanSu();
            }
            else {
                //xem thông tin cá nhân
                cout << "\n-----THONG TIN CA NHAN-----\n";
                cout << "Ma NV: " << nguoiDangNhap.maNV << endl;
                cout << "Ho ten: " << nguoiDangNhap.hoTen << endl;
                cout << "So DT: " << nguoiDangNhap.soDT << endl;
                cout << "Vi tri: " << chuyenViTriThanhMa(nguoiDangNhap.viTri) << endl;
            }
            break;

        case 2:
            if (nguoiDangNhap.viTri == 1) {
                quanLyPhim();
            }
            else {
                cout << "\nBan khong co quyen!\n";
            }
            break;
        case 3:
            if (nguoiDangNhap.viTri == 1) {
                quanLySuatChieu();
            }
            else {
                cout << "\nBan khong co quyen!\n";
            }
            break;
        case 4:
            if (nguoiDangNhap.viTri == 1 || nguoiDangNhap.viTri == 2) {
                quanLyDatVe();
            }
            else {
                cout << "\nBan khong co quyen!\n";
            }
            break;
        case 0:
            dangXuat();
            cout << "\nTAM BIET!\n";
            break;

        default:
            cout << "\nLua chon khong hop le!\n";
        }
    } while (chon != 0);
}

int main() {
    //HIỆN BẢNG ĐĂNG NHẬP NGAY KHI VÀO CHƯƠNG TRÌNH
    cout << "\n";
    cout << "==========================================\n";
    cout << "=                                        =\n";
    cout << "=     HE THONG QUAN LY RAP CHIEU PHIM    =\n";
    cout << "=                                        =\n";
    cout << "==========================================\n";

    bool tiepTuc = true;
    while (tiepTuc) {
        if (loginNhanVien()) {
            hienThiChuongTrinh();
            char luaChon;
            cout << "\nBan co muon dang nhap lai? (y/n): ";
            cin >> luaChon;

            if (luaChon != 'y' && luaChon != 'Y') {
                tiepTuc = false;
                cout << "\nTAM BIET! HEN GAP LAI!\n";
            }
        }
        else {
            //đăng nhập thất bại, hỏi có thử lại ko
            char luaChon;
            cout << "\nBan co muon thu lai? (y/n): ";
            cin >> luaChon;

            if (luaChon != 'y' && luaChon != 'Y') {
                tiepTuc = false;
                cout << "\nTAM BIET!\n";
            }
        }
    }
    return 0;
}