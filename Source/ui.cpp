#include "all.h"
extern int step_count;
extern int UiImage1;
extern int UiImage2;
extern int UiHandle3[8];
extern int judge_timer;
extern bool tutorial_check;
extern int score_board;
extern int score_num[10];
extern int enterskip;
extern int judge_loop;
extern bool isJumpButtonLight;
extern bool isSkipButtonLight;
extern int game_state;
extern int tutorial_state;
extern int die;
extern int Tutorial_retry;

OBJ2D effect[4];
int jump_timer;
int skip_timer;
OBJ2D ui;
//--------------------------------
// 初期設定
//--------------------------------
void ui_init() {
	ui.skip_anime = 0;
	ui.jump_anime = 4;
	skip_timer = 0;
	jump_timer = 0;

	for (int i = 0; i < 4; i++) {
		effect[i].anime = -1;
		effect[i].timer = 0;
	}
}


//--------------------------------
// 更新処理
//--------------------------------
void ui_update() {
	if (judge_timer > judge_loop / 2 + 1 && judge_timer < judge_loop) {
		skip_timer++;
		ui.skip_anime = skip_timer / (judge_loop / 15) % 7;
		if (ui.skip_anime >= 3) {
			ui.skip_anime = 5 - ui.skip_anime;
			if (ui.skip_anime == 0) {
				isSkipButtonLight = true;
			}
		}
		if (isSkipButtonLight == true) {
			ui.skip_anime = 0;
		}
	}
	else {
		ui.skip_anime = 0;
		skip_timer = 0;
		isSkipButtonLight = false;
	}

	if (judge_timer > 0 && judge_timer < judge_loop / 2) {
		jump_timer++;
		ui.jump_anime = jump_timer / (judge_loop / 15) % 7 + 4;
		if (ui.jump_anime >= 7) {
			ui.jump_anime = 13 - ui.jump_anime;
			if (ui.jump_anime == 4) {
				isJumpButtonLight = true;
			}
		}
		if (isJumpButtonLight == true) {
			ui.jump_anime = 4;
		}
	}
	else {
		ui.jump_anime = 4;
		jump_timer = 0;
		isJumpButtonLight = false;
	}
}
//--------------------------------
// 描画処理
//--------------------------------
void ui_draw(){
	//描画座標,画像座標,画像の幅高さ,画像番号,透明処理フラグ,横反転フラグ,縦反転フラグ
	//DrawRectGraph(bg2PosX, 500, bg2_anime.x, bg2_anime.y, BG2_SIZE_X, BG2_SIZE_Y, ImageGame2, 1, 0, 0);
	//if (tutorial_check == false) { DrawFormatString(0, 0, (255, 255, 255), L"%d", step_count); }          //かえた
 //   DrawExtendFormatString(100, 100, 10, 10, (255, 255, 255), L"YOUR_SELECT:%d", player_state_check());
 //   DrawExtendFormatString(100, 300, 10, 10, (255, 255, 255), L"TIMING:%d", Timing_timer());
 //   DrawExtendFormatString(850, 300, 4, 4, (255, 255, 255), L"1:ジャンプ");
 //   DrawExtendFormatString(850, 400, 4, 4, (255, 255, 255), L"2:加速");

	/*DrawGraph(0, 458, UiImage1, 1);
	DrawGraph(0, 458, UiImage2, 1);*/
	/*DrawGraphF(-74, 555, UiHandle3[ui.jump_anime], TRUE);
	DrawGraphF(1135,555, UiHandle3[ui.skip_anime], TRUE);*/
	if (tutorial_check == true) {
		DrawGraph(SCREEN_WIDTH - 400, 0, enterskip, 1);
	}
	
	if (tutorial_check == false) {
		DrawGraph(30, -110, score_board, 1);
		draw_stepcount(step_count, 100, 115);
	}
	if (game_state == 2) {
		DrawGraph(SCREEN_WIDTH / 2 - 346, SCREEN_HEIGHT / 2 - 172, die, 1);
	}
	if (tutorial_state == 4) {
		DrawGraph(0, SCREEN_HEIGHT / 2 - 100, Tutorial_retry, 1);
		
	}
}

void draw_stepcount(int step_count, int x, int y) {
	int s = step_count;
	int n3 = s / 100;
	int n2 = s / 10 % 10;
	int n1 = s % 10;
	DrawGraph(x + 0 * 57, y + 40, score_num[n3], true);
	DrawGraph(x + 1 * 57, y + 20, score_num[n2], true);
	DrawGraph(x + 2 * 57, y,      score_num[n1], true);
}