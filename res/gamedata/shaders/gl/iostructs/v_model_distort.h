
out gl_PerVertex { vec4 gl_Position; };

struct vf
{
	float2	tc0	; // TEXCOORD0;	// base
	float4	c0	; // COLOR0;		// color
//	Igor: for additional depth dest
#ifdef	USE_SOFT_PARTICLES
	float4 tctexgen	; // TEXCOORD1;
#endif	//	USE_SOFT_PARTICLES
	float4	hpos; // SV_Position;
};

layout(location = POSITION)		in float4	v_model_P		; // POSITION;		// (float,float,float,1)
#ifdef	SKIN_0
layout(location = NORMAL)		in float3	v_model_N		; // NORMAL;		// (nx,ny,nz)
#else
layout(location = NORMAL)		in float4	v_model_N		; // NORMAL;		// (nx,ny,nz,index)
#endif
#if defined(SKIN_3) || defined(SKIN_4)
layout(location = TANGENT)		in float4	v_model_T		; // TANGENT;		// (nx,ny,nz,weight0)
layout(location = BINORMAL)		in float4	v_model_B		; // BINORMAL;		// (nx,ny,nz,weight1)
#else
layout(location = TANGENT)		in float3	v_model_T		; // TANGENT;		// (nx,ny,nz)
layout(location = BINORMAL)		in float3	v_model_B		; // BINORMAL;		// (nx,ny,nz)
#endif
#ifdef	SKIN_NONE
layout(location = TEXCOORD0)	in float2	v_model_tc		; // TEXCOORD0;	// (u,v)
#elif defined(SKIN_2) || defined(SKIN_3)
layout(location = TEXCOORD0)	in int4		v_model_tc		; // TEXCOORD0;	// (u,v)
#else
layout(location = TEXCOORD0)	in int2		v_model_tc		; // TEXCOORD0;	// (u,v)
#endif
#ifdef	SKIN_4
layout(location = TEXCOORD1)	in float4	v_model_ind		; // (x=m-index0, y=m-index1, z=m-index2, w=m-index3)
#endif

layout(location = TEXCOORD0) 	out float2	v2p_particle_tc0; // TEXCOORD0;
layout(location = COLOR0) 		out float4	v2p_particle_c0	; // COLOR0;
#ifdef	USE_SOFT_PARTICLES
layout(location = TEXCOORD1) 	out float4	v2p_particle_tctexgen; // TEXCOORD1;
#endif	//	USE_SOFT_PARTICLES

vf   _main (v_model v);

void main()
{
#ifdef 	SKIN_NONE
	v_model I;
#endif
#ifdef 	SKIN_0
	v_model_skinned_0 I;
#endif
#ifdef	SKIN_1
	v_model_skinned_1 I;
#endif
#ifdef	SKIN_2
	v_model_skinned_2 I;
#endif
#ifdef	SKIN_3
	v_model_skinned_3 I;
#endif
#ifdef	SKIN_4
	v_model_skinned_4 I;
	I.ind = v_model_ind;
#endif

	I.P = v_model_P;
	I.N = v_model_N;
	I.T = v_model_T;
	I.B = v_model_B;
	I.tc = v_model_tc;

	vf O;
#ifdef 	SKIN_NONE
	O = _main(I);
#endif
#ifdef 	SKIN_0
	O = _main(skinning_0(I));
#endif
#ifdef	SKIN_1
	O = _main(skinning_1(I));
#endif
#ifdef	SKIN_2
	O = _main(skinning_2(I));
#endif
#ifdef	SKIN_3
	O = _main(skinning_3(I));
#endif
#ifdef	SKIN_4
	O = _main(skinning_4(I));
#endif

	v2p_particle_tc0 = O.tc0;
	v2p_particle_c0 = O.c0;
	v2p_particle_tctexgen = O.tctexgen;
	gl_Position = O.hpos;
}
