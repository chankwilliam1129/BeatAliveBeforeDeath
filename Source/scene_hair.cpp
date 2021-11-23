// ------< インクルード >-------------------------------------------------------- -
#include "all.h"

//------< プロトタイプ宣言 >-----------------------------------------------------

//------< 変数 >----------------------------------------------------------------
OBJ2D player;
int hairChoice;
int hair_timer;
int* hairStyle;
extern char KeyBuf[256];
extern int PlHandle[8];
extern int PlHandle2[8];
extern int PlHandle3[8];
extern int PlHandle4[8];
extern int PlHandle5[8];
extern int nextScene;
extern int curScene;
extern int hairset;

//--------------------------------
// 初期設定
//--------------------------------
void hair_init() {
	hairChoice = 0;
	hair_timer = 0;
	hairStyle = PlHandle;
	image_load(nextScene);
	hairset = 1;
}

//--------------------------------
// 更新処理
//--------------------------------
void hair_update() {
	player.anime = hair_timer / 6 % PL_ANIME;
	switch (hairChoice) {
	case 0:
		hairChoice++;
		break;
	case 1:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			nextScene = SCENE_TITLE;
		}
		if (KeyBuf[KEY_INPUT_RIGHT] == 1) {
			hairChoice++;
			hairStyle = PlHandle2;
		}
		break;
	case 2:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			nextScene = SCENE_TITLE;
		}
		if (KeyBuf[KEY_INPUT_RIGHT] == 1) {
			hairChoice++;
			hairStyle = PlHandle3;
		}
		if (KeyBuf[KEY_INPUT_LEFT] == 1) {
			hairChoice--;
			hairStyle = PlHandle;
		}
		break;
	case 3:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			nextScene = SCENE_TITLE;
		}
		if (KeyBuf[KEY_INPUT_RIGHT] == 1) {
			hairChoice++;
			hairStyle = PlHandle4;
		}
		if (KeyBuf[KEY_INPUT_LEFT] == 1) {
			hairChoice--;
			hairStyle = PlHandle2;
		}
		break;
	case 4:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			nextScene = SCENE_TITLE;
		}
		if (KeyBuf[KEY_INPUT_RIGHT] == 1) {
			hairChoice++;
			hairStyle = PlHandle5;
		}
		if (KeyBuf[KEY_INPUT_LEFT] == 1) {
			hairChoice--;
			hairStyle = PlHandle3;
		}
		break;
	case 5:
		if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			nextScene = SCENE_TITLE;
		}
		if (KeyBuf[KEY_INPUT_LEFT] == 1) {
			hairChoice--;
			hairStyle = PlHandle4;
		}
		break;
	}
	hair_timer++;
}
//--------------------------------
// 描画処理
//--------------------------------
void hair_draw() {
	DrawGraph(0, 0, hairStyle[player.anime], TRUE);
}
//--------------------------------
// 終了処理
//--------------------------------
void hair_end(){
	DeleteDraw(PlHandle[8]);
	DeleteDraw(PlHandle2[8]);
	DeleteDraw(PlHandle3[8]);
	DeleteDraw(PlHandle4[8]);
	DeleteDraw(PlHandle5[8]);
}