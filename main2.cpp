#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm> 
#include <numeric>
#include <ctime>
#include <cctype>
using namespace std;
void setCard(vector<string>& card, string color) {

	vector<int> numbers1(13);
	iota(numbers1.begin(), numbers1.end(), 1);  // 1���� 13������ ���ڷ� ä��
	random_shuffle(numbers1.begin(), numbers1.end());  // ���ڸ� �������� ����

	vector<int> numbers2(13);
	iota(numbers2.begin(), numbers2.end(), 1);  // 1���� 13������ ���ڷ� ä��
	random_shuffle(numbers2.begin(), numbers2.end());  // ���ڸ� �������� ����

	for (int i = 0; i < 13; i++)
		card.insert(card.begin() + i, color + to_string(numbers1[i]));
	for (int i = 0; i < 13; i++)
		card.insert(card.begin() + i + 13, color + to_string(numbers2[i]));
	// ��ü ī�� �迭�� 1���� 13���� ī�带 ���
}

class card {
	string p_name;
	vector<string> p_card;
public:
	card() {}
	card(string p_name_in) { p_name = p_name_in; }
	void getCard(vector<vector<string>>& allCard); // ó�� ī�� ����ϴ� �Լ�
	int rollCard(vector<vector<string>>& paidCard_in); // ī�� ����ϴ� �Լ�
	void showCard(); // ī�� �����ִ� �Լ�
	void showCard(vector<vector<string>>& paidCard_in);  // �÷��̾ �� ī�带 �����ִ� �Լ�
	int sendCard(vector<vector<string>>& paidCard_in); // ��� �� ī�� ���� �Լ�
	void getAllCard(vector<vector<string>>& allCard);// ī�� �� �� �������� �Լ�
	int cardSize() { return p_card.size(); } // ���� ī�� ���� �����ִ� �Լ�
	string showName() { return p_name; } // �÷��̾� �̸� �����ִ� �Լ�
	~card() {}
};

void card::getCard(vector<vector<string>>& allCard) {
	p_card.clear(); //�÷��̾� ī�� �迭 �ʱ�ȭ

	srand((unsigned int)time(NULL)); //���� ����
	vector<string> v; //2���� ���Ϳ��� �������� ������ ���� ������ ���� ����

	if (!allCard.empty()) {
		for (int i = 0; i < 14; i++) {
			int randNum = rand() % allCard.size();
			v = allCard[randNum];

			if (!v.empty()) {
				p_card.push_back(v.back());
				allCard[randNum].pop_back();
			}
			else i--;
		}
	} //�÷��̾� ��ü�� ī�� ����ϴ� �Լ�
}
int card::rollCard(vector<vector<string>>& paidCard_in) {
	showCard();

	int num;
	cout << "�� ī�� ������ ������ ��������>>" << endl;
	cin >> num;
	cout << "������ ī�� ������ ���� ���� �� �� ������ 1�� ��������>> ";

	vector<string> comb(num);
	for (int i = 0; i < num; i++) {
		cin >> comb[i];
		if (comb[0] == "1") {
			return 1;
		} // ī�� ���� �ޱ�
	}
	vector<int> cardNum;
	for (const string& str : comb) {
		int cnum = 0;
		for (char ch : str) {
			// ���ڿ����� ���ڸ��� �����Ͽ� ������ ��ȯ
			if (isdigit(ch)) {
				cnum = cnum * 10 + (ch - '0');
			}
		}
		// ����� ���ڰ� ������ cardNum�� �߰�
		if (cnum != 0) {
			cardNum.push_back(cnum);
		}
	}
	int sum = 0;
	for (int k = 0; k < cardNum.size(); k++) {
		sum += cardNum[k]; // ���ڿ��� ����� ī�忡�� ���ڸ� ����
	}
	if (sum < 30) return 1; // ī�� ������ ���� 30 �̸��� ��� ��� �Ұ�

	for (int a = 0; a < num; a++) {
		for (int j = 0; j < p_card.size(); j++) {
			if (comb[a] == p_card[j])
				p_card.erase(p_card.begin() + j); //�÷��̾� ī�� �迭���� ����� �� ī�� ���� ����
		}
	}
	paidCard_in.push_back(comb); // ���� �÷��̾ �� ī�尡 ����� �迭�� ī�� ����
	
	return 0;
} // ī�� ����ϴ� �Լ�
void card::showCard() {
	int half = p_card.size() / 2;

	cout << "����� ���� ī�� ������ ������ �����ϴ�>> " << endl;
	for (int i = 0; i < p_card.size(); i++) {
		cout << " " << p_card[i] << " /";
		if (i == half)
			cout << "\n";
	}
	cout << "\n";
} // ī�� �����ִ� �Լ�
void card::showCard(vector<vector<string>>& paidCard_in) {
	int half = paidCard_in.size() / 2;

	cout << "���� �÷��̾ �� ī�� ������ ������ �����ϴ�>> " << endl;
	for (int i = 0; i < paidCard_in.size(); i++) {
		for (int j = 0; j < paidCard_in[i].size(); j++)
			cout << " " << paidCard_in[i][j] << " /";
		cout << "\n";
	}
	cout << "\n";
} // �÷��̾ �� ī�带 �����ִ� �Լ�

int card::sendCard(vector<vector<string>>& paidCard_in) {

	showCard();
	showCard(paidCard_in);

	int num;

	cout << "�� ī�� ������ ������ ��������>>" << endl;
	cin >> num;
	cout << "������ ī�忡�� ������ ī�� ������ ���� ���� �� �� ������ 1�� ��������>> ";

	vector<string> comb(num);
	for (int i = 0; i < num; i++) {
		cin >> comb[i];
		if (comb[0] == "1") {
			return 1;
		} // ī�� ���� �ޱ�
	}
	
	int num2;
	cout << "���� �÷��̾ �� ī�忡�� ���ϴ� ī�� ������ ������ ��������>>" << endl;
	cin >> num2;

	if (!num2) return 0;

	vector<string> comb2(num2);
	for (int j = 0; j < num2; j++) {
		cin >> comb2[j];
		 // ī�� ���� �ޱ�
	}
	for (int a = 0; a < num; a++) {
		for (int k = 0; k < p_card.size(); k++) {
			if (comb[a] == p_card[k])
				p_card.erase(p_card.begin() + k); //�÷��̾� ī�� �迭���� ����� �� ī�� ���� ����

		}
	}
	for (int x = 0; x < num; x++) {
		int y = 0;
		while (y < paidCard_in[x].size()) {
			if (comb[x] == paidCard_in[x][y]) {
				paidCard_in[x].erase(paidCard_in[x].begin() + y);
			}
			else {
				y++;
			}
		}
	}
	paidCard_in.push_back(comb); // ���� �÷��̾ �� ī�尡 ����� �迭�� ī�� ����
	paidCard_in.push_back(comb2); // ���� �÷��̾ �� ī�尡 ����� �迭�� ī�� ����

	return 0;
} // ��� �� ī�� ���� �Լ�
void card::getAllCard(vector<vector<string>>& allCard) {
	srand((unsigned int)time(NULL)); //���� ����
	vector<string> v;

	int randNum;
	do {
		randNum = rand() % allCard.size();
		v = allCard[randNum]; // ��ü ī�� �迭���� �������� �� ����
	} while (v.empty());

	p_card.push_back(v.back());
	allCard[randNum].pop_back();
} // ī�� �� �� �������� ��� �Լ�
int main() {
	vector<vector<string>> allCard(5, vector<string>(0, "")); //��ü ī�� �迭 ����

	setCard(allCard[0], "red");
	setCard(allCard[1], "black");
	setCard(allCard[2], "sky");
	setCard(allCard[3], "orange"); //���� ī�� �迭 �ʱ�ȭ

	allCard[4].clear(); //��Ŀ ī�� �迭 ũ�� 0���� ��ȯ
	allCard[4] = { "j_red", "j_black" }; //��Ŀ ī�� �迭 �ʱ�ȭ

	cout << "������ �����մϴ�." << endl;

	vector<string> playerNames;
	for (int i = 0; i < 4; i++) {
		string str;
		cout << "�̸��� �Է����ּ���" << endl;
		getline(cin, str);
		playerNames.push_back(str);
	} // �̸� �Է¹ޱ�

	card p1(playerNames[0]); // ��ü ����
	card p2(playerNames[1]); // ��ü ����
	card p3(playerNames[2]); // ��ü ����
	card p4(playerNames[3]); // ��ü ����

	string Name;
	card* ptr = NULL;
	vector<vector<string> > paidCard; // ���� �÷��̾ �� ī�� �迭 ����

	do {
		cout << "����� �̸���? >>";
		cin >> Name;
		if (Name == playerNames[0])
			ptr = &p1;
		else if (Name == playerNames[1])
			ptr = &p2;
		else if (Name == playerNames[2])
			ptr = &p3;
		else if (Name == playerNames[3])
			ptr = &p4;  // ������ �����ϴ� �÷��̾� ã��

		ptr->getCard(allCard); // �÷��̾�� ī�� ���
		int check; int isRoll = 0;

		cout << "����� ���ϸ� 0�� ���� �̹� �� ���¶�� 1�� ��������>>";
		cin >> check;

		if (!check)
			ptr->sendCard(paidCard);
		else {
			isRoll = ptr->rollCard(paidCard);
		}
		if (isRoll) {
			cout << "�� ī�尡 �����Ƿ� ���� ���ʷ� �Ѿ�ϴ�." << endl;
			ptr->getAllCard(allCard); //�� ī�� ������ �� �� ��������
		}
		cout << "���� �÷��̾��� �����Դϴ�." << endl;
	} while (ptr->cardSize() != 0);

	cout << ptr->showName() << "�÷��̾ �¸��Ͽ����ϴ�";

	return 0;
}