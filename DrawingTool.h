#pragma once
#include "EasyGraphics.h"
using namespace std;

class DrawingTool :
	public EasyGraphics



{
public:
	DrawingTool();
	~DrawingTool();
	double randomPurchase;
	double getRandomPurchase();
	double getRandomPay();
	int colour;
	int cx = 50;
	int cy = 300;
	virtual void onDraw();
	virtual void onLButtonDown(UINT nFlags, int x, int y);
	int denomCount[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	double denom[11]{0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.0, 2.0, 5.0, 10.0, 20.0};
	double amounts[2] = { 0.00,0.00 }; // 1 for purchase 2 for pay
	double balance = 0.0, balanceAnswer = 0.0;
	double getBalance();
	double checkRemainingBalance();
	void balanceDue();
	void answerText();
	bool checkAnswer();
	int sec;
	string text1, text2, correctText;
protected:
	void onTimer(UINT nIDEvent);
protected:
	static const int REDRAW_TIMER_ID = 1;
	static const int MS_PER_SECOND = 1000;
	DWORD starttime;
	string timerStamp;
	bool correct = false;
	// change voids

	

};

