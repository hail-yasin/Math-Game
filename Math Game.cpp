#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

enum enQuestionsLevel { Easy = 1 , Med = 2 , Hard = 3 , Mix = 4};

enum enOperationType { Add = 1 , Sub = 2 , Mul = 3 , Div = 4 , MixOP = 5};

struct stRoundInfo
{
	short HowManyRounds = 0;
	short QuestionsLevel = 0;
	int Number1 = 0;
	int Number2 = 0;
	short OperationType;
	char Operation;
	int PlayerAnswer = 0;
	double RightAnswer = 0;
};
struct stGameInfo
{
	short NumberOfQuestion = 0;
	string QuestionLevel = "";
	string OperationType = "";
	short NumberOfRight = 0;
	short NumberOfWrong = 0;
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
	cout << "\n\n\n";
	
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

char SelectOperation(stRoundInfo& RoundInfo)
{
	short CurrentOperation = RoundInfo.OperationType;

	if (CurrentOperation == enOperationType::MixOP)
		CurrentOperation = RandomNumber(1, 4);

	switch (CurrentOperation)
	{
	case enOperationType::Add:
		return '+';
	case enOperationType::Sub:
		return '-';
	case enOperationType::Mul:
		return '*';
	case enOperationType::Div:
		return '/';
	}
}

stRoundInfo CalculateResult(stRoundInfo& RoundInfo)
{
	if (RoundInfo.Operation == '+')
		RoundInfo.RightAnswer = RoundInfo.Number1 + RoundInfo.Number2;
	else if (RoundInfo.Operation == '-')
		RoundInfo.RightAnswer = RoundInfo.Number1 - RoundInfo.Number2;
	else if (RoundInfo.Operation == '*')
		RoundInfo.RightAnswer = RoundInfo.Number1 * RoundInfo.Number2;
	else if (RoundInfo.Operation == '/')
		RoundInfo.RightAnswer = RoundInfo.Number1 / RoundInfo.Number2;

	return RoundInfo;
}

void InsideRound( short RoundNumber ,stRoundInfo& RoundInfo)
{
	cout << "Question [" << RoundNumber << "/" << RoundInfo.HowManyRounds << "]\n\n";
	cout << RoundInfo.Number1 << "\n";
	cout <<  RoundInfo.Number2 << " " << RoundInfo.Operation << "\n\n";
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
		cout << "Wrong Answer :-(\n";
		cout << "The right answer is : " << RoundInfo.RightAnswer << "\n\n\n";
		system("color 4F");
		cout << '\a';
	}
}

string CheckLevelName(stRoundInfo RoundInfo)
{
	string LevelName[4] = { "Easy" , "Med" , "Hard" , "Mix" };
	return LevelName[RoundInfo.QuestionsLevel - 1];
}

string CheckOpTypeName(stRoundInfo RoundInfo)
{
	string OpTypeName[5] = { "+" , "-" , "*" , "/" , "Mix" };
	return OpTypeName[RoundInfo.OperationType - 1];
}

void PrintGameOver(short NumberOfRightAnswers, short NumberOfWrongAnswers)
{
	cout << "--------------------------\n\n";
	if (NumberOfRightAnswers > NumberOfWrongAnswers)
	{
		cout << "Final Result is Pass :-) \n\n";
	}
	else
	{
		cout << "Final Result is Fail :-(\n\n";
	}
	cout << "--------------------------\n\n";
}

void PrintFinalResult(stGameInfo GameInfo)
{
	cout << "Number of Questions: " << GameInfo.NumberOfQuestion;
	cout << "\nQuestions Level    : " << GameInfo.QuestionLevel;
	cout << "\nOpType             : " << GameInfo.OperationType;
	cout << "\nNumber of Right Answers: " << GameInfo.NumberOfRight;
	cout << "\nNumber of Wrong Answers: " << GameInfo.NumberOfWrong;
	cout << "\n\n--------------------------\n\n";
}

void GamePlay()
{
	stRoundInfo RoundInfo;
	stGameInfo GameInfo;
	ReadRoundInfo(RoundInfo);
	short NumberOfRightAnswers = 0, NumberOfWrongAnswers = 0;
	


	for (short RoundNumber = 1; RoundNumber <= RoundInfo.HowManyRounds; RoundNumber++)
	{
		GenerateQuestionsByLeveL(RoundInfo);
		RoundInfo.Operation = SelectOperation(RoundInfo);
		CalculateResult(RoundInfo);
		InsideRound(RoundNumber, RoundInfo);
		CheckPlayerAnswer(RoundInfo);
		if (RoundInfo.RightAnswer == RoundInfo.PlayerAnswer)
			NumberOfRightAnswers++;
		else
			NumberOfWrongAnswers++;

	}
	
	GameInfo.NumberOfQuestion = RoundInfo.HowManyRounds;
	GameInfo.QuestionLevel = CheckLevelName(RoundInfo);
	GameInfo.OperationType = CheckOpTypeName(RoundInfo);
	GameInfo.NumberOfRight = NumberOfRightAnswers;
	GameInfo.NumberOfWrong = NumberOfWrongAnswers;

	PrintGameOver(NumberOfRightAnswers,NumberOfWrongAnswers);
	PrintFinalResult(GameInfo);

}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		system("cls");
		system("color 0F");
		 GamePlay();
		 cout << "Do you want play again ? Y/N \n";
		 cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();

	return 0;
}
