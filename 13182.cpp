#include <iostream>
#include <string>
#include "function.h"
using namespace std;

// Guest class implementation
Guest::Guest() : name(""), money(0), skill(0) {}
Guest::Guest(string s, int m, int ski) : name(s), money(m), skill(ski) {}
Guest::~Guest() {}
string Guest::get_name() { return name; }
int Guest::get_money() { return money; }
int Guest::get_skill() { return skill; }
void Guest::Win(int m) { money += m; }

// Casino class implementation
Casino::Casino() : fee(0), guest_num(0), income(0), list_num(0) {
    for (int i = 0; i < 1009; ++i) {
        guest[i] = nullptr;
        blacklist[i] = ""; //inget initialize blacklist juga
    }
}

Casino::~Casino() {
    for (int i = 0; i < guest_num; ++i) {
        if (guest[i] != nullptr) {
            delete guest[i];
            guest[i] = nullptr;
        }
    }
}

void Casino::Enterance(int f) {
    fee = f;
}

void Casino::GuestEnter(string s, int m, int ski) {
    for (int i = 0; i < guest_num; ++i) {
        if (guest[i] != nullptr && guest[i]->get_name() == s) {
            return;
        }
    }
    for (int i = 0; i < list_num; ++i) {
        if (blacklist[i] == s) {
            return;
        }
    }

    Guest* new_guest = new Guest(s, m, ski);

    int fee_to_pay = min(fee, new_guest->get_money());
    new_guest->Win(-fee_to_pay);
    income += fee_to_pay;

    if (new_guest->get_money() <= 0) {
        blacklist[list_num++] = s;
        delete new_guest;
        return;
    }

    guest[guest_num++] = new_guest; //inget masukkin guest ke guest list
}

void Casino::Win(string s, int m) {
    // Find guest in casino
    Guest* target = nullptr;
    int target_idx = -1;
    for (int i = 0; i < guest_num; ++i) {
        if (guest[i] != nullptr && guest[i]->get_name() == s) {
            target = guest[i];
            target_idx = i;
            break;
        }
    }
    if (target == nullptr) return; //Not inside the casino

    for (int i = 0; i < list_num; ++i) { //shouldn't happen since they can't enter
        if (blacklist[i] == s) {
            return;
        }
    }

    // Process win
    target->Win(m); //inget ini pake win
    income -= m;

    if (m > 2 * target->get_skill()) {
        blacklist[list_num++] = s;
        delete guest[target_idx];
        guest[target_idx] = nullptr;
        return;
    }

    if (target->get_money() <= 0) {
        income += target->get_money();
        blacklist[list_num++] = s;
        delete guest[target_idx];
        guest[target_idx] = nullptr;
    }
}

void Casino::EndDay() {
    //clear all kecuali blacklist karena nanti harus di print
    for (int i = 0; i < guest_num; ++i) {
        if (guest[i] != nullptr) {
            delete guest[i];
            guest[i] = nullptr;
        }
    }
    guest_num = 0; //inget set balik ke 0
}

void Casino::Result() {
    cout << income << endl;
    for (int i = 0; i < list_num; ++i) {
        cout << blacklist[i] << endl;
    }
}

//masukkin sampe ini

int n;
Casino casino = {};

int main() {
	cin >> n;
	for (int i = 0; i < n; ++ i) {
		string op;
		int q, fee;

		cin >> op >> q >> fee;
		casino.Enterance(fee);
		for (int j = 0; j < q; ++ j) {
			cin >> op;
			if (op == "Guest") {
				string name;
				int money, skill;
				cin >> name >> money >> skill;
				casino.GuestEnter(name, money, skill);
			}
			else if (op == "Win") {
				string name;
				int money;
				cin >> name >> money;
				casino.Win(name, money);
			}
		}
		casino.EndDay();
	}
	casino.Result();
}
