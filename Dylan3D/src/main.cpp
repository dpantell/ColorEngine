#pragma once

#include <cmath>
#include <cstdio>

#include "SDL\SDL.h"
#include "GL\glew.h"

#include "Core\Application\Clock.h"
#include "Core\Application\InputManager.h"

#include "Camera\Camera.h"
#include "Camera\FreeCameraController.h"

#include "Math\Math3D.h"
#include "Math\Transform3D.h"

#include "Rendering\UniformCommand.h"

#include "Cube.h"

#include "ImageRenderer.h"
#include "GBufferRenderer.h"


int main(int argc, char *argv[])
{
	Vector2ui window_size(1366, 768);

	SDL_Init(SDL_INIT_EVERYTHING);

	auto window_ptr_ = SDL_CreateWindow(
		"Dylan3D",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_size.x, window_size.y,
		SDL_WINDOW_OPENGL);

	if (window_ptr_ == 0)
	{
		fprintf(stderr, "SDL_Window Creation Failed.");
	}

	auto gl_context_ = SDL_GL_CreateContext(window_ptr_);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Glew Initialization Failed.");
	}

	SDL_GL_SetSwapInterval(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	Clock clock;
	InputManager input_manager;

	Camera camera;
	camera.SetPosition(Vector3f(0, 0, -2));

	FreeCameraController camera_controller;
	camera_controller.SetSpeed(5.0f);
	camera_controller.SetSensitivity(0.15f);

	Matrix4 view;
	Matrix4 projection;

	Transform3D tranform;
	Math3D::Perspective::LoadProjection(projection, window_size, 0.01f, 1000.0f, 75.0f);
	
	Cube cube;
	FullScreen fullscreen;

	std::vector<Renderable*> cube_ptr = { &cube };
	std::vector<Renderable*> fullscreen_ptr = { &fullscreen };

	std::vector<Vector3f> positions;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			positions.push_back(Vector3f(i, 0, j));
		}
	}

	cube.SetPositions(positions);

	ImageRenderer image_renderer(window_size);
	GBufferRenderer gb_renderer(window_size);

	image_renderer.SetImage(gb_renderer.GetTextureUnit(GBufferRenderer::TEXTURE::POSITION));

	int i = 0;
	while (++i)
	{
		input_manager.Update();

		if (input_manager.IsKeyDown(SDL_SCANCODE_Q)) break;

		clock.Update();

		camera.GetWorldToView(view);
		camera_controller.Update(camera, input_manager, clock);

		gb_renderer.SetViewMatrix(view);
		gb_renderer.SetProjectionMatrix(projection);

		gb_renderer.Render(GL::DrawMode::TRIANGLES, cube_ptr);
		image_renderer.Render(GL::DrawMode::TRIANGLES, fullscreen_ptr);

		SDL_GL_SwapWindow(window_ptr_);
	}

	return 0;
}