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
	iota(numbers1.begin(), numbers1.end(), 1);  // 1에서 13까지의 숫자로 채움
	random_shuffle(numbers1.begin(), numbers1.end());  // 숫자를 랜덤으로 섞음

	vector<int> numbers2(13);
	iota(numbers2.begin(), numbers2.end(), 1);  // 1에서 13까지의 숫자로 채움
	random_shuffle(numbers2.begin(), numbers2.end());  // 숫자를 랜덤으로 섞음

	for (int i = 0; i < 13; i++)
		card.insert(card.begin() + i, color + to_string(numbers1[i]));
	for (int i = 0; i < 13; i++)
		card.insert(card.begin() + i + 13, color + to_string(numbers2[i]));
	// 전체 카드 배열에 1부터 13까지 카드를 배분
}

class card {
	string p_name;
	vector<string> p_card;
public:
	card() {}
	card(string p_name_in) { p_name = p_name_in; }
	void getCard(vector<vector<string>>& allCard); // 처음 카드 배분하는 함수
	int rollCard(vector<vector<string>>& paidCard_in); // 카드 등록하는 함수
	void showCard(); // 카드 보여주는 함수
	void showCard(vector<vector<string>>& paidCard_in);  // 플레이어가 낸 카드를 보여주는 함수
	int sendCard(vector<vector<string>>& paidCard_in); // 등록 후 카드 내는 함수
	void getAllCard(vector<vector<string>>& allCard);// 카드 한 장 가져오는 함수
	int cardSize() { return p_card.size(); } // 남은 카드 개수 보여주는 함수
	string showName() { return p_name; } // 플레이어 이름 보여주는 함수
	~card() {}
};

void card::getCard(vector<vector<string>>& allCard) {
	p_card.clear(); //플레이어 카드 배열 초기화

	srand((unsigned int)time(NULL)); //난수 생성
	vector<string> v; //2차원 벡터에서 랜덤으로 선택한 행을 저장할 벡터 생성

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
	} //플레이어 객체에 카드 배분하는 함수
}
int card::rollCard(vector<vector<string>>& paidCard_in) {
	showCard();

	int num;
	cout << "낼 카드 조합의 개수를 적으세요>>" << endl;
	cin >> num;
	cout << "가능한 카드 조합을 적고 만약 낼 게 없으면 1을 적으세요>> ";

	vector<string> comb(num);
	for (int i = 0; i < num; i++) {
		cin >> comb[i];
		if (comb[0] == "1") {
			return 1;
		} // 카드 조합 받기
	}
	vector<int> cardNum;
	for (const string& str : comb) {
		int cnum = 0;
		for (char ch : str) {
			// 문자열에서 숫자만을 추출하여 정수로 변환
			if (isdigit(ch)) {
				cnum = cnum * 10 + (ch - '0');
			}
		}
		// 추출된 숫자가 있으면 cardNum에 추가
		if (cnum != 0) {
			cardNum.push_back(cnum);
		}
	}
	int sum = 0;
	for (int k = 0; k < cardNum.size(); k++) {
		sum += cardNum[k]; // 문자열로 저장된 카드에서 숫자만 추출
	}
	if (sum < 30) return 1; // 카드 숫자의 합이 30 미만일 경우 등록 불가

	for (int a = 0; a < num; a++) {
		for (int j = 0; j < p_card.size(); j++) {
			if (comb[a] == p_card[j])
				p_card.erase(p_card.begin() + j); //플레이어 카드 배열에서 내기로 한 카드 조합 삭제
		}
	}
	paidCard_in.push_back(comb); // 이전 플레이어가 낸 카드가 저장된 배열에 카드 내기
	
	return 0;
} // 카드 등록하는 함수
void card::showCard() {
	int half = p_card.size() / 2;

	cout << "당신이 가진 카드 조합은 다음과 같습니다>> " << endl;
	for (int i = 0; i < p_card.size(); i++) {
		cout << " " << p_card[i] << " /";
		if (i == half)
			cout << "\n";
	}
	cout << "\n";
} // 카드 보여주는 함수
void card::showCard(vector<vector<string>>& paidCard_in) {
	int half = paidCard_in.size() / 2;

	cout << "이전 플레이어가 낸 카드 조합은 다음과 같습니다>> " << endl;
	for (int i = 0; i < paidCard_in.size(); i++) {
		for (int j = 0; j < paidCard_in[i].size(); j++)
			cout << " " << paidCard_in[i][j] << " /";
		cout << "\n";
	}
	cout << "\n";
} // 플레이어가 낸 카드를 보여주는 함수

int card::sendCard(vector<vector<string>>& paidCard_in) {

	showCard();
	showCard(paidCard_in);

	int num;

	cout << "낼 카드 조합의 개수를 적으세요>>" << endl;
	cin >> num;
	cout << "본인의 카드에서 가능한 카드 조합을 적고 만약 낼 게 없으면 1을 적으세요>> ";

	vector<string> comb(num);
	for (int i = 0; i < num; i++) {
		cin >> comb[i];
		if (comb[0] == "1") {
			return 1;
		} // 카드 조합 받기
	}
	
	int num2;
	cout << "이전 플레이어가 낸 카드에서 원하는 카드 조합의 개수를 적으세요>>" << endl;
	cin >> num2;

	if (!num2) return 0;

	vector<string> comb2(num2);
	for (int j = 0; j < num2; j++) {
		cin >> comb2[j];
		 // 카드 조합 받기
	}
	for (int a = 0; a < num; a++) {
		for (int k = 0; k < p_card.size(); k++) {
			if (comb[a] == p_card[k])
				p_card.erase(p_card.begin() + k); //플레이어 카드 배열에서 내기로 한 카드 조합 삭제

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
	paidCard_in.push_back(comb); // 이전 플레이어가 낸 카드가 저장된 배열에 카드 내기
	paidCard_in.push_back(comb2); // 이전 플레이어가 낸 카드가 저장된 배열에 카드 내기

	return 0;
} // 등록 후 카드 내는 함수
void card::getAllCard(vector<vector<string>>& allCard) {
	srand((unsigned int)time(NULL)); //난수 생성
	vector<string> v;

	int randNum;
	do {
		randNum = rand() % allCard.size();
		v = allCard[randNum]; // 전체 카드 배열에서 랜덤으로 행 선택
	} while (v.empty());

	p_card.push_back(v.back());
	allCard[randNum].pop_back();
} // 카드 한 장 가져오는 멤버 함수
int main() {
	vector<vector<string>> allCard(5, vector<string>(0, "")); //전체 카드 배열 생성

	setCard(allCard[0], "red");
	setCard(allCard[1], "black");
	setCard(allCard[2], "sky");
	setCard(allCard[3], "orange"); //숫자 카드 배열 초기화

	allCard[4].clear(); //조커 카드 배열 크기 0으로 변환
	allCard[4] = { "j_red", "j_black" }; //조커 카드 배열 초기화

	cout << "게임을 시작합니다." << endl;

	vector<string> playerNames;
	for (int i = 0; i < 4; i++) {
		string str;
		cout << "이름을 입력해주세요" << endl;
		getline(cin, str);
		playerNames.push_back(str);
	} // 이름 입력받기

	card p1(playerNames[0]); // 객체 생성
	card p2(playerNames[1]); // 객체 생성
	card p3(playerNames[2]); // 객체 생성
	card p4(playerNames[3]); // 객체 생성

	string Name;
	card* ptr = NULL;
	vector<vector<string> > paidCard; // 이전 플레이어가 낸 카드 배열 생성

	do {
		cout << "당신의 이름은? >>";
		cin >> Name;
		if (Name == playerNames[0])
			ptr = &p1;
		else if (Name == playerNames[1])
			ptr = &p2;
		else if (Name == playerNames[2])
			ptr = &p3;
		else if (Name == playerNames[3])
			ptr = &p4;  // 게임을 진행하는 플레이어 찾기

		ptr->getCard(allCard); // 플레이어에게 카드 배분
		int check; int isRoll = 0;

		cout << "등록을 원하면 0을 적고 이미 한 상태라면 1을 적으세요>>";
		cin >> check;

		if (!check)
			ptr->sendCard(paidCard);
		else {
			isRoll = ptr->rollCard(paidCard);
		}
		if (isRoll) {
			cout << "낼 카드가 없으므로 다음 차례로 넘어갑니다." << endl;
			ptr->getAllCard(allCard); //낼 카드 없으면 한 장 가져오기
		}
		cout << "다음 플레이어의 차례입니다." << endl;
	} while (ptr->cardSize() != 0);

	cout << ptr->showName() << "플레이어가 승리하였습니다";

	return 0;
}