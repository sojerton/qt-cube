#ifndef VECTORS_H
#define VECTORS_H
#include "vertex.h"

// Front Verticies
#define VERTEX_FTR Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_FTL Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_FBL Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_FBR Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
// Back Verticies
#define VERTEX_BTR Vertex( QVector3D( 0.5f,  0.5f, -1.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_BTL Vertex( QVector3D(-0.5f,  0.5f, -1.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_BBL Vertex( QVector3D(-0.5f, -0.5f, -1.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )
#define VERTEX_BBR Vertex( QVector3D( 0.5f, -0.5f, -1.5f), QVector3D( 0.3f, 0.3f, 0.3f ) )

// Front Primitive
#define PRIM_FTR Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_FTL Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_FBL Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_FBR Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
// Back Primitive
#define PRIM_BTR Vertex( QVector3D( 0.5f,  0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_BTL Vertex( QVector3D(-0.5f,  0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_BBL Vertex( QVector3D(-0.5f, -0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )
#define PRIM_BBR Vertex( QVector3D( 0.5f, -0.5f, -1.5f), QVector3D( 1.3f, 0.3f, 0.3f ) )

// Serifs long
#define ONE Vertex( QVector3D(0.5f,  0.5f,  0.5f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define N_ONE Vertex( QVector3D(0.55f,  0.5f,  0.5f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define TWO Vertex( QVector3D(0.5f,  0.5f,  0.3f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define N_TWO Vertex( QVector3D(0.55f,  0.5f,  0.3f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define THREE Vertex( QVector3D(0.5f,  0.5f,  0.1f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_THREE Vertex( QVector3D(0.55f,  0.5f,  0.1f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define FOUR Vertex( QVector3D(0.5f,  0.5f,  -0.1f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_FOUR Vertex( QVector3D(0.55f,  0.5f,  -0.1f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define FIVE Vertex( QVector3D(0.5f,  0.5f,  -0.3f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_FIVE Vertex( QVector3D(0.55f,  0.5f,  -0.3f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define SIX Vertex( QVector3D(0.5f,  0.5f,  -0.5f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_SIX Vertex( QVector3D(0.55f,  0.5f,  -0.5f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define SEVEN Vertex( QVector3D(0.5f,  0.5f,  -0.7f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_SEVEN Vertex( QVector3D(0.55f,  0.5f,  -0.7f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define EIGHN Vertex( QVector3D(0.5f,  0.5f,  -0.9f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_EIGHN Vertex( QVector3D(0.55f,  0.5f,  -0.9f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define NINE Vertex( QVector3D(0.5f,  0.5f,  -1.1f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_NINE Vertex( QVector3D(0.55f,  0.5f,  -1.1f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define TEN Vertex( QVector3D(0.5f,  0.5f,  -1.3f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_TEN Vertex( QVector3D(0.55f,  0.5f,  -1.3f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define LOOP Vertex( QVector3D(0.5f,  0.5f,  -1.5f), QVector3D( 0.0f, 1.0f, 0.0f )  )
#define N_LOOP Vertex( QVector3D(0.55f,  0.5f,  -1.5f), QVector3D( 0.0f, 1.0f, 0.0f )  )

// Create serifs
Vertex sg_vertexes_serif[] = {
    ONE, N_ONE, TWO, N_TWO, THREE, N_THREE,
    FOUR, N_FOUR, FIVE, N_FIVE, SIX, N_SIX,
    SEVEN, N_SEVEN, EIGHN, N_EIGHN, NINE, N_NINE,
    TEN, N_TEN, LOOP, N_LOOP
};

Vertex initSerif(){
    Vertex* longserif = new Vertex[22*8];
    for(unsigned int i=0; i<10; i++){
        float x_count, z_count = 0.5f;
        if(i%2==0) x_count = 0.5f;
        else x_count = 0.55f;
        longserif[i].setPosition(QVector3D(x_count,  0.5f,  z_count));
        longserif[i].setColor(QVector3D(0.0f, 1.0f, 0.0f));
        if(i%2!=0) z_count -= 0.2f;
    }
    return *longserif;
}

// Create figure
static const Vertex sg_vertexes[] = {
  // Face 1 (Front)
    VERTEX_FTR, VERTEX_FTL, VERTEX_FBL,
    VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
  // Face 2 (Back)
    VERTEX_BBR, VERTEX_BTL, VERTEX_BTR,
    VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
  // Face 3 (Top)
    VERTEX_FTR, VERTEX_BTR, VERTEX_BTL,
    VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
  // Face 4 (Bottom)
    VERTEX_FBR, VERTEX_FBL, VERTEX_BBL,
    VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
  // Face 5 (Left)
    VERTEX_FBL, VERTEX_FTL, VERTEX_BTL,
    VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
  // Face 6 (Right)
    VERTEX_FTR, VERTEX_FBR, VERTEX_BBR,
    VERTEX_BBR, VERTEX_BTR, VERTEX_FTR
};
// Create primitive
static const Vertex sg_vertexes_prim[] = {
    PRIM_FTR, PRIM_FTL, PRIM_FBL,
    PRIM_FBR, PRIM_FTR, PRIM_BTR,
    PRIM_BTL, PRIM_FTL, PRIM_BTL,
    PRIM_BBL, PRIM_FBL, PRIM_BBL,
    PRIM_BBR, PRIM_FBR, PRIM_BBR,
    PRIM_BTR
};

#undef ONE
#undef N_ONE
#undef TWO
#undef N_TWO
#undef THREE
#undef N_THREE
#undef FOUR
#undef N_FOUR
#undef FIVE
#undef N_FIVE
#undef SIX
#undef N_SIX
#undef SEVEN
#undef N_SEVEN
#undef EIGHN
#undef N_EIGHN
#undef NINE
#undef N_NINE
#undef TEN
#undef N_TEN
#undef LOOP
#undef N_LOOP

#undef PRIM_BBR
#undef PRIM_BBL
#undef PRIM_BTL
#undef PRIM_BTR
#undef PRIM_FBR
#undef PRIM_FBL
#undef PRIM_FTL
#undef PRIM_FTR

#undef VERTEX_BBR
#undef VERTEX_BBL
#undef VERTEX_BTL
#undef VERTEX_BTR
#undef VERTEX_FBR
#undef VERTEX_FBL
#undef VERTEX_FTL
#undef VERTEX_FTR



#endif // VECTORS_H
