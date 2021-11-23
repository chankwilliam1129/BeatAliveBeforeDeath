#include "all.h"

int effect_state;
int effect_timer;

int effect_jump_timer;
int effect_skip_timer;

OBJ2D jump;
OBJ2D skip;
extern OBJ2D player;
float jump_Opacity;
float skip_Opacity;

bool effect_jump_check;
bool effect_skip_check;
bool isJumpButtonLight;
bool isSkipButtonLight;

extern char KeyBuf[256];
extern int effectHandle[6];
extern int judge_timer;
extern int GoalHandle[8];
extern float block_draw_pos_x;
extern Box box[AREA_Y + 1][AREA_X];
extern int UiImage1;
extern int UiImage2;
extern int UiHandle3[8];
extern OBJ2D ui;

extern int explain_state;
extern int tutorial_restart;

extern int sx;
extern int sy;
extern int ny;
extern int nx;
extern int judge_loop;
extern int ground_timer;
//--------------------------------
// 初期設定
//--------------------------------
void effect_init() {
	effect_state = 0;
	effect_timer = 0;
	effect_jump_check = false;
	effect_skip_check = false;
	isJumpButtonLight = false;
	isSkipButtonLight = false;
	jump.anime = 0;
	skip.anime = 0;

	jump.draw_pos.x = JUMP_DRAW_X;
	jump.draw_pos.y = JUMP_DRAW_Y;
	skip.draw_pos.x = SKIP_DRAW_X;
	skip.draw_pos.y = SKIP_DRAW_Y;
}

//--------------------------------
// 更新処理
//--------------------------------
void effect_update() 
{
	//ジャンプエフェクト
	if (player_state_check() == JUMP) 
	{
		switch (jump.state) 
		{
		case 0:
			effect_jump_timer = 0;
			jump.state++;
		case 1:
			effect_jump_timer++;
			if (jump.anime == 2) 
			{
				jump.anime = -1;
				jump.anime2 = -1;
				jump.state++;
			}
			if (jump.state != 2) 
			{
				jump.anime = effect_jump_timer / 4 % 3;
				jump.anime2 = effect_jump_timer / 4 % 3 + 3;
			}
			break;
		}
		effect_jump_check = true;
	}
	else {
		jump.state = 0;
	}


	//スキップ& MIX エフェクト
	if (player_state_check() == SKIP || player_state_check() == JUMPSKIP) {
		switch (skip.state) {
		case 0:
			effect_skip_timer = 0;
			skip.state++;
		case 1:
			effect_skip_timer++;
			if (skip.anime == 2) {
				skip.anime = -1;
				skip.anime2 = -1;
				skip.state++;
			}
			if (skip.state != 2)
				skip.anime = (effect_skip_timer / 4) % 3;
			skip.anime2 = (effect_skip_timer / 4) % 3 + 3;
			break;
		}
		effect_skip_check = true;
	}
	else {
		skip.state = 0;
	}


	if (judge_timer == 0) 
	{
		effect_jump_check = false;
		effect_skip_check = false;
		jump.draw_pos.y = JUMP_DRAW_Y;
		skip.draw_pos.y = SKIP_DRAW_Y;
	}
	/*effect_timer++;	*/

	if (player_state_check() == 0) {
		for (int y = 0; y < AREA_Y + 1; y++) {
			for (int x = 0; x < AREA_X; x++) {
				box[y][x].next_light = false;
				box[y][x].next_Red_light = false;
			}
		}
		if (box[sy + 1][sx].ground_flg == true) {
			for (int y = ny + 1; y < AREA_Y + 1; y++) {
				if (box[y][sx + 1].ground_flg == true) {
					box[y - 1][sx + 1].next_light = true;
				}
				if (box[y][sx + 1].type == 2) {
					box[y - 1][sx + 1].next_Red_light = true;
				}
			}
		}
	}
	else if (player_state_check() == 1) {
		for (int y = 0; y < AREA_Y + 1; y++) {
			for (int x = 0; x < AREA_X; x++) {
				box[y][x].next_light = false;
				box[y][x].next_Red_light = false;
			}
		}
		for (int y = ny; y < AREA_Y + 1; y++) {
			if (box[y][sx + 1].ground_flg == true) {
				box[y - 1][sx + 1].next_light = true;
			}
			if (box[y][sx + 1].type == 2) {
				box[y - 1][sx + 1].next_Red_light = true;
			}
		}
	}
	else if (player_state_check() == 2) {
		for (int y = 0; y < AREA_Y + 1; y++) {
			for (int x = 0; x < AREA_X; x++) {
				box[y][x].next_light = false;
				box[y][x].next_Red_light = false;
			}
		}
		for (int y = ny + 1; y < AREA_Y + 1; y++) {
			if (box[y][nx + 2].ground_flg == true) {
				box[y - 1][nx + 2].next_light = true;
			}
			if (box[y][nx + 2].type == 2) {
				box[y - 1][nx + 2].next_Red_light = true;
			}
		}
	}
	else if (player_state_check() == 3) {
		for (int y = 0; y < AREA_Y + 1; y++) {
			for (int x = 0; x < AREA_X; x++) {
				box[y][x].next_light = false;
				box[y][x].next_Red_light = false;
			}
		}
		for (int y = ny; y < AREA_Y + 1; y++) {
			if (box[y][nx + 2].ground_flg == true) {
				box[y - 1][nx + 2].next_light = true;
			}
			if (box[y][nx + 2].type == 2) {
				box[y - 1][nx + 2].next_Red_light = true;
			}
		}
	}

}

//--------------------------------
// 描画処理
//--------------------------------
void effect_draw() 
{

	DrawGraph(0, 458, UiImage1, 1);
	if (player.exist == TRUE) 
	{
		if (effect_jump_check == true && jump.anime != -1 && jump.anime2 != -1) 
		{
			DrawGraphF(jump.draw_pos.x - 5, jump.draw_pos.y, effectHandle[jump.anime], TRUE);
			DrawGraphF(jump.draw_pos.x + 5, jump.draw_pos.y, effectHandle[jump.anime2], TRUE);
		}
		if (effect_skip_check == true && skip.anime != -1) 
		{
			if (tutorial_restart != 1) {
				DrawGraphF(skip.draw_pos.x - 5, skip.draw_pos.y, effectHandle[skip.anime], TRUE);
				DrawGraphF(skip.draw_pos.x + 5, skip.draw_pos.y, effectHandle[skip.anime2], TRUE);
			}
		}
	}

	DrawGraph(0, 458, UiImage2, 1);
	if (player.exist == TRUE)
	{
		DrawGraphF(-74, 555, UiHandle3[ui.jump_anime], TRUE);
		if (tutorial_restart != 1) {
			DrawGraphF(1135, 555, UiHandle3[ui.skip_anime], TRUE);
		}
	}

	if (player.exist == FALSE) 
	{
		DrawGraphF(-74, 555, UiHandle3[4], TRUE);
		if (tutorial_restart != 1) {
			DrawGraphF(1135, 555, UiHandle3[0], TRUE);
		}
	}
	

	if (tutorial_restart == 1 && explain_state == 4)
	{
		DrawGraphF(-74, 555, UiHandle3[ground_timer / 6 % 4 + 4], TRUE);
	}
	if (tutorial_restart == 2 && explain_state == 1)
	{
		DrawGraphF(1135, 555, UiHandle3[ground_timer / 6 % 4 ], TRUE);
	}
	if (tutorial_restart == 3 && explain_state == 1)
	{
		DrawGraphF(-74, 555, UiHandle3[ground_timer / 8 % 4 + 4], TRUE);
		DrawGraphF(1135, 555, UiHandle3[ground_timer / 8 % 4], TRUE);
	}
	
}
