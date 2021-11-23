#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

//******************************************************************************
//
//
//      player.h
//
//
//******************************************************************************

//------< 定数 >----------------------------------------------------------------
// 自機の幅（の半分）と高さ（の半分）を定義する
#define PL_WIDTH        (32)
#define PL_HEIGHT       (32)
#define PL_POS_X        (0)
#define PL_POS_Y        (5)
#define PL_ANIME        (8)
#define START_FIX_X     (300)
#define PL_FIX_X        (13)
#define PL_FIX_Y        (21)
//------< プロトタイプ宣言 >-----------------------------------------------------
void player_init();
void player_update();
void player_draw();
int  goal_check(OBJ2D);
void dead_pos(OBJ2D *);
void normal_dead1(OBJ2D *player);
void jump_dead1(OBJ2D *player);
void jump_dead2(OBJ2D *player);
void kasoku_dead1(OBJ2D *player);
void mix_dead1(OBJ2D *player);

#endif // !INCLUDED_PLAYER

