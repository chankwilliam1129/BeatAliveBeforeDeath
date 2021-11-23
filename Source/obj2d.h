#ifndef INCLUDED_OBJ2D
#define INCLUDED_OBJ2D

struct OBJ2D {
	
	VECTOR texPos;         // 画像位置
	VECTOR texSize;        // 画像サイズ
	VECTOR texPivot;       // 画像の基準点
	int     anime;          // アニメーション用（仮）
	int anime2;
	int jump_anime;
	int     type;           // タイプ
	int       hp;
	BOOL    exist;          // 存在フラグ

	// 汎用的なもの
	VECTOR pos;            // 位置
	VECTOR scale;          // スケール
	float   angle;          // 角度
	VECTOR color;          // 色（xyzwそれぞれrgba）
	float   radius;         // 半径
	int     state;          // 状態遷移用
	int     timer;          // タイマー
    int jump_timer;
    int skip_timer;
	VECTOR speed;          // 速度
	int     cnt;            // 汎用カウンタ（使い方は自由）
	BOOL    hostilityFg;    // 敵フラグ（今回から追加）

    int pos_number;
	VECTOR draw_pos;
	int pos_before;
	int pos_after;
	float distance;
	int dash_anime;
	VECTOR spos;
	int skip_anime;
	int GRAVITY;
	float FRICTION;
	bool dead_flg;
	int state2;
	VECTOR dead_pos;
};
struct Box {
	int number;
	int type;
	int height;
	bool ground_flg; //地面
	bool ground_flg2;
	bool goal_flg; //clear
	bool next_light;
	bool next_Red_light;
};

#endif // !INCLUDED_SCENE_GAME