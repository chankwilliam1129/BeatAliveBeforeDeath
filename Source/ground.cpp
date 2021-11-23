// ------< インクルード >-------------------------------------------------------- -
#include "all.h"
#include "time.h"

//------< プロトタイプ宣言 >-----------------------------------------------------

//------< 変数 >----------------------------------------------------------------
float block_draw_pos_x;
bool toge_flg;
bool toge_flg2;
bool j_unable_flg;
bool tutorial3_end = false;
extern int GrHandle[24];
extern OBJ2D player;
Box box[AREA_Y+1][AREA_X];
Box tutorial1[TUTORIAL1_Y][TUTORIAL1_X];
int height;
int type;
extern int tutorial_restart;
extern int GoalHandle[8];
extern int ground_timer;
extern int point[8];
extern int explain_state;
//--------------------------------
// groundのランダム生成
//--------------------------------
void ground_init() {
	for (int y = 0; y < AREA_Y + 1; y++) {
		for (int x = 0; x < AREA_X; x++) {
			box[y][x].type = 0;
			box[y][x].ground_flg = false;
			box[y][x].height = 0;
			box[y][x].goal_flg = false;
		}
	}
	int rand_object = 0;
	srand((unsigned int)time(NULL));
	box[AREA_Y + 1][AREA_X] = { NULL };
	//始めの５マス
	for (int x = 0; x < 5; x++) {
		box[AREA_Y - 1][x].ground_flg = true;
		box[AREA_Y - 1][x].type = 1; //ブロック
	}

	//6マス以降
	for (int x = 5; x < AREA_X; x++) {
		height = rand() % 3;
		rand_object = rand() % 3;
		switch (rand_object) {
		case 0: //toge
			for (int y1 = AREA_Y - 1 + 1 - height; y1 >= 0; y1--) {
				if (box[y1][x - 1].ground_flg == true && box[AREA_Y - 1 - height][x].type != 10) {
					box[AREA_Y - 1 - height][x].type = 2;
					for (int y = AREA_Y - 1 - height + 1; y <= AREA_Y; y++) {
						box[y][x].type = 11;
					}
					break;
				}
			}
			if (box[AREA_Y - 1 - height][x].type != 2) {
				x--;
				continue;
			}
			break;
		case 1://ジャンプ禁止
			if (box[AREA_Y - 1 - height - 1][x].type != 10 && box[AREA_Y - 1 - height][x - 1].type != 10) {
				if ((box[AREA_Y - 1 - height][x - 1].ground_flg == true || box[AREA_Y - 1 - height + 1][x - 1].ground_flg == true || box[AREA_Y - 1 - height + 1][x - 2].ground_flg == true ||
					box[AREA_Y - 1 - height][x - 2].ground_flg == true) && box[AREA_Y - 1 - height - 1][x - 1].type == 0) {
					box[AREA_Y - 1 - height][x].type = 3;
					box[AREA_Y - 1 - height - 2][x].type = 4;
					box[AREA_Y - 1 - height - 1][x + 1].type = 10;
					box[AREA_Y - 1 - height][x].ground_flg = true;
					for (int y = AREA_Y - 1 - height - 3; y >= 0; y--) {
						box[y][x].type = 12;
					}
					for (int y = AREA_Y - 1 - height + 1; y <= AREA_Y; y++) {
						box[y][x].type = 11;
					}
					break;
				}
			}
			if (box[AREA_Y - 1 - height - 1][x].type != 3) {
				x--;
				continue;
			}
			break;

		default://ブロック
			for (int y2 = AREA_Y - 1 - height + 1; y2 <= AREA_Y; y2++) {
				if (box[AREA_Y - 1 - height][x - 1].type != 10 && box[y2][x - 1].type != 2) {
					for (int y1 = AREA_Y - 1 - height + 1; y1 >= 0; y1--) {
						if ((box[y1][x - 1].ground_flg == true || box[y1][x - 2].ground_flg == true) && box[AREA_Y - 1 - height][x].type != 10) {
							box[AREA_Y - 1 - height][x].type = 1;
							box[AREA_Y - 1 - height][x].ground_flg = true;
							for (int y = AREA_Y - 1 - height + 1; y <= AREA_Y; y++) {
								box[y][x].type = 11;
							}
							break;
						}
					}
				}
			}
			if (box[AREA_Y - 1 - height][x].type != 1) {
				x--;
				continue;
			}
			break;
		}
	}


}
//--------------------------------
// 今のgroundの位置
//--------------------------------
void ground_check(OBJ2D *player) {
    int x, y;
    while (1) {
        int x = player->pos.x;
        int y = player->pos.y;

        if (box[y + 1][x].ground_flg == FALSE && player->exist == TRUE) {
            dead_check(player);
            if (player->exist == FALSE) {
                break;
            }
            player->pos.y += 1;
        }
        else {
            break;
        }
    }
}
//--------------------------------
// チュートリアル　ステージ１
//--------------------------------
void Tutorial_1_init() {
	tutorial_restart = 1;
	for (int y = 0; y < AREA_Y + 1; y++) {
		for (int x = 0; x < AREA_X; x++) {
			box[y][x].ground_flg = false;
			box[y][x].type = 0;
			box[y][x].goal_flg = false;
			box[y][x].next_light = false;
			box[y][x].next_Red_light = false;
		}
	}
	for (int y = 0; y < TUTORIAL1_Y; y++) {
		for (int x = 0; x < TUTORIAL1_X; x++) {
			box[y][x].type = 0;
			box[y][x].ground_flg = false;
		}
	}

	for (int x = 0; x < TUTORIAL1_X - TUTORIAL1_FIX; x++) {
		box[6][x].type = 1;
		box[6][x].ground_flg = true;
	}

	for (int x = TUTORIAL1_X - TUTORIAL1_FIX; x < TUTORIAL1_X; x++) {
		if (x == TUTORIAL1_X - TUTORIAL1_FIX + 1 || x == TUTORIAL1_X - TUTORIAL1_FIX + 3 || x == TUTORIAL1_X - TUTORIAL1_FIX + 5 || x == TUTORIAL1_X - TUTORIAL1_FIX + 6 || x == TUTORIAL1_X - TUTORIAL1_FIX + 7) {
			box[6][x].type = 11;
		}
		else {
			box[6][x].type = 1;
			box[6][x].ground_flg = true;
		}
	}

	for (int x = TUTORIAL1_X - TUTORIAL1_FIX; x < TUTORIAL1_X; x++) {
		if (x == TUTORIAL1_X - TUTORIAL1_FIX + 1 || x == TUTORIAL1_X - TUTORIAL1_FIX + 3 || x == TUTORIAL1_X - TUTORIAL1_FIX + 5) {
			box[5][x].type = 1;
			box[5][x].ground_flg = true;
		}
		if (x == TUTORIAL1_X - TUTORIAL1_FIX + 6 || x == TUTORIAL1_X - TUTORIAL1_FIX + 7) {
			box[5][x].type = 11;
		}
	}
	box[4][TUTORIAL1_X - TUTORIAL1_FIX + 6].type = 1;
	box[4][TUTORIAL1_X - TUTORIAL1_FIX + 6].ground_flg = true;
	box[4][TUTORIAL1_X - TUTORIAL1_FIX + 7].type = 11;

	box[3][TUTORIAL1_X - TUTORIAL1_FIX + 7].type = 1;
	box[3][TUTORIAL1_X - TUTORIAL1_FIX + 7].ground_flg = true;

	box[5][TUTORIAL1_X - TUTORIAL1_FIX + 9].goal_flg = true;
}
//--------------------------------
// チュートリアル　ステージ2
//--------------------------------
void Tutorial_2_init() {
	//初期設定
	tutorial_restart = 2;
	for (int y = 0; y < AREA_Y + 1; y++) {
		for (int x = 0; x < AREA_X; x++) {
			box[y][x].ground_flg = false;
			box[y][x].type = 0;
			box[y][x].goal_flg = false;
			box[y][x].next_light = false;
			box[y][x].next_Red_light = false;
		}
	}
	box[5][12].goal_flg = false;
	for (int y = 0; y < TUTORIAL2_Y; y++) {
		for (int x = 0; x < TUTORIAL2_X; x++) {
			box[6][x].ground_flg = false;
			box[y][x].type = 0;
		}
	}

	for (int x = 0; x < TUTORIAL2_X - TUTORIAL2_FIX; x++) {
		box[6][x].type = 1;
		box[6][x].ground_flg = true;
	}

	for (int x = TUTORIAL2_X - TUTORIAL2_FIX; x < TUTORIAL2_X; x++) {
		if (x == TUTORIAL2_X - TUTORIAL2_FIX + 1 || x == TUTORIAL2_X - TUTORIAL2_FIX + 3 || x == TUTORIAL2_X - TUTORIAL2_FIX + 5) {
			box[6][x].type = 2;
		}
		else if (x == TUTORIAL2_X - TUTORIAL2_FIX + 0 || x == TUTORIAL2_X - TUTORIAL2_FIX + 2 || x == TUTORIAL2_X - TUTORIAL2_FIX + 4) {
			box[6][x].type = 3;//ジャンプ禁止
			box[6][x].ground_flg = true;
			box[4][x].type = 4;
			box[3][x].type = 12;
			box[2][x].type = 12;
			box[1][x].type = 12;
			box[0][x].type = 12;
		}
		else {
			box[6][x].type = 1;
			box[6][x].ground_flg = true;
		}
	}

	box[5][12].goal_flg = true;
}

//--------------------------------
// チュートリアル　ステージ3
//--------------------------------

void Tutorial_3_init() {
	tutorial_restart = 3;

	for (int y = 0; y < AREA_Y + 1; y++) {
		for (int x = 0; x < AREA_X; x++) {
			box[y][x].ground_flg = false;
			box[y][x].type = 0;
			box[y][x].goal_flg = false;
			box[y][x].next_light = false;
			box[y][x].next_Red_light = false;
		}
	}
	for (int y = 0; y < TUTORIAL3_Y; y++) {
		for (int x = 0; x < TUTORIAL3_X; x++) {
			box[6][x].ground_flg = false;
			box[y][x].type = 0;
		}
	}

	for (int x = 0; x < TUTORIAL3_X - TUTORIAL3_FIX; x++) {
		box[6][x].type = 1;
		box[6][x].ground_flg = true;
	}
	for (int x = TUTORIAL3_X - TUTORIAL3_FIX; x < TUTORIAL3_X; x++) {
		if (x == TUTORIAL3_X - TUTORIAL3_FIX + 0 || x == TUTORIAL3_X - TUTORIAL3_FIX + 3 || x == TUTORIAL3_X - TUTORIAL3_FIX + 6 || x == TUTORIAL3_X - TUTORIAL3_FIX + 9 || x == TUTORIAL3_X - TUTORIAL3_FIX + 9 || x == TUTORIAL3_X - TUTORIAL3_FIX + 12 || x == TUTORIAL3_X - TUTORIAL3_FIX + 14 || x == TUTORIAL3_X - TUTORIAL3_FIX + 15) {
			box[6][x].type = 1;
			box[6][x].ground_flg = true;
		}
		else if (x == TUTORIAL3_X - TUTORIAL3_FIX + 1 || x == TUTORIAL3_X - TUTORIAL3_FIX + 4 || x == TUTORIAL3_X - TUTORIAL3_FIX + 7 || x == TUTORIAL3_X - TUTORIAL3_FIX + 10) {
			box[6][x].type = 2;
		}
		else {
			box[6][x].type = 11;
		}

		if (x == TUTORIAL3_X - TUTORIAL3_FIX + 2 || x == TUTORIAL3_X - TUTORIAL3_FIX + 5 || x == TUTORIAL3_X - TUTORIAL3_FIX + 8 || x == TUTORIAL3_X - TUTORIAL3_FIX + 11) {
			box[5][x].type = 1;
			box[5][x].ground_flg = true;
		}
	}
	box[5][TUTORIAL3_X - TUTORIAL3_FIX + 13].type = 11;
	box[4][TUTORIAL3_X - TUTORIAL3_FIX + 13].type = 1;
	box[4][TUTORIAL3_X - TUTORIAL3_FIX + 13].ground_flg = true;

	box[5][TUTORIAL3_X - TUTORIAL3_FIX + 15].goal_flg = true;
}


//--------------------------------
// 描画処理
//--------------------------------
void ground_draw() {
	for (int y = AREA_Y - 1; y >= 0; y--) {
		for (int x = 0; x < AREA_X; x++) {
			switch (box[y][x].type) {
			case 1:DrawGraphF(x * BOX_SIZE_X - block_draw_pos_x + START_FIX_X, y * (BOX_SIZE_Y - BOX_FIX) - GROUND_FIX, GrHandle[ground_timer / 5 % 8 + 8] , TRUE); break;
			case 2:DrawGraphF((x * BOX_SIZE_X) - block_draw_pos_x + START_FIX_X, (y * (BOX_SIZE_Y - BOX_FIX)) - GROUND_FIX, GrHandle[ground_timer / 5 % 8 + 16], TRUE); break;
			case 3:DrawGraphF((x * BOX_SIZE_X) - block_draw_pos_x + START_FIX_X, (y * (BOX_SIZE_Y - BOX_FIX)) - GROUND_FIX, GrHandle[ground_timer / 5 % 8 + 24], TRUE); break;
			//case 4:DrawGraphF((x * BOX_SIZE_X) - block_draw_pos_x + START_FIX_X, (y * (BOX_SIZE_Y - BOX_FIX)) - GROUND_FIX, GrHandle[32], TRUE); break;
			case 11:DrawGraphF(x * BOX_SIZE_X - block_draw_pos_x + START_FIX_X, y * (BOX_SIZE_Y - BOX_FIX) - GROUND_FIX, GrHandle[0], TRUE); break;
			}
		}
	}

	for (int y = AREA_Y - 1; y >= 0; y--) {
		for (int x = 0; x < AREA_X; x++) {
			if (box[y][x].goal_flg == true) {
				DrawGraphF(x * BOX_SIZE_X - block_draw_pos_x + START_FIX_X, y * (BOX_SIZE_Y - BOX_FIX - 5) - GROUND_FIX, GoalHandle[ground_timer / 4 % 8], TRUE);
				if (ground_timer / 4 % 8 - 2 >= 0) {
					DrawGraphF(x * BOX_SIZE_X - block_draw_pos_x + START_FIX_X, y * (BOX_SIZE_Y - BOX_FIX - 5) - GROUND_FIX, GoalHandle[ground_timer / 4 % 8 - 2], TRUE);
				}
			}
            if (player.exist == TRUE) {
                if (box[y][x].next_light == true) {
                    DrawGraphF(x * BOX_SIZE_X - block_draw_pos_x + START_FIX_X, (y + 1) *(BOX_SIZE_Y - BOX_FIX) - GROUND_FIX, point[ground_timer / 6 % 4 + 4], TRUE);
                }
                if (box[y][x].next_Red_light == true) {
                    DrawGraphF(x * BOX_SIZE_X - block_draw_pos_x + START_FIX_X, (y + 1) * (BOX_SIZE_Y - BOX_FIX) - GROUND_FIX, point[ground_timer / 6 % 4], TRUE);
                }
            }
		}
	}
	if (tutorial_restart == 1 && explain_state == 2)
	{
		DrawGraphF(BOX_SIZE_X - block_draw_pos_x + START_FIX_X, 6 * (BOX_SIZE_Y - BOX_FIX) - GROUND_FIX, point[ground_timer / 6 % 4 + 4], TRUE);
	}

	if (tutorial_restart == 1 && explain_state == 3)
	{
		DrawGraphF(BOX_SIZE_X - block_draw_pos_x + START_FIX_X, 6*(BOX_SIZE_Y - BOX_FIX) - GROUND_FIX, point[ground_timer / 6 % 4 ], TRUE);
	}
}
void d_ground_check(OBJ2D *player) {
    while (1) {
        int x = player->spos.x;
        int y = player->spos.y;

        if (box[y + 1][x].ground_flg == FALSE && player->exist == TRUE) {
            dead_check(player);
            if (player->exist == FALSE) {
                break;
            }
            player->spos.y += 1;
        }
        else {
            break;
        }
    }
}