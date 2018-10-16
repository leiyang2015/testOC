#pragma once

#include "address.h"
#include "util.h"
#include <map>

namespace bytetrade {
    class authority {
    public:
        //  public static final String KEY_ACCOUNT_AUTHS = "account_auths";
        //     public static final String KEY_KEY_AUTHS = "key_auths";
        //     public static final String KEY_ADDRESS_AUTHS = "address_auths";
        //     public static final String KEY_WEIGHT_THRESHOLD = "weight_threshold";
        //   //  public static final String KEY_EXTENSIONS = "extensions";
        
        long weight_threshold;
        
        std::map<string, uint64_t> address_auths;
        //private Extensions extensions;
        
        authority() {
            weight_threshold = 1;
            address_auths.clear();
        }
        
        authority(jsonxx::Object o) {
            
            weight_threshold = o.get<long>("weight_threshold");
            jsonxx::Array array = o.get<jsonxx::Array>("address_auths");
            for (size_t i = 0; i < array.size(); ++i) {
                jsonxx::Array o1 = array.get<jsonxx::Array>(i);
                
                std::string add = o1.get<string>(0);
                //LogUtils.i("AccountGetEvent " + add);
                //address ad(add);
                address_auths[add] = o1.get<long>(1);
            }
        }
        
        // void setAddressAuthorities(HashMap<Address, Long> keyAuths) {
        //     if (keyAuths != null) {
        //         for (Address address : keyAuths.keySet()) {
        //             address_auths.put(address, keyAuths.get(address));
        //         }
        //     }
        // }
        
        // void setAccountAuthorities(HashMap<UserAccount, Long> accountAuthorities) {
        //     this.account_auths = accountAuthorities;
        // }
        
        jsonxx::Object toJsonObject();
        jsonxx::Object toRegisterObject();
        
    };
}

