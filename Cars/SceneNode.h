#pragma once
#include <ISceneNode.h>

class SceneNode
{
protected:
    irr::scene::ISceneNode* node_;

public:
    SceneNode(void)
    {
    }

    virtual ~SceneNode(void)
    {
    }

    operator irr::scene::ISceneNode*()
    {
        return node_;
    }
};
