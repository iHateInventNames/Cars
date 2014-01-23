#include "StdAfx.h"
#include "CollisionDetector.h"


void CollisionDetector::Register( irr::scene::ISceneNode* node )
{
    nodes_.push_back(node);
}

bool CollisionDetector::HasCollisions( irr::scene::ISceneNode* node, nodes_collection_t* collisedNodes /*= 0*/ )
{
    using namespace irr;
    using namespace core;
    aabbox3d<f32> sourceNodeBox = node->getBoundingBox();
    node->getRelativeTransformation().transformBoxEx(sourceNodeBox);

    bool intersectionDetected = false;
    for (nodes_collection_t::iterator it = nodes_.begin(); it != nodes_.end(); ++it)
    {
        if (*it != node)
        {
            aabbox3d<f32> targetBox = (*it)->getBoundingBox();
            (*it)->getRelativeTransformation().transformBoxEx(targetBox);
            if (sourceNodeBox.intersectsWithBox(targetBox))
            {
                // collision detected
                intersectionDetected = true;
                if (collisedNodes)
                {
                    collisedNodes->push_back(*it);
                }
            }
        }
    }

    return intersectionDetected;
}