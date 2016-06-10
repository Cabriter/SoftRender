#pragma once

typedef struct
{
	int render_state;			//��Ⱦ״̬

	int width;					//viewport��
	int height;					//viewport��

	UINT32** frameBuffer;		//��ɫ������ [��ά����]
	float** zBuffer;			//��Ȼ����� [��ά����]
	UINT32** texture;			//��ͼ������ [��ά����]

	float texture_u_max;        //��ǰ��ͼU�������ֵ��texture_width - 1
	float texture_v_max;        //��ǰ��ͼV�������ֵ��texture_height - 1

	UINT32 background;			//������ɫ
	UINT32 foreground;			//ǰ����ɫ

	Matrix44 world;
	Matrix44 view;
	Matrix44 projection;
	Matrix44 wvp;				// world * view * projection

	Camera camera;

} Renderdev;

void renderdev_init(Renderdev* device, int width, int height, void* fb);
void renderdev_clear(Renderdev* device);
void renderdev_draw_mesh(Renderdev* device, Mesh mesh);

void renderdev_set_camera(Renderdev* device, Camera camera);
void renderdev_update_transform(Renderdev* device);

void renderdev_primitive(Renderdev* device, const Vertex* vx1, const Vertex* vx2, const Vertex* vx3);
void renderdev_rasterize(Renderdev* device, Vertex* vx1, Vertex* vx2, Vertex* vx3);

void renderdev_process_vertex(Renderdev* device, Vertex* outvx, const Vertex* vx);
void renderdev_process_fragment(Renderdev* device, const Vertex* vx, float rhw, int x, int y);

void renderdev_draw_scanline(Renderdev* device, float y, Vertex* vxa, Vertex* vxb, Vertex* vxc, Vertex* vxd);
void renderdev_draw_pixel(Renderdev* device, int x, int y, UINT32 color);
void renderdev_draw_line(Renderdev* device, Vector4* v1, Vector4* v2);

int renderdev_cvv_cut(const Vector4* v);
void renderdev_project_viewport(Renderdev* device, Vector4* outv, const Vector4* v);

UINT32 renderdev_texture_sample(const Renderdev* device, float u, float v);
void renderdev_set_texture(Renderdev* device, void* bits, long pitch, int w, int h);

Vertex vertex_shader(Vertex vx, const Renderdev* device);
UINT32 fragment_shader(Vertex vx, const Renderdev* device);
