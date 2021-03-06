//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPP_NEUTRONFIELD_H
#define REACTORCPP_NEUTRONFIELD_H

#include <vector>
#include <Godot.hpp>
#include <Node2D.hpp>
#include "Neutron.h"
#include "BatchResult.h"
#include "../NeutronRegion/ReactorCore/ReactorCore.h"
#include "../NeutronRegion/NeutronRegion.h"
#include "../HeatMap/HeatMap.h"
#include "../HeatMap/DiffusingHeatMap.h"
#include "../../util/ThreadPool.h"
#include "BspTree/BspTree.h"
#include "BspTree/BspTreeNode.h"


namespace nuclearPhysics
{
	class NeutronField : public godot::Node2D
	{
	GODOT_CLASS(NeutronField, godot::Node2D)
	private:
		nuclearPhysics::ThreadPool *threadPool;
		int numWorkers;

		std::vector<nuclearPhysics::Neutron> neutrons;
		std::vector<int> toRemove;
		std::vector<std::vector<int> *> workerScratchSpace;

		int maxPopulation = 100000;
		bool enableRendering = true;
		int maxRender = DEFAULT_MAX_RENDER;

		godot::NodePath reactorCorePath;
		nuclearPhysics::ReactorCore *reactorCore = nullptr;

		float biproduct = DEFAULT_BIPRODUCT;
		float biproductDecayRate = DEFAULT_BIPRODUCT_DECAY_RATE;
		float biproductFissionRate = DEFAULT_BIPRODUCT_FISSION_RATE;
		godot::NodePath biproductMapPath;
		nuclearPhysics::HeatMap *biproductMap = nullptr;

		godot::NodePath thermalMapPath;
		nuclearPhysics::DiffusingHeatMap *thermalMap = nullptr;

		int neutronFlux = 0;

		void processFissionBiproducts();

		bool processFissionBiproductBatch(float *row, int yy);

		std::vector<nuclearPhysics::NeutronRegion *> regions;
		nuclearPhysics::BspTree bspTree;
		int bspTreeDepth;

		void initBspTree();

		void debugTreeDraw(const BspTreeNode *node, int level);

		BatchResult processNeutronBatch(std::vector<int> *removal, int start, int end, float delta);

		godot::Color neutronThermalColor;
		godot::Color neutronRelativisticColor;
	public:
		NeutronField();

		~NeutronField();

		int getMaxPopulation() const;

		void setCapacity(int capacity);

		void addNeutronRegion(nuclearPhysics::NeutronRegion *region);

		void addNeutron(const nuclearPhysics::Neutron &neutron);

		void createNeutron(const godot::Vector2 position, const godot::Vector2 velocity);

		int numNeutrons() const;

		int getNeutronFlux() const;

		void addFissionBiproduct(const godot::Vector2 &position);

		godot::Point2 toHeatGrid(const godot::Vector2 &position) const;

		void addHeat(const godot::Vector2 &position, const float heat);

		float readHeat(const godot::Vector2 &position) const;

		virtual void _init();

		virtual void _ready();

		virtual void _physics_process(float delta);

		virtual void _draw();

		static void _register_methods();

		static constexpr int DEFAULT_BSP_TREE_DEPTH = 3;
		static constexpr int DEFAULT_MAX_RENDER = 1000;
		static constexpr float DEFAULT_BIPRODUCT = 0.01f;
		static constexpr float DEFAULT_BIPRODUCT_FISSION_RATE = 0.01f;
		static constexpr float DEFAULT_BIPRODUCT_DECAY_RATE = 0.00025f;
		inline static const char *GROUP = "neutron_field";
	};
}


#endif //REACTORCPP_NEUTRONFIELD_H
