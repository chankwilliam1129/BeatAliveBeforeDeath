//******************************************************************************
//
//
//      player
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< プロトタイプ宣言 >-----------------------------------------------------

//------< 変数 >----------------------------------------------------------------
extern OBJ2D player;
extern OBJ2D bg;
// TODO:47 game_stateをextern宣言する
extern int game_state;
extern int PlHandle[8];
extern int J_PlHandle[8];
extern int rocketHandle[8];
extern int step_count;
extern int judge_timer;
extern int* hairStyle;
int hairset = 0;
extern float block_draw_pos_x;
extern Box box[AREA_Y][AREA_X];
extern int Dash_Handle[10];
extern char KeyBuf[256];
VECTOR speed;
int sx;
int sy;
int nx;
int ny;

extern int judge_loop;
extern int decision;
extern bool tutorial_check;
extern int tutorial_state;
extern bool tutorial3_end;
int tutorial_restart = 0;
bool spos_count_jumpflg;
bool spos_count_skipflg;
bool spos_count_jumpskipflg;
int rocket_fix;

extern int ground_timer;
extern int GrHandle[32];
extern int dead[4];
extern int dead_sound;
bool DeadSoundCheck;
//--------------------------------
// 初期設定
//--------------------------------
void player_init()
{
	sx = 0;
	sy = 0;
	nx = 0;
	ny = 0;
	speed = VECTOR{ 0,0 };
	player.spos = VECTOR{ 0, 5 };
	block_draw_pos_x = 0;
	player.distance = 0;
	player.draw_pos.x = 0;
	// 自機の初期設定を行う
	player.pos.x = PL_POS_X;
	player.pos.y = PL_POS_Y;

	player.pos_before = 0;
	player.pos_after = 0;

	player.exist = TRUE; // プレイヤーが存在している
	player.dash_anime = -1;

	if (hairset == 0) { hairStyle = PlHandle; }
	spos_count_jumpflg = true;
	spos_count_skipflg = true;
	spos_count_jumpskipflg = true;
	DeadSoundCheck = false;
	judge_loop = JUDGE_LOOP;
    player.state2 = 0;
}

//--------------------------------
// 更新処理
//--------------------------------
void player_update()
{
	if (step_count > 30)  { judge_loop = 54;}
	if (step_count > 50)  { judge_loop = 50;}
	if (step_count > 60)  { judge_loop = 48;}
	if (step_count > 70)  { judge_loop = 42;}
	if (step_count > 80)  { judge_loop = 40;}
	if (step_count > 90)  { judge_loop = 38;}
	if (step_count > 100) { judge_loop = 36;}
	if (step_count > 110) { judge_loop = 34;}
	if (step_count > 120) { judge_loop = 32;}
	if (step_count > 130) { judge_loop = 30;}
	if (step_count > 150) { judge_loop = 28;}
	if (step_count > 160) { judge_loop = 24; }


	player.jump_timer++;
	player.skip_timer++;

	if (judge_timer == 1)
	{
		spos_count_jumpflg = true;
		spos_count_skipflg = true;
		spos_count_jumpskipflg = true;
	}

	sx = player.spos.x;
	sy = player.spos.y;
	nx = player.pos.x;
	ny = player.pos.y;

	player.pos_before = player.pos.x;

	if (player.exist == FALSE)
	{
		// TODO:49 ゲームオーバーへ	
		if (tutorial_check == false)
		{
			if (DeadSoundCheck == false)
			{
				sound_play_back(dead_sound);
				DeadSoundCheck = true;
			}  
			judge_loop = JUDGE_LOOP;
			game_state = 2;
			//return;
		}
		else if (tutorial_check == true)
		{
			tutorial_restart = tutorial_state;
			tutorial_state = 4;
			//return;
		}
	}

	if (goal_check(player) == 1)
	{
		if (tutorial_restart == 3) 
		{
			if (KeyBuf[KEY_INPUT_SPACE] == 1)
			{
				sound_play_back(decision);
				tutorial_state = 5;
				tutorial_restart = 0;
			}
		}
		else if (KeyBuf[KEY_INPUT_SPACE] == 1) {
			sound_play_back(decision);
			tutorial_restart++;
			tutorial_state = 0;
		}
		return;
	}

	Timing_Judge();
	player_state_check();

    if (player.exist == TRUE) {
        switch (player_state_check())
        {

        case 0: //normal

            if (judge_timer == judge_loop - 1)
            {
                player.spos.x += 1;
                if (player.exist == TRUE) {
                    normal_dead1(&player);
                }
            }

            if (judge_timer == judge_loop)
            {
                player.pos.x += 1;
                ground_check(&player);
                d_ground_check(&player);

                if (player.exist == true)
                {
                    if (tutorial_check == false)
                    {
                        step_count += 1;
                    }
                }
            }
            break;
        case 1: //jamp
            //if (judge_timer == JUDGE_LOOP / 2 - 4) {
            if (spos_count_jumpflg == true)
            {
                player.jump_timer = 0;
                rocket_fix = (judge_loop / 2 + 4 - judge_timer) / 4;
                player.spos.y -= 1;
                if (player.exist == TRUE) {
                    jump_dead1(&player);
                }
                spos_count_jumpflg = false;
            }
            //}
            if (judge_timer == judge_loop)
            {
                player.pos.y -= 1;
                dead_check(&player);
                player.pos.x += 1;
                player.spos.x += 1;
                if (player.exist == TRUE) {
                    jump_dead2(&player);
                }

                ground_check(&player);
                d_ground_check(&player);
                if (player.exist == true)
                {
                    if (tutorial_check == false)
                    {
                        step_count += 1;
                    }
                }
            }
            break;

        case 2: //加速
            //if (judge_timer == JUDGE_LOOP - 4) {
            if (spos_count_skipflg == true)
            {
                player.skip_timer = 5;
                rocket_fix = (judge_loop + 4 - judge_timer) / 4;
                if (box[ny][nx + 1].goal_flg == true)
                {
                    player.spos.x += 1;
                }
                else
                {
                    player.spos.x += 1;
                    if (player.exist == TRUE) {
                        kasoku_dead1(&player);
                    }
                    player.spos.x += 1;
                }
                spos_count_skipflg = false;
            }

            //}
            if (judge_timer == judge_loop) {
                //kasoku_dead1(&player);
                if (box[ny][nx + 1].goal_flg == true) {
                    player.pos.x += 1;
                }
                else {
                    player.pos.x += 2;
                }

                dead_check2(&player);
                ground_check(&player);
                d_ground_check(&player);
                if (player.exist == true) {
                    if (tutorial_check == false) {
                        step_count += 2;
                    }
                }
            }
            break;

        case 3: //mix
            if (spos_count_jumpskipflg == true)
            {
                if (box[ny][nx + 1].goal_flg == true) {
                    player.spos.x += 1;
                }
                else {
                    player.spos.x += 1;
                    mix_dead1(&player);
                    player.spos.x += 1;
                }
                player.skip_timer = 5;
                spos_count_jumpskipflg = false;
            }

            //}
            if (judge_timer == judge_loop)
            {
                //mix_dead1(&player);
                player.pos.y -= 1;
                dead_check(&player);

                if (box[ny][nx + 1].goal_flg == true)
                {
                    player.pos.x += 1;
                }
                else
                {
                    player.pos.x += 2;
                }

                dead_check2(&player);
                ground_check(&player);
                d_ground_check(&player);

                if (player.exist == true)
                {
                    if (tutorial_check == false)
                    {
                        step_count += 2;
                    }
                }
            }
            break;
        }
    }
	player.pos_after = player.pos.x;

	if (judge_timer == judge_loop) 
	{
		player.distance = float(player.pos_after) - float(player.pos_before);
		player.distance = player.distance*BOX_SIZE_X / (judge_loop + 2);
	}

	player.draw_pos.x = (player.pos.x) * BOX_SIZE_X;
	player.draw_pos.y = player.pos.y * (BOX_SIZE_Y - BOX_FIX);

	player.draw_pos.x += (speed.x * BOX_SIZE_X);

	block_draw_pos_x += player.distance;

	player.anime = judge_timer / PL_ANIME;
	player.jump_anime = judge_timer / PL_ANIME;

	if (judge_timer == 0) {
		player.dash_anime = 0;
	}

	if (player.dash_anime >= 0) {
		player.dash_anime = judge_timer / 2;
		if (player.dash_anime > 7) {
			player.dash_anime = -1;
		}
	}
	//if (judge_timer == JUDGE_LOOP) {
	if (player_state_check() == 0) { //normal
		if (speed.x < BOX_SIZE_X * player.spos.x) {
			speed.x += 56;
			if (speed.x >= BOX_SIZE_X * player.spos.x)
				speed.x = BOX_SIZE_X * player.spos.x;
		}
	}
	//}

	//if (judge_timer >= 26 && judge_timer <= 30) {//ジャンプ
    else if (player_state_check() == 1) {
        if (speed.y >(BOX_SIZE_Y - BOX_FIX) * player.spos.y) {
            speed.y -= 40;
            if (speed.y <= (BOX_SIZE_Y - BOX_FIX) * player.spos.y) {
                speed.y = (BOX_SIZE_Y - BOX_FIX) * player.spos.y;
            }
        }
        if (speed.x < BOX_SIZE_X * player.spos.x) {
            speed.x += 150;
            if (speed.x >= BOX_SIZE_X * player.spos.x) {
                speed.x = BOX_SIZE_X * player.spos.x;
            }
        }
    }

	//if (judge_timer >= 56 && judge_timer <= 60) { //加速
    else if (player_state_check() == 2) {
        if (speed.x < BOX_SIZE_X * (player.spos.x)) {
            speed.x += 25;
            if (speed.x >= BOX_SIZE_X * (player.spos.x)) {
                speed.x = BOX_SIZE_X * (player.spos.x);
                if (player.exist == TRUE) {
                    kasoku_dead1(&player);
                }
            }
        }

    }

	//if (judge_timer >= 56 && judge_timer <= 60) {
    else if (player_state_check() == 3) {
        if (speed.x < BOX_SIZE_X * player.spos.x) {
            speed.x += 50;
            if (speed.x >= BOX_SIZE_X * player.spos.x) {
                speed.x = BOX_SIZE_X * player.spos.x;
                mix_dead1(&player);
            }
        }
    }
}

//--------------------------------
// 描画処理
//--------------------------------
void player_draw()
{

	/*if (player.dash_anime >= 0) {
		DrawGraphF((player.draw_pos.x - block_draw_pos_x + START_FIX_X) - 200, (player.draw_pos.y + PL_FIX_Y - GROUND_FIX) + 38, Dash_Handle[player.dash_anime], TRUE);
	}*/
	// TODO:25 自機が存在しないならリターン
	//if (player.exist == FALSE) return;
	// 自機を描画する
	//描画座標,画像座標,画像の幅高さ,画像番号,透明処理フラグ,横反転フラグ,縦反転フラグ    
	if (player.exist == TRUE) {
		switch (player_state_check()) {
		case 0: DrawGraphF(speed.x - block_draw_pos_x + START_FIX_X + PL_FIX_X, player.spos.y*(BOX_SIZE_Y - BOX_FIX) + speed.y - GROUND_FIX + PL_FIX_Y, PlHandle[player.anime], TRUE); break;
		case 1: DrawGraphF(speed.x - block_draw_pos_x + START_FIX_X + PL_FIX_X, player.spos.y*(BOX_SIZE_Y - BOX_FIX) + speed.y - GROUND_FIX + PL_FIX_Y, PlHandle[player.anime], TRUE);
			if (judge_timer <= 30)DrawGraphF(speed.x - block_draw_pos_x + START_FIX_X + PL_FIX_X, player.spos.y*(BOX_SIZE_Y - BOX_FIX) + speed.y - GROUND_FIX + PL_FIX_Y, rocketHandle[player.jump_timer / rocket_fix % 4], TRUE); break;
		case 2: DrawGraphF(speed.x - block_draw_pos_x + START_FIX_X + PL_FIX_X, player.spos.y*(BOX_SIZE_Y - BOX_FIX) + speed.y - GROUND_FIX + PL_FIX_Y, PlHandle[player.jump_anime], TRUE);
			if (judge_timer <= 60)DrawGraphF(speed.x - block_draw_pos_x + START_FIX_X + PL_FIX_X, player.spos.y*(BOX_SIZE_Y - BOX_FIX) + speed.y - GROUND_FIX + PL_FIX_Y, rocketHandle[player.skip_timer / rocket_fix % 4 + 4], TRUE); break;
		case 3: DrawGraphF(speed.x - block_draw_pos_x + START_FIX_X + PL_FIX_X, player.spos.y*(BOX_SIZE_Y - BOX_FIX) + speed.y - GROUND_FIX + PL_FIX_Y, PlHandle[player.jump_anime], TRUE);
			if (judge_timer <= 60)DrawGraphF(speed.x - block_draw_pos_x + START_FIX_X + PL_FIX_X, player.spos.y*(BOX_SIZE_Y - BOX_FIX) + speed.y - GROUND_FIX + PL_FIX_Y, rocketHandle[player.skip_timer / rocket_fix % 4 + 4], TRUE); break;
		}
	}

	for (int y = AREA_Y - 1; y >= 0; y--) {
		for (int x = 0; x < AREA_X; x++) {
			switch (box[y][x].type) {
			case 4:DrawGraphF((x * BOX_SIZE_X) - block_draw_pos_x + START_FIX_X, (y * (BOX_SIZE_Y - BOX_FIX)) - GROUND_FIX, GrHandle[ground_timer / 5 % 8 + 32], TRUE); break;
			case 12:DrawGraphF(x * BOX_SIZE_X - block_draw_pos_x + START_FIX_X, y * (BOX_SIZE_Y - BOX_FIX) - GROUND_FIX, GrHandle[0], TRUE); break;
			}
		}
	}
	
    if (player.exist == FALSE)
    {
        DrawGraph(player.dead_pos.x* BOX_SIZE_X - block_draw_pos_x + START_FIX_X + 13, player.dead_pos.y*(BOX_SIZE_Y - BOX_FIX) - 15, dead[ground_timer / 5 % 4], 1);
    }

	/*DrawFormatString(0, 20, (255, 255, 255), L"%f", speed.x);
	if (player.exist == FALSE)
		DrawFormatString(0, 40, (255, 255, 255), L"%d", 1);*/
}


//--------------------------------
// 死亡判定
//--------------------------------
void dead_check(OBJ2D *player) { //めり込み
    int x = player->pos.x;
    int y = player->pos.y;

    switch (box[y][x].type) {
    case 1:
        player->dead_pos.x = player->pos.x;
        player->dead_pos.y = player->pos.y;
        break;
    case 2:
        player->dead_pos.x = player->pos.x;
        player->dead_pos.y = player->pos.y - 1;
        break;
    case 3:
        player->dead_pos.x = player->pos.x;
        player->dead_pos.y = player->pos.y;
        break;
    case 4:
        player->dead_pos.x = player->pos.x;
        player->dead_pos.y = player->pos.y;
        break;
    case 11:
        player->dead_pos.x = player->pos.x;
        player->dead_pos.y = player->pos.y;
        break;
    case 12:
        player->dead_pos.x = player->pos.x;
        player->dead_pos.y = player->pos.y;
        break;

    }
    if (box[y][x].type != 0 && box[y][x].type != 10) {
        player->exist = FALSE;
    }
}

void dead_check2(OBJ2D *player) { //加速用
    int x = player->pos.x;
    int y = player->pos.y;

    if (box[y][x - 1].type != 0 && box[y][x - 1].type != 10) {
        player->exist = FALSE;
    }
}

int goal_check(OBJ2D player) {
    int x = player.pos.x;
    int y = player.pos.y;
    if (box[y][x].goal_flg == true) {
        return 1;
    }
    return 0;
}

void dead_pos(OBJ2D *player) {
    switch (player->state2) {
    case 0:
        if (player->exist == false)
            player->state2++;
        break;
    case 1:
        player->dead_pos.x = player->pos.x;
        player->dead_pos.y = player->pos.y;
        player->state2++;
        break;
    case 2:
        break;
    }
}


void normal_dead1(OBJ2D *player) {
    int x = player->spos.x;
    int y = player->spos.y;

    switch (box[y][x].type) {
    case 1:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 2:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 3:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 4:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 11:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 12:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;

    }
    if (box[y][x].type != 0 && box[y][x].type != 10) {
        player->exist = FALSE;
    }
}

void jump_dead1(OBJ2D *player) {
    int x = player->spos.x;
    int y = player->spos.y;

    switch (box[y][x].type) {
    case 4:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    }

    if (box[y][x].type != 0 && box[y][x].type != 10) {
        player->exist = FALSE;
    }
}

void jump_dead2(OBJ2D *player) {
    int x = player->spos.x;
    int y = player->spos.y;

    switch (box[y][x].type) {
    case 1:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 2:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 3:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 4:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 11:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 12:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;

    }
    if (box[y][x].type != 0 && box[y][x].type != 10) {
        player->exist = FALSE;
    }
}

void kasoku_dead1(OBJ2D *player) {
    int x = player->spos.x;
    int y = player->spos.y;

    switch (box[y][x].type) {
    case 1:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 2:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 3:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 4:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 11:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 12:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;

    }
    if (box[y][x].type != 0 && box[y][x].type != 10) {
        player->exist = FALSE;
    }
}

void mix_dead1(OBJ2D *player) {
    int x = player->spos.x;
    int y = player->spos.y;

    switch (box[y][x].type) {
    case 1:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 2:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 3:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 4:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 11:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;
    case 12:
        player->dead_pos.x = player->spos.x;
        player->dead_pos.y = player->spos.y;
        break;

    }
    if (box[y][x].type != 0 && box[y][x].type != 10) {
        player->exist = FALSE;
    }
}