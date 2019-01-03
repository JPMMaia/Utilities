#ifndef MAIA_UTILITIES_GLTF_H_INCLUDED
#define MAIA_UTILITIES_GLTF_H_INCLUDED

#include <cstddef>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <Eigen/Geometry>
#include <nlohmann/json.hpp>

namespace Maia::Utilities::glTF
{
	struct Accessor
	{
		std::optional<std::size_t> buffer_view_index;
		std::size_t component_type;
		std::size_t count;
		std::string type;
		std::optional<Eigen::Vector3f> max;
		std::optional<Eigen::Vector3f> min;
	};

	void from_json(nlohmann::json const& json, Accessor& value);
	void to_json(nlohmann::json& json, Accessor const& value);


	struct Buffer
	{
		std::optional<std::string> uri;
		std::size_t byte_length;
	};

	void from_json(nlohmann::json const& json, Buffer& value);
	void to_json(nlohmann::json& json, Buffer const& value);


	struct Buffer_view
	{
		std::size_t buffer_index;
		std::size_t byte_offset{ 0 };
		std::size_t byte_length;
	};

	void from_json(nlohmann::json const& json, Buffer_view& value);
	void to_json(nlohmann::json& json, Buffer_view const& value);


	struct PbrMetallicRoughness
	{
		Eigen::Vector4f base_color_factor{ 1.0f, 1.0f, 1.0f, 1.0f };
		float metallic_factor{ 1.0f };
		float roughness_factor{ 1.0f };
	};

	void from_json(nlohmann::json const& json, PbrMetallicRoughness& value);
	void to_json(nlohmann::json& json, PbrMetallicRoughness const& value);


	struct Material
	{
		std::optional<std::string> name;
		PbrMetallicRoughness pbr_metallic_roughness{};
		Eigen::Vector3f emissive_factor{ 0.0f, 0.0f, 0.0f };
		std::string alpha_mode{ "OPAQUE" };
		float alpha_cutoff{ 0.5f };
		bool double_sided{ false };
	};

	void from_json(nlohmann::json const& json, Material& value);
	void to_json(nlohmann::json& json, Material const& value);


	struct Primitive
	{
		std::unordered_map<std::string, std::size_t> attributes;
		std::optional<std::size_t> indices_index;
		std::optional<std::size_t> material_index;
	};

	void from_json(nlohmann::json const& json, Primitive& value);
	void to_json(nlohmann::json& json, Primitive const& value);


	struct Mesh
	{
		std::vector<Primitive> primitives;
		std::optional<std::string> name;
	};

	void from_json(nlohmann::json const& json, Mesh& value);
	void to_json(nlohmann::json& json, Mesh const& value);


	struct Node
	{
		Eigen::Matrix4f matrix{ Eigen::Matrix4f::Identity() };
		std::optional<std::size_t> mesh_index;
		Eigen::Quaternionf rotation{ Eigen::Quaternionf::Identity() };
		Eigen::Vector3f scale{ Eigen::Vector3f::Ones() };
		Eigen::Vector3f translation{ Eigen::Vector3f::Zero() };
		std::optional<std::string> name;
	};

	void from_json(nlohmann::json const& json, Node& value);
	void to_json(nlohmann::json& json, Node const& value);


	struct Scene
	{
		std::optional<std::string> name;
		std::optional<std::vector<std::size_t>> nodes;
	};

	void from_json(nlohmann::json const& json, Scene& value);
	void to_json(nlohmann::json& json, Scene const& value);


	struct Gltf
	{
		std::optional<std::vector<Accessor>> accessors;
		std::optional<std::vector<Buffer>> buffers;
		std::optional<std::vector<Buffer_view>> buffer_views;
		std::optional<std::vector<Material>> materials;
		std::optional<std::vector<Mesh>> meshes;
		std::optional<std::vector<Node>> nodes;
		std::optional<std::size_t> scene_index;
		std::optional<std::vector<Scene>> scenes;
	};

	void from_json(nlohmann::json const& json, Gltf& value);
	void to_json(nlohmann::json& json, Gltf const& value);

}

#endif
