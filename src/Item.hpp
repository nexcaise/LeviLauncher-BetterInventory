/// @symbolgeneration
#pragma once

class Item {
public:
    bool mAllowOffhand : 1;
    std::string mNamespace;
    std::string mRawNameId;
	Item& setAllowOffhand(bool allowOffhand);
};