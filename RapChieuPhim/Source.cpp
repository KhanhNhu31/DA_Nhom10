#include "Header.h"

//biến toàn cục
NhanVien danhSachNV[MAX_NV];
int soLuongNV = 0;
LichSuDangNhap lichSuLog[MAX_LOG];
int soLuongLogIn = 0;
NhanVien nguoiDangNhap; //người đang đăng nhập
bool daDangNhap = false;
int indexDangNhap = -1;
Phim danhSachPhim[MAX_PHIM];

//CÁC HÀM HỖ TRỢ
string taoMaNVTuDong() {
	string maNV = "NV";
	int soThuTu = soLuongNV + 1;
	if (soThuTu < 10) {
		maNV += "00" + to_string(soThuTu);
	}
	else if (soThuTu < 100) {
		maNV += "0" + to_string(soThuTu);
	}
	else {
		maNV += to_string(soThuTu);
	}
	return maNV;
}

string nhapMatKhauAn() {
	string matKhau = "";
	char ch;
	while (true) {
		ch = _getch();
		if (ch == 13) {
			cout << endl;
			break;
		}
		else if (ch == 8) {
			if (matKhau.length() > 0) {
				matKhau.pop_back();
				cout << "\b \b";
			}
		}
		else {
			matKhau += ch;
			cout << '*';
		}
	}
	return matKhau;
}

string layThoiGianHienTai() {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	string thoiGian = "";
	thoiGian += to_string(ltm->tm_mday) + "/";
	thoiGian += to_string(1 + ltm->tm_mon) + "/";
	thoiGian += to_string(1900 + ltm->tm_year) + " ";
	thoiGian += to_string(ltm->tm_hour) + ":";
	thoiGian += to_string(ltm->tm_min) + ":";
	thoiGian += to_string(ltm->tm_sec);
	return thoiGian;
}

string chuyenViTriThanhMa(int viTri) {
	if (viTri == 1)return"Quan ly";
	if (viTri == 2)return"NV Ban ve";
	return "Khong xac dinh!";
}

//kiểm tra quyền truy cập
bool kiemTraQuyen(int quyenYeuCau) {
	if (!daDangNhap) {
		cout << "\n Ban chua dang nhap!\n";
		return false;
	}
	if (nguoiDangNhap.viTri == 1) {
		return true;
	}
	if (nguoiDangNhap.viTri != quyenYeuCau) {
		cout << "\n BAN KHONG CO QUYEN TRUY CAP!\n";
		cout << "Quyen cua ban: " << chuyenViTriThanhMa(nguoiDangNhap.viTri) << endl;
		return false;
	}
	return true;
}

//lưu lịch sử ra file
void luuLichSuDangNhap() {
	ofstream file("lichsudangnhap.txt");
	file << "====LICH SU DANG NHAP HE THONG====\n\n";
	file << left << setw(10) << "MaNV"
		<< setw(25) << "Ho ten"
		<< setw(22) << "Thoi gian login"
		<< setw(22) << "Thoi gian logout" << endl;
	file << string(79, '-') << endl;
	for (int i = 0;i < soLuongLogIn;i++) {
		file << left << setw(10) << lichSuLog[i].maNV
			<< setw(25) << lichSuLog[i].hoTen
			<< setw(22) << lichSuLog[i].thoiGianLogIn
			<< setw(22) << lichSuLog[i].thoiGianLogOut << endl;
	}
	file.close();
}

//hàm đăng nhập
bool loginNhanVien() {
	string maNV;
	string matKhau;

//tạo tk mặc định nếu chưa có nv
	if (soLuongNV == 0) {
		danhSachNV[0].maNV = "admin";
		danhSachNV[0].hoTen = "Quan tri vien";
		danhSachNV[0].soDT = "0123456789";
		danhSachNV[0].viTri = 1;
		danhSachNV[0].matKhau = "3110";
		soLuongNV = 1;
		cout << "\n============================================\n";
		cout << "\nDa tao tai khoan mac dinh: admin\n";
		cout << "Quyen: Quan ly(toan quyen)\n";
		cout << "\n============================================\n";
	}

	cout << "\n===== DANG NHAP HE THONG ====\n";
	cout << "Ma nhan vien: ";
	cin >> maNV;
	cout << "Mat khau: ";
	matKhau = nhapMatKhauAn();

	for (int i = 0;i < soLuongNV;i++) {
		if (danhSachNV[i].maNV == maNV && danhSachNV[i].matKhau == matKhau) {
			nguoiDangNhap = danhSachNV[i];
			daDangNhap = true;
			//ghi nhận thời gian login
			lichSuLog[soLuongLogIn].maNV = nguoiDangNhap.maNV;
			lichSuLog[soLuongLogIn].hoTen = nguoiDangNhap.hoTen;
			lichSuLog[soLuongLogIn].thoiGianLogIn = layThoiGianHienTai();
			lichSuLog[soLuongLogIn].thoiGianLogOut = "Dang hoat dong";
			indexDangNhap = soLuongLogIn;
			soLuongLogIn++;
			cout << "\n====DANG NHAP THANH CONG!====\n";
			cout << "Chao mung: " << nguoiDangNhap.hoTen << endl;
			cout << "Quyen: " << chuyenViTriThanhMa(nguoiDangNhap.viTri) << endl;
			cout << "Thoi gian: " << layThoiGianHienTai() << endl;
			cout << "================================\n";
			return true;
		}
	}
	cout << "\n Dang nhap that bai!\n";
	return false;
}

void dangXuat() {
	if (!daDangNhap) {
		cout << "\n Ban chua dang nhap kia\n";
		return;
	}
	//ghi nhận thời gian logout
	lichSuLog[indexDangNhap].thoiGianLogOut = layThoiGianHienTai();
	cout << "\n====DANG XUAT THANH CONG!====\n";
	cout << "Tam biet: " << nguoiDangNhap.hoTen << endl;
	cout << "Thoi gian: " << layThoiGianHienTai() << endl;
	cout << "===============================\n";

	luuLichSuDangNhap();
	//reset trạng thái
	daDangNhap = false;
	indexDangNhap = -1;
}

//hàm thêm nhân viên
void themNhanVien(NhanVien dsNV[], int& soLuongNV) {
	if (!kiemTraQuyen(1)) {
		return;
	}
	if (soLuongNV >= MAX_NV) {
		cout << "\n Danh sach nhan vien day!\n";
		return;
	}
	NhanVien nv;
	cin.ignore();
	cout << "\n----THEM NHAN VIEN----\n";
	cout << "Nhap ma nhan vien: ";
	getline(cin, nv.maNV);

//kiểm tra trùng mã
	for (int i = 0;i < soLuongNV;i++) {
		if (dsNV[i].maNV == nv.maNV) {
			cout << "\nMa nhan vien da ton tai!\n";
			return;
		}
	}
	cout << "Nhap ho ten: ";
	getline(cin, nv.hoTen);

	cout << "Nhap so dien thoai: ";
	getline(cin, nv.soDT);

	cout << "Nhap vi tri (1: Quan ly, 2: NV Ban ve): ";
	cin >> nv.viTri;
	cin.ignore();

	cout << "Nhap mat khau: ";
	cin.ignore();
	nv.matKhau = nhapMatKhauAn();

	dsNV[soLuongNV] = nv;
	soLuongNV++;
	cout << "\n Them nhan vien thanh cong!!\n";
}

//hàm hiển thị danh sách nv
void hienThiNhanVien(NhanVien dsNV[], int soLuongNV) {
	if (!kiemTraQuyen(1)) {
		return;
	}
	if (soLuongNV == 0) {
		cout << "\n Danh sach nhan vien trong!\n";
		return;
	}

	cout << "\n----- DANH SACH NHAN VIEN -----\n";
	cout << left << setw(12) << "Ma NV"
		<< setw(25) << "Ho ten"
		<< setw(15) << "So DT"
		<< setw(15) << "Vi tri" << endl;
	cout << string(67, '-') << endl;

	for (int i = 0; i < soLuongNV; i++) {
		cout << left << setw(12) << dsNV[i].maNV
			<< setw(25) << dsNV[i].hoTen
			<< setw(15) << dsNV[i].soDT
			<< setw(15) << dsNV[i].viTri << endl;
	}
}

//hàm xóa nhân viên
void xoaNhanVien(NhanVien dsNV[], int& soLuongNV) {
	if (soLuongNV == 0) {
		cout << "\nDanh sach nhan vien trong!\n";
		return;
	}

	string maXoa;
	cin.ignore();
	cout << "\nNhap ma nhan vien can xoa: ";
	getline(cin, maXoa);

	if (maXoa == "admin") {
		cout << "\nKhong the xoa tai khoan admin!\n";
		return;
	}

	for (int i = 0; i < soLuongNV; i++) {
		if (dsNV[i].maNV == maXoa) {
			for (int j = i; j < soLuongNV - 1; j++) {
				dsNV[j] = dsNV[j + 1];
			}
			soLuongNV--;
			cout << "\nXoa nhan vien thanh cong!\n";
			return;
		}
	}

	cout << "\nKhong tim thay nhan vien co ma: " << maXoa << endl;
}


void xemLichSuDangNhap() {
	if (!kiemTraQuyen(1)) {
		return;
	}
	if (soLuongLogIn == 0) {
		cout << "\nChua co lich su dang nhap\n";
		return;
	}
	cout << "\n====LICH SU DANG NHAP====\n";
	cout << left << setw(10) << "Ma NV"
		<< setw(25) << "Ho ten"
		<< setw(22) << "Login"
		<< setw(22) << "Logout" << endl;
	cout << string(79, '-') << endl;
	for (int i = 0; i < soLuongLogIn; i++) {
		cout << left << setw(10) << lichSuLog[i].maNV
			<< setw(25) << lichSuLog[i].hoTen
			<< setw(22) << lichSuLog[i].thoiGianLogIn
			<< setw(22) << lichSuLog[i].thoiGianLogOut << endl;
	}
}
//hàm quản lý nhân viên
void quanLyNhanSu() {
	if (!kiemTraQuyen(1)) {
		return;
	}
	int chon;
	do {
		cout << "\n==== QUAN LY NHAN SU ====\n";
		cout << "1.Them nhan vien\n";
		cout << "2.Xem thong tin nhan vien\n";
		cout << "3.Xem lich su dang nhap\n";
		cout << "4.Xoa nhan vien\n";
		cout << "0.Quay lai\n";
		cout << "Lua chon cua ban: ";
		cin >> chon;

		switch (chon) {
		case 1:
			themNhanVien(danhSachNV, soLuongNV);
			break;
		case 2:
			hienThiNhanVien(danhSachNV, soLuongNV);
			break;
		case 3:
			xemLichSuDangNhap();
			break;
		case 4:
			xoaNhanVien(danhSachNV, soLuongNV);
		case 0:
			cout << "\n Quay lai menu chinh...\n";
			break;
		default:
			cout << "\n Lua chon cua ban khong hop le!\n";
		}
	} while (chon != 0);
	
}

void quanLyPhim() {
	cout << "\n [Quan ly phim]";
}

void quanLySuatChieu() {
	cout << "\n [Quan ly suat chieu]";
}

void quanLyDatVe() {
	cout << "\n [Dat ve]";
}