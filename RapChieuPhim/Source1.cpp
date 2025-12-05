#include "Header.h"

void hienThiChuongTrinh() {
	int chon;
    NhanVien nguoiDangNhap;

	do {
		cout << "\n==== CHUONG TRINH DAT VE XEM PHIM ====\n";
		cout << "1. Nguoi dung: " << nguoiDangNhap.hoTen << endl;
		cout << "2. Quyen han: " << chuyenViTriThanhMa(nguoiDangNhap.viTri) << endl;
		
//hiển thị menu theo quyền
		if (nguoiDangNhap.viTri == 1) {
			cout << "1. Quan ly nhan su\n";
			cout << "2. Quan ly phim\n";
			cout << "3. Quan ly suat chieu\n";
			cout << "4. Dat ve\n";
		}
		else if (nguoiDangNhap.viTri == 2) {  
			cout << "1. Xem thong tin ca nhan\n";
			cout << "3. Dat ve\n";
		}
		cout << "0. Dang xuat\n";
		cout << "========================================\n";
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
                    cout << "\n Ban khong co quyen!\n";
                }
                break;

            case 3:
                if (nguoiDangNhap.viTri == 1 || nguoiDangNhap.viTri == 2) {
                    quanLyDatVe();
                }
                else {
                    cout << "\n Ban khong co quyen!\n";
                }
                break;
            case 0:
                dangXuat();
                cout << "\n TAM BIET!\n";
                break;

            default:
                cout << "\n Lua chon khong hop le!\n";
        }
    } while (chon != 0);
}
int main() {
	cout << "\n";
	cout << "==========================================\n";
	cout << "=                                        =\n";
	cout << "=     HE THONG QUAN LY RAP CHIEU PHIM    =\n";
	cout << "=                                        =\n";
	cout << "==========================================\n";

	if (!loginNhanVien()) {
		cout << "\n Dang nhap that bai!\n";
		return 0;
	}
	hienThiChuongTrinh();
	return 0;
}



