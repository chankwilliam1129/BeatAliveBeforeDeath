#include "all.h"

//------< 変数 >----------------------------------------------------------------
extern int nextScene;
extern int game_state;
extern int RankBgImage;
extern int RankScoreImage;
extern int num[10];
extern int retry1;
extern int retry2;

extern char KeyBuf[256];
int ranking[RANKING_MAX];
int ranking_state;
int ranking_timer;
extern int decision;
extern int cursor;
extern int rankingBG;
int ranking_draw_y;

extern int impact;
int impactcount;

OBJ2D Rank;
//--------------------------------
// 初期設定
//--------------------------------
void ranking_init()
{
	sound_load(nextScene);
	ranking_state = 0;
	ranking_timer = 0;
	ranking_draw_y = 0;
	hiscore_load();
	impactcount = 0;
	Rank.pos = VECTOR{ 0, 0 };// y:-600
	Rank.speed = VECTOR{ 0,0 };
	Rank.GRAVITY = 3;
	Rank.FRICTION = 0.5;
}

//--------------------------------
// 更新処理
//--------------------------------
void ranking_update() {
	if (impactcount < 3) {
		if (Rank.pos.y == SCREEN_HEIGHT - 100) {
			sound_play_back(impact);
			impactcount++;
		}
	}
	switch (ranking_state) {
	case 0:
		//////// 初期設定 ////////		
			sound_play_back(rankingBG);
			hiscore_new();
			ranking_state++;			
		break;

	case 1:
		//////// 通常時 ////////
		if (KeyBuf[KEY_INPUT_SPACE] == 1)
		{
			sound_play_back(decision);
			ranking_state++;
		}
		break;

	case 2:
		//////// 通常時 ////////
		if (KeyBuf[KEY_INPUT_SPACE] == 1)
		{
		//////// リトライ ////////
			sound_play_back(decision);
			StopSoundMem(rankingBG);
			nextScene = SCENE_GAME;
		}
		if (KeyBuf[KEY_INPUT_LEFT] == 1)
		{
			sound_play_back(cursor);
			ranking_state++;
		}
		break;
	case 3:
		//////// 通常時 ////////
		if (KeyBuf[KEY_INPUT_SPACE] == 1)
		{
			//////// タイトルへ ////////
			sound_play_back(decision);
			StopSoundMem(rankingBG);
			nextScene = SCENE_TITLE;
		}
		if (KeyBuf[KEY_INPUT_RIGHT] == 1)
		{
			sound_play_back(cursor);
			ranking_state--;
		}
		break;
	}
	
	Rank.speed.y += Rank.GRAVITY;
	Rank.pos.y += Rank.speed.y;
	if (Rank.pos.y > SCREEN_HEIGHT - 100) {
		Rank.speed.y *= -1 * Rank.FRICTION;
		Rank.pos.y = SCREEN_HEIGHT - 100;
	}
	//ranking_timer++;

}

//--------------------------------
// 順位並び替え
//--------------------------------
void ranking_check(int score) 
{
	for (int i = 0; i < RANKING_MAX; i++) 
	{
		if (score > ranking[i]) 
		{
			for (int j = RANKING_MAX - 1; j > i; j--) 
			{
				ranking[j] = ranking[j - 1];
			}
			ranking[i] = score;
			break;
		}
	}
}

//--------------------------------
// 描画処理
//--------------------------------
void ranking_draw(){
	DrawGraph(0, 0, RankBgImage, 1);
	DrawGraph(0, Rank.pos.y - 650, RankScoreImage, 1);
	ranking_show();
	if (ranking_state == 2) {
		DrawGraph(SCREEN_WIDTH / 2 - 463, 145, retry1, 1);
	}
	if (ranking_state == 3) {
		DrawGraph(SCREEN_WIDTH / 2 - 463, 145, retry2, 1);
	}

	/*for (int i = 0; i < RANKING_MAX; i++) {
		DrawFormatString(100, 20+(i*30), (0, 255, 0), L"%d\n", ranking[i]);
	}*/	
}

//--------------------------------
// 終了処理
//--------------------------------
void ranking_end(){
	DeleteDraw(RankBgImage);
	DeleteDraw(RankScoreImage);	
	DeleteDraw(num[10]);
	DeleteDraw(retry1);
	DeleteDraw(retry2);
	
}

void drawRanking(int ranking, int x, int y) {
	int r = ranking;
	int n3 = r / 100;
	int n2 = r / 10 % 10;
	int n1 = r % 10;
	DrawGraph(x + 0 * RANK_SIZE_X, y, num[n3], true);
	DrawGraph(x + 1 * RANK_SIZE_X, y, num[n2], true);
	DrawGraph(x + 2 * RANK_SIZE_X, y, num[n1], true);
}

void ranking_show() {
	int x = RANK_POS_X;
	int y = RANK_POS_Y + Rank.pos.y - 650;
	for (int i = 0; i < RANKING_MAX; i++) {
		drawRanking(ranking[i], x, y);
		y += RANK_SIZE_Y;
	}
}