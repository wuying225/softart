check_build_with_unicode()
config_3rd_party()
INCLUDE_DIRECTORIES(../
${3rd_party_includes}
)
LINK_DIRECTORIES(${3rd_party_libs})
set (HEADER_FILES
	include/buffer.h
	include/clipper.h
	include/colors.h
	include/colors_convertors.h
	include/decl.h
	include/enums.h
	include/framebuffer.h
	include/handles.h
	include/index_fetcher.h
	include/lockfree_queue.h
	include/presenter_dev.h
	include/rasterizer.h
	include/render_stage.h
	include/renderer.h
	include/renderer_capacity.h
	include/renderer_impl.h
	include/resource_manager.h
	include/sampler.h
	include/shader.h
	include/shader_utility.h
	include/shaderregs.h
	include/shaderregs_op.h
	include/softart_fwd.h
	include/stream.h
	include/stream_assembler.h
	include/surface.h
	include/texture.h
	include/thread_pool.h
	include/vertex_cache.h
)

set (SOURCE_FILES
	src/clipper.cpp
	src/color_convertors.cpp
	src/default_vertex_cache.cpp
	src/framebuffer.cpp
	src/index_fetcher.cpp
	src/pixel_shader.cpp
	src/rasterizer.cpp
	src/renderer_impl.cpp
	src/resource_manager.cpp
	src/result.cpp
	src/sampler.cpp
	src/shader.cpp
	src/stream_assembler.cpp
	src/surface.cpp
	src/texture1d.cpp
	src/texture2d.cpp
	src/texture_cube.cpp
	src/thread_pool.cpp
)

ADD_LIBRARY( SoftArt STATIC
${HEADER_FILES}
${SOURCE_FILES}
)

TARGET_LINK_LIBRARIES(SoftArt
EFLIB
)

config_output_paths(SoftArt)