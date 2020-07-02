#include "DrawingTool.h"
#include <fstream>
#include <time.h>


DrawingTool::DrawingTool()
{
	setImmediateDrawMode(false);
	srand((int)time(0));
}


DrawingTool::~DrawingTool()
{
}
void DrawingTool::onDraw()
{
	clearScreen(WHITE);
	setTextColour(BLACK);
	setFont(20, L"Segoe UI");
	drawText("GIVE THE CORRECT CHANGE", 4, 5);
	setBackColour(GREEN);
	drawRectangle(650, 150, 70, 50, true);
	drawRectangle(650, 225, 70, 50, true);
	setFont(10, L"Segoe UI");
	drawText("START", 670, 170);
	drawText("CLEAR", 670, 250);
	drawBitmap(L"assets\\onepence.bmp", 0, 400, 50, 50);
	drawBitmap(L"assets\\2pence.bmp", 50, 400, 50, 50);
	drawBitmap(L"assets\\5pence.bmp", 100, 400, 50, 50);
	drawBitmap(L"assets\\10pence.bmp", 150, 400, 50, 50);
	drawBitmap(L"assets\\20pence.bmp", 200, 400, 50, 50);
	drawBitmap(L"assets\\50pence.bmp", 250, 400, 50, 50);
	drawBitmap(L"assets\\pound.bmp", 300, 400, 50, 50);
	drawBitmap(L"assets\\2pound.bmp", 350, 400, 50, 50);
	drawBitmap(L"assets\\5pounds.bmp", 0, 450, 100, 50);
	drawBitmap(L"assets\\10pound.bmp", 100, 450, 100, 50);
	drawBitmap(L"assets\\20pound.bmp", 200, 450, 100, 50);
	DWORD elapsed = ::GetTickCount() - starttime;
	sec = elapsed / MS_PER_SECOND;
	if (sec > 10000)
	{
		sec = 0;
	}
	timerStamp = to_string(sec);
	setFont(28, L"Segoe UI");
	setTextColour(RED);
	drawText(timerStamp.c_str(), 35, 20);
	if ((sec > 14) && (correct == false))
	{
		correctText = "Incorrect.";
		correct = false;
		if (sec == 16)
		{
			//restart();
		}
	}

	balanceDue();
	answerText();
	EasyGraphics::onDraw();
}
void DrawingTool::onLButtonDown(UINT nFlags, int x, int y)
{
	cx = x;
	cy = y;
	if (cx >= 0 && cx <= 50 && cy >= 400 && cy < 450)
	{
		denomCount[0] += 1;
		checkAnswer();
	}
	if (cx >= 50 && cx < 100 && cy > 400 && cy < 450)
	{
		denomCount[1] += 1;
		checkAnswer();
	}
	if (cx >= 100 && cx < 150 && cy > 400 && cy < 450)
	{
		denomCount[2] += 1;
		checkAnswer();
	}
	if (cx >= 150 && cx < 200 && cy > 400 && cy < 450)
	{
		denomCount[3] += 1;
		checkAnswer();
	}
	if (cx >= 200 && cx < 250 && cy > 400 && cy < 450)
	{
		denomCount[4] += 1;
		checkAnswer();

	}
	if (cx >= 250 && cx < 300 && cy>400 && cy < 450)
	{
		denomCount[5] += 1;
		checkAnswer();
	}
	if (cx >= 300 && cx < 350 && cy>400 && cy < 450)
	{
		denomCount[6] += 1;
		checkAnswer();
	}
	if (cx >= 350 && cx < 400 && cy>400 && cy < 450)
	{
		denomCount[7] += 1;
		checkAnswer();
	}
	if (cx >= 0 && cx <= 100 && cy > 450 && cy < 500)
	{
		denomCount[8] += 1;
		checkAnswer();
	}
	if (cx >= 100 && cx <= 200 && cy > 450 && cy < 500)
	{
		denomCount[9] += 1;
		checkAnswer();
	}
	if (cx >= 200 && cx <= 300 && cy > 450 && cy < 500)
	{
		denomCount[10] += 1;
		checkAnswer();
	}


	if (cx > 650 && cx <= 720 && cy > 150 && cy < 200)
	{
		starttime = ::GetTickCount();
		setTimer(REDRAW_TIMER_ID, 60);
		amounts[0] = getRandomPurchase();
		text1 = to_string(amounts[0]);
		amounts[1] = getRandomPay();
		text2 = to_string(amounts[1]);
		for (int i = 0; i < 11; i++)
		{
			denomCount[i] = 0;
		}
	}
	if (cx > 650 && cx <= 720 && cy > 225 && cy < 295)
	{
		for (int i = 0; i < 11; i++)
		{
			denomCount[i] = 0;
		}
	}
	onDraw();

}
double DrawingTool::getRandomPurchase()
{
	srand((double)time(NULL));
	double decimal = (double)rand()/(RAND_MAX);
	decimal = round(decimal * 100) / 100;
	int a = rand() % 100;
	decimal += (double)a;
	return randomPurchase = decimal;

}
double DrawingTool::getRandomPay()
{
	int randomPay = ceil(randomPurchase);
	if (randomPay % 10 == 2)
	{
		randomPay += 3;
	}
	else if (randomPay % 10 == 5)
	{
		randomPay += 1;

	}
	return randomPay;

}
double DrawingTool::getBalance()
{
	return balance = amounts[1] - amounts[0];
}

void DrawingTool::balanceDue()
{
	setTextColour(BLACK);
	setFont(18, L"Tahoma");
	string text = "Balance Due: ";
	double due = getBalance();
	text += to_string(due);
	drawText(text.c_str(), 80, 500);
}
void DrawingTool::answerText()
{
	setTextColour(BLACK);
	setFont(18, L"Tahoma");
	string text = "Remaining Balance :";
	double bal = checkRemainingBalance();
	text += to_string(bal);
	drawText(text.c_str(), 400, 500);
}
double DrawingTool::checkRemainingBalance()
{
	double answer = 0;
	for (int i = 0; i < 11; i++)
	{
		answer += (denomCount[i] * denom[i]);
	}
	return balanceAnswer = balance - answer;

}
void DrawingTool::onTimer(UINT nIDEvent)
{
	if (nIDEvent == REDRAW_TIMER_ID)
		onDraw();
}
bool DrawingTool::checkAnswer()
{
	balanceAnswer = checkRemainingBalance();
	if ((balanceAnswer == 0.00000))
	{
		correct = true;
	}
	return correct;
}