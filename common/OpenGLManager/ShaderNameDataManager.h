#pragma once
#include <map>
#include <memory>
#include <string>

/** 着色器变量名类型
*/
enum ShaderNameType
{
	//初始化
	SHADER_NAME_TYPE_INIT,
	//顶点位置
	IN_POSITION,
	//法向量
	IN_NORMAL,
	//顶点颜色
	IN_COLOR,
	//纹理坐标
	IN_TEXCOORDS,
	//传出法向量
	OUT_NORMAL,
	//传出顶点颜色
	OUT_COLOR,
	//传出纹理坐标
	OUT_TEXCOORDS,
	//传出光栅化后面上的点位置
	OUT_FRAG_POS,
	//片段着色器中每个点的输出颜色
	OUT_FRAG_COLOR,
	//模型矩阵，包含平移旋转缩放
	MODEL,
	//观察矩阵
	VIEW,
	//投影矩阵
	PROJECTION,
	//环境光强度
	AMBIENT_STRENGTH,
	//漫反射强度
	DIFFUSE_STRENGTH,
	//光晕强度
	SPECULAR_STRENGTH,
	//反射强度
	SHININESS_STRENGTH,
	//物体颜色
	OBJECT_COLOR,
	//摄像机位置
	CAMERA_POS,
	//光源位置
	LIGHT_POS,
	//灯光颜色
	LIGHT_COLOR,
	//平行光方向
	LIGHT_DIRECTION,
	//照射方向
	SHINE_DIRECTION,
	//聚光切角
	CUT_OFF,
	//聚光外切角
	OUT_CUT_OFF,
	//衰减常数项
	CONSTANT,
	//衰减一次项
	LINEAR,
	//衰减二次项
	QUADRATIC,
	//纹理
	TEXTURE,
	//环境光的纹理图片
	TEXTURE_AMBIENT,
	//漫反射的纹理图片
	TEXTURE_DIFFUSE,
	//光晕的纹理图片
	TEXTURE_SPECULAR,
	//环境光分量
	AMBIENT,
	//标准化的法向量
	NORM,
	//片段点指向光源的方向
	FRAG_TO_LIGHT_DIR,
	//聚光的照射方向和照射到片段点方向的夹角
	THETA,
	//内角和外角差
	EPSILON,
	//弱化强度
	INTENSITY,
	//法向量和片段点和光源形成向量的余弦角
	DIFF_THETA,
	//漫反射分量
	DIFFUSE,
	//片段到摄像机的向量
	VIEW_DIRECTION,
	//光照到片段后的反射方向
	REFLECT_DIRECTION,
	//片段点上的光晕亮度系数
	SPEC,
	//镜面光分量
	SPECULAR,
	//光源到片段点的距离
	DISTANCE,
	//衰减系数
	ATTENUATION,
	//片段点颜色
	FRAG_COLOR
};

/** 着色器变量名
*/
struct ShaderNameData
{
	//纹理材质在着色器中的变量名
	std::map<ShaderNameType, std::pair<std::string, std::string>> m_name;

	/** 构造函数
	*/
	ShaderNameData()
	{
		m_name[IN_POSITION] = {"vec3", "aPos"};
		m_name[IN_NORMAL] = {"vec3", "aNormal"};
		m_name[IN_COLOR] = {"vec3", "aColor"};
		m_name[IN_TEXCOORDS] = {"vec2", "aTexCoords"};
		m_name[OUT_NORMAL] = {"vec3", "Normal"};
		m_name[OUT_COLOR] = {"vec3", "Color"};
		m_name[OUT_TEXCOORDS] = {"vec2", "TexCoords"};
		m_name[OUT_FRAG_POS] = {"vec3", "FragPos"};
		m_name[OUT_FRAG_COLOR] = {"vec4", "FragColor"};
		m_name[MODEL] = {"mat4", "model"};
		m_name[VIEW] = {"mat4", "view"};
		m_name[PROJECTION] = {"mat4", "projection"};
		m_name[AMBIENT_STRENGTH] = {"vec3", "ambientStrength"};
		m_name[DIFFUSE_STRENGTH] = {"vec3", "diffuseStrength"};
		m_name[SPECULAR_STRENGTH] = {"vec3", "specularStrength"};
		m_name[SHININESS_STRENGTH] = {"float", "shininessStrength"};
		m_name[OBJECT_COLOR] = {"vec3", "objectColor"};
		m_name[CAMERA_POS] = {"vec3", "cameraPos"};
		m_name[LIGHT_POS] = {"vec3", "lightPos"};
		m_name[LIGHT_COLOR] = {"vec3", "lightColor"};
		m_name[LIGHT_DIRECTION] = {"vec3", "lightDirection"};
		m_name[SHINE_DIRECTION] = {"vec3", "shineDirection"};
		m_name[CUT_OFF] = {"float", "cutOff"};
		m_name[OUT_CUT_OFF] = {"float", "outCutOff"};
		m_name[CONSTANT] = {"float", "constant"};
		m_name[LINEAR] = {"float", "linear"};
		m_name[QUADRATIC] = {"float", "quadratic"};
		m_name[TEXTURE] = {"sampler2D", "texture"};
		m_name[TEXTURE_AMBIENT] = {"sampler2D", "textureAmbient"};
		m_name[TEXTURE_DIFFUSE] = {"sampler2D", "textureDiffuse"};
		m_name[TEXTURE_SPECULAR] = {"sampler2D", "textureSpecular"};
		m_name[AMBIENT] = {"vec3", "ambient"};
		m_name[NORM] = {"vec3", "norm"};
		m_name[FRAG_TO_LIGHT_DIR] = {"vec3", "fragToLightDir"};
		m_name[THETA] = {"float", "theta"};
		m_name[EPSILON] = {"float", "epsilon"};
		m_name[INTENSITY] = {"float", "intensity"};
		m_name[DIFF_THETA] = {"float", "diffTheta"};
		m_name[DIFFUSE] = {"vec3", "diffuse"};
		m_name[VIEW_DIRECTION] = {"vec3", "viewDir"};
		m_name[REFLECT_DIRECTION] = {"vec3", "reflectDir"};
		m_name[SPEC] = {"float", "spec"};
		m_name[SPECULAR] = {"vec3", "specular"};
		m_name[DISTANCE] = {"float", "distance"};
		m_name[ATTENUATION] = {"float", "attenuation"};
		m_name[FRAG_COLOR] = {"vec3", "fragColor"};
	}
};

/** 着色器变量名管理类
*/
class ShaderNameDataManager
{
protected:
	/** 构造函数
	*/
	ShaderNameDataManager();

public:
	/** 单一实例
	@return 返回单一实例
	*/
	static ShaderNameDataManager& instance();

public:
	/** 从默认名字结构体中拷贝出一份新的名字结构体
	@return 返回名字结构体
	*/
	std::shared_ptr<ShaderNameData> copyFromDefaultShaderNameData();

	/** 返回默认名字结构体
	@return 返回名字结构体
	*/
	std::shared_ptr<ShaderNameData> defaultShaderNameData();

private:
	//名字结构体
	std::shared_ptr<ShaderNameData> m_spShaderNameData;
};