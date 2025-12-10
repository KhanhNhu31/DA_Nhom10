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
int soLuongPhim = 0;
SuatChieu danhSachSuatChieu[MAX_SUATCHIEU];
int soLuongSuatChieu = 0;
Ve danhSachVe[500];
int soLuongVe = 0;

//CÁC HÀM HỖ TRỢ
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
		cout << "\n----Da tao tai khoan mac dinh: admin----\n";
		cout << "Quyen: Quan ly(toan quyen)\n";
	}

	cout << "\n=====DANG NHAP HE THONG====\n";
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
	cout << "Nhap ma nhan vien(VD: NV001, NV002,..): ";
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

	cout << "Nhap mat khau: ";
	nv.matKhau = nhapMatKhauAn();

	dsNV[soLuongNV] = nv;
	soLuongNV++;
	cout << "\nThem nhan vien thanh cong!!\n";
}

//hàm hiển thị danh sách nv
void hienThiNhanVien(NhanVien dsNV[], int soLuongNV) {
	if (!kiemTraQuyen(1)) {
		return;
	}
	if (soLuongNV == 0) {
		cout << "\nDanh sach nhan vien trong!\n";
		return;
	}

	cout << "\n-----DANH SACH NHAN VIEN-----\n";
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
//hàm quản lý nv
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
			break;
		case 0:
			cout << "\n Quay lai menu chinh...\n";
			break;
		default:
			cout << "\n Lua chon cua ban khong hop le!\n";
		}
	} while (chon != 0);
	
}


//hàm thêm phim
void themPhim(Phim dsPhim[], int& soLuongPhim) {
	if (soLuongPhim >= MAX_PHIM) {
		cout << "\nDanh sach phim da day!\n";
		return;
	}

	Phim phim;
	cin.ignore();

	cout << "\n-----THEM PHIM-----\n";
	cout << "Nhap ma phim(VD: P01, P02,...): ";
	getline(cin, phim.maPhim);

	//kiểm tra trùng mã
	for (int i = 0; i < soLuongPhim; i++) {
		if (dsPhim[i].maPhim == phim.maPhim) {
			cout << "\nMa phim da ton tai!\n";
			return;
		}
	}

	cout << "Nhap ten phim: ";
	getline(cin, phim.tenPhim);

	cout << "Nhap the loai: ";
	getline(cin, phim.theLoai);

	cout << "Nhap thoi luong (phut): ";
	cin >> phim.thoiLuong;
	cin.ignore();

	dsPhim[soLuongPhim] = phim;
	soLuongPhim++;
	cout << "\nThem phim thanh cong!\n";
}

		
//hàm xóa phim
void xoaPhim(Phim dsPhim[], int& soLuongPhim) {
	if (soLuongPhim == 0) {
		cout << "\nDanh sach phim trong!\n";
		return;
	}

	string maXoa;
	cin.ignore();
	cout << "\nNhap ma phim can xoa: ";
	getline(cin, maXoa);

	for (int i = 0; i < soLuongPhim; i++) {
		if (dsPhim[i].maPhim == maXoa) {
			cout << "\nBan co chac chan muon xoa phim '" << dsPhim[i].tenPhim << "'? (y/n): ";
			char xacNhan;
			cin >> xacNhan;

			if (xacNhan == 'y' || xacNhan == 'Y') {
				for (int j = i; j < soLuongPhim - 1; j++) {
					dsPhim[j] = dsPhim[j + 1];
				}
				soLuongPhim--;
				cout << "\nXoa phim thanh cong!\n";
			}
			else {
				cout << "\nHuy xoa phim.\n";
			}
			return;
		}
	}

	cout << "\nKhong tim thay phim co ma: " << maXoa << endl;
}

//hàm hiển thị danh sách phim
void hienThiPhim(Phim dsPhim[], int soLuongPhim) {
	if (soLuongPhim == 0) {
		cout << "\nDanh sach phim trong!\n";
		return;
	}

	cout << "\n-----DANH SACH PHIM-----\n";
	cout << left << setw(10) << "Ma phim"
		<< setw(30) << "Ten phim"
		<< setw(15) << "The loai"
		<< setw(12) << "Thoi luong" << endl;
	cout << string(87, '-') << endl;

	for (int i = 0; i < soLuongPhim; i++) {
		cout << left << setw(10) << dsPhim[i].maPhim
			<< setw(30) << dsPhim[i].tenPhim
			<< setw(15) << dsPhim[i].theLoai
			<< setw(12) << (to_string(dsPhim[i].thoiLuong) + " phut") << endl;
	}
}

//hàm tìm kiếm phim
void timKiemPhim(Phim dsPhim[], int soLuongPhim) {
	if (soLuongPhim == 0) {
		cout << "\nDanh sach phim trong!\n";
		return;
	}

	int luaChon;
	cout << "\n-----TIM KIEM PHIM-----\n";
	cout << "1. Tim theo ma phim\n";
	cout << "2. Tim theo ten phim\n";
	cout << "Lua chon cua ban: ";
	cin >> luaChon;
	cin.ignore();

	if (luaChon == 1) {
		//tìm theo mã
		string maTim;
		cout << "Nhap ma phim can tim: ";
		getline(cin, maTim);

		bool timThay = false;
		for (int i = 0; i < soLuongPhim; i++) {
			if (dsPhim[i].maPhim == maTim) {
				cout << "\n-----THONG TIN PHIM-----\n";
				cout << "Ma phim: " << dsPhim[i].maPhim << endl;
				cout << "Ten phim: " << dsPhim[i].tenPhim << endl;
				cout << "The loai: " << dsPhim[i].theLoai << endl;
				cout << "Thoi luong: " << dsPhim[i].thoiLuong << " phut" << endl;
				timThay = true;
				break;
			}
		}

		if (!timThay) {
			cout << "\nKhong tim thay phim co ma: " << maTim << endl;
		}
	}
	else if (luaChon == 2) {
		//tìm theo tên
		string tenTim;
		cout << "Nhap ten phim can tim: ";
		getline(cin, tenTim);
		//chuyển thành chữ thường
		for (int i = 0; i < tenTim.length(); i++) {
			tenTim[i] = tolower(tenTim[i]);
		}
		bool timThay = false;
		for (int i = 0; i < soLuongPhim; i++) {
			string tenPhim = dsPhim[i].tenPhim;
			for (int j = 0; j < tenPhim.length(); j++) {
				tenPhim[j] = tolower(tenPhim[j]);
			}
			if (tenPhim.find(tenTim) != string::npos) {
				cout << "\n-----THONG TIN PHIM-----\n";
				cout << "Ma phim: " << dsPhim[i].maPhim << endl;
				cout << "Ten phim: " << dsPhim[i].tenPhim << endl;
				cout << "The loai: " << dsPhim[i].theLoai << endl;
				cout << "Thoi luong: " << dsPhim[i].thoiLuong << " phut" << endl;
				cout << string(40, '-') << endl;
				timThay = true;
			}
		}

		if (!timThay) {
			cout << "\nKhong tim thay phim nao co ten: " << tenTim << endl;
		}
	}
	else {
		cout << "\nLua chon khong hop le!\n";
	}
}

//hàm quản lý phim
void quanLyPhim() {
	int chon;
	do {
		cout << "\n=====QUAN LY PHIM=====\n";
		cout << "1. Them phim moi\n";
		cout << "2. Xoa phim\n";
		cout << "3. Xem danh sach phim\n";
		cout << "4. Tim kiem phim\n";
		cout << "0. Quay lai\n";
		cout << "Lua chon cua ban: ";
		cin >> chon;

		switch (chon) {
		case 1:
			themPhim(danhSachPhim, soLuongPhim);
			break;
		case 2:
			xoaPhim(danhSachPhim, soLuongPhim);
			break;
		case 3:
			hienThiPhim(danhSachPhim, soLuongPhim);
			break;
		case 4:
			timKiemPhim(danhSachPhim, soLuongPhim);
			break;
		case 0:
			cout << "\nQuay lai menu chinh...\n";
			break;
		default:
			cout << "\nLua chon khong hop le!\n";
		}
	} while (chon != 0);
}

//hàm thêm suất chiếu
void themSuatChieu(SuatChieu dsSuat[], int& soLuongSuat, Phim dsPhim[], int soLuongPhim) {
	if (!kiemTraQuyen(1)) {
		return;
	}
	if (soLuongSuat >= MAX_SUATCHIEU) {
		cout << "\nDanh sach suat chieu da day!\n";
		return;
	}
	if(soLuongPhim == 0){
		cout << "\nVui long them phim truoc!\n";
		return;
	}
	SuatChieu suat;
	cin.ignore();
	cout << "\n----THEM SUAT CHIEU----\n";

	//hiển thị ds phim
	cout << "\n-----DANH SACH PHIM-----\n";
	for (int i = 0; i < soLuongPhim; i++) {
		cout << i + 1 << ". [" << dsPhim[i].maPhim << "] "
			<< dsPhim[i].tenPhim << " (" << dsPhim[i].thoiLuong << " phut)\n";
	}

	//chọn phim
	int chonPhim;
	cout << "\nChon phim (1-" << soLuongPhim << "): ";
	cin >> chonPhim;
	cin.ignore();

	if (chonPhim < 1 || chonPhim > soLuongPhim) {
		cout << "\nLua chon khong hop le!\n";
		return;
	}

	suat.maPhim = dsPhim[chonPhim - 1].maPhim;
	suat.tenPhim = dsPhim[chonPhim - 1].tenPhim;

	cout << "Nhap ma suat chieu (VD: SC01, SC02,...): ";
	getline(cin, suat.maSuat);

	cout << "Nhap ngay chieu (dd/mm/yyyy): ";
	getline(cin, suat.ngayChieu);

	cout << "Nhap gio chieu (hh:mm): ";
	getline(cin, suat.gioChieu);

	cout << "Nhap phong chieu (VD: P1, P2): ";
	getline(cin, suat.phongChieu);

	if (kiemTraTrungSuat(dsSuat, soLuongSuat, suat.ngayChieu, suat.gioChieu, suat.phongChieu)) {
		cout << "\n***CANH BAO: DA CO SUAT CHIEU TRUNG!***\n";
		cout << "Ngay: " << suat.ngayChieu << " - Gio: " << suat.gioChieu << endl;
		cout << "Phong: " << suat.phongChieu << endl;
		cout << "Ban co muon tiep tuc? (y/n): ";
		char xacNhan;
		cin >> xacNhan;
		if (xacNhan != 'y' && xacNhan != 'Y') {
			cout << "\nHuy them suat chieu.\n";
			return;
		}
	}

	cout << "Nhap so ghe trong: ";
	cin >> suat.soGheTrong;

	//khởi tạo tất cả ghế = false (trống)
	for (int i = 0; i < SO_HANG; i++) {
		for (int j = 0; j < SO_COT; j++) {
			suat.trangThaiGhe[i][j] = false;
		}
	}

	dsSuat[soLuongSuat] = suat;
	soLuongSuat++;

	cout << "\nTHEM SUAT CHIEU THANH CONG!\n";
	cout << "Ma suat: " << suat.maSuat << endl;
	cout << "Phim: " << suat.tenPhim << endl;
	cout << "Thoi gian: " << suat.ngayChieu << " - " << suat.gioChieu << endl;
	cout << "Phong: " << suat.phongChieu << endl;
	cout << "========================================\n";
}

//kiểm tra trùng suất chiêu
bool kiemTraTrungSuat(SuatChieu dsSuat[], int soLuongSuat, string ngay, string gio, string phong) {
	for (int i = 0;i < soLuongSuat;i++) {
		if (dsSuat[i].ngayChieu == ngay &&
			dsSuat[i].gioChieu == gio &&
			dsSuat[i].phongChieu == phong) {
			return true; //trùng
		}
	}
	return false;  //ko trùng
}

//xóa suất chiếu
void xoaSuatChieu(SuatChieu dsSuat[], int& soLuongSuat) {
	if (!kiemTraQuyen(1)) {
		return;
	}

	if (soLuongSuat == 0) {
		cout << "\nDanh sach suat chieu trong!\n";
		return;
	}

	string maXoa;
	cin.ignore();
	cout << "\nNhap ma suat chieu can xoa: ";
	getline(cin, maXoa);

	for (int i = 0; i < soLuongSuat; i++) {
		if (dsSuat[i].maSuat == maXoa) {
			cout << "\nBan co chac chan muon xoa suat chieu '"
				<< dsSuat[i].tenPhim << "' ngay " << dsSuat[i].ngayChieu
				<< " - " << dsSuat[i].gioChieu << "? (y/n): ";
			char xacNhan;
			cin >> xacNhan;

			if (xacNhan == 'y' || xacNhan == 'Y') {
				for (int j = i; j < soLuongSuat - 1; j++) {
					dsSuat[j] = dsSuat[j + 1];
				}
				soLuongSuat--;
				cout << "\nXoa suat chieu thanh cong!\n";
			}
			else {
				cout << "\nHuy xoa suat chieu.\n";
			}
			return;
		}
	}

	cout << "\nKhong tim thay suat chieu co ma: " << maXoa << endl;
}

//hiển thị danh sách suất chiếu
void hienThiSuatChieu(SuatChieu dsSuat[], int soLuongSuat) {
	if (soLuongSuat == 0) {
		cout << "\nDanh sach suat chieu trong!\n";
		return;
	}

	cout << "\n-----DANH SACH SUAT CHIEU-----\n";
	cout << left << setw(8) << "Ma suat"
		<< setw(30) << "Ten phim"
		<< setw(12) << "Ngay"
		<< setw(8) << "Gio"
		<< setw(8) << "Phong"
		<< setw(10) << "Ghe trong" << endl;
	cout << string(76, '-') << endl;

	for (int i = 0; i < soLuongSuat; i++) {
		cout << left << setw(8) << dsSuat[i].maSuat
			<< setw(30) << dsSuat[i].tenPhim
			<< setw(12) << dsSuat[i].ngayChieu
			<< setw(8) << dsSuat[i].gioChieu
			<< setw(8) << dsSuat[i].phongChieu
			<< setw(10) << dsSuat[i].soGheTrong << endl;
	}
}

//tìm kiếm suất chiếu
void timKiemSuatChieu(SuatChieu dsSuat[], int soLuongSuat) {
	if (soLuongSuat == 0) {
		cout << "\nDanh sach suat chieu trong!\n";
		return;
	}
	int luaChon;
	cout << "\n-----TIM KIEM SUAT CHIEU-----\n";
	cout << "1. Tim theo ma suat\n";
	cout << "2. Tim theo ten phim\n";
	cout << "Lua chon cua ban: ";
	cin >> luaChon;
	cin.ignore();

	if (luaChon == 1) {
		//tìm theo mã
		string maTim;
		cout << "Nhap ma suat chieu can tim: ";
		getline(cin, maTim);

		for (int i = 0; i < soLuongSuat; i++) {
			if (dsSuat[i].maSuat == maTim) {
				cout << "\n-----THONG TIN SUAT CHIEU-----\n";
				cout << "Ma suat: " << dsSuat[i].maSuat << endl;
				cout << "Phim: " << dsSuat[i].tenPhim << endl;
				cout << "Ngay chieu: " << dsSuat[i].ngayChieu << endl;
				cout << "Gio chieu: " << dsSuat[i].gioChieu << endl;
				cout << "Phong chieu: " << dsSuat[i].phongChieu << endl;
				cout << "So ghe trong: " << dsSuat[i].soGheTrong << endl;
				return;
			}
		}
		cout << "\nKhong tim thay suat chieu!\n";

	}
	else if (luaChon == 2) {
		//tìm theo tên phim
		string tenTim;
		cout << "Nhap ten phim can tim: ";
		getline(cin, tenTim);

		//chuyển thành chữ thường
		for (int i = 0; i < tenTim.length(); i++) {
			tenTim[i] = tolower(tenTim[i]);
		}

		bool timThay = false;
		cout << "\n-----KET QUA TIM KIEM-----\n";

		for (int i = 0; i < soLuongSuat; i++) {
			string tenPhim = dsSuat[i].tenPhim;
			for (int j = 0; j < tenPhim.length(); j++) {
				tenPhim[j] = tolower(tenPhim[j]);
			}

			if (tenPhim.find(tenTim) != string::npos) {
				cout << "\n[" << dsSuat[i].maSuat << "] "
					<< dsSuat[i].tenPhim << endl;
				cout << "  Ngay: " << dsSuat[i].ngayChieu
					<< " | Gio: " << dsSuat[i].gioChieu
					<< " | Phong: " << dsSuat[i].phongChieu << endl;
				timThay = true;
			}
		}

		if (!timThay) {
			cout << "\nKhong tim thay phim nao!\n";
		}

	}
	else {
		cout << "\nLua chon khong hop le!\n";
	}
}

//hàm quản lý suất chiếu
void quanLySuatChieu() {
	if (!kiemTraQuyen(1)) {
		return;
	}

	int chon;
	do {
		cout << "\n=====QUAN LY SUAT CHIEU=====\n";
		cout << "1. Them suat chieu\n";
		cout << "2. Xoa suat chieu\n";
		cout << "3. Xem danh sach suat chieu\n";
		cout << "4. Tim kiem suat chieu\n";
		cout << "0. Quay lai\n";
		cout << "Lua chon cua ban: ";
		cin >> chon;

		switch (chon) {
		case 1:
			themSuatChieu(danhSachSuatChieu, soLuongSuatChieu,
				danhSachPhim, soLuongPhim);
			break;
		case 2:
			xoaSuatChieu(danhSachSuatChieu, soLuongSuatChieu);
			break;
		case 3:
			hienThiSuatChieu(danhSachSuatChieu, soLuongSuatChieu);
			break;
		case 4:
			timKiemSuatChieu(danhSachSuatChieu, soLuongSuatChieu);
			break;
		case 0:
			cout << "\nQuay lai menu chinh...\n";
			break;
		default:
			cout << "\nLua chon khong hop le!\n";
		}
	} while (chon != 0);
}

//tạo mã vé tự động
string taoMaVeTuDong(int soLuongVe) {
	string maVe = "VE";
	int soThuTu = soLuongVe + 1;

	if (soThuTu < 10) {
		maVe += "000" + to_string(soThuTu);
	}
	else if (soThuTu < 100) {
		maVe += "00" + to_string(soThuTu);
	}
	else if (soThuTu < 1000) {
		maVe += "0" + to_string(soThuTu);
	}
	else {
		maVe += to_string(soThuTu);
	}
	return maVe;
}

//hiển thị sơ đồ ghế
void hienThiSoDoGhe(SuatChieu& suat) {
	cout << "\n***********SO DO GHE***********\n";
	cout << "          MAN HINH\n";
	cout << "*********************************\n\n";

	//header cột
	cout << "    ";
	for (int j = 1; j <= SO_COT; j++) {
		cout << setw(3) << j << " ";
	}
	cout << endl;

	//hiển thị từng hàng
	for (int i = 0; i < SO_HANG; i++) {
		char hang = 'A' + i;
		cout << " " << hang << "  ";

		for (int j = 0; j < SO_COT; j++) {
			if (suat.trangThaiGhe[i][j]) {
				cout << "[X] ";  //ghế đã đặt
			}
			else {
				cout << "[ ] ";  //ghế trống
			}
		}
		cout << endl;
	}

	cout << "\n===============================\n";
	cout << "[ ] = Ghe trong   [X] = Da dat\n";
	cout << "================================\n";
}

//in hóa đơn
void inHoaDon(Ve ve) {
	cout << "\n";
	cout << "════════════════════════════════════════\n";
	cout << "=          HOA DON DAT VE XEM PHIM     =\n";
	cout << "════════════════════════════════════════\n";
	cout << "Ma ve: " << ve.maVe << endl;
	cout << "========================================\n";
	cout << "Phim: " << ve.tenPhim << endl;
	cout << "Ngay chieu: " << ve.ngayChieu << endl;
	cout << "Gio chieu: " << ve.gioChieu << endl;
	cout << "Phong: " << ve.phongChieu << endl;
	cout << "----------------------------------------\n";
	cout << "Ghe: " << ve.danhSachGhe << endl;
	cout << "So luong: " << ve.soLuongGhe << " ghe\n";
	cout << "Don gia: " << GIA_VE << " VND/ghe\n";
	cout << "========================================\n";
	cout << "TONG TIEN: " << ve.tongTien << " VND\n";
	cout << "========================================\n";
	cout << "Thoi gian dat: " << ve.thoiGianDat << endl;
	cout << "========================================\n";
	cout << "     CAM ON QUY KHACH! HEN GAP LAI!\n";
	cout << "========================================\n\n";
}

//lưu vé ra file
void luuVeRaFile(Ve ve) {
	ofstream file("danhsach_ve.txt", ios::app);  //chế độ append

	if (!file.is_open()) {
		cout << "\nKhong the mo file de luu!\n";
		return;
	}

	file << "========================================\n";
	file << "Ma ve: " << ve.maVe << endl;
	file << "Phim: " << ve.tenPhim << endl;
	file << "Ngay: " << ve.ngayChieu << " - Gio: " << ve.gioChieu << endl;
	file << "Phong: " << ve.phongChieu << endl;
	file << "Ghe: " << ve.danhSachGhe << endl;
	file << "So luong: " << ve.soLuongGhe << " ghe\n";
	file << "Tong tien: " << ve.tongTien << " VND\n";
	file << "Thoi gian: " << ve.thoiGianDat << endl;
	file << "========================================\n\n";
	file.close();
}

//xem ds vé đã đặt
void xemDanhSachVe(Ve dsVe[], int soLuongVe) {
	if (soLuongVe == 0) {
		cout << "\nChua co ve nao duoc dat!\n";
		return;
	}

	cout << "\n----- DANH SACH VE DA DAT -----\n";
	cout << left << setw(10) << "Ma ve"
		<< setw(25) << "Phim"
		<< setw(12) << "Ngay"
		<< setw(8) << "Gio"
		<< setw(8) << "Phong"
		<< setw(15) << "Ghe"
		<< setw(12) << "Tong tien" << endl;
	cout << string(90, '-') << endl;

	for (int i = 0; i < soLuongVe; i++) {
		cout << left << setw(10) << dsVe[i].maVe
			<< setw(25) << dsVe[i].tenPhim
			<< setw(12) << dsVe[i].ngayChieu
			<< setw(8) << dsVe[i].gioChieu
			<< setw(8) << dsVe[i].phongChieu
			<< setw(15) << dsVe[i].danhSachGhe
			<< setw(12) << dsVe[i].tongTien << endl;
	}
}

//đặt vé
void datVe(SuatChieu dsSuat[], int soLuongSuat, Ve dsVe[], int& soLuongVe) {
	if (!kiemTraQuyen(2)) { 
		if (!kiemTraQuyen(1)) {
			return;
		}
	}

	if (soLuongSuat == 0) {
		cout << "\nChua co suat chieu nao!\n";
		return;
	}

	//hiển thị danh sách suất chiếu
	cout << "\n----- DANH SACH SUAT CHIEU -----\n";
	for (int i = 0; i < soLuongSuat; i++) {
		cout << i + 1 << ". [" << dsSuat[i].maSuat << "] "
			<< dsSuat[i].tenPhim << endl;
		cout << "   Ngay: " << dsSuat[i].ngayChieu
			<< " | Gio: " << dsSuat[i].gioChieu
			<< " | Phong: " << dsSuat[i].phongChieu
			<< " | Ghe trong: " << dsSuat[i].soGheTrong << endl;
	}

	//chọn suất chiếu
	int chonSuat;
	cout << "\nChon suat chieu (1-" << soLuongSuat << "): ";
	cin >> chonSuat;

	if (chonSuat < 1 || chonSuat > soLuongSuat) {
		cout << "\nLua chon khong hop le!\n";
		return;
	}

	SuatChieu& suatChon = dsSuat[chonSuat - 1];

	if (suatChon.soGheTrong <= 0) {
		cout << "\nSuat chieu da het cho!\n";
		return;
	}

	//hiển thị sơ đồ ghế
	hienThiSoDoGhe(suatChon);
	Ve ve;
	cin.ignore();
	//chọn ghế
	cout << "\n-----CHON GHE-----\n";
	cout << "Nhap so luong ghe muon dat: ";
	cin >> ve.soLuongGhe;

	if (ve.soLuongGhe > suatChon.soGheTrong) {
		cout << "\nKhong du ghe trong! (Chi con " << suatChon.soGheTrong << " ghe)\n";
		return;
	}
	//nhập từng ghế
	vector<string> danhSachGheDat;
	cin.ignore();

	for (int i = 0; i < ve.soLuongGhe; i++) {
		string ghe;
		cout << "Nhap ghe thu " << (i + 1) << " (VD: A1, B5): ";
		getline(cin, ghe);

		//kiểm tra định dạng ghế
		if (ghe.length() < 2) {
			cout << "Dinh dang ghe khong hop le!\n";
			i--;
			continue;
		}

		char hang = toupper(ghe[0]);
		int cot = 0;
		//chuyển cột thành số
		for (int j = 1; j < ghe.length(); j++) {
			if (ghe[j] >= '0' && ghe[j] <= '9') {
				cot = cot * 10 + (ghe[j] - '0');
			}
		}
		//kiểm tra hợp lệ
		if (hang < 'A' || hang >= 'A' + SO_HANG || cot < 1 || cot > SO_COT) {
			cout << "Ghe khong ton tai!\n";
			i--;
			continue;
		}
		int hangIdx = hang - 'A';
		int cotIdx = cot - 1;
		//kiểm tra ghế đã đặt chưa
		if (suatChon.trangThaiGhe[hangIdx][cotIdx]) {
			cout << "Ghe " << ghe << " da duoc dat! Vui long chon ghe khac.\n";
			i--;
			continue;
		}
		//đánh dấu ghế đã đặt
		suatChon.trangThaiGhe[hangIdx][cotIdx] = true;
		danhSachGheDat.push_back(ghe);
	}

	//giảm số ghế trống
	suatChon.soGheTrong -= ve.soLuongGhe;

	//tạo chuỗi danh sách ghế
	ve.danhSachGhe = "";
	for (int i = 0; i < danhSachGheDat.size(); i++) {
		ve.danhSachGhe += danhSachGheDat[i];
		if (i < danhSachGheDat.size() - 1) {
			ve.danhSachGhe += ", ";
		}
	}
	//tính tổng tiền
	ve.tongTien = ve.soLuongGhe * GIA_VE;

	//thông tin vé
	ve.maVe = taoMaVeTuDong(soLuongVe);
	ve.maSuat = suatChon.maSuat;
	ve.tenPhim = suatChon.tenPhim;
	ve.ngayChieu = suatChon.ngayChieu;
	ve.gioChieu = suatChon.gioChieu;
	ve.phongChieu = suatChon.phongChieu;
	ve.thoiGianDat = layThoiGianHienTai();

	//lưu vé
	dsVe[soLuongVe] = ve;
	soLuongVe++;

	//in hóa đơn
	inHoaDon(ve);

	//lưu ra file
	luuVeRaFile(ve);
	cout << "Da luu hoa don vao file 'danhsach_ve.txt'\n";
}

//hàm quản lý đặt vé
void quanLyDatVe() {
	if (!kiemTraQuyen(2)) {
		if (!kiemTraQuyen(1)) {
			return;
		}
	}

	int chon;
	do {
		cout << "\n=====QUAN LY DAT VE=====\n";
		cout << "1. Dat ve\n";
		cout << "2. Xem danh sach ve da dat\n";
		cout << "0. Quay lai\n";
		cout << "Lua chon cua ban: ";
		cin >> chon;

		switch (chon) {
		case 1:
			datVe(danhSachSuatChieu, soLuongSuatChieu, danhSachVe, soLuongVe);
			break;
		case 2:
			xemDanhSachVe(danhSachVe, soLuongVe);
			break;
		case 0:
			cout << "\nQuay lai menu chinh...\n";
			break;
		default:
			cout << "\nLua chon cua ban khong hop le!\n";
		} 
	} while (chon != 0);
}