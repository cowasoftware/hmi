#include "OpenGLManager.h"
#include "Glm.h"
#include <math.h>
//#include "SendToMessageTest.h"
#include <set>
#include "StbImage.h"
#include "VertexShaderSource.h"
#include "FragmentShaderSource.h"
#include "PointLightGL.h"
#include "ParallelLightGL.h"
#include "SpotLightGL.h"
#include "ShaderNameDataManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "CalcString.h"
#include "cppgl.h"

OpenGLManager::OpenGLManager():
m_GL(nullptr),
m_window(nullptr),
m_programId(0),
m_isOpenDepthTest(false),
m_isOpenStencilTest(false),
m_isOpenBlend(false),
m_isOpenCullFace(false),
m_deltaTime(1.0),
m_cameraLook(nullptr),
m_cameraPos(nullptr),
m_cameraFront(nullptr),
m_cameraUp(nullptr),
m_major(0),
m_minor(0),
m_isES(false),
m_spShaderNameData(nullptr)
{
	m_cameraLook = new GlmVec3;
	m_cameraPos = new GlmVec3;
	m_cameraFront = new GlmVec3;
	m_cameraUp = new GlmVec3;
}

OpenGLManager::~OpenGLManager()
{
	delete m_cameraLook;
	m_cameraLook = nullptr;
	delete m_cameraPos;
	m_cameraPos = nullptr;
	delete m_cameraFront;
	m_cameraFront = nullptr;
	delete m_cameraUp;
	m_cameraUp = nullptr;
}

OpenGLManager& OpenGLManager::instance()
{
	static OpenGLManager s_openGLManager;
	return s_openGLManager;
}

void OpenGLManager::initGL(cppgl::CppGL* gl)
{
	m_GL = gl;
}

void OpenGLManager::initEnvironment(int32_t major, int32_t minor, bool isES)
{
	//glfwInit();
	////glfwWindowHint(GLFW_SAMPLES, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_major = major;
	m_minor = minor;
	m_isES = isES;

//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, cppgl::CPPGL_TRUE);
//#endif
}

//bool OpenGLManager::initOpenGLFunction()
//{
//	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == cppgl::CPPGL_TRUE;
//}

void OpenGLManager::setShaderNameData(const std::shared_ptr<ShaderNameData>& spShaderNameData)
{
	m_spShaderNameData = spShaderNameData;
}

//void OpenGLManager::uninit()
//{
//	glfwTerminate();
//}

void OpenGLManager::openDepthTest()
{
	m_GL->Enable(cppgl::CPPGL_DEPTH_TEST);
	m_isOpenDepthTest = true;
}

void OpenGLManager::closeDepthTest()
{
	m_GL->Disable(cppgl::CPPGL_DEPTH_TEST);
	m_isOpenDepthTest = false;
}

void OpenGLManager::keepDepthTest(bool isKeep)
{
	if (!m_isOpenDepthTest)
	{
		return;
	}
	m_GL->DepthMask(isKeep ? cppgl::CPPGL_FALSE : cppgl::CPPGL_TRUE);
}

void OpenGLManager::setDepthMode(int32_t mode)
{
	if (!m_isOpenDepthTest)
	{
		return;
	}
	m_GL->DepthFunc(mode);
}

void OpenGLManager::openStencilTest()
{
	m_GL->Enable(cppgl::CPPGL_STENCIL_TEST);
	m_isOpenStencilTest = true;
}

void OpenGLManager::closeStencilTest()
{
	m_GL->Disable(cppgl::CPPGL_STENCIL_TEST);
	m_isOpenStencilTest = false;
}

void OpenGLManager::setStencilMaskValue(unsigned char mask)
{
	if (!m_isOpenStencilTest)
	{
		return;
	}
	m_GL->StencilMask(mask);
}

void OpenGLManager::setStencilFunMode(int32_t mode, bool isUse, unsigned char mask)
{
	if (!m_isOpenStencilTest)
	{
		return;
	}
	m_GL->StencilFunc(mode, (int32_t)isUse, mask);
}

void OpenGLManager::setStencilAction(int32_t failMode, int32_t dpFailMode, int32_t dpPassMode)
{
	if (!m_isOpenStencilTest)
	{
		return;
	}
	m_GL->StencilOp(failMode, dpFailMode, dpPassMode);
}

void OpenGLManager::openBlend()
{
	m_GL->Enable(cppgl::CPPGL_BLEND);
}

void OpenGLManager::closeBlend()
{
	m_GL->Disable(cppgl::CPPGL_BLEND);
}

void OpenGLManager::setBlendFunMode(int32_t sourceMode, int32_t destMode)
{
	if (!m_isOpenBlend)
	{
		return;
	}
	m_GL->BlendFunc(sourceMode, destMode);
}

void OpenGLManager::setBlendSeparateMode(int32_t rMode, int32_t gMode, int32_t bMode, int32_t aMode)
{
	if (!m_isOpenBlend)
	{
		return;
	}
	m_GL->BlendFuncSeparate(rMode, gMode, bMode, aMode);
}

void OpenGLManager::setBlendCalcMode(int32_t calcMode)
{
	if (!m_isOpenBlend)
	{
		return;
	}
	m_GL->BlendEquation(calcMode);
}

void OpenGLManager::openCullFace()
{
	m_GL->Enable(cppgl::CPPGL_CULL_FACE);
}

void OpenGLManager::closeCullFace()
{
	m_GL->Disable(cppgl::CPPGL_CULL_FACE);
}

void OpenGLManager::setCullFaceMode(bool isCullFront)
{
	m_GL->CullFace(isCullFront ? cppgl::CPPGL_FRONT : cppgl::CPPGL_BACK);
}

void OpenGLManager::setCullFaceFront(bool isFrontClockwise)
{
	m_GL->FrontFace(isFrontClockwise ? cppgl::CPPGL_CW : cppgl::CPPGL_CCW);
}

//GLFWwindow* OpenGLManager::createWindow(int32_t width, int32_t height, const std::string& windowName)
//{
//	return glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
//}
//
//void OpenGLManager::selectWindow(GLFWwindow* window)
//{
//	m_window = window;
//	glfwMakeContextCurrent(window);
//}
//
//void OpenGLManager::setOnSize(void(*onSize)(GLFWwindow*, int32_t, int32_t))
//{
//	if (m_window == nullptr)
//	{
//		return;
//	}
//	glfwSetFramebufferSizeCallback(m_window, onSize);
//}

void OpenGLManager::setViewPort(int32_t x, int32_t y, int32_t width, int32_t height)
{
	m_GL->Viewport(x, y, width, height);
}

//bool OpenGLManager::shouldCloseWindow()
//{
//	if (m_window == nullptr)
//	{
//		return true;
//	}
//	return glfwWindowShouldClose(m_window);
//}
//
//void OpenGLManager::setShouldCloseWindow(bool shouldClose)
//{
//	if (m_window == nullptr)
//	{
//		return;
//	}
//	glfwSetWindowShouldClose(m_window, shouldClose);
//}
//
//int32_t OpenGLManager::getKeyStatus(int32_t code)
//{
//	if (m_window == nullptr)
//	{
//		return 0;
//	}
//	return glfwGetKey(m_window, code);
//}

void OpenGLManager::setBackgroundColor(int32_t r, int32_t g, int32_t b, int32_t a)
{
	m_GL->ClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 100.0f);
}

void OpenGLManager::brushBackground()
{
	auto field = m_isOpenDepthTest ? cppgl::CPPGL_COLOR_BUFFER_BIT | cppgl::CPPGL_DEPTH_BUFFER_BIT : cppgl::CPPGL_COLOR_BUFFER_BIT;
	field = m_isOpenStencilTest ? cppgl::CPPGL_STENCIL_BUFFER_BIT | field : field;
	m_GL->Clear(field);
}

//void OpenGLManager::paint()
//{
//	glfwSwapBuffers(m_window);
//}
//
//void OpenGLManager::pollEvents()
//{
//	glfwPollEvents();
//}

int32_t OpenGLManager::createShader(int32_t shaderType, const std::string& source)
{
	unsigned int vertexShader = m_GL->CreateShader(shaderType);

	const char* src = source.c_str();

    m_GL->ShaderSource(vertexShader, 1, &src, NULL);
    m_GL->CompileShader(vertexShader);
	return vertexShader;
}

std::string OpenGLManager::getCreateShaderError(int32_t shaderId)
{
	int32_t success = 0;
    char infoLog[1024] = {};
    m_GL->GetShaderiv(shaderId, cppgl::CPPGL_COMPILE_STATUS, &success);

    if(!success)
    {
        m_GL->GetShaderInfoLog(shaderId, 1024, NULL, infoLog);
    }
	return infoLog;
}

void OpenGLManager::destroyShader(int32_t shaderId)
{
	m_GL->DeleteShader(shaderId);
}

int32_t OpenGLManager::createProgram()
{
	return m_GL->CreateProgram();
}

void OpenGLManager::setProgramId(int32_t programId)
{
	m_programId = programId;
}

void OpenGLManager::selectProgram(int32_t programId)
{
	setProgramId(programId);
	activeProgram();
}

void OpenGLManager::destroyProgram(int32_t programId)
{
	m_GL->DeleteProgram(programId);
}

void OpenGLManager::addShader(int32_t shaderId)
{
	if (m_programId == 0)
	{
		return;
	}
	m_GL->AttachShader(m_programId, shaderId);
}

void OpenGLManager::link()
{
	if (m_programId == 0)
	{
		return;
	}
	m_GL->LinkProgram(m_programId);
}

std::string OpenGLManager::getLinkShaderError()
{
	if (m_programId == 0)
	{
		return "";
	}
	int32_t success = 0;
    char infoLog[1024] = {};
	m_GL->GetProgramiv(m_programId, cppgl::CPPGL_LINK_STATUS, &success);
    if(!success)
    {
        m_GL->GetProgramInfoLog(m_programId, 1024, NULL, infoLog);
    }
	return infoLog;
}

void OpenGLManager::activeProgram()
{
	if (m_programId == 0)
	{
		return;
	}
	m_GL->UseProgram(m_programId);
}

void OpenGLManager::vertexDataExplain(int32_t location, int32_t dimension, int32_t dataType, bool isNormal, int32_t stride, size_t offset)
{
	m_GL->VertexAttribPointer(location, dimension, dataType, !isNormal, stride, (void*)offset);
}

void OpenGLManager::useVertexData(int32_t location)
{
	m_GL->EnableVertexAttribArray(location);
}

uint32_t OpenGLManager::createVertexObject()
{
	uint32_t result;
	m_GL->GenVertexArrays(1, &result);
	return result;
}

std::vector<uint32_t> OpenGLManager::createVertexObjects(int32_t num)
{
	std::vector<uint32_t> result;
	result.resize(num);
	m_GL->GenVertexArrays(num, &(result[0]));
	return result;
}

void OpenGLManager::selectVertexObject(uint32_t vertexObjectId)
{
	m_GL->BindVertexArray(vertexObjectId);
}

void OpenGLManager::destroyVertexObject(uint32_t vertexObjectId)
{
	if (vertexObjectId == 0)
	{
		return;
	}
	m_GL->DeleteVertexArrays(1, &vertexObjectId);
}

void OpenGLManager::destroyVertexObjects(const std::vector<uint32_t>& vertexObjects)
{
	if (vertexObjects.empty())
	{
		return;
	}
	m_GL->DeleteVertexArrays(vertexObjects.size(), &vertexObjects[0]);
}

uint32_t OpenGLManager::createVertexBuffer()
{
	uint32_t VBOId;
    m_GL->GenBuffers(1, &VBOId);
	return VBOId;
}

std::vector<uint32_t> OpenGLManager::createVertexBuffers(int32_t num)
{
	std::vector<uint32_t> result;
	result.resize(num);
	m_GL->GenBuffers(num, &(result[0]));
	return result;
}

void OpenGLManager::selectVertexBuffer(uint32_t vertexBufferId)
{
	m_GL->BindBuffer(cppgl::CPPGL_ARRAY_BUFFER, vertexBufferId);
}

void OpenGLManager::destroyVertexBuffer(uint32_t vertexBufferId)
{
	if (vertexBufferId == 0)
	{
		return;
	}
	m_GL->DeleteBuffers(1, &vertexBufferId);
}

void OpenGLManager::destroyVertexBuffers(const std::vector<uint32_t>& vertexBuffers)
{
	if (vertexBuffers.empty())
	{
		return;
	}
	m_GL->DeleteBuffers(vertexBuffers.size(), &vertexBuffers[0]);
}

void OpenGLManager::destroyModelId(const std::vector<MeshIdInfo>& modelIdInfo)
{
	std::set<uint32_t> allTextureId;
	for (std::size_t meshIndex = 0; meshIndex < modelIdInfo.size(); ++meshIndex)
	{
		const MeshIdInfo& idInfo = modelIdInfo[meshIndex];
		OpenGLManager::instance().destroyVertexElement(idInfo.m_EBOId);
    	OpenGLManager::instance().destroyVertexBuffer(idInfo.m_VBOId);
    	OpenGLManager::instance().destroyVertexObject(idInfo.m_VAOId);
		for (auto itTextureId = idInfo.m_textureIdMap.begin(); itTextureId != idInfo.m_textureIdMap.end(); ++itTextureId)
		{
			const std::vector<std::pair<uint32_t, std::string>>& vecTextureId = itTextureId->second;
			for (std::size_t textureIndex = 0; textureIndex < vecTextureId.size(); ++textureIndex)
			{
				allTextureId.insert(vecTextureId[textureIndex].first);
			}
		}
		OpenGLManager::instance().destroyVertexObject(idInfo.m_programId);
	}

	for (auto itId = allTextureId.begin(); itId != allTextureId.end(); ++itId)
	{
		OpenGLManager::instance().destroyTexture(*itId);
	}
}

void OpenGLManager::vertexDataCopy(const void* data, int32_t size, int32_t dataUsage)
{
	m_GL->BufferData(cppgl::CPPGL_ARRAY_BUFFER, size, data, dataUsage);
}

std::vector<MeshIdInfo> OpenGLManager::addModelData(const std::vector<ModelMeshInfo>& modelData,
	std::vector<std::shared_ptr<LightGL>>& vecLight, const GlmMat4& model, const GlmMat4& projection,
	bool hasObjectColor, const GlmVec3& objectColor, bool isLoadTexture, int32_t shaderTextureBeginIndex)
{
	std::map<std::string, uint32_t> textureIdMap;
	std::vector<MeshIdInfo> result;
	for (std::size_t meshIndex = 0; meshIndex < modelData.size(); ++meshIndex)
	{
		const ModelMeshInfo& modelMashInfo = modelData[meshIndex];
		result.emplace_back(MeshIdInfo());
		MeshIdInfo& meshIdInfo = result.back();

		VertexShaderSource vertexShaderSource;
		vertexShaderSource.init(m_major, m_minor, m_isES);
		vertexShaderSource.initShaderNameData(m_spShaderNameData);
		vertexShaderSource.addPosition();
		if (modelMashInfo.m_hasColor)
		{
			vertexShaderSource.addColor();
		}
		if (modelMashInfo.m_hasNormal && !vecLight.empty())
		{
			vertexShaderSource.addLight();
		}
		//一个mesh中有的纹理坐标数量，IN_TEXTURE
		vertexShaderSource.addTextureCoords(modelMashInfo.m_textureCoordCount);

		//RCSend("%s", vertexShaderSource.toString().c_str());
		int32_t vertexShaderId = OpenGLManager::instance().createShader(cppgl::CPPGL_VERTEX_SHADER,
			vertexShaderSource.toString().c_str());
    	std::string error = OpenGLManager::instance().getCreateShaderError(vertexShaderId);
    	if (!error.empty())
    	{
    	    printf("error = %s\n", error.c_str());
    	}

		FragmentShaderSource fragmentShaderSource;
		fragmentShaderSource.init(m_major, m_minor, m_isES);
		fragmentShaderSource.initShaderNameData(m_spShaderNameData);
		if (modelMashInfo.m_hasColor)
		{
			fragmentShaderSource.addColor();
		}
		if (hasObjectColor)
		{
			fragmentShaderSource.addObjectColor();
		}
		if (modelMashInfo.m_hasMaterialColor)
		{
			fragmentShaderSource.addMaterial();
		}
		fragmentShaderSource.addTextureCoords(modelMashInfo.m_texturePathMap);
		if (modelMashInfo.m_hasNormal)
		{
			for (std::size_t lightIndex = 0; lightIndex < vecLight.size(); ++lightIndex)
			{
				fragmentShaderSource.addLight(vecLight[lightIndex]);
			}
		}

		//RCSend("%s", fragmentShaderSource.toString().c_str());
		int32_t fragmentShaderId = OpenGLManager::instance().createShader(cppgl::CPPGL_FRAGMENT_SHADER,
			fragmentShaderSource.toString().c_str());
    	error = OpenGLManager::instance().getCreateShaderError(fragmentShaderId);
    	if (!error.empty())
    	{
    	    printf("error = %s\n", error.c_str());
    	}

		//创建着色器程序
    	int32_t programId = OpenGLManager::instance().createProgram();
    	OpenGLManager::instance().setProgramId(programId);
    	OpenGLManager::instance().addShader(vertexShaderId);
    	OpenGLManager::instance().addShader(fragmentShaderId);
    	OpenGLManager::instance().link();
    	error = OpenGLManager::instance().getLinkShaderError();
    	if (!error.empty())
    	{
    	    printf("error = %s\n", error.c_str());
    	}

    	//激活程序
    	OpenGLManager::instance().activeProgram();

		OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[MODEL].second, model.valuePtr());
		OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[PROJECTION].second, projection.valuePtr());

		if (hasObjectColor)
		{
			OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[OBJECT_COLOR].second, objectColor);
		}

		if (modelMashInfo.m_hasMaterialColor)
		{
			OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[AMBIENT_STRENGTH].second,
				modelMashInfo.m_ambientColor);
    		OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[DIFFUSE_STRENGTH].second,
				modelMashInfo.m_diffuseColor);
    		OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[SPECULAR_STRENGTH].second,
				modelMashInfo.m_specularColor);
    		OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[SHININESS_STRENGTH].second,
				modelMashInfo.m_shininess);
		}

		if (modelMashInfo.m_hasNormal)
		{
			for (std::size_t lightIndex = 0; lightIndex < vecLight.size(); ++lightIndex)
			{
				OpenGLManager::instance().searchSetUniformValue(CalcString(m_spShaderNameData->m_name[LIGHT_COLOR].second,
					lightIndex).toString(), vecLight[lightIndex]->lightColor());

				std::shared_ptr<ParallelLightGL> light = std::dynamic_pointer_cast<ParallelLightGL>(vecLight[lightIndex]);
				LightGLType type = vecLight[lightIndex]->type();
				if (type == PARALLEL)
				{
					std::shared_ptr<ParallelLightGL> light = std::dynamic_pointer_cast<ParallelLightGL>(vecLight[lightIndex]);
					OpenGLManager::instance().searchSetUniformValue(CalcString(m_spShaderNameData->m_name[LIGHT_DIRECTION].second, lightIndex),
						light->lightDirection());
				}
				else if (type == POINT || type == SPOT)
				{
					std::shared_ptr<PointLightGL> light = std::dynamic_pointer_cast<PointLightGL>(vecLight[lightIndex]);
					OpenGLManager::instance().searchSetUniformValue(CalcString(m_spShaderNameData->m_name[LIGHT_POS].second, lightIndex),
						light->lightPos());
					OpenGLManager::instance().searchSetUniformValue(CalcString(m_spShaderNameData->m_name[CONSTANT].second, lightIndex),
						light->attenuationConstant());
    				OpenGLManager::instance().searchSetUniformValue(CalcString(m_spShaderNameData->m_name[LINEAR].second, lightIndex),
						light->attenuationLinear());
    				OpenGLManager::instance().searchSetUniformValue(CalcString(m_spShaderNameData->m_name[QUADRATIC].second, lightIndex),
						light->attenuationQuadratic());
					
					if (type == SPOT)
					{
						std::shared_ptr<SpotLightGL> light = std::dynamic_pointer_cast<SpotLightGL>(vecLight[lightIndex]);
						OpenGLManager::instance().searchSetUniformValue(CalcString(m_spShaderNameData->m_name[SHINE_DIRECTION].second, lightIndex),
							light->shineDirection());
    					OpenGLManager::instance().searchSetUniformValue(CalcString(m_spShaderNameData->m_name[CUT_OFF].second, lightIndex),
							light->cutOffCos());
    					OpenGLManager::instance().searchSetUniformValue(CalcString(m_spShaderNameData->m_name[OUT_CUT_OFF].second, lightIndex),
							light->outCutOffCos());
					}
				}
			}
		}

		OpenGLManager::instance().destroyShader(vertexShaderId);
   		OpenGLManager::instance().destroyShader(fragmentShaderId);

		meshIdInfo.m_programId = programId;
		
		//创建顶点数据对象
    	meshIdInfo.m_VAOId = OpenGLManager::instance().createVertexObject();
    	OpenGLManager::instance().selectVertexObject(meshIdInfo.m_VAOId);

    	//创建顶点数据对象的缓冲区
    	meshIdInfo.m_VBOId = OpenGLManager::instance().createVertexBuffer();
    	OpenGLManager::instance().selectVertexBuffer(meshIdInfo.m_VBOId);

		OpenGLManager::instance().vertexDataCopy(&modelMashInfo.m_vertices[0],
			modelMashInfo.m_vertices.size() * sizeof(float), cppgl::CPPGL_STATIC_DRAW);

		int32_t rowCount = 3;
		if (modelMashInfo.m_hasNormal && !vecLight.empty())
		{
			rowCount += 3;
		}
		if (modelMashInfo.m_hasColor)
		{
			rowCount += 4;
		}
		rowCount += modelMashInfo.m_textureCoordCount * 2;

		int32_t offset = 0;
		int32_t locationIndex = 0;
		std::vector<int32_t> vecDimension;
		vecDimension.push_back(3);

		if (modelMashInfo.m_hasNormal && !vecLight.empty())
		{
			vecDimension.push_back(3);
		}
    	
		if (modelMashInfo.m_hasColor)
		{
			vecDimension.push_back(4);
		}

		for (int32_t coordIndex = 0; coordIndex < modelMashInfo.m_textureCoordCount; ++coordIndex)
		{
			vecDimension.push_back(2);
		}

		for (std::size_t dimensionIndex = 0; dimensionIndex < vecDimension.size(); ++dimensionIndex)
		{
			OpenGLManager::instance().vertexDataExplain(locationIndex, vecDimension[dimensionIndex],
				cppgl::CPPGL_FLOAT, true, rowCount * sizeof(float), offset * sizeof(float));
    		OpenGLManager::instance().useVertexData(locationIndex);
			offset += vecDimension[dimensionIndex];
			++locationIndex;
		}

		meshIdInfo.m_EBOId = OpenGLManager::instance().createVertexElement();
    	OpenGLManager::instance().selectVertexElement(meshIdInfo.m_EBOId);
		OpenGLManager::instance().vertexElementIndexCopy(&modelMashInfo.m_indices[0],
			modelMashInfo.m_indices.size() * sizeof(uint32_t), cppgl::CPPGL_STATIC_DRAW);

		if (isLoadTexture)
		{
			//当前只会有一张纹理图
			int32_t shaderTextureIndex = 0;

			for (auto itType = modelMashInfo.m_texturePathMap.begin(); itType != modelMashInfo.m_texturePathMap.end(); ++itType)
			{
				aiTextureType type = (aiTextureType)itType->first;
				//ShaderNameType shaderNameType = SHADER_NAME_TYPE_INIT;
				//if (type == aiTextureType_AMBIENT)
				//{
				//	shaderNameType = TEXTURE_AMBIENT;
				//}
				//else if (type == aiTextureType_DIFFUSE)
				//{
				//	shaderNameType = TEXTURE_DIFFUSE;
				//}
				//else if (type == aiTextureType_SPECULAR)
				//{
				//	shaderNameType = TEXTURE_SPECULAR;
				//}
				
				const std::vector<std::string>& vecTexturePicPath = itType->second;
				for (std::size_t textureIndex = 0; textureIndex < vecTexturePicPath.size(); ++textureIndex)
				{
					const std::string& modelPath = vecTexturePicPath[textureIndex];
					uint32_t textureId = 0;
					std::string textureName = CalcString(m_spShaderNameData->m_name[TEXTURE].second, shaderTextureIndex);
					auto itPath = textureIdMap.find(modelPath);
					if (itPath == textureIdMap.end())
					{
						textureId = OpenGLManager::instance().loadModelTexture(modelPath, textureName, shaderTextureIndex);
						textureIdMap[modelPath] = textureId;
					}
					else
					{
						textureId = itPath->second;
					}
					meshIdInfo.m_textureIdMap[type].push_back(std::pair<uint32_t, std::string>(textureId, textureName));
				}
			}
		}
	}

	return result;
}

uint32_t OpenGLManager::loadModelTexture(const std::string& texturePath, const std::string& shaderTextureName,
	int32_t shaderTextureIndex)
{
	int32_t imageWidth = 0;
    int32_t imageHeight = 0;
    int32_t imageChannels = 0;
    unsigned char* imageData = StbImage::loadImage(texturePath, imageWidth, imageHeight, imageChannels);
    if (imageData == nullptr)
    {
		printf("Failed to load image, path = %s\n", texturePath.c_str());
        return -1;
    }

	uint32_t textureId = OpenGLManager::instance().createTexture();
    OpenGLManager::instance().selectTextureAndType(textureId, cppgl::CPPGL_TEXTURE_2D, shaderTextureName, shaderTextureIndex);
    OpenGLManager::instance().setTextureWrapTypeX(imageChannels == 4 ? cppgl::CPPGL_CLAMP_TO_EDGE : cppgl::CPPGL_REPEAT);
    OpenGLManager::instance().setTextureWrapTypeY(imageChannels == 4 ? cppgl::CPPGL_CLAMP_TO_EDGE : cppgl::CPPGL_REPEAT);
    OpenGLManager::instance().setMinFilterType(cppgl::CPPGL_LINEAR);
    OpenGLManager::instance().setMagFilterType(cppgl::CPPGL_NEAREST);
	OpenGLManager::instance().loadTexture(imageWidth, imageHeight, imageData, imageChannels);

	StbImage::freeImage(imageData);
	return textureId;
}

void OpenGLManager::drawModelData(const std::vector<MeshIdInfo>& modelIdInfo, const std::vector<ModelMeshInfo>& modelDataInfo,
	const GlmMat4& model)
{
	for (std::size_t modelMeshIndex = 0; modelMeshIndex < modelDataInfo.size(); ++modelMeshIndex)
    {
        const ModelMeshInfo& modelMeshInfo = modelDataInfo[modelMeshIndex];
        const MeshIdInfo& meshIdInfo = modelIdInfo[modelMeshIndex];

        //先选择顶点数据或先选择着色器程序没有要求
		OpenGLManager::instance().selectProgram(meshIdInfo.m_programId);
        OpenGLManager::instance().selectVertexObject(meshIdInfo.m_VAOId);

		for (auto itType = meshIdInfo.m_textureIdMap.begin(); itType != meshIdInfo.m_textureIdMap.end(); ++itType)
		{
			const std::vector<std::pair<uint32_t, std::string>>& vecIdPair = itType->second;
			for (std::size_t textureIdIndex = 0; textureIdIndex < vecIdPair.size(); ++textureIdIndex)
			{
				//当前只会有一张纹理图
				OpenGLManager::instance().selectTextureAndType(vecIdPair[textureIdIndex].first, cppgl::CPPGL_TEXTURE_2D,
					vecIdPair[textureIdIndex].second, 0);
			}
		}

		OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[CAMERA_POS].second, *m_cameraPos);

		GlmMat4 view;
        view.initView(*m_cameraPos, *m_cameraLook, *m_cameraUp);
        OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[VIEW].second, view.valuePtr());

		OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[MODEL].second, model.valuePtr());

		if (modelMeshInfo.m_isAllTriangles)
		{
			OpenGLManager::instance().drawIndex(cppgl::CPPGL_TRIANGLES, 0, modelMeshInfo.m_indices.size());
		}
		else
		{
			int32_t indicesIndex = 0;
        	for (std::size_t faceIndex = 0; faceIndex < modelMeshInfo.m_indicesPointNum.size(); ++faceIndex)
        	{
        	    int32_t indicesNum = modelMeshInfo.m_indicesPointNum[faceIndex];
        	    OpenGLManager::instance().drawIndex(cppgl::CPPGL_TRIANGLE_FAN, indicesIndex, indicesNum);
        	    indicesIndex += indicesNum;
        	}
		}
    }
}

void OpenGLManager::draw(int32_t drawType, int32_t vertexDataIndex, int32_t vertexNum)
{
	m_GL->DrawArrays(drawType, vertexDataIndex, vertexNum);
}

uint32_t OpenGLManager::createVertexElement()
{
	unsigned int VBOId;
    m_GL->GenBuffers(1, &VBOId);
	return VBOId;
}

std::vector<uint32_t> OpenGLManager::createVertexElements(int32_t num)
{
	std::vector<uint32_t> result;
	result.resize(num);
	m_GL->GenBuffers(num, &(result[0]));
	return result;
}

void OpenGLManager::selectVertexElement(uint32_t vertexElementId)
{
	m_GL->BindBuffer(cppgl::CPPGL_ELEMENT_ARRAY_BUFFER, vertexElementId);
}

void OpenGLManager::destroyVertexElement(uint32_t vertexElementId)
{
	if (vertexElementId == 0)
	{
		return;
	}
	m_GL->DeleteBuffers(1, &vertexElementId);
}

void OpenGLManager::destroyVertexElements(const std::vector<uint32_t>& vertexElements)
{
	if (vertexElements.empty())
	{
		return;
	}
	m_GL->DeleteBuffers(vertexElements.size(), &vertexElements[0]);
}

void OpenGLManager::vertexElementIndexCopy(const void* data, int32_t size, int32_t dataUsage)
{
	m_GL->BufferData(cppgl::CPPGL_ELEMENT_ARRAY_BUFFER, size, data, cppgl::CPPGL_STATIC_DRAW);
}

void OpenGLManager::drawIndex(int32_t drawType, std::size_t elementIndex, int32_t elementNum)
{
	m_GL->DrawElements(drawType, elementNum, cppgl::CPPGL_UNSIGNED_INT, (void*)(elementIndex * sizeof(uint32_t)));
}

void OpenGLManager::setDrawMode(int32_t mode)
{
	//m_GL->PolygonMode(cppgl::CPPGL_FRONT_AND_BACK, mode);
}

int32_t OpenGLManager::getUniformLocation(const std::string& uniformName)
{
	if (m_programId == 0)
	{
		return -1;
	}
	return m_GL->GetUniformLocation(m_programId, uniformName.c_str());
}

void OpenGLManager::setUniformValue(int32_t location, float num)
{
	if (location == -1)
	{
		return;
	}
	m_GL->Uniform1f(location, num);
}

void OpenGLManager::setUniformValue(int32_t location, float v0, float v1, float v2)
{
	if (location == -1)
	{
		return;
	}
	m_GL->Uniform3f(location, v0, v1, v2);
}

void OpenGLManager::setUniformValue(int32_t location, float v0, float v1, float v2, float v3)
{
	if (location == -1)
	{
		return;
	}
	m_GL->Uniform4f(location, v0, v1, v2, v3);
}

void OpenGLManager::searchSetUniformValue(const std::string& uniformName, float num)
{
	setUniformValue(getUniformLocation(uniformName), num);
}

void OpenGLManager::searchSetUniformValue(const std::string& uniformName, float v0, float v1, float v2)
{
	setUniformValue(getUniformLocation(uniformName), v0, v1, v2);
}

void OpenGLManager::searchSetUniformValue(const std::string& uniformName, const GlmVec3& vec3)
{
	setUniformValue(getUniformLocation(uniformName), vec3.x(), vec3.y(), vec3.z());
}

void OpenGLManager::searchSetUniformValue(const std::string& uniformName, float v0, float v1, float v2, float v3)
{
	setUniformValue(getUniformLocation(uniformName), v0, v1, v2, v3);
}

void OpenGLManager::searchSetMaterial(const MaterialGL& material)
{
	OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[AMBIENT_STRENGTH].second,
		material.ambientStrength());
	OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[DIFFUSE_STRENGTH].second,
		material.diffuseStrength());
	OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[SPECULAR_STRENGTH].second,
		material.specularStrength());
	OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[SHININESS_STRENGTH].second,
		material.shininessStrength());
}

void OpenGLManager::searchSetObjectColor(const GlmVec3& objectColor)
{
	OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[OBJECT_COLOR].second, objectColor);
}

void OpenGLManager::searchSetAllLight(const std::vector<std::shared_ptr<LightGL>>& vecLight)
{
	if (!vecLight.empty())
	{
		OpenGLManager::instance().searchUpdateCameraPos();
	}
	for (std::size_t index = 0; index < vecLight.size(); ++index)
	{
		std::shared_ptr<LightGL> spLight = vecLight[index];
		switch (spLight->type())
		{
			//平行光
			case PARALLEL:
			{
				const std::shared_ptr<ParallelLightGL>& spParallelLight = std::static_pointer_cast<ParallelLightGL>(spLight);
				OpenGLManager::instance().searchSetUniformValue(
					CalcString(m_spShaderNameData->m_name[LIGHT_DIRECTION].second, index),
					spParallelLight->lightDirection());
			}
			break;
			//聚光
			case SPOT:
			{
				const std::shared_ptr<SpotLightGL>& spSpotLightGL = std::static_pointer_cast<SpotLightGL>(spLight);
				OpenGLManager::instance().searchSetUniformValue(
					CalcString(m_spShaderNameData->m_name[SHINE_DIRECTION].second, index),
					spSpotLightGL->shineDirection());
				OpenGLManager::instance().searchSetUniformValue(
					CalcString(m_spShaderNameData->m_name[CUT_OFF].second, index),
					spSpotLightGL->cutOffCos());
				OpenGLManager::instance().searchSetUniformValue(
					CalcString(m_spShaderNameData->m_name[OUT_CUT_OFF].second, index),
					spSpotLightGL->outCutOffCos());
			}
			//点光源
			case POINT:
			{
				const std::shared_ptr<PointLightGL>& spPointLight = std::static_pointer_cast<PointLightGL>(spLight);
				OpenGLManager::instance().searchSetUniformValue(
					CalcString(m_spShaderNameData->m_name[LIGHT_POS].second, index),
					spPointLight->lightPos());
				OpenGLManager::instance().searchSetUniformValue(
					CalcString(m_spShaderNameData->m_name[CONSTANT].second, index),
					spPointLight->attenuationConstant());
				OpenGLManager::instance().searchSetUniformValue(
					CalcString(m_spShaderNameData->m_name[LINEAR].second, index),
					spPointLight->attenuationLinear());
				OpenGLManager::instance().searchSetUniformValue(
					CalcString(m_spShaderNameData->m_name[QUADRATIC].second, index),
					spPointLight->attenuationQuadratic());
				
			}
			break;
			default:
			break;
		}
		OpenGLManager::instance().searchSetUniformValue(
			CalcString(m_spShaderNameData->m_name[LIGHT_COLOR].second, index), spLight->lightColor());
	}
}

void OpenGLManager::searchUpdateView()
{
	//设置观察矩阵
	GlmMat4 view;
	view.initView(*m_cameraPos, *m_cameraLook, *m_cameraUp);
	OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[VIEW].second, view.valuePtr());
}

void OpenGLManager::searchUpdateCameraPos()
{
	OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[CAMERA_POS].second, *m_cameraPos);
}

void OpenGLManager::searchModifyModel(const GlmMat4& model)
{
	OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[MODEL].second, model.valuePtr());
}

void OpenGLManager::searchModifyProjection(const GlmMat4& projection)
{
	OpenGLManager::instance().searchSetUniformValue(m_spShaderNameData->m_name[PROJECTION].second, projection.valuePtr());
}

void OpenGLManager::searchModifyLightPos(int32_t index, const GlmVec3& lightPos)
{
	OpenGLManager::instance().searchSetUniformValue(CalcString(m_spShaderNameData->m_name[LIGHT_POS].second, index), lightPos);
}

void OpenGLManager::searchModifyShineDirection(int32_t index, const GlmVec3& shineDirection)
{
	OpenGLManager::instance().searchSetUniformValue(CalcString(m_spShaderNameData->m_name[SHINE_DIRECTION].second, index),
		shineDirection);
}

//double OpenGLManager::getTime()
//{
//	return glfwGetTime();
//}

uint32_t OpenGLManager::createTexture()
{
	uint32_t textureId = 0;
	m_GL->GenTextures(1, &textureId);
	return textureId;
}

std::vector<uint32_t> OpenGLManager::createTextures(int32_t num)
{
	std::vector<uint32_t> textureIds;
	textureIds.resize(num);
	m_GL->GenTextures(num, &textureIds[0]);
	return textureIds;
}

void OpenGLManager::selectTextureAndType(uint32_t textureId, int32_t textureType, const std::string& textureName, int32_t textureIndex)
{
	m_textureType = textureType;
	m_GL->Uniform1i(getUniformLocation(textureName), textureIndex);
	m_GL->ActiveTexture(cppgl::CPPGL_TEXTURE0 + textureIndex);
	m_GL->BindTexture(textureType, textureId);
}

void OpenGLManager::destroyTexture(uint32_t textureId)
{
	if (textureId == 0)
	{
		return;
	}
	m_GL->DeleteTextures(1, &textureId);
}

void OpenGLManager::destroyTextures(const std::vector<uint32_t>& textureIds)
{
	if (textureIds.empty())
	{
		return;
	}
	m_GL->DeleteTextures(textureIds.size(), &textureIds[0]);
}

void OpenGLManager::setTextureWrapTypeX(int32_t wrapType)
{
	if (m_textureType == 0)
	{
		return;
	}
	m_GL->TexParameteri(m_textureType, cppgl::CPPGL_TEXTURE_WRAP_S, wrapType);
}

void OpenGLManager::setTextureWrapTypeY(int32_t wrapType)
{
	if (m_textureType == 0)
	{
		return;
	}
	m_GL->TexParameteri(m_textureType, cppgl::CPPGL_TEXTURE_WRAP_T, wrapType);
}

void OpenGLManager::setTextureWrapTypeZ(int32_t wrapType)
{
	if (m_textureType == 0)
	{
		return;
	}
	m_GL->TexParameteri(m_textureType, cppgl::CPPGL_TEXTURE_WRAP_R, wrapType);
}

void OpenGLManager::setTextureBorderColor(int32_t r, int32_t g, int32_t b, int32_t a)
{
	if (m_textureType == 0)
	{
		return;
	}
	float borderColor[4] = { r / 255.0f, g / 255.0f, b / 255.0f, a / 100.0f };
	m_GL->TexParameterfv(m_textureType, cppgl::CPPGL_TEXTURE_BORDER_COLOR, borderColor);
}

void OpenGLManager::setMinFilterType(int32_t filterShowType, int32_t mipmapFilterShowType)
{
	if (m_textureType == 0)
	{
		return;
	}
	if (mipmapFilterShowType == 0)
	{
		m_GL->TexParameteri(m_textureType, cppgl::CPPGL_TEXTURE_MIN_FILTER, filterShowType);
		return;
	}
	if (filterShowType == cppgl::CPPGL_NEAREST && mipmapFilterShowType == cppgl::CPPGL_NEAREST)
	{
		m_GL->TexParameteri(m_textureType, cppgl::CPPGL_TEXTURE_MIN_FILTER, cppgl::CPPGL_NEAREST_MIPMAP_NEAREST);
	}
	else if (filterShowType == cppgl::CPPGL_NEAREST && mipmapFilterShowType == cppgl::CPPGL_LINEAR)
	{
		m_GL->TexParameteri(m_textureType, cppgl::CPPGL_TEXTURE_MIN_FILTER, cppgl::CPPGL_NEAREST_MIPMAP_LINEAR);
	}
	else if (filterShowType == cppgl::CPPGL_LINEAR && mipmapFilterShowType == cppgl::CPPGL_NEAREST)
	{
		m_GL->TexParameteri(m_textureType, cppgl::CPPGL_TEXTURE_MIN_FILTER, cppgl::CPPGL_LINEAR_MIPMAP_NEAREST);
	}
	else if (filterShowType == cppgl::CPPGL_LINEAR && mipmapFilterShowType == cppgl::CPPGL_LINEAR)
	{
		m_GL->TexParameteri(m_textureType, cppgl::CPPGL_TEXTURE_MIN_FILTER, cppgl::CPPGL_LINEAR_MIPMAP_LINEAR);
	}
	m_GL->GenerateMipmap(cppgl::CPPGL_TEXTURE_2D);
}

void OpenGLManager::setMagFilterType(int32_t filterShowType)
{
	if (m_textureType == 0)
	{
		return;
	}
	m_GL->TexParameteri(m_textureType, cppgl::CPPGL_TEXTURE_MAG_FILTER, filterShowType);
}

void OpenGLManager::loadTexture(int32_t width, int32_t height, unsigned char* data, int32_t imageChannels)
{
	if (imageChannels == 3)
	{
		loadRGBTexture(width, height, data);
	}
	else if (imageChannels == 4)
	{
		loadRGBATexture(width, height, data);
	}
}

void OpenGLManager::loadRGBTexture(int32_t width, int32_t height, unsigned char* data)
{
	if (m_textureType == 0)
	{
		return;
	}
	m_GL->TexImage2D(m_textureType, 0, cppgl::CPPGL_RGB, width, height, 0, cppgl::CPPGL_RGB, cppgl::CPPGL_UNSIGNED_BYTE, data);
}

void OpenGLManager::loadRGBATexture(int32_t width, int32_t height, unsigned char* data)
{
	if (m_textureType == 0)
	{
		return;
	}
	m_GL->TexImage2D(m_textureType, 0, cppgl::CPPGL_RGBA, width, height, 0, cppgl::CPPGL_RGBA, cppgl::CPPGL_UNSIGNED_BYTE, data);
}

void OpenGLManager::setUniformValue(int32_t location, float* mat4)
{
	if (mat4 == nullptr)
	{
		return;
	}
	m_GL->UniformMatrix4fv(location, 1, cppgl::CPPGL_FALSE, mat4);
}

void OpenGLManager::searchSetUniformValue(const std::string& uniformName, const float* mat4)
{
	if (mat4 == nullptr)
	{
		return;
	}
	m_GL->UniformMatrix4fv(getUniformLocation(uniformName), 1, cppgl::CPPGL_FALSE, mat4);
}

//void OpenGLManager::hideMouseAndLimitScope()
//{
//	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//}
//
//void OpenGLManager::setMouseMoveCallback(void(*mouseMoveCallback)(GLFWwindow*, double, double))
//{
//	glfwSetCursorPosCallback(m_window, mouseMoveCallback);
//}
//
//void OpenGLManager::setMouseScrollCallback(void(*mouseScrollCallback)(GLFWwindow*, double, double))
//{
//	glfwSetScrollCallback(m_window, mouseScrollCallback);
//}

void OpenGLManager::setLookPosition(double x, double y, float speed)
{
	static float lastX = x;
    static float lastY = y;
	//以前向量为起始方向，顺时针增加角度
    static float yaw = 0.0f;
	//以前向量为起始方向，向上看增加角度
    static float pitch = 0.0f;

    float xoffset = x - lastX;
    float yoffset = lastY - y;
    lastX = x;
    lastY = y;

    xoffset *= (speed * m_deltaTime);
    yoffset *= (speed * m_deltaTime);

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 5.0f)
    {
        pitch = 5.0f;
    }
    if(pitch < -30.0f)
    {
        pitch = -30.0f;
    }

	int32_t up = 0;
	float upX = m_cameraUp->x();
	float upY = m_cameraUp->y();
	float upZ = m_cameraUp->z();
	if (!floatCompareZero(upX) && floatCompareZero(upY) && floatCompareZero(upZ))
	{
		up = (int32_t)upX;
	}
	else if (floatCompareZero(upX) && !floatCompareZero(upY) && floatCompareZero(upZ))
	{
		up = 2 * (int32_t)upY;
	}
	else if (floatCompareZero(upX) && floatCompareZero(upY) && !floatCompareZero(upZ))
	{
		up = 3 * (int32_t)upZ;
	}

	int32_t front = 0;
	float frontX = m_cameraFront->x();
	float frontY = m_cameraFront->y();
	float frontZ = m_cameraFront->z();
	if (!floatCompareZero(frontX) && floatCompareZero(frontY) && floatCompareZero(frontZ))
	{
		front = (int32_t)frontX;
	}
	else if (floatCompareZero(frontX) && !floatCompareZero(frontY) && floatCompareZero(frontZ))
	{
		front = 2 * (int32_t)frontY;
	}
	else if (floatCompareZero(frontX) && floatCompareZero(frontY) && !floatCompareZero(frontZ))
	{
		front = 3 * (int32_t)frontZ;
	}

	if (up == 0 || front == 0)
	{
		return;
	}

	if (up == 3 && front == 2)
	{
		*m_cameraLook = Glm::normalize(GlmVec3(sin(Glm::radians(yaw)), cos(Glm::radians(yaw)), sin(Glm::radians(pitch))));
	}
	else if (up == 2 && front == -3)
	{
		//if(yaw > 90.0f)
    	//{
    	//    yaw = 90.0f;
    	//}
    	//if(yaw < -90.0f)
    	//{
    	//    yaw = -90.0f;
    	//}
		*m_cameraLook = Glm::normalize(GlmVec3(sin(Glm::radians(yaw)), sin(Glm::radians(pitch)), -cos(Glm::radians(pitch)) * cos(Glm::radians(yaw))));
	}
}

GlmVec3 OpenGLManager::getCameraLook()
{
	return *m_cameraLook;
}

GlmVec3 OpenGLManager::getCameraUp()
{
	return *m_cameraUp;
}

GlmVec3 OpenGLManager::getCameraFront()
{
	return *m_cameraFront;
}

void OpenGLManager::setDeltaTime(float deltaTime)
{
	m_deltaTime = deltaTime;
}

void OpenGLManager::initCameraPos(const GlmVec3& cameraPos)
{
	*m_cameraPos = cameraPos;
}

void OpenGLManager::initCameraUp(const GlmVec3& cameraUp)
{
	*m_cameraUp = Glm::normalize(cameraUp);
}

void OpenGLManager::initCameraFront(const GlmVec3& cameraFront)
{
	*m_cameraFront = Glm::normalize(cameraFront);
	*m_cameraLook = *m_cameraFront;
	//RCSend("look.x = %f, look.y = %f, look.z = %f", (*m_cameraLook).x(), (*m_cameraLook).y(), (*m_cameraLook).z());
}

void OpenGLManager::addCameraPosTranslate(double speed, const GlmVec3& direct)
{
	m_cameraPos->add(Glm::scale(Glm::normalize(direct), speed * m_deltaTime));
}

void OpenGLManager::setCameraLook(const GlmVec3& cameraLook)
{
	*m_cameraLook = Glm::normalize(cameraLook);
}

void OpenGLManager::setCameraPos(const GlmVec3& cameraPos)
{
	*m_cameraPos = cameraPos;
}

GlmVec3 OpenGLManager::getCameraPos()
{
	return *m_cameraPos;
}

void OpenGLManager::setLineWidth(float lineWidth)
{
	m_GL->LineWidth(lineWidth);
}

bool OpenGLManager::floatCompareZero(float num)
{
	const float EPSINON = 0.000001;
	if (num >= -EPSINON && num <= EPSINON)
	{
		return true;
	}
	return false;
}

void OpenGLManager::setCurrentExePath(const std::string& currentExePath)
{
	m_currentExePath = currentExePath;
}

std::string OpenGLManager::GetCurrentExePath()
{
	return m_currentExePath;
}