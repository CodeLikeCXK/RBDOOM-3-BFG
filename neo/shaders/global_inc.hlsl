/*
===========================================================================

Doom 3 BFG Edition GPL Source Code
Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
Copyright (C) 2013-2024 Robert Beckebans

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

#include "vulkan.hlsli"

// *INDENT-OFF*
cbuffer globals : register( b0 VK_DESCRIPTOR_SET( 0 ) )
{
	float4 rpScreenCorrectionFactor;
	float4 rpWindowCoord;
	float4 rpDiffuseModifier;
	float4 rpSpecularModifier;

	float4 rpLocalLightOrigin;
	float4 rpLocalViewOrigin;

	float4 rpLightProjectionS;
	float4 rpLightProjectionT;
	float4 rpLightProjectionQ;
	float4 rpLightFalloffS;

	float4 rpBumpMatrixS;
	float4 rpBumpMatrixT;

	float4 rpDiffuseMatrixS;
	float4 rpDiffuseMatrixT;

	float4 rpSpecularMatrixS;
	float4 rpSpecularMatrixT;

	float4 rpVertexColorModulate;
	float4 rpVertexColorAdd;

	float4 rpColor;
	float4 rpViewOrigin;
	float4 rpGlobalEyePos;

	float4 rpMVPmatrixX;
	float4 rpMVPmatrixY;
	float4 rpMVPmatrixZ;
	float4 rpMVPmatrixW;

	float4 rpModelMatrixX;
	float4 rpModelMatrixY;
	float4 rpModelMatrixZ;
	float4 rpModelMatrixW;

	float4 rpProjectionMatrixX;
	float4 rpProjectionMatrixY;
	float4 rpProjectionMatrixZ;
	float4 rpProjectionMatrixW;

	float4 rpModelViewMatrixX;
	float4 rpModelViewMatrixY;
	float4 rpModelViewMatrixZ;
	float4 rpModelViewMatrixW;

	float4 rpTextureMatrixS;
	float4 rpTextureMatrixT;

	float4 rpTexGen0S;
	float4 rpTexGen0T;
	float4 rpTexGen0Q;
	float4 rpTexGen0Enabled;

	float4 rpTexGen1S;
	float4 rpTexGen1T;
	float4 rpTexGen1Q;
	float4 rpTexGen1Enabled;

	float4 rpWobbleSkyX;
	float4 rpWobbleSkyY;
	float4 rpWobbleSkyZ;

	float4 rpOverbright;
	float4 rpEnableSkinning;
	float4 rpAlphaTest;

	// RB begin
	float4 rpAmbientColor;
	float4 rpGlobalLightOrigin;
	float4 rpJitterTexScale;
	float4 rpJitterTexOffset;
	float4 rpPSXDistortions;
	float4 rpCascadeDistances;

	float4 rpShadowMatrices[6 * 4];
	float4 rpShadowAtlasOffsets[6];
	// RB end

	float4 rpUser0;
	float4 rpUser1;
	float4 rpUser2;
	float4 rpUser3;
	float4 rpUser4;
	float4 rpUser5;
	float4 rpUser6;
	float4 rpUser7;
};

// *INDENT-ON*

static float dot2( float2 a, float2 b )
{
	return dot( a, b );
}
static float dot3( float3 a, float3 b )
{
	return dot( a, b );
}
static float dot3( float3 a, float4 b )
{
	return dot( a, b.xyz );
}
static float dot3( float4 a, float3 b )
{
	return dot( a.xyz, b );
}
static float dot3( float4 a, float4 b )
{
	return dot( a.xyz, b.xyz );
}
static float dot4( float4 a, float4 b )
{
	return dot( a, b );
}
static float dot4( float2 a, float4 b )
{
	return dot( float4( a, 0, 1 ), b );
}

// RB begin
#ifndef PI
	#define PI	3.14159265358979323846
#endif

#define DEG2RAD( a )				( ( a ) * PI / 180.0f )
#define RAD2DEG( a )				( ( a ) * 180.0f / PI )

// RB: the golden ratio is useful to animate Blue noise
#define c_goldenRatioConjugate 0.61803398875

static const float DOOM_TO_METERS = 0.0254;					// doom to meters
static const float METERS_TO_DOOM = ( 1.0 / DOOM_TO_METERS );	// meters to doom

// ----------------------
// sRGB <-> Linear RGB Color Conversion
// ----------------------

float Linear1( float c )
{
	return ( c <= 0.04045 ) ? c / 12.92 : pow( ( c + 0.055 ) / 1.055, 2.4 );
}

float3 Linear3( float3 c )
{
	return float3( Linear1( c.r ), Linear1( c.g ), Linear1( c.b ) );
}

float Srgb1( float c )
{
	return ( c < 0.0031308 ? c * 12.92 : 1.055 * pow( c, 0.41666 ) - 0.055 );
}

float3 Srgb3( float3 c )
{
	return float3( Srgb1( c.r ), Srgb1( c.g ), Srgb1( c.b ) );
}

static const float3 photoLuma = float3( 0.2126, 0.7152, 0.0722 );
float PhotoLuma( float3 c )
{
	return dot( c, photoLuma );
}

// RB: Conditional sRGB -> linear conversion. It is the default for all 3D rendering
// and only shaders for 2D rendering of GUIs define USE_SRGB to work directly on the ldr render target
float3 sRGBToLinearRGB( float3 c )
{
#if !defined( USE_SRGB ) || !USE_SRGB
	c = clamp( c, 0.0, 1.0 );

	return Linear3( c );
#else
	return c;
#endif
}

float4 sRGBAToLinearRGBA( float4 c )
{
#if !defined( USE_SRGB ) || !USE_SRGB
	c = clamp( c, 0.0, 1.0 );

	return float4( Linear1( c.r ), Linear1( c.g ), Linear1( c.b ), Linear1( c.a ) );
#else
	return c;
#endif
}

float3 LinearRGBToSRGB( float3 c )
{
#if !defined( USE_SRGB ) || !USE_SRGB
	c = clamp( c, 0.0, 1.0 );

	return Srgb3( c );
#else
	return c;
#endif
}

float4 LinearRGBToSRGB( float4 c )
{
#if !defined( USE_SRGB ) || !USE_SRGB
	c = clamp( c, 0.0, 1.0 );

	return float4( Srgb1( c.r ), Srgb1( c.g ), Srgb1( c.b ), c.a );
#else
	return c;
#endif
}

float3 HSVToRGB( float3 HSV )
{
	float3 RGB = HSV.z;

	float var_h = HSV.x * 6;
	float var_i = floor( var_h ); // Or ... var_i = floor( var_h )
	float var_1 = HSV.z * ( 1.0 - HSV.y );
	float var_2 = HSV.z * ( 1.0 - HSV.y * ( var_h - var_i ) );
	float var_3 = HSV.z * ( 1.0 - HSV.y * ( 1 - ( var_h - var_i ) ) );
	if( var_i == 0 )
	{
		RGB = float3( HSV.z, var_3, var_1 );
	}
	else if( var_i == 1 )
	{
		RGB = float3( var_2, HSV.z, var_1 );
	}
	else if( var_i == 2 )
	{
		RGB = float3( var_1, HSV.z, var_3 );
	}
	else if( var_i == 3 )
	{
		RGB = float3( var_1, var_2, HSV.z );
	}
	else if( var_i == 4 )
	{
		RGB = float3( var_3, var_1, HSV.z );
	}
	else
	{
		RGB = float3( HSV.z, var_1, var_2 );
	}

	return ( RGB );
}

/** Efficient GPU implementation of the octahedral unit vector encoding from

    Cigolle, Donow, Evangelakos, Mara, McGuire, Meyer,
    A Survey of Efficient Representations for Independent Unit Vectors, Journal of Computer Graphics Techniques (JCGT), vol. 3, no. 2, 1-30, 2014

    Available online http://jcgt.org/published/0003/02/01/
*/

float signNotZeroFloat( float k )
{
	return ( k >= 0.0 ) ? 1.0 : -1.0;
}


float2 signNotZero( float2 v )
{
	return float2( signNotZeroFloat( v.x ), signNotZeroFloat( v.y ) );
}

/** Assumes that v is a unit vector. The result is an octahedral vector on the [-1, +1] square. */
float2 octEncode( float3 v )
{
	float l1norm = abs( v.x ) + abs( v.y ) + abs( v.z );
	float2 oct = v.xy * ( 1.0 / l1norm );
	if( v.z < 0.0 )
	{
		oct = ( 1.0 - abs( oct.yx ) ) * signNotZero( oct.xy );
	}
	return oct;
}


/** Returns a unit vector. Argument o is an octahedral vector packed via octEncode,
    on the [-1, +1] square*/
float3 octDecode( float2 o )
{
	float3 v = float3( o.x, o.y, 1.0 - abs( o.x ) - abs( o.y ) );
	if( v.z < 0.0 )
	{
		v.xy = ( 1.0 - abs( v.yx ) ) * signNotZero( v.xy );
	}
	return normalize( v );
}

// RB end

// ----------------------
// YCoCg Color Conversion
// ----------------------
// Co
#define matrixRGB1toCoCg1YX half4( 0.50,  0.0, -0.50, 0.50196078 )
// Cg
#define matrixRGB1toCoCg1YY half4( -0.25,  0.5, -0.25, 0.50196078 )
// 1.0
#define matrixRGB1toCoCg1YZ half4( 0.0,   0.0,  0.0,  1.0 )
// Y
#define matrixRGB1toCoCg1YW half4( 0.25,  0.5,  0.25, 0.0 )

#define matrixCoCg1YtoRGB1X half4( 1.0, -1.0,  0.0,        1.0 )
// -0.5 * 256.0 / 255.0
#define matrixCoCg1YtoRGB1Y half4( 0.0,  1.0, -0.50196078, 1.0 )
// +1.0 * 256.0 / 255.0
#define matrixCoCg1YtoRGB1Z half4( -1.0, -1.0,  1.00392156, 1.0 )

static half3 ConvertYCoCgToRGB( half4 YCoCg )
{
	half3 rgbColor;

	YCoCg.z = ( YCoCg.z * 31.875 ) + 1.0;			//z = z * 255.0/8.0 + 1.0
	YCoCg.z = 1.0 / YCoCg.z;
	YCoCg.xy *= YCoCg.z;
	rgbColor.x = dot4( YCoCg, matrixCoCg1YtoRGB1X );
	rgbColor.y = dot4( YCoCg, matrixCoCg1YtoRGB1Y );
	rgbColor.z = dot4( YCoCg, matrixCoCg1YtoRGB1Z );
	return rgbColor;
}

static float2 CenterScale( float2 inTC, float2 centerScale )
{
	float scaleX = centerScale.x;
	float scaleY = centerScale.y;
	float4 tc0 = float4( scaleX, 0, 0, 0.5 - ( 0.5f * scaleX ) );
	float4 tc1 = float4( 0, scaleY, 0, 0.5 - ( 0.5f * scaleY ) );

	float2 finalTC;
	finalTC.x = dot4( inTC, tc0 );
	finalTC.y = dot4( inTC, tc1 );
	return finalTC;
}

static float2 Rotate2D( float2 inTC, float2 cs )
{
	float sinValue = cs.y;
	float cosValue = cs.x;

	float4 tc0 = float4( cosValue, -sinValue, 0, ( -0.5f * cosValue ) + ( 0.5f * sinValue ) + 0.5f );
	float4 tc1 = float4( sinValue, cosValue, 0, ( -0.5f * sinValue ) + ( -0.5f * cosValue ) + 0.5f );

	float2 finalTC;
	finalTC.x = dot4( inTC, tc0 );
	finalTC.y = dot4( inTC, tc1 );
	return finalTC;
}

// better noise function available at https://github.com/ashima/webgl-noise
float rand( float2 co )
{
	return frac( sin( dot( co.xy, float2( 12.9898, 78.233 ) ) ) * 43758.5453 );
}

#define square( x )		( x * x )

#define LUMINANCE_SRGB half4( 0.2125, 0.7154, 0.0721, 0.0 )
#define LUMINANCE_LINEAR half4( 0.299, 0.587, 0.144, 0.0 )

#define _half2( x )		half2( x, x )
#define _half3( x )		half3( x, x, x )
#define _half4( x )		half4( x, x, x, x )
#define _float2( x )	float2( x, x )
#define _float3( x )	float3( x, x, x )
#define _float4( x )	float4( x, x, x, x )
#define _int2( x )		int2( x, x )
#define _int3( x )		int3( x, x, x )
#define vec2			float2
#define vec3			float3
#define vec4			float4

#define VPOS SV_Position

#define dFdx ddx
#define dFdy ddy

static float4 idtex2Dproj( SamplerState samp, Texture2D t, float4 texCoords )
{
	return t.Sample( samp, texCoords.xy / texCoords.w );
}

static float idtex2Dproj( SamplerState samp, Texture2D<float> t, float4 texCoords )
{
	return t.Sample( samp, texCoords.xy / texCoords.w );
}

static float3 idtex2Dproj( SamplerState samp, Texture2D<float3> t, float4 texCoords )
{
	return t.Sample( samp, texCoords.xy / texCoords.w );
}

static float4 swizzleColor( float4 c )
{
	return c;
	//return sRGBAToLinearRGBA( c );
}

static float4 texelFetch( Texture2D buffer, int2 ssc, int mipLevel )
{
	float4 c = buffer.Load( int3( ssc.xy, mipLevel ) );
	return c;
}

static float3 texelFetch( Texture2D<float3> buffer, int2 ssc, int mipLevel )
{
	float3 c = buffer.Load( int3( ssc.xy, mipLevel ) );
	return c;
}

static float1 texelFetch( Texture2D<float1> buffer, int2 ssc, int mipLevel )
{
	float1 c = buffer.Load( int3( ssc.xy, mipLevel ) );
	return c;
}

static float texelFetch( Texture2D<float> buffer, int2 ssc, int mipLevel )
{
	float1 c = buffer.Load( int3( ssc.xy, mipLevel ) );
	return c;
}

// returns width and height of the texture in texels
static int2 textureSize( Texture2D buffer, int mipLevel )
{
	int width = 1;
	int height = 1;
	int levels = 0;
	buffer.GetDimensions( mipLevel, width, height, levels );
	return int2( width, height );
}

static int2 textureSize( Texture2D<float1> buffer, int mipLevel )
{
	int width = 1;
	int height = 1;
	int levels = 0;
	buffer.GetDimensions( mipLevel, width, height, levels );
	return int2( width, height );
}

static int2 textureSize( Texture2D<float> buffer, int mipLevel )
{
	int width = 1;
	int height = 1;
	int levels = 0;
	buffer.GetDimensions( mipLevel, width, height, levels );
	return int2( width, height );
}

static float2 vposToScreenPosTexCoord( float2 vpos )
{
	return vpos.xy * rpWindowCoord.xy;
}

// ----------------------
// PSX rendering
// ----------------------

// a very useful resource with many examples about the PS1 look:
// https://www.david-colson.com/2021/11/30/ps1-style-renderer.html

// emulate rasterization with fixed point math
static float3 psxVertexJitter( float4 clipPos )
{
	float jitterScale = rpPSXDistortions.x;
	if( jitterScale > 0.0 )
	{
		// snap to vertex to a pixel position on a lower grid
		float3 vertex = clipPos.xyz / clipPos.w;

		//float2 resolution = float2( 320, 240 ) * ( 1.0 - jitterScale );
		//float2 resolution = float2( 160, 120 );
		float2 resolution = float2( rpPSXDistortions.x, rpPSXDistortions.y );

		// depth independent snapping
		float w = dot4( rpProjectionMatrixW,  float4( vertex.xyz, 1.0 ) );
		vertex.xy = round( vertex.xy / w * resolution ) / resolution * w;

		//vertex.xy = floor( vertex.xy / 4.0 ) * 4.0;
		//vertex.xy = round( vertex.xy * resolution ) / resolution;
		//vertex.xyz = round( vertex.xyz * resolution.x ) / resolution.x;

		vertex *= clipPos.w;

		return vertex;
	}

	return clipPos.xyz;
}

static float psxAffineWarp( float distance )
{
	return log10( distance ) / 2.0;
}

#define BRANCH
#define IFANY


// ----------------------
// Noise tricks
// ----------------------


//note: works for structured patterns too
// [0;1[
float RemapNoiseTriErp( const float v )
{
	float r2 = 0.5 * v;
	float f1 = sqrt( r2 );
	float f2 = 1.0 - sqrt( r2 - 0.25 );
	return ( v < 0.5 ) ? f1 : f2;
}

//note: returns [-intensity;intensity[, magnitude of 2x intensity
//note: from "NEXT GENERATION POST PROCESSING IN CALL OF DUTY: ADVANCED WARFARE"
//      http://advances.realtimerendering.com/s2014/index.html
float InterleavedGradientNoise( float2 uv )
{
	const float3 magic = float3( 0.06711056, 0.00583715, 52.9829189 );
	float rnd = frac( magic.z * frac( dot( uv, magic.xy ) ) );

	return rnd;
}

// this noise, including the 5.58... scrolling constant are from Jorge Jimenez
float InterleavedGradientNoiseAnim( float2 uv, float frameIndex )
{
	uv += ( frameIndex * 5.588238f );

	const float3 magic = float3( 0.06711056, 0.00583715, 52.9829189 );
	float rnd = frac( magic.z * frac( dot( uv, magic.xy ) ) );

	return rnd;
}

float R2Noise( float2 uv )
{
	const float a1 = 0.75487766624669276;
	const float a2 = 0.569840290998;

	return frac( a1 * float( uv.x ) + a2 * float( uv.y ) );
}

// array/table version from http://www.anisopteragames.com/how-to-fix-color-banding-with-dithering/
static const uint ArrayDitherArray8x8[] =
{
	0, 32,  8, 40,  2, 34, 10, 42,   /* 8x8 Bayer ordered dithering  */
	48, 16, 56, 24, 50, 18, 58, 26,  /* pattern.  Each input pixel   */
	12, 44,  4, 36, 14, 46,  6, 38,  /* is scaled to the 0..63 range */
	60, 28, 52, 20, 62, 30, 54, 22,  /* before looking in this table */
	3, 35, 11, 43,  1, 33,  9, 41,   /* to determine the action.     */
	51, 19, 59, 27, 49, 17, 57, 25,
	15, 47,  7, 39, 13, 45,  5, 37,
	63, 31, 55, 23, 61, 29, 53, 21
};

float DitherArray8x8( float2 pos )
{
	uint stippleOffset = ( ( uint )pos.y % 8 ) * 8 + ( ( uint )pos.x % 8 );
	uint byte = ArrayDitherArray8x8[stippleOffset];
	float stippleThreshold = byte / 64.0f;
	return stippleThreshold;
}

float DitherArray8x8Anim( float2 pos, int frameIndexMod4 )
{
	pos += int2( frameIndexMod4 % 2, frameIndexMod4 / 2 ) * uint2( 5, 5 );

	uint stippleOffset = ( ( uint )pos.y % 8 ) * 8 + ( ( uint )pos.x % 8 );
	uint byte = ArrayDitherArray8x8[stippleOffset];
	float stippleThreshold = byte / 64.0f;
	return stippleThreshold;
}


// ----------------------
// COLLISION DETECTION
// ----------------------

// RB: TODO OPTIMIZE
// this is a straight port of idBounds::RayIntersection
bool AABBRayIntersection( float3 b[2], float3 start, float3 dir, out float scale )
{
	int i, ax0, ax1, ax2, side, inside;
	float f;
	float3 hit;

	ax0 = -1;
	inside = 0;
	for( i = 0; i < 3; i++ )
	{
		if( start[i] < b[0][i] )
		{
			side = 0;
		}
		else if( start[i] > b[1][i] )
		{
			side = 1;
		}
		else
		{
			inside++;
			continue;
		}
		if( dir[i] == 0.0f )
		{
			continue;
		}

		f = ( start[i] - b[side][i] );

		if( ax0 < 0 || abs( f ) > abs( scale * dir[i] ) )
		{
			scale = - ( f / dir[i] );
			ax0 = i;
		}
	}

	if( ax0 < 0 )
	{
		scale = 0.0f;

		// return true if the start point is inside the bounds
		return ( inside == 3 );
	}

	ax1 = ( ax0 + 1 ) % 3;
	ax2 = ( ax0 + 2 ) % 3;
	hit[ax1] = start[ax1] + scale * dir[ax1];
	hit[ax2] = start[ax2] + scale * dir[ax2];

	return ( hit[ax1] >= b[0][ax1] && hit[ax1] <= b[1][ax1] &&
			 hit[ax2] >= b[0][ax2] && hit[ax2] <= b[1][ax2] );
}

