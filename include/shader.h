#pragma once

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char( fragmentPath);

    void use();

    void setBool(const std::string &name, bool vlaue) const;
    void setInt(const std::string &name, bool vlaue) const;
    void setFloat(const std::string &name, bool vlaue) const;
};

Shader(const char* vertexPath, const char( fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
}
