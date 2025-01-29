//
// Created by Ben Gotts on 25/01/2025.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "ShaderUtility.h"
#include "../core/SceneObject.h"
#include "../core/Camera.h"

using namespace BG3DRenderer::Core;

namespace BG3DRenderer::Graphics{
	class Renderer {
	private:
        ShaderUtility activeShader;
		std::shared_ptr<Camera> activeCamera;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;

		static const int FPS_BUFFER_SIZE = 60;
		float fpsBuffer[FPS_BUFFER_SIZE] = {0};
		int fpsBufferIndex = 0;
		float minFrameTime = std::numeric_limits<float>::max();
		float maxFrameTime = 0.0f;
		std::vector<float> frameTimeHistory;
	public:
		Renderer();

		void UpdateFrameTime();
		void Render(const std::vector<SceneObject*>& objects);

		void SetCamera(const std::shared_ptr<Camera> camera);

        ShaderUtility* GetShader();

		float GetDeltaTime() const { return deltaTime; }

		float GetRawFPS() const { return 1.0f / deltaTime; }
		float GetSmoothedFPS() const {
			float sum = 0;
			for (int i = 0; i < FPS_BUFFER_SIZE; ++i) {
				sum += fpsBuffer[i];
			}
			return sum / FPS_BUFFER_SIZE;
		}
		float GetMinFrameTime() const { return minFrameTime; }
		float GetMaxFrameTime() const { return maxFrameTime; }
		float GetFrameTimeVariance() const {
			if (frameTimeHistory.empty()) return 0.0f;

			float mean = 0.0f;
			for (float time : frameTimeHistory) mean += time;
			mean /= frameTimeHistory.size();

			float variance = 0.0f;
			for (float time : frameTimeHistory) {
				variance += std::pow(time - mean, 2);
			}
			return variance / frameTimeHistory.size();
		}
	};
}

#endif //RENDERER_H
