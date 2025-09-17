#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

vector<unsigned int> GenerateRandomNumbers(int index)
{
    vector<unsigned int> numbers;
    int num = 0;

    while (numbers.size() < index)
    {
        num = rand() % 9 + 1;       // 1 ~ 9 사이의 숫자

        // 중복되는 숫자가 없도록 처리함.
        if (find(numbers.begin(), numbers.end(), num) == numbers.end())
        {
            numbers.push_back(num);
        }        
    }

    return numbers;
}

static pair<int, int> CalculateScore(const vector<unsigned int>& comNumber, const vector<unsigned int>& playerNumber)
{
    int strikes = 0, balls = 0;

    for (int i = 0; i < comNumber.size(); i++)
    {
        //cout << "플레이어가 고른 숫자 (" << i << ") = " << playerNumber[i] << endl;
        //cout << "컴퓨터가 고른 숫자 (" << i << ") = " << comNumber[i] << endl;

        // 플레이어가 숫자를 맞혔다면
        if (comNumber[i] == playerNumber[i])
        {
            strikes++;
        }
        // 플레이어가 입력한 숫자가 있긴 하지만, 위치가 다를 경우.
        else if (find(comNumber.begin(), comNumber.end(), playerNumber[i]) != comNumber.end())
        {
            balls++;
        }
    }

    return { strikes, balls };
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));    // 랜덤 시드
    int difficulty              = 0;              // 난이도
    bool isPlayerWin            = false;          // 게임 종료 유무
    int opertunity              = 10;              // 기회
    pair<int, int> strikesBalls = { 0, 0 };       // 스트라이크, 볼
    

    cout << "숫자 야구 게임에 오신 걸 환영합니다.\n\n";
    cout << "난이도를 선택해주세요. \n********************************\n1 = 쉬움 (숫자 3개)\n2 = 보통 (숫자 4개)\n3 = 어려움 (숫자 5개)\n********************************\n";
    cout << "난이도: "; cin >> difficulty;

    // difficulty 입력 예외 처리
    
    // -------------------------

    difficulty += 2;

    vector<unsigned int> comNumber = GenerateRandomNumbers(difficulty);      // 컴퓨터의 숫자 생성
    vector<unsigned int> playerNumber(difficulty);                           // 플레이어의 입력 숫자

    while (isPlayerWin == false && opertunity > 0)
    {
        cout << "남은 기회: " << opertunity << "번" << endl;
        if (opertunity == 1)
            cout << "마지막 기회입니다!\n" << endl;
        cout << difficulty << "개의 숫자를 입력해주세요." << endl;

        for (int i = 0; i < difficulty; i++)
        {
            try
            {
                cout << i + 1 << "번째 숫자 입력: "; cin >> playerNumber[i];

            }
            catch (string exeption)
            {
                cout << exeption << endl;
            }
        }

        strikesBalls = CalculateScore(comNumber, playerNumber);

        cout << strikesBalls.first << "스트라이크, " << strikesBalls.second << "볼\n" << endl;

        // 플레이어 승리 조건
        if (strikesBalls.first == difficulty)
        {
            isPlayerWin = true;

            cout << "플레이어의 승리입니다!" << endl;
        }
        else
        {
            opertunity--;
        }
    }

    string endText = isPlayerWin ? "승리" : "패배";
    cout << "\n\n게임이 종료되었습니다.\n당신의 결과: " << endText << endl;

    

    // while (endGame == false)
    // {
    // }

    return 0;
}