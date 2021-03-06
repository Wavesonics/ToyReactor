//
// Created by Adam on 2/27/2020.
//

#ifndef REACTORCPP_HEATMAP_H
#define REACTORCPP_HEATMAP_H


#include <Godot.hpp>
#include <Node2D.hpp>
#include "../NeutronRegion/ReactorCore/ReactorCore.h"

namespace nuclearPhysics
{
	class HeatMap : public godot::Node2D
	{
	GODOT_CLASS(HeatMap, godot::Node2D)
	private:
		inline godot::Color calculateTempColor(const float value, const float min, const float max) const;
	protected:
		godot::NodePath reactorCorePath;
		nuclearPhysics::ReactorCore* reactorCore = nullptr;

		bool enableRendering = true;
		float minValue = 0.01f;
		float maxValue = 1.0f;
		float drawRectSize;

		virtual bool rangeCheck(const int x, const int y) const;
	public:
		int mapSize = DEFAULT_MAP_SIZE;
		float cellWidth = 1.0f;
		float cellHeight = 1.0f;
		float **map;

		HeatMap();

		~HeatMap();

		void calculateCellSizes(const godot::Rect2 &rect);

		virtual godot::Point2 toGrid(const godot::Vector2 &neutronPos) const;

		virtual void addHeat(float heat, const int x, const int y);

		virtual float readMagnitude(const int x, const int y) const;

		virtual void _init();

		virtual void _ready();

		virtual void _draw();

		static void _register_methods();

		static constexpr int DEFAULT_MAP_SIZE = 64;
		static constexpr int DEFAULT_DRAW_SIZE = 2.0f;
	};
}

#endif //REACTORCPP_HEATMAP_H
