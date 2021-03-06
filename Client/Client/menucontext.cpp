#include "menucontext.h"
#include "menuitem.h"
#include "ingamecontext.h"
#include "connectcontext.h"

namespace NeonHockey
{
    MenuContext::MenuContext(HGE* hge, std::shared_ptr<ResourceManager> rm, std::shared_ptr<MenuContextData> data)
        : IContext(hge, rm, data)
    {
        menu = new hgeGUI();

        DWORD shadowColor = ARGB(200, 255, 0, 0);
        DWORD itemColor = ARGB(255, 0, 255, 0);

        items.push_back(std::make_pair("Connect", "Connect to dedicated server"));
        items.push_back(std::make_pair("About", "Information about NeonHockey"));
        items.push_back(std::make_pair("Exit", "Exit game"));


        for(unsigned i = 0; i < items.size(); ++i)
            menu->AddCtrl(
                new hgeGUIMenuItem(i + 1,
                   _rm->getFont(FontType::MENU).get(),
#ifndef PLATFORM_UNIX
                   _rm->getSound(SoundType::COLLISION),
#else
                   0,
#endif
                   400, 200+40*i, float(i)/10.0,
                   (char*)items[i].first.c_str(),
                   itemColor, shadowColor));

        menu->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
    }


    IContextReturnData MenuContext::frameFunc()
    {
        float dt = _hge->Timer_GetDelta();

        id = menu->Update(dt);

        if(id == -1)
        {
            menu->Enter();
            menu->SetFocus(1);

            switch(lastId)
            {
            case ItemType::Connect:
                lastId = 0;
                return IContextReturnData(Context::ConnectContext, std::make_shared<ConnectContextData>(_data->screenWidth, _data->screenHeight));

            case ItemType::About:
                lastId = 0;
                break;
                //return IContextReturnData(Context::InGameContext, new InGameContextData(_data->screenWidth, _data->screenHeight, 0));

            case ItemType::Exit:
                lastId = 0;
                return IContextReturnData(Context::NoContext, nullptr);
            }
        }
        else if(id)
        {
            lastId = id;
            menu->Leave();
        }

        return IContextReturnData(Context::MenuContext, _data);
    }

    void MenuContext::renderFunc()
    {
        auto statusFont = _rm->getFont(FontType::STATUSBAR);

        menu->Render();
        int id = menu->GetFocus();
        if(id) //TODO: too many magics
            statusFont->Render(10, 600-32, 0, items[id-1].second.c_str());
    }

    void MenuContext::show()
    {
        menu->Enter();
        menu->SetFocus(ItemType::Connect);
    }

    MenuContext::~MenuContext()
    {
        delete menu;
    }
}
