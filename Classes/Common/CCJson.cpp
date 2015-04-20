
#include "CCJson.h"

using namespace json;
using namespace cocos2d;

CCJsonObject *visit_cJOSON(cJSON *cjson) {
      CCJsonObject *json = nullptr;
      switch (cjson->type) {
            case cJSON_False:
                  json =  CCJsonBool::create(false);
                  break;
            case cJSON_True:
                  json =  CCJsonBool::create(true);
                  break;
            case cJSON_NULL:
                  json = CCJsonNull::create();
                  break;
            case cJSON_Number:
                  json = CCJsonNumber::create(cjson->valuedouble);
                  break;
            case cJSON_String:
                  json = CCJsonString::create(cjson->valuestring);
                  break;
            case cJSON_Array:
            {
                  CCJsonArray *array = CCJsonArray::create(cJSON_GetArraySize(cjson));
                  cJSON *child = cjson->child;
                  while (child) {
                        array->addObject(visit_cJOSON(child));
                        child = child->next;
                  }
                  json = array;
                  break;
            }
            case cJSON_Object:
            {
                  CCJsonDictionary *dic = CCJsonDictionary::create(cJSON_GetArraySize(cjson));
                  cJSON *child = cjson->child;
                  while (child) {
                        dic->setObject(visit_cJOSON(child), child->string);
                        child = child->next;
                  }
                  json = dic;
                  break;
            }
            default:
                  json = CCJsonNull::create();
                  break;
      }
      return json;
}

cJSON *visit_CCJsonObject(CCJsonObject *json) {
      cJSON *cjson = nullptr;
      switch (json->type()) {
            case CCJsonType::NullObject:
                  cjson = cJSON_CreateNull();
                  break;
            case CCJsonType::Number:
                  cjson = cJSON_CreateNumber(static_cast<CCJsonNumber*>(json)->doubleValue());
                  break;
            case CCJsonType::Bool:
                  cjson = cJSON_CreateBool(static_cast<CCJsonBool*>(json)->value());
                  break;
            case CCJsonType::String:
                  cjson = cJSON_CreateString(static_cast<CCJsonString*>(json)->value().c_str());
                  break;
            case CCJsonType::Array:
            {
                  cjson = cJSON_CreateArray();
                  CCJsonArray::VectorType &vec = static_cast<CCJsonArray*>(json)->getCCVector();
                  for (auto obj : vec) {
                        cJSON_AddItemToArray(cjson, visit_CCJsonObject(static_cast<CCJsonObject*>(obj)));
                  }
                  break;
            }
            case CCJsonType::Dictionary:
            {
                  cjson = cJSON_CreateObject();
                  CCJsonDictionary::MapType &map = static_cast<CCJsonDictionary*>(json)->getCCMap();
                  for(auto kv : map) {
                        cJSON_AddItemToObject(cjson, kv.first.c_str(), visit_CCJsonObject(kv.second));
                  }
                  break;
            }
            default:
                  cjson = cJSON_CreateNull();
                  break;
      }
      return cjson;
};

CCJsonObject *CCJson::parse(const char *data) {
      cJSON *cjson = cJSON_Parse(data);
      if (cjson == nullptr) {
            return nullptr;
      }
      CCJsonObject *json = visit_cJOSON(cjson);
      cJSON_Delete(cjson);
      return json;
}

const char* CCJson::print(std::string &data_out, CCJsonObject* json) {
      cJSON *cjson = visit_CCJsonObject(json);
      char *out = nullptr;
      if (cjson) {
            out = cJSON_Print(cjson);
            data_out = out;
            cJSON_Delete(cjson);
            free(out);
      }
      return data_out.c_str();
}

CCJsonObject *CCJson::readFormFile(const std::string& path) {
      std::string data = cc::FileUtils::getInstance()->getStringFromFile(path);
      return parse(data);
}

size_t CCJson::writeToFile(const std::string& path, CCJsonObject* json) {
      std::string filepath = cc::FileUtils::getInstance()->getWritablePath() + path;
      FILE *fp = fopen(filepath.c_str(), "w");
      if (!fp || !json) {
            return 0;
      }
      std::string data("");
      print(data, json);
      size_t size = fwrite(data.c_str(), sizeof(char), data.size(), fp);
      fclose(fp);
      return size;
}

CCJsonDictionary *CCJsonDictionary::create(const std::string& filePath) {
      CCJsonObject *json = CCJson::readFormFile(filePath);
      return dynamic_cast<CCJsonDictionary*>(json);
}

CCJsonArray *CCJsonArray::create(const std::string& filePath) {
      CCJsonObject *json = CCJson::readFormFile(filePath);
      return dynamic_cast<CCJsonArray*>(json);
}

