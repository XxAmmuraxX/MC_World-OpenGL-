#pragma once

#include "../Renderer.h"

#include "../vendor/imgui/imgui.h"

#include "../Texture.h"
#include <vector>
#include <string>
#include <iostream>

#include "../mineclone/World.h"

#include <memory>

struct GLFWwindow;

	class Game
    {
    protected:
        GLFWwindow* m_Window;
	public:
		Game();
		~Game();

        void SetWindowPointer(GLFWwindow* window) { m_Window = window; }
		void OnUpdate(float deltaTime);
		void OnRender();
		void OnImGuiRender();
		void UpdatePos();
		void AddBlock(Vector3 pos);
        void PrintIB();
        void PrintVB();
        void PushData();

	private:
		Vector3 m_TranslationA = { 0 };
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		float m_Angle = 0;
        float m_Pitch = 0;

		Matrix m_Proj;
		Matrix m_View;
		Matrix m_Model;

        BlockTextures atlas = BlockTextures(256, 256);

        World world;

		std::vector<float> vertices;

		std::vector<unsigned int> indices;

        float block_model_vertices[5 * 4 * 6] =
        {
                // Front face
                -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // Vertex 1
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,  // Vertex 0
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // Vertex 3
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // Vertex 2

                // Back face
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // Vertex 4
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // Vertex 5
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // Vertex 6
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // Vertex 7

                // Top face
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // Vertex 8
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // Vertex 9
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,  // Vertex 10
                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,  // Vertex 11

                // Bottom face
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // Vertex 12
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // Vertex 13
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  // Vertex 14
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // Vertex 15

                // Left face
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // Vertex 16
                -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,  // Vertex 17
                -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // Vertex 18
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // Vertex 19

                // Right face
                0.5f, 0.5f, 0.5f, 0.0f, 0.0f,  // Vertex 20
                0.5f, 0.5f, -0.5f, 1.0f, 0.0f,  // Vertex 21
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  // Vertex 22
                0.5f, -0.5f, 0.5f, 0.0f, 1.0f   // Vertex 23
        };

        unsigned int block_model_indices[2 * 3 * 6] =
        {
            // Front face
            0, 1, 2,
            2, 3, 0,

            // Back face
            4, 5, 6,
            6, 7, 4,

            // Top face
            8, 9, 10,
            10, 11, 8,

            // Bottom face
            12, 13, 14,
            14, 15, 12,

            // Left face
            16, 17, 18,
            18, 19, 16,

            // Right face
            20, 21, 22,
            22, 23, 20
        };

    };