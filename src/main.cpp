#define GLEW_STATIC

#include <iostream>

#include "window/window.h"
#include "window/events.h"
#include "graphics/shader.h"
#include "window/camera.h"
#include "OpenGL/include/GLEW/glew.h"
#include "OpenGL/include/GLFW/glfw3.h"
#include "graphics/Texture.h"
//GL math
#include "OpenGL/include/glm/ext.hpp"
#include "voxels/voxel.h"
#include "voxels/chunk.h"
#include "graphics/mesh.h"
#include "graphics/VoxelRenderer.h"
#include "voxels/chunks.h"
#include "graphics/LineBatch.h"
#include "save/files.h"
#include "lighting/LightSolver.h"
#include "lighting/Lightmap.h"
#include "lighting/Lighting.h"
#include "voxels/Block.h"
#include "save//WorldFiles.h"



int WIDTH = 1920, HEIGHT = 1080;


float vertices[] = {
        // x    y
        0.0f, 0.01f,
        0.0f, -0.01f,

        -0.01f, 0.0f,
        0.01f,-0.0f,
};

int attrs[] = {
        2,  0 //null terminator
};

int main()
{
    Window::initialize(WIDTH, HEIGHT, "Voxel");
    Events::initialize();

    shader *mains = load_shader("../res/mainv.glsl", "../res/mainf.glsl");

    shader *crosshairShader = load_shader("../res/crossv.glsl", "../res/crossf.glsl");

    shader* boxshader = load_shader("../res/boxv.glsl", "../res/boxf.glsl");

    if (boxshader == nullptr){
        std::cerr << "failed to load lines shader" << std::endl;
        Window::terminate();
        return 1;
    }
    if (crosshairShader == nullptr)
    {
        std::cerr << "failed to load cross shader" << std::endl;
        Window::terminate();
        return 1;
    }

    if (mains == nullptr)
    {
        std::cerr << "Shader import error" << std::endl;
        Window::terminate();
        return -1;
    }

    Texture *texture = load_texture("../res/atlas.png");
    if (texture == nullptr)
    {
        std::cerr << "Texture import error" << std::endl;
        delete mains;
        Window::terminate();
        return -2;
    }

    {
        // AIR
        auto* block = new Block(0,0);
        block->drawGroup = 1;
        block->lightPassing = true;
        Block::blocks[block->id] = block;

        // STONE
        block = new Block(1,19);
        Block::blocks[block->id] = block;

        // GRASS
        block = new Block(2,3);
        block->textureFaces[3] = 2;
        block->textureFaces[2] = 50;
        Block::blocks[block->id] = block;

        // LAMP
        block = new Block(3,229);
        block->emission[0] = 13;
        block->emission[1] = 13;
        block->emission[2] = 7;
        Block::blocks[block->id] = block;

        // GLASS
        block = new Block(4,152);
        block->drawGroup = 2;
        block->lightPassing = true;
        Block::blocks[block->id] = block;

        // GLASS
        block = new Block(5,152);
        Block::blocks[block->id] = block;

        // WATER
        block = new Block(7, 0);
        block->textureFaces[3] = 448;
        block->drawGroup = 0;
        block->lightPassing = true;
        Block::blocks[block->id] = block;



    }

    WorldFiles wfile = WorldFiles("world/", 24*1024*1024);
    auto* chunks = new Chunks(16 * 4,1,16 * 4, 0,0,0);
    VoxelRenderer renderer(1024*1024*4);
    auto* lineBatch = new LineBatch(4096);

    Lighting::initialize(chunks);
           //      R: 167,               G: 192,              B: 232
    glClearColor(167.0f / 255.0f,192.0f / 255.0f,232.0f / 255.0f,1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    Mesh* crosshair = new Mesh(vertices, 4, attrs);
    auto* camera = new Camera(glm::vec3(32,32,32), glm::radians(90.0f));


    float lastTime = glfwGetTime();
    float delta;

    float camX = 0.0f;
    float camY = 0.0f;

    float speed = 15;
    Events::toogleCursor();

    int cur_id = 0;

    glfwSwapInterval(0);

    while (!Window::isShouldClose())
    {
        auto currentTime = (float) glfwGetTime();
        delta = currentTime - lastTime;
        lastTime = currentTime;

        Events::pullEvents();

        for (int i = 1; i < 6; i++)
        {
            if (Events::jpressed(GLFW_KEY_0+i))
            {
                cur_id = i;
            }
        }

        if (Events::pressed(GLFW_KEY_W))
        {
            camera->position += camera->front * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_S))
        {
            camera->position -= camera->front * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_D))
        {
            camera->position += camera->right * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_A))
        {
            camera->position -= camera->right * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_Z))
        {
            camera->position -= camera->up * delta * speed;
        }
        if (Events::pressed(GLFW_KEY_X))
        {
            camera->position += camera->up * delta * speed;
        }


        if (Events::pressed(GLFW_KEY_ESCAPE) || Events::pressed(GLFW_KEY_Q))
        {
            Window::setShouldClose(true);
        }
        if (Events::jpressed(GLFW_KEY_E))
        {
            Events::toogleCursor();
        }
        if (Events::jpressed(GLFW_KEY_T))
        {
            cur_id++;
        }
        if (Events::jpressed(GLFW_KEY_G))
        {
            cur_id--;
        }

        if (Events::pressed(GLFW_KEY_LEFT_CONTROL) && Events::pressed(GLFW_KEY_S))
        {
            puts("Ctrl+s");
            system("pause");
            for (unsigned int i = 0; i < chunks->volume; i++)
            {
                Chunk* chunk = chunks->chunks[i];
                if (chunk == nullptr)
                    continue;
                wfile.put((const char*)chunk->voxels, chunk->x, chunk->z);
            }

            wfile.write();
        }

        chunks->setCenter(camera->position.x,0,camera->position.z);
        chunks->_buildMeshes(&renderer);
        chunks->loadVisible(&wfile);

        std::cout << cur_id << std::endl;
        if (Events::_cursor_locked)
        {
            camY += (float) -Events::deltaY / (float) Window::height * 2;
            camX += (float) -Events::deltaX / (float) Window::height * 2;

            if (camY < -glm::radians(89.0f))
            {
                camY = -glm::radians(89.0f);
            }
            if (camY > glm::radians(89.0f))
            {
                camY = glm::radians(89.0f);
            }

            camera->rotation = glm::mat4(1.0f);
            camera->rotate(camY, camX, 0);
        }
        {
            glm::vec3 end;
            glm::vec3 norm;
            glm::vec3 iend;
            voxel* vox = chunks->rayCast(camera->position, camera->front, 10.0f, end, norm, iend);
            if (vox != nullptr)
            {
                lineBatch->box(iend.x+0.5f, iend.y+0.5f, iend.z+0.5f, 1.005f,1.005f,1.005f, 0,0,0,0.5f);

                if (Events::jclicked(GLFW_MOUSE_BUTTON_1))
                {
                    int x = (int)iend.x;
                    int y = (int)iend.y;
                    int z = (int)iend.z;
                    chunks->set(x,y,z, 0);
                    Lighting::onBlockSet(x,y,z,0);
                }
                if (Events::jclicked(GLFW_MOUSE_BUTTON_2))
                {
                    int x = (int)(iend.x)+(int)(norm.x);
                    int y = (int)(iend.y)+(int)(norm.y);
                    int z = (int)(iend.z)+(int)(norm.z);
                    chunks->set(x, y, z, cur_id);
                    Lighting::onBlockSet(x,y,z, cur_id);
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw VAO
        mains->use();
        mains->uniformMatrix("projview", camera->getProjection()*camera->getView());
        texture->bind();
        glm::mat4 model(1.0f);
        for (size_t i = 0; i < chunks->volume; i++)
        {

            Chunk* chunk = chunks->chunks[i];
            if (chunk == nullptr)
                continue;
            Mesh* mesh = chunks->meshes[i];
            if (mesh == nullptr)
                continue;
            model = glm::translate(glm::mat4(1.0f), glm::vec3(chunk->x*CHUNK_W+0.5f, chunk->y*CHUNK_H+0.5f, chunk->z*CHUNK_D+0.5f));
            mains->uniformMatrix("model", model);
            mesh->draw(GL_TRIANGLES);
        }

        crosshairShader->use();
        crosshair->draw(GL_LINES);

        boxshader->use();
        boxshader->uniformMatrix("projview", camera->getProjection()*camera->getView());
        glLineWidth(2.0f);
        lineBatch->render();

        Window::swapBuffers();

    }
    Lighting::finalize();

    for (unsigned int i = 0; i < chunks->volume; i++)
    {
        Chunk* chunk = chunks->chunks[i];
        if (chunk == nullptr)
            continue;
        wfile.put((const char*)chunk->voxels, chunk->x, chunk->z);
    }

    wfile.write();

    delete mains;
    delete texture;
    delete chunks;
    delete crosshair;
    delete crosshairShader;
    delete boxshader;
    delete lineBatch;

    Window::terminate();
    return 0;
}

