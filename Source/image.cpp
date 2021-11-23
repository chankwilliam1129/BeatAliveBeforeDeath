#include "all.h"

int bgImage;
int bgImage2;
int RankBgImage;
int RankScoreImage;
int TitleBgImage1;
int TitleBgImage2;
int TitleBgImage3;
int TitleBgImage4;
int TitleBgImage5;
int TitleBgImage6;
int TitleBgImage7;
int TitleBgImage8;
int TitleBgImage9;

int hairSelect;
int tutorialSelect;
int GrHandle[40];
int PlHandle[8];
int PlHandle2[8];
int PlHandle3[8];
int PlHandle4[8];
int PlHandle5[8];
int rocketHandle[8];
int dead[4];

int J_PlHandle[8];
int Dash_Handle[10];
int BgHandle[8];
int UiImage1;
int UiImage2;
int UiHandle3[8];
int effectHandle[6];
int GoalHandle[8];

int Tutorial_1_explain[7];
int Tutorial_2_explain[5]; 
int Tutorial_3_explain[4]; 
int Tutorial_retry;
int enterskip;

int num[10];
extern int hair_Style = 0;

int score_board;
int score_num[10];

int tutorial_;
int game_;

int retry1;
int retry2;
int die;
int point[8];
//--------------------------------
// âÊëúì«Ç›çûÇ›
//--------------------------------
void image_load(int scene) {
	switch (scene) {
	case SCENE_TITLE:
		TitleBgImage1 = LoadGraph(L".\\Data\\Image\\new_bg_BIG.png");
		TitleBgImage2 = LoadGraph(L".\\Data\\Image\\2.png");
		TitleBgImage3 = LoadGraph(L".\\Data\\Image\\3.png");
		TitleBgImage4 = LoadGraph(L".\\Data\\Image\\4.png");
		TitleBgImage5 = LoadGraph(L".\\Data\\Image\\5.png");
		TitleBgImage6 = LoadGraph(L".\\Data\\Image\\6.png");
		TitleBgImage7 = LoadGraph(L".\\Data\\Image\\7.png");
		TitleBgImage8 = LoadGraph(L".\\Data\\Image\\8.png");
		TitleBgImage9 = LoadGraph(L".\\Data\\Image\\9.png");
		tutorial_ = LoadGraph(L".\\Data\\Image\\title_tutorial1.png");
		game_ = LoadGraph(L".\\Data\\Image\\title_tutorial2.png");
		bgImage2 = LoadGraph(L".\\Data\\Image\\new_bg.png");
		break;
	case SCENE_GAME:
		LoadDivGraph(L".\\Data\\Image\\character_run.png", 8, 4, 2, 85, 113, PlHandle);
		LoadDivGraph(L".\\Data\\Image\\character_run.png", 8, 4, 2, 85, 113, J_PlHandle);
		LoadDivGraph(L".\\Data\\Image\\hair2.png", 8, 4, 2, 115, 153, PlHandle2);
		LoadDivGraph(L".\\Data\\Image\\hair3.png", 8, 4, 2, 115, 153, PlHandle3);
		LoadDivGraph(L".\\Data\\Image\\hair4.png", 8, 4, 2, 115, 153, PlHandle4);
		LoadDivGraph(L".\\Data\\Image\\hair5.png", 8, 4, 2, 115, 153, PlHandle5);
		LoadDivGraph(L".\\Data\\Image\\stage.png", 40, 8, 5, BOX_SIZE_X, BOX_SIZE_Y, GrHandle);
		bgImage = LoadGraph(L".\\Data\\Image\\bg_back.png");
		bgImage2 = LoadGraph(L".\\Data\\Image\\new_bg.png");
		LoadDivGraph(L".\\Data\\Image\\dash.png", 8, 1, 8, 247, 96, Dash_Handle);
		LoadDivGraph(L".\\Data\\Image\\bg_back.png", 8, 8, 1, 262, 645, BgHandle);
		LoadDivGraph(L".\\Data\\Image\\endpoint_set.png", 8, 8, 1, 112, 172, GoalHandle);
		score_board = LoadGraph(L".\\Data\\Image\\score.png");
		LoadDivGraph(L".\\Data\\Image\\dead.png", 4, 4, 1, 90, 90, dead);
		die = LoadGraph(L".\\Data\\Image\\dead1.png");
		LoadDivGraph(L".\\Data\\Image\\num2.png", 10, 10, 1, 70, 118, score_num);
		
		UiImage1 = LoadGraph(L".\\Data\\Image\\ui1.png");
		UiImage2 = LoadGraph(L".\\Data\\Image\\ui2.png");
		LoadDivGraph(L".\\Data\\Image\\run_jump_set.png", 8, 4, 2, 215, 206, UiHandle3);
		LoadDivGraph(L".\\Data\\Image\\effect.png", 6, 3, 2, 400, 400, effectHandle);
        LoadDivGraph(L".\\Data\\Image\\character_rocket.png", 8, 4, 2, 85, 113, rocketHandle);
		LoadDivGraph(L".\\Data\\Image\\mask.png", 8, 4, 2, 112, 63, point);
		break;
	case SCENE_RANKING:
		RankBgImage = LoadGraph(L".\\Data\\Image\\ranking_bg.png");
		RankScoreImage = LoadGraph(L".\\Data\\Image\\ranking.png");
		LoadDivGraph(L".\\Data\\Image\\suuzi.png", 10, 10, 1, 21, 26, num);
		retry1 = LoadGraph(L".\\Data\\Image\\restart2.png");
		retry2 = LoadGraph(L".\\Data\\Image\\restart1.png");
		break;

	case SCENE_HAIR:
		LoadDivGraph(L".\\Data\\Image\\character_set.png", 8, 4, 2, 115, 153, PlHandle);
		LoadDivGraph(L".\\Data\\Image\\hair2.png", 8, 4, 2, 115, 153, PlHandle2);
		LoadDivGraph(L".\\Data\\Image\\hair3.png", 8, 4, 2, 115, 153, PlHandle3);
		LoadDivGraph(L".\\Data\\Image\\hair4.png", 8, 4, 2, 115, 153, PlHandle4);
		LoadDivGraph(L".\\Data\\Image\\hair5.png", 8, 4, 2, 115, 153, PlHandle5);
		break;

	case SCENE_TUTORIAL:
		LoadDivGraph(L".\\Data\\Image\\character_run.png", 8, 4, 2, 85, 113, PlHandle);
		LoadDivGraph(L".\\Data\\Image\\character_run.png", 8, 4, 2, 85, 113, J_PlHandle);
		LoadDivGraph(L".\\Data\\Image\\hair2.png", 8, 4, 2, 115, 153, PlHandle2);
		LoadDivGraph(L".\\Data\\Image\\hair3.png", 8, 4, 2, 115, 153, PlHandle3);
		LoadDivGraph(L".\\Data\\Image\\hair4.png", 8, 4, 2, 115, 153, PlHandle4);
		LoadDivGraph(L".\\Data\\Image\\hair5.png", 8, 4, 2, 115, 153, PlHandle5);
		LoadDivGraph(L".\\Data\\Image\\stage.png", 40, 8, 5, BOX_SIZE_X, BOX_SIZE_Y, GrHandle);
		bgImage = LoadGraph(L".\\Data\\Image\\bg_back.png");
		bgImage2 = LoadGraph(L".\\Data\\Image\\new_bg.png");
		LoadDivGraph(L".\\Data\\Image\\dash.png", 8, 1, 8, 247, 96, Dash_Handle);
		LoadDivGraph(L".\\Data\\Image\\bg_back.png", 8, 8, 1, 262, 645, BgHandle);
		LoadDivGraph(L".\\Data\\Image\\endpoint_set.png", 8, 8, 1, 112, 172, GoalHandle);
		UiImage1 = LoadGraph(L".\\Data\\Image\\ui1.png");
		UiImage2 = LoadGraph(L".\\Data\\Image\\ui2.png");
		LoadDivGraph(L".\\Data\\Image\\run_jump_set.png", 8, 4, 2, 215, 206, UiHandle3);
		LoadDivGraph(L".\\Data\\Image\\effect.png", 6, 3, 2, 400, 400, effectHandle);
		LoadDivGraph(L".\\Data\\Image\\character_rocket.png", 8, 4, 2, 85, 113, rocketHandle);
		LoadDivGraph(L".\\Data\\Image\\dead.png", 4, 4, 1, 90, 90, dead);
		LoadDivGraph(L".\\Data\\Image\\tutorial01.png", 7, 1, 7, 1280, 212, Tutorial_1_explain);
		LoadDivGraph(L".\\Data\\Image\\tutorial02.png", 5, 1, 5, 1280, 212, Tutorial_2_explain); 
		LoadDivGraph(L".\\Data\\Image\\tutorial03.png", 4, 1, 4, 1280, 212, Tutorial_3_explain); 
		enterskip = LoadGraph(L".\\Data\\Image\\enterskip.png");
		LoadDivGraph(L".\\Data\\Image\\mask.png", 8, 4, 2, 112, 63, point);
		Tutorial_retry = LoadGraph(L".\\Data\\Image\\tutorial04.png");
		break;
	}
}
//--------------------------------
// âÊëúîjä¸
//--------------------------------
void DeleteDraw(int draw) {
	DeleteGraph(draw);
}