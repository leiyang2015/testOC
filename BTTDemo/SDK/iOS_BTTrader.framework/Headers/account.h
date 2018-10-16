
#pragma once

#include "authority.h"
#include "util.h"
#include <string>

namespace bytetrade {
    
    class account {
    public:
        //  public static final String KEY_NAME = "id";
        //   public static final String KEY_OWNER = "owner";
        //   public static final String KEY_ACTIVE = "active";
        
        std::string id;
        
        authority owner;
        
        authority active;
        
        account(std::string name) {
            id = name;
        }
        
        account(jsonxx::Object o) {
            id = o.get<std::string>("id");
            owner = authority(o.get<jsonxx::Object>("owner"));
            active = authority(o.get<jsonxx::Object>("active"));
        }
        
        jsonxx::Object toJsonObject() {
            jsonxx::Object account;
            account << "id" << id;
            account << "owner" << owner.toJsonObject();
            account << "active" << active.toJsonObject();
            
            return account;
        }
        
        jsonxx::Object toRegisterObject() {
            jsonxx::Object account;
            account << "id" << id;
            account << "owner" << owner.toRegisterObject();
            account << "active" << active.toRegisterObject();
            
            return account;
        }
    };
}

