#include "stdafx.h"
#include <iostream>
#include <time.h>

// 랜덤 숫자 구하기 Proc
bool getRandProc(int(&refArr)[3]);

// 입력받기 Proc
bool inputNumProc(int(&refArr)[3]);

// 입력값 체크
bool checkVaild(int(&refArr)[3]);

// 종료(결과) 검사
bool checkResult(int strike, int ball);

// 배열의 특정 인덱스<까지> 어떠한 값이 있는지
int valueInArr(int(&refArr)[3], int idx, int value);

// 배열의 특정 인덱스를 <제외>하고 어떠한 값이 있는지
int valueInArrEx(int(&refArr)[3], int idx, int value);

// 배열 받아서 변환해서 넣는 함수
bool numToArr(int(&refArr)[3], int inputParam);

// 입력 받기
bool inputNum(int& inputParam);

int main()
{
	// 랜덤 숫자 먼저 구한다
	srand((unsigned int)time(NULL));
	int randNumArr[3] = {};
	getRandProc(randNumArr);

	std::wcout << L"rand value is : " << randNumArr[0] << randNumArr[1] << randNumArr[2] << std::endl;

	while (1) {
		// 스트라이크, 볼
		int strike = 0;
		int ball = 0;

		// 숫자 3개로 분리
		int inputNumArr[3] = {};

		if (!inputNumProc(inputNumArr)) {
			std::wcout << L"input data is incorrect" << std::endl;
			continue;
		}

		// Strike Check
		for (int i = 0; i < 3; i++) {
			if (inputNumArr[i] == randNumArr[i])
				++strike;
		}

		// Ball Check
		for (int i = 0; i < 3; i++) {
			if (valueInArrEx(randNumArr, i, inputNumArr[i]) != -1) {
				++ball;
			}
		}

		// 결과 확인
		if (checkResult(strike, ball)) {
			break;
		}
	}

	return 0;
}

bool getRandProc(int(&refArr)[3]) {
	refArr[0] = (rand() % 9) + 1;

	int i = 1;
	while (i < 3) {
		refArr[i] = (rand() % 9) + 1;

		if (valueInArr(refArr, i, refArr[i]) != -1)
			continue;

		++i;
	}

	return true;
}

bool inputNumProc(int(&refArr)[3]) {
	// 일단 입력 받고
	int localInputNum = -1;
	if (!inputNum(localInputNum))
		return false;

	// 숫자 3개로 분리
	int inputNumArr[3] = {};
	if (!numToArr(inputNumArr, localInputNum))
		return false;

	// 대입
	for (int i = 0; i < 3; i++) {
		refArr[i] = inputNumArr[i];
	}

	return true;
}

bool checkVaild(int(&refArr)[3]) {
	// 이미 입력한 값 중에 중복된 것이 있는지
	for (int i = 1; i < 3; i++) {
		if (refArr[i] == 0) {
			return false;
		}

		if (valueInArr(refArr, i, refArr[i]) != -1) {
			return false;
		}
	}

	return true;
}

bool checkResult(int strike, int ball)
{
	if (strike == 3) {
		std::wcout << L"end" << std::endl;
		return true;
	}

	if ((strike == 0) && (ball == 0)) {
		std::wcout << L"nothing" << std::endl;
		return false;
	}

	std::wcout << L"ball : " << ball << L" // strike : " << strike << std::endl;
	return false;
}

int valueInArr(int(&refArr)[3], int idx, int value) {
	for (int i = 0; i < idx; i++) {
		if (refArr[i] == value)
			return i;
	}

	return -1;
}

int valueInArrEx(int(&refArr)[3], int idx, int value) {
	for (int i = 0; i < 3; i++) {
		if (i == idx)
			continue;

		if (refArr[i] == value)
			return i;
	}

	return -1;
}

bool numToArr(int(&refArr)[3], int inputParam) {
	refArr[0] = (inputParam / 100);
	refArr[1] = ((inputParam % 100) / 10);
	refArr[2] = (inputParam % 10);

	// 유효성 검사
	if (!checkVaild(refArr))
		return false;

	return true;
}

bool inputNum(int& inputParam) {
	std::wcout << L"input number : ";
	std::cin >> inputParam;

	if (inputParam == -1)
		return false;

	if ((inputParam < 0) || (inputParam > 999))
		return false;

	return true;
}