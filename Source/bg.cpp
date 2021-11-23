#include "all.h"
extern int bgImage;
extern int bgImage2;
extern OBJ2D player;
extern float block_draw_pos_x;
extern int BgHandle[8];
float bg_x[7];
float bg2_x[3];
int x[7] = { 0,1,2,3,4,5 };
int x2[3];
// BGのX座標を保持する変数を宣言する
int bg_anime;
extern int judge_timer;
extern int ground_timer;

//--------------------------------
// 初期設定
//--------------------------------
void bg_init()
{
	int k = 0;
	int k2 = 0;
	for (int i = 0; i < 6; i++) {
		x[i] = k;
		bg_x[i] = x[i] * BG_SIZE_X;
		k++;
	}

	for (int i = 0; i < 3; i++) {
		x2[i] = k2;
		bg2_x[i] = x2[i] * BG2_SIZE_X;
		k2++;
	}
	// BGのX座標の初期設定を行う
}

//--------------------------------
// 更新処理
//--------------------------------
void bg_update()
{
	//アニメーション

	/*bg_anime = ground_timer / 6 % 15;
	if (bg_anime > 7)bg_anime = (14 - bg_anime);*/

	// BGをスクロールさせる
	for (int i = 0; i < 7; i++) {
		bg_x[i] = x[i] * BG_SIZE_X;
		if (bg_x[i] + BG_SIZE_X <= block_draw_pos_x * 0.7) {
			x[i] += 6;
		}
	}

	for (int i = 0; i < 3; i++) {
		bg2_x[i] = x2[i] * BG2_SIZE_X;
		if (bg2_x[i] + BG2_SIZE_X <= block_draw_pos_x * 0.4) {
			x2[i] += 2;
		}
	}
}
//--------------------------------
// 描画処理
//--------------------------------
void bg_draw()
{
	bg_anime = ground_timer / 6 % 15;
	if (bg_anime > 7)bg_anime = (14 - bg_anime);

	for (int i = 0; i < 3; i++) {
		DrawGraph(bg2_x[i] - block_draw_pos_x*0.4, 10, bgImage2, 1);
	}

	for (int i = 0; i < 6; i++) {
		DrawGraphF(bg_x[i] - block_draw_pos_x*0.7, -90, BgHandle[bg_anime], TRUE);
	}
	
	//DrawGraphF(0,0, BgHandle[0], TRUE);
	//DrawGraph(bg1PosX, 0, ImageGame, 1);
	//描画座標,画像座標,画像の幅高さ,画像番号,透明処理フラグ,横反転フラグ,縦反転フラグ
	//DrawRectGraph(bgPosX, 0, 0, 0, SCREEN_WIDTH  , SCREEN_HEIGHT, bgImage, 1, 0, 0);
	//DrawGraph(bg3PosX, 0, ImageGame3,  1);
}

