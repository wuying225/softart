#ifndef SALVIAX_SKIN_MESH_H
#define SALVIAX_SKIN_MESH_H

#include <salviax/include/resource/resource_forward.h>

#include <salviax/include/resource/mesh/sa/mesh.h>
#include <eflib/include/metaprog/util.h>
#include <eflib/include/math/matrix.h>

#include <eflib/include/platform/boost_begin.h>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <eflib/include/platform/boost_end.h>

#include <vector>
#include <string>

BEGIN_NS_SALVIAX_RESOURCE();

EFLIB_DECLARE_CLASS_SHARED_PTR(animation_player);
EFLIB_DECLARE_STRUCT_SHARED_PTR(animation_info);
EFLIB_DECLARE_CLASS_SHARED_PTR(scene_node);
EFLIB_DECLARE_CLASS_SHARED_PTR(skin_mesh);

enum interpolation_methods{
	im_none,
	im_linear
};

struct animation_info
{
	std::vector<interpolation_methods>	interps;
};

template <typename T>
struct animation_info_impl: public animation_info
{
	std::vector<float>					X;
	std::vector<T>						Y;
	boost::function<void(T const&)>		applier;
};

class animation_player
{
public:
	virtual void				set_play_time(float t) = 0;
	virtual void				update_play_time(float elapsed) = 0;
	virtual animation_info_ptr	anim_info() = 0;
};

template <typename T>
class animation_player_impl : public animation_player
{
public:
	animation_player_impl()
		: current_time(0), aninfo( make_shared< animation_info_impl<T> >() )
	{}

	virtual void set_play_time(float t)
	{
		current_time = t;
		aninfo->applier( resolve(current_time) );
	}

	virtual void update_play_time(float elapsed)
	{
		current_time += elapsed;
		aninfo->applier( resolve(current_time) );
	}

	animation_info_ptr anim_info() { return aninfo; }
	boost::shared_ptr< animation_info_impl<T> >
		anim_info2() { return aninfo; }
							
private:
	T resolve(float time)
	{
		// Find segment
		std::vector<float>::iterator it = lower_bound(aninfo->X.begin(), aninfo->X.end(), time);
		int i_segment = distance(aninfo->X.begin(), it) - 1;

		if( it == aninfo->X.begin() )
		{
			switch(aninfo->interps[0])
			{
			case im_none:
			case im_linear:
			default:
				return aninfo->Y[0];
			}
		}

		if( it == aninfo->X.end() )
		{
			switch(aninfo->interps[i_segment])
			{
			case im_none:
			case im_linear:
			default:
				return aninfo->Y.back();
			}
		}

		switch(aninfo->interps[i_segment])
		{
		case im_none:
		case im_linear:
		default:
			float diff = aninfo->X[i_segment+1] - aninfo->X[i_segment];
			float t = (time - aninfo->X[i_segment]) / diff;
			return (aninfo->Y[i_segment+1] - aninfo->Y[i_segment]) * t + aninfo->Y[i_segment];
		}
	}

	boost::shared_ptr<
		animation_info_impl<T>
	>		aninfo;
	float	current_time;
};

class scene_node
{
public:
	scene_node(scene_node* parent);

	scene_node* parent;
	std::vector<scene_node_ptr>	children;

	void reset_world_matrix();
	void reset_world_matrix_recursive();

	void update_world_matrix();
	void update_world_matrix_recursive();

	eflib::mat44				local_matrix;
	eflib::mat44				original_matrix;
	eflib::mat44				world_matrix;
};

class skin_mesh: public base_skin_mesh
{
public:
	virtual size_t	submesh_count();
	virtual void	render( uint32_t submesh_id );
	virtual void	update_time(float t);
	virtual void	set_time(float t);
	virtual std::vector<eflib::mat44> joint_transformations();

	boost::unordered_map<
		std::string, scene_node*>		joint_nodes;
	std::vector<animation_player_ptr>	anims;
	std::vector<std::string>			joints;
	std::vector<eflib::mat44*>			joint_matrices;
	std::vector<h_mesh>					submeshes;
	std::vector<scene_node_ptr>			roots;
};

END_NS_SALVIAX_RESOURCE();

#endif