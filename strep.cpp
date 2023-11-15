#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <algorithm>

using namespace std;

vector <string> file;
string f, newf, cnewf, nextf, nowf;
unsigned long long int line = 1, files = 1;

vector <string> d, dn, df, da, db, dfn, dlp, daf, dbf, dlpn, dlpf, dlpfn;
vector <long unsigned int> dl, dln, dah, dbh, dafh, dbfh;
bool dt = false;

vector <string> i0, i1, ia0, ia1, ib0, ib1, if0, if1, il1, iaf0, iaf1, ian0, ian1, ial1, ibf0, ibf1, ibp0, ibp1, ibl1, iln1, ilp0, ilp1, iafn0, iafn1, ialn1, iblp0, iblp1, ibln1, ibpn0, ibpn1, ibfn0, ibfn1, ibpf0, ibpf1, ilpn0, ilpn1, ilpf0, ilpf1, iblpf0, iblpf1, ibpfn0, ibpfn1, ilpfn0, ilpfn1, iblpfn0, iblpfn1; // options for -i[nsert]
vector <vector <long unsigned int>> il0, ial0, ibl0, iln0, ialn0, ibln0;

vector <string> c, cn, cb, cf, cfn, cbn, cbf, cph0, cbph0, cbnh0, cbfn, cpfh0;
vector <long unsigned int> cl, ch, cln, cbh, cph1, cph2, cbph1, cbph2, cbnh1, cbnh2, cpfh1, cpfh2;

vector <string> s, sb, sf, st0, sbt0, stf0, sbtf0;
vector <long unsigned int> st1, st2, sh, sbt1, sbt2, sfh, stf1, stf2, sbtf1, sbtf2;

vector <string> m, ml0, mp0, mp1, mbl0, mbp0, mbp1, mpf0, mpf1, mbpf0, mbpf1;
vector <long unsigned int> ml1, mbl1;
vector <bool> ml2, mp2, mpf2;
bool oom = false; // operate on merge

vector <string> r0, r1, rf0, rf1, rl1, rln1, rlp0, rlp1, rlpn0, rlpn1, rlpf0, rlpf1, rlpfn0, rlpfn1;
vector <vector <long unsigned int>> rl0, rln0;

bool pipe = false;
ifstream fs;
ofstream newfs;

inline void write(string& s) {
	if (f.size() > 0 and not pipe and newf.size() == 0) {
		newfs << s;
	} else if (newf.size() > 0 and pipe) {
		newfs << s;
		cout << s;
	} else if (newf.size() > 0) {
		newfs << s;
	} else {
		cout << s;
	}
}

inline void operate(string& str);

inline void merge() {
	for (long long int int1 = 0; int1 < m.size(); int1++) {
		ifstream ifs(m.at(int1));
		string str;
		if (oom) {
			while (getline(ifs, str)) {
				operate(str);
			}
		} else {
			while (getline(ifs, str)) {
				write(str);
			}
		}
	}
}

inline void merge(string& path) {
	for (long long int int1 = 0; int1 < m.size(); int1++) {
		ifstream ifs(path);
		string str;
		if (oom) {
			while (getline(ifs, str)) {
				operate(str);
			}
		} else {
			while (getline(ifs, str)) {
				write(str);
			}
		}
	}
}

inline void replace(string& sprstr, string substr, string repstr) {
	long long int pos = -1;
	pos = sprstr.find(substr);
	if (not (pos < 0)) {
		sprstr.erase(pos, substr.size());
		sprstr.insert(pos, repstr);
	}
}

inline void parse(vector <string>& argv, long long int& int1, vector <string>& sv) {
	while (true) {
		int1++;
		if (argv.at(int1).at(argv.at(int1).size() - 1) == ',') {
			argv.at(int1).pop_back();
			sv.push_back(argv.at(int1));
		} else {
			sv.push_back(argv.at(int1));
			break;
		}
	}
}

inline void parse(vector <string>& argv, long long int& int1, vector <long unsigned int>& iv) {
	while (true) {
		int1++;
		if (argv.at(int1).at(argv.at(int1).size() - 1) == ',' and argv.at(int1).find("-") >= 0) {
			replace(argv.at(int1), "-", " ");
			argv.at(int1).pop_back();
			stringstream explns;
			explns << argv.at(int1);
			long unsigned int int2, int3;
			explns >> int2 >> int3;
			if (int2 < int3) {
				for (long unsigned int int4 = int2; int4 <= int3; int4++) {
					iv.push_back(int4);
				}
			} else {
				for (long unsigned int int4 = int3; int4 <= int2; int4++) {
					iv.push_back(int4);
				}
			}
		} else if (argv.at(int1).at(argv.at(int1).size() - 1) != ',' and argv.at(int1).find("-") >= 0) {
			replace(argv.at(int1), "-", " ");
			stringstream explns;
			explns << argv.at(int1);
			long unsigned int int2, int3;
			explns >> int2 >> int3;
			if (int2 < int3) {
				for (long unsigned int int4 = int2; int4 <= int3; int4++) {
					iv.push_back(int4);
				}
			} else {
				for (long unsigned int int4 = int3; int4 <= int2; int4++) {
					iv.push_back(int4);
				}
			}
			break;
		} else if (argv.at(int1).at(argv.at(int1).size() - 1) == ',') {
			argv.at(int1).pop_back();
			iv.push_back(stoi(argv.at(int1)));
		}
		 else {
			iv.push_back(stoi(argv.at(int1)));
			break;
		}
	}
}

inline void parse(vector <string>& argv, long long int& int1, vector <string>& sv0, vector <string>& sv1) {
	while (true) {
		int1++;
		sv0.push_back(argv.at(int1));
		int1++;
		if (argv.at(int1).at(argv.at(int1).size() - 1) != ',') {
			sv1.push_back(argv.at(int1));
			break;
		} else {
			argv.at(int1).pop_back();
			sv1.push_back(argv.at(int1));
		}
	}
}

inline void parse(vector <string>& argv, long long int& int1, vector <string>& sv, vector <long unsigned int>& iv) {
	while (true) {
		int1++;
		sv.push_back(argv.at(int1));
		int1++;
		if (argv.at(int1).at(argv.at(int1).size() - 1) == ',' and argv.at(int1).find("-") >= 0) {
			replace(argv.at(int1), "-", " ");
			argv.at(int1).pop_back();
			stringstream explns;
			explns << argv.at(int1);
			long unsigned int int2, int3;
			explns >> int2 >> int3;
			if (int2 < int3) {
				for (long unsigned int int4 = int2; int4 <= int3; int4++) {
					iv.push_back(int4);
				}
			} else {
				for (long unsigned int int4 = int3; int4 <= int2; int4++) {
					iv.push_back(int4);
				}
			}
		} else if (argv.at(int1).at(argv.at(int1).size() - 1) != ',' and argv.at(int1).find("-") >= 0) {
			replace(argv.at(int1), "-", " ");
			stringstream explns;
			explns << argv.at(int1);
			long unsigned int int2, int3;
			explns >> int2 >> int3;
			if (int2 < int3) {
				for (long unsigned int int4 = int2; int4 <= int3; int4++) {
					iv.push_back(int4);
				}
			} else {
				for (long unsigned int int4 = int3; int4 <= int2; int4++) {
					iv.push_back(int4);
				}
			}
			break;
		} else if (argv.at(int1).at(argv.at(int1).size() - 1) == ',') {
			argv.at(int1).pop_back();
			iv.push_back(stoi(argv.at(int1)));
		} else {
			iv.push_back(stoi(argv.at(int1)));
			break;
		}
	}
}

inline void parse_nodash(vector <string>& argv, long long int& int1, vector <long unsigned int>& iv) {
	while (true) {
		int1++;
		iv.push_back(stoi(argv.at(int1)));
		int1++;
		if (argv.at(int1).at(argv.at(int1).size() - 1) != ',') {
			iv.push_back(stoi(argv.at(int1)));
			break;
		} else {
			argv.at(int1).pop_back();
			iv.push_back(stoi(argv.at(int1)));
		}
	}
}

inline void parse_nodash(vector <string>& argv, long long int& int1, vector <long unsigned int>& iv0, vector <long unsigned int>& iv1) {
	while (true) {
		int1++;
		iv0.push_back(stoi(argv.at(int1)));
		int1++;
		if (argv.at(int1).at(argv.at(int1).size() - 1) != ',') {
			iv1.push_back(stoi(argv.at(int1)));
			break;
		} else {
			argv.at(int1).pop_back();
			iv1.push_back(stoi(argv.at(int1)));
		}
	}
}

inline void parse(vector <string>& argv, long long int& int1, vector <vector <long unsigned int>>& ivv, vector <string>& sv) {
	while (true) {
		int1++;
		sv.push_back(argv.at(int1));
		int1++;
		if (argv.at(int1).at(argv.at(int1).size() - 1) == ',' and argv.at(int1).find("-") >= 0) {
			vector <long unsigned int> iv;
			replace(argv.at(int1), "-", " ");
			argv.at(int1).pop_back();
			stringstream explns;
			explns << argv.at(int1);
			long unsigned int int2, int3;
			explns >> int2 >> int3;
			if (int2 < int3) {
				for (long unsigned int int4 = int2; int4 <= int3; int4++) {
					iv.push_back(int4);
				}
				ivv.push_back(iv);
			} else {
				for (long unsigned int int4 = int3; int4 <= int2; int4++) {
					iv.push_back(int4);
				}
				ivv.push_back(iv);
			}
		} else if (argv.at(int1).at(argv.at(int1).size() - 1) != ',' and argv.at(int1).find("-") >= 0) {
			vector <long unsigned int> iv;
			replace(argv.at(int1), "-", " ");
			stringstream explns;
			explns << argv.at(int1);
			long unsigned int int2, int3;
			explns >> int2 >> int3;
			if (int2 < int3) {
				for (long unsigned int int4 = int2; int4 <= int3; int4++) {
					iv.push_back(int4);
				}
				ivv.push_back(iv);
			} else {
				for (long unsigned int int4 = int3; int4 <= int2; int4++) {
					iv.push_back(int4);
				}
				ivv.push_back(iv);
			}
			break;
		} else if (argv.at(int1).at(argv.at(int1).size() - 1) == ',') {
			vector <long unsigned int> iv;
			argv.at(int1).pop_back();
			iv.push_back(stoi(argv.at(int1)));
			ivv.push_back(iv);
		} else {
			vector <long unsigned int> iv;
			iv.push_back(stoi(argv.at(int1)));
			ivv.push_back(iv);
			break;
		}
	}
}

inline void parse_nodash(vector <string>& argv, long long int& int1, vector <string>& sv, vector <long unsigned int>& iv) {
	while (true) {
		int1++;
		sv.push_back(argv.at(int1));
		int1++;
		if (argv.at(int1).at(argv.at(int1).size() - 1) != ',') {
			iv.push_back(stoi(argv.at(int1)));
			break;
		} else {
			argv.at(int1).pop_back();
			iv.push_back(stoi(argv.at(int1)));
		}
	}
}

inline void operate(string& str) { // order of options is intentional, options that remove more should be higher up, options that add more should go lower down, and other options go where they make sense.
	vector <string> tomerge;
	if (c.size() > 0) {
		for (long long int int1 = 0; int1 < c.size(); int1++){
			long long int pos = -1;
			pos = str.find(c.at(int1));
			if (pos >= 0) {
				files++;
				nextf = cnewf + "-" + to_string(files);
			}
		}
	}
	if (cn.size() > 0) {
		for (long long int int1 = 0; int1 < cn.size(); int1++){
			long long int pos = -1;
			pos = str.find(cn.at(int1));
			if (pos == -1) {
				files++;
				nextf = cnewf + "-" + to_string(files);
			}
		}
	}
	if (cb.size() > 0) {
		for (long long int int1 = 0; int1 < cb.size(); int1++){
			long long int pos = -1;
			pos = str.find(cb.at(int1));
			if (pos >= 0) {
				files++;
				newf = cnewf + "-" + to_string(files);
			}
		}
	}
	if (cf.size() > 0) {
		for (long long int int1 = 0; int1 < cf.size(); int1++){
			long long int pos = -1;
			pos = str.find(cf.at(int1));
			if (pos >= 0) {
				files++;
				nextf = cnewf + "-" + to_string(files);
				auto it = cf.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				cf.erase(it);
				int1--;
			}
		}
	}
	if (cl.size() > 0) {
		for (long long int int1 = 0; int1 < cl.size(); int1++){
			if (line == cl.at(int1)) {
				files++;
				nextf = cnewf + "-" + to_string(files);
			}
		}
	}
	if (ch.size() > 0) {
		for (long long int int1 = 0; int1 < ch.size(); int1++){
			if (line % ch.at(int1) == 0 and line >= ch.at(int1)) {
				files++;
				nextf = cnewf + "-" + to_string(files);
			}
		}
	}
	if (cln.size() > 0) {
		for (long long int int1 = 0; int1 < cln.size(); int1++){
			if (line != cln.at(int1)) {
				files++;
				nextf = cnewf + "-" + to_string(files);
			}
		}
	}
	if (cfn.size() > 0) {
		for (long long int int1 = 0; int1 < cfn.size(); int1++){
			long long int pos = -1;
			pos = str.find(cfn.at(int1));
			if (pos == -1) {
				files++;
				nextf = cnewf + "-" + to_string(files);
				auto it = cfn.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				cfn.erase(it);
				int1--;
			}
		}
	}
	if (cbn.size() > 0) {
		for (long long int int1 = 0; int1 < cbn.size(); int1++){
			long long int pos = -1;
			pos = str.find(cbn.at(int1));
			if (pos == -1) {
				files++;
				newf = cnewf + "-" + to_string(files);
			}
		}
	}
	if (cbf.size() > 0) {
		for (long long int int1 = 0; int1 < cbf.size(); int1++){
			long long int pos = -1;
			pos = str.find(cbf.at(int1));
			if (pos >= 0) {
				files++;
				newf = cnewf + "-" + to_string(files);
				auto it = cbf.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				cbf.erase(it);
				int1--;
			}
		}
	}
	if (cbh.size() > 0) {
		for (long long int int1 = 0; int1 < cbh.size(); int1++){
			if (line % cbh.at(int1) == 0 and line >= cbh.at(int1)) {
				files++;
				newf = cnewf + "-" + to_string(files);
			}
		}
	}
	if (cph0.size() > 0) {
		if (cph2.size() < cph0.size()) {
			for (long long int int1 = 0; int1 < cph0.size(); int1++) {
				cph2.push_back(0);
			}
		}
		for (long long int int1 = 0; int1 < cph0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(cph0.at(int1));
			if (pos >= 0) {
				if (cph2.at(int1) % cph1.at(int1) == 0 and cph2.at(int1) != 0) {
					files++;
					nextf = cnewf + "-" + to_string(files);
				}
				cph2.at(int1)++;
			}
		}
	}
	if (cbph0.size() > 0) {
		if (cbph2.size() < cbph0.size()) {
			for (long long int int1 = 0; int1 < cbph0.size(); int1++) {
				cph2.push_back(0);
			}
		}
		for (long long int int1 = 0; int1 < cbph0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(cbph0.at(int1));
			if (pos >= 0) {
				if (cbph2.at(int1) % cbph1.at(int1) == 0 and cbph2.at(int1) != 0) {
					files++;
					newf = cnewf + "-" + to_string(files);
				}
				cbph2.at(int1)++;
			}
		}
	}
	if (cbnh0.size() > 0) {
		if (cbnh2.size() < cbnh0.size()) {
			for (long long int int1 = 0; int1 < cph0.size(); int1++) {
				cbnh2.push_back(0);
			}
		}
		for (long long int int1 = 0; int1 < cbnh0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(cbnh0.at(int1));
			if (pos == -1) {
				if (cbnh2.at(int1) % cbnh1.at(int1) == 0 and cbnh2.at(int1) != 0) {
					files++;
					newf = cnewf + "-" + to_string(files);
				}
				cbnh2.at(int1)++;
			}
		}
	}
	if (cbfn.size() > 0) {
		for (long long int int1 = 0; int1 < cbfn.size(); int1++){
			long long int pos = -1;
			pos = str.find(cbfn.at(int1));
			if (pos == -1) {
				files++;
				newf = cnewf + "-" + to_string(files);
				auto it = cbfn.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				cbfn.erase(it);
				int1--;
			}
		}
	}
	if (cpfh0.size() > 0) {
		if (cpfh2.size() < cpfh0.size()) {
			for (long long int int1 = 0; int1 < cpfh0.size(); int1++) {
				cpfh2.push_back(0);
			}
		}
		for (long long int int1 = 0; int1 < cpfh0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(cpfh0.at(int1));
			if (pos >= 0) {
				if (cpfh2.at(int1) % cpfh1.at(int1) == 0 and cpfh2.at(int1) != 0) {
					files++;
					nextf = cnewf + "-" + to_string(files);
					auto it = cpfh0.begin();
					for (long long int int2 = 0; int2 < int1; int2++) {it++;}
					cpfh0.erase(it);
					auto it1 = cpfh1.begin();
					for (long long int int2 = 0; int2 < int1; int2++) {it1++;}
					cpfh1.erase(it1);
					auto it2 = cpfh2.begin();
					for (long long int int2 = 0; int2 < int1; int2++) {it2++;}
					cpfh2.erase(it2);
					int1--;
				} else {
					cpfh2.at(int1)++;
				}
			}
		}
	}
	if (ml0.size() > 0) {
		for (long long int int1 = 0; int1 < ml1.size(); int1++) {
			if (line == ml1.at(int1)) {
				tomerge.push_back(ml0.at(int1));
			}
		}
	}
	if (mp0.size() > 0) {
		for (long long int int1 = 0; int1 < mp1.size(); int1++) {
			long long int pos = -1;
			pos = str.find(mp1.at(int1));
			if (pos >= 0) {
				tomerge.push_back(mp0.at(int1));
			}
		}
	}
	if (mpf0.size() > 0) {
		for (long long int int1 = 0; int1 < mpf1.size(); int1++) {
			long long int pos = -1;
			pos = str.find(mpf1.at(int1));
			if (pos >= 0) {
				tomerge.push_back(mpf0.at(int1));
				auto it = mpf0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				mpf0.erase(it);
				mpf1.erase(it);
				int1--;
			}
		}
	}
	if (mbl0.size() > 0) {
		for (long long int int1 = 0; int1 < mbl1.size(); int1++) {
			if (line == mbl1.at(int1)) {
				merge(mbl0.at(int1));
			}
		}
	}
	if (mbp0.size() > 0) {
		for (long long int int1 = 0; int1 < mbp1.size(); int1++) {
			long long int pos = -1;
			pos = str.find(mbp1.at(int1));
			if (pos >= 0) {
				merge(mbp0.at(int1));
			}
		}
	}
	if (mbpf0.size() > 0) {
		for (long long int int1 = 0; int1 < mbpf1.size(); int1++) {
			long long int pos = -1;
			pos = str.find(mbpf1.at(int1));
			if (pos >= 0) {
				merge(mbpf0.at(int1));
				auto it = mbpf0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				mbpf0.erase(it);
				mbpf1.erase(it);
				int1--;
			}
		}
	}
	if (dlpfn.size() > 0) {
		for (long long int int1 = 0; int1 < dlpfn.size(); int1++) {
			long long int pos = -1;
			pos = str.find(dlpfn.at(int1));
			if (pos >= 0) {
				str.clear();
				auto it = dlpfn.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				dlpfn.erase(it);
				int1--;
			}
		}
	}
	if (dlpn.size() > 0) {
		for (long long int int1 = 0; int1 < dlpn.size(); int1++) {
			long long int pos = -1;
			pos = str.find(dlpn.at(int1));
			if (pos == -1) {
				str.clear();
			}
		}
	}
	if (dln.size() > 0) {
		for (long long int int1 = 0; int1 < dln.size(); int1++) {
			if (line != dln.at(int1)) {
				str.clear();
			}
		}
	}
	if (dlp.size() > 0) {
		for (long long int int1 = 0; int1 < dlp.size(); int1++) {
			long long int pos = -1;
			pos = str.find(dlp.at(int1));
			if (pos >= 0) {
				str.clear();
			}
		}
	}
	if (dl.size() > 0) {
		for (long long int int1 = 0; int1 < dl.size(); int1++) {
			if (line == dl.at(int1)) {
				str.clear();
			}
		}
	}
	if (dlpf.size() > 0) {
		for (long long int int1 = 0; int1 < dlpf.size(); int1++) {
			long long int pos = -1;
			pos = str.find(dlpf.at(int1));
			if (pos >= 0) {
				str.clear();
				auto it = dlpf.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				dlpf.erase(it);
				int1--;
			}
		}
	}
	if (dn.size() > 0) {
		for (long long int int1 = 0; int1 < dn.size(); int1++) {
			long long int pos = 1;
			pos = -1;
			pos = str.find(dn.at(int1));
			if (pos >= 0) {
				str.erase(0, pos);
				str.erase(pos + dn.at(int1).size(), str.size() - 1);
			}
		}
	}
	if (dfn.size() > 0) {
		for (long long int int1 = 0; int1 < dfn.size(); int1++) {
			long long int pos = 1;
			pos = -1;
			pos = str.find(dfn.at(int1));
			if (pos >= 0) {
				str.erase(0, pos);
				str.erase(pos + dfn.at(int1).size(), str.size() - 1);
				auto it = dfn.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				dfn.erase(it);
				int1--;
			}
		}
	}
	if (da.size() > 0) {
		for (long long int int1 = 0; int1 < da.size(); int1++) {
			long long int pos = -1;
			pos = str.find(da.at(int1));
			if (pos >= 0 and str.at(str.size() - 1) == '\n') {
				str.erase(pos + da.at(int1).size());
				str += "\n";
			} else if (pos >= 0) {
				str.erase(pos + da.at(int1).size());
			}
		}
	}
	if (daf.size() > 0) {
		for (long long int int1 = 0; int1 < daf.size(); int1++) {
			long long int pos = -1;
			pos = str.find(daf.at(int1));
			if (pos >= 0 and str.at(str.size() - 1) == '\n') {
				str.erase(pos + daf.at(int1).size());
				str += "\n";
				auto it = daf.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				daf.erase(it);
				int1--;
			} else if (pos >= 0) {
				str.erase(pos + daf.at(int1).size());
				auto it = daf.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				daf.erase(it);
				int1--;
			}
		}
	}
	if (db.size() > 0) {
		for (long long int int1 = 0; int1 < db.size(); int1++) {
			long long int pos = -1;
			pos = str.find(db.at(int1));
			if (pos >= 0) {
				str.erase(0, pos);
			}
		}
	}
	if (dbf.size() > 0) {
		for (long long int int1 = 0; int1 < dbf.size(); int1++) {
			reverse(dbf.at(int1).begin(), dbf.at(int1).end());
			long long int pos = -1;
			pos = str.find(dbf.at(int1));
			if (pos >= 0) {
				str.erase(0, pos);
				auto it = dbf.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				dbf.erase(it);
				int1--;
			}
		}
	}
	if (dah.size() > 0) {
		for (long long int int1 = 0; int1 < dah.size(); int1++) {
			if (str.size() > dah.at(int1)) {
				str.erase(dah.at(int1) - 1);
			}
		}
	}
	if (dbh.size() > 0) {
		for (long long int int1 = 0; int1 < dbh.size(); int1++) {
			if (str.size() > dbh.at(int1)) {
				reverse(str.begin(), str.end());
				str.erase(dbh.at(int1) - 1);
				reverse(str.begin(), str.end());
			}
		}
	}
	if (dafh.size() > 0) {
		for (long long int int1 = 0; int1 < dafh.size(); int1++) {
			if (str.size() > dafh.at(int1)) {
				str.erase(dafh.at(int1) - 1);
				auto it = dafh.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				dafh.erase(it);
				int1--;
			}
		}
	}
	if (dbfh.size() > 0) {
		for (long long int int1 = 0; int1 < dbfh.size(); int1++) {
			if (str.size() > dbfh.at(int1)) {
				reverse(str.begin(), str.end());
				str.erase(dbfh.at(int1) - 1);
				reverse(str.begin(), str.end());
				auto it = dbfh.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				dbfh.erase(it);
				int1--;
			}
		}
	}
	if (d.size() > 0) {
		for (long long int int1 = 0; int1 < d.size(); int1++) {
			long long int pos = 1;
			while (pos >= 0) {
				pos = -1;
				pos = str.find(d.at(int1));
				if (pos >= 0) {
					str.erase(pos, d.at(int1).size());
				}
			}
		}
	}
	if (dt) {
		if (str.at(str.size() - 1) == '\n') {
			str.pop_back();
			while (str.at(str.size() - 1) == ' ' or str.at(str.size() - 1) == '	') {
				str.pop_back();
			}
			str += "\n";
		} else {
			while (str.at(str.size() - 1) == ' ' or str.at(str.size() - 1) == '	') {
				str.pop_back();
			}
		}
	}
	if (df.size() > 0) {
		for (long long int int1 = 0; int1 < df.size(); int1++) {
			long long int pos = -1;
			pos = str.find(df.at(int1));
			if (pos >= 0) {
				str.erase(pos, df.at(int1).size());
				auto it = df.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				df.erase(it);
				int1--;
			}
		}
	}
	if (r0.size() > 0) {
		for (long long int int1 = 0; int1 < r0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(r0.at(int1));
			while (pos >= 0) {
				replace(str, r0.at(int1), r1.at(int1));
				pos = -1;
				pos = str.find(r0.at(int1));
			}
		}
	}
	if (rf0.size() > 0) {
		for (long long int int1 = 0; int1 < rf0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(rf0.at(int1));
			while (pos >= 0) {
				replace(str, rf0.at(int1), rf1.at(int1));
				pos = -1;
				pos = str.find(rf0.at(int1));
				auto it = rf0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				rf0.erase(it);
				auto it1 = rf1.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it1++;}
				rf1.erase(it1);
				int1--;
			}
		}
	}
	if (rl0.size() > 0) {
		for (long long int int1 = 0; int1 < rl0.size(); int1++) {
			for (long long int int2 = 0; int2 < rl0.at(int1).size(); int2++) {
				if (rl0.at(int1).at(int2) == line) {
					str = rl1.at(int1);
				}
			}
		}
	}
	if (rln0.size() > 0) {
		for (long long int int1 = 0; int1 < rln0.size(); int1++) {
			for (long long int int2 = 0; int2 < rln0.at(int1).size(); int2++) {
				if (rln0.at(int1).at(int2) != line) {
					str = rln1.at(int1);
				}
			}
		}
	}
	if (rlp0.size() > 0) {
		for (long long int int1 = 0; int1 < rlp0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(rlp0.at(int1));
			if (pos >= 0) {
				str = rlp1.at(int1);
			}
		}
	}
	if (rlpn0.size() > 0) {
		for (long long int int1 = 0; int1 < rlpn0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(rlpn0.at(int1));
			if (pos < 0) {
				str = rlpn1.at(int1);
			}
		}
	}
	if (rlpf0.size() > 0) {
		for (long long int int1 = 0; int1 < rlpf0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(rlpf0.at(int1));
			if (pos >= 0) {
				str = rlpf1.at(int1);
				auto it = rlpf0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				rlpf0.erase(it);
				auto it1 = rlpf0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it1++;}
				rlpf1.erase(it1);
				int1--;
			}
		}
	}
	if (rlpfn0.size() > 0) {
		for (long long int int1 = 0; int1 < rlpfn0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(rlpfn0.at(int1));
			if (pos < 0) {
				str = rlpfn1.at(int1);
				auto it = rlpfn0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				rlpfn0.erase(it);
				auto it1 = rlpfn0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it1++;}
				rlpfn1.erase(it1);
				int1--;
			}
		}
	}
	if (s.size() > 0) {
		for (long long int int1 = 0; int1 < s.size(); int1++) {
			long long int pos = -1;
			pos = str.find(s.at(int1));
			if (pos >= 0) {
				str.insert(pos + s.at(int1).size(), "\n");
			}
		}
	}
	if (sb.size() > 0) {
		for (long long int int1 = 0; int1 < sb.size(); int1++) {
			long long int pos = -1;
			pos = str.find(sb.at(int1));
			while (pos >= 0) {
				str.insert(pos, "\n");
				pos = -1;
				pos = str.find(sb.at(int1));
			}
		}
	}
	if (sf.size() > 0) {
		for (long long int int1 = 0; int1 < sf.size(); int1++) {
			long long int pos = -1;
			pos = str.find(sf.at(int1));
			if (pos >= 0) {
				str.insert(pos + sf.at(int1).size(), "\n");
				auto it = sf.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				sf.erase(it);
				int1--;
			}
		}
	}
	if (st0.size() > 0) {
		if (st2.size() < st0.size()) {
			for (long long int int1 = 0; int1 < st0.size(); int1++) {
				st2.push_back(0);
			}
		}
		for (long long int int1 = 0; int1 < st0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(st0.at(int1));
			if (pos >= 0) {
				if (st2.at(int1) % st1.at(int1) == 0 and st2.at(int1) != 0) {
					str.insert(pos + st0.at(int1).size(), "\n");
				}
				st2.at(int1)++;
			}
		}
	}
	if (sh.size() > 0) {
		for (long long int int1 = 0; int1 < sh.size(); int1++) {
			if (str.size() > sh.at(int1)) {
				str.insert(sh.at(int1), "\n");
			}
		}
	}
	if (sbt0.size() > 0) {
		if (sbt2.size() < sbt0.size()) {
			for (long long int int1 = 0; int1 < sbt0.size(); int1++) {
				sbt2.push_back(0);
			}
		}
		for (long long int int1 = 0; int1 < sbt0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(sbt0.at(int1));
			if (pos >= 0) {
				if (sbt2.at(int1) % sbt1.at(int1) == 0 and sbt2.at(int1) != 0) {
					str.insert(pos, "\n");
				}
				sbt2.at(int1)++;
			}
		}
	}
	if (sfh.size() > 0) {
		for (long long int int1 = 0; int1 < sfh.size(); int1++) {
			if (str.size() > sfh.at(int1)) {
				str.insert(sfh.at(int1), "\n");
				auto it = sfh.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				sfh.erase(it);
				int1--;
			}
		}
	}
	if (stf0.size() > 0) {
		if (stf2.size() < stf0.size()) {
			for (long long int int1 = 0; int1 < stf0.size(); int1++) {
				stf2.push_back(0);
			}
		}
		for (long long int int1 = 0; int1 < stf0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(stf0.at(int1));
			if (pos >= 0) {
				if (stf2.at(int1) % stf1.at(int1) == 0 and stf2.at(int1) != 0) {
					str.insert(pos + stf0.at(int1).size(), "\n");
					auto it = stf0.begin();
					for (long long int int2 = 0; int2 < int1; int2++) {it++;}
					stf0.erase(it);
					auto it1 = stf1.begin();
					for (long long int int2 = 0; int2 < int1; int2++) {it1++;}
					stf1.erase(it1);
					auto it2 = stf2.begin();
					for (long long int int2 = 0; int2 < int1; int2++) {it2++;}
					stf2.erase(it2);
					int1--;
				} else {
					stf2.at(int1)++;
				}
			}
		}
	}
	if (sbtf0.size() > 0) {
		if (sbtf2.size() < sbtf0.size()) {
			for (long long int int1 = 0; int1 < sbtf0.size(); int1++) {
				sbtf2.push_back(0);
			}
		}
		for (long long int int1 = 0; int1 < sbtf0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(sbtf0.at(int1));
			if (pos >= 0) {
				if (sbtf2.at(int1) % sbtf1.at(int1) == 0 and sbtf2.at(int1) != 0) {
					str.insert(pos, "\n");
					auto it = sbtf0.begin();
					for (long long int int2 = 0; int2 < int1; int2++) {it++;}
					sbtf0.erase(it);
					auto it1 = sbtf1.begin();
					for (long long int int2 = 0; int2 < int1; int2++) {it1++;}
					sbtf1.erase(it1);
					auto it2 = sbtf2.begin();
					for (long long int int2 = 0; int2 < int1; int2++) {it2++;}
					sbtf2.erase(it2);
					int1--;
				} else {
					sbtf2.at(int1)++;
				}
			}
		}
	}
	if (i0.size() > 0) {
		for (long long int int1 = 0; int1 < i0.size(); int1++) {
			vector <long long int> pv;
			long long int pos = -1;
			pos = str.find(i0.at(int1));
			while (pos >= 0) {
				pv.push_back(pos);
				pos = -1;
				pos = str.find(i0.at(int1), pos + 1);
			}
			for (long long int int2 = 0; int2 < pv.size(); int2++) {
				str.insert(pv.at(int2) + i0.size(), i1.at(int1));
			}
		}
	}
	if (ia0.size() > 0) {
		for (long long int int1 = 0; int1 < ia0.size(); int1++) {
			long long int pos = 1;
			pos = -1;
			pos = str.find(ia0.at(int1));
			if (pos >= 0) {
				if (str.at(str.size() - 1) == '\n') {
					str.pop_back();
				}
				str.append(ia1.at(int1));
				str += "\n";
			}
		}
	}
	if (ib0.size() > 0) {
		for (long long int int1 = 0; int1 < ib0.size(); int1++) {
			vector <long long int> pv;
			long long int pos = -1;
			pos = str.find(ib0.at(int1));
			while (pos >= 0) {
				pv.push_back(pos);
				pos = -1;
				pos = str.find(ib0.at(int1), pos + 1);
			}
			for (long long int int2 = 0; int2 < pv.size(); int2++) {
				str.insert(pv.at(int2), i1.at(int1));
			}
		}
	}
	if (if0.size() > 0) {
		for (long long int int1 = 0; int1 < if0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(if0.at(int1));
			if (pos >= 0) {
				str.insert(pos + if0.at(int1).size(), if1.at(int1));
				auto it = if0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				if0.erase(it);
				if1.erase(it);
				int1--;
			}
		}
	}
	if (il0.size() > 0) {
		for (long long int int1 = 0; int1 < il0.size(); int1++) {
			for (long long int int2 = 0; int2 < il0.at(int1).size(); int2++) {
				if (line == il0.at(int1).at(int2)) {
					if (str.at(str.size() - 1) != '\n') {
						str.append("\n");
					}
					str.append(il1.at(int1));
					if (str.at(str.size() - 1) != '\n') {
						str.append("\n");
					}
				}
			}
		}
	}
	if (iaf0.size() > 0) {
		for (long long int int1 = 0; int1 < iaf0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(iaf0.at(int1));
			if (pos >= 0) {
				if (str.at(str.size() - 1) == '\n') {
					str.pop_back();
				}
				str.append(iaf1.at(int1));
				str += "\n";
				auto it = iaf0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				iaf0.erase(it);
				iaf1.erase(it);
				int1--;
			}
		}
	}
	if (ial0.size() > 0) {
		for (long long int int1 = 0; int1 < ial0.size(); int1++) {
			for (long long int int2 = 0; int2 < ial0.at(int1).size(); int2++) {
				if (line == ial0.at(int1).at(int2)) {
					if (str.at(str.size() - 1) == '\n') {
						str.pop_back();
					}
					str.append(ial1.at(int1));
					if (str.at(str.size() - 1) != '\n') {
						str += "\n";
					}
				}
			}
		}
	}
	if (ian0.size() > 0) {
		for (long long int int1 = 0; int1 < ian0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(ian0.at(int1));
			if (pos == -1) {
				if (str.at(str.size() - 1) == '\n') {
					str.pop_back();
				}
				str.append(iaf1.at(int1));
				if (str.at(str.size() - 1) != '\n') {
					str += "\n";
				}
			}
		}
	}
	if (ibf0.size() > 0) {
		for (long long int int1 = 0; int1 < ibf0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(ibf0.at(int1));
			if (pos >= 0) {
				str.insert(pos, ibf1.at(int1));
				auto it = ibf0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				ibf0.erase(it);
				ibf1.erase(it);
				int1--;
			}
		}
	}
	if (ibp0.size() > 0) {
		for (long long int int1 = 0; int1 < ibp0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(ibp0.at(int1));
			if (pos >= 0) {
				str.insert(0, ibp1.at(int1));
			}
		}
	}
	if (ibl0.size() > 0) {
		for (long long int int1 = 0; int1 < ibl0.size(); int1++) {
			for (long long int int2 = 0; int2 < ibl0.at(int1).size(); int2++) {
				if (line == ibl0.at(int1).at(int2)) {
					str.insert(0, ibl1.at(int1));
				}
			}
		}
	}
	if (iln0.size() > 0) {
		for (long long int int1 = 0; int1 < iln0.size(); int1++) {
			for (long long int int2 = 0; int2 < iln0.at(int1).size(); int2++) {
				if (line != iln0.at(int1).at(int2)) {
					if (str.at(str.size() - 1) != '\n') {
						str.append("\n");
					}
					str.append(iln1.at(int1));
				}
			}
		}
	}
	if (ilp0.size() > 0) {
		for (long long int int1 = 0; int1 < ilp0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(ilp0.at(int1));
			if (pos >= 0) {
				if (str.at(str.size() - 1) != '\n') {
					str.append("\n");
				}
				str.append(ilp1.at(int1));
			}
		}
	}
	if (iafn0.size() > 0) {
		for (long long int int1 = 0; int1 < iafn0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(iafn0.at(int1));
			if (pos == -1) {
				if (str.at(str.size() - 1) == '\n') {
					str.pop_back();
				}
				str.append(iafn1.at(int1));
				str += "\n";
				auto it = iafn0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				iafn0.erase(it);
				iafn1.erase(it);
				int1--;
			}
		}
	}
	if (ialn0.size() > 0) {
		for (long long int int1 = 0; int1 < ialn0.size(); int1++) {
			for (long long int int2 = 0; int2 < ialn0.at(int1).size(); int2++) {
				if (line != ialn0.at(int1).at(int2)) {
					if (str.at(str.size() - 1) == '\n') {
						str.pop_back();
					}
					str.append(ialn1.at(int1));
					str += "\n";
				}
			}
		}
	}
	if (iblp0.size() > 0) {
		for (long long int int1 = 0; int1 < iblp0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(iblp0.at(int1));
			if (pos >= 0) {
				str.insert(0, "\n");
				str.insert(0, iblp1.at(int1));
			}
		}
	}
	if (ibln0.size() > 0) {
		for (long long int int1 = 0; int1 < ibln0.size(); int1++) {
			for (long long int int2 = 0; int2 < ibln0.at(int1).size(); int2++) {
				if (line != ibln0.at(int1).at(int2)) {
					str.insert(0, ibln1.at(int1));
				}
			}
		}
	}
	if (ibpn0.size() > 0) {
		for (long long int int1 = 0; int1 < ibpn0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(ibpn0.at(int1));
			if (pos == -1) {
				str.insert(0, ibpn1.at(int1));
			}
		}
	}
	if (ibfn0.size() > 0) {
		for (long long int int1 = 0; int1 < ibfn0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(ibfn0.at(int1));
			if (pos == -1) {
				str.insert(0, ibfn1.at(int1));
				auto it = ibfn0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				ibfn0.erase(it);
				ibfn1.erase(it);
				int1--;
			}
		}
	}
	if (ibpf0.size() > 0) {
		for (long long int int1 = 0; int1 < ibpf0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(ibpf0.at(int1));
			if (pos >= 0) {
				str.insert(0, ibpf1.at(int1));
				auto it = ibpf0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				ibpf0.erase(it);
				ibpf1.erase(it);
				int1--;
			}
		}
	}
	if (ilpn0.size() > 0) {
		for (long long int int1 = 0; int1 < ilpn0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(ilpn0.at(int1));
			if (pos >= 0) {
				if (str.at(str.size() - 1) != '\n') {
					str += "\n";
				}
				str.append(ilpn1.at(int1));
				if (str.at(str.size() - 1) != '\n') {
					str += '\n';
				}
			}
		}
	}
	if (ilpf0.size() > 0) {
		for (long long int int1 = 0; int1 < ilpf0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(ilpf0.at(int1));
			if (pos >= 0) {
				if (str.at(str.size() - 1) != '\n') {
					str += '\n';
				}
				str.append(ilpf1.at(int1));
				auto it = ilpf0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				ilpf0.erase(it);
				ilpf1.erase(it);
				int1--;
			}
		}
	}
	if (iblpf0.size() > 0) {
		for (long long int int1 = 0; int1 < iblpf0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(iblpf0.at(int1));
			if (pos >= 0) {
				str.insert(0, "\n");
				str.insert(0, iblpf1.at(int1));
				auto it = iblpf0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				iblpf0.erase(it);
				iblpf1.erase(it);
				int1--;
			}
		}
	}
	if (ibpfn0.size() > 0) {
		for (long long int int1 = 0; int1 < ibpfn0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(ibpfn0.at(int1));
			if (pos == -1) {
				str.insert(0, ibpfn1.at(int1));
				auto it = ibpfn0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				ibpfn0.erase(it);
				ibpfn1.erase(it);
				int1--;
			}
		}
	}
	if (ilpfn0.size() > 0) {
		for (long long int int1 = 0; int1 < ilpfn0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(ilpfn0.at(int1));
			if (pos == -1) {
				if (str.at(str.size() -1) != '\n') {
					str.append("\n");
				}
				str.append(ilpfn1.at(int1));
				str.append("\n");
				auto it = ilpfn0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				ilpfn0.erase(it);
				ilpfn1.erase(it);
				int1--;
			}
		}
	}
	if (iblpfn0.size() > 0) {
		for (long long int int1 = 0; int1 < iblpfn0.size(); int1++) {
			long long int pos = -1;
			pos = str.find(iblpfn0.at(int1));
				if (pos == -1) {
				str.insert(0, "\n");
				str.insert(0, iblpfn1.at(int1));
				auto it = iblpfn0.begin();
				for (long long int int2 = 0; int2 < int1; int2++) {it++;}
				iblpfn0.erase(it);
				iblpfn1.erase(it);
				int1--;
			}
		}
	}

	if (not (newf.find(nowf) == 0 and newf.size() == nowf.size()) and newf.size() != 0) {
		newfs.close();
		newfs.open(newf);
		nowf = newf;
	}
	write(str);
	if (not (nextf.find(nowf) == 0 and nextf.size() == nowf.size()) and nextf.size() != 0) {
		newfs.close();
		newfs.open(nextf);
		newf = nextf;
		nowf = nextf;
	}
	for (int int1 = 0; int1 < tomerge.size(); int1++) {
		merge(tomerge.at(int1));
	}
	line++;
}

int main(int argc, char * arga[]) {

	{vector <string> argv;
	for (long long int int1 = 0; int1 < argc; int1++) {
		argv.push_back(arga[int1]);
	}

	for (long long int int1 = 1; int1 < argv.size(); int1++) {
		if (argv.at(int1).find("-d") == 0 and argv.at(int1).size() == 2) {parse(argv, int1, d);}
		else if (argv.at(int1).find("-df") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, df);}
		else if (argv.at(int1).find("-dn") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, dn);}
		else if (argv.at(int1).find("-dl") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, dl);}
		else if (argv.at(int1).find("-da") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, da);}
		else if (argv.at(int1).find("-db") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, db);}
		else if (argv.at(int1).find("-dt") == 0 and argv.at(int1).size() == 3) {dt = true;}
		else if (argv.at(int1).find("-dfn") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, dfn);}
		else if (argv.at(int1).find("-dln") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, dln);}
		else if (argv.at(int1).find("-dlp") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, dlp);}
		else if (argv.at(int1).find("-daf") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, daf);}
		else if (argv.at(int1).find("-da#") == 0 and argv.at(int1).size() == 4) {parse_nodash(argv, int1, dah);}
		else if (argv.at(int1).find("-dbf") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, dbf);}
		else if (argv.at(int1).find("-db#") == 0 and argv.at(int1).size() == 4) {parse_nodash(argv, int1, dbh);}
		else if (argv.at(int1).find("-dlpn") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, dlpn);}
		else if (argv.at(int1).find("-dlpf") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, dlpf);}
		else if (argv.at(int1).find("-daf#") == 0 and argv.at(int1).size() == 5) {parse_nodash(argv, int1, dafh);}
		else if (argv.at(int1).find("-dbf#") == 0 and argv.at(int1).size() == 5) {parse_nodash(argv, int1, dbfh);}
		else if (argv.at(int1).find("-dlpfn") == 0 and argv.at(int1).size() == 6) {parse(argv, int1, dlpfn);}
		else if (argv.at(int1).find("-i") == 0 and argv.at(int1).size() == 2) {parse(argv, int1, i0, i1);}
		else if (argv.at(int1).find("-ia") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, ia0, ia1);}
		else if (argv.at(int1).find("-ib") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, ib0, ib1);}
		else if (argv.at(int1).find("-if") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, if0, if1);}
		else if (argv.at(int1).find("-il") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, il0, il1);}
		else if (argv.at(int1).find("-iaf") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, iaf0, iaf1);}
		else if (argv.at(int1).find("-ial") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, ial0, ial1);}
		else if (argv.at(int1).find("-ian") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, ian0, ian1);}
		else if (argv.at(int1).find("-ibf") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, ibf0, ibf1);}
		else if (argv.at(int1).find("-ibp") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, ibp0, ibp1);}
		else if (argv.at(int1).find("-ibl") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, ibl0, ibl1);}
		else if (argv.at(int1).find("-iln") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, iln0, iln1);}
		else if (argv.at(int1).find("-iafn") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, iafn0, iafn1);}
		else if (argv.at(int1).find("-ialn") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, ialn0, ialn1);}
		else if (argv.at(int1).find("-iblp") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, iblp0, iblp1);}
		else if (argv.at(int1).find("-ibln") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, ibln0, ibln1);}
		else if (argv.at(int1).find("-ibpn") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, ibpn0, ibpn1);}
		else if (argv.at(int1).find("-ibfn") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, ibfn0, ibfn1);}
		else if (argv.at(int1).find("-ibpf") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, ibpf0, ibpf1);}
		else if (argv.at(int1).find("-ilpn") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, ilpn0, ilpn1);}
		else if (argv.at(int1).find("-ilpf") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, ilpf0, ilpf1);}
		else if (argv.at(int1).find("-iblpf") == 0 and argv.at(int1).size() == 6) {parse(argv, int1, iblpf0, iblpf1);}
		else if (argv.at(int1).find("-ibpfn") == 0 and argv.at(int1).size() == 6) {parse(argv, int1, ibpfn0, ibpfn1);}
		else if (argv.at(int1).find("-ilpfn") == 0 and argv.at(int1).size() == 6) {parse(argv, int1, ilpfn0, ilpfn1);}
		else if (argv.at(int1).find("-iblpfn") == 0 and argv.at(int1).size() == 7) {parse(argv, int1, iblpfn0, iblpfn1);}
		else if (argv.at(int1).find("-c") == 0 and argv.at(int1).size() == 2) {parse(argv, int1, c);}
		else if (argv.at(int1).find("-cn") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, cn);}
		else if (argv.at(int1).find("-cb") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, cb);}
		else if (argv.at(int1).find("-cf") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, cf);}
		else if (argv.at(int1).find("-cl") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, cl);}
		else if (argv.at(int1).find("-c#") == 0 and argv.at(int1).size() == 3) {parse_nodash(argv, int1, ch);}
		else if (argv.at(int1).find("-cln") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, cln);}
		else if (argv.at(int1).find("-cfn") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, cfn);}
		else if (argv.at(int1).find("-cbn") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, cbn);}
		else if (argv.at(int1).find("-cbf") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, cbf);}
		else if (argv.at(int1).find("-cb#") == 0 and argv.at(int1).size() == 4) {parse_nodash(argv, int1, cbh);}
		else if (argv.at(int1).find("-cp#") == 0 and argv.at(int1).size() == 4) {parse_nodash(argv, int1, cph0, cph1);}
		else if (argv.at(int1).find("-cbp#") == 0 and argv.at(int1).size() == 5) {parse_nodash(argv, int1, cbph0, cbph1);}
		else if (argv.at(int1).find("-cbn#") == 0 and argv.at(int1).size() == 5) {parse_nodash(argv, int1, cbnh0, cbnh1);}
		else if (argv.at(int1).find("-cbfn") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, cbfn);}
		else if (argv.at(int1).find("-cpf#") == 0 and argv.at(int1).size() == 5) {parse_nodash(argv, int1, cpfh0, cpfh1);}
		else if (argv.at(int1).find("-s") == 0 and argv.at(int1).size() == 2) {parse(argv, int1, s);}
		else if (argv.at(int1).find("-sb") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, sb);}
		else if (argv.at(int1).find("-sf") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, sf);}
		else if (argv.at(int1).find("-st") == 0 and argv.at(int1).size() == 3) {parse_nodash(argv, int1, st0, st1);}
		else if (argv.at(int1).find("-s#") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, sh);}
		else if (argv.at(int1).find("-sbt") == 0 and argv.at(int1).size() == 4) {parse_nodash(argv, int1, sbt0, sbt1);}
		else if (argv.at(int1).find("-sf#") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, sfh);}
		else if (argv.at(int1).find("-stf") == 0 and argv.at(int1).size() == 4) {parse_nodash(argv, int1, stf0, stf1);}
		else if (argv.at(int1).find("-sbtf") == 0 and argv.at(int1).size() == 5) {parse_nodash(argv, int1, sbtf0, sbtf1);}
		else if (argv.at(int1).find("-m") == 0 and argv.at(int1).size() == 2) {parse(argv, int1, m);}
		else if (argv.at(int1).find("-ml") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, ml0, ml1);}
		else if (argv.at(int1).find("-mp") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, mp0, mp1);}
		else if (argv.at(int1).find("-mbl") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, mbl0, mbl1);}
		else if (argv.at(int1).find("-mbp") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, mbp0, mbp1);}
		else if (argv.at(int1).find("-mpf") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, mpf0, mpf1);}
		else if (argv.at(int1).find("-mbpf") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, mbpf0, mbpf1);}
		else if (argv.at(int1).find("-r") == 0 and argv.at(int1).size() == 2) {parse(argv, int1, r0, r1);}
		else if (argv.at(int1).find("-rf") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, rf0, rf1);}
		else if (argv.at(int1).find("-rl") == 0 and argv.at(int1).size() == 3) {parse(argv, int1, rl0, rl1);}
		else if (argv.at(int1).find("-rln") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, rln0, rln1);}
		else if (argv.at(int1).find("-rlp") == 0 and argv.at(int1).size() == 4) {parse(argv, int1, rlp0, rlp1);}
		else if (argv.at(int1).find("-rlpn") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, rlpn0, rlpn1);}
		else if (argv.at(int1).find("-rlpf") == 0 and argv.at(int1).size() == 5) {parse(argv, int1, rlpf0, rlpf1);}
		else if (argv.at(int1).find("-rlpfn") == 0 and argv.at(int1).size() == 6) {parse(argv, int1, rlpfn0, rlpfn1);}
		else if (argv.at(int1).find("-f") == 0 and argv.at(int1).size() == 2) {
			f = argv.at(++int1);
		} else if (argv.at(int1).find("-o") == 0 and argv.at(int1).size() == 2) {
			newf = argv.at(++int1);
		} else if (argv.at(int1).find("-p") == 0 and argv.at(int1).size() == 2) {
			pipe = true;
		} else if (argv.at(int1).find("-oom") == 0 and argv.at(int1).size() == 4) {
			oom = true;
		} else if ((argv.at(int1).find("-h") == 0 and argv.at(int1).size() == 2) or (argv.at(int1).find("-help") == 0 and argv.at(int1).size() == 5) or (argv.at(int1).find("--help") == 0 and argv.at(int1).size() == 6)) {
			cout << "Options:\n\n-f[ile]\nFile to use as input, by default write back to file unless -p or -o\n<string>\n\n-p[ipe]\nOutput to STDOUT when used with -f\n(toggle)\n\n-o[utput]\nNew output file. Will always output.\n<string>\n\nInput is taken via STDIN by default.\n-f will cause the program to take input from the specified file, and output to it if -o or -p are not selected.\n-o will cause the program to output to the specified file.\n-p will cause the program to output to STDOUT.\n\nYou can specify multiple parameters by adding a comma at the end, for example \"replace this, and this\" or \"100, 150, 250\".\nWhen you can specify <int-int>, it means that all numbers including and between the numbers will be specified.\n(toggle) means that there is no parameter to be specified, as the option toggles something on by itself.\nLine count starts at 1, not 0.\nUnicode characters will count as more than one character if they are not in ascii, emojis, etc. Only applies to options that rely on character numbers.\nThe formatting like t[his] is not usable, it is only meant to explain the option to provide a greater understanding.\n\nThe options are not listed here in the order they are checked by the program. List of options in order available below.\n\n-d[elete]\nDelete patterns.\n<string>\n\n	f\n	Delete the first occurence of a pattern.\n	<string>\n\n	n\n	Delete everything on a line but a pattern from a line containing the pattern.\n	<string>\n\n	l\n	Delete lines by line numbers.\n	<int>/<int-int>\n\n	a\n	Delete all (truncate) after a pattern.\n	<string>\n\n	b\n	Delete all of a line up until a pattern.\n	<string>\n\n	t\n	Delete all trailing whitespace and tab characters.\n	(toggle)\n\n	fn\n	Delete everything on a line but a pattern from a line containing the pattern once.\n	<string>\n\n	ln\n	Delete every line not specified.\n	<int>/<int-int>\n\n	lp\n	Delete lines that contain a pattern.\n	<string>\n\n	af\n	Delete all (truncate) after a pattern once.\n	<string>\n\n	a#\n	Truncate after after a number of characters.\n	<int>\n\n	bf\n	Delete all of a line up until a pattern once.\n	<string>\n\n	b#\n	Delete after a number of characters from the beginning of the line.\n	<int>\n\n	lpn\n	Delete lines that don't contain a pattern.\n	<string>\n\n	lpf\n	Delete first line matching pattern\n	<string>\n\n	af#\n	Truncate after a certain number of characters once.\n	<int>\n\n	bf#\n	Delete after a number of characters from the beginning of a line once.\n	<int>\n\n	lpfn\n	Delete lines until a pattern occurs\n	<string>\n\n-i[nsert]\nInsert text after a pattern. First put the pattern, then the text.\n<string> <string>\n\n	a\n	Append something to a line that contains a pattern.\n	<string> <string>\n\n	b\n	Insert text before a pattern.\n	<string> <string>\n\n	f\n	Insert text after the first occurence of a pattern.\n	<string> <string>\n\n	l\n	Insert a line after specified line numbers.\n	<string> <int>/<int-int>\n\n	af\n	Append text to the first line that contains a pattern.\n	<string> <string>\n\n	al\n	Append text to specified lines.\n	<string> <int>/<int-int>\n\n	an\n	Append text to the end of every line that doesn't contain a pattern.\n	<string> <string>\n\n	bf\n	Insert text before the first occurence of a pattern.\n	<string> <string>\n\n	bp\n	Insert text at the start of a line that matches a pattern\n	<string> <string>\n\n	bl\n	Insert text at the beginning of specified lines.\n	<string> <int>/<int-int>\n\n	ln\n	Insert a line after every line not specified.\n	<string> <int>/<int-int>\n\n	lp\n	Insert a line after a line contains a pattern.\n	<string> <string>\n\n	afn\n	Append text to the first line not containing a pattern.\n	<string> <string>\n\n	aln\n	Append text to every line not specified.\n	<string> <int>/<int-int>\n\n	blp\n	Insert a line before a line containing a pattern.\n	<string> <string>\n\n	bln\n	Insert a line before every line not specified.\n	<string> <int>/<int-int>\n\n	bpn\n	Insert text at the start of a line that doesn't contain a pattern.\n	<string> <string>\n\n	bfn\n	Insert text at the start of a line that doesn't contain a pattern once.\n	<string> <string>\n\n	bpf\n	Insert text at the start of a line that contains a pattern once.\n	<string> <string>\n\n	lpn\n	Insert a line after a line that doesn't contain a pattern.\n	<string> <string>\n\n	lpf\n	Insert a line after the first occurence of a pattern in a line.\n	<string> <string>\n\n	blpf\n	Insert a line before a line containing a pattern once.\n	<string> <string>\n\n	bpfn\n	Insert text at the start of a line that doesn't contain a pattern once.\n	<string> <string>\n\n	lpfn\n	Insert a line after a line that doesn't contain a pattern once.\n	<string> <string>\n\n	blpfn\n	Insert a line before a line not containing a pattern once.\n	<string> <string>\n\n-c[ut]\nCut the file after a pattern. File names are formatted as <original name>-#, with the first being 1, & no 0 padding.\n<string>\n\n	n\n	Cut after lines that don't contain a pattern.\n	<string>\n\n	b\n	Cut before a line containing a pattern.\n	<string>\n\n	f\n	Cut after first occurence of a pattern.\n	<string>\n\n	l\n	Cut after lines by number.\n	<int>\n\n	#\n	Cut after every ### lines.\n	<int>\n\n	ln\n	Cut after every line not specified.\n	<int>\n\n	fn\n	Cut after the first line that doesn't contain a pattern.\n	<string>\n\n	bn\n	Cut before lines not containing a pattern.\n	<string>\n\n	bf\n	Cut before line where a pattern is found once.\n	<string>\n\n	b#\n	Cut before every ### lines.\n	<int>\n\n	p#\n	Cut after the number of times a pattern is found reaches a limit.\n	<string> <int>\n\n	bp#\n	Cut before the number of times a pattern is found reaches a limit.\n	<string> <int>\n\n	bn#\n	Cut before number of lines not containing a pattern reaches a limit.\n	<string> <int>\n\n	bfn\n	Cut before a line where a pattern is not found once.\n	<string>\n\n	pf#\n	Cut the after the number of times a pattern is found reaches a limit once.\n	<string> <int>\n\n-s[plit]\nSplit a line (insert newline) after a pattern.\n<string>\n\n	b\n	Split before a pattern.\n	<string>\n\n	f\n	Split after the first occurence of a pattern.\n	<string>\n\n	t\n	Split after total count of a pattern reaches a limit\n	<string> <int>\n\n	#\n	Split after a limit of characters on a line.\n	<int>\n\n	bt\n	Split before total count of a pattern reaches a limit.\n	<string> <int>\n\n	f#\n	Split after a limit of characters on a line once.\n	<int>\n\n	tf\n	Split the first time a total count of a pattern reaches a limit.\n	<string> <int>\n\n	btf\n	Split before a pattern reaches a limit once.\n	<string> <int>\n\n-m[erge]\nMerge multiple text files. Optionally operate on files being merged by specifying \"-oom\".\n<file>\n\n	l\n	Merge file after specified lines in the input.\n	<file> <int>\n\n	p\n	Insert a file after lines containing a pattern.\n	<file> <string>\n\n	pf\n	Insert a file after lines containing a pattern once.\n	<file> <string>\n\n	bl\n	Merge file before specified lines in the input.\n	<file> <int>\n\n	bp\n	Merge file before lines containing a pattern.\n	<file> <string>\n\n	bpf\n	Merge file before the first line containing a pattern.\n	<file> <string>\n\n-r[eplace]\nReplace patters with text. Substring first, the replacing pattern second.\n<string> <string>\n\n	f\n	Only replace the first occurence of a pattern.\n	<string> <string>\n\n	l\n	Replace lines with other lines.\n	<int>/<int-int> <string>\n\n	ln\n	Replace every line not specified with another line.\n	<int>/<int-int> <string>\n\n	lp\n	Replace lines containing a pattern with other lines.\n	<string> <string>\n\n	lpn\n	Replace lines not containing a pattern with other lines.\n	<string> <string>\n\n	lpf\n	Replace lines containing a pattern with other lines once.\n	<string> <string>\n\n	lpfn\n	Replace lines not containing a pattern with other lines once.\n	 <string> <string>\n\nList of options in order:\n\n-c\n-cn\n-cb\n-cf\n-cl\n-ch\n-cln\n-cfn\n-cbn\n-cbf\n-cbh\n-cph\n-cbph\n-cbnh\n-cbfn\n-cpfh\n-ml\n-mp\n-mpf\n-mbl\n-mbp\n-mbpf\n-dlpfn\n-dlpn\n-dln\n-dlp\n-dl\n-dlpf\n-dn\n-dfn\n-da\n-daf\n-db\n-dbf\n-dah\n-dbh\n-dafh\n-dbfh\n-d\n-df\n-r\n-rf\n-rl\n-rln\n-rlp\n-rlpn\n-rlpf\n-rlpfn\n-s\n-sb\n-sf\n-st\n-sh\n-sbt\n-sfh\n-stf\n-sbtf\n-i\n-ia\n-ib\n-if\n-il\n-iaf\n-ial\n-ian\n-ibf\n-ibp\n-ibl\n-iln\n-ilp\n-iafn\n-ialn\n-iblp\n-ibln\n-ibpn\n-ibfn\n-ibpf\n-ilpn\n-ilpf\n-iblpf\n-ibpfn\n-ilpfn\n-iblpfn\n";
			exit(0);
		} else {
			cerr << endl << "Unrecognized option:" << argv.at(int1) << endl;
			exit(2);
		}
	}
	} // delete argv

	if (c.size() > 0 or cn.size() > 0 or cb.size() > 0 or cf.size() > 0 or cfn.size() > 0 or cbn.size() > 0 or cbf.size() > 0 or cph0.size() > 0 or cbfn.size() > 0 or cpfh0.size() > 0 or cl.size() > 0 or ch.size() > 0 or cln.size() > 0 or cbh.size() > 0) {
		if (newf.size() > 0) {
			cnewf = newf;
			newf = cnewf + "-" + to_string(files);
		} else if (f.size() > 0 and not pipe) {
			cnewf = f;
			newf = cnewf + "-" + to_string(files);
		} else {
			cerr << "cut must be used with file output!" << endl;
			exit(1);
		}
	}

	if (f.size() > 0) {
		fs.open(f);
		if ((f.size() > 0 and not pipe and newf.size() == 0) and not (f.find(newf) == 0 and f.size() == newf.size())) {
			string str;
			while (getline(fs, str)) {
				file.push_back(str);
			}
			reverse(file.begin(), file.end());
			fs.close();
			newfs.open(f);
		}
	}
	if (newf.size() > 0) {
		newfs.open(newf);
	}

	if (f.size() == 0) {
		string str;
		while (getline(cin, str)) {
			str += "\n";
			operate(str);
		}
		merge();
		exit(0);
	} else if (file.size() > 0) {
		string str;
		while (file.size() > 0) {
			str = file.at(file.size() - 1);
			file.pop_back();
			str += "\n";
			operate(str);
		}
		merge();
		exit(0);
	} else {
		string str;
		while (getline(fs, str)) {
			str += "\n";
			operate(str);
		}
		merge();
		exit(0);
	}
}
