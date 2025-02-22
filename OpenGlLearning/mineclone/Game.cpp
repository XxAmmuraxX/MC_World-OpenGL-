#include "../vendor/imgui/imgui.h"
#include "Game.h"
#include "../Input.h"

    Game::Game()
    {

        m_Proj = MatrixPerspective(45*DEG2RAD, 16.0f/9.0f, 0.01f, 100.0f);

        float FOV = 80.0f;
        float tanHalfFOV = tanf((FOV / 2) * DEG2RAD);
        float d = 1 / tanHalfFOV;

        float NearZ = 0.01f;
        float FarZ = 1000.0f;

        int width = 16.0f, height = 9.0f;

        if(m_Window) glfwGetWindowSize(m_Window, &width, &height);
        float ar = (float)width / (float)height;

        float zRange = NearZ - FarZ;

        float A = (-FarZ - NearZ) / zRange;

        float B = 2.0f * FarZ * NearZ / zRange;

        Matrix projection = {
            d/ar, 0.0f, 0.0f, 0.0f,
            0.0f, d,    0.0f, 0.0f,
            0.0f, 0.0f, A,    B,
            0.0f, 0.0f, 1.0f, 0.0f
        };

        m_Proj = projection;
        m_Model = MatrixTranslate(0.0f, 0.0f, 0.0f);
        m_TranslationA.z = -50;
        //m_Proj = MatrixIdentity();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");

        m_VAO = std::make_unique<VertexArray>();
        
        //for (float y = 0; y < 16; y++)
        //    for (float x = 0; x < 16; x++)
        //        for (float z = 0; z < 16; z++)
        //        {
        //            AddBlock(Vector3{ x,y,z });
        //        }

        for (float i = 0; i < 30; i++)
            for (float j = 0; j < 30; j++)
                world.AddChunk(Vector3{ i,-0.75f,j });

        PushData();

        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

       
        m_Texture = std::make_unique<Texture>("mineclone/Textures/atlas2.png");
        m_Shader->SetUniform1i("u_Texture", 0);
    }
    Game::~Game()
    {
    }
    void Game::OnUpdate(float deltaTime)
    {
        UpdatePos();
        Matrix trans = MatrixTranslate(m_TranslationA.x, m_TranslationA.y, m_TranslationA.z);
        Matrix rot_h = MatrixRotate({ 0.0f,1.0f,0.0f }, m_Angle);
        Matrix rot_v = MatrixRotate({ cosf(m_Angle),0.0f,sinf(m_Angle) }, m_Pitch);

        m_View = MatrixMultiply(MatrixMultiply(trans, rot_v),rot_h);

    }
    void Game::OnRender()
    {
        
        glClearColor(0.678f, 0.847f, 0.902f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Renderer renderer;

        m_Texture->Bind();
        
        //for(int k = 0; k < 1; k++)
        //for(int j = 0; j < 1;j++)
        //    for (int i = 0; i < 1; i++)
        //    {
        //        //Matrix mvp = MatrixMultiply(MatrixMultiply(m_Proj, m_View), m_Model);
        //        if ((i > 0 && i < 19) && (j > 0 && j < 19) && (k > 0 && k < 19))
        //            continue;
        //        Vector4 color{Clamp(expf(-abs(m_TranslationA.z - j) / 50.0f), 0.0f, 1.0f)};
        //    m_Shader->SetUniform4f("u_Color",color.x, color.x, color.x, 1.0f);
        //    m_Model = MatrixTranslate(1.0f * -i, 1.0f * -k, 1.0f*-j);
        //}
            Matrix mvp = MatrixMultiply(MatrixMultiply(m_Model,m_View),m_Proj);
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            Vector3 light_dir = world.GetLightDir();
            m_Shader->SetUniform4f("light_dir", light_dir.x, light_dir.y, light_dir.z, 0.0f);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

    }
    void Game::OnImGuiRender()
    {
        //ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, -20, 20);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Translation_Z = %.2f", m_TranslationA.z);
    }
    void Game::UpdatePos()
    {
        Input::Init(m_Window);

        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        float DT = ImGui::GetIO().DeltaTime;

        Vector3 look = { cosf(m_Angle + PI/2), cosf(m_Pitch) , sinf(m_Angle + PI / 2)};
        Vector3 side = Vector3RotateByAxisAngle(look, { 0.0f,1.0f,0.0f }, PI / 2);

        if (Input::isKeyPressed(GLFW_KEY_A))
        {
            m_TranslationA.x += 10 * DT * side.x;
            m_TranslationA.z += 10 * DT * side.z;
        }

        if (Input::isKeyPressed(GLFW_KEY_D))
        {
            m_TranslationA.x -= 10 * DT * side.x;
            m_TranslationA.z -= 10 * DT * side.z;
        }

        if (Input::isKeyPressed(GLFW_KEY_W))
        {
            m_TranslationA.x -= 10 * DT * look.x;
            m_TranslationA.z -= 10 * DT * look.z;
        }

        if (Input::isKeyPressed(GLFW_KEY_S))
        {
            m_TranslationA.x += 10 * DT * look.x;
            m_TranslationA.z += 10 * DT * look.z;
        }

        if (Input::isKeyPressed(GLFW_KEY_SPACE))
        {
            m_TranslationA.y -= 10 * DT;
        }

        if (Input::isKeyPressed(GLFW_KEY_LEFT_CONTROL))
        {
            m_TranslationA.y += 10 * DT;
        }

        if (Input::isKeyPressed(GLFW_KEY_RIGHT))
        {
            m_Angle -= 0.01;
        }

        if (Input::isKeyPressed(GLFW_KEY_LEFT))
        {
            m_Angle += 0.01;
        }
        

        if (Input::isKeyPressed(GLFW_KEY_UP))
        {
            m_Pitch += 0.01;
        }

        if (Input::isKeyPressed(GLFW_KEY_DOWN))
        {
            m_Pitch -= 0.01;
        }

        float mouseX, mouseY;
        
        mouseX = ImGui::GetMousePos().x;
        mouseY = ImGui::GetMousePos().y;

        // Calculate mouse delta
        static float lastMouseX = mouseX;
        static float lastMouseY = mouseY;
        float deltaX = mouseX - lastMouseX;
        float deltaY = mouseY - lastMouseY;
        lastMouseX = mouseX;
        lastMouseY = mouseY;

        //ImGui::SetCursorPos({ ImGui::GetCursorScreenPos().x / 1.f,ImGui::GetCursorScreenPos().y / 2.f });

        m_Pitch -= deltaY * 0.001;

        m_Angle -= deltaX * 0.001;


    }

    void Game::AddBlock(Vector3 pos)
    {
        int start_index = indices.size() / 1.5f;

        std::vector<unsigned int> new_indices;

        for (int i = 0; i < 36; i++)
            new_indices.push_back(block_model_indices[i] + start_index);

        for (auto& index : new_indices)
            indices.push_back(index);

        std::vector<float> new_vertices;

        for (int i = 0; i < 120; i++)
        {
            if (i % 5 == 0)
                new_vertices.push_back(block_model_vertices[i] + pos.x);
            if (i % 5 == 1)
                new_vertices.push_back(block_model_vertices[i] + pos.y);
            if (i % 5 == 2)
                new_vertices.push_back(block_model_vertices[i] + pos.z);
            if(i % 5 == 3 || i % 5 == 4)
                new_vertices.push_back(block_model_vertices[i]);
        }
        
        for (auto& vertex : new_vertices)
            vertices.push_back(vertex);

        m_VertexBuffer.reset();
        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);

        m_IndexBuffer.reset();

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices.data(), indices.size());

        m_VAO->AddBuffer(*m_VertexBuffer, layout);
    }

    void Game::PrintIB()
    {
        for (int i = 0; i < indices.size(); i++)
        {
            if (i % 3 == 0)
                std::cout << std::endl;
            if(i % 6 == 0)
                std::cout << std::endl;
            std::cout << indices[i] << " ";
        }
    }
    void Game::PrintVB()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (i % 5 == 0)
            {
                std::cout << "\nPos: ";
            }
            
            if (i % 5 == 3)
            {
                std::cout << "TexCoords: ";
            }
            
            std::cout << vertices[i] << " ";
        }
    }
    void Game::PushData()
    {
        int start_index = indices.size() / 1.5f;

        int block_id = -1;

        for (auto& chunk : world.GetChunks())
        {
            for(int y = 0 ; y < Chunk::HEIGHT ; y++)
            for(int x = 0 ; x < Chunk::WIDTH ; x++)
                for (int z = 0; z < Chunk::WIDTH; z++)
                {
                    int index_idx = 0;

                    int vertex_idx = 0;

                    int skip_bottom_face = -1;
                    int skip_right_face = -1;
                    int skip_front_face = -1;
                    int skip_back_face = -1;
                    int skip_left_face = -1;
                    int skip_top_face = -1;

                    int max_idx = 36;

                    if (chunk.blocks[x][y][z].GetId() == 0)
                        continue;

                    if (z == Chunk::WIDTH - 1)
                    {
      
                    }
                    else if (chunk.blocks[x][y][z + 1].GetId() != air &&
                             chunk.blocks[x][y][z + 1].GetId() != water)
                    {
                        skip_front_face = 0;
                    }


                    if (x == Chunk::WIDTH - 1)
                    {

                    }
                    else if (chunk.blocks[x + 1][y][z].GetId() != air && 
                             chunk.blocks[x + 1][y][z].GetId() != water)
                    {
                        skip_right_face = 100;
                    }

                    
                    if (z == 0)
                    {

                    }
                    else if (chunk.blocks[x][y][z - 1].GetId() != air && 
                             chunk.blocks[x][y][z - 1].GetId() != water)
                    {
                        skip_back_face = 20;
                    }


                    if (x == 0)
                    {

                    }
                    else if (chunk.blocks[x - 1][y][z].GetId() != air && 
                             chunk.blocks[x - 1][y][z].GetId() != water)
                    {
                        skip_left_face = 80;
                    }


                    if (y == Chunk::HEIGHT - 1)
                    {
                       
                    }
                    else if (chunk.blocks[x][y + 1][z].GetId() != air &&
                             chunk.blocks[x][y + 1][z].GetId() != water)
                    {
                        skip_top_face = 40;
                    }

                    if (y == 0)
                    {
                       
                    }
                    else if (chunk.blocks[x][y - 1][z].GetId() != air && 
                             chunk.blocks[x][y - 1][z].GetId() != water)
                    {
                        skip_bottom_face = 60;
                    }

                    unsigned int curr_face = 0;

                    for (vertex_idx; vertex_idx < 120; vertex_idx++)
                    {
                        if (vertex_idx == skip_left_face ||
                            vertex_idx == skip_right_face ||
                            vertex_idx == skip_front_face ||
                            vertex_idx == skip_back_face ||
                            vertex_idx == skip_bottom_face ||
                            vertex_idx == skip_top_face)
                        {
                            vertex_idx += 19;
                            max_idx -= 6;
                            continue;
                        }

                        if (vertex_idx % 5 == 0)
                            vertices.push_back(block_model_vertices[vertex_idx] + chunk.blocks[x][y][z].GetPos().x);
                        if (vertex_idx % 5 == 1)
                            vertices.push_back(block_model_vertices[vertex_idx] + chunk.blocks[x][y][z].GetPos().y);
                        if (vertex_idx % 5 == 2)
                            vertices.push_back(block_model_vertices[vertex_idx] + chunk.blocks[x][y][z].GetPos().z);

                       /* if (vertex_idx % 5 == 3)
                            vertices.push_back(block_model_vertices[vertex_idx]);
                        else if (vertex_idx % 5 == 4)
                            vertices.push_back(block_model_vertices[vertex_idx]);*/



                        if (vertex_idx % 20 == 18)
                        {
                            vertices.push_back(atlas.GetBotLeft(chunk.blocks[x][y][z].GetId(), vertex_idx + 2).x);
                            vertices.push_back(atlas.GetBotLeft(chunk.blocks[x][y][z].GetId(), vertex_idx + 2).y);
                        }
                        else if (vertex_idx % 20 == 13)
                        {
                            vertices.push_back(atlas.GetBotRight(chunk.blocks[x][y][z].GetId(), vertex_idx + 7).x);
                            vertices.push_back(atlas.GetBotRight(chunk.blocks[x][y][z].GetId(), vertex_idx + 7).y);
                        }
                        else if (vertex_idx % 20 == 8)
                        {
                            vertices.push_back(atlas.GetTopRight(chunk.blocks[x][y][z].GetId(), vertex_idx + 12).x);
                            vertices.push_back(atlas.GetTopRight(chunk.blocks[x][y][z].GetId(), vertex_idx + 12).y);
                        }
                        else if (vertex_idx % 20 == 3)
                        {
                            vertices.push_back(atlas.GetTopLeft(chunk.blocks[x][y][z].GetId(), vertex_idx + 17).x);
                            vertices.push_back(atlas.GetTopLeft(chunk.blocks[x][y][z].GetId(), vertex_idx + 17).y);
                        }

                    }


                    for (index_idx; index_idx < max_idx; index_idx++)
                        indices.push_back(block_model_indices[index_idx] + start_index);

                    start_index += max_idx / 1.5f;

                }

        }

        m_VertexBuffer.reset();
        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);

        m_IndexBuffer.reset();

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices.data(), indices.size());

        m_VAO->AddBuffer(*m_VertexBuffer, layout);
    }
