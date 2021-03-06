// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_CATEGORY
#define SSVMS_CATEGORY

namespace ssvms
{
    class Menu;
    class ItemBase;

    class Category
    {
        friend Menu;

    private:
        Menu& menu;
        std::string name;
        std::vector<std::unique_ptr<ItemBase>> items;
        int index{0};

        inline void wrapIndex()
        {
            if(index > ssvu::toInt(items.size() - 1))
                index = 0;
            else if(index < 0)
                index = items.size() - 1;
        }

    public:
        Category(Menu& mMenu, const std::string& mName)
            : menu(mMenu), name{mName}
        {
        }

        template <typename T, typename... TArgs>
        inline T& create(const std::string& mName, TArgs&&... mArgs)
        {
            return ssvu::getEmplaceUPtr<T>(
                items, menu, *this, mName, FWD(mArgs)...);
        }

        inline void next()
        {
            ++index;
            wrapIndex();
        }
        inline void previous()
        {
            --index;
            wrapIndex();
        }

        inline const auto& getName() const { return name; }
        inline auto& getItem() const { return *(items[index]); }
        inline const auto& getItems() const { return items; }
        inline int getIdx() { return index; }
    };
}

#endif
