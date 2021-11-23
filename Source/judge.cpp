//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< プロトタイプ宣言 >-----------------------------------------------------

//------< 変数 >----------------------------------------------------------------
char KeyBuf[256];
extern int judge_timer;
bool first;
bool second;
extern int tutorial_restart;

void TimingInit()
{
	first = false;
	second = false;
}
int judge_loop = JUDGE_LOOP;
//--------------------------------
// タイミング
//--------------------------------
void Timing_Judge() {
    if (judge_timer > judge_loop) { judge_timer = -1; first = false; second = false; }
    if ((KeyBuf[KEY_INPUT_SPACE] == 1) && judge_timer < judge_loop / 2 + 1 && judge_timer > 0) { first = true; }
	if (tutorial_restart != 1) 
	{
		if ((KeyBuf[KEY_INPUT_SPACE] == 1) && judge_timer < judge_loop + 1 && judge_timer > judge_loop / 2) { second = true; }
		if (tutorial_restart != 2) 
		{
			if ((KeyBuf[KEY_INPUT_SPACE] > 2)) { first = false; second = false; }
		}
	}
    
}
//--------------------------------
// 自機の行動
//--------------------------------
int player_state_check() {
	if (first == true && second == true) { return JUMPSKIP; }
	if (first == true && second == false) { return JUMP; }
	if (first == false && second == true) { return SKIP; }
	return RUN;
}

int Timing_timer() {
	if (judge_timer <= judge_loop / 2 && judge_timer >= 1)
		return 1;
	else {
		return 2;
	}
}
//--------------------------------
// キー読み込み
//--------------------------------
void GetKeyState() {
	static char Buf[256];
	GetHitKeyStateAll(Buf);
	for (int i = 0; i < 256; i++) {
		if (Buf[i]) {
			if (KeyBuf[i] == 0) {
				KeyBuf[i] = 1;
			}
			else if (KeyBuf[i] == 1) {
				KeyBuf[i]++;
			}
		}
		else {
			if (KeyBuf[i] > 0) {
				KeyBuf[i] = -1;
			}
			else KeyBuf[i] = 0;
		}
	}
}
