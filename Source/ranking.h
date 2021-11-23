#ifndef INCLUDED_RANKING
#define INCLUDED_RANKING

//******************************************************************************
//
//
//      
//
//
//******************************************************************************

//------< 定数 >----------------------------------------------------------------
#define RANKING_MAX     (10)

#define NUMBER_WIDTH    (64)
#define NUMBER_HEIGHT   (96)
#define RANK_SIZE_X     (21)
#define RANK_SIZE_Y     (26 + 18)
#define RANK_POS_X      (SCREEN_WIDTH / 2- 32)
#define RANK_POS_Y      (252)
//------< プロトタイプ宣言 >-----------------------------------------------------
void ranking_init();
void ranking_update();
void ranking_check(int score);
void ranking_draw();
void ranking_end();
void ranking_show();
#endif 



