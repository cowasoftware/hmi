#pragma once
#include <stdint.h>
#include <string>
#include <functional>
#include <vector>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include "ModelDataParam.h"
#include <memory>
#include "GlmMat4.h"
#include "MaterialGL.h"
#include "TextureType.h"

struct GLFWwindow;
typedef struct GLFWwindow GLFWwindow;
class GlmVec3;
class LightGL;
struct ShaderNameData;

namespace cppgl
{
	class CppGL;
}


/** OpenGL管理者
*/
class OpenGLManager
{
protected:
	/** 构造函数
	*/
	OpenGLManager();

	/** 析构函数
	*/
	~OpenGLManager();

public:
	/** 单一实例
	return 返回单一实例
	*/
	static OpenGLManager& instance();

public:
	/** 初始化OpenGL绘画指针
	@param [in] gl OpenGL绘画指针
	*/
	void initGL(cppgl::CppGL* gl);
	
	/** 初始化
	@param [in] major 大版本号
	@param [in] minor 小版本号
	@param [in] isES 是否使用es版本
	*/
	void initEnvironment(int32_t major = 3, int32_t minor = 3, bool isES = false);

	///** 初始化OpenGL函数，在选择窗口后才可以执行
	//@return 返回加载结果
	//*/
	//bool initOpenGLFunction();

	/** 设置着色器名字
	@param [in] spShaderNameData 着色器名字
	*/
	void setShaderNameData(const std::shared_ptr<ShaderNameData>& spShaderNameData);

	///** 反初始化
	//*/
	//void uninit();

	/** 开启深度测试
	*/
	void openDepthTest();

	/** 关闭深度测试
	*/
	void closeDepthTest();

	/** 保持当前深度缓冲
	@param [in] isKeep 是否保持，默认不保持
	*/
	void keepDepthTest(bool isKeep);

	/** 设置深度缓冲模式
	@param [in] mode 深度缓冲模式
	*/
	void setDepthMode(int32_t mode);

	/** 开启模板缓冲
	*/
	void openStencilTest();

	/** 关闭模板缓冲
	*/
	void closeStencilTest();

	/** 设置模板缓冲掩码值
	@param [in] mask 掩码值
	*/
	void setStencilMaskValue(unsigned char mask);

	/** 设置模板函数
	@param [in] mode 模板函数类型
	@param [in] isUse 是否使用
	@param [in] mask 掩码值
	*/
	void setStencilFunMode(int32_t mode, bool isUse, unsigned char mask);

	/** 设置模板过滤行为
	@param [in] failMode 模板测试失败时的行为类型
	@param [in] dpFailMode 模板测试通过深度测试失败时的行为类型
	@param [in] dpPassMode 模板测试和深度测试都通过时的行为类型
	*/
	void setStencilAction(int32_t failMode, int32_t dpFailMode, int32_t dpPassMode);

	/** 开启混合
	*/
	void openBlend();

	/** 关闭混合
	*/
	void closeBlend();
	
	/** 设置混合函数模式
	@param [in] sourceMode 源模式
	@param [in] destMode 目标模式
	*/
	void setBlendFunMode(int32_t sourceMode, int32_t destMode);

	/** 设置颜色分量的混合模式
	@param [in] rMode 红色分量模式
	@param [in] gMode 绿色分量模式
	@param [in] bMode 蓝色分量模式
	@param [in] aMode 透明分量模式
	*/
	void setBlendSeparateMode(int32_t rMode, int32_t gMode, int32_t bMode, int32_t aMode);

	/** 设置混合计算方式模式
	@param [in] calcMode 计算方式模式
	*/
	void setBlendCalcMode(int32_t calcMode);

	/** 开启面剔除
	*/
	void openCullFace();

	/** 关闭面剔除
	*/
	void closeCullFace();

	/** 设置面剔除模式
	@param [in] isCullFront 是否剔除正面，默认是false
	*/
	void setCullFaceMode(bool isCullFront);

	/** 设置正向面是否是顺时针，默认逆时针
	@param [in] isFrontClockwise 是否是顺时针，默认是false
	*/
	void setCullFaceFront(bool isFrontClockwise);

	///** 创建窗口
	//@param [in] width 窗口宽度
	//@param [in] height 窗口高度
	//@param [in] windowName 窗口名
	//@return 返回窗口指针
	//*/
	//GLFWwindow* createWindow(int32_t width, int32_t height, const std::string& windowName);

	///** 切换到某个窗口的上下文环境
	//@param [in] window 窗口指针
	//*/
	//void selectWindow(GLFWwindow* window);

	///** 设置窗口大小改变时的事件函数
	//@param [in] onSize 窗口大小改变时的事件函数
	//*/
	//void setOnSize(void(*onSize)(GLFWwindow*, int32_t, int32_t));

	/** 设置视口位置
	@param [in] x 左上角x坐标
	@param [in] y 左上角y坐标
	@param [in] width 宽度
	@param [in] height 高度
	*/
	void setViewPort(int32_t x, int32_t y, int32_t width, int32_t height);

	///** 是否应该关闭窗口
	//@return 返回是否应该关闭窗口
	//*/
	//bool shouldCloseWindow();

	///** 设置窗口是否需要关闭
	//@param [in] shouldClose 是否需要关闭
	//*/
	//void setShouldCloseWindow(bool shouldClose);

	///** 获取key的状态
	//@param [in] code 按键值
	//@return 返回按键状态
	//*/
	//int32_t getKeyStatus(int32_t code);

	/** 设置背景颜色
	@param [in] r 红色，0-255
	@param [in] g 绿色，0-255
	@param [in] b 蓝色，0-255
	@param [in] a 透明度，0-100
	*/
	void setBackgroundColor(int32_t r, int32_t g, int32_t b, int32_t a);

	/** 刷背景颜色
	*/
	void brushBackground();

	///** 绘制到屏幕
	//*/
	//void paint();

	///** 处理各类事件消息
	//*/
	//void pollEvents();

	/** 创建着色器
	@param [in] source 着色器代码
	@return 返回着色器id
	*/
	int32_t createShader(int32_t shaderType, const std::string& source);

	/** 获取创建着色器错误提示
	@param [in] shaderId 着色器id
	@return 出错时返回提示，否则返回空字符串
	*/
	std::string getCreateShaderError(int32_t shaderId);

	/** 销毁着色器
	@param [in] shaderId 着色器id
	*/
	void destroyShader(int32_t shaderId);

	/** 创建一个着色器程序
	@return 返回着色器程序id
	*/
	int32_t createProgram();

	/** 选择一个着色器程序
	@param [in] programId 着色器程序id
	*/
	void setProgramId(int32_t programId);

	/** 选择并激活一个着色器程序
	@param [in] programId 着色器程序id
	*/
	void selectProgram(int32_t programId);

	/** 销毁一个着色器程序
	@param [in] programId 着色器程序id
	*/
	void destroyProgram(int32_t programId);

	/** 添加一个着色器到程序
	@param [in] shaderId 着色器id
	*/
	void addShader(int32_t shaderId);

	/** 链接已添加的着色器
	*/
	void link();

	/** 获取创建着色器错误提示
	@return 出错时返回提示，否则返回空字符串
	*/
	std::string getLinkShaderError();

	/** 激活着色器程序
	*/
	void activeProgram();

	/** 顶点数据的解释
	@param [in] location 顶点属性的位置值
	@param [in] dimension 维度
	@param [in] dataType 数据类型
	@param [in] isNormal 是否是标准化数据，标准化数据为-1到1之间
	@param [in] stride 下一组数据离上一组数据的步长字节数
	@param [in] offset 偏移字节数
	*/
	void vertexDataExplain(int32_t location, int32_t dimension, int32_t dataType, bool isNormal, int32_t stride, size_t offset);

	/** 启动顶点数据
	@param [in] location 顶点属性的位置值
	*/
	void useVertexData(int32_t location);

	/** 创建顶点数组对象
	@return 返回数组对象id
	*/
	uint32_t createVertexObject();

	/** 批量创建顶点数组对象
	@param [in] num 对象个数
	@return 返回数组对象id集合
	*/
	std::vector<uint32_t> createVertexObjects(int32_t num);

	/** 选择顶点数组对象
	@param [in] vertexObjectId 顶点数组对象id
	*/
	void selectVertexObject(uint32_t vertexObjectId);

	/** 销毁顶点数组对象
	@param [in] vertexObjectId 顶点数组对象id
	*/
	void destroyVertexObject(uint32_t vertexObjectId);

	/** 批量销毁顶点数组对象
	@param [in] vertexObjects 顶点数组对象集合
	*/
	void destroyVertexObjects(const std::vector<uint32_t>& vertexObjects);

	/** 创建顶点数组对象的数据缓冲区
	@return 返回顶点数组对象的数据缓冲区id
	*/
	uint32_t createVertexBuffer();

	/** 批量创建顶点数组对象的数据缓冲区
	@param [in] num 对象个数
	@return 返回顶点数组对象数据缓冲区id的集合
	*/
	std::vector<uint32_t> createVertexBuffers(int32_t num);

	/** 选择顶点数组对象的数据缓冲区
	@param [in] vertexBufferId 顶点数组对象的数据缓冲区id
	*/
	void selectVertexBuffer(uint32_t vertexBufferId);

	/** 销毁顶点数组对象的数据缓冲区
	@param [in] vertexBufferId 顶点数组对象的数据缓冲区id
	*/
	void destroyVertexBuffer(uint32_t vertexBufferId);

	/** 批量销毁顶点数组对象的数据缓冲区集合
	@param [in] vertexBuffers 顶点数组对象的数据缓冲区的集合
	*/
	void destroyVertexBuffers(const std::vector<uint32_t>& vertexBuffers);

	/** 销毁模型相关资源
	@param [in] modelIdInfo 模型相关ID信息
	*/
	void destroyModelId(const std::vector<MeshIdInfo>& modelIdInfo);

	/** 顶点数据拷贝
	@param [in] data 数据指针
	@param [in] size 数据字节数
	@param [in] dataUsage 数据作用类型
	*/
	void vertexDataCopy(const void* data, int32_t size, int32_t dataUsage);

	/** 添加模型数据，包含着色器程序和数据
	@param [in] modelData 模型数据
	@param [in] vecLight 光源
	@param [in] model 模型位移矩阵
	@param [in] projection 投影矩阵
	@param [in] hasObjectColor 是否有物体主题颜色
	@param [in] objectColor 物体主题颜色，和顶点颜色不同，该颜色不在模型中，自定义主题颜色
	@param [in] isLoadTexture 是否加载纹理
	@param [in] shaderTextureBeginIndex 着色器中纹理变量的起始索引值
	@return 返回模型ID集合
	*/
	std::vector<MeshIdInfo> addModelData(const std::vector<ModelMeshInfo>& modelData,
		std::vector<std::shared_ptr<LightGL>>& vecLight, const GlmMat4& model, const GlmMat4& projection,
		bool hasObjectColor = false, const GlmVec3& objectColor = GlmVec3(),
		bool isLoadTexture = true, int32_t shaderTextureBeginIndex = 0);

	/** 加载模型纹理
	@param [in] rootName 模型文件夹名
	@param [in] texturePath 纹理图片路径
	@param [in] shaderTextureName 着色器中的纹理变量名
	@param [in] shaderTextureBeginIndex 着色器中纹理变量的起始索引值
	@return 返回纹理ID
	*/
	uint32_t loadModelTexture(const std::string& texturePath, const std::string& shaderTextureName,
		int32_t shaderTextureBeginIndex);

	/** 绘制模型
	@param [in] modelIdInfo 模型相关的ID信息
	@param [in] modelDataInfo 模型数据信息
	*/
	void drawModelData(const std::vector<MeshIdInfo>& modelIdInfo, const std::vector<ModelMeshInfo>& modelDataInfo,
		const GlmMat4& model);

	/** 绘制图形
	@param [in] drawType 绘制类型
	@param [in] vertexDataIndex 顶点，以点为单位的索引值，点的大小取决于解释
	@param [in] vertexNum 顶点个数
	*/
	void draw(int32_t drawType, int32_t vertexDataIndex, int32_t vertexNum);

	/** 创建顶点数组对象的数据缓冲区
	@return 返回顶点数组对象的数据缓冲区id
	*/
	uint32_t createVertexElement();

	/** 批量创建顶点数组对象的数据缓冲区
	@param [in] num 对象个数
	@return 返回顶点数组对象数据缓冲区id的集合
	*/
	std::vector<uint32_t> createVertexElements(int32_t num);

	/** 选择顶点数组对象的数据缓冲区
	@param [in] vertexElementId 顶点数组对象的数据缓冲区id
	*/
	void selectVertexElement(uint32_t vertexElementId);

	/** 销毁顶点数组对象的数据缓冲区
	@param [in] vertexElementId 顶点数组对象的数据缓冲区id
	*/
	void destroyVertexElement(uint32_t vertexElementId);

	/** 批量销毁顶点数组对象的数据缓冲区集合
	@param [in] vertexElements 顶点数组对象的数据缓冲区的集合
	*/
	void destroyVertexElements(const std::vector<uint32_t>& vertexElements);

	/** 顶点数据元素索引拷贝
	@param [in] data 数据指针
	@param [in] size 数据字节数
	@param [in] dataUsage 数据作用类型
	*/
	void vertexElementIndexCopy(const void* data, int32_t size, int32_t dataUsage);

	/** 按照索引绘制图形
	@param [in] drawType 绘制类型
	@param [in] elementIndex 索引起始位置
	@param [in] elementNum 索引个数
	*/
	void drawIndex(int32_t drawType, std::size_t elementIndex, int32_t elementNum);

	/** 设置绘图类型
	@param [in] mode 线或填充，GL_LINE或GL_FILL
	*/
	void setDrawMode(int32_t mode);

	/** 获取当前激活的着色器程序中全局变量所在索引位置
	@param [in] uniformName 变量名
	@return 返回变量所在位置
	*/
	int32_t getUniformLocation(const std::string& uniformName);

	/** 设置全局变量内容
	@param [in] location 变量索引位置
	@param [in] num 值
	*/
	void setUniformValue(int32_t location, float num);

	/** 设置全局变量内容
	@param [in] location 变量索引位置
	@param [in] v0 分量0
	@param [in] v1 分量1
	@param [in] v2 分量2
	*/
	void setUniformValue(int32_t location, float v0, float v1, float v2);

	/** 设置全局变量内容
	@param [in] location 变量索引位置
	@param [in] v0 分量0
	@param [in] v1 分量1
	@param [in] v2 分量2
	@param [in] v3 分量3
	*/
	void setUniformValue(int32_t location, float v0, float v1, float v2, float v3);

	/** 搜索位置并设置全局变量内容
	@param [in] uniformName 变量名
	@param [in] num 值
	*/
	void searchSetUniformValue(const std::string& uniformName, float num);

	/** 搜索位置并设置全局变量内容
	@param [in] uniformName 变量名
	@param [in] v0 分量0
	@param [in] v1 分量1
	@param [in] v2 分量2
	*/
	void searchSetUniformValue(const std::string& uniformName, float v0, float v1, float v2);

	/** 搜索位置并设置全局变量内容
	@param [in] uniformName 变量名
	@param [in] vec3 向量
	*/
	void searchSetUniformValue(const std::string& uniformName, const GlmVec3& vec3);

	/** 搜索位置并设置全局变量内容
	@param [in] uniformName 变量名
	@param [in] v0 分量0
	@param [in] v1 分量1
	@param [in] v2 分量2
	@param [in] v3 分量3
	*/
	void searchSetUniformValue(const std::string& uniformName, float v0, float v1, float v2, float v3);

	/** 设置材质
	@param [in] material 材质
	*/
	void searchSetMaterial(const MaterialGL& material);

	/** 设置物体颜色
	@param [in] objectColor 物体颜色
	*/
	void searchSetObjectColor(const GlmVec3& objectColor);

	/** 设置光源
	@param [in] vecLight 所有光源
	*/
	void searchSetAllLight(const std::vector<std::shared_ptr<LightGL>>& vecLight);

	/** 更新观察矩阵
	*/
	void searchUpdateView();

	/** 更新着色器中的摄像机位置
	*/
	void searchUpdateCameraPos();

	/** 改变物体位置
	@param [in] model 物体位置
	*/
	void searchModifyModel(const GlmMat4& model);

	/** 改变投影矩阵
	@param [in] projection 投影矩阵
	*/
	void searchModifyProjection(const GlmMat4& projection);

	/** 改变光源位置
	@param [in] index 光源索引值
	@param [in] lightPos 光源位置
	*/
	void searchModifyLightPos(int32_t index, const GlmVec3& lightPos);

	/** 改变照射方向
	@param [in] index 光源索引值
	@param [in] shineDirection 照射方向
	*/
	void searchModifyShineDirection(int32_t index, const GlmVec3& shineDirection);

	///** 获取时间
	//@return 返回时间
	//*/
	//double getTime();

	/** 创建纹理
	@return 返回纹理id
	*/
	uint32_t createTexture();

	/** 批量纹理集合
	@param [in] num 对象个数
	@return 返回纹理id的集合
	*/
	std::vector<uint32_t> createTextures(int32_t num);

	/** 选择纹理和类型
	@param [in] textureId 纹理id
	@param [in] textureType 纹理类型
	@param [in] textureName 着色器中的纹理变量名
	@param [in] textureIndex 着色器中的纹理位置，0-15，内部最多允许存在16个
	*/
	void selectTextureAndType(uint32_t textureId, int32_t textureType, const std::string& textureName, int32_t textureIndex);

	/** 销毁纹理
	@param [in] textureId 纹理id
	*/
	void destroyTexture(uint32_t textureId);

	/** 批量纹理的集合
	@param [in] textureIds 纹理id的集合
	*/
	void destroyTextures(const std::vector<uint32_t>& textureIds);

	/** 设置横轴方向纹理环绕方式
	@param [in] wrapType 纹理环绕类型
	*/
	void setTextureWrapTypeX(int32_t wrapType);

	/** 设置纵轴方向纹理环绕方式
	@param [in] wrapType 纹理环绕类型
	*/
	void setTextureWrapTypeY(int32_t wrapType);

	/** 设置深度方向纹理环绕方式
	@param [in] wrapType 纹理环绕类型
	*/
	void setTextureWrapTypeZ(int32_t wrapType);

	/** 当纹理类型为GL_TEXTURE_BORDER_COLOR时，设置背景边框颜色
	@param [in] r 红色，0-255
	@param [in] g 绿色，0-255
	@param [in] b 蓝色，0-255
	@param [in] a 透明度，0-100
	*/
	void setTextureBorderColor(int32_t r, int32_t g, int32_t b, int32_t a);

	/** 设置显示图小于原图的显示方式
	@param [in] filterShowType 显示方式
	@param [in] mipmapFilterShowType 多级渐远的纹理之间使用的显示方式，如果不为0表示使用多级渐远
	*/
	void setMinFilterType(int32_t filterShowType, int32_t mipmapFilterShowType = 0);

	/** 设置显示图大于原图的显示方式
	@param [in] filterShowType 显示方式
	*/
	void setMagFilterType(int32_t filterShowType);

	/** 加载纹理
	@param [in] width 图片宽度
	@param [in] height 图片高度
	@param [in] data 图片数据
	@param [in] imageChannels 图片通道
	*/
	void loadTexture(int32_t width, int32_t height, unsigned char* data, int32_t imageChannels);

	/** 加载RGB纹理
	@param [in] width 图片宽度
	@param [in] height 图片高度
	@param [in] data 图片数据
	*/
	void loadRGBTexture(int32_t width, int32_t height, unsigned char* data);

	/** 加载RGBA纹理
	@param [in] width 图片宽度
	@param [in] height 图片高度
	@param [in] data 图片数据
	*/
	void loadRGBATexture(int32_t width, int32_t height, unsigned char* data);

	/** 设置转换矩阵全局变量内容
	@param [in] location 变量索引位置
	@param [in] mat4 转换矩阵
	*/
	void setUniformValue(int32_t location, float* mat4);

	/** 搜索位置并设置转换矩阵全局变量内容
	@param [in] uniformName 变量名
	@param [in] mat4 转换矩阵
	*/
	void searchSetUniformValue(const std::string& uniformName, const float* mat4);

	///** 隐藏鼠标并限制鼠标在当前窗口中活动
	//*/
	//void hideMouseAndLimitScope();
//
	///** 设置鼠标移动的事件回调函数
	//@param [in] mouseMoveCallback 鼠标移动事件回调函数
	//*/
	//void setMouseMoveCallback(void(*mouseMoveCallback)(GLFWwindow*, double, double));
//
	///** 设置鼠标滚轮的事件回调函数
	//@param [in] mouseScrollCallback 鼠标滚轮事件回调函数
	//*/
	//void setMouseScrollCallback(void(*mouseScrollCallback)(GLFWwindow*, double, double));

	/** 设置所看位置的向量
	@param [in] x 鼠标所在位置的横轴
	@param [in] y 鼠标所在位置的纵轴
	@param [in] speed 显示的移动速度
	*/
	void setLookPosition(double x, double y, float speed);

	/** 获取当前所看位置向量
	@return 返回当前所看位置向量
	*/
	GlmVec3 getCameraLook();

	/** 获取上向量
	@return 返回上向量
	*/
	GlmVec3 getCameraUp();

	/** 获取前向量
	@return 返回前向量
	*/
	GlmVec3 getCameraFront();

	/** 设置绘制帧的间隔时间
	@param [in] deltaTime 绘制帧的间隔时间
	*/
	void setDeltaTime(float deltaTime);

	/** 初始化摄像头位置
	@param [in] cameraPos 摄像头位置
	*/
	void initCameraPos(const GlmVec3& cameraPos);

	/** 初始化上向量
	@param [in] cameraUp 上向量
	*/
	void initCameraUp(const GlmVec3& cameraUp);

	/** 初始化前向量，初始时观察位置和前向量一致
	@param [in] cameraFront 观察位置
	*/
	void initCameraFront(const GlmVec3& cameraFront);

	/** 平移摄像头
	@param [in] speed 平移速度
	@param [in] direct 平移方向
	*/
	void addCameraPosTranslate(double speed, const GlmVec3& direct);

	/** 设置当前所看位置向量
	@param [in] cameraLook 当前所看位置向量
	*/
	void setCameraLook(const GlmVec3& cameraLook);

	/** 设置摄像机位置向量
	@param [in] cameraPos 摄像机位置向量
	*/
	void setCameraPos(const GlmVec3& cameraPos);

	/** 获取摄像机位置
	@return 返回摄像机位置
	*/
	GlmVec3 getCameraPos();

	/** 设置线宽
	@param [in] lineWidth 线宽
	*/
	void setLineWidth(float lineWidth);

	/** float类型和0比较
	@param [in] num 值
	@return 返回是否是0值
	*/
	bool floatCompareZero(float num);

	/** 设置当前可执行文件所在路径
	@param [in] currentExePath 当前可执行文件所在路径
	*/
	void setCurrentExePath(const std::string& currentExePath);

	/** 获取当前可执行文件所在路径
	@return 返回当前可执行文件所在路径
	*/
	std::string GetCurrentExePath();

private:
	//OpenGL绘画指针
	cppgl::CppGL* m_GL;
	//当前执行路径
	std::string m_currentExePath;
	//当前操作的窗口指针
	GLFWwindow* m_window;
	//当前操作的着色器程序id
	int32_t m_programId;
	//当前操作的纹理类型
	int32_t m_textureType;
	//是否开启了深度测试
	bool m_isOpenDepthTest;
	//是否开启了模板缓冲
	bool m_isOpenStencilTest;
	//是否开启了混合
	bool m_isOpenBlend;
	//是否开启了面剔除
	bool m_isOpenCullFace;
	//绘制帧的间隔时间
	float m_deltaTime;
	//所看位置相对摄像头的向量
	GlmVec3* m_cameraLook;
	//摄像头位置
	GlmVec3* m_cameraPos;
	//前向量
	GlmVec3* m_cameraFront;
	//上向量
	GlmVec3* m_cameraUp;
	//大版本号
	int32_t m_major;
	//小版本号
	int32_t m_minor;
	//是否是es版本
	bool m_isES;
	//着色器名字
	std::shared_ptr<ShaderNameData> m_spShaderNameData;
};