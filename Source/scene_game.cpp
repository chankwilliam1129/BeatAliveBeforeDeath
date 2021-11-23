#include "all.h"
//変えた UI.cpp scenegame.cpp scene tutorial.cpp image.cpp 

//------< 変数 >----------------------------------------------------------------
int game_state;     // 状態
int game_timer;     // タイマー
int step_count;     // スコア
int judge_timer;
int ground_timer;
int bg_sound;
extern int nextScene;
extern char KeyBuf[256];
extern int GrHandle[24];
//player
extern int PlHandle[8];
extern int PlHandle2[8];
extern int PlHandle3[8];
extern int PlHandle4[8];
extern int PlHandle5[8];
extern int Dash_Handle[10];
extern int bgImage; //BG
extern int bgImage2;
extern int UiImage1;
extern int UiImage2;
extern int UiHandle3[8];
extern int effectHandle[16];//sound
extern int decision;
extern int score_board;
extern int score_num[10];
extern int dead[4];
extern int BgHandle[8];
extern int point[8];
extern int GoalHandle[8];
extern int rocketHandle[8];
extern int J_PlHandle[8];
extern int die;
//--------------------------------
// 初期設定
//--------------------------------
void game_init()
{
	sound_load(nextScene);
	game_state = 0;
	game_timer = 0;
	step_count = 0;
	judge_timer = 0;
	ground_timer = 0;
}
//--------------------------------
// ゲーム中
//--------------------------------
void game_common()
{
	// プレイヤーの更新
	player_update();

	// BGの更新
	bg_update();
	// 敵の更新
	//サウンド
	sound_update();

	// エフェクトの更新
	effect_update();
	//UIの初期設定
	ui_update();
	// あたり判定関数を呼ぶ
	
}

//--------------------------------
// 更新処理
//--------------------------------
void game_update()
{
	switch (game_state)
	{
	case 0:
		TimingInit(); 
		//////// 初期設定 ////////
	// プレイヤー（自機）の初期設定
		player_init();
		// 敵の初期設定		

		// エフェクトの初期設定
		effect_init();
		//UIの初期設定
		ui_init();
		// groundの初期設定
		ground_init();
		// BGの初期設定
		bg_init();
		// TODO:09 ゲーム中の音楽を再生させる
		
		game_state++;
		break;

	case 1:
		//////// 通常時 ////////
		game_common();
		break;

	case 2:
		//////// ランキング ////////
		if (KeyBuf[KEY_INPUT_SPACE] == 1)
		{
			sound_play_back(decision);
			//ランキングを表示
			//hiscore_load();
			nextScene = SCENE_RANKING;
		}
		game_common();
		break;
	}
	game_timer++;
	judge_timer++;
	ground_timer++;
}
//--------------------------------
// 描画処理
//--------------------------------
void game_draw()
{	
	// BGの描画（地上物）
	bg_draw();
	// 敵の描画（地上物）
	ground_draw();
	// BGの描画（空中物）

	// 敵の描画（空中物）
	
	// プレイヤーの描画
	player_draw();
	// UIの描画
	ui_draw();
	// エフェクトの描画
	effect_draw();
}

//--------------------------------
// 終了処理
//--------------------------------
void game_end(){
	DeleteDraw(bgImage);
	DeleteDraw(bgImage2);
	DeleteDraw(GrHandle[24]);
	DeleteDraw(PlHandle[8]);
	DeleteDraw(PlHandle2[8]);
	DeleteDraw(PlHandle3[8]);
	DeleteDraw(PlHandle4[8]);
	DeleteDraw(PlHandle5[8]);
	DeleteDraw(UiImage1);
	DeleteDraw(UiImage2);
	DeleteDraw(UiHandle3[8]);
	DeleteDraw(effectHandle[6]);
	DeleteDraw(Dash_Handle[10]);
	DeleteDraw(score_board);
	DeleteDraw(score_num[10]);
	DeleteDraw(dead[4]);
	DeleteDraw(point[8]);
	DeleteDraw(rocketHandle[8]);
	DeleteDraw(BgHandle[8]);
	DeleteDraw(GoalHandle[8]);
	DeleteDraw(J_PlHandle[8]);	
	DeleteDraw(die);

}
