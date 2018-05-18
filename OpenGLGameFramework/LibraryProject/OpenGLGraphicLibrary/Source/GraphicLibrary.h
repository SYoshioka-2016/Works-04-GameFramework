#ifndef _INCLUDE_GUARD_GRAPHICLIBRARY_H_
#define _INCLUDE_GUARD_GRAPHICLIBRARY_H_



//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_OGLGRAPHIC_H_
#include "Graphic/OGLGraphic.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLGRAPHIC_H_

#ifndef _INCLUDE_GUARD_GRAPHICMATHEMATICS_H_
#include "Graphic/Math/GraphicMathematics.h"
#endif	// #ifndef _INCLUDE_GUARD_GRAPHICMATHEMATICS_H_

#ifndef _INCLUDE_GUARD_OGLGRAPHIC2D_H_
#include "../Source/Graphic/Graphic2D/OGLGraphic2D.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLGRAPHIC2D_H_

#ifndef _INCLUDE_GUARD_OGLGRAPHIC3D_H_
#include "../Source/Graphic/Graphic3D/OGLGraphic3D.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLGRAPHIC3D_H_

#ifndef _INCLUDE_GUARD_GLUT_H_
#define _INCLUDE_GUARD_GLUT_H_
#include "../Include/GL/glut.h"
#endif	// #ifndef _INCLUDE_GUARD_GLUT_H_



//==================================================================================================================================
// ライブラリリンク
//==================================================================================================================================
#pragma comment ( lib, "OpenGL32.lib" )
#pragma comment ( lib, "glut32.lib" )
#pragma comment ( lib, "OpenGLGraphicLibrary.lib" )



#endif	// #ifndef _INCLUDE_GUARD_GRAPHICLIBRARY_H_