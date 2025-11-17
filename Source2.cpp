#include "Header.h"

void hienThiChuongTrinh() {
	int chon;
	do {
		cout << "\n==== CHUONG TRINH DAT VE XEM PHIM ====\n";
		cout << "1. Quan ly nhan su\n";
		cout << "2. Quan ly phim\n";
		cout << "3. Quan ly suat chieu\n";
		cout << "4. Dat ve\n";
		cout << "0. Thoat chuong trinh\n";
		cout << "Nhap lua chon cua ban nha";
		cin >> chon;

		switch (chon) {
			case 1;
				quanLyNhanSu();
				break;
			case 2;
				quanLyPhim();
				break;
			case 3;
				quanLySuatChieu();
				break;
			case 4;
				quanLyDatVe;
				break;
			case 0;
				cout << "\n Dang thoat chuong trinh!\n";
				break;
			default;
				cout << "\n Lua chon khong hop le, vui long nhap lai!\n";
		}
	} while (chon != 0);
}
int main() {
	hienThiChuongTrinh();
	return 0;
}