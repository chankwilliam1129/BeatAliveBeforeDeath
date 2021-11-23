#ifndef INCLUDED_JUDGE
#define INCLUDED_JUDGE

//******************************************************************************
//
//
//      common.h
//
//
//******************************************************************************

//------< 定数 >----------------------------------------------------------------
#define RUN (0)
#define JUMP (1)
#define SKIP (2)
#define JUMPSKIP (3)
#define JUDGE_LOOP (60)

//プロトタイプ宣言
void Timing_Judge();
int player_state_check();
void TimingInit();
#endif

