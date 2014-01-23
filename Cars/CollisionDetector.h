#pragma once
#include "singleton.h"
#include <ISceneNode.h>
#include <vector>

class CollisionDetector :
    public Singleton<CollisionDetector>
{
public:
    typedef std::vector<irr::scene::ISceneNode*>  nodes_collection_t;
    void Register(irr::scene::ISceneNode* node);
    bool HasCollisions(irr::scene::ISceneNode* node, nodes_collection_t* collisedNodes = 0);

private:
    nodes_collection_t nodes_;
};
