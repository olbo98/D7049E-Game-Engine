#include "Coordinator.h"
#include "MeshRenderable.h"
#include "Transform.h"
#include "RenderSystem.h"
#include "EntityComponentDef.h"

Coordinator gCoordinator;

int main(int argc, char* argv[])
{
    gCoordinator.init();

    gCoordinator.registerComponent<MeshRenderable>();
    gCoordinator.registerComponent<Transform>();

    // Create render system and set the signature of the elements to draw
    auto renderSystem = gCoordinator.registerSystem<RenderSystem>();
    Signature signature;
    signature.set(gCoordinator.getComponentType<MeshRenderable>());
    gCoordinator.setSystemSignature<RenderSystem>(signature);

    renderSystem->Init();

    std::vector<Entity> entities(MAX_ENTITIES - 1);

	for (auto& entity : entities)
	{
		entity = gCoordinator.createEntity();
        //MeshRenderable entityRenderable;
        //entityRenderable.mesh 
		/*gCoordinator.addComponent(
			entity,
			MeshRenderable);*/
	}
    return 0;
}
