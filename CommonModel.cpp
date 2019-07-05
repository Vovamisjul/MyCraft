#include "CommonModel.h"

CommonModel::CommonModel(string path, const GLchar* vertexPath, const GLchar* fragmentPath) : Model::Model(path), Shader::Shader(vertexPath, fragmentPath)
{

}