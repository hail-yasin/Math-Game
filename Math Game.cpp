#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

enum enQuestionsLevel { Easy = 1 , Med = 2 , Hard = 3 , Mix = 4};

enum enOperationType { Add = 1 , Sub = 2 , Mul = 3 , Div = 4 , Mix = 5};

enum enAnswerType { Right = 1 , Worng = 2};

struct stRoundInfo
{
	short HowManyRounds = 0;
	short QuestionsLevel = 0;
	int Number1 = 0;
	int Number2 = 0;
	short OperationType = 0;
	int PlayerAnswer = 0;
	int RightAnswer = 0;
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}


stRoundInfo ReadRoundInfo(stRoundInfo& RoundInfo)
{
	

	cout << "How Many Questions do you want to answer ? ";
	cin >> RoundInfo.HowManyRounds;
	cout << "\nEnter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
	cin >> RoundInfo.QuestionsLevel;
	cout << "\nEnter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div [5] Mix ? ";
	cin >> RoundInfo.OperationType;
	
	return RoundInfo;
}

stRoundInfo GenerateQuestionsByLeveL(stRoundInfo& RoundInfo)
{
	switch (RoundInfo.QuestionsLevel)
	{
	case enQuestionsLevel::Easy:
		RoundInfo.Number1 = RandomNumber(1, 10), RoundInfo.Number2 = RandomNumber(1, 10);
		break;
	case enQuestionsLevel::Med:
		RoundInfo.Number1 = RandomNumber(10, 50), RoundInfo.Number2 = RandomNumber(10, 50);
		break;
	case enQuestionsLevel::Hard:
		RoundInfo.Number1 = RandomNumber(50, 100), RoundInfo.Number2 = RandomNumber(50, 100);
		break;
	case enQuestionsLevel::Mix:
		RoundInfo.Number1 = RandomNumber(1, 100), RoundInfo.Number2 = RandomNumber(1, 100);
		break;

	}
	return RoundInfo;
}

stRoundInfo SelectOperation(stRoundInfo& RoundInfo)
{
	if (RoundInfo.OperationType == enOperationType::Mix)
		RoundInfo.OperationType = RandomNumber(1, 4);


	return RoundInfo;
}

stRoundInfo CalculateResult(stRoundInfo& RoundInfo)
{
	if (RoundInfo.OperationType == enOperationType::Add)
		RoundInfo.RightAnswer = RoundInfo.Number1 + RoundInfo.Number2;
	else if (RoundInfo.OperationType == enOperationType::Sub)
		RoundInfo.RightAnswer = RoundInfo.Number1 - RoundInfo.Number2;
	else if (RoundInfo.OperationType == enOperationType::Mul)
		RoundInfo.RightAnswer = RoundInfo.Number1 * RoundInfo.Number2;
	else if (RoundInfo.OperationType == enOperationType::Div)
		RoundInfo.RightAnswer = RoundInfo.Number1 / RoundInfo.Number2;

	return RoundInfo;
}

void InsideRound( short RoundNumber ,stRoundInfo& RoundInfo)
{
	cout << "Question [" << RoundNumber << "/" << RoundInfo.HowManyRounds << "]\n\n";
	cout << RoundInfo.Number1 << "\n";
	cout << RoundInfo.Number2 << " " << char(RoundInfo.OperationType) << "\n\n";
	cout << "---------\n";
	cin >> RoundInfo.PlayerAnswer;
}

void CheckPlayerAnswer(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerAnswer == RoundInfo.RightAnswer)
	{
		cout << "Right Answer :-) \n\n\n";
		system("color 2F");
		
	}
	else
	{
		cout << "Worng Answer :-(\n";
		cout << "The right answer is : " << RoundInfo.RightAnswer << "\n\n\n";
		system("color 4F");
		cout << '\a';
	}
}

void GamePlay()
{
	stRoundInfo RoundInfo;
	ReadRoundInfo(RoundInfo);
	


	for (short RoundNumber = 1; RoundNumber <= RoundInfo.HowManyRounds; RoundNumber++)
	{
		GenerateQuestionsByLeveL(RoundInfo);
		SelectOperation(RoundInfo);
		CalculateResult(RoundInfo);
		InsideRound(RoundNumber, RoundInfo);
		CheckPlayerAnswer(RoundInfo);

	}

}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		 GamePlay();
		 cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();

	return 0;
}
