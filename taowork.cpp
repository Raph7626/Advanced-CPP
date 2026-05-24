#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

class TaiLieu{
	private:
		int MaTL;
		string TenTL;
		int SoTrang;
	public:
		TaiLieu() : MaTL(0), TenTL(""), SoTrang(0) {};
		TaiLieu(int ma, string ten, int trang) : MaTL(ma),TenTL(ten),SoTrang(trang){};
		
		int getMaTL() const {return MaTL;};
		void setMaTL(int ma) {MaTL = ma;};
		
		string getTenTL() const {return TenTL;};
		void setTenTL(string ten) {TenTL = ten;};
		
		int getSoTrang() const {return SoTrang;};
		void setSoTrang(int trang) {SoTrang = trang;};
		
		virtual void input() {
			cout<<"Ma: "; cin>>MaTL;
			cin.ignore();
			cout<<"Ten tl: "; getline(cin,TenTL);
			cout<<"So trang: "; cin>>SoTrang;
		}
		
		virtual void output(){
			cout<<"Ma: "<<MaTL<<endl;
			cout<<"Ten cua TL: "<<TenTL<<endl;
			cout<<"So trang cua TL: "<<SoTrang<<endl;
		}
		
		virtual float tinhPhi(){
			return SoTrang * 500;
		}
		
		friend bool operator==(const TaiLieu& tl1, const TaiLieu& tl2){
			return tl1.MaTL == tl2.MaTL;
		}	
};

class Sach : public TaiLieu{
	private:
		string TheLoai;
	public:
		Sach () : TheLoai(""), TaiLieu() {};
		Sach(int ma, string hoten, int trang, string loai) : TaiLieu(ma,hoten,trang), TheLoai(loai) {};
		
		string getTheLoai() const {return TheLoai;};
		void setTheLoai(string loai) {TheLoai = loai;	};
		
		void input() override{
			TaiLieu :: input();
			cin.ignore();
			cout<<"Nhap vao the loai: "; getline(cin,TheLoai);
		}
		
		void output() override{
			TaiLieu :: output();
			cout<<"The loai cua tai lieu: "<<TheLoai<<endl;
		}
		
		float tinhPhi() override{
		return getSoTrang() * 500 * 0.8;
		}
};

class TapChi : public TaiLieu{
	private:
		string ChuyenNganh;
	public:
		TapChi () : ChuyenNganh(""), TaiLieu() {};
		TapChi(int ma, string hoten, int trang, string nganh) : TaiLieu(ma,hoten,trang), ChuyenNganh(nganh) {};
		
		string getChuyenNganh() const {return ChuyenNganh;};
		void setTheLoai(string nganh) {ChuyenNganh = nganh;};
		
		void input() override{
			TaiLieu :: input();
			cin.ignore();
			cout<<"Nhap vao chuyen nganh: "; getline(cin,ChuyenNganh);
		}
		
		void output() override{
			TaiLieu :: output();
			cout<<"Chuyen Nganh cua tai lieu: "<<ChuyenNganh<<endl;
		}
		
		float tinhPhi() override{
		return getSoTrang() * 500 * 1.3;
		}
};

int main(){
	vector <TaiLieu*> DSTaiLieu;
	int n;
	cout<<"Nhap vao so tai lieu ban muon nhap: "; cin>>n;
	
	for (int i=0; i<n; i++){
		int loai;
		cout<<"Chon loai sach ban muon nhap(1-TL,2-S,3-TC): "; cin>>loai;
		
		TaiLieu *tl;
		if (loai == 1) tl = new TaiLieu;
		else if (loai == 2) tl = new Sach;
		else if (loai ==3 ) tl = new TapChi;
		else{
			cout<<"Khong hop le, vui long nhap lai!!"<<endl;
			i--;
			continue;
		}
		
		tl->input();
		DSTaiLieu.push_back(tl);
		
	}
	
	float tong=0;
	for (int i=0; i<DSTaiLieu.size(); i++){
		cout<<"THONG TIN VE TAI LIEU THU "<<i+1<<": "<<endl;
		TaiLieu *tl;
		tl = DSTaiLieu[i];
		
		tl->output();
		tong+=tl->tinhPhi();
		cout<<endl;
	}
	cout<<"TONG TAT CA TAI LIEU: "<<tong<<endl;
	
	if(!DSTaiLieu.empty()){
		TaiLieu *tlMax = DSTaiLieu [0];
		TaiLieu *tlMin = DSTaiLieu[0];
		for (int i =0; i<DSTaiLieu.size(); i++){
			TaiLieu *tl;
			tl = DSTaiLieu[i];
			
			if(tl->tinhPhi()>tlMax->tinhPhi()){
				tlMax = tl;
			}
			if(tl->tinhPhi()<tlMin->tinhPhi()){
				tlMin = tl;
			}
		}
		cout<<"Gia cao nhat: "<<tlMax->tinhPhi()<<endl;
		cout<<"Gia thap naht: "<<tlMin->tinhPhi()<<endl;
	}

	
	float tongTC=0;
	bool coTC = false;
	for (int i = 0; i<DSTaiLieu.size(); i++){
		TaiLieu *tl;
		tl = DSTaiLieu[i];
		
		if (typeid(*tl)==typeid(TapChi)){
			tongTC+=tl->tinhPhi();
			coTC = true;
		}
	}
	if(!coTC){
		cout<<"Khong co tap chi nao!";
		}
		else{ cout<<"Tong in an cua tap chi: "<<tongTC<<endl;
		}
	
	Sach sachMoi(999,"Sach ve may tinh",36,"Cong Nghe");
	bool trungMa = false;
	
	for (int i = 0; i<DSTaiLieu.size(); i++){
		TaiLieu *tl;
		tl = DSTaiLieu[i];
		
		if(*tl == sachMoi){
			cout<<"Sach co ma "<<tl->getMaTL()<<" trung voi sach moi!!";
			trungMa = true;
		}
	}
	if(!trungMa){
		cout<<"Sach hoan toan la sach moi";
	}
}
