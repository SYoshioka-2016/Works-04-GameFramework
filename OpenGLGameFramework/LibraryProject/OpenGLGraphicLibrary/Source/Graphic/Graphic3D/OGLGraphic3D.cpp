//==================================================================================================================================
// インクルード
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_OGLGRAPHIC3D_H_
#include "OGLGraphic3D.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLGRAPHIC3D_H_

#ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_
#include <OpenGLResourceLib.h>
#endif	// #ifndef _INCLUDE_GUARD_OPENGLRESOURCELIB_H_

#ifndef _INCLUDE_GUARD_GL_H_
#define _INCLUDE_GUARD_GL_H_
#include <gl/GL.h>
#endif	// #ifndef _INCLUDE_GUARD_GL_H_



//==================================================================================================================================
// 関数定義
//==================================================================================================================================



extern void NS_Graphic::NS_Graphic3D::DrawLine( 
	const float			fLineWidth,
	const Vector3DF&	vec3Start,
	const Vector3DF&	vec3End
)
{
	glLineWidth( fLineWidth );

	glBegin( GL_LINES );
	{
		glVertex3fv( (GLfloat*)&vec3Start );

		glVertex3fv( (GLfloat*)&vec3End );
	}
	glEnd();
}



extern void NS_Graphic::NS_Graphic3D::DrawLines( 
	const float						fLineWidth,
	const std::vector<Vector3DF>&	points
)
{
	for ( int i = 0; i < (int)points.size() - 1; i += 2 ) 
	{
		DrawLine( fLineWidth, points.at( i ), points.at( i + 1 ) );
	}
}



extern void NS_Graphic::NS_Graphic3D::DrawWireTriangle(
	const float			fLineWidth,
	const Vector3DF&	vec3Vertex1,
	const Vector3DF&	vec3Vertex2,
	const Vector3DF&	vec3Vertex3
)
{
	glLineWidth( fLineWidth );

	glBegin( GL_LINE_STRIP );
	{
		glVertex3fv( (GLfloat*)&vec3Vertex1 );

		glVertex3fv( (GLfloat*)&vec3Vertex2 );

		glVertex3fv( (GLfloat*)&vec3Vertex3 );
		
		glVertex3fv( (GLfloat*)&vec3Vertex1 );
	}
	glEnd();
}



extern void NS_Graphic::NS_Graphic3D::DrawWireTriangles( 
	const float						fLineWidth,
	const std::vector<Vector3DF>&	points
)
{
	for ( int i = 0; i < (int)points.size() - 2; i += 3 ) 
	{
		DrawWireTriangle( fLineWidth, points.at( i ), points.at( i + 1 ), points.at( i + 2 ) );
	}
}