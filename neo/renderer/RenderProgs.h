/*
===========================================================================

Doom 3 BFG Edition GPL Source Code
Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
Copyright (C) 2013-2023 Robert Beckebans
Copyright (C) 2016-2017 Dustin Land
Copyright (C) 2022 Stephen Pridham

This file is part of the Doom 3 BFG Edition GPL Source Code ("Doom 3 BFG Edition Source Code").

Doom 3 BFG Edition Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 BFG Edition Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 BFG Edition Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 BFG Edition Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 BFG Edition Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/
#ifndef __RENDERPROGS_H__
#define __RENDERPROGS_H__


static const int PC_ATTRIB_INDEX_VERTEX		= 0;
static const int PC_ATTRIB_INDEX_NORMAL		= 2;
static const int PC_ATTRIB_INDEX_COLOR		= 3;
static const int PC_ATTRIB_INDEX_COLOR2		= 4;
static const int PC_ATTRIB_INDEX_ST			= 8;
static const int PC_ATTRIB_INDEX_TANGENT	= 9;


/*
================================================
vertexMask_t

NOTE: There is a PS3 dependency between the bit flag specified here and the vertex
attribute index and attribute semantic specified in DeclRenderProg.cpp because the
stored render prog vertexMask is initialized with cellCgbGetVertexConfiguration().
The ATTRIB_INDEX_ defines are used to make sure the vertexMask_t and attrib assignment
in DeclRenderProg.cpp are in sync.

Even though VERTEX_MASK_XYZ_SHORT and VERTEX_MASK_ST_SHORT are not real attributes,
they come before the VERTEX_MASK_MORPH to reduce the range of vertex program
permutations defined by the vertexMask_t bits on the Xbox 360 (see MAX_VERTEX_DECLARATIONS).
================================================
*/
enum vertexMask_t
{
	VERTEX_MASK_XYZ			= BIT( PC_ATTRIB_INDEX_VERTEX ),
	VERTEX_MASK_ST			= BIT( PC_ATTRIB_INDEX_ST ),
	VERTEX_MASK_NORMAL		= BIT( PC_ATTRIB_INDEX_NORMAL ),
	VERTEX_MASK_COLOR		= BIT( PC_ATTRIB_INDEX_COLOR ),
	VERTEX_MASK_TANGENT		= BIT( PC_ATTRIB_INDEX_TANGENT ),
	VERTEX_MASK_COLOR2		= BIT( PC_ATTRIB_INDEX_COLOR2 ),
};



// This enum list corresponds to the global constant register indecies as defined in global.inc for all
// shaders.  We used a shared pool to keeps things simple.  If something changes here then it also
// needs to change in global.inc and vice versa
enum renderParm_t
{
	// For backwards compatibility, do not change the order of the first 17 items
	RENDERPARM_SCREENCORRECTIONFACTOR = 0,
	RENDERPARM_WINDOWCOORD,
	RENDERPARM_DIFFUSEMODIFIER,
	RENDERPARM_SPECULARMODIFIER,

	RENDERPARM_LOCALLIGHTORIGIN,
	RENDERPARM_LOCALVIEWORIGIN,

	RENDERPARM_LIGHTPROJECTION_S,
	RENDERPARM_LIGHTPROJECTION_T,
	RENDERPARM_LIGHTPROJECTION_Q,
	RENDERPARM_LIGHTFALLOFF_S,

	RENDERPARM_BUMPMATRIX_S,
	RENDERPARM_BUMPMATRIX_T,

	RENDERPARM_DIFFUSEMATRIX_S,
	RENDERPARM_DIFFUSEMATRIX_T,

	RENDERPARM_SPECULARMATRIX_S,
	RENDERPARM_SPECULARMATRIX_T,

	RENDERPARM_VERTEXCOLOR_MODULATE,
	RENDERPARM_VERTEXCOLOR_ADD,

	// The following are new and can be in any order

	RENDERPARM_COLOR,
	RENDERPARM_VIEWORIGIN,
	RENDERPARM_GLOBALEYEPOS,

	RENDERPARM_MVPMATRIX_X,
	RENDERPARM_MVPMATRIX_Y,
	RENDERPARM_MVPMATRIX_Z,
	RENDERPARM_MVPMATRIX_W,

	RENDERPARM_MODELMATRIX_X,
	RENDERPARM_MODELMATRIX_Y,
	RENDERPARM_MODELMATRIX_Z,
	RENDERPARM_MODELMATRIX_W,

	RENDERPARM_PROJMATRIX_X,
	RENDERPARM_PROJMATRIX_Y,
	RENDERPARM_PROJMATRIX_Z,
	RENDERPARM_PROJMATRIX_W,

	RENDERPARM_MODELVIEWMATRIX_X,
	RENDERPARM_MODELVIEWMATRIX_Y,
	RENDERPARM_MODELVIEWMATRIX_Z,
	RENDERPARM_MODELVIEWMATRIX_W,

	RENDERPARM_TEXTUREMATRIX_S,
	RENDERPARM_TEXTUREMATRIX_T,

	RENDERPARM_TEXGEN_0_S,
	RENDERPARM_TEXGEN_0_T,
	RENDERPARM_TEXGEN_0_Q,
	RENDERPARM_TEXGEN_0_ENABLED,

	RENDERPARM_TEXGEN_1_S,
	RENDERPARM_TEXGEN_1_T,
	RENDERPARM_TEXGEN_1_Q,
	RENDERPARM_TEXGEN_1_ENABLED,

	RENDERPARM_WOBBLESKY_X,
	RENDERPARM_WOBBLESKY_Y,
	RENDERPARM_WOBBLESKY_Z,

	RENDERPARM_OVERBRIGHT,
	RENDERPARM_ENABLE_SKINNING,
	RENDERPARM_ALPHA_TEST,

	// RB begin
	RENDERPARM_AMBIENT_COLOR,

	RENDERPARM_GLOBALLIGHTORIGIN,
	RENDERPARM_JITTERTEXSCALE,
	RENDERPARM_JITTERTEXOFFSET,

	RENDERPARM_PSX_DISTORTIONS,

	RENDERPARM_CASCADEDISTANCES,

	RENDERPARM_SHADOW_MATRIX_0_X,	// rpShadowMatrices[6 * 4]
	RENDERPARM_SHADOW_MATRIX_0_Y,
	RENDERPARM_SHADOW_MATRIX_0_Z,
	RENDERPARM_SHADOW_MATRIX_0_W,

	RENDERPARM_SHADOW_MATRIX_1_X,
	RENDERPARM_SHADOW_MATRIX_1_Y,
	RENDERPARM_SHADOW_MATRIX_1_Z,
	RENDERPARM_SHADOW_MATRIX_1_W,

	RENDERPARM_SHADOW_MATRIX_2_X,
	RENDERPARM_SHADOW_MATRIX_2_Y,
	RENDERPARM_SHADOW_MATRIX_2_Z,
	RENDERPARM_SHADOW_MATRIX_2_W,

	RENDERPARM_SHADOW_MATRIX_3_X,
	RENDERPARM_SHADOW_MATRIX_3_Y,
	RENDERPARM_SHADOW_MATRIX_3_Z,
	RENDERPARM_SHADOW_MATRIX_3_W,

	RENDERPARM_SHADOW_MATRIX_4_X,
	RENDERPARM_SHADOW_MATRIX_4_Y,
	RENDERPARM_SHADOW_MATRIX_4_Z,
	RENDERPARM_SHADOW_MATRIX_4_W,

	RENDERPARM_SHADOW_MATRIX_5_X,
	RENDERPARM_SHADOW_MATRIX_5_Y,
	RENDERPARM_SHADOW_MATRIX_5_Z,
	RENDERPARM_SHADOW_MATRIX_5_W,

	RENDERPARM_SHADOW_ATLAS_OFFSET_0,	// rpShadowAtlasOffsets[6]
	RENDERPARM_SHADOW_ATLAS_OFFSET_1,
	RENDERPARM_SHADOW_ATLAS_OFFSET_2,
	RENDERPARM_SHADOW_ATLAS_OFFSET_3,
	RENDERPARM_SHADOW_ATLAS_OFFSET_4,
	RENDERPARM_SHADOW_ATLAS_OFFSET_5,

	RENDERPARM_USER0,
	RENDERPARM_USER1,
	RENDERPARM_USER2,
	RENDERPARM_USER3,
	RENDERPARM_USER4,
	RENDERPARM_USER5,
	RENDERPARM_USER6,
	RENDERPARM_USER7,
	// RB end

	RENDERPARM_TOTAL,
};

enum rpStage_t
{
	SHADER_STAGE_VERTEX		= BIT( 0 ),
	SHADER_STAGE_FRAGMENT	= BIT( 1 ),
	SHADER_STAGE_COMPUTE	= BIT( 2 ), // RB: for future use

	SHADER_STAGE_DEFAULT	= SHADER_STAGE_VERTEX | SHADER_STAGE_FRAGMENT
};

enum rpBinding_t
{
	BINDING_TYPE_UNIFORM_BUFFER,
	BINDING_TYPE_SAMPLER,
	BINDING_TYPE_MAX
};

struct ShaderBlob
{
	void* data = nullptr;
	size_t size = 0;
};

#define VERTEX_UNIFORM_ARRAY_NAME				"_va_"
#define FRAGMENT_UNIFORM_ARRAY_NAME				"_fa_"

static const int AT_VS_IN			= BIT( 1 );
static const int AT_VS_OUT			= BIT( 2 );
static const int AT_PS_IN			= BIT( 3 );
static const int AT_PS_OUT			= BIT( 4 );
static const int AT_VS_OUT_RESERVED = BIT( 5 );
static const int AT_PS_IN_RESERVED	= BIT( 6 );
static const int AT_PS_OUT_RESERVED = BIT( 7 );

struct attribInfo_t
{
	const char* 	type;
	const char* 	name;
	const char* 	semantic;
	const char* 	glsl;
	int				bind;
	int				flags;
	int				vertexMask;
};

extern attribInfo_t attribsPC[];

// Shader macros are used to pick which permutation of a shader to load from a ShaderBlob
// binary file.
struct shaderMacro_t
{
	idStr name;
	idStr definition;

	shaderMacro_t()
		: name()
		, definition()
	{
	}

	shaderMacro_t( const idStr& _name, const idStr& _definition )
		: name( _name )
		, definition( _definition )
	{ }
};

struct programInfo_t
{
	int bindingLayoutType;
	nvrhi::ShaderHandle vs;
	nvrhi::ShaderHandle ps;
	nvrhi::ShaderHandle cs;
	nvrhi::InputLayoutHandle inputLayout;
	idStaticList<nvrhi::BindingLayoutHandle, nvrhi::c_MaxBindingLayouts>* bindingLayouts;
};

enum
{
	BUILTIN_GUI,
	BUILTIN_COLOR,
	// RB begin
	BUILTIN_COLOR_SKINNED,
	BUILTIN_VERTEX_COLOR,

	BUILTIN_AMBIENT_LIGHTING_IBL,
	BUILTIN_AMBIENT_LIGHTING_IBL_SKINNED,
	BUILTIN_AMBIENT_LIGHTING_IBL_PBR,
	BUILTIN_AMBIENT_LIGHTING_IBL_PBR_SKINNED,

	BUILTIN_AMBIENT_LIGHTGRID_IBL,
	BUILTIN_AMBIENT_LIGHTGRID_IBL_SKINNED,
	BUILTIN_AMBIENT_LIGHTGRID_IBL_PBR,
	BUILTIN_AMBIENT_LIGHTGRID_IBL_PBR_SKINNED,

	BUILTIN_SMALL_GEOMETRY_BUFFER,
	BUILTIN_SMALL_GEOMETRY_BUFFER_SKINNED,
	// RB end
	BUILTIN_TEXTURED,
	BUILTIN_TEXTURE_VERTEXCOLOR,
	BUILTIN_TEXTURE_VERTEXCOLOR_SRGB,
	BUILTIN_TEXTURE_VERTEXCOLOR_SKINNED,
	BUILTIN_TEXTURE_TEXGEN_VERTEXCOLOR,

	BUILTIN_INTERACTION,
	BUILTIN_INTERACTION_SKINNED,
	BUILTIN_INTERACTION_AMBIENT,
	BUILTIN_INTERACTION_AMBIENT_SKINNED,

	// RB begin
	BUILTIN_PBR_INTERACTION,
	BUILTIN_PBR_INTERACTION_SKINNED,
	BUILTIN_PBR_INTERACTION_AMBIENT,
	BUILTIN_PBR_INTERACTION_AMBIENT_SKINNED,

	BUILTIN_INTERACTION_SHADOW_MAPPING_SPOT,
	BUILTIN_INTERACTION_SHADOW_MAPPING_SPOT_SKINNED,
	BUILTIN_INTERACTION_SHADOW_MAPPING_POINT,
	BUILTIN_INTERACTION_SHADOW_MAPPING_POINT_SKINNED,
	BUILTIN_INTERACTION_SHADOW_MAPPING_PARALLEL,
	BUILTIN_INTERACTION_SHADOW_MAPPING_PARALLEL_SKINNED,

	BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_SPOT,
	BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_SPOT_SKINNED,
	BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_POINT,
	BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_POINT_SKINNED,
	BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_PARALLEL,
	BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_PARALLEL_SKINNED,

	BUILTIN_INTERACTION_SHADOW_ATLAS_SPOT,
	BUILTIN_INTERACTION_SHADOW_ATLAS_SPOT_SKINNED,
	BUILTIN_INTERACTION_SHADOW_ATLAS_POINT,
	BUILTIN_INTERACTION_SHADOW_ATLAS_POINT_SKINNED,
	BUILTIN_INTERACTION_SHADOW_ATLAS_PARALLEL,
	BUILTIN_INTERACTION_SHADOW_ATLAS_PARALLEL_SKINNED,

	BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_SPOT,
	BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_SPOT_SKINNED,
	BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_POINT,
	BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_POINT_SKINNED,
	BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_PARALLEL,
	BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_PARALLEL_SKINNED,

	BUILTIN_DEBUG_LIGHTGRID,
	BUILTIN_DEBUG_LIGHTGRID_SKINNED,

	BUILTIN_DEBUG_OCTAHEDRON,
	BUILTIN_DEBUG_OCTAHEDRON_SKINNED,
	// RB end

	BUILTIN_ENVIRONMENT,
	BUILTIN_ENVIRONMENT_SKINNED,
	BUILTIN_BUMPY_ENVIRONMENT,
	BUILTIN_BUMPY_ENVIRONMENT_SKINNED,
	BUILTIN_BUMPY_ENVIRONMENT2,				// RB
	BUILTIN_BUMPY_ENVIRONMENT2_SKINNED,		// RB
	BUILTIN_BUMPY_ENVIRONMENT2_SSR,			// RB
	BUILTIN_BUMPY_ENVIRONMENT2_SSR_SKINNED,	// RB

	BUILTIN_DEPTH,
	BUILTIN_DEPTH_SKINNED,

	BUILTIN_BLENDLIGHT,
	BUILTIN_BLENDLIGHT_SKINNED,
	BUILTIN_FOG,
	BUILTIN_FOG_SKINNED,
	BUILTIN_SKYBOX,
	BUILTIN_WOBBLESKY,
	BUILTIN_POSTPROCESS,
	// RB begin
	BUILTIN_POSTPROCESS_RETRO_2BIT,		// CGA, Gameboy, cool for Gamejams
	BUILTIN_POSTPROCESS_RETRO_C64,		// Commodore 64
	BUILTIN_POSTPROCESS_RETRO_CPC,		// Amstrad 6128
	BUILTIN_POSTPROCESS_RETRO_GENESIS,	// Sega Genesis / Megadrive
	BUILTIN_POSTPROCESS_RETRO_PSX,		// Sony Playstation 1
	BUILTIN_CRT_MATTIAS,
	BUILTIN_CRT_NUPIXIE,
	BUILTIN_CRT_EASYMODE,
	BUILTIN_SCREEN,
	BUILTIN_TONEMAP,
	BUILTIN_BRIGHTPASS,
	BUILTIN_HDR_GLARE_CHROMATIC,
	BUILTIN_HDR_DEBUG,

	BUILTIN_SMAA_EDGE_DETECTION,
	BUILTIN_SMAA_BLENDING_WEIGHT_CALCULATION,
	BUILTIN_SMAA_NEIGHBORHOOD_BLENDING,

	BUILTIN_TAA_MOTION_VECTORS,
	BUILTIN_TAA_RESOLVE,
	BUILTIN_TAA_RESOLVE_MSAA_2X,
	BUILTIN_TAA_RESOLVE_MSAA_4X,
	BUILTIN_TAA_RESOLVE_MSAA_8X,

	BUILTIN_AMBIENT_OCCLUSION,
	BUILTIN_AMBIENT_OCCLUSION_AND_OUTPUT,
	BUILTIN_AMBIENT_OCCLUSION_BLUR,
	BUILTIN_AMBIENT_OCCLUSION_BLUR_AND_OUTPUT,

	BUILTIN_DEEP_GBUFFER_RADIOSITY_SSGI,
	BUILTIN_DEEP_GBUFFER_RADIOSITY_BLUR,
	BUILTIN_DEEP_GBUFFER_RADIOSITY_BLUR_AND_OUTPUT,
	// RB end
	BUILTIN_STEREO_DEGHOST,
	BUILTIN_STEREO_WARP,
	BUILTIN_BINK,
	BUILTIN_BINK_SRGB,	// SRS - Added Bink shader without sRGB to linear conversion for testVideo cmd
	BUILTIN_BINK_GUI,
	BUILTIN_STEREO_INTERLACE,
	BUILTIN_MOTION_BLUR,

	BUILTIN_DEBUG_SHADOWMAP,

	// SP Begin
	BUILTIN_BLIT,
	BUILTIN_RECT,
	BUILTIN_TONEMAPPING,
	BUILTIN_TONEMAPPING_TEX_ARRAY,
	BUILTIN_HISTOGRAM_CS,
	BUILTIN_HISTOGRAM_TEX_ARRAY_CS,
	BUILTIN_EXPOSURE_CS,
	// SP End

	MAX_BUILTINS
};

/*
================================================================================================
idRenderProgManager
================================================================================================
*/
class idRenderProgManager
{
public:
	idRenderProgManager();
	virtual ~idRenderProgManager();

	void	Init( nvrhi::IDevice* device );
	void	Shutdown();

	void	StartFrame();

	void	SetRenderParm( renderParm_t rp, const float value[4] );
	void	SetRenderParms( renderParm_t rp, const float values[], int numValues );

	int		FindShader( const char* name, rpStage_t stage );
	int		FindShader( const char* name, rpStage_t stage, const char* nameOutSuffix, uint32 features, bool builtin, vertexLayoutType_t vertexLayout = LAYOUT_DRAW_VERT );
	int		FindShader( const char* name, rpStage_t stage, const char* nameOutSuffix, const idList<shaderMacro_t>& macros, bool builtin, vertexLayoutType_t vertexLayout = LAYOUT_DRAW_VERT );

	nvrhi::ShaderHandle GetShader( int index );

	programInfo_t GetProgramInfo( int index );

	int		CurrentProgram() const
	{
		return currentIndex;
	}

	void	BindProgram( int progIndex );

	void	BindShader_GUI()
	{
		BindShader_Builtin( BUILTIN_GUI );
	}

	void	BindShader_Color()
	{
		BindShader_Builtin( BUILTIN_COLOR );
	}

	// RB begin
	void	BindShader_ColorSkinned()
	{
		BindShader_Builtin( BUILTIN_COLOR_SKINNED );
	}

	void	BindShader_VertexColor()
	{
		BindShader_Builtin( BUILTIN_VERTEX_COLOR );
	}

	void	BindShader_ImageBasedLighting()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_LIGHTING_IBL );
	}

	void	BindShader_ImageBasedLightingSkinned()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_LIGHTING_IBL_SKINNED );
	}

	void	BindShader_ImageBasedLighting_PBR()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_LIGHTING_IBL_PBR );
	}

	void	BindShader_ImageBasedLightingSkinned_PBR()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_LIGHTING_IBL_PBR_SKINNED );
	}


	void	BindShader_ImageBasedLightGrid()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_LIGHTGRID_IBL );
	}

	void	BindShader_ImageBasedLightGridSkinned()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_LIGHTGRID_IBL_SKINNED );
	}

	void	BindShader_ImageBasedLightGrid_PBR()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_LIGHTGRID_IBL_PBR );
	}

	void	BindShader_ImageBasedLightGridSkinned_PBR()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_LIGHTGRID_IBL_PBR_SKINNED );
	}


	void	BindShader_SmallGeometryBuffer()
	{
		BindShader_Builtin( BUILTIN_SMALL_GEOMETRY_BUFFER );
	}

	void	BindShader_SmallGeometryBufferSkinned()
	{
		BindShader_Builtin( BUILTIN_SMALL_GEOMETRY_BUFFER_SKINNED );
	}
	// RB end

	void	BindShader_Texture()
	{
		BindShader_Builtin( BUILTIN_TEXTURED );
	}

	void	BindShader_TextureVertexColor()
	{
		BindShader_Builtin( BUILTIN_TEXTURE_VERTEXCOLOR );
	}

	void	BindShader_TextureVertexColor_sRGB()
	{
		BindShader_Builtin( BUILTIN_TEXTURE_VERTEXCOLOR_SRGB );
	}

	void	BindShader_TextureVertexColorSkinned()
	{
		BindShader_Builtin( BUILTIN_TEXTURE_VERTEXCOLOR_SKINNED );
	}

	void	BindShader_TextureTexGenVertexColor()
	{
		BindShader_Builtin( BUILTIN_TEXTURE_TEXGEN_VERTEXCOLOR );
	}

	void	BindShader_Interaction()
	{
		BindShader_Builtin( BUILTIN_INTERACTION );
	}

	void	BindShader_InteractionSkinned()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SKINNED );
	}

	void	BindShader_InteractionAmbient()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_AMBIENT );
	}

	void	BindShader_InteractionAmbientSkinned()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_AMBIENT_SKINNED );
	}

	// PBR variantes

	void	BindShader_PBR_Interaction()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION );
	}

	void	BindShader_PBR_InteractionSkinned()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SKINNED );
	}

	void	BindShader_PBR_InteractionAmbient()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_AMBIENT );
	}

	void	BindShader_PBR_InteractionAmbientSkinned()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_AMBIENT_SKINNED );
	}

	//
	// regular shadow mapping
	//

	void	BindShader_Interaction_ShadowMapping_Spot()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_MAPPING_SPOT );
	}

	void	BindShader_Interaction_ShadowMapping_Spot_Skinned()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_MAPPING_SPOT_SKINNED );
	}

	void	BindShader_Interaction_ShadowMapping_Point()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_MAPPING_POINT );
	}

	void	BindShader_Interaction_ShadowMapping_Point_Skinned()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_MAPPING_POINT_SKINNED );
	}

	void	BindShader_Interaction_ShadowMapping_Parallel()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_MAPPING_PARALLEL );
	}

	void	BindShader_Interaction_ShadowMapping_Parallel_Skinned()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_MAPPING_PARALLEL_SKINNED );
	}

	void	BindShader_PBR_Interaction_ShadowMapping_Spot()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_SPOT );
	}

	void	BindShader_PBR_Interaction_ShadowMapping_Spot_Skinned()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_SPOT_SKINNED );
	}

	void	BindShader_PBR_Interaction_ShadowMapping_Point()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_POINT );
	}

	void	BindShader_PBR_Interaction_ShadowMapping_Point_Skinned()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_POINT_SKINNED );
	}

	void	BindShader_PBR_Interaction_ShadowMapping_Parallel()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_PARALLEL );
	}

	void	BindShader_PBR_Interaction_ShadowMapping_Parallel_Skinned()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_MAPPING_PARALLEL_SKINNED );
	}

	//
	// shadow mapping using a big atlas
	//

	void	BindShader_Interaction_ShadowAtlas_Spot()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_ATLAS_SPOT );
	}

	void	BindShader_Interaction_ShadowAtlas_Spot_Skinned()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_ATLAS_SPOT_SKINNED );
	}

	void	BindShader_Interaction_ShadowAtlas_Point()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_ATLAS_POINT );
	}

	void	BindShader_Interaction_ShadowAtlas_Point_Skinned()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_ATLAS_POINT_SKINNED );
	}

	void	BindShader_Interaction_ShadowAtlas_Parallel()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_ATLAS_PARALLEL );
	}

	void	BindShader_Interaction_ShadowAtlas_Parallel_Skinned()
	{
		BindShader_Builtin( BUILTIN_INTERACTION_SHADOW_ATLAS_PARALLEL_SKINNED );
	}

	void	BindShader_PBR_Interaction_ShadowAtlas_Spot()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_SPOT );
	}

	void	BindShader_PBR_Interaction_ShadowAtlas_Spot_Skinned()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_SPOT_SKINNED );
	}

	void	BindShader_PBR_Interaction_ShadowAtlas_Point()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_POINT );
	}

	void	BindShader_PBR_Interaction_ShadowAtlas_Point_Skinned()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_POINT_SKINNED );
	}

	void	BindShader_PBR_Interaction_ShadowAtlas_Parallel()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_PARALLEL );
	}

	void	BindShader_PBR_Interaction_ShadowAtlas_Parallel_Skinned()
	{
		BindShader_Builtin( BUILTIN_PBR_INTERACTION_SHADOW_ATLAS_PARALLEL_SKINNED );
	}

	//
	// debug tools
	//

	void	BindShader_DebugLightGrid()
	{
		BindShader_Builtin( BUILTIN_DEBUG_LIGHTGRID );
	}

	void	BindShader_DebugLightGridSkinned()
	{
		BindShader_Builtin( BUILTIN_DEBUG_LIGHTGRID_SKINNED );
	}

	void	BindShader_DebugOctahedron()
	{
		BindShader_Builtin( BUILTIN_DEBUG_OCTAHEDRON );
	}

	void	BindShader_DebugOctahedronSkinned()
	{
		BindShader_Builtin( BUILTIN_DEBUG_OCTAHEDRON_SKINNED );
	}
	// RB end

	void	BindShader_Environment()
	{
		BindShader_Builtin( BUILTIN_ENVIRONMENT );
	}

	void	BindShader_EnvironmentSkinned()
	{
		BindShader_Builtin( BUILTIN_ENVIRONMENT_SKINNED );
	}

	void	BindShader_BumpyEnvironment()
	{
		BindShader_Builtin( BUILTIN_BUMPY_ENVIRONMENT );
	}

	void	BindShader_BumpyEnvironmentSkinned()
	{
		BindShader_Builtin( BUILTIN_BUMPY_ENVIRONMENT_SKINNED );
	}

	void	BindShader_BumpyEnvironment2()
	{
		BindShader_Builtin( BUILTIN_BUMPY_ENVIRONMENT2 );
	}

	void	BindShader_BumpyEnvironment2Skinned()
	{
		BindShader_Builtin( BUILTIN_BUMPY_ENVIRONMENT2_SKINNED );
	}

	void	BindShader_BumpyEnvironment2_SSR()
	{
		BindShader_Builtin( BUILTIN_BUMPY_ENVIRONMENT2_SSR );
	}

	void	BindShader_BumpyEnvironment2_SSR_Skinned()
	{
		BindShader_Builtin( BUILTIN_BUMPY_ENVIRONMENT2_SSR_SKINNED );
	}

	void	BindShader_Depth()
	{
		BindShader_Builtin( BUILTIN_DEPTH );
	}

	void	BindShader_DepthSkinned()
	{
		BindShader_Builtin( BUILTIN_DEPTH_SKINNED );
	}

	void	BindShader_BlendLight()
	{
		BindShader_Builtin( BUILTIN_BLENDLIGHT );
	}

	void	BindShader_Fog()
	{
		BindShader_Builtin( BUILTIN_FOG );
	}

	void	BindShader_FogSkinned()
	{
		BindShader_Builtin( BUILTIN_FOG_SKINNED );
	}

	void	BindShader_SkyBox()
	{
		BindShader_Builtin( BUILTIN_SKYBOX );
	}

	void	BindShader_WobbleSky()
	{
		BindShader_Builtin( BUILTIN_WOBBLESKY );
	}

	void	BindShader_StereoDeGhost()
	{
		BindShader_Builtin( BUILTIN_STEREO_DEGHOST );
	}

	void	BindShader_StereoWarp()
	{
		BindShader_Builtin( BUILTIN_STEREO_WARP );
	}

	void	BindShader_StereoInterlace()
	{
		BindShader_Builtin( BUILTIN_STEREO_INTERLACE );
	}

	void	BindShader_PostProcess()
	{
		BindShader_Builtin( BUILTIN_POSTPROCESS );
	}

	void	BindShader_PostProcess_RetroC64()
	{
		BindShader_Builtin( BUILTIN_POSTPROCESS_RETRO_C64 );
	}

	void	BindShader_PostProcess_RetroCPC()
	{
		BindShader_Builtin( BUILTIN_POSTPROCESS_RETRO_CPC );
	}

	void	BindShader_PostProcess_Retro2Bit()
	{
		BindShader_Builtin( BUILTIN_POSTPROCESS_RETRO_2BIT );
	}

	void	BindShader_PostProcess_RetroGenesis()
	{
		BindShader_Builtin( BUILTIN_POSTPROCESS_RETRO_GENESIS );
	}

	void	BindShader_PostProcess_RetroPSX()
	{
		BindShader_Builtin( BUILTIN_POSTPROCESS_RETRO_PSX );
	}

	void	BindShader_CrtMattias()
	{
		BindShader_Builtin( BUILTIN_CRT_MATTIAS );
	}

	void	BindShader_CrtNewPixie()
	{
		BindShader_Builtin( BUILTIN_CRT_NUPIXIE );
	}

	void	BindShader_CrtEasyMode()
	{
		BindShader_Builtin( BUILTIN_CRT_EASYMODE );
	}

	void	BindShader_Screen()
	{
		BindShader_Builtin( BUILTIN_SCREEN );
	}

	void	BindShader_Tonemap()
	{
		BindShader_Builtin( BUILTIN_TONEMAP );
	}

	void	BindShader_Brightpass()
	{
		BindShader_Builtin( BUILTIN_BRIGHTPASS );
	}

	void	BindShader_HDRGlareChromatic()
	{
		BindShader_Builtin( BUILTIN_HDR_GLARE_CHROMATIC );
	}

	void	BindShader_HDRDebug()
	{
		BindShader_Builtin( BUILTIN_HDR_DEBUG );
	}

	void	BindShader_SMAA_EdgeDetection()
	{
		BindShader_Builtin( BUILTIN_SMAA_EDGE_DETECTION );
	}

	void	BindShader_SMAA_BlendingWeightCalculation()
	{
		BindShader_Builtin( BUILTIN_SMAA_BLENDING_WEIGHT_CALCULATION );
	}

	void	BindShader_SMAA_NeighborhoodBlending()
	{
		BindShader_Builtin( BUILTIN_SMAA_NEIGHBORHOOD_BLENDING );
	}

	void	BindShader_AmbientOcclusion()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_OCCLUSION );
	}

	void	BindShader_AmbientOcclusionAndOutput()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_OCCLUSION_AND_OUTPUT );
	}

	void	BindShader_AmbientOcclusionBlur()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_OCCLUSION_BLUR );
	}

	void	BindShader_AmbientOcclusionBlurAndOutput()
	{
		BindShader_Builtin( BUILTIN_AMBIENT_OCCLUSION_BLUR_AND_OUTPUT );
	}

	void	BindShader_DeepGBufferRadiosity()
	{
		BindShader_Builtin( BUILTIN_DEEP_GBUFFER_RADIOSITY_SSGI );
	}

	void	BindShader_DeepGBufferRadiosityBlur()
	{
		BindShader_Builtin( BUILTIN_DEEP_GBUFFER_RADIOSITY_BLUR );
	}

	void	BindShader_DeepGBufferRadiosityBlurAndOutput()
	{
		BindShader_Builtin( BUILTIN_DEEP_GBUFFER_RADIOSITY_BLUR_AND_OUTPUT );
	}

	void	BindShader_Bink()
	{
		BindShader_Builtin( BUILTIN_BINK );
	}

	void	BindShader_Bink_sRGB()
	{
		BindShader_Builtin( BUILTIN_BINK_SRGB );
	}

	void	BindShader_BinkGUI()
	{
		BindShader_Builtin( BUILTIN_BINK_GUI );
	}

	void	BindShader_MotionBlur()
	{
		BindShader_Builtin( BUILTIN_MOTION_BLUR );
	}

	void	BindShader_MotionVectors()
	{
		BindShader_Builtin( BUILTIN_TAA_MOTION_VECTORS );
	}

	void	BindShader_DebugShadowMap()
	{
		BindShader_Builtin( BUILTIN_DEBUG_SHADOWMAP );
	}
	// RB end

	// the joints buffer should only be bound for vertex programs that use joints
	bool		ShaderUsesJoints() const
	{
		return renderProgs[currentIndex].usesJoints;
	}

	// the rpEnableSkinning render parm should only be set for vertex programs that use it
	bool		ShaderHasOptionalSkinning() const
	{
//#if defined( USE_NVRHI )
		// FIXME
		return false;
//#else
//		return renderProgs[current].optionalSkinning;
//#endif
	}

	// unbind the currently bound render program
	void		Unbind();

	// RB begin
	bool		IsShaderBound() const;
	// RB end

	// this should only be called via the reload shader console command
	void		LoadAllShaders();
	void		KillAllShaders();

	static const int	MAX_GLSL_USER_PARMS = 8;
	const char*	GetGLSLParmName( int rp ) const;

	void		SetUniformValue( const renderParm_t rp, const float value[4] );
	void		CommitUniforms( uint64 stateBits );
	int			FindProgram( const char* name, int vIndex, int fIndex, bindingLayoutType_t bindingType = BINDING_LAYOUT_DEFAULT );
	void		ZeroUniforms();
	int			UniformSize();

	bool									CommitConstantBuffer( nvrhi::ICommandList* commandList, bool bindingLayoutTypeChanged );

	ID_INLINE nvrhi::IBuffer*				ConstantBuffer()
	{
		return constantBuffer;//[BindingLayoutType()];
	}
	ID_INLINE idUniformBuffer&				BindingParamUbo()
	{
		return bindingParmUbo[ BindingLayoutType() ];
	}
	ID_INLINE nvrhi::InputLayoutHandle		InputLayout()
	{
		return renderProgs[currentIndex].inputLayout;
	}
	ID_INLINE int							BindingLayoutType()
	{
		return renderProgs[currentIndex].bindingLayoutType;
	}
	ID_INLINE idStaticList<nvrhi::BindingLayoutHandle, nvrhi::c_MaxBindingLayouts>* GetBindingLayout( int layoutType )
	{
		return &bindingLayouts[layoutType];
	}

	idUniformBuffer									renderParmUbo;
	idArray<idUniformBuffer, NUM_BINDING_LAYOUTS>	bindingParmUbo;
	idArray<idVec4*, NUM_BINDING_LAYOUTS>			mappedRenderParms;

	static const char* FindEmbeddedSourceShader( const char* name );

private:
	void		LoadShader( int index, rpStage_t stage );

	// Reads the binary fileName and returns a ShaderBlob.
	ShaderBlob	GetBytecode( const char* fileName );

	int builtinShaders[MAX_BUILTINS];
	void BindShader_Builtin( int i )
	{
		BindProgram( i );
	}

	void	LoadProgram( const int programIndex, const int vertexShaderIndex, const int fragmentShaderIndex );
	void	LoadComputeProgram( const int programIndex, const int computeShaderIndex );

	static const uint INVALID_PROGID = 0xFFFFFFFF;

	struct shader_t
	{
		shader_t() :
			name(),
			nameOutSuffix(),
			shaderFeatures( 0 ),
			builtin( false ),
			macros(),
			handle( nullptr ),
			stage( SHADER_STAGE_DEFAULT )
		{
		}

		idStr						name;
		idStr						nameOutSuffix;
		uint32						shaderFeatures;
		bool						builtin;
		idList<shaderMacro_t>		macros;
		nvrhi::ShaderHandle			handle;
		rpStage_t					stage;
	};

	struct renderProg_t
	{
		renderProg_t() :
			name(),
			vertexShaderIndex( -1 ),
			fragmentShaderIndex( -1 ),
			computeShaderIndex( -1 ),
			builtin( true ),
			usesJoints( false ),
			vertexLayout( LAYOUT_UNKNOWN ),
			bindingLayoutType( BINDING_LAYOUT_DEFAULT ),
			inputLayout( nullptr ),
			bindingLayouts()
		{
		}

		idStr						name;
		int							vertexShaderIndex;
		int							fragmentShaderIndex;
		int							computeShaderIndex;
		bool						builtin;
		bool						usesJoints;
		vertexLayoutType_t			vertexLayout;
		bindingLayoutType_t			bindingLayoutType;
		nvrhi::InputLayoutHandle	inputLayout;
		idStaticList< nvrhi::BindingLayoutHandle, nvrhi::c_MaxBindingLayouts > bindingLayouts;
	};

	void	LoadShader( shader_t& shader );

	int											currentIndex;
	idList<renderProg_t, TAG_RENDER>			renderProgs;
	idList<shader_t, TAG_RENDER>				shaders;
	idStaticList< idVec4, RENDERPARM_TOTAL >	uniforms;
	bool										uniformsChanged;
	nvrhi::IDevice*								device;

	using VertexAttribDescList = idList< nvrhi::VertexAttributeDesc >;
	idStaticList< VertexAttribDescList, NUM_VERTEX_LAYOUTS > vertexLayoutDescs;

	idStaticList< idStaticList<nvrhi::BindingLayoutHandle, nvrhi::c_MaxBindingLayouts>, NUM_BINDING_LAYOUTS > bindingLayouts;

	//idArray<nvrhi::BufferHandle, NUM_BINDING_LAYOUTS>	constantBuffer;
	nvrhi::BufferHandle							constantBuffer;
};

extern idRenderProgManager renderProgManager;

#endif
