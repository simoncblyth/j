#include "Material.h"

std::map<std::string, Material*> Material::materials;

Material::Material(std::string name, double n_value, double k_value) :
    fName(name)
{
    n = TComplex(n_value, k_value);
    materials.insert(std::pair<std::string, Material*>(name, this));
}

Material::~Material()
{
}

Material* Material::GetMaterial(std::string name)
{
    std::map<std::string, Material*>::iterator iter;
    iter = materials.find(name);
    if(iter != materials.end()){
        return iter->second;
    }else{
        std::cout<<name<<" not found !!!"<<std::endl;
        exit(0);
    }
}
