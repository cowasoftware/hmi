#include "./skybox.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <iostream>

using namespace glm;

using namespace three;

Skybox::Skybox(cppgl::CppGL &_gl) : gl_(_gl)
{
}

Skybox::~Skybox()
{
    gl_.DeleteBuffers(1, &vbo_);
    gl_.DeleteBuffers(1, &index_);
    gl_.DeleteVertexArrays(1, &vao_);
    gl_.DeleteTextures(1, &texture_);
    gl_.DeleteProgram(program_);
}

void Skybox::Init(std::vector<std::string> const &files)
{
    if(initalized_)
    {
        return;

    }
    

    gl_.GenTextures(1, &texture_);
    gl_.BindTexture(cppgl::CPPGL_TEXTURE_CUBE_MAP, texture_);

    int width, height, nrChannels;
    unsigned char *data;
    // stbi_set_flip_vertically_on_load( true ) ;

    for (size_t i = 0; i < files.size(); i++)
    {

        auto data = stbi_load(files[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            gl_.TexImage2D(cppgl::CPPGL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                           0, cppgl::CPPGL_RGBA, width, height, 0, cppgl::CPPGL_RGBA, cppgl::CPPGL_UNSIGNED_BYTE, data);
        }

        stbi_image_free(data);
    }

    gl_.TexParameteri(cppgl::CPPGL_TEXTURE_CUBE_MAP, cppgl::CPPGL_TEXTURE_MIN_FILTER, cppgl::CPPGL_LINEAR);
    gl_.TexParameteri(cppgl::CPPGL_TEXTURE_CUBE_MAP, cppgl::CPPGL_TEXTURE_MAG_FILTER, cppgl::CPPGL_LINEAR);
    gl_.TexParameteri(cppgl::CPPGL_TEXTURE_CUBE_MAP, cppgl::CPPGL_TEXTURE_WRAP_S, cppgl::CPPGL_CLAMP_TO_EDGE);
    gl_.TexParameteri(cppgl::CPPGL_TEXTURE_CUBE_MAP, cppgl::CPPGL_TEXTURE_WRAP_T, cppgl::CPPGL_CLAMP_TO_EDGE);
    gl_.TexParameteri(cppgl::CPPGL_TEXTURE_CUBE_MAP, cppgl::CPPGL_TEXTURE_WRAP_R, cppgl::CPPGL_CLAMP_TO_EDGE);

    auto vertices = std::vector<float>{

        -1.0f, 1.0f, 1.0f,  // 上左前顶点
        1.0f, 1.0f, 1.0f,   // 上右前顶点
        -1.0f, 1.0f, -1.0f, // 上左后顶点
        1.0f, 1.0f, -1.0f,  // 上右后顶点

        -1.0f, -1.0f, 1.0f,  // 下左前顶点
        1.0f, -1.0f, 1.0f,   // 下右前顶点
        -1.0f, -1.0f, -1.0f, // 下左后顶点
        1.0f, -1.0f, -1.0f,  // 下右后顶点
    };

    auto indices = std::vector<uint32_t>{

        1, 3, 0, 0, 3, 2, // Front

        4, 6, 5, 5, 6, 7, // Back

        0, 2, 4, 4, 2, 6, // Left

        5, 7, 1, 1, 7, 3, // Right

        5, 1, 4, 4, 1, 0, // Top

        6, 2, 7, 7, 2, 3 // Bottom
    };

    gl_.GenBuffers(1, &vbo_);
    gl_.BindBuffer(cppgl::CPPGL_ARRAY_BUFFER, vbo_);
    gl_.BufferData(cppgl::CPPGL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), cppgl::CPPGL_STATIC_DRAW);
    gl_.BindBuffer(cppgl::CPPGL_ARRAY_BUFFER, 0);

    gl_.GenBuffers(1, &index_);
    gl_.BindBuffer(cppgl::CPPGL_ARRAY_BUFFER, index_);
    gl_.BufferData(cppgl::CPPGL_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), cppgl::CPPGL_STATIC_DRAW);
    gl_.BindBuffer(cppgl::CPPGL_ARRAY_BUFFER, 0);

    gl_.GenVertexArrays(1, &vao_);
    gl_.BindVertexArray(vao_);

    gl_.BindBuffer(cppgl::CPPGL_ARRAY_BUFFER, vbo_);

    gl_.EnableVertexAttribArray(0);
    gl_.VertexAttribPointer(0, 3, cppgl::CPPGL_FLOAT, false, 0, nullptr);

    gl_.BindBuffer(cppgl::CPPGL_ELEMENT_ARRAY_BUFFER, index_);

    gl_.BindBuffer(cppgl::CPPGL_ARRAY_BUFFER, 0);
    gl_.BindVertexArray(0);

    auto glsl_version = gl_.GetGLSLVersion();

    std::stringstream version;
    version << "#version " << glsl_version.major << glsl_version.minor << glsl_version.revision << " " << glsl_version.type << "\n";

    std::string vertex_glsl = R"(
        precision highp float;
        precision highp int;

        layout(location = 0) in vec3 aPos;

        out vec3 TexCoords;

        uniform mat4 projection;
        uniform mat4 view;

        void main() {
            TexCoords = aPos;
            vec4 pos =  projection * view *  vec4(aPos,1.0);
            gl_Position = pos.xyww;
        } 
    )";
    vertex_glsl = version.str() + vertex_glsl;

    std::string fragment_glsl = R"(
        precision highp float;
        precision highp int;

        out vec4 FragColor;

        in vec3 TexCoords;

        uniform samplerCube skybox;

        void main()
        {    
            FragColor = texture(skybox, TexCoords);
        }
    )";

    fragment_glsl = version.str() + fragment_glsl;

    char log[1024] = {0};
    auto vertex_shader = gl_.CreateShader(cppgl::CPPGL_VERTEX_SHADER);
    auto vertex_glsl_data = vertex_glsl.c_str();
    gl_.ShaderSource(vertex_shader, 1, &vertex_glsl_data, nullptr);
    gl_.CompileShader(vertex_shader);
    memset(log, 0, sizeof(log));
    gl_.GetShaderInfoLog(vertex_shader, sizeof(log), NULL, log);

    if (strlen(log) > 0)
    {
        std::cerr << vertex_glsl_data << std::endl;
        throw std::logic_error(log);
    }

    auto fragment_shader = gl_.CreateShader(cppgl::CPPGL_FRAGMENT_SHADER);
    auto fragment_glsl_data = fragment_glsl.c_str();
    gl_.ShaderSource(fragment_shader, 1, &fragment_glsl_data, nullptr);
    gl_.CompileShader(fragment_shader);
    memset(log, 0, sizeof(log));
    gl_.GetShaderInfoLog(fragment_shader, sizeof(log), NULL, log);

    if (strlen(log) > 0)
    {
        std::cerr << fragment_glsl_data << std::endl;
        throw std::logic_error(log);
    }

    program_ = gl_.CreateProgram();
    gl_.AttachShader(program_, vertex_shader);
    gl_.AttachShader(program_, fragment_shader);
    gl_.LinkProgram(program_);
    gl_.DeleteShader(vertex_shader);
    gl_.DeleteShader(fragment_shader);
    memset(log, 0, sizeof(log));
    gl_.GetProgramInfoLog(program_, sizeof(log), NULL, log);

    if (strlen(log) > 0)
    {
        throw std::logic_error(log);
    }

    slot_ = 0;

    initalized_ = true;
}

void Skybox::Render(mat4 const& view, mat4 const& projection)
{
    if(!initalized_)
    {
        return;
    }
    
    auto q = quat(view);
    auto q2 = glm::quat(vec3(0, 1, 0), vec3(0, 0, 1));
    auto q3 = quat(vec3(-0.03, 0, 0)) * q * q2;
    auto view2 = mat4_cast(q3);

    gl_.DepthFunc(cppgl::CPPGL_LEQUAL);
    gl_.UseProgram(program_);
    gl_.Uniform1i(gl_.GetUniformLocation(program_, "skybox"), slot_);
    gl_.UniformMatrix4fv(gl_.GetUniformLocation(program_, "view"), 1, false, value_ptr(glm::mat4(glm::mat3(view2))));
    gl_.UniformMatrix4fv(gl_.GetUniformLocation(program_, "projection"), 1, false, value_ptr(projection));
    gl_.BindVertexArray(vao_);
    gl_.ActiveTexture(cppgl::CPPGL_TEXTURE0);
    gl_.BindTexture(cppgl::CPPGL_TEXTURE_CUBE_MAP, texture_);
    gl_.DrawElements(cppgl::CPPGL_TRIANGLES, 36, cppgl::CPPGL_UNSIGNED_INT, nullptr);
    gl_.BindVertexArray(0);
    gl_.DepthFunc(cppgl::CPPGL_LESS);
}
