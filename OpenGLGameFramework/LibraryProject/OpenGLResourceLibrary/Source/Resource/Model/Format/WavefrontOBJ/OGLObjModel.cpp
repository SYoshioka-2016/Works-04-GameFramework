//==================================================================================================================================
// �C���N���[�h
//==================================================================================================================================

#ifndef _INCLUDE_GUARD_OGLOBJMODEL_H_
#include "OGLObjModel.h"
#endif	// #ifndef _INCLUDE_GUARD_OGLOBJMODEL_H_

#ifndef _INCLUDE_GUARD_MATERIAL_H_
#include "../../Base/Material.h"
#endif	// #ifndef _INCLUDE_GUARD_MATERIAL_H_

#ifndef _INCLUDE_GUARD_MESH_H_
#include "../../Base/Mesh.h"
#endif	// #ifndef _INCLUDE_GUARD_MESH_H_

#ifndef _INCLUDE_GUARD_GL_H_
#define _INCLUDE_GUARD_GL_H_
#include <gl/GL.h>
#endif	// #ifndef _INCLUDE_GUARD_GL_H_



//==================================================================================================================================
// using�f�B���N�e�B�u
//==================================================================================================================================

// ���\�[�X���O���
using namespace NS_Resource;

// ���f�����O���
using namespace NS_Model;

// �e�N�X�`�����O���
using namespace NS_Texture;



//==================================================================================================================================
// �֐���`
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �R���X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLObjModel::OGLObjModel()
{
	
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �f�X�g���N�^
//
// @note : 
//
//----------------------------------------------------------------------------------------------------------------------------------
OGLObjModel::~OGLObjModel() 
{
	// ���b�V�����폜
	SAFE_DELETE( m_pMesh );



	// �}�e���A���f�[�^���N���A
	for each ( auto material in m_MaterialData ) 
	{
		SAFE_DELETE( material.second );
	}
	m_MaterialData.clear();
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : ���f���̓ǂݍ���
//
// @param [in] / const char* pcFileName : OBJ�t�H�[�}�b�g�t�@�C����
//
// @return / HRESULT : ���f���̓ǂݍ��݂ɐ���������
//	
// @note : 
//
// OBJ�t�H�[�}�b�g�t�@�C������f�[�^�̓ǂݍ��ݏ������s���B
//----------------------------------------------------------------------------------------------------------------------------------
HRESULT OGLObjModel::Load( const char* pcFileName ) 
{
	// ���b�V�����L��Ώ������Ȃ�
	if ( POINTER_CHECK( m_pMesh ) ) 
	{
		DEBUG_CONSOLE_LOG( "���ɓǂݍ��܂�Ă��܂��B" );

		return S_OK;
	}



	// �t�@�C�����J��
	FILE* pFile = nullptr;
	if ( fopen_s( &pFile, pcFileName, "rt" ) != 0 ) 
	{
		DEBUG_CONSOLE_LOG( "obj�t�@�C���̃t�@�C���I�[�v���Ɏ��s���܂����B" );

		return E_FAIL;
	}



	// ������ۑ��p
	char		strBuffer[ 256 ]		= { 0 };

	// �}�e���A�����ۑ��p
	char		strMaterialName[ 256 ]	= { 0 };

	// �x�N�g���ۑ��p
	Vector3DF	vec3Buffer;



	// ���b�V���𐶐�����
	m_pMesh = new MESH;

	

	// �t�@�C���|�C���^�̈ʒu���t�@�C���̐擪�Ɉړ�����
	fseek( pFile, SEEK_SET, 0 );

	// �t�@�C������f�[�^��ǂݍ���
	while ( !feof( pFile ) ) 
	{
		// �t�@�C������1�s( �L�[���[�h )�ǂݍ���
		ZeroMemory( strBuffer, sizeof(strBuffer) );
		fscanf_s( pFile, "%s ", strBuffer, sizeof(strBuffer) );



		// �}�e���A���t�@�C����ǂݍ���
		if ( strcmp( strBuffer, "mtllib" ) == 0 ) 
		{ 
			// �}�e���A���t�@�C������ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( pFile, "%s ", strBuffer, sizeof(strBuffer) );

			// �}�e���A���t�@�C�����Ƀf�B���N�g�����q�����킹��
			char fullPath[ 256 ] = "";
			strcpy_s( fullPath, GetFileDirectory( pcFileName ).c_str() );
			strcat_s( fullPath, strBuffer );

			// �}�e���A���t�@�C����ǂݍ���
			LoadMaterial( fullPath );
		}

		// ���_���W��ǂݍ���
		if ( strcmp( strBuffer, "v" ) == 0 ) 
		{ 
			// ���_���W��ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( pFile, "%f %f %f", &vec3Buffer.x, &vec3Buffer.y, &vec3Buffer.z );

			 m_pMesh->vertexPositionData.push_back( vec3Buffer );
		}

		// �@����ǂݍ���
		if ( strcmp( strBuffer, "vn" ) == 0 ) 
		{
			// �@����ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( pFile, "%f %f %f", &vec3Buffer.x, &vec3Buffer.y, &vec3Buffer.z );
			
			m_pMesh->normalData.push_back( vec3Buffer );
		}

		// �e�N�X�`�����W��ǂݍ���
		if ( strcmp( strBuffer, "vt" ) == 0 ) 
		{ 	
			// �e�N�X�`�����W��ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( pFile, "%f %f", &vec3Buffer.x, &vec3Buffer.y );

			// obj�t�@�C����y�������t�Ȃ̂ō��킹��
			m_pMesh->texCoordData.push_back( Vector2DF( vec3Buffer.x, 1 - vec3Buffer.y ) );
		}	

		// �}�e���A������ǂݍ���
		if ( strcmp( strBuffer, "usemtl" ) == 0 ) 
		{
			// �}�e���A������ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( pFile, "%s ", strMaterialName, sizeof(strMaterialName) );
		}

		// �C���f�b�N�X��ǂݍ���
		if ( strcmp( strBuffer, "f" ) == 0 ) 
		{ 
			// ���_���W�C���f�b�N�X�ۑ��p
			Vector3DI	ivec3VertexPositionIndex;
			
			// �e�N�X�`�����W�C���f�b�N�X�ۑ��p
			Vector3DI	ivec3TexcoordIndex;
			
			// �@���C���f�b�N�X�ۑ��p
			Vector3DI	ivec3NormalIndex;

			// �C���f�b�N�X�̃|�C���^
			Vector3DI* pivec3Index		= nullptr;
	
			// �}�e���A���Q�Ɨp
			MATERIAL*	pMaterial		= nullptr;



			// ���݂̃}�e���A�����Q�Ƃ���
			try 
			{
				pMaterial = m_MaterialData.at( strMaterialName );
			}
//			catch ( std::exception &e ) { }
			catch ( ... ) { }



			// �C���f�b�N�X��ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( 
				pFile, "%d/%d/%d %d/%d/%d %d/%d/%d", 
				&ivec3VertexPositionIndex.x, &ivec3TexcoordIndex.x, &ivec3NormalIndex.x, 
				&ivec3VertexPositionIndex.y, &ivec3TexcoordIndex.y, &ivec3NormalIndex.y, 
				&ivec3VertexPositionIndex.z, &ivec3TexcoordIndex.z, &ivec3NormalIndex.z 
			);



			// �ۑ����钸�_���W�C���f�b�N�X�𒲐�
			pivec3Index		= new Vector3DI;
			*pivec3Index	= ivec3VertexPositionIndex - Vector3DI( 1, 1, 1 );

			// ���_���W�C���f�b�N�X�f�[�^�ɃC���f�b�N�X��ۑ�����
			m_pMesh->vertexPositionIndexData.insert( std::pair<std::string, Vector3DI*>( strMaterialName, pivec3Index ) );

			// ���݂̃}�e���A�����L��΁A���̃}�e���A���ɃC���f�b�N�X��ۑ�����
			if ( POINTER_CHECK( pMaterial ) ) 
			{
				pMaterial->vertexPositionIndexData.push_back( pivec3Index );
			}


			
			// �ۑ�����e�N�X�`�����W�C���f�b�N�X�𒲐�
			pivec3Index		= new Vector3DI;
			*pivec3Index	= ivec3TexcoordIndex - Vector3DI( 1, 1, 1 );
			
			// �e�N�X�`�����W�C���f�b�N�X�f�[�^�ɃC���f�b�N�X��ۑ�����
			m_pMesh->texcoordIndexData.insert( std::pair<std::string, Vector3DI*>( strMaterialName, pivec3Index ) );
			
			// ���݂̃}�e���A�����L��΁A���̃}�e���A���ɃC���f�b�N�X��ۑ�����
			if ( POINTER_CHECK( pMaterial ) ) 
			{
				pMaterial->texcoordIndexData.push_back( pivec3Index );
			}


						
			// �ۑ�����@�����W�C���f�b�N�X�𒲐�
			pivec3Index		= new Vector3DI;
			*pivec3Index	= ivec3NormalIndex - Vector3DI( 1, 1, 1 );
			
			// �@���C���f�b�N�X�f�[�^�ɃC���f�b�N�X��ۑ�����
			m_pMesh->normalIndexData.insert( std::pair<std::string, Vector3DI*>( strMaterialName, pivec3Index ) );
			
			// ���݂̃}�e���A�����L��΁A���̃}�e���A���ɃC���f�b�N�X��ۑ�����
			if ( POINTER_CHECK( pMaterial ) ) 
			{
				pMaterial->normalIndexData.push_back( pivec3Index );
			}
		}
	}



	// �t�@�C�������
	if ( POINTER_CHECK( pFile ) ) { fclose( pFile ); }



	return S_OK;
}



//----------------------------------------------------------------------------------------------------------------------------------
// @purpose : �}�e���A���̓ǂݍ���
//
// @param [in] / const char* pcFileName : mtl�t�H�[�}�b�g�t�@�C����
//
// @return / HRESULT : �}�e���A���̓ǂݍ��݂ɐ���������
//	
// @note : 
//
// mtl�t�H�[�}�b�g�t�@�C������}�e���A���̓ǂݍ��ݏ������s���B
//----------------------------------------------------------------------------------------------------------------------------------
HRESULT OGLObjModel::LoadMaterial( const char* pcFileName ) 
{
	// �t�@�C�����J��
	FILE* pFile = nullptr;
	if ( fopen_s( &pFile, pcFileName, "rt" ) != 0 ) 
	{
		DEBUG_CONSOLE_LOG( "mtl�t�@�C���̃t�@�C���I�[�v���Ɏ��s���܂����B" );

		return E_FAIL;
	}
	


	// ������ۑ��p
	char		strBuffer[ 256 ]	= { 0 };

	// �x�N�g���ۑ��p
	Vector4DF	vec4Buffer;

	// �}�e���A���ۑ��p
	MATERIAL*	pMaterial			= nullptr;



	// �t�@�C���|�C���^�̈ʒu���t�@�C���̐擪�Ɉړ�����
	fseek( pFile, SEEK_SET, 0 );

	// �t�@�C������f�[�^��ǂݍ���
	while ( !feof( pFile ) ) 
	{
		// �t�@�C������1�s( �L�[���[�h )�ǂݍ���
		ZeroMemory( strBuffer, sizeof(strBuffer) );
		fscanf_s( pFile, "%s ", strBuffer, sizeof(strBuffer) );



		// �}�e���A������ǂݍ���
		if ( strcmp( strBuffer, "newmtl" ) == 0 ) 
		{ 
			// ���Ƀ}�e���A������������Ă���Εۑ����Ă���
			if ( POINTER_CHECK( pMaterial ) ) 
			{ 
				m_MaterialData.insert( std::pair<std::string, MATERIAL*>( pMaterial->strMaterialName, pMaterial ) ); 
			}



			// �}�e���A���𐶐�
			pMaterial = new MATERIAL;

			// �}�e���A������ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( pFile, "%s ", strBuffer, sizeof(strBuffer) );
			pMaterial->strMaterialName = strBuffer;
		}

		// �A���r�G���g��ǂݍ���
		if ( strcmp( strBuffer, "Ka" ) == 0 ) 
		{
			// �A���r�G���g��ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( pFile, "%f %f %f", &vec4Buffer.x, &vec4Buffer.y, &vec4Buffer.z );

			if ( POINTER_CHECK( pMaterial ) ) { pMaterial->vec4Ambient = vec4Buffer; }
		}

		// �f�B�t���[�Y��ǂݍ���
		if ( strcmp( strBuffer, "Kd" ) == 0 ) 
		{
			// �f�B�t���[�Y��ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( pFile, "%f %f %f", &vec4Buffer.x, &vec4Buffer.y, &vec4Buffer.z );

			if ( POINTER_CHECK( pMaterial ) ) { pMaterial->vec4Diffuse = vec4Buffer; }
		}

		// �X�y�L������ǂݍ���
		if ( strcmp( strBuffer, "Ks" ) == 0 ) 
		{
			// �X�y�L������ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( pFile, "%f %f %f", &vec4Buffer.x, &vec4Buffer.y, &vec4Buffer.z );

			if ( POINTER_CHECK( pMaterial ) ) { pMaterial->vec4Specular = vec4Buffer; }
		}

		// ���ʔ��˂̋�����ǂݍ���
		if ( strcmp( strBuffer, "Ns" ) == 0 ) 
		{
			// ���ʔ��˂̋�����ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( pFile, "%f", &vec4Buffer.x );

			if ( POINTER_CHECK( pMaterial ) ) { pMaterial->fShininess = vec4Buffer.x; }
		}

		// �e�N�X�`����ǂݍ���
		if ( strcmp( strBuffer, "map_Kd" ) == 0 ) 
		{
			// �e�N�X�`������ǂݍ���Ńo�b�t�@�ɕۑ�
			fscanf_s( pFile, "%s ", strBuffer, sizeof(strBuffer) );
			
			// �e�N�X�`�����Ƀf�B���N�g�����q�����킹��
			char fullPath[ 256 ] = "";
			strcpy_s( fullPath, GetFileDirectory( pcFileName ).c_str() );
			strcat_s( fullPath, strBuffer );

			// �e�N�X�`����ǂݍ���
			if ( POINTER_CHECK( pMaterial ) )
			{
				pMaterial->uiTextureResourceID = LoadTexture( fullPath );
			}
/*
			// �e�N�X�`������ۑ�����
			if ( POINTER_CHECK( pMaterial ) ) 
			{ 
				pMaterial->strTextureName = fullPath;
			}
*/
		}
	}

	// �t�@�C�������
	if ( POINTER_CHECK( pFile ) ) { fclose( pFile ); }



	// �}�e���A������������Ă���Εۑ����Ă���
	if ( POINTER_CHECK( pMaterial ) ) 
	{ 
		m_MaterialData.insert( std::pair<std::string, MATERIAL*>( pMaterial->strMaterialName, pMaterial ) ); 

		pMaterial = nullptr;
	}



	return S_OK;
}