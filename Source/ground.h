#ifndef INCLUDED_GROUND
#define INCLUDED_GROUND

//******************************************************************************
//
//
//     
//
//
//******************************************************************************
//------< 定数 >----------------------------------------------------------------
#define AREA_X        (1000)
#define AREA_Y        (7)
#define BOX_SIZE_X    (112)
#define BOX_SIZE_Y    (160)
#define BOX_FIX       (63)
#define GROUND_FIX    (80)

#define TUTORIAL1_X   (10 + 3)
#define TUTORIAL1_Y   (7)
#define TUTORIAL1_FIX (10)

#define TUTORIAL2_X   (8 + 5)
#define TUTORIAL2_Y   (7)
#define TUTORIAL2_FIX (8)

#define TUTORIAL3_X   (16 + 3)
#define TUTORIAL3_Y   (7)
#define TUTORIAL3_FIX (16)

//------< プロトタイプ宣言 >-----------------------------------------------------
void ground_init();
void ground_check(OBJ2D*);
void dead_check(OBJ2D*);
void dead_check2(OBJ2D*);
void d_ground_check(OBJ2D*);
void ground_draw();
void Tutorial_1_init();
void Tutorial_2_init();
void Tutorial_3_init();
void tutorial_explain();

#endif // !INCLUDED_BG

